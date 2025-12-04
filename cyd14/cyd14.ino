#include "LGFX_JustDisplay.h"
#include <lvgl.h>
#include "logging.h"
#include "leds.h"
#include "sdcard.h"
#include "display.h"
#include "touchinput.h"
#include "code.h"

void setup()
{
    loglevel++;  // would normally be part of the call to enterfunction for Setup()

    InitializeSerialCommunication();
    InitializeOnboardLEDs();
InitializeSDCard();


    
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


InitializeDisplay();
logit("####1");
lv_obj_t* img;
logit("####2");
//img = lv_img_create(lv_scr_act());
//lv_img_set_src(img, &img_wink_png);
//lv_obj_align(img, LV_ALIGN_LEFT_MID, 20, 0);


/* Assuming a File system is attached to letter 'A'
     * E.g. set LV_USE_FS_STDIO 'A' in lv_conf.h */
/*Create a new decoder and register functions */

//lv_img_set_src(img, "A:/01.png");
logit("####3");
//lv_obj_align(img, LV_ALIGN_RIGHT_MID, 0, 0);
//lv_obj_set_pos(img, 10, 10);
//String content = readFile(SD, "/test.txt");

//lv_obj_center(img);
logit("####4");
listDir(SD, "/", 0);
logit("####5");
    SD.end();
    logit("####6");

    InitializeTouch();
    SetupTestTouch();

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