#include <LovyanGFX.hpp>  // Display library
#include <lvgl.h>         // LVGL v9
#include "pins_arduino.h"
// Include the jpeg decoder library
#include <TJpg_Decoder.h>  // https://github.com/Bodmer/TJpg_Decoder

// Include SD
#define FS_NO_GLOBALS
#include <FS.h>
#include <SPI.h>
#include <SD.h>
#define SD_CS 5
// going away once get lvgl reading working
// JPEG decoder library
//#include <JPEGDecoder.h>

#include "CST820.h"            // Capacitive touch driver
#include "LGFX_JustDisplay.h"  // Display Setup for ST7789 on ESP32 =======
#include "code.h"
#include "touchinput.h"  // Touch input for LVGL
//#include "sdcard.h"

#if !defined(DEBUGMODE)
#define DEBUGMODE 1
#endif

//#define DEBUGMODE 1

// Button event callback
void on_button_event(lv_event_t *e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        Serial.println("✅ Button Clicked!");
    }
}

static void imgbtn_event_cb(lv_event_t *e)
{
    LV_LOG_USER(" IMG BUTTON WAS CLICKED ");

    lv_obj_t *btn = (lv_obj_t *)lv_event_get_target(e);
    lv_obj_t *label = lv_obj_get_child(btn, 0);
    // lv_label_set_text_fmt(label, "%"LV_PRIu32, RedDotX);

    //// LV_LOG_USER("==== PRE:  ");
    //// char str[10];
    /*
   sprintf(str, "%d", RedDotXpre);
  LV_LOG_USER(str);
 sprintf(str, "%d", beercoords.x2);
  LV_LOG_USER(str);
 */
    /*
  char *source = "Hello";
 char destination[20];
 strcpy(destination, source);
 */
    char *user_data;
    char buffer[100];
    user_data = (char *)lv_event_get_user_data(e);
    //strcpy(buffer,user_data);
    printf("%s", "\nBEGIN USER DATA\n");
    //printf("%s", buffer);
    printf("%s", user_data);
    printf("%s", "\nEND USER DATA\n");
    ////lv_label_set_text_fmt(label, "%s", user_data);

    // these run in the same thread before the ui update and I can't find a way to force the
    // ui to refresh without creating a timer and callback and i'm too tired to care
    // setNowPlayingText(user_data);
    // showNowPlaying();
    //Pause(5);
    // hideNowPlaying();
}
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





void setup()
{
    Serial.begin(115200);

    // Wait for the serial port to connect so the Serial Monitor printouts work consistently
    // This may not be necessary on Windows or Linux but with my Macbook Air M3 (2024) it is.
    delay(2000);

    if (DEBUGMODE)
    {
        Serial.println("");  // insert a newline after the random garbage that gets printed on connection/powerup
        Serial.println("####### START SETUP ################################");
    }
    // Set all chip selects high to avoid bus contention during initialisation of each peripheral
    ////digitalWrite(22, HIGH);  // Touch controller chip select (if used)
    ////digitalWrite(15, HIGH);  // TFT screen chip select
    ////digitalWrite(5, HIGH);   // SD card chips select, must use GPIO 5 (ESP32 SS)

    strcpy(buttonnames[0], "A:/01.png");
    strcpy(buttonnames[0], "A:/02.png");
    strcpy(buttonnames[0], "A:/03.png");
    strcpy(buttonnames[0], "A:/04.png");
    strcpy(buttonnames[0], "A:/01.png");
    strcpy(buttonnames[0], "A:/01.png");
    strcpy(buttonnames[0], "A:/01.png");
    strcpy(buttonnames[0], "A:/01.png");
    strcpy(buttonnames[0], "A:/01.png");
    strcpy(buttonnames[0], "A:/01.png");

    // Backlight
    if (DEBUGMODE)
    {
        Serial.println("BEGIN initialize backlight.");
    }
    pinMode(27, OUTPUT);
    digitalWrite(27, HIGH);
    if (DEBUGMODE)
    {
        Serial.println("END initialize backlight.");
    }

    // Initialise SD before TFT
    if (!SD.begin(SD_CS))
    {
        Serial.println(F("SD.begin failed!"));
        Serial.println("Card Mount Failed");
        return;
    }
    Serial.println("\r\nInitialisation done.");

    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if (cardType == CARD_MMC)
    {
        Serial.println("MMC");
    }
    else if (cardType == CARD_SD)
    {
        Serial.println("SDSC");
    }
    else if (cardType == CARD_SDHC)
    {
        Serial.println("SDHC");
    }
    else
    {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

    Serial.println("initialisation done.");
    Serial.println("####### CALL LISTDIR ########");
    listDir(SD, "/", 0);
    Serial.println("####### BACK FROM CALL LISTDIR ########");



    // Display init
    if (DEBUGMODE)
    {
        Serial.println("BEGIN initialize display.");
    }
    tft.init();
    tft.setRotation(2);  // Use native portrait orientation
    if (DEBUGMODE)
    {
        Serial.println("END initialize display.");
    }


    // Touch init
    if (DEBUGMODE)
    {
        Serial.println("BEGIN initialize touch.");
    }
    touch.begin();
    if (DEBUGMODE)
    {
        //    Serial.printf("\t🔍 Touch Chip ID: 0x%02X\n", touch.readChipID());
        Serial.println("END Initialize touch.");
    }


    // InitializeSDCard();
    /*
    // LVGL init
    lv_init();

    // Display driver
    static lv_color_t buf1[240 * 10];
    static lv_display_t* disp = lv_display_create(240, 320);
    lv_display_set_flush_cb(disp, lv_flush_cb);
    lv_display_set_buffers(disp, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    // Input device (touch)
    lv_indev_t* indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, touchpad_read_cb);

    // Set background color (light gray)
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0xDDDDDD), LV_PART_MAIN);

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_flex_flow(&style, LV_FLEX_FLOW_ROW_WRAP);
    lv_style_set_flex_main_place(&style, LV_FLEX_ALIGN_SPACE_EVENLY);
    lv_style_set_layout(&style, LV_LAYOUT_FLEX);
    lv_obj_add_style(lv_screen_active(), &style, 0);

    int i;
    for (i = 0; i < 10; i++)
    {
        // Create an image button
        lv_obj_t *imagebutton1 = lv_imagebutton_create(lv_screen_active());
        lv_imagebutton_set_src(imagebutton1, LV_IMAGEBUTTON_STATE_RELEASED, NULL, buttonnames[i], NULL);
        //lv_imagebutton_set_src(imagebutton1, LV_IMAGEBUTTON_STATE_RELEASED, NULL, pressed, NULL);
        lv_obj_set_width(imagebutton1, 48);

        lv_obj_add_event_cb(imagebutton1, imgbtn_event_cb, LV_EVENT_CLICKED, buttonnames[i]);

        lv_obj_align(imagebutton1, LV_ALIGN_CENTER, 0, 0);
    }
    
    // Create centered button with label
    lv_obj_t* btn = lv_button_create(lv_screen_active());
    lv_obj_center(btn);
    lv_obj_add_event_cb(btn, on_button_event, LV_EVENT_ALL, NULL);

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, "Hello Touch World");
    lv_obj_center(label);
*/


    /*
    if (DEBUGMODE)
    {
        Serial.println("BEGIN draw jpg buttons.");
    }
    drawSdJpeg("/btn1.jpg", 12, 0);  //x = right      y = down pixel location
    drawSdJpeg("/btn1.jpg", 12, 108);
    drawSdJpeg("/btn1.jpg", 12, 216);
    drawSdJpeg("/btn1.jpg", 128, 0);
    drawSdJpeg("/btn1.jpg", 128, 108);
    drawSdJpeg("/btn1.jpg", 128, 215);
    if (DEBUGMODE)
    {
        Serial.println("END draw jpg buttons.");
    }

    if (DEBUGMODE)
    {
        Serial.println("####### CALL LISTDIR ########");
    }
    listDir(SD, "/", 0);
    if (DEBUGMODE)
    {
        Serial.println("####### BACK FROM CALL LISTDIR ########");
    }
*/

    // Initialise the TFT
    tft.begin();
    //tft.setRotation(2); // it is already in portrait orientation
    tft.setTextColor(0xFFFF, 0x0000);
    tft.fillScreen(TFT_BLACK);
    tft.setSwapBytes(true);  // We need to swap the colour bytes (endianess)

    // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
    TJpgDec.setJpgScale(1);

    // The decoder must be given the exact name of the rendering function above
    TJpgDec.setCallback(tft_output);

    tft.drawCentreString("Touch Image -> next", tft.width() / 2, 20, 2);
    tft.drawCentreString("Touch Image -> next", tft.width() / 2, 290, 2);

lv_indev_t* indev = lv_indev_create();
lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
lv_indev_set_read_cb(indev, touchpad_read_cb);


    if (DEBUGMODE)
    {
        Serial.println("####### DONE SETUP #################################");
    }
}

void displayImage(String imagename)
{
    Serial.printf("displayImage filename: %s\n", imagename);
    tft.fillScreen(TFT_WHITE);
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
    tft.drawCentreString("Touch Image -> next", tft.width() / 2, 20, 2);
    tft.drawCentreString("Touch Image -> next", tft.width() / 2, 290, 2);
}

void loop()
{
    /*
    if (millis() - lastLvTick > LVGL_TICK_PERIOD)
    {
        lv_tick_inc(LVGL_TICK_PERIOD);
        lastLvTick = millis();
    }

    lv_timer_handler();
    delay(5);
    */
    int32_t x, y;
    lgfx::v1::touch_point_t tp;
    if (tft.getTouch(&x, &y))
    {
        char buf[40];
        sprintf(buf, "Touch at rawX: %d rawY: %d", x, y);
        Serial.println(buf);
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_GREEN, TFT_BLACK);
        sprintf(buf, "Touch at rawX: %d", x);
        tft.drawCentreString(buf, tft.width() / 2, tft.height() / 2 - 20, 2);  // the touch point
        sprintf(buf, "Touch at rawY: %d", y);
        tft.drawCentreString(buf, tft.width() / 2, tft.height() / 2, 2);  // the touch point
        delay(1000);
        imageIndex++;
        if (imageIndex > (MAX_IMAGES - 1)) imageIndex = 0;
        displayImage(fileNames[imageIndex]);
        tft.setTextColor(TFT_RED, TFT_BLACK);
        tft.drawCentreString("Touch Image -> next", tft.width() / 2, 20, 2);
        tft.drawCentreString("Touch Image -> next", tft.width() / 2, 290, 2);
    }
}