#ifndef UICALLBACKS_H
#define UICALLBACKS_H

#include <lvgl.h>

void swdarkmode_event_handler(lv_event_t *);
void HandleTouch(lv_indev_t *, lv_indev_data_t *);
void HandleBrightnessSlider(lv_event_t *);
void HandleGesture(lv_event_t *);
void HandleButtonClick(lv_event_t *);
void ExitSettingsScreen();
void close_button_event_cb(lv_event_t *);

#endif  // UICALLBACKS_H