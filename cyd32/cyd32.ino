#include <FS.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

// Prevent stack overflow reboot loops.
SET_LOOP_TASK_STACK_SIZE(16 * 1024);

TFT_eSPI tft = TFT_eSPI();

//extern unsigned long lastLvTick;

#include "logging.h"
#include "sdcard.h"
#include "layout.h"
#include "display.h"
#include "touchinput.h"
#include "physical.h"



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

    lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);

    label = lv_label_create(btn1);
    lv_label_set_text(label, "Button");
    lv_obj_center(label);

    lv_obj_t * btn2 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_height(btn2, LV_SIZE_CONTENT);

    label = lv_label_create(btn2);
    lv_label_set_text(label, "Toggle");
    lv_obj_center(label);
}

void setup()
{
    InitializeSerialCommunication("SKETCH CYD31");

    sdcard_setup();

    InitializeDisplay();

    InitializeTouch();

//lv_example_btn_1();



    exitfunction("setup");
}

void loop()
{
    //lv_display_flush_ready(disp);
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

void InitializeSerialCommunication(const char* title)
{
    Serial.begin(115200);

    // Wait for the serial port to connect so the Serial Monitor printouts work consistently
    // This may not be necessary on Windows or Linux but with my Macbook Air M3 (2024) it is.
    delay(2000);

    logit("");  // insert a newline after the random garbage that gets printed on connection/powerup

    logheader(title);
    loglevel++;  // would normally be part of the call to enterfunction for InitializeSerialCommunication()

    logit("####### Done initializing serial communication. ################################");
    exitfunction("InitializeSerialCommunication");
}