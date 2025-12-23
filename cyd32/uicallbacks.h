#ifndef UICALLBACKS_H
#define UICALLBACKS_H

#include "Arduino.h"

void HandleBrightnessSlider(lv_event_t* e);
void HandleGesture(lv_event_t* e);
void HandleButtonClick(lv_event_t* e);

#endif // UICALLBACKS_H