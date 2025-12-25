#include <Arduino.h>
#include "theme.h"
#include "logging.h"

extern...

void ApplyDarkModeToSettingsScreen()
{
    lv_obj_set_style_bg_color(main_container, lv_color_black(), LV_PART_MAIN);
    //////////  lv_obj_set_style_bg_color(brightness_container, lv_color_black(), LV_PART_MAIN);
    ////////// lv_obj_set_style_bg_color(brightness_sliderandlabel_container, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_color(darkmode_container, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_color(titlebar_container, lv_color_black(), LV_PART_MAIN);

    lv_obj_add_state(darkmode_switch, LV_STATE_CHECKED);

    lv_obj_set_style_text_color(main_title, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_color(close_button, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_color(darkmode_title, lv_color_white(), LV_PART_MAIN);
    ////////// lv_obj_set_style_text_color(brightness_title, lv_color_white(), LV_PART_MAIN);
    ////////// lv_obj_set_style_text_color(brightness_label, lv_color_white(), LV_PART_MAIN);

    lv_obj_set_style_bg_color(test_container, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_text_color(test_title, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_color(test_button, lv_color_white(), LV_PART_MAIN);
}

void ApplyLightModeToSettingsScreen()
{
    lv_obj_set_style_bg_color(main_container, lv_color_white(), LV_PART_MAIN);
    //////////lv_obj_set_style_bg_color(brightness_container, lv_color_white(), LV_PART_MAIN);
    //////////lv_obj_set_style_bg_color(brightness_sliderandlabel_container, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_color(darkmode_container, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_color(titlebar_container, lv_color_white(), LV_PART_MAIN);

    lv_obj_clear_state(darkmode_switch, LV_STATE_CHECKED);

    lv_obj_set_style_text_color(main_title, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_text_color(close_button, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_text_color(darkmode_title, lv_color_black(), LV_PART_MAIN);
    //////////lv_obj_set_style_text_color(brightness_title, lv_color_black(), LV_PART_MAIN);
    //////////lv_obj_set_style_text_color(brightness_label, lv_color_black(), LV_PART_MAIN);

    lv_obj_set_style_bg_color(test_container, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_color(test_title, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_text_color(test_button, lv_color_black(), LV_PART_MAIN);
}