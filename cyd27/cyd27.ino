#include <lvgl.h>
#include <SPI.h>

#include <FS.h>
#include <SD.h>
//#include "image.h"

#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

// JPEG decoder library
#include <JPEGDecoder.h>
#include <TJpg_Decoder.h>


void log_print(lv_log_level_t level, const char *buf)
{
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
}

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

void showTime(uint32_t msTime)
{
    //tft.setCursor(0, 0);
    //tft.setTextFont(1);
    //tft.setTextSize(2);
    //tft.setTextColor(TFT_WHITE, TFT_BLACK);
    //tft.print(F(" JPEG drawn in "));
    //tft.print(msTime);
    //tft.println(F(" ms "));
    Serial.print(F(" JPEG drawn in "));
    Serial.print(msTime);
    Serial.println(F(" ms "));
}

void drawSdJpeg(const char *filename, int xpos, int ypos)
{

    // Open the named file (the Jpeg decoder library will close it)
    File jpegFile = SD.open(filename, FILE_READ);  // or, file handle reference for SD library

    if (!jpegFile)
    {
        Serial.print("ERROR: File \"");
        Serial.print(filename);
        Serial.println("\" not found!");
        return;
    }

    Serial.println("===========================");
    Serial.print("Drawing file: ");
    Serial.println(filename);
    Serial.println("===========================");

    // Use one of the following methods to initialise the decoder:
    bool decoded = JpegDec.decodeSdFile(jpegFile);  // Pass the SD file handle to the decoder,
    //bool decoded = JpegDec.decodeSdFile(filename);  // or pass the filename (String or character array)

    if (decoded)
    {
        // print information about the image to the serial port
        jpegInfo();
        // render the image onto the screen at given coordinates
        jpegRender(xpos, ypos);
    }
    else
    {
        Serial.println("Jpeg file format not supported!");
    }
}

//####################################################################################################
// Draw a JPEG on the TFT, images will be cropped on the right/bottom sides if they do not fit
//####################################################################################################
// This function assumes xpos,ypos is a valid screen coordinate. For convenience images that do not
// fit totally on the screen are cropped to the nearest MCU size and may leave right/bottom borders.
void jpegRender(int xpos, int ypos)
{

    //jpegInfo(); // Print information from the JPEG file (could comment this line out)

    uint16_t *pImg;
    uint16_t mcu_w = JpegDec.MCUWidth;
    uint16_t mcu_h = JpegDec.MCUHeight;
    uint32_t max_x = JpegDec.width;
    uint32_t max_y = JpegDec.height;

    bool swapBytes = tft.getSwapBytes();
    tft.setSwapBytes(true);

    // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
    // Typically these MCUs are 16x16 pixel blocks
    // Determine the width and height of the right and bottom edge image blocks
    uint32_t min_w = jpg_min(mcu_w, max_x % mcu_w);
    uint32_t min_h = jpg_min(mcu_h, max_y % mcu_h);

    // save the current image block size
    uint32_t win_w = mcu_w;
    uint32_t win_h = mcu_h;

    // record the current time so we can measure how long it takes to draw an image
    uint32_t drawTime = millis();

    // save the coordinate of the right and bottom edges to assist image cropping
    // to the screen size
    max_x += xpos;
    max_y += ypos;

    // Fetch data from the file, decode and display
    while (JpegDec.read())
    {                           // While there is more data in the file
        pImg = JpegDec.pImage;  // Decode a MCU (Minimum Coding Unit, typically a 8x8 or 16x16 pixel block)

        // Calculate coordinates of top left corner of current MCU
        int mcu_x = JpegDec.MCUx * mcu_w + xpos;
        int mcu_y = JpegDec.MCUy * mcu_h + ypos;

        // check if the image block size needs to be changed for the right edge
        if (mcu_x + mcu_w <= max_x) win_w = mcu_w;
        else win_w = min_w;

        // check if the image block size needs to be changed for the bottom edge
        if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
        else win_h = min_h;

        // copy pixels into a contiguous block
        if (win_w != mcu_w)
        {
            uint16_t *cImg;
            int p = 0;
            cImg = pImg + win_w;
            for (int h = 1; h < win_h; h++)
            {
                p += mcu_w;
                for (int w = 0; w < win_w; w++)
                {
                    *cImg = *(pImg + w + p);
                    cImg++;
                }
            }
        }

        // calculate how many pixels must be drawn
        uint32_t mcu_pixels = win_w * win_h;

        // draw image MCU block only if it will fit on the screen
        if ((mcu_x + win_w) <= tft.width() && (mcu_y + win_h) <= tft.height())
            tft.pushImage(mcu_x, mcu_y, win_w, win_h, pImg);
        else if ((mcu_y + win_h) >= tft.height())
            JpegDec.abort();  // Image has run off bottom of screen so abort decoding
    }

    tft.setSwapBytes(swapBytes);

    showTime(millis() - drawTime);  // These lines are for sketch testing only
}

//####################################################################################################
// Print image information to the serial port (optional)
//####################################################################################################
// JpegDec.decodeFile(...) or JpegDec.decodeArray(...) must be called before this info is available!
void jpegInfo()
{

    // Print information extracted from the JPEG file
    Serial.println("JPEG image info");
    Serial.println("===============");
    Serial.print("Width      :");
    Serial.println(JpegDec.width);
    Serial.print("Height     :");
    Serial.println(JpegDec.height);
    Serial.print("Components :");
    Serial.println(JpegDec.comps);
    Serial.print("MCU / row  :");
    Serial.println(JpegDec.MCUSPerRow);
    Serial.print("MCU / col  :");
    Serial.println(JpegDec.MCUSPerCol);
    Serial.print("Scan type  :");
    Serial.println(JpegDec.scanType);
    Serial.print("MCU width  :");
    Serial.println(JpegDec.MCUWidth);
    Serial.print("MCU height :");
    Serial.println(JpegDec.MCUHeight);
    Serial.println("===============");
    Serial.println("");
}


void setup()
{
    // put your setup code here, to run once:

    Serial.begin(115200);

    // Wait for the serial port to connect so the Serial Monitor printouts work consistently
    // This may not be necessary on Windows or Linux but with my Macbook Air M3 (2024) it is.
    delay(2000);

    Serial.println("");

    // Register print function for LVGL debugging
    lv_log_register_print_cb(log_print);

    tft.begin();

    pinMode(27, OUTPUT);
    digitalWrite(27, HIGH);

    if (!SD.begin())
    {
        Serial.println("Card Mount Failed");
        return;
    }

    tft.setRotation(2);
    tft.fillScreen(0x001100);

    drawSdJpeg("/horn04.jpg", 128, 200);

    Serial.println("xxxxxxxxxxxx");
    File jpegFile = SD.open("/horn02.jpg", FILE_READ);  // or, file handle reference for SD library
    if (!jpegFile)
    {
        Serial.print("ERROR: File \"");
        Serial.print("/horn02.jpg");
        Serial.println("\" not found!");
        return;
    }
    jpegFile.close();

    // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
    TJpgDec.setJpgScale(1);

    // The decoder must be given the exact name of the rendering function above
    TJpgDec.setCallback(tft_output);


    Serial.println("xxxxxxxxxxxx");

    drawSdJpeg("/horn01.jpg", 0, 200);


    // Draw the image, top left at 0,0
    TJpgDec.drawSdJpg(0, 90, "/btn1.jpg");


    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello LVGL with TJpgDec!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *img = lv_image_create(lv_screen_active());
    lv_image_set_src(img, "/btn1.jpg");  // 'A:' is your filesystem driver
    lv_obj_center(img);

    //LV_IMAGE_DECLARE(my_image);
    //lv_obj_t * img1 = lv_image_create(lv_screen_active());
    //lv_image_set_src(img1, &my_image);
    //lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * labelf = lv_label_create(lv_screen_active());
    lv_label_set_text(labelf, "Hello LVGL!");
}

void loop()
{
    // put your main code here, to run repeatedly:
}
