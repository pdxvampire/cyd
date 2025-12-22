#ifndef DISPLAY_H
#define DISPLAY_H

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define LVGL_TICK_PERIOD 2
unsigned long lastLvTick = 0;

/* Draw buffer for LVGL */
static <uint8_t draw_buf[SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8)];

// main display object for LVGL
static lv_display_t *disp;

int curpage = 0;

void ShowPopupLabelBriefly(const char* msg);
void ShowSettingsScreen();

#endif // DISPLAY_H