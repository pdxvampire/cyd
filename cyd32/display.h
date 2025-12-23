#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>
#include <lvgl.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define LVGL_TICK_PERIOD 2
extern unsigned long lastLvTick;

/* Draw buffer for LVGL */
static uint8_t draw_buf[SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8)];

// main display object for LVGL
extern lv_display_t *disp;

extern lv_style_t *popuplabelstyle;
extern lv_obj_t *popuplabel;
extern lv_obj_t *screen1;
extern lv_obj_t *screen2;
extern lv_obj_t *settingsscreen;
extern lv_obj_t *btn1;
extern lv_obj_t *btn2;
extern lv_obj_t *label1;
extern lv_obj_t *label2;
extern lv_obj_t *label3;
extern lv_obj_t *slider;
extern lv_obj_t *slider_label;

void hide_object_timer_cb(lv_timer_t *timer);
void ShowPopupLabelBriefly(const char *msg);
void ShowSettingsScreen();
void create_image_button_from_sd(int id);
void CreateScreen1();
void CreateScreen2();
void InitializeDisplay();

#endif  // DISPLAY_H