#include <Arduino.h>  // Automatically included in .ino files
#include "logging.h"
#include "physical.h"
#include "layout.h"
#include "display.h"

extern TFT_eSPI tft;
extern std::vector<Horn> horns;

void DoSomethingButton01()
{
    enterfunction("DoSomethingButton01");

    ShowPopupLabelBriefly("PLAY HORN 01");

    exitfunction("DoSomethingButton01");
}

void DoSomethingButton02()
{
    enterfunction("DoSomethingButton02");

    ShowPopupLabelBriefly("PLAY HORN 02");

    exitfunction("DoSomethingButton02");
}

void DoSomethingButton03()
{
    enterfunction("DoSomethingButton03");

    ShowPopupLabelBriefly("PLAY HORN 03");

    exitfunction("DoSomethingButton03");
}

void DoSomethingButton04()
{
    enterfunction("DoSomethingButton04");

    ShowPopupLabelBriefly("PLAY HORN 04");

    exitfunction("DoSomethingButton04");
}

void DoSomethingButton05()
{
    enterfunction("DoSomethingButton05");

    ShowPopupLabelBriefly("PLAY HORN 05");

    exitfunction("DoSomethingButton05");
}

void DoSomethingButton06()
{
    enterfunction("DoSomethingButton06");

    ShowPopupLabelBriefly("PLAY HORN 06");

    exitfunction("DoSomethingButton06");
}

void DoSomethingButton07()
{
    enterfunction("DoSomethingButton07");

    ShowPopupLabelBriefly("PLAY HORN 07");

    exitfunction("DoSomethingButton07");
}

void DoSomethingButton08()
{
    enterfunction("DoSomethingButton08");

    ShowPopupLabelBriefly("PLAY HORN 08");

    exitfunction("DoSomethingButton08");
}

void DoSomethingButton09()
{
    enterfunction("DoSomethingButton09");

    ShowPopupLabelBriefly("PLAY HORN 09");

    exitfunction("DoSomethingButton09");
}

void DoSomethingButton10()
{
    enterfunction("DoSomethingButton10");

    logit("call load anim for settings screen");
    lv_screen_load_anim(settingsscreen, LV_SCREEN_LOAD_ANIM_MOVE_TOP, 30, 0, false);

    logit("flush display");
    lv_display_flush_ready(disp);

    exitfunction("DoSomethingButton10");
}

void DoSomethingButton11()
{
    enterfunction("DoSomethingButton11");

    // NOOP

    exitfunction("DoSomethingButton11");
}

void DoSomethingButton12()
{
    enterfunction("DoSomethingButton12");

    // NOOP

    exitfunction("DoSomethingButton12");
}
