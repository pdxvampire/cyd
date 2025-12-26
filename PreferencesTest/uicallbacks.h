#ifndef UI_H
#define UI_H

#include <lvgl.h>

void swdarkmode_event_handler(lv_event_t *);
void HandleTouch(lv_indev_t *, lv_indev_data_t *);
void HandleBrightnessSlider(lv_event_t *);

#endif