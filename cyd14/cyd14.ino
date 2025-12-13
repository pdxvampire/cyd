#include "LGFX_JustDisplay.h"
#include <lvgl.h>
#include "logging.h"
#include "leds.h"
#include "sdcard.h"
#include "display.h"
#include "touchinput.h"
#include "code.h"
#include <PNGdec.h>

// JPEG decoder library
#include "jpeg.h"
 int rc=0;
    PNG png;
void setup()
{
    loglevel++;  // would normally be part of the call to enterfunction for Setup()

    InitializeSerialCommunication();
    logit("init leds");
    InitializeOnboardLEDs();

    logit("pins high");
    // Set all chip selects high to avoid bus contention during initialisation of each peripheral
    digitalWrite(22, HIGH);  // Touch controller chip select (if used)
    digitalWrite(15, HIGH);  // TFT screen chip select
    digitalWrite(5, HIGH);   // SD card chips select, must use GPIO 5 (ESP32 SS)

    logit("init sdcard");
    bool cardloaded = InitializeSDCard();

    if (!cardloaded)
    {
        logit("**** SD card failed to load, skipping file operations.");
    }
    else
    {
        logit("test file access 1");
        TestFileAccess();
    }

    logit("init display");
    InitializeDisplay();
    logit("test file access 2");
    TestFileAccess();

    logit("test png");
   
/*
    rc = png.open((const char *)"01.png", myOpen, myClose, myRead, mySeek, PNGDraw);
    if (rc == PNG_SUCCESS)
    {
        Serial.printf("image specs: (%d x %d), %d bpp, pixel type: %d\n", png.getWidth(), png.getHeight(), png.getBpp(), png.getPixelType());
        rc = png.decode(NULL, 0);
        png.close();
    }
    logit("the rest");
*/
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);

    /*Create a white label, set its text and align it to the center*/
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "LOADING SD CARD...");
    lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    //SPI.beginTransaction();

    if (!cardloaded)
    {
        logit("SD card failed to load, skipping file operations.");
        lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0xFF0000), LV_PART_MAIN);
        lv_label_set_text(label, "SD CARD LOAD FAILED");
        lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    }
    else
    {
        logit("####### CALL LISTDIR (1 level deep) ########");
        listDir(SD, "/", 0);
        logit("####### BACK FROM CALL LISTDIR ########");

        TestFileAccess();









        //SPI.endTransaction();

        //SPI.beginTransaction();

        drawSdJpeg("/btn1.jpg", 12, 0);  //x = right      y = down pixel location
        drawSdJpeg("/btn1.jpg", 12, 108);
        drawSdJpeg("/btn1.jpg", 12, 216);
        drawSdJpeg("/btn1.jpg", 128, 0);
        drawSdJpeg("/btn1.jpg", 128, 108);
        drawSdJpeg("/btn1.jpg", 128, 215);
SD.end();
        //SPI.endTransaction();

        //SD.end();


        /*
logit("####1");
lv_obj_t* img;
logit("####2");
lv_img_set_src(img, "/btn1.jpg");
logit("####3");
//lv_obj_align(img, LV_ALIGN_RIGHT_MID, 0, 0);
//lv_obj_set_pos(img, 10, 10);
lv_obj_center(img);

logit("####4");
listDir(SD, "/", 0);
logit("####5");
    SD.end();
    logit("####6");
*/
    }
    //    InitializeTouch();
    //    SetupTestTouch();

    // No need to blink the lights at this point
    // unless nothing is displaying.
    blinkflag = false;

    exitfunction("setup");
}

void loop()
{
    if (millis() - lastLvTick > LVGL_TICK_PERIOD)
    {
        lv_tick_inc(LVGL_TICK_PERIOD);
        lastLvTick = millis();
    }

    lv_timer_handler();
    delay(5);
}

// Functions to access a file on the SD card
File myfile;

void *myOpen(const char *filename, int32_t *size)
{
    Serial.printf("Attempting to open %s\n", filename);
    myfile = SD.open(filename);
    *size = myfile.size();
    return &myfile;
}
void myClose(void *handle)
{
    if (myfile) myfile.close();
}
int32_t myRead(PNGFILE *handle, uint8_t *buffer, int32_t length)
{
    if (!myfile) return 0;
    return myfile.read(buffer, length);
}
int32_t mySeek(PNGFILE *handle, int32_t position)
{
    if (!myfile) return 0;
    return myfile.seek(position);
}

// Function to draw pixels to the display
void PNGDraw(PNGDRAW *pDraw)
{
    uint16_t usPixels[320];

    png.getLineAsRGB565(pDraw, usPixels, PNG_RGB565_LITTLE_ENDIAN, 0xffffffff);
    lcd.writeData(0, pDraw->y + 24, pDraw->iWidth, 1, usPixels);
    //lcd.pushImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer);
}
