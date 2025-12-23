#include <Arduino.h>  // Automatically included in .ino files
#include <CST820.h>
#include <lvgl.h>
#include "logging.h"
#include "touchinput.h"

uint16_t rawX, rawY;

// Touch input for LVGL
void HandleTouch(lv_indev_t* indev, lv_indev_data_t* data)
{
    //uint16_t rawX, rawY;
    if (touch.getTouch(&rawX, &rawY))
    {
        data->state = LV_INDEV_STATE_PRESSED;

        ///// without LVGL use this for portrait with USB at top
        /////        data->point.x = 240 - rawX - 1;
        /////        data->point.y = 320 - rawY - 1;

        ///// with LVGL the raw coords are correct
        data->point.x = rawX;
        data->point.y = rawY;

        Serial.printf("🖐 LVGL Touch at ");
        Serial.printf("%d,", (int)(data->point.x));
        Serial.printf("%d\n", (int)(data->point.y));
        Serial.printf("🖐 RAW ");
        Serial.printf("%d,", rawX);
        Serial.printf("%d\n", rawY);
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

    exitfunction("InitializeTouch");
}