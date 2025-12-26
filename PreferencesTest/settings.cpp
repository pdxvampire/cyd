// https://randomnerdtutorials.com/esp32-save-data-permanently-preferences/
#include <Arduino.h>
#include <Preferences.h>
#include "settings.h"
#include "logging.h"

int brightness = -1;
const char* pct = "";
bool darkmode = true;
int percentage = -1;

void LoadSettings()
{
    darkmode = GetDarkMode();
    brightness = GetBrightness();

    // Saved value is the real 10..255, convert here to % for the slider.
    percentage = (int)map(GetBrightness(), 0, 255, 0, 100);
    logit("############################################### int percentage: %d", percentage);
    String tmpstrpct = String(percentage);
    logit("############################################### String tmpstrpct: %s", tmpstrpct);
    pct = tmpstrpct.c_str();
    logit("############################################### const char* pct: %s", pct);
}

int GetBrightness()
{
    Preferences preferences;
    preferences.begin("horns", false);

    // if the key does not exist, return a default value of -1 so we know that it was bad (full)
    int val = preferences.getInt("brightness", -1);

    preferences.end();

    logit("got brightness:  %d", val);

    if (val < 10)
    {
        logit("brightness invalid, setting to 255");
        val = 255;
    }

    return val;
}

void SetBrightness(int val)
{
    Preferences preferences;

    preferences.begin("horns", false);

    preferences.putInt("brightness", val);

    preferences.end();

    logit("set brightness:  %d", val);
}

bool GetDarkMode()
{
    Preferences preferences;
    preferences.begin("horns", false);

    // if the key does not exist, default to dark
    bool val = preferences.getBool("darkmode", true);

    preferences.end();

    logit("got darkmode:  %b", val);

    return val;
}

void SetDarkMode(bool val)
{
    Preferences preferences;

    preferences.begin("horns", false);

    preferences.putBool("darkmode", val);

    preferences.end();

    logit("set darkmode:  %b", val);
}