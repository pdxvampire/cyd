#include <Arduino.h>   // Automatically included in .ino files
#include <TFT_eSPI.h>  // only needed for TFT_BL
#include <lvgl.h>
#include "CST820.h"
#include "uicallbacks.h"
#include "logging.h"
#include "theme.h"
#include "settings.h"
#include "layout.h"
#include "touch.h"

void swdarkmode_event_handler(lv_event_t *e)
{
    // enterfunction("swdarkmode_event_handler");

    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        if (lv_obj_has_state(darkmode_switch, LV_STATE_CHECKED))
        {
            logit("switch is checked, set dark mode");
            SetDarkMode(true);
            ApplyThemeToSettingsScreen(true);
        }
        else
        {
            logit("switch is not checked, set light mode");
            SetDarkMode(false);
            ApplyThemeToSettingsScreen(false);
        }

        // avoid repeated events if long press
        lv_indev_wait_release(lv_indev_get_act());
    }

    // exitfunction("swdarkmode_event_handler");
}

void HandleBrightnessSlider(lv_event_t *e)
{
    int slidercurrent = lv_slider_get_value(brightness_slider);

    if (slidercurrent < 10) slidercurrent = 10;

    int val = (int)map(slidercurrent, 0, 100, 0, 255);  // brightness is 0..255, show user-friendly percentage 0..100

    switch (lv_event_get_code(e))
    {
        case LV_EVENT_VALUE_CHANGED:
            static char buf[4]; /* max 3 bytes for number plus 1 null terminating byte */
            snprintf(buf, 4, "%u", slidercurrent);
            lv_label_set_text(brightness_label, buf);
            logit("🎚 Slider changed, value: %d, pct: %d", val, slidercurrent);
            break;

        case LV_EVENT_RELEASED:
            logit("🎚 Slider released, value: %d, pct: %d", val, slidercurrent);
            analogWrite(TFT_BL, val);  // backlight pin is 27
            SetBrightness(val);
            break;
    }
}
