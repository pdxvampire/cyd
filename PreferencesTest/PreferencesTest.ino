#include <TFT_eSPI.h>
#include <CST820.h>
#include <lvgl.h>
#include <Preferences.h>

// Prevent stack overflow reboot loops.
SET_LOOP_TASK_STACK_SIZE(16 * 1024);

TFT_eSPI tft = TFT_eSPI();

#include "logging.h"
#include "settings.h"
#include "uicallbacks.h"
#include "touch.h"

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
lv_obj_t *main_container;
lv_obj_t *brightness_container;
lv_obj_t *brightness_sliderandlabel_container;
lv_obj_t *brightness_slider;
lv_obj_t *brightness_label;
lv_obj_t *brightness_title;
lv_obj_t *darkmode_container;
lv_obj_t *darkmode_switch;
lv_obj_t *darkmode_title;
lv_obj_t *titlebar_container;
lv_obj_t *main_title;
lv_obj_t *close_button;

lv_obj_t *test_container;
lv_obj_t *test_title;
lv_obj_t *test_button;

lv_display_t *disp;

int brightness = -1;
bool darkmode = true;
int percentage;
const char *pct;

static CST820 touch(33, 32, 25, 21);  // Touch: SDA, SCL, RST, INT

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define LVGL_TICK_PERIOD 2
uint16_t rawX, rawY;

/* Draw buffer for LVGL */
static uint8_t draw_buf[SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8)];





void CreateMainContainer()
{
    //
    // Create main container with COLUMN flex direction
    // brightness_container
    // darkmode_container
    main_container = lv_obj_create(lv_screen_active());
    lv_obj_set_layout(main_container, LV_LAYOUT_FLEX);

    lv_obj_set_flex_flow(main_container, LV_FLEX_FLOW_COLUMN);  // reverse so the title can be created later and still ends up visually on top
    // Set width and height to 100% of the parent's content area
    lv_obj_set_size(main_container, LV_PCT(100), LV_PCT(100));
    // Comment this during testing to see the container border so you know it's what you want.
    ////lv_obj_set_style_border_width(main_container, 0, 0);
}

void CreateContainers()
{
    //
    // Create brightness container with COLUMN flex direction
    // TITLE
    // brightness_sliderandlabel_container
    //
    //////////
    //////////lv_obj_set_flex_flow(brightness_container, LV_FLEX_FLOW_COLUMN_REVERSE);  // reverse so the title can be created later and still ends up visually on top
    //////////lv_obj_set_width(brightness_container, lv_pct(100));
    //////////lv_obj_set_flex_grow(brightness_container, 1);  // fill remaining space
    ////lv_obj_set_height(brightness_container, LV_SIZE_CONTENT);  // grow/shrink based on content
    // Comment this during testing to see the container border so you know it's what you want.
    //lv_obj_set_style_border_width(brightness_container, 0, 0);


    //
    // Create brightness_sliderandlabel_container with ROW direction
    // SLIDER | LABEL
    //
    ////////// brightness_sliderandlabel_container = lv_obj_create(main_container);
    ////////// lv_obj_set_flex_flow(brightness_sliderandlabel_container, LV_FLEX_FLOW_ROW);
    ////////// lv_obj_set_width(brightness_sliderandlabel_container, lv_pct(100));
    //////////lv_obj_set_width(brightness_sliderandlabel_container, LV_SIZE_CONTENT);
    ///    lv_obj_set_flex_grow(brightness_sliderandlabel_container, 1);
    ///    //lv_obj_set_style_border_width(brightness_sliderandlabel_container, 0, 0);
}

void CreateTitleBar()
{
    titlebar_container = lv_obj_create(main_container);
    lv_obj_set_flex_flow(titlebar_container, LV_FLEX_FLOW_ROW);
    lv_obj_set_width(titlebar_container, lv_pct(100));
    lv_obj_set_height(titlebar_container, LV_SIZE_CONTENT);  // grow/shrink based on content

    main_title = lv_label_create(titlebar_container);
    lv_label_set_text(main_title, "SETTINGS");
    lv_obj_set_flex_grow(main_title, 1);

    close_button = lv_label_create(titlebar_container);
    lv_label_set_text(close_button, "X");
}

void CreateBrightness()
{
    brightness_container = lv_obj_create(main_container);
    lv_obj_set_flex_flow(brightness_container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_width(brightness_container, lv_pct(100));
    lv_obj_set_height(darkmode_container, LV_SIZE_CONTENT); // grow/shrink based on content
    //////lv_obj_set_flex_grow(darkmode_container, 1);  // fill remaining space
    // Comment this during testing to see the container border so you know it's what you want.
    
brightness_title = lv_label_create(brightness_container);
    lv_label_set_text(brightness_title, "Brightness");
    
    brightness_sliderandlabel_container = lv_obj_create(brightness_container);
    lv_obj_set_flex_flow(brightness_sliderandlabel_container, LV_FLEX_FLOW_ROW);
    lv_obj_set_width(brightness_sliderandlabel_container, lv_pct(100));
    lv_obj_set_height(brightness_sliderandlabel_container, LV_SIZE_CONTENT);  // grow/shrink based on content

    brightness_slider = lv_slider_create(brightness_sliderandlabel_container);
    lv_slider_set_range(brightness_slider, 10, 100);  // don't allow turning completely off or there is no way to turn it back on
    lv_obj_set_flex_grow(brightness_slider, 3);
    //////////lv_obj_add_event_cb(brightness_slider, HandleBrightnessSlider, LV_EVENT_ALL, NULL);

logit("create slider label");
    brightness_label = lv_label_create(brightness_sliderandlabel_container);
lv_label_set_text(brightness_label, pct);
lv_obj_set_flex_grow(brightness_label, 1);

    // lv_obj_align(brightness_container, LV_ALIGN_TOP_MID, 0, 5);
    //lv_obj_set_size(brightness_container, LV_PCT(100),LV_SIZE_CONTENT); // fill wid to content, width 100%

    //lv_obj_set_flex_grow(brightness_title, 1);

    //////////logit("create brightness slider");
    //////////brightness_slider = lv_slider_create(brightness_sliderandlabel_container);
    //lv_obj_set_width(slider, 150);
    //lv_obj_align(slider, LV_ALIGN_LEFT_MID, 20, 0);
    //////////lv_obj_add_event_cb(brightness_slider, HandleBrightnessSlider, LV_EVENT_ALL, NULL);
    //////////lv_slider_set_range(brightness_slider, 10, 100);  // don't allow turning completely off or there is no way to turn it back on
    //////////lv_slider_set_value(brightness_slider, percentage, LV_ANIM_OFF);
    
    //////////
    //lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_RIGHT_TOP, 20, 0);

    //////////lv_obj_set_flex_grow(brightness_slider, 3);
    //////////lv_obj_set_flex_grow(brightness_label, 1);
    //////////lv_obj_set_style_pad_gap(brightness_sliderandlabel_container, 0, LV_PART_MAIN);
}

void CreateTest()
{
    test_container = lv_obj_create(main_container);
    lv_obj_set_flex_flow(test_container, LV_FLEX_FLOW_ROW);
    lv_obj_set_width(test_container, lv_pct(100));
    lv_obj_set_height(test_container, LV_SIZE_CONTENT);  // grow/shrink based on content

    test_title = lv_label_create(test_container);
    lv_label_set_text(test_title, "FOO BAR BAZ");
    lv_obj_set_flex_grow(test_title, 1);

    test_button = lv_label_create(test_container);
    lv_label_set_text(test_button, "X");
}

void CreateDarkMode()
{
    //
    // Create darkmode container with COLUMN direction
    // TITLE
    // SWITCH
    //
    darkmode_container = lv_obj_create(main_container);
    lv_obj_set_flex_flow(darkmode_container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_width(darkmode_container, lv_pct(100));
    //lv_obj_set_height(darkmode_container, LV_SIZE_CONTENT); // grow/shrink based on content
    lv_obj_set_flex_grow(darkmode_container, 1);  // fill remaining space
    // Comment this during testing to see the container border so you know it's what you want.
    // lv_obj_set_style_border_width(darkmode_container, 0, 0);

    //lv_obj_set_size(darkmode_container, 200, 150);
    //  lv_obj_align_to(darkmode_container, brightness_container, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

    darkmode_title = lv_label_create(darkmode_container);
    lv_label_set_text(darkmode_title, "Dark Mode");

    darkmode_switch = lv_switch_create(darkmode_container);

    //lv_obj_align_to(swdarkmode, slider, LV_ALIGN_BOTTOM_MID, 0, 80);
    lv_obj_add_event_cb(darkmode_switch, swdarkmode_event_handler, LV_EVENT_ALL, NULL);
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
    //tft.setTextColor(TFT_WHITE, TFT_BLACK);
    //tft.fillScreen(TFT_BLACK);
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
    logit("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ analogwrite: %d", brightness);
    analogWrite(TFT_BL, brightness);  // backlight pin is 27, range is 0..255

    darkmode = GetDarkMode();

    // set display rotation for both tft and LVGL to match
    tft.setRotation(0);
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_180);

    InitializeTouch();

    // Saved value is the real 10..255, convert here to % for the slider.
    percentage = (int)map(GetBrightness(), 0, 255, 0, 100);
    logit("############################################### int percentage: %d", percentage);
    String tmpstrpct = String(percentage);
    logit("############################################### String tmpstrpct: %s", tmpstrpct);
    pct = tmpstrpct.c_str();
    logit("############################################### const char* pct: %s", pct);


    //CreateContainers();
    CreateMainContainer();
    CreateTitleBar();
    CreateBrightness();
    CreateDarkMode();
    //CreateTest();
    
    if (darkmode)
    {
        lv_obj_set_style_bg_color(lv_screen_active(), lv_color_black(), LV_PART_MAIN);
        ApplyDarkModeToSettingsScreen();
    }
    else
    {
        lv_obj_set_style_bg_color(lv_screen_active(), lv_color_white(), LV_PART_MAIN);
        ApplyLightModeToSettingsScreen();
    }
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
