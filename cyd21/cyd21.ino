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

//SPIClass touchscreenSPI = SPIClass(VSPI);
#include "touchinput.h"

const uint8_t DISPLAY_ORIENTATION_PORTRAIT = 0;

const uint8_t MAX_IMAGES = 2;
//String fileNames[MAX_IMAGES] = { "/panda.jpg", "/GrandPrismaticSpring_240_320_ys08_0398_P1020005.jpg" };
String fileNames[MAX_IMAGES] = { "/btn1.jpg", "/btn2.jpg" };
uint8_t imageIndex = 0;

// This next function will be called during decoding of the jpeg file to
// render each block to the TFT.  If you use a different TFT library
// you will need to adapt this function to suit.
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
  // Stop further decoding as image is running off bottom of screen
  if (y >= lcd.height()) return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
  lcd.pushImage(x, y, w, h, bitmap);

  // This might work instead if you adapt the sketch to use the Adafruit_GFX library
  // tft.drawRGBBitmap(x, y, bitmap, w, h);

  // Return 1 to decode next block
  return 1;
}

void setup() {
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

  displayImage(fileNames[imageIndex]);

  InitializeTouch();
}

void displayImage(String imagename) {
  Serial.printf("displayImage filename: %s\n", imagename);
  //tft.fillScreen(TFT_WHITE);
  // Get the width and height in pixels of the jpeg if you wish
  uint16_t w = 0, h = 0;
  TJpgDec.getSdJpgSize(&w, &h, imagename);
  Serial.print("Width = ");
  Serial.print(w);
  Serial.print(", height = ");
  Serial.println(h);

  // Draw the image, top left at 0,0
  TJpgDec.drawSdJpg(0, 0, imagename);

  //displayImage(fileNames[imageIndex]);
  lcd.drawCentreString("Touch Image -> next", lcd.width() / 2, 20, 2);
  lcd.drawCentreString("Touch Image -> next", lcd.width() / 2, 290, 2);
  //displayImage(fileNames[imageIndex]);
}

void loop() {
  HandleTouch();
  delay(500);
}