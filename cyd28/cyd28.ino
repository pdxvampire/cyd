// Example for library:
// https://github.com/Bodmer/TJpg_Decoder

// This example if for an ESP8266 or ESP32, it renders a Jpeg file
// that is stored in a SD card file. The test image is in the sketch
// "data" folder (press Ctrl+K to see it). You must save the image
// to the SD card using you PC.

// Include the jpeg decoder library
#include <TJpg_Decoder.h>
#include "sdcard.h"
// Include SD
#define FS_NO_GLOBALS
#include <FS.h>
#ifdef ESP32
#include "SPIFFS.h"  // ESP32 only
#endif

#define SD_CS 5

// Include the TFT library https://github.com/Bodmer/TFT_eSPI
#include "SPI.h"
#include <TFT_eSPI.h>  // Hardware-specific library
#include <lvgl.h>
#include "image.h"
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

/* Define screen resolution */
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

/* Draw buffer for LVGL */
static uint8_t draw_buf[SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8)];
lv_display_t *disp;

// This next function will be called during decoding of the jpeg file to
// render each block to the TFT.  If you use a different TFT library
// you will need to adapt this function to suit.
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
    // Stop further decoding as image is running off bottom of screen
    if (y >= tft.height()) return 0;

    // This function will clip the image block rendering automatically at the TFT boundaries
    tft.pushImage(x, y, w, h, bitmap);

    // This might work instead if you adapt the sketch to use the Adafruit_GFX library
    // tft.drawRGBBitmap(x, y, bitmap, w, h);

    // Return 1 to decode next block
    return 1;
}

#if LV_USE_LOG != 0
/* Serial debugging */
void log_print(lv_log_level_t level, const char *buf)
{
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
}
#endif


void setup()
{
    Serial.begin(115200);
    delay(2000);
    Serial.println("\n\n Testing TJpg_Decoder library");
    sdcard_setup();
    Serial.println("\r\nInitialisation done.");

Serial.println("xxxxxxxxxxxx");
 if (!SD.begin())
    {
        Serial.println("Card Mount Failed");
        return;
    }

    File jpegFile = SD.open("/horn02.jpg", FILE_READ);  // or, file handle reference for SD library
    if (!jpegFile)
    {
        Serial.print("ERROR: File \"");
        Serial.print("/horn02.jpg");
        Serial.println("\" not found!");
        return;
    }
    jpegFile.close();
Serial.println("xxxxxxxxxxxx");

    lv_init();

    // Register print function for LVGL debugging
#if LV_USE_LOG != 0
    lv_log_register_print_cb(log_print);
#endif

    // Initialise the TFT
    tft.begin();

    // basic test, this gets overwritten by lvgl & images below
    tft.setTextColor(TFT_BLUE);
    // basic test, this gets overwritten by lvgl & images below
    tft.fillScreen(TFT_ORANGE);

    /* 1. Register display using the built-in TFT_eSPI helper */
    disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));

    /* 2. Optional: Set display rotation */
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_0);

    // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
    TJpgDec.setJpgScale(1);

    // The decoder must be given the exact name of the rendering function above
    TJpgDec.setCallback(tft_output);
    tft.setRotation(2);

    // Time recorded for test purposes
    uint32_t t = millis();

Serial.println("8888888888888");
 jpegFile = SD.open("/horn02.jpg", FILE_READ);  // or, file handle reference for SD library
    if (!jpegFile)
    {
        Serial.print("ERROR: File \"");
        Serial.print("/horn02.jpg");
        Serial.println("\" not found!");
        return;
    }
    jpegFile.close();
    Serial.println("8888888888888");

    // Draw the image, top left at 0,0
    TJpgDec.drawSdJpg(10, 200, "/horn01.jpg");

    // How much time did rendering take
    t = millis() - t;
    Serial.print(t);
    Serial.println(" ms");
/*
    LV_IMAGE_DECLARE(my_image);
    lv_obj_t *imgarr = lv_image_create(lv_screen_active());
    lv_image_set_src(imgarr, &my_image);
    lv_obj_align(imgarr, LV_ALIGN_CENTER, 0, 0);

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_text_letter_space(&style, 5);

    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "Hello LVGL with\nimages and styles!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 100);
    lv_obj_align_to(label, imgarr, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);

    lv_obj_t *imgsdcard = lv_image_create(lv_screen_active());
    lv_image_set_src(imgsdcard, "A:/horn03.jpg");
    lv_obj_center(imgsdcard);
    */
}

void loop()
{
  //  lv_display_flush_ready(disp);
  //  lv_timer_handler();
  //  lv_tick_inc(5);
    delay(5);
}
