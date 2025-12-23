#include <Arduino.h>  // Automatically included in .ino files
#include "physical.h"
#include "layout.h"
#include "display.h"

extern TFT_eSPI tft;
extern std::vector<Horn> horns;

void DoSomethingButton01()
{
    ShowPopupLabelBriefly(horns[0].name);
    tft.setBrightness(255);
}

void DoSomethingButton02()
{
    ShowPopupLabelBriefly(horns[1].name);
}

void DoSomethingButton03()
{
    ShowPopupLabelBriefly(horns[2].name);
}

void DoSomethingButton04()
{
    ShowPopupLabelBriefly(horns[3].name);
}

void DoSomethingButton05()
{
    ShowPopupLabelBriefly(horns[4].name);
}

void DoSomethingButton06()
{
    ShowPopupLabelBriefly(horns[5].name);
}

void DoSomethingButton07()
{
    ShowPopupLabelBriefly(horns[6].name);
}

void DoSomethingButton08()
{
    ShowPopupLabelBriefly(horns[7].name);
}

void DoSomethingButton09()
{
    ShowPopupLabelBriefly(horns[0].name);
}

void DoSomethingButton10()
{
    ShowSettingsScreen();
}

void DoSomethingButton11()
{
    // NOOP
}

void DoSomethingButton12()
{
    // NOOP
}
