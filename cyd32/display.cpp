#include "core/lv_obj_pos.h"
#include <Arduino.h>  // Automatically included in .ino files
#include <vector>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include "logging.h"
#include "layout.h"
#include "display.h"
#include "uicallbacks.h"
#include "settings.h"
#include "theme.h"

unsigned long lastLvTick = 0;

lv_display_t *disp;

void hide_object_timer_cb(lv_timer_t *timer)
{
    enterfunction("hide_object_timer_cb");

    lv_obj_t *obj = (lv_obj_t *)timer->user_data;
    if (obj != NULL)
    {
        logit("hide the object");
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);  // Hide the object

        //lv_obj_set_hidden(slider, true);
        logit("delete the timer");
        lv_timer_del(timer);  // Optional: delete the timer after it runs once
    }
    else
    {
        logit("NOOP, object is NULL");
    }

    exitfunction("hide_object_timer_cb");
}

void ShowPopupLabelBriefly(const char *msg)
{
    enterfunction("ShowPopupLabelBriefly");

    logit("add style to popuplable");
    lv_obj_add_style(popuplabel, &popuplabelstyle, 0);

    logit("set label text to '%s'", msg);
    lv_label_set_text(popuplabel, msg);

    logit("center popuplable");
    lv_obj_align(popuplabel, LV_ALIGN_CENTER, 0, 0);

    logit("unhide popuplable");
    lv_obj_clear_flag(popuplabel, LV_OBJ_FLAG_HIDDEN);

    logit("set popuplable parent");
    lv_obj_set_parent(popuplabel, lv_screen_active());

    logit("move popuplable to foreground");
    lv_obj_move_foreground(popuplabel);

    // This creates a timer that runs the callback after 3000 milliseconds (3 seconds).
    logit("add timer to popuplable");
    lv_timer_create(hide_object_timer_cb, 1000, popuplabel);

    exitfunction("ShowPopupLabelBriefly");
}

void create_image_button_from_sd(int id)
{
    enterfunction("create_image_button_from_sd");
    logit("Creating button %d", id);

    Horn horn;
    if (darkmode)
    {
        horn = darkhorns[id];
    }
    else
    {
        horn = lighthorns[id];
    }

    const char *imagepath = horn.name;
    lv_obj_t *imgbtnsdcard;
    logit("Image path:  %s", imagepath);
    logit("Image page:  %d", horn.page);

    // create the image button object
    switch (horn.page)
    {
        case 1:
            imgbtnsdcard = lv_imagebutton_create(screen1);
            logit("Created on screen 1");
            break;
        case 2:
            imgbtnsdcard = lv_imagebutton_create(screen2);
            logit("Created on screen 2");
            break;
    }

    // set the image sources for different states
    // load the main image from SD card, use NULL for left/right sides because we don't care about those
    logit("Set image to '%s'", horn.name);
    lv_imagebutton_set_src(imgbtnsdcard, LV_IMAGEBUTTON_STATE_RELEASED, NULL, imagepath, NULL);  // horn icons

    // for testing use mona lisa when pressed
    // lv_imagebutton_set_src(imgbtnsdcard, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "A:/btn1.jpg", NULL);  // mona lisa

    // set the position based on the array defined at the top of this file
    lv_obj_set_pos(imgbtnsdcard, horn.xcoord, horn.ycoord);
    logit("Position set to %d,%d", horn.xcoord, horn.ycoord);

    // darken the button when pressed
    lv_style_init(&style_pr);
    lv_style_set_img_recolor_opa(&style_pr, LV_OPA_50);
    lv_style_set_img_recolor(&style_pr, lv_color_black());
    lv_obj_add_style(imgbtnsdcard, &style_pr, LV_STATE_PRESSED);
    logit("Pressed style added.");

    // add a callback function for button press event
    // add the filename as user data to identify the button in the event handler
    lv_obj_add_event_cb(imgbtnsdcard, HandleButtonClick, LV_EVENT_CLICKED, (void *)id);
    logit("Event callback added.");

    exitfunction("create_image_button_from_sd");
}

void CreateScreen1()
{
    enterfunction("CreateScreen1");

    screen1 = lv_obj_create(NULL);
    if (darkmode)
    {
        lv_obj_set_style_bg_color(screen1, lv_color_black(), LV_PART_MAIN);
    }
    else
    {
        lv_obj_set_style_bg_color(screen1, lv_color_white(), LV_PART_MAIN);
    }
    logit("add gesture event handler to screen1");
    lv_obj_add_event_cb(screen1, HandleGesture, LV_EVENT_GESTURE, NULL);
    logit("back from add gesture handler");

    for (int x = 1; x <= 6; x++)
    {
        create_image_button_from_sd(x);
    }
    lv_obj_set_style_anim_duration(screen1, 30, LV_PART_MAIN);
    exitfunction("CreateScreen1");
}

void CreateScreen2()
{
    enterfunction("CreateScreen2");

    screen2 = lv_obj_create(NULL);
    if (darkmode)
    {
        lv_obj_set_style_bg_color(screen2, lv_color_black(), LV_PART_MAIN);
    }
    else
    {
        lv_obj_set_style_bg_color(screen2, lv_color_white(), LV_PART_MAIN);
    }

    logit("add gesture event handler to screen1");
    lv_obj_add_event_cb(screen2, HandleGesture, LV_EVENT_GESTURE, NULL);
    logit("back from add gesture handler");

    for (int x = 7; x <= 10; x++)
    {
        create_image_button_from_sd(x);
    }

    exitfunction("CreateScreen2");
}

void CreateSettingsScreen()
{
    enterfunction("CreateSettingsScreen");

    logit("create settingsscreen");
    settingsscreen = lv_obj_create(NULL);

    CreateMainContainer();
    CreateTitleBar();
    CreateBrightness();
    CreateDarkMode();

    if (darkmode)
    {
        ApplyThemeToSettingsScreen(true);
    }
    else
    {
        ApplyThemeToSettingsScreen(false);
    }

    exitfunction("CreateSettingsScreen");
}

void InitializeDisplay()
{
    enterfunction("InitializeDisplay");

    // Initialise the TFT
    tft.begin();

    // Clear TFT screen
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.fillScreen(TFT_BLACK);
    // Example: fuschia
    // uint16_t fuschia = tft.color565(255, 0, 255);
    //tft.fillScreen(fuschia);

    // Initialize LVGL
    lv_init();

    // Register print function for LVGL debugging
#if LV_USE_LOG != 0
    lv_log_register_print_cb(log_print);
#endif

    // register LVGL display using the built-in TFT_eSPI helper
    disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));

    pinMode(TFT_BL, TFT_BACKLIGHT_ON);  // defined in User_Setup.h

    logit("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ analogwrite: %d", brightness);
    analogWrite(TFT_BL, brightness);  // backlight pin is 27, range is 0..255

    // set display rotation for both tft and LVGL to match
    tft.setRotation(0);
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_180);

    CreateScreen1();
    CreateScreen2();
    CreateSettingsScreen();

    logit("load screen1");
    lv_scr_load(screen1);
    logit("back from load screen1");

    // fill active screen with amber, useful for seeing image placement
    // for other predefines see https://docs.lvgl.io/8.0/overview/color.html
    // lv_obj_set_style_bg_color(lv_screen_active(), lv_palette_main(LV_PALETTE_AMBER), LV_PART_MAIN);

    logit("initialize popuplabel");
    lv_style_init(&popuplabelstyle);
    lv_style_set_text_color(&popuplabelstyle, lv_palette_main(LV_PALETTE_RED));
    // Set the background color and ensure it's visible
    lv_style_set_bg_color(&popuplabelstyle, lv_color_black());
    lv_style_set_bg_opa(&popuplabelstyle, LV_OPA_COVER);

    //lv_style_set_text_letter_space(&popuplabelstyle, 5); // more space between letters
    lv_style_set_text_font(&popuplabelstyle, &lv_font_montserrat_30);  // Set a larger font

    popuplabel = lv_label_create(lv_screen_active());
    //lv_obj_set_pos(popuplabel, 200,200);
    lv_obj_center(popuplabel);
    lv_obj_add_flag(popuplabel, LV_OBJ_FLAG_HIDDEN);  // Hide the object

    exitfunction("InitializeDisplay");
}
