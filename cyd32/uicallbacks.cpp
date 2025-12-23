#include <Arduino.h>  // Automatically included in .ino files
#include <lvgl.h>
#include "logging.h"
#include "layout.h"
#include "display.h"
#include "uicallbacks.h"
#include "physical.h"

extern lv_obj_t* screen1;
extern lv_obj_t* screen2;
extern lv_obj_t* slider;
extern lv_obj_t* slider_label;
extern lv_display_t* disp;

void HandleBrightnessSlider(lv_event_t * e)
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
            analogWrite(27, val);  // backlight pin is 27
            break;
    }
}

void HandleGesture(lv_event_t* e)
{
    enterfunction("HandleGesture");

    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());

    switch (dir)
    {
        case LV_DIR_LEFT:
            logit("L");
            lv_screen_load_anim(screen2, LV_SCREEN_LOAD_ANIM_MOVE_LEFT, 200, 0, false);
            //lv_obj_del_async(screen1);
            lv_obj_del(screen1);
            CreateScreen2();
            lv_display_flush_ready(disp);
            break;
        case LV_DIR_RIGHT:
            logit("R");
            lv_obj_del(screen2);
            CreateScreen1();
            lv_screen_load_anim(screen1, LV_SCREEN_LOAD_ANIM_MOVE_RIGHT, 200, 0, false);
            lv_display_flush_ready(disp);
            break;
        case LV_DIR_TOP:
            logit("T");
            break;
        case LV_DIR_BOTTOM:
            logit("B");
            break;
    }

    exitfunction("HandleGesture");
}

// Button event callback
void HandleButtonClick(lv_event_t* e)
{
    enterfunction("HandleButtonClick");

    if (lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        logit("✅ Button Clicked!");

        //lv_obj_t* btn = (lv_obj_t*)lv_event_get_target(e);  // Get the object that triggered the event
                                                            // Now 'btn' points to the specific button that was clicked
        // You can use 'btn' to identify the button
        lv_obj_t* user_obj = (lv_obj_t*)lv_event_get_user_data(e);
        int button_id = (int)user_obj;

        logit("button id:  %s", horns[button_id].name);

        // These are defined in physical.cpp
        switch (button_id)
        {
            case 0:
                DoSomethingButton01();
                break;
            case 1:
                DoSomethingButton02();
                break;
            case 2:
                DoSomethingButton03();
                break;
            case 3:
                DoSomethingButton04();
                break;
            case 4:
                DoSomethingButton05();
                break;
            case 5:
                DoSomethingButton06();
                break;
            case 6:
                DoSomethingButton07();
                break;
            case 7:
                DoSomethingButton08();
                break;
            case 8:
                DoSomethingButton09();
                break;
            case 9:
                DoSomethingButton10();
                break;
            case 10:
                DoSomethingButton11();
                break;
            case 11:
                DoSomethingButton12();
                break;
        }
    }

    exitfunction("HandleButtonClick");
}