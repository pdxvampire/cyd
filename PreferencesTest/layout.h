#ifndef LAYOUT_H
#define LAYOUT_H

void CreateMainContainer();
void CreateTitleBar();
void CreateBrightness();
void CreateTest();
void CreateDarkMode();
void CreateZiploc();

// Style for horn buttons when pressed
extern lv_style_t style_pr;

// Screens
extern lv_obj_t *screen1;
extern lv_obj_t *screen2;
extern lv_obj_t *settingsscreen;

// These need better names or to be gotten rid of if they aren't needed
extern lv_obj_t *btn1;
extern lv_obj_t *btn2;
extern lv_obj_t *label1;
extern lv_obj_t *label2;
extern lv_obj_t *label3;

// Flex containers
extern lv_obj_t *main_container;
extern lv_obj_t *brightness_container;
extern lv_obj_t *brightness_sliderandlabel_container;
extern lv_obj_t *darkmode_container;
extern lv_obj_t *titlebar_container;
extern lv_obj_t *test_container;

// Brightness slider, printed value, and title
extern lv_obj_t *brightness_slider;
extern lv_obj_t *brightness_label;
extern lv_obj_t *brightness_title;

// Dark mode switch and title
extern lv_obj_t *darkmode_switch;
extern lv_obj_t *darkmode_title;

// Titlebar title and close button
extern lv_obj_t *main_title;
extern lv_obj_t *close_button;
extern lv_obj_t *labelX;

// Test title and close button
extern lv_obj_t *test_title;
extern lv_obj_t *test_button;

// Popup label for button testing
extern lv_obj_t *popuplabel;
extern lv_style_t popuplabelstyle;

#define MASK_WIDTH 150
#define MASK_HEIGHT 30

void generate_mask(lv_draw_buf_t *mask, int32_t w, int32_t h, const char *txt);

#endif