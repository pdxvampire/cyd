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
#include "theme.h"
#include "layout.h"

unsigned long lastLvTick = 0;

lv_display_t *disp;

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define LVGL_TICK_PERIOD 2

/* Draw buffer for LVGL */
static uint8_t draw_buf[SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8)];

void setup()
{
    Serial.begin(115200);

    // Wait for the serial port to connect so the Serial Monitor printouts work consistently
    // This may not be necessary on Windows or Linux but with my Macbook Air M3 (2024) it is.
    delay(2000);
    logit("");  // insert a newline after the random garbage that gets printed on connection/powerup

    logheader("PreferencesTest");
    loglevel++;  // would normally be part of the call to enterfunction for InitializeSerialCommunication()
    pct = "666";
    logit("################# just B4 LS ############################## const char* pct: %s", pct);

    LoadSettings();

    if (darkmode)
    {
        logit("#### darkmode");
    }
    else
    {
        logit("#### lightmode");
    }

    logit("################# just after LS ############################## const char* pct: %s", pct);


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
    logit("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ analogwrite: %d", brightness);

    logit("################# afyter aw ############################ const char* pct: %s", pct);

    analogWrite(TFT_BL, brightness);  // backlight pin is 27, range is 0..255

    // set display rotation for both tft and LVGL to match
    tft.setRotation(0);
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_180);

    InitializeTouch();
    logit("################# just before create gui ############################## const char* pct: %s", pct);

    //CreateContainers();
    CreateMainContainer();
    CreateTitleBar();
    CreateBrightness();
    //CreateZiploc();
    CreateDarkMode();
    //CreateTest();

    ApplyThemeToSettingsScreen(darkmode);
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
