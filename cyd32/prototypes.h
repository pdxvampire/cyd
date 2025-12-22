#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

#include <FS.h>
#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library
#include <lvgl.h>
#include <vector>  // for std::vector
#include "CST820.h"

void InitializeSerialCommunication(const char* title);
void ShowPopupLabelBriefly(const char* msg);
void HandleTouch(lv_indev_t* indev, lv_indev_data_t* data);
void HandleButtonClick(lv_event_t* e);
void hide_object_timer_cb(lv_timer_t* timer);
void HandleGesture(lv_event_t* e);
void create_image_button_from_sd(int id);
void CreateScreen1();
void CreateScreen2();
void ShowSettingsScreen();
void InitializeDisplay();
void InitializeTouch();
void DoSomethingButton01();
void DoSomethingButton02();
void DoSomethingButton03();
void DoSomethingButton04();
void DoSomethingButton05();
void DoSomethingButton06();
void DoSomethingButton07();
void DoSomethingButton08();
void DoSomethingButton09();
void DoSomethingButton10();
void DoSomethingButton11();
void DoSomethingButton12();

#endif /* PROTOTYPES_H_ */