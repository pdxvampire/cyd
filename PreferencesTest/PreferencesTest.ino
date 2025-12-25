#include <TFT_eSPI.h>
#include <CST820.h>
#include <lvgl.h>
#include <Preferences.h>

// Prevent stack overflow reboot loops.
SET_LOOP_TASK_STACK_SIZE(16 * 1024);

TFT_eSPI tft = TFT_eSPI();

#include "logging.h"
#include "settings.h"

//LEFTOFF = ADD THE GUI SLIDER TO SAVE/LOAD/SETBRIGHTNESSONLOAD, GET THAT WORKING AS A UNIT TEST

unsigned long lastLvTick = 0;

lv_style_t popuplabelstyle;
lv_style_t style_pr;
lv_obj_t *popuplabel;
lv_obj_t *screen1;
lv_obj_t *screen2;
lv_obj_t *settingsscreen;
lv_obj_t *btn1;
lv_obj_t *btn2;
lv_obj_t *label1;
lv_obj_t *label2;
lv_obj_t *label3;
lv_obj_t *slider;
lv_obj_t *slider_label;

lv_display_t *disp;

int brightness = -1;

static CST820 touch(33, 32, 25, 21);  // Touch: SDA, SCL, RST, INT

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define LVGL_TICK_PERIOD 2
uint16_t rawX, rawY;

/* Draw buffer for LVGL */
static uint8_t draw_buf[SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8)];


void HandleTouch(lv_indev_t *indev, lv_indev_data_t *data)
{
    if (touch.getTouch(&rawX, &rawY))
    {
        data->state = LV_INDEV_STATE_PRESSED;

        ///// without LVGL use this for portrait with USB at top
        /////        data->point.x = 240 - rawX - 1;
        /////        data->point.y = 320 - rawY - 1;

        ///// with LVGL the raw coords are correct
        data->point.x = rawX;
        data->point.y = rawY;

        logit("🖐 LVGL Touch at (%d, %d) | Raw: (%d, %d)",
              data->point.x, data->point.y, rawX, rawY);
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void InitializeTouch()
{
    enterfunction("InitializeTouch");

    // Initialize touchscreen
    touch.begin();
    logit("🔍 Touch Chip ID: 0x%02X", touch.readChipID());

    // LVGL Input device (touch)
    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, HandleTouch);

    // Gestures
    /* Set the minimum gesture velocity to 10 pixels/second */
    indev->gesture_min_velocity = 2;
    indev->gesture_limit = 4;  // Make it more sensitive (trigger after 10px)

    exitfunction("InitializeTouch");
}

void HandleBrightnessSlider(lv_event_t *e)
{
    int percentage = lv_slider_get_value(slider);
    int val = (int)map(percentage, 0, 100, 0, 255);  // brightness is 0..255, show user-friendly percentage 0..100

    switch (lv_event_get_code(e))
    {
        case LV_EVENT_VALUE_CHANGED:
            static char buf[4]; /* max 3 bytes for number plus 1 null terminating byte */
            snprintf(buf, 4, "%u", percentage);
            lv_label_set_text(slider_label, buf);
            logit("🎚 Slider changed, value: %d, pct: %d", val, percentage);
            break;

        case LV_EVENT_RELEASED:
            logit("🎚 Slider released, value: %d, pct: %d", val, percentage);
            analogWrite(TFT_BL, val);  // backlight pin is 27
            SetBrightness(val);
            break;
    }
}

void setup()
{
    Serial.begin(115200);

    // Wait for the serial port to connect so the Serial Monitor printouts work consistently
    // This may not be necessary on Windows or Linux but with my Macbook Air M3 (2024) it is.
    delay(2000);
    logit("");  // insert a newline after the random garbage that gets printed on connection/powerup

    logheader("PreferencesTest");
    loglevel++;  // would normally be part of the call to enterfunction for InitializeSerialCommunication()

digitalWrite(TFT_BL, 0); 
    // Initialise the TFT
    tft.begin();

    // Clear TFT screen
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.fillScreen(TFT_BLACK);
    // Example: fuschia
    // uint16_t fuschia = tft.color565(255, 0, 255);
    //tft.fillScreen(fuschia);

    // Initialize LVGL
    lv_init();

    // Register print function for LVGL debugging
#if LV_USE_LOG != 0
    lv_log_register_print_cb(log_print);
#endif

    // register LVGL display using the built-in TFT_eSPI helper
    disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
//lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);

    pinMode(TFT_BL, TFT_BACKLIGHT_ON);  // defined in User_Setup.h
    brightness = GetBrightness();
    logit("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ analogwrite: %d",brightness);
    analogWrite(TFT_BL, brightness);  // backlight pin is 27, range is 0..255


    // set display rotation for both tft and LVGL to match
    tft.setRotation(0);
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_180);



    InitializeTouch();

    logit("create slider");
    slider = lv_slider_create(lv_screen_active());
    lv_obj_set_width(slider, 170);
    lv_obj_align(slider, LV_ALIGN_LEFT_MID, 10, 0);
    lv_obj_add_event_cb(slider, HandleBrightnessSlider, LV_EVENT_ALL, NULL);
    lv_slider_set_range(slider, 10, 100);  // don't allow turning completely off or there is no way to turn it back on
    // Saved value is the real 10..255, convert here to % for the slider.
    int percentage = (int)map(GetBrightness(), 0, 255, 0, 100);
    logit("############################################### int percentage: %d", percentage);
    lv_slider_set_value(slider, percentage, LV_ANIM_OFF);
    logit("create slider label");
    slider_label = lv_label_create(lv_screen_active());
    String tmpstrpct = String(percentage);
    logit("############################################### String tmpstrpct: %s", tmpstrpct);
    const char *pct = tmpstrpct.c_str();
    logit("############################################### const char* pct: %s", pct);
    lv_label_set_text(slider_label, pct);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_RIGHT_TOP, 30, 0);
}

void loop()
{
     if (millis() - lastLvTick > LVGL_TICK_PERIOD)
    {
        lv_tick_inc(LVGL_TICK_PERIOD);  // tell LVGL how much time has passed
        lastLvTick = millis();
    }

    lv_task_handler();        // let the GUI do its work
    delay(LVGL_TICK_PERIOD);  // let this time pass
}
