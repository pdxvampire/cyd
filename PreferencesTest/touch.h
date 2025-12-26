#ifndef TOUCH_H
#define TOUCH_H

#include <lvgl.h>
#include "CST820.h"

void HandleTouch(lv_indev_t *, lv_indev_data_t *);
void InitializeTouch();

extern CST820 touch;

#endif