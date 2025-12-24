// https://randomnerdtutorials.com/esp32-save-data-permanently-preferences/

#include <Preferences.h>
#include "settings.h"
#include "logging.h"

int GetBrightness()
{
    Preferences preferences;

    preferences.begin("horns", false);

    // if the key does not exist, return a default value of 255 (full)
    int brightness = preferences.getInt("brightness", -1);

    preferences.end();

    logit("got brightness:  %d", brightness);

    if (brightness < 10)
    {
        logit("brightness invalid, setting to 255");
        brightness = 255;
    }

    return brightness;
}

void SetBrightness(int brightness)
{
    Preferences preferences;

    preferences.begin("horns", false);

    preferences.putInt("brightness", brightness);

    preferences.end();

    logit("set brightness:  %d", brightness);
}