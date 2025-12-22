#include <Arduino.h>  // Automatically included in .ino files
#include "sdcard.h"

void listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if (!root)
    {
        Serial.println("Failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if (levels)
            {
                listDir(fs, file.path(), levels - 1);
            }
        }
        else
        {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }

        file = root.openNextFile();
    }
}

void createDir(fs::FS &fs, const char *path)
{
    Serial.printf("Creating Dir: %s\n", path);
    if (fs.mkdir(path))
    {
        Serial.println("Dir created");
    }
    else
    {
        Serial.println("mkdir failed");
    }
}

void removeDir(fs::FS &fs, const char *path)
{
    Serial.printf("Removing Dir: %s\n", path);
    if (fs.rmdir(path))
    {
        Serial.println("Dir removed");
    }
    else
    {
        Serial.println("rmdir failed");
    }
}

void readFile(fs::FS &fs, const char *path)
{
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while (file.available())
    {
        Serial.write(file.read());
    }
    file.close();
}

void writeFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return;
    }
    if (file.print(message))
    {
        Serial.println("File written");
    }
    else
    {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if (!file)
    {
        Serial.println("Failed to open file for appending");
        return;
    }
    if (file.print(message))
    {
        Serial.println("Message appended");
    }
    else
    {
        Serial.println("Append failed");
    }
    file.close();
}

void renameFile(fs::FS &fs, const char *path1, const char *path2)
{
    Serial.printf("Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2))
    {
        Serial.println("File renamed");
    }
    else
    {
        Serial.println("Rename failed");
    }
}

void deleteFile(fs::FS &fs, const char *path)
{
    Serial.printf("Deleting file: %s\n", path);
    if (fs.remove(path))
    {
        Serial.println("File deleted");
    }
    else
    {
        Serial.println("Delete failed");
    }
}

void testFileIO(fs::FS &fs, const char *path)
{
    File file = fs.open(path);
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;
    if (file)
    {
        len = file.size();
        size_t flen = len;
        start = millis();
        while (len)
        {
            size_t toRead = len;
            if (toRead > 512)
            {
                toRead = 512;
            }
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        Serial.printf("%u bytes read for %lu ms\n", flen, end);
        file.close();
    }
    else
    {
        Serial.println("Failed to open file for reading");
    }

    file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return;
    }

    size_t i;
    start = millis();
    for (i = 0; i < 2048; i++)
    {
        file.write(buf, 512);
    }
    end = millis() - start;
    Serial.printf("%u bytes written for %lu ms\n", 2048 * 512, end);
    file.close();
}

/*--------------------------------------------------------------------------------
 * Setup SD card (Mounting fails if card is not inserted)
 * Note the global variable 'SPI' is assigned to 'VSPI' same as 'CYD_SD_SPI_BUS'.
 * https://github.com/espressif/arduino-esp32/blob/master/libraries/SPI/src/SPI.cpp#L333-L337
 *--------------------------------------------------------------------------------*/
void sdcard_setup()
{

#if false

#ifdef REASSIGN_PINS
  SPI.begin(sck, miso, mosi, cs);

  if (!SD.begin(cs)) {
#else
  // this also works since CYD_SD_* are assigned to the default spi pins.
  if (!SD.begin()) {
#endif
    Serial.println("Card Mount Failed");
    return;
  }

#elif 0

    // this also works since the SD card is connected to the default SPI bus, VSPI
    // and when display and touch panel are connected to HSPI
    if (!SD.begin())
    {
        Serial.println("Card Mount Failed");
        return;
    }

#elif 1

#ifndef CYD_SD_SPI_BUS
#define CYD_SD_SCK SCK
#define CYD_SD_MISO MISO
#define CYD_SD_MOSI MOSI
#define CYD_SD_SS SS
#endif

    // this also works since the SD card is connected to the SPI bus, HSPI
    // and when display and touch panel are connected to VSPI
    static SPIClass spi = SPIClass(HSPI /*CYD_SD_SPI_BUS*/);  // VSPI
    spi.begin(CYD_SD_SCK, CYD_SD_MISO, CYD_SD_MOSI, CYD_SD_SS);

    if (!SD.begin(CYD_SD_SS, spi, 50000000))
    {
        Serial.println("Card Mount Failed");
        return;
    }

#else

// this does not work because SD has different pins
#define SD_CONFIG SS, tft.getSPIinstance(), 20000000

    if (!SD.begin(SD_CONFIG))
    {
        Serial.println("Card Mount Failed");
        return;
    }

#endif

    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE)
    {
        Serial.println("No SD card attached");
        return;
    }

#if false
  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }
#endif
}

/*--------------------------------------------------------------------------------
 * Test basic functions
 *--------------------------------------------------------------------------------*/
void sdcard_test(void)
{
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

    listDir(SD, "/", 0);
    createDir(SD, "/mydir");
    listDir(SD, "/", 0);
    removeDir(SD, "/mydir");
    listDir(SD, "/", 2);
    writeFile(SD, "/hello.txt", "Hello ");
    appendFile(SD, "/hello.txt", "World!\n");
    readFile(SD, "/hello.txt");
    deleteFile(SD, "/foo.txt");
    renameFile(SD, "/hello.txt", "/foo.txt");
    readFile(SD, "/foo.txt");
    testFileIO(SD, "/test.txt");
    Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

inline void color565toRGB(uint16_t color, uint8_t &r, uint8_t &g, uint8_t &b)
{
    r = (color >> 8) & 0x00F8;
    g = (color >> 3) & 0x00FC;
    b = (color << 3) & 0x00F8;
}

