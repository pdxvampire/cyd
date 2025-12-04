#include "LGFX_JustDisplay.h"
#include <lvgl.h>
#include "logging.h"
#include "leds.h"
#include "sdcard.h"
#include "display.h"
#include "touchinput.h"
#include "code.h"


// JPEG decoder library
#include "jpeg.h"

void setup()
{
    loglevel++;  // would normally be part of the call to enterfunction for Setup()

    InitializeSerialCommunication();
    InitializeOnboardLEDs();
InitializeSDCard();

InitializeDisplay();
//SPI.beginTransaction();
    
    logit("####### CALL LISTDIR (1 level deep) ########");
    listDir(SD, "/", 0);
    logit("####### BACK FROM CALL LISTDIR ########");



if (SD.exists("/helloworld.txt"))
{
    Serial.println("helloworld.txt exists.");
}
else
{
    Serial.println("helloworld.txt doesn't exist.");
}

if (SD.exists("/01.png"))
{
    Serial.println("01.png exists.");
}
else
{
    Serial.println("01.png doesn't exist.");
}

/*Change the active screen's background color*/
//  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);

  /*Create a white label, set its text and align it to the center*/
//  lv_obj_t * label = lv_label_create(lv_scr_act());
//  lv_label_set_text(label, "Hello world");
//  lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);
//  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

//SPI.endTransaction();

//SPI.beginTransaction();

 drawSdJpeg("/btn1.jpg", 12, 0);  //x = right      y = down pixel location
        drawSdJpeg("/btn1.jpg", 12, 108);
        drawSdJpeg("/btn1.jpg", 12, 216);
        drawSdJpeg("/btn1.jpg", 128, 0);
        drawSdJpeg("/btn1.jpg", 128, 108);
        drawSdJpeg("/btn1.jpg", 128, 215);

//SPI.endTransaction();

//SD.end();


/*
logit("####1");
lv_obj_t* img;
logit("####2");
lv_img_set_src(img, "/btn1.jpg");
logit("####3");
//lv_obj_align(img, LV_ALIGN_RIGHT_MID, 0, 0);
//lv_obj_set_pos(img, 10, 10);
lv_obj_center(img);

logit("####4");
listDir(SD, "/", 0);
logit("####5");
    SD.end();
    logit("####6");
*/
//    InitializeTouch();
//    SetupTestTouch();

    // No need to blink the lights at this point
    // unless nothing is displaying.
    blinkflag = false;

    exitfunction("setup");
}

void loop()
{
    if (millis() - lastLvTick > LVGL_TICK_PERIOD)
    {
        lv_tick_inc(LVGL_TICK_PERIOD);
        lastLvTick = millis();
    }

    lv_timer_handler();
    delay(5);
}