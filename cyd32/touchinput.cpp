#include <Arduino.h>  // Automatically included in .ino files
#include <CST820.h>
#include <lvgl.h>
#include "touchinput.h"
//#include "display/lv_display.h"
//#include "core/lv_obj_pos.h"
#include "display.h"
#include "layout.h"

void HandleGesture(lv_event_t* e)
{
    enterfunction("HandleGesture");

    lv_obj_t* screen = (lv_obj_t*)lv_event_get_current_target(e);
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());
    switch (dir)
    {
        case LV_DIR_LEFT:
            logit("L");
            lv_screen_load_anim(screen2, LV_SCREEN_LOAD_ANIM_MOVE_LEFT, 200, 0, false);
            //   lv_obj_del_async(screen1);
            lv_display_flush_ready(disp);
            break;
        case LV_DIR_RIGHT:
            logit("R");
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

        lv_obj_t* btn = (lv_obj_t*)lv_event_get_target(e);  // Get the object that triggered the event
                                                            // Now 'btn' points to the specific button that was clicked
        // You can use 'btn' to identify the button
        lv_obj_t* user_obj = (lv_obj_t*)lv_event_get_user_data(e);
        int button_id = (int)user_obj;

        logit("button id:  %s", horns[button_id].name);

        // These are defined in code.h
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

// Touch input for LVGL
void HandleTouch(lv_indev_t* indev, lv_indev_data_t* data)
{
    uint16_t rawX, rawY;
    if (touch.getTouch(&rawX, &rawY))
    {
        //lv_obj_add_flag(popuplabel, LV_OBJ_FLAG_HIDDEN);

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
    lv_indev_t* indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, HandleTouch);

    // Gestures
    /* Set the minimum gesture velocity to 10 pixels/second */
    indev->gesture_min_velocity = 5;
    indev->gesture_limit = 10;  // Make it more sensitive (trigger after 10px)

    exitfunction("InitializeTouch");
}