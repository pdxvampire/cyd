#ifndef SETTINGS_H
#define SETTINGS_H

int GetBrightness();
void SetBrightness(int);

bool GetDarkMode();
void SetDarkMode(bool);

void LoadSettings();

extern int brightness;
extern String pct;
extern bool darkmode;
extern int percentage;

#endif  //SETTINGS_H