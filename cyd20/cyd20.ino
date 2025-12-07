#include "logging.h"
#include "sdcard.h"

const char* infilename = "/btn1.jpg";
const char* outfilename = "/btn4.jpg";

//start over with just sd card again in main, then add logging.h,
// sdcard.h, lovyangfx, lvgl and make commits with those names
// so can easily get back to them

void setup()
{
    Serial.begin(115200);
    delay(2000);
    Serial.println("==========================================");

    // Enable backlight (GPIO 27 must be HIGH)
    pinMode(27, OUTPUT);
    digitalWrite(27, HIGH);

    logit("serial init done, display gpio set high");
    showmemstats();

    logit("now init sd card");
    if (!InitializeSDCard())
    {
        logit("Aborting due to no SD.");
        return;
    }
    showmemstats();

    logit("now open the file");
    // Open the file for reading
    infile = SD.open(infilename);
    if (!infile)
    {
        logit("Error opening file '%s' for reading.", infilename);

        // Close the file
        infile.close();
        logit("File '%s' closed.", infilename);

        exitfunction("readbinarydata");
        while (1)
            ;
    }
    showmemstats();
    logit("Reading from '%s' into buffer.", infilename);
    // Get the file size in bytes
    filesize = infile.size();
    logit("buffer size is '%d'", buffersize);
    logit("file size is '%d'", filesize);
    showmemstats();

    logit("allocat argh");
    uint8_t argh[buffersize];
    showmemstats();

    logit("read argh");
    size_t bytes_read = infile.read(argh, filesize);
    //    size_t bytes_read = infile.read(argh, buffersize);
    showmemstats();

    /*
    if (!readbinarydata(infilename, infile, arrImages[0], filesize))
    {
        // error handling is done in readbinarydata(), just exit
        return;
    }
    
    if (!writebinarydata(outfilename, outfile, arrImages[0]))
    {
        // error handling is done in writebinarydata(), just exit
        return;
    }
*/
    // the new file has been written, show a dir listing to see it
    logit("####### CALL LISTDIR (1 level deep) ########");
    //  listDir(SD, "/", 0);
    logit("####### BACK FROM CALL LISTDIR ########");

    ///////// only sdcard stuff above, if you touch another SPI bus
    ///////// device it kills off the sd card

    //    lcd.init();
    //    lcd.setRotation(2);  // Use native portrait orientationv
    // Set the color mode as needed. (Initial value is 16)
    // 16 - Faster, but the red and blue tones are 5 bits.
    // 24 - Slower, but the gradation expression is cleaner.
    //lcd.setColorDepth(16);  // Set to 16 bits of RGB565
    //    lcd.setColorDepth(24);  // Set to 24 bits for RGB888 - Note that the actual
    // number of colors displayed may be 18 bits (RGB666)
    // depending on the display hardware.
    // start lvgl
    //   lv_init();

    //   lcd.fillScreen(lcd.color888(199, 0, 100));

    // Seed the random number generator using an analog pin for better randomness
    // randomSeed(analogRead(0));

    // Create an LVGL timer to update the color every 1000 milliseconds (1 second)
    //lv_timer_create(update_background_color, 1000, NULL);


    logit("attempting draw");

    /*
    if (lcd.drawJpg(arrImages[0], filesize, 0, 0))
    {
        Serial.println("JPEG drawn successfully from byte array.");
    }
    else
    {
        Serial.println("Error drawing JPEG. Check memory or image format.");
        // Error codes can be retrieved if you use the underlying utility functions.
    }
*/
    logit("back");
}
void loop()
{
    //HandleTouch();
    delay(500);  // Wait for 500 milliseconds (adjust for desired speed)
}