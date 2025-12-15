#include <SPI.h>
#include <FS.h>
#include <SD.h>

uint8_t cardType;
uint64_t cardSize;

bool InitializeSDCard(void)
{
    enterfunction("InitializeSDCard");

    if (!SD.begin())
    {
        logit("SD.begin failed!");
        logit("Card Mount Failed");
        exitfunction("InitializeSDCard");
        return false;
    }
    logit("SD card initialisation done.");

    cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        logit("No SD card attached");
        exitfunction("InitializeSDCard");
        return false;
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
    return true;
}

String readFile(fs::FS &fs, const char *path)
{
    Serial.printf("Reading file: %s\n", path);
    File file = fs.open(path, FILE_READ);  // Open the file in read mode
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return "";  // Return empty string if file can't be opened
    }

    Serial.print("Read from file: ");
    String fileContent = "";
    while (file.available())
    {
        // Read byte by byte into the string
        fileContent += (char)file.read();
    }
    file.close();        // Close the file
    return fileContent;  // Return the entire content
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

void TestFileAccess(void)
{
    enterfunction("TestFileAccess");

    if (SD.exists("/helloworld.txt"))
    {
        logit("helloworld.txt exists.");
    }
    else
    {
        logit("helloworld.txt doesn't exist.");
    }

    if (SD.exists("/01.png"))
    {
        logit("01.png exists.");
    }
    else
    {
        logit("01.png doesn't exist.");
    }

    exitfunction("TestFileAccess");
}