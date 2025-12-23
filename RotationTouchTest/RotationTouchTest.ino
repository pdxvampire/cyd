#include <FS.h>
//#ifdef ESP32
//#include "SPIFFS.h"  // ESP32 only
//#endif

#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library
#include <lvgl.h>
#include "touchinput.h"
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define LVGL_TICK_PERIOD 5
unsigned long lastLvTick = 0;

/* Draw buffer for LVGL */
static uint8_t draw_buf[SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8)];

// main display object for LVGL
lv_display_t *disp;

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}

void lv_example_btn_1(void)
{
    lv_obj_t * label;

    lv_obj_t * btn2 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 80);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_height(btn2, LV_SIZE_CONTENT);

    label = lv_label_create(btn2);
    lv_label_set_text(label, "Toggle");
    lv_obj_center(label);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

    // Wait for the serial port to connect so the Serial Monitor printouts work consistently
    // This may not be necessary on Windows or Linux but with my Macbook Air M3 (2024) it is.
    delay(2000);

    tft.begin();
 // Initialize LVGL
    lv_init();
     // register LVGL display using the built-in TFT_eSPI helper
    disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  tft.setRotation(2);
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_180);


    InitializeTouch();


lv_example_btn_1();
}

void loop() {
  // put your main code here, to run repeatedly:
lv_display_flush_ready(disp);
    //lv_timer_handler();
    //lv_tick_inc(5);

    //delay(5);
    if (millis() - lastLvTick > LVGL_TICK_PERIOD)
    {
        lv_tick_inc(LVGL_TICK_PERIOD);  // tell LVGL how much time has passed
        lastLvTick = millis();
    }

    lv_task_handler();        // let the GUI do its work
    delay(LVGL_TICK_PERIOD);  // let this time pass
}
