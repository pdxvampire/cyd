#include "logging.h"
#include "code.h"

void setup()
{
    loglevel++; // would normally be part of the call to enterfunction for Setup()
    
    InitializeSerialCommunication();
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