#include <FS.h>
//#ifdef ESP32
//#include "SPIFFS.h"  // ESP32 only
//#endif

#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library
#include <lvgl.h>

// Globals needed by several of the includes below.
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
static lv_style_t popuplabelstyle;
static lv_obj_t* popuplabel;

// Prevent stack overflow reboot loops.
SET_LOOP_TASK_STACK_SIZE(16 * 1024);

#include "logging.h"
#include "sdcard.h"
#include "touchinput.h"
#include "display.h"
#include "code.h"

lv_obj_t * tv;
lv_obj_t * tile1;
lv_obj_t * tile2;
lv_obj_t * label1;
lv_obj_t * label2;
lv_obj_t * btn1;

void HandleGesture(lv_event_t * e)
{
    lv_obj_t * screen = (lv_obj_t*)lv_event_get_current_target(e);
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());
    switch(dir) {
        case LV_DIR_LEFT:
            logit("L");
            break;
        case LV_DIR_RIGHT:
            logit("R");
            break;
        case LV_DIR_TOP:
            logit("T");
            break;
        case LV_DIR_BOTTOM:
            logit("B");
            break;
    }
}
void setup()
{
    InitializeSerialCommunication("SKETCH CYD29");

    sdcard_setup();

    InitializeDisplay();

    InitializeTouch();

    // draw the grid of buttons
    // zero-based so the first time through the loop 'curpage = 0' results in 0-5,
    // second time through the loop 'curpage = 1' results in 6-11
    // SETTING CURPAGE TO 1 CAUSED A REBOOT LOOP SO LOOK AT THIS AGAIN WHEN HAVEN'T BEEN UP 24+ HOURS
   /* for (int x = (NUMPAGEIMGS * curpage); x < (NUMPAGEIMGS * curpage) + NUMPAGEIMGS; x++)
    {
        // we're currently only using 10 images out of the
        // possible 12 based on 2 pages of 6 images
        if (x > NUMIMAGESUSED) return;

        create_image_button_from_sd(x);
    }
    */
    
 // lv_obj_t * tv = lv_tileview_create(lv_screen_active());
//lv_obj_set_scrollbar_mode(tv, LV_SCROLLBAR_MODE_OFF);
//lv_obj_add_flag(tv, LV_OBJ_FLAG_SCROLL_MOMENTUM);
//lv_page_set_anim_time(tv, 10); // Faster animation (10ms)


 /*
    lv_obj_t * tile1 = lv_tileview_add_tile(tv, 0, 0, LV_DIR_LEFT);
    lv_obj_t * label = lv_label_create(tile1);
    lv_label_set_text(label, "Swipe left");
    lv_obj_center(label);

    lv_obj_t * tile2 = lv_tileview_add_tile(tv, 0, 1,LV_DIR_RIGHT);

    lv_obj_t * btn = lv_button_create(tile2);

    label = lv_label_create(btn);
    lv_label_set_text(label, "Swipe right");

    lv_obj_set_size(btn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_center(btn);
*/


lv_obj_add_event_cb(lv_screen_active(), HandleGesture, LV_EVENT_GESTURE, NULL);

tv = lv_tileview_create(lv_screen_active());

    tile1 = lv_tileview_add_tile(tv, 0, 1, LV_DIR_TOP);
    label1 = lv_label_create(tile1);
    lv_label_set_text(label1, "Scroll down");
    lv_obj_center(label1);

    tile2 = lv_tileview_add_tile(tv, 0, 0, (lv_dir_t)(LV_DIR_BOTTOM));
    btn1 = lv_button_create(tile2);
    label2 = lv_label_create(btn1);
    lv_label_set_text(label2, "Swipe right");
 lv_obj_set_size(btn1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_center(btn1);

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
