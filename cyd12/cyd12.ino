#include "LGFX_JustDisplay.h"
#include <lvgl.h>
#include "logging.h"
#include "leds.h"
#include "display.h"
#include "touchinput.h"
#include "code.h"

void setup()
{
    loglevel++;  // would normally be part of the call to enterfunction for Setup()

    InitializeSerialCommunication();
    InitializeOnboardLEDs();
    InitializeDisplay();

    InitializeTouch();
    SetupTestTouch();

    // No need to blink the lights at this point
    // unless nothing is displaying.
    blinkflag = false;

    exitfunction("setup");
}

void loop()
{
    HandleTouchBasic();
    delay(10);  // Small delay to prevent I2C flooding
}