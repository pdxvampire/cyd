//// https://garrysblog.com/2025/11/13/animating-a-blinking-eye-on-an-arduino-powered-lcd-display/

#include <LovyanGFX.hpp>
#include "lodepng.h"
#include "lgfx.h"
#include <lvgl.h>
#include "eye_open_center.h"
#include "eye_closed_center.h"

#include "logging.h"
#include "sdcard.h"
#include "code.h"

//static lgfx::LGFX_SPI<LGFX_Config> lcd;
//static lgfx::Panel_ST7789 panel;

LGFX_JustDisplay lcd;
const int IMAGE_WIDTH = 240;
const int IMAGE_HEIGHT = 240;
uint32_t error;                 /*For the return values of png decoder functions*/

/*Load the PNG file into buffer. It's still compressed (not decoded)*/
unsigned char * png_data;      /*Pointer to the loaded data. Same as the original file just loaded into the RAM*/
size_t png_data_size;          /*Size of `png_data` in bytes*/

void setup()
{
     loglevel++;  // would normally be part of the call to enterfunction for InitializeSerialCommunication()

     InitializeSerialCommunication();

    lcd.init();
    lcd.setRotation(2);  // Use native portrait orientationv
    // Set the color mode as needed. (Initial value is 16)
    // 16 - Faster, but the red and blue tones are 5 bits.
    // 24 - Slower, but the gradation expression is cleaner.
    //lcd.setColorDepth(16);  // Set to 16 bits of RGB565
    //lcd.setColorDepth(16);
    // Enable backlight (GPIO 27 must be HIGH)
    pinMode(27, OUTPUT);
    digitalWrite(27, HIGH);
     // LVGL init
    lv_init();
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


error = lodepng_load_file(&png_data, &png_data_size, "01.png");   /*Load the file*/
if(error) {
    printf("error %u: %s\n", error, lodepng_error_text(error));
    while(1);
}


/*Decode the PNG image*/
unsigned char * png_decoded;    /*Will be pointer to the decoded image*/
uint32_t png_width;             /*Will be the width of the decoded image*/
uint32_t png_height;            /*Will be the width of the decoded image*/

/*Decode the loaded image in ARGB8888 */
error = lodepng_decode32(&png_decoded, &png_width, &png_height, png_data, png_data_size);   

if(error) {
    printf("error %u: %s\n", error, lodepng_error_text(error));
    while(1);
}

/*Initialize an image descriptor for LittlevGL with the decoded image*/
lv_img_dsc_t png_dsc;
png_dsc.header.always_zero = 0;                          /*It must be zero*/
png_dsc.header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;      /*Set the color format*/
png_dsc.header.w = png_width;
png_dsc.header.h = png_height;
png_dsc.data_size = png_width * png_height * 4;
png_dsc.data = png_decoded;

/*Create an image object and set the decoded PNG image as it's source*/
lv_obj_t * img_obj = lv_img_create(lv_scr_act(), NULL);     /*Create the an image object in LittlevGL*/
lv_img_set_src(img_obj, &png_dsc);                          /*Set the image source to the decoded PNG*/
lv_obj_set_drag(img_obj, true);                             /*Make to image dragable*/



}

void loop()
{
    //lcd.pushImage(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, humaneyeopen240x240_data);
    //delay(2000);

    //lcd.pushImage(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, humaneyeclosed240x240_data);
    //delay(1000);
}
