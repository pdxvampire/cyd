#include "logging.h"
#include "sdcard.h"
#include "leds.h"
#include "code.h"

void setup()
{
    loglevel++;  // would normally be part of the call to enterfunction for Setup()

    InitializeSerialCommunication();
    InitializeOnboardLEDs();

    // Initialise SD before TFT
    InitializeSDCard();

    logit("####### CALL LISTDIR (1 level deep) ########");
    listDir(SD, "/", 0);
    logit("####### BACK FROM CALL LISTDIR ########");

    // I know the board is working right now,
    // no need to blink the lights
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