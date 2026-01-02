#include <FS.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <CST820.h>
#include <lvgl.h>
#include <Preferences.h>

// Prevent stack overflow reboot loops.
SET_LOOP_TASK_STACK_SIZE(16 * 1024);

TFT_eSPI tft = TFT_eSPI();

#include "logging.h"
#include "sdcard.h"
#include "layout.h"
#include "display.h"
#include "touchinput.h"
#include "physical.h"
#include "settings.h"
#include "uicallbacks.h"
#include "theme.h"

void setup()
{
    InitializeSerialCommunication("SKETCH CYD32");

    LoadSettings();

    sdcard_setup();

    InitializeDisplay();

    InitializeTouch();

    exitfunction("setup");
}

void loop()
{
    lv_display_flush_ready(disp);

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
    loglevel += 2;  // would normally be part of the call to enterfunction for InitializeSerialCommunication()

    logit("####### Done initializing serial communication. ################################");
    exitfunction("InitializeSerialCommunication");
}