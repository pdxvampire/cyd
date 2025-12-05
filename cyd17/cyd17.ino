#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include "logging.h"

const int chipSelect = 5;           // Chip select pin for the SD module
const int bufferSize = 18432;  // Define the size of your buffer
char readBuffer[bufferSize];        // Character array (buffer) to store data
int bytesRead = 0;                  // Counter for the number of bytes read

uint8_t binarydata[bufferSize];

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

void setup()
{
    Serial.begin(115200);
    delay(2000);
    // Set all chip selects high to avoid bus contention during initialisation of each peripheral
    digitalWrite(22, HIGH);  // Touch controller chip select (if used)
    digitalWrite(15, HIGH);  // TFT screen chip select
    digitalWrite(5, HIGH);   // SD card chips select, must use GPIO 5 (ESP32 SS)


    Serial.print("Initializing SD card...");
    if (!SD.begin(chipSelect))
    {
        Serial.println("initialization failed!");
        while (true)
            ;  // Halt if failed
    }
    Serial.println("initialization done.");

    // Open the file for reading
    File dataFile = SD.open("/btn1.jpg");

    if (dataFile)
    {
        Serial.println("Reading from data.txt into buffer:");

        // Read until the buffer is full or the end of the file is reached
        //while (dataFile.available() && bytesRead < bufferSize - 1)
        //{
        //    readBuffer[bytesRead] = (char)dataFile.read();  // Read one byte and store in buffer
        //    bytesRead++;
        //}

        // Null-terminate the string in the buffer
        //readBuffer[bytesRead] = '\\0';
// Get the file size in bytes
  size_t fileSize = dataFile.size();

size_t bytes_read = dataFile.read((uint8_t*)binarydata, fileSize);
  if (bytes_read == fileSize) {
    Serial.println("Data successfully read from file");
 //   Serial.print("Read data: ");
 //   for (int i = 0; i < fileSize; i++) {
 //     Serial.printf("0x%02X ", binarydata[i]);
 //   }
 //   Serial.println();
  } else {
    Serial.println("Error reading data");
  }


        // Close the file
        dataFile.close();
        Serial.println("File closed.");


        File myFile = SD.open("/btn2.jpg", FILE_WRITE);
        if (myFile)
        {
            Serial.println("File writing from 0 byte.");
            myFile.seek(0);  //Write from 0 byte
            myFile.write(binarydata, fileSize);
            
        }
        else
        {
            Serial.println("Error Opening File");
        }
                        // if the file didn't open, print an error:
        myFile.close();  // close the file:
        Serial.println("File write done.");

        // Print the buffer content to the Serial Monitor
        //Serial.println(readBuffer);

        logit("####### CALL LISTDIR (1 level deep) ########");
    listDir(SD, "/", 0);
    logit("####### BACK FROM CALL LISTDIR ########");

    }
    else
    {
        // If the file didn't open, print an error
        Serial.println("Error opening data.txt");
    }
}

void loop()
{
    // Nothing happens in loop as we read the file once in setup
}
