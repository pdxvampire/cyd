#include "logging.h"
#include "code.h"

// Include the jpeg decoder library
#include <TJpg_Decoder.h>  // https://github.com/Bodmer/TJpg_Decoder

// Include SD
#include "sdcard.h"

// Include the TFT library https://github.com/Bodmer/TFT_eSPI
#include "SPI.h"
#include <TFT_eSPI.h>       // Hardware-specific library
TFT_eSPI lcd = TFT_eSPI();  // Invoke custom library

#include "display.h"

//SPIClass touchscreenSPI = SPIClass(VSPI);
#include "touchinput.h"


void setup()
{
    InitializeSerialCommunication("SKETCH CYD25");

    // Initialise the TFT
    lcd.begin();
    lcd.setRotation(DISPLAY_ORIENTATION_PORTRAIT);
    lcd.setTextColor(0xFFFF, 0x0000);
    lcd.fillScreen(TFT_BLACK);
    lcd.setSwapBytes(true);


    sdcard_setup();

    // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
    TJpgDec.setJpgScale(1);

    // The decoder must be given the exact name of the rendering function above
    TJpgDec.setCallback(tft_output);

    lcd.drawCentreString("Touch Image -> next", lcd.width() / 2, 20, 2);
    lcd.drawCentreString("Touch Image -> next", lcd.width() / 2, 290, 2);

    displayImage(fileNames[imageIndex]);

    InitializeTouch();
}

void loop()
{
    // put your main code here, to run repeatedly:
    //lv_task_handler();

    HandleTouch();
    delay(5);
}
