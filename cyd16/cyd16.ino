// JPEG decoder library
//#include <JPEGDecoder.h>
#include "LGFX_JustDisplay.h"
#include <lvgl.h>
#include "logging.h"
#include "leds.h"
#include "sdcard.h"
#include "display.h"
#include "touchinput.h"
#include "code.h"


void setup()
{
    loglevel++;  // would normally be part of the call to enterfunction for Setup()

    InitializeSerialCommunication();

    InitializeSDCard();
    const char *infilename = "/btn1.jpg";
    if (!readbinarydata(infilename, infile, arrImages[0], filesize))
    {
        // error handling is done in readbinarydata(), just exit
        return;
    }

// this shows the actual size of the image, 17278 (or whatever)
//    logit("filesize: %d", filesize);

//    const size_t jpeg_data_len = sizeof(arrImages[0]);
// this shows 51200, the preallocated size of the byte array
//    logit("sizeof: %d", jpeg_data_len);

    InitializeOnboardLEDs();
    logit("lcd init");
   //lcd.init();
   lv_init();
InitializeDisplay();
//lcd.setColorDepth(16);
// Enable backlight (GPIO 27 must be HIGH)
//    pinMode(27, OUTPUT);
//    digitalWrite(27, HIGH);

 //   lcd.setBrightness(128);
 //   lcd.setRotation(2);  // portrait
    //lcd.fillScreen(random(0xFFFF));
 //   logit("fill black");
 //   lcd.fillScreen(0xfff);  //backfill white

    logit("fill color yellow");
    lcd.fillScreen(lcd.color888(255, 255, 0));

    
    //


    logit("attempting draw");


    if (lcd.drawJpg(arrImages[0], filesize, 0, 0))
    {
        Serial.println("JPEG drawn successfully from byte array.");
    }
    else
    {
        Serial.println("Error drawing JPEG. Check memory or image format.");
        // Error codes can be retrieved if you use the underlying utility functions.
    }

    logit("back");

    //   InitializeTouch();
    //   SetupTestTouch();


   TurnOffOnboardLEDs();

    // No need to blink the lights at this point
    // unless nothing is displaying.
    blinkflag = false;
    Serial.println("####### DONE SETUP #################################");
}

//####################################################################################################
// Main loop
//####################################################################################################
void loop()
{
    //HandleTouch();
    delay(500);  // Wait for 500 milliseconds (adjust for desired speed)
}

