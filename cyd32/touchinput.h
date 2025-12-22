#ifndef TOUCHINPUT_H
#define TOUCHINPUT_H

//#include "display/lv_display.h"
//#include "core/lv_obj_pos.h"
#include <lvgl.h>
#include "CST820.h"
#include "display.h"
#include "layout.h"

CST820 touch(33, 32, 25, 21);  // Touch: SDA, SCL, RST, INT
uint16_t rawX;
uint16_t rawY;

void HandleGesture(lv_event_t* e);
void hide_object_timer_cb(lv_timer_t* timer);
void HandleButtonClick(lv_event_t* e);
void HandleTouch(lv_indev_t* indev, lv_indev_data_t* data);
void InitializeTouch();

#endif  // TOUCHINPUT_H