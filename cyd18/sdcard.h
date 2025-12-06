#include <SPI.h>
#include <FS.h>
#include <SD.h>

uint8_t cardType;
uint64_t cardSize;

// Define the size of your buffer,
// in this case set a maximum of 50k which should be way
// more than needed for a single 120x120 jpg.
// Yes it would be possible to use std::vector to
// dynamically handle the size but that is not recommended
// on Arduino due to a high likelihood of heap corruption.
const int buffersize = 51200;

//uint8_t binarydata[buffersize]; /// now in .ino
size_t filesize;  // actual file size from File object

File infile;
File outfile;

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

bool readbinarydata(const char *infilename, File &infile, uint8_t *buffer, size_t &filesize)
{
    enterfunction("readbinarydata");

    // Open the file for reading
    infile = SD.open(infilename);

    if (!infile)
    {
        logit("Error opening file '%s' for reading.", infilename);

        // Close the file
        infile.close();
        logit("File '%s' closed.", infilename);

        exitfunction("readbinarydata");
        return false;
    }

    logit("Reading from '%s' into buffer.", infilename);

    // Get the file size in bytes
    filesize = infile.size();

    size_t bytes_read = infile.read((uint8_t *)buffer, filesize);

    if (bytes_read == filesize)
    {
        logit("Data successfully read from '%s' into buffer, '%d' bytes.", infilename, filesize);

        // If you really want to see the hex...
        //   Serial.print("Read data: ");
        //   for (int i = 0; i < filesize; i++) {
        //     Serial.printf("0x%02X ", binarydata[i]);
        //   }
        //   logit("");

        // Close the file
        infile.close();
        logit("File '%s' closed.", infilename);
    }
    else
    {
        logit("Error reading file '%s'.", infilename);

        // Close the file
        infile.close();
        logit("File '%s' closed.", infilename);

        exitfunction("readbinarydata");
        return false;
    }

    // whatever was passed in for buffer now contains the binary data
    exitfunction("readbinarydata");
    return true;
}

bool writebinarydata(const char *outfilename, File &outfile, const uint8_t *buffer)
{
    enterfunction("writebinarydata");

    outfile = SD.open(outfilename, FILE_WRITE);
    if (!outfile)
    {
        logit("Error opening file '%s' for writing.", outfilename);

        // Close the file
        outfile.close();
        logit("File '%s' closed.", outfilename);

        exitfunction("writebinarydata");
        return false;
    }

    logit("File writing from 0 byte.");
    outfile.seek(0);  //Write from 0 byte
    outfile.write(buffer, filesize);

    logit("Wrote '%d' bytes.", filesize);

    // Close the file
    outfile.close();
    logit("File '%s' closed.", outfilename);

    // outfile now contains the binary data from whatever was passed in for buffer
    exitfunction("writebinarydata");
    return true;
}