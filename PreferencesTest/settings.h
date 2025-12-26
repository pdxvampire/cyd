#ifndef SETTINGS_H
#define SETTINGS_H

int GetBrightness();
void SetBrightness(int);

bool GetDarkMode();
void SetDarkMode(bool);

void LoadSettings();

extern int brightness;
extern const char *pct;
extern bool darkmode;

#endif  //SETTINGS_H