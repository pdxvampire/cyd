#ifndef TOUCHINPUT_H
#define TOUCHINPUT_H

#include <lvgl.h>
#include "CST820.h"

static CST820 touch(33, 32, 25, 21);  // Touch: SDA, SCL, RST, INT
extern uint16_t rawX;
extern uint16_t rawY;

void HandleTouch(lv_indev_t* indev, lv_indev_data_t* data);
void InitializeTouch();

#endif  // TOUCHINPUT_H