#include <FS.h>
//#ifdef ESP32
//#include "SPIFFS.h"  // ESP32 only
//#endif

#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library
#include <lvgl.h>


TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

#include "logging.h"
#include "sdcard.h"
#include "touchinput.h"
#include "display.h"
#include "code.h"

// Prevent stack overflow reboot loops.
SET_LOOP_TASK_STACK_SIZE(32 * 1024);



void setup()
{
    InitializeSerialCommunication("SKETCH CYD29");

    sdcard_setup();

    lv_init();
    // Register print function for LVGL debugging
#if LV_USE_LOG != 0
    lv_log_register_print_cb(log_print);
#endif

    // Initialise the TFT
    tft.begin();

    /* 1. Register display using the built-in TFT_eSPI helper */
    disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));

    /* 2. Set display rotation for both tft and LVGL to match */
    tft.setRotation(2);
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_180);

    InitializeTouch();

    create_image_button_from_sd(0);
/*
 for (int x = 0; x < NUMIMGS; x++)
    {
        create_image_button_from_sd(x);
    }

*/


   
}

void loop()
{
    lv_display_flush_ready(disp);
    //lv_timer_handler();
    //lv_tick_inc(5);

    //delay(5);
 if (millis() - lastLvTick > LVGL_TICK_PERIOD)
    {
        lv_tick_inc(LVGL_TICK_PERIOD);  // tell LVGL how much time has passed
        lastLvTick = millis();
    }

    lv_task_handler();        // let the GUI do its work
    delay(LVGL_TICK_PERIOD);  // let this time pass
}
