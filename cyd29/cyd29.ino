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

    /* 2. Optional: Set display rotation */
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_0);

    InitializeTouch();

    create_image_button_from_sd();
/*
 for (int x = 0; x < NUMIMGS; x++)
    {
        create_image_button_from_sd(x);
    }

*/


    /*
    

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_text_letter_space(&style, 5);

    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "Hello LVGL with\nimages and styles!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 100);
    lv_obj_align_to(label, imgarr, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);
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
