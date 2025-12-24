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

    ShowPopupLabelBriefly(horns[1].name);

    exitfunction("DoSomethingButton01");
}

void DoSomethingButton02()
{
    enterfunction("DoSomethingButton02");

    ShowPopupLabelBriefly(horns[2].name);

    exitfunction("DoSomethingButton02");
}

void DoSomethingButton03()
{
    enterfunction("DoSomethingButton03");

    ShowPopupLabelBriefly(horns[3].name);

    exitfunction("DoSomethingButton03");
}

void DoSomethingButton04()
{
    enterfunction("DoSomethingButton04");

    ShowPopupLabelBriefly(horns[4].name);

    exitfunction("DoSomethingButton04");
}

void DoSomethingButton05()
{
    enterfunction("DoSomethingButton05");

    ShowPopupLabelBriefly(horns[5].name);

    exitfunction("DoSomethingButton05");
}

void DoSomethingButton06()
{
    enterfunction("DoSomethingButton06");

    ShowPopupLabelBriefly(horns[6].name);

    exitfunction("DoSomethingButton06");
}

void DoSomethingButton07()
{
    enterfunction("DoSomethingButton07");

    ShowPopupLabelBriefly(horns[7].name);

    exitfunction("DoSomethingButton07");
}

void DoSomethingButton08()
{
    enterfunction("DoSomethingButton08");

    ShowPopupLabelBriefly(horns[8].name);

    enterfunction("DoSomethingButton08");
}

void DoSomethingButton09()
{
    enterfunction("DoSomethingButton09");

    ShowPopupLabelBriefly(horns[9].name);

    enterfunction("DoSomethingButton09");
}

void DoSomethingButton10()
{
    enterfunction("DoSomethingButton10");

    logit("call CreateSettingsScreen");
    CreateSettingsScreen();
    logit("call load anim for settings screen");
    lv_screen_load_anim(settingsscreen, LV_SCREEN_LOAD_ANIM_MOVE_TOP, 30, 0, true);
    //lv_obj_del_async(screen1);
    //lv_obj_del(screen1);
    logit("flush display");
    lv_display_flush_ready(disp);

    enterfunction("DoSomethingButton10");
}

void DoSomethingButton11()
{
    enterfunction("DoSomethingButton11");

    // NOOP

    enterfunction("DoSomethingButton11");
}

void DoSomethingButton12()
{
    enterfunction("DoSomethingButton12");

    // NOOP

    exitfunction("DoSomethingButton12");
}
