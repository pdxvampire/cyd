#include <FS.h>
#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library
#include <lvgl.h>
#include <array> // for std::array
#include <vector>

// Globals needed by several of the includes below.
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
static lv_style_t popuplabelstyle;
static lv_obj_t *popuplabel;
static lv_obj_t *screen1;
static lv_obj_t *screen2;
static lv_obj_t *settingsscreen;
static uint8_t array_size = 10;
//lv_obj_t *lv_memory_buffer = (lv_obj_t *)heap_caps_malloc(sizeof(lv_obj_t) * array_size, HEAP_CAPS_SPIRAM);

// Prevent stack overflow reboot loops.
SET_LOOP_TASK_STACK_SIZE(16 * 1024);

#include "logging.h"
//#include "prototypes.h"
#include "physical.h"
#include "sdcard.h"
#include "touchinput.h"
#include "display.h"
#include "layout.h"
#include "code.h"



void setup()
{
    InitializeSerialCommunication("SKETCH CYD31");
/*
if (lv_memory_buffer == NULL)
{
    logit("Failed to allocate memory for lv_memory_buffer");
}
*/
    sdcard_setup();

    InitializeDisplay();

    InitializeTouch();

    // draw the grid of buttons
    // zero-based so the first time through the loop 'curpage = 0' results in 0-5,
    // second time through the loop 'curpage = 1' results in 6-11
    // SETTING CURPAGE TO 1 CAUSED A REBOOT LOOP SO LOOK AT THIS AGAIN WHEN HAVEN'T BEEN UP 24+ HOURS
    /* for (int x = (NUMPAGEIMGS * curpage); x < (NUMPAGEIMGS * curpage) + NUMPAGEIMGS; x++)
    {
        // we're currently only using 10 images out of the
        // possible 12 based on 2 pages of 6 images
        if (x > NUMIMAGESUSED) return;

        create_image_button_from_sd(x);
    }
    */

    exitfunction("setup");
}

void loop()
{
    //lv_display_flush_ready(disp);
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
