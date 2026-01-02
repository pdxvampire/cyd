#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>
#include <lvgl.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define LVGL_TICK_PERIOD 5
extern unsigned long lastLvTick;

extern TFT_eSPI tft;
extern lv_display_t *disp;

/* Draw buffer for LVGL */
static uint8_t draw_buf[SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8)];

void hide_object_timer_cb(lv_timer_t *timer);
void ShowPopupLabelBriefly(const char *msg);
void CreateSettingsScreen();
void create_image_button_from_sd(int id);
void CreateScreen1();
void CreateScreen2();
void InitializeDisplay();
void generate_mask(lv_draw_buf_t *mask, int32_t w, int32_t h, const char *txt);

#endif  // DISPLAY_H