#include <Arduino.h>
#include <lvgl.h>
#include "uicallbacks.h"
#include "logging.h"
#include "theme.h"

extern lv_obj_t *brightness_container;
extern lv_obj_t *brightness_sliderandlabel_container;
extern lv_obj_t *brightness_slider;
extern lv_obj_t *brightness_label;
extern lv_obj_t *brightness_title;
extern lv_obj_t *brightness_container;
extern lv_obj_t *brightness_sliderandlabel_container;
extern lv_obj_t *brightness_slider;
extern lv_obj_t *brightness_label;
extern lv_obj_t *brightness_title;
extern lv_obj_t *darkmode_container;
extern lv_obj_t *darkmode_switch;
extern lv_obj_t *darkmode_title;
extern lv_obj_t *titlebar_container;
extern lv_obj_t *main_title;
extern lv_obj_t *close_button;

extern CST820 touch;

void swdarkmode_event_handler(lv_event_t *e)
{
    enterfunction("swdarkmode_event_handler");

    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        if (lv_obj_has_state(darkmode_switch, LV_STATE_CHECKED))
        {
            logit("switch is checked, set dark mode");
            ApplyDarkModeToSettingsScreen();
        }
        else
        {
            logit("switch is not checked, set light mode");
            ApplyLightModeToSettingsScreen();
        }

        // force refresh since we toggled the mode
        // lv_refr_now(disp);

        lv_indev_wait_release(lv_indev_get_act());  // avoid repeated events if long press
    }

    exitfunction("swdarkmode_event_handler");
}

void HandleTouch(lv_indev_t *indev, lv_indev_data_t *data)
{
    if (touch.getTouch(&rawX, &rawY))
    {
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

void HandleBrightnessSlider(lv_event_t *e)
{
    int percentage = lv_slider_get_value(brightness_slider);
    int val = (int)map(percentage, 0, 100, 0, 255);  // brightness is 0..255, show user-friendly percentage 0..100

    switch (lv_event_get_code(e))
    {
        case LV_EVENT_VALUE_CHANGED:
            static char buf[4]; /* max 3 bytes for number plus 1 null terminating byte */
            snprintf(buf, 4, "%u", percentage);
            lv_label_set_text(brightness_label, buf);
            logit("🎚 Slider changed, value: %d, pct: %d", val, percentage);
            break;

        case LV_EVENT_RELEASED:
            logit("🎚 Slider released, value: %d, pct: %d", val, percentage);
            analogWrite(TFT_BL, val);  // backlight pin is 27
            SetBrightness(val);
            break;
    }
}
