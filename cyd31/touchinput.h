#include "display/lv_display.h"
#include "core/lv_obj_pos.h"
#include "CST820.h"
CST820 touch(33, 32, 25, 21);  // Touch: SDA, SCL, RST, INT
uint16_t rawX, rawY;

void hide_object_timer_cb(lv_timer_t* timer)
{
    enterfunction("hide_object_timer_cb");

    lv_obj_t* obj = (lv_obj_t*)timer->user_data;
    if (obj != NULL)
    {
        logit("hide the object");
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);  // Hide the object

        //lv_obj_set_hidden(slider, true);
        logit("delete the timer");
        lv_timer_del(timer);  // Optional: delete the timer after it runs once
    }
    else
    {
        logit("NOOP, object is NULL");
    }

    exitfunction("hide_object_timer_cb");
}

// Button event callback
void HandleButtonClick(lv_event_t* e)
{
    enterfunction("HandleButtonClick");

    if (lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        logit("✅ Button Clicked!");

        //imageIndex++;
        //       if (imageIndex > (MAX_IMAGES - 1)) imageIndex = 0;
        //       displayImage(fileNames[imageIndex]);

        lv_obj_t* btn = (lv_obj_t*)lv_event_get_target(e);  // Get the object that triggered the event
                                                            // Now 'btn' points to the specific button that was clicked
        // You can use 'btn' to identify the button
        lv_obj_t* user_obj = (lv_obj_t*)lv_event_get_user_data(e);
        const char* button_id = (const char*)user_obj;

        logit("button id:  %s", button_id);


        lv_obj_add_style(popuplabel, &popuplabelstyle, 0);
        lv_label_set_text(popuplabel, button_id);
        lv_obj_align(popuplabel, LV_ALIGN_CENTER, 0, 0);
        //lv_obj_align_to(popuplabel, imgarr, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);
        lv_obj_clear_flag(popuplabel, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_parent(popuplabel, lv_screen_active());  //Re-setting an object's parent (even to its current parent) automatically places it in the foreground of that parent.

        lv_obj_move_foreground(popuplabel);

        lv_timer_create(hide_object_timer_cb, 1050, popuplabel);
        // This creates a timer that runs the callback after 3000 milliseconds (3 seconds).
    }

    exitfunction("HandleButtonClick");
}

// Touch input for LVGL
void HandleTouch(lv_indev_t* indev, lv_indev_data_t* data)
{
    uint16_t rawX, rawY;
    if (touch.getTouch(&rawX, &rawY))
    {
        lv_obj_add_flag(popuplabel, LV_OBJ_FLAG_HIDDEN);

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

void InitializeTouch(void)
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
    indev->gesture_limit = 10; // Make it more sensitive (trigger after 30px)


    exitfunction("InitializeTouch");
}