#include "logging.h"
//#include "sdcard.h"
#include "leds.h"
#include "code.h"

#include <LittleFS.h>
#define FileSys LittleFS

// Include the PNG decoder library
#include <PNGdec.h> // https://github.com/bitbank2/PNGdec Important: version 1.0.2 !

PNG png;
#define MAX_IMAGE_WIDTH 240 // Adjust for your images

int16_t xpos = 0;
int16_t ypos = 0;


#include <LovyanGFX.hpp>
#include "LGFX_JustDisplay.h"


// Here are the callback functions that the decPNG library
// will use to open files, fetch data and close the file.

File pngfile;


LGFX_JustDisplay tft;


void * pngOpen(const char *filename, int32_t *size) {
  Serial.printf("Attempting to open %s\n", filename);
  pngfile = FileSys.open(filename, "r");
  *size = pngfile.size();
  return &pngfile;
}

void pngClose(void *handle) {
  File pngfile = *((File*)handle);
  if (pngfile) pngfile.close();
}

int32_t pngRead(PNGFILE *page, uint8_t *buffer, int32_t length) {
  if (!pngfile) return 0;
  page = page; // Avoid warning
  return pngfile.read(buffer, length);
}

int32_t pngSeek(PNGFILE *page, int32_t position) {
  if (!pngfile) return 0;
  page = page; // Avoid warning
  return pngfile.seek(position);
}


//=========================================v==========================================
//                                      pngDraw
//====================================================================================
// This next function will be called during decoding of the png file to
// render each image line to the TFT.  If you use a different TFT library
// you will need to adapt this function to suit.
// Callback function to draw pixels to the display
void pngDraw(PNGDRAW *pDraw) {
  uint16_t lineBuffer[MAX_IMAGE_WIDTH];
  // ### lgfx
  //static uint16_t dmaBuffer[MAX_IMAGE_WIDTH]; // static so buffer persists after fn exit

  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
/* ### lgfx
                                                         tft.pushImageDMA(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer, dmaBuffer);
  Compilation error: no matching function for call to 'LGFX::pushImageDMA(int16_t&, int, int&, int, uint16_t [240], uint16_t [240])'
  Available constructors:
                                                        void pushImageDMA(int32_t x, int32_t y, int32_t w, int32_t h, const T* data)
                                                        note:   candidate expects 5 arguments, 6 provided
                                                        void pushImageDMA(int32_t x, int32_t y, int32_t w, int32_t h, const void* data, color_depth_t depth, const T* palette)
                                                        candidate expects 7 arguments, 6 provided
  Solution: skip the dmaBuffer: 
  tft.pushImageDMA(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer);
*/  
  // ### lgfx
  //tft.pushImageDMA(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer, dmaBuffer);
  // ### lgfx pushImageDMA give display errors
  // so I'm using the draw method without DMA support:
  //tft.pushImageDMA(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer);
  tft.pushImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer);
}
#include <SPI.h>
#include <FS.h>
#include <SD.h>
void setup()
{
    loglevel++;  // would normally be part of the call to enterfunction for Setup()

    InitializeSerialCommunication();
    InitializeOnboardLEDs();
tft.begin(); // Initialize the display

  // ### lgfx change the rotation from (old) 2 to (new) 0
  tft.setRotation(2);
  tft.fillScreen(TFT_BLUE);

  // Initialize the SD card (check your board's specific CS pin)
  if (!SD.begin(CYD_SD_SS)) { 
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized.");

// Open the JPG file from the SD card
  auto jpgFile = SD.open("/btn1.jpg"); 

  if (jpgFile) {
    // Draw the JPEG image using the file stream
    tft.drawJpg(&jpgFile); 
    jpgFile.close(); // Close the file after drawing
  } else {
    Serial.println("Error opening JPG file");
  }


  //  logit("####### CALL LISTDIR (1 level deep) ########");
  //  listDir(SD, "/", 0);
  //  logit("####### BACK FROM CALL LISTDIR ########");

    // I know the board is working right now,
    // no need to blink the lights
    blinkflag = false;

    exitfunction("setup");
}

void loop()
{
    // Seriously DO NOT ENABLE THESE or you will just
    // get a constantly scrolling Serial Monitor
    // window printing the entering/exiting
    // statements
    //
    // enterfunction("loop");





  // Scan LittleFS and load any *.png files
  File root = LittleFS.open("/", "r");
  while (File file = root.openNextFile()) {
    String strname = file.name();
    strname = "/" + strname;
    Serial.println(file.name());
    // If it is not a directory and filename ends in .png then load it
    if (!file.isDirectory() && strname.endsWith(".png")) {
      // Pass support callback function names to library
      int16_t rc = png.open(strname.c_str(), pngOpen, pngClose, pngRead, pngSeek, pngDraw);
      if (rc == PNG_SUCCESS) {
        tft.startWrite();
        Serial.printf("image specs: (%d x %d), %d bpp, pixel type: %d\n", png.getWidth(), png.getHeight(), png.getBpp(), png.getPixelType());
        uint32_t dt = millis();
        if (png.getWidth() > MAX_IMAGE_WIDTH) {
          Serial.println("Image too wide for allocated lin buffer!");
        }
        else {
          rc = png.decode(NULL, 0);
          png.close();
        }
        tft.endWrite();
        // How long did rendering take...
        Serial.print(millis()-dt); Serial.println("ms");
      }
    }
    delay(3000);
    tft.fillScreen(random(0x10000));
  }
    // Blink so we have a visual clue that the
    // sketch ran in case the display isn't
    // used or isn't working.
    if (blinkflag)
    {
        BlinkOnboardLEDs();
        blinkctr++;

        if (blinkctr >= 3)
        {
            blinkflag = false;
        }

        delay(300);
    }

    // See warning above enterfunction()
    // exitfunction("loop");
}

