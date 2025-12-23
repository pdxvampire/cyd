#include <FS.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

// Prevent stack overflow reboot loops.
SET_LOOP_TASK_STACK_SIZE(16 * 1024);

TFT_eSPI tft = TFT_eSPI();

//extern unsigned long lastLvTick;

#include "logging.h"
#include "sdcard.h"
#include "layout.h"
#include "display.h"
#include "touchinput.h"
#include "physical.h"

void setup()
{
    InitializeSerialCommunication("SKETCH CYD31");

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

void InitializeSerialCommunication(const char* title)
{
    Serial.begin(115200);

    // Wait for the serial port to connect so the Serial Monitor printouts work consistently
    // This may not be necessary on Windows or Linux but with my Macbook Air M3 (2024) it is.
    delay(2000);

    logit("");  // insert a newline after the random garbage that gets printed on connection/powerup

    logheader(title);
    loglevel++;  // would normally be part of the call to enterfunction for InitializeSerialCommunication()

    logit("####### Done initializing serial communication. ################################");
    exitfunction("InitializeSerialCommunication");
}