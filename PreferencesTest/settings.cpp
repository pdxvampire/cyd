// https://randomnerdtutorials.com/esp32-save-data-permanently-preferences/
#include <Arduino.h>
#include <Preferences.h>
#include "settings.h"
#include "logging.h"

int brightness = -1;
  String pct = "";
bool darkmode = true;
int percentage = -1;

void LoadSettings()
{
    enterfunction("LoadSettings");

    darkmode = GetDarkMode();
    brightness = GetBrightness();

    // Saved value is the real 10..255, convert here to % for the slider.
    percentage = (int)map(GetBrightness(), 0, 255, 0, 100);
    logit("############################################### int percentage: %d", percentage);
    pct = String(percentage);
    logit("################## JUST BEFORE EXITING LOADSETTINGS ############################# String pct: %s", pct);

    exitfunction("LoadSettings");
}

int GetBrightness()
{
    enterfunction("GetBrightness");

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

    exitfunction("GetBrightness");
    return val;
}

void SetBrightness(int val)
{
    enterfunction("SetBrightness");

    Preferences preferences;

    preferences.begin("horns", false);

    preferences.putInt("brightness", val);

    preferences.end();

    logit("set brightness:  %d", val);

    exitfunction("SetBrightness");
}

bool GetDarkMode()
{
    enterfunction("GetDarkMode");

    Preferences preferences;
    preferences.begin("horns", false);

    // if the key does not exist, default to dark
    bool val = preferences.getBool("darkmode", true);

    preferences.end();

    logit("got darkmode:  %b", val);

    exitfunction("GetDarkMode");
    return val;
}

void SetDarkMode(bool val)
{
    enterfunction("SetDarkMode");

    Preferences preferences;

    preferences.begin("horns", false);

    preferences.putBool("darkmode", val);

    preferences.end();

    logit("set darkmode:  %b", val);

    exitfunction("SetDarkMode");
}