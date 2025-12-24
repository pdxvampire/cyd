// https://randomnerdtutorials.com/esp32-save-data-permanently-preferences/

#include <Preferences.h>

void setup()
{
    Serial.begin(115200);

    // Wait for the serial port to connect so the Serial Monitor printouts work consistently
    // This may not be necessary on Windows or Linux but with my Macbook Air M3 (2024) it is.
    delay(2000);
    Serial.println("");

    // put your setup code here, to run once:
    Preferences preferences;
    preferences.begin("horns", false);

    // if the key does not exist, return a default value of 255 (full)
    unsigned int brightness = preferences.getUInt("brightness", 255);
    Serial.printf("Brightness before:  %u\n", brightness);

    preferences.putUInt("brightness", 42);

    brightness = preferences.getUInt("brightness", 255);
    Serial.printf("Brightness after:  %u\n", brightness);

    preferences.end();
}

void loop()
{
    // put your main code here, to run repeatedly:
}
