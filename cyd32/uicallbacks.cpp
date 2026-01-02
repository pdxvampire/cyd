#include <Arduino.h>   // Automatically included in .ino files
#include <TFT_eSPI.h>  // only needed for TFT_BL
#include <lvgl.h>
#include "CST820.h"
#include "logging.h"
#include "layout.h"
#include "display.h"
#include "uicallbacks.h"
#include "physical.h"
#include "settings.h"
#include "theme.h"
#include "touchinput.h"

void close_button_event_cb(lv_event_t* e)
{
    ExitSettingsScreen();
}

void swdarkmode_event_handler(lv_event_t* e)
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

void HandleBrightnessSlider(lv_event_t* e)
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

void HandleGesture(lv_event_t* e)
{
    enterfunction("HandleGesture");

    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_active());

    switch (dir)
    {
        case LV_DIR_LEFT:
            logit("SWIPE L");
            logit("call load anim for screen 2");
            lv_screen_load_anim(screen2, LV_SCR_LOAD_ANIM_FADE_IN, 15, 0, false);
            logit("flush display");
            lv_display_flush_ready(disp);
            break;
        case LV_DIR_RIGHT:
            logit("SWIPE R");
            logit("call load anim for screen 1");
            lv_screen_load_anim(screen1, LV_SCREEN_LOAD_ANIM_MOVE_RIGHT, 29, 0, false);
            logit("flush display");
            lv_display_flush_ready(disp);
            break;
        case LV_DIR_TOP:
            logit("SWIPE UP");
            break;
        case LV_DIR_BOTTOM:
            logit("SWIPE DOWN");
            break;
    }

    // Tell the input device to wait for release before processing more events
    lv_indev_wait_release(lv_indev_get_act());

    exitfunction("HandleGesture");
}

void ExitSettingsScreen()
{
    logit("call load anim for screen 2");
    lv_screen_load(screen2);
    logit("flush display");
    lv_display_flush_ready(disp);
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

        logit("button id:    %d", button_id);
        if (darkmode)
        {
            logit("button name:  %s", darkhorns[button_id].name);
        }
        else
        {
            logit("button name:  %s", lighthorns[button_id].name);
        }

        // These are defined in physical.cpp
        switch (button_id)
        {
            case 1:
                DoSomethingButton01();
                break;
            case 2:
                DoSomethingButton02();
                break;
            case 3:
                DoSomethingButton03();
                break;
            case 4:
                DoSomethingButton04();
                break;
            case 5:
                DoSomethingButton05();
                break;
            case 6:
                DoSomethingButton06();
                break;
            case 7:
                DoSomethingButton07();
                break;
            case 8:
                DoSomethingButton08();
                break;
            case 9:
                DoSomethingButton09();
                break;
            case 10:
                DoSomethingButton10();
                break;
            case 11:
                DoSomethingButton11();
                break;
            case 12:
                DoSomethingButton12();
                break;
            case 13:
                ExitSettingsScreen();
                break;
        }
    }

    exitfunction("HandleButtonClick");
}