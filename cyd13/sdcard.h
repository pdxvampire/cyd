#include <SPI.h>
#include <FS.h>
#include <SD.h>

uint8_t cardType;
uint64_t cardSize;

void InitializeSDCard(void)
{
    enterfunction("InitializeSDCard");

    if (!SD.begin())
    {
        logit("SD.begin failed!");
        logit("Card Mount Failed");
        return;
    }
    logit("SD card initialisation done.");

    cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        logit("No SD card attached");
        return;
    }

    logitnonewline("SD Card Type: ");
    if (cardType == CARD_MMC)
    {
        logitnoindent("MMC");
    }
    else if (cardType == CARD_SD)
    {
        logitnoindent("SDSC");
    }
    else if (cardType == CARD_SDHC)
    {
        logitnoindent("SDHC");
    }
    else
    {
        logitnoindent("UNKNOWN");
    }

    cardSize = SD.cardSize() / (1024 * 1024);
    logit("SD Card Size: %dMB", cardSize);

    exitfunction("InitializeSDCard");
}

// from https:  //randomnerdtutorials.com/esp32-microsd-card-arduino/
void listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    logit("Listing directory: %s", dirname);
    incrementindent();

    File root = fs.open(dirname);

    if (!root)
    {
        logit("Failed to open directory");
        decrementindent();
        return;
    }
    if (!root.isDirectory())
    {
        logit("Not a directory");
        decrementindent();
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            logit("DIR: %s", file.name());
            incrementindent();
            if (levels)
            {
                listDir(fs, file.name(), levels - 1);
            }
            decrementindent();
        }
        else
        {
            logit("FILE: %s", file.name());
            logit("    SIZE: %dkb", file.size() / 1024);
        }

        file = root.openNextFile();
    }
    decrementindent();
}