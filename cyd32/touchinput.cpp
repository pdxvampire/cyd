#include <Arduino.h>  // Automatically included in .ino files
#include <CST820.h>
#include <lvgl.h>
#include "logging.h"
#include "touchinput.h"

// Touch input for LVGL
void HandleTouch(lv_indev_t* indev, lv_indev_data_t* data)
{
    uint16_t rawX, rawY;
    if (touch.getTouch(&rawX, &rawY))
    {
        data->state = LV_INDEV_STATE_PRESSED;
        //data->point.x = rawY;
        //data->point.y = 240 - rawX;
        //data->point.x = rawY;
        data->point.x = 240 - rawX - 1;
        //data->point.y = 240 - tmp - 1;
        data->point.y = 320 - rawY - 1;

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