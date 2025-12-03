#include "LGFX_JustDisplay.h"
#include "logging.h"
#include "leds.h"
#include "display.h"
#include "code.h"

void setup()
{
    loglevel++;  // would normally be part of the call to enterfunction for Setup()

    InitializeSerialCommunication();
    InitializeOnboardLEDs();
    
    InitializeDisplay();
    TestDisplayJustLGFX();

    // No need to blink the lights at this point
    // unless nothing is displaying.
    blinkflag = false;

    exitfunction("setup");
}

void loop()
{
    // Seriously DO NOT ENABLE THESE or you will just
    // get a constantly scrolling Serial Monitor
    // window printing the entering/exiting
    // statements
    //
    // enterfunction("loop");

    // Blink so we have a visual clue that the
    // sketch ran in case the display isn't
    // used or isn't working.
    if (blinkflag)
    {
        BlinkOnboardLEDs();
        blinkctr++;

        if (blinkctr >= 3)
        {
            blinkflag = false;
        }

        delay(300);
    }

    // See warning above enterfunction()
    // exitfunction("loop");
}