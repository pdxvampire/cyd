#include <lvgl.h>
#include <SPI.h>

#include <FS.h>
#include <SD.h>

// JPEG decoder library
//#include <JPEGDecoder.h>
#include <TJpg_Decoder.h>

#include "logging.h"
#include "LGFX_JustDisplay.h"
#include "leds.h"
#include "sdcard.h"
#include "display.h"
#include "touchinput.h"
#include "code.h"
//#include "image.h"

// If LVGL logging is enabled, it will inform the user about what is happening in the library
void log_print(lv_log_level_t level, const char* buf)
{
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
}

void setup()
{
    InitializeSerialCommunication("SKETCH CYD26");
    InitializeOnboardLEDs();
    // Register print function for LVGL debugging
    lv_log_register_print_cb(log_print);

    InitializeDisplay();

    //InitializeSDCard();
    sdcard_setup();
        logit("####### CALL LISTDIR (1 level deep) ########");
    listDir(SD, "/", 0);
    logit("####### BACK FROM CALL LISTDIR ########");

    InitializeTouch();
    SetupTestTouch();

    //TJpgDec.setJpgScale(1);
    //displayImage(fileNames[imageIndex]);

    // No need to blink the lights at this point
    // unless nothing is displaying.
    blinkflag = false;

    //    LV_IMAGE_DECLARE(my_image);
    //  lv_obj_t * img1 = lv_image_create(lv_screen_active());
    //  lv_image_set_src(img1, &my_image);
    //  lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
//sdcard_test();
logit("######################################################");
//testFileIO(SD, "/test.txt");
File file = SD.open("/btn1.jpg");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }
  file.close();
//testFileIO(SD, "/pic01-1.jpg");
//testFileIO(SD, "A:pic01-1.jpg");
//testFileIO(SD, "A:/pic01-1.jpg");
    lv_obj_t* wp;

    wp = lv_image_create(lv_screen_active());
    /* Assuming a File system is attached to letter 'A'
     * E.g. set LV_USE_FS_STDIO 'A' in lv_conf.h */
    //const void* void_ptr = imagename.c_str();
    lv_image_set_src(wp, "/horn02.jpg");
    //lv_obj_center(wp);
    lv_obj_align(wp, LV_ALIGN_CENTER, 0, 0);

    //lv_imagebutton_set_src(imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, "A:/pic01-1.jpg", NULL);
    // Set size automatically based on content
    //lv_obj_set_size(imgbtn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

    exitfunction("setup");
}

void loop()
{
    if (millis() - lastLvTick > LVGL_TICK_PERIOD)
    {
        lv_tick_inc(LVGL_TICK_PERIOD);  // tell LVGL how much time has passed
        lastLvTick = millis();
    }

    lv_task_handler();        // let the GUI do its work
    delay(LVGL_TICK_PERIOD);  // let this time pass
}