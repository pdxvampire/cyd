#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <TFT_eSPI.h>
#include "code.h"
TFT_eSPI tft = TFT_eSPI();

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    // Set all chip selects high to avoid bus contention during initialisation of each peripheral
    digitalWrite(22, HIGH);  // Touch controller chip select (if used)
    digitalWrite(15, HIGH);  // TFT screen chip select
    digitalWrite(5, HIGH);   // SD card chips select, must use GPIO 5 (ESP32 SS)

    tft.begin();
    if (!SD.begin())
    {
        Serial.println("Card Mount Failed");
        return;
    }
    cardType = SD.cardType();
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

    cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

    Serial.println("initialisation done.");

    // set up onboard LED pins so we can get visual feedback that at least that much is working
    delay(1000);
    for (int p : ledPins) pinMode(p, OUTPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    BlinkOnboardLEDs();
}
