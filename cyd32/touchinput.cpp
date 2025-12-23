#include <Arduino.h>  // Automatically included in .ino files
#include <CST820.h>
#include <lvgl.h>
#include "logging.h"
#include "touchinput.h"

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