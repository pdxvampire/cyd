/*
  Device: ESP32 Cheap Yellow Display (CYD) with 2.8-inches
          TFT display with Resistive Touch Controller.
          As this devices comes in two variants be sure to 
          activate the right one by using the correct
          User Settings file.
          - If it is a device with one USB (Micro) connector
            ILI9341 display use: Setup801_ESP32_CYD_ILI9341_240x320_NoMiso.h
          - If the device has two (Micro- and C) USB connectors
            ST7789 display use:  Setup805_ESP32_CYD_ST7789_240x320_NoMiso.h

  This sketch is loading JPG images from an inserted SD-Card and
  displays them on the display. The next image is loaded after a
  touch on the screen. The (raw) positions of the touch are 
  displayed and the next image is loaded and displayed.

  This is using the TFT_eSPI library for displaying the content and the
  XPT2046 Touchscreen library by Paul Stoffregen to run the Touch
  Controller.

  This is using the AUTODETECT feature of LovyanGFX.
  As this sketch is for an ESP32 Cheap Yellow Display please select
  'ESP32-2432S028R CYD' as your board !
  If using another board you probably will receive an error like 
  'Compilation error: 'CYD_TFT_SCK' was not declared in this scope'

  Please insert an SD-Card that has two JPG files in the root folder:
  Wave_240_320.jpg
  GrandPrismaticSpring_240_320.jpg

  The GPIO and SPI Bus connections are done based on the work by
  'embedded-kiddie', see: 
  https://github.com/embedded-kiddie/Arduino-CYD-2432S028R
*/

/*
  Environment and Libraries used for this example:
  Arduino 2.3.6 (Windows)
  TFT_eSPI Mar 6, 2024
  TJpg_Decoder 1.1.0 (https://github.com/Bodmer/TJpg_Decoder)
*/

// Include the jpeg decoder library
#include <TJpg_Decoder.h>  // https://github.com/Bodmer/TJpg_Decoder

// Include SD
#include "sdcard.h"

// Include the TFT library https://github.com/Bodmer/TFT_eSPI
#include "SPI.h"
#include <TFT_eSPI.h>       // Hardware-specific library
TFT_eSPI lcd = TFT_eSPI();  // Invoke custom library

// Important: in User_Settings-file leave out the TFT_MISO pin !!!
// User_Settings file in use is 'Setup801_ESP32_CYD_ILI9341_240x320_NoMiso.h'

#include "display.h"

//SPIClass touchscreenSPI = SPIClass(VSPI);
#include "touchinput.h"

#include <lvgl.h>

void create_image_button_from_sd() {
  // 1. Create the image button object
  lv_obj_t *imgbtn = lv_imagebutton_create(lv_screen_active());
  lv_obj_center(imgbtn);
  lv_obj_set_size(imgbtn, 100, 100); // Set size if using all three src parts

  // 2. Set the image sources for different states
  // We use the same image for simplicity, but you can have different images for pressed/released states
  const char *imagePath = "/horn01.jpg"; 

  lv_imagebutton_set_src(imgbtn, LV_IMAGEBUTTON_STATE_RELEASED, NULL, imagePath, NULL);
  lv_imagebutton_set_src(imgbtn, LV_IMAGEBUTTON_STATE_PRESSED, NULL, imagePath, NULL);
  // ... set for other states like DISABLED, CHECKED, etc.

  // 3. Optional: Add a callback function for button press event
  lv_obj_add_event_cb(imgbtn, button_event_callback, LV_EVENT_CLICKED, NULL);
}

// Callback function definition
void button_event_callback(lv_event_t *e) {
  // Handle button click here
  Serial.println("Image button clicked!");
}

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\n Testing TJpg_Decoder library");

    // Initialise the TFT
    lcd.begin();
    lcd.setRotation(DISPLAY_ORIENTATION_PORTRAIT);
    lcd.setTextColor(0xFFFF, 0x0000);
    lcd.fillScreen(TFT_BLACK);
    lcd.setSwapBytes(true);  // We need to swap the colour bytes (endianess)

    sdcard_setup();

    // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
    TJpgDec.setJpgScale(1);

    // The decoder must be given the exact name of the rendering function above
    TJpgDec.setCallback(tft_output);

    lcd.drawCentreString("Touch Image -> next", lcd.width() / 2, 20, 2);
    lcd.drawCentreString("Touch Image -> next", lcd.width() / 2, 290, 2);

    //displayImage(fileNames[imageIndex]);
    foo();
    InitializeTouch();

    //lv_init();
    //create_image_button_from_sd();
}

void loop()
{
    //HandleTouch();
    delay(100);
}

void foo(void)
{
    lcd.fillScreen(TFT_BLACK);
    // Draw the image, top left at 0,0

    // 0 = green
    TJpgDec.drawSdJpg(10, 0, fileNames[0]);
    
    // 5 = red
    TJpgDec.drawSdJpg(10, 110, fileNames[5]);

// 8 = brown
    TJpgDec.drawSdJpg(10, 220, fileNames[8]);

    // 3 = purple
       TJpgDec.drawSdJpg(120, 0, fileNames[3]);

    // 4 = yellow
        TJpgDec.drawSdJpg(120, 110, fileNames[4]);

    // 6 = light blue
      TJpgDec.drawSdJpg(120, 220, fileNames[6]);

    //page2
    // 1 = dk blue
    // TJpgDec.drawSdJpg(10, 0, fileNames[1]);
    
    // 7 = pink
    //TJpgDec.drawSdJpg(10, 108, fileNames[7]);

    // 2 = orange
    //TJpgDec.drawSdJpg(10, 216, fileNames[2]);

    // 9 = settings
    //TJpgDec.drawSdJpg(120, 0, fileNames[9]);
}