// Including this library will also include lvgl.h and TFT_eSPI.h 
#include <LVGL_CYD.h>

// Include the jpeg decoder library
#include <TJpg_Decoder.h>  // https://github.com/Bodmer/TJpg_Decoder

#include "logging.h"/Users/jordysimpson/Documents/Arduino/libraries/LVGL_CYD/src/LVGL_CYD.h
// Include SD/Users/jordysimpson/Documents/Arduino/libraries/LVGL_CYD/src/LVGL_CYD.cpp
#include "sdcard.h"

// This next function will be called during decoding of the jpeg file to
// render each block to the TFT.  If you use a different TFT library
// you will need to adapt this function to suit.
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
  // Stop further decoding as image is running off bottom of screen
  if (y >= LVGL_CYD::tft->height()) return 0;
/*
TFT_eSprite spr = TFT_eSprite(&lcd); // Create a sprite object
int crop_width = 50;
int crop_height = 50;
spr.createSprite(crop_width, crop_height);
// Assuming 'master_image_data' is a C array of a 100x100 image
// To crop the area starting at (20, 30) with size 50x50:
int src_x = 20;
int src_y = 30;
int master_image_width = 240;
int master_image_height = 320;

// Push to the sprite with negative offset relative to the sprite's top-left corner
spr.pushImage(-src_x, -src_y, master_image_width, master_image_height, (uint16_t *)bitmap);

int dest_x = 10;
int dest_y = 10;
spr.pushSprite(dest_x, dest_y);
spr.deleteSprite(); // Free memory
*/
  // This function will clip the image block rendering automatically at the TFT boundaries
  LVGL_CYD::tft->pushImage(x, y, w, h, bitmap);

  // This might work instead if you adapt the sketch to use the Adafruit_GFX library
  // tft.drawRGBBitmap(x, y, bitmap, w, h);

  // Return 1 to decode next block
  return 1;
}


// Callback function definition
void button_event_callback(lv_event_t *e) {
  // Handle button click here
  Serial.println("Image button clicked!");
}

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

void setup() {
  
  // Start Serial and lvgl, set everything up for this device
  // Will also do Serial.begin(115200), lvgl.init(), set up the touch driver
  // and the lvgl timer.

  LVGL_CYD::begin(USB_UP);

  // Create single button in center of active screen
  lv_obj_t * button = lv_button_create(lv_scr_act());
  lv_obj_set_size(button, 100, 100); // Set size if using all three src parts

  lv_obj_align(button, LV_ALIGN_CENTER, 0, 0);

  // Put text in button
  lv_obj_t * button_label = lv_label_create(button);
  lv_label_set_text(button_label, "Oh yeah?");

  // Set a callback to print to serial port when button is clicked.
  //   For those unfamiliar: The "[]() ->" thing is an "anonymous function". It lets
  //   you define a function in place instead pointing to one named elsewhere.
  lv_obj_add_event_cb(button, [](lv_event_t * e) -> void {
    Serial.println("Hell yeah!");
  }, LV_EVENT_CLICKED, NULL);


    sdcard_setup();

    // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
    TJpgDec.setJpgScale(1);

    // The decoder must be given the exact name of the rendering function above
    TJpgDec.setCallback(tft_output);
create_image_button_from_sd();
}

void loop() {

  // lvgl needs this to be called in a loop to run the interface
  lv_task_handler();

}