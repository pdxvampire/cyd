#ifndef LAYOUT_H
#define LAYOUT_H

void CreateMainContainer();
void CreateTitleBar();
void CreateBrightness();
void CreateTest();
void CreateDarkMode();

int percentage;
const char *pct;

lv_style_t popuplabelstyle;
lv_style_t style_pr;

lv_obj_t *popuplabel;
lv_obj_t *screen1;
lv_obj_t *screen2;
lv_obj_t *settingsscreen;
lv_obj_t *btn1;
lv_obj_t *btn2;
lv_obj_t *label1;
lv_obj_t *label2;
lv_obj_t *label3;
lv_obj_t *main_container;
lv_obj_t *brightness_container;
lv_obj_t *brightness_sliderandlabel_container;
lv_obj_t *brightness_slider;
lv_obj_t *brightness_label;
lv_obj_t *brightness_title;
lv_obj_t *darkmode_container;
lv_obj_t *darkmode_switch;
lv_obj_t *darkmode_title;
lv_obj_t *titlebar_container;
lv_obj_t *main_title;
lv_obj_t *close_button;
lv_obj_t *test_container;
lv_obj_t *test_title;
lv_obj_t *test_button;

#endif