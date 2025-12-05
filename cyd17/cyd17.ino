#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include "logging.h"
#include "leds.h"
#include "sdcard.h"

void setup()
{
    Serial.begin(115200);
    delay(2000);
    // Set all chip selects high to avoid bus contention during initialisation of each peripheral
    digitalWrite(22, HIGH);  // Touch controller chip select (if used)
    digitalWrite(15, HIGH);  // TFT screen chip select
    digitalWrite(5, HIGH);   // SD card chips select, must use GPIO 5 (ESP32 SS)

    InitializeSDCard();

    const char* infilename = "/btn1.jpg";
    const char* outfilename = "/btn3.jpg";

    if (!readbinarydata(infilename, infile, binarydata, filesize))
    {
        // error handling is done in readbinarydata(), just exit
        return;
    }

    // 'binarydata' now contains the binary data of the input file

    if (!writebinarydata(outfilename, outfile, binarydata))
    {
        // error handling is done in writebinarydata(), just exit
        return;
    }

    // the new file has been written, show a dir listing to see it
    logit("####### CALL LISTDIR (1 level deep) ########");
    listDir(SD, "/", 0);
    logit("####### BACK FROM CALL LISTDIR ########");

    TurnOffOnboardLEDs();
}

void loop()
{
    // NOOP
}
