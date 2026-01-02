#include <Arduino.h>
#include "theme.h"
#include "logging.h"
#include "layout.h"

void ApplyThemeToSettingsScreen(bool usedarkmode)
{
    enterfunction("ApplyThemeToSettingsScreen");

    lv_color_t bgcolor;
    lv_color_t txtcolor;

    if (usedarkmode)
    {
        logit("Dark mode is selected.");

        logit(">>>>> set the background color to black");
        bgcolor = lv_color_black();

        logit(">>>>> set the text color to white");
        txtcolor = lv_color_white();
    }
    else
    {
        logit("Light mode is selected.");

        logit(">>>>> set the background color to white");
        bgcolor = lv_color_white();

        logit(">>>>> set the text color to black");
        txtcolor = lv_color_black();
    }

    logit(">>>>> apply to window");
    lv_obj_set_style_bg_color(lv_screen_active(), bgcolor, LV_PART_MAIN);

    logit(">>>>> apply to main_container");
    lv_obj_set_style_bg_color(main_container, bgcolor, LV_PART_MAIN);

    logit(">>>>> apply to brightness_container");
    lv_obj_set_style_bg_color(brightness_container, bgcolor, LV_PART_MAIN);

    logit(">>>>> apply to brightness_sliderandlabel_container");
    lv_obj_set_style_bg_color(brightness_sliderandlabel_container, bgcolor, LV_PART_MAIN);

    logit(">>>>> apply to darkmode_container");
    lv_obj_set_style_bg_color(darkmode_container, bgcolor, LV_PART_MAIN);

    logit(">>>>> apply to titlebar_container");
    lv_obj_set_style_bg_color(titlebar_container, bgcolor, LV_PART_MAIN);
    lv_obj_set_style_bg_color(titlebar_leftside, bgcolor, LV_PART_MAIN);
    lv_obj_set_style_bg_color(titlebar_rightside, bgcolor, LV_PART_MAIN);

    logit(">>>>> apply dark to close_button");
    lv_obj_set_style_text_color(close_button, txtcolor, LV_PART_MAIN);

    logit(">>>>> apply dark to darkmode_title");
    lv_obj_set_style_text_color(darkmode_title, txtcolor, LV_PART_MAIN);
    lv_obj_set_style_text_color(brightness_title, txtcolor, LV_PART_MAIN);
    lv_obj_set_style_text_color(brightness_label, txtcolor, LV_PART_MAIN);

    exitfunction("ApplyThemeToSettingsScreen");
}
