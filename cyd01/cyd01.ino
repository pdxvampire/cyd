#include "logging.h"
#include "leds.h"
#include "code.h"

void setup()
{
    InitializeSerialCommunication("SKETCH CYD01");
    InitializeOnboardLEDs();
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