#include <Arduino.h>  // Automatically included in .ino files
#include <vector>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include "logging.h"
#include "layout.h"
#include "display.h"
#include "uicallbacks.h"

extern TFT_eSPI tft;

unsigned long lastLvTick = 0;

lv_style_t popuplabelstyle;
lv_style_t style_pr;

lv_obj_t *popuplabel;
lv_obj_t *screen1;
lv_obj_t *screen2;
lv_obj_t *settingsscreen;
lv_obj_t *btn1;
lv_obj_t *btn2;
lv_obj_t *label1;
lv_obj_t *label2;
lv_obj_t *label3;
lv_obj_t *slider;
lv_obj_t *slider_label;

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
    lv_timer_create(hide_object_timer_cb, 1050, popuplabel);

    exitfunction("ShowPopupLabelBriefly");
}

void create_image_button_from_sd(int id)
{
    enterfunction("create_image_button_from_sd");
    logit("Creating button %d", id);

    const char *imagepath = horns[id].name;
    lv_obj_t *imgbtnsdcard;
    logit("Image path:  %s", imagepath);
    logit("Image page:  %d", horns[id].page);

    // create the image button object
    switch (horns[id].page)
    {
        case 1:
            imgbtnsdcard = lv_imagebutton_create(screen1);
            logit("Created on screen 1");
            break;
        case 2:
            imgbtnsdcard = lv_imagebutton_create(screen2);
            logit("Created on screen 1");
            break;
    }

    // set the image sources for different states
    // load the main image from SD card, use NULL for left/right sides because we don't care about those
    logit("Set image to '%s'", horns[id].name);
    lv_imagebutton_set_src(imgbtnsdcard, LV_IMAGEBUTTON_STATE_RELEASED, NULL, imagepath, NULL);  // horn icons

    // for testing use mona lisa when pressed
    // lv_imagebutton_set_src(imgbtnsdcard, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "A:/btn1.jpg", NULL);  // mona lisa

    // set the position based on the array defined at the top of this file
    lv_obj_set_pos(imgbtnsdcard, horns[id].xcoord, horns[id].ycoord);
    logit("Position set to %d,%d", horns[id].xcoord, horns[id].ycoord);

    // darken the button when pressed
    lv_style_init(&style_pr);
    lv_style_set_img_recolor_opa(&style_pr, LV_OPA_20);
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
    lv_obj_set_style_bg_color(screen1, lv_color_black(), LV_PART_MAIN);

    logit("add gesture event handler to screen1");
    lv_obj_add_event_cb(screen1, HandleGesture, LV_EVENT_GESTURE, NULL);
    logit("back from add gesture handler");

    for (int x = 1; x <= 6; x++)
    {
        create_image_button_from_sd(x);
    }

    exitfunction("CreateScreen1");
}

void CreateScreen2()
{
    enterfunction("CreateScreen2");

    screen2 = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen2, lv_palette_main(LV_PALETTE_AMBER), LV_PART_MAIN);

    logit("add gesture event handler to screen1");
    lv_obj_add_event_cb(screen2, HandleGesture, LV_EVENT_GESTURE, NULL);
    logit("back from add gesture handler");

    for (int x = 7; x <= 12; x++)
    {
        create_image_button_from_sd(x);
    }

    exitfunction("CreateScreen2");
}

void ShowSettingsScreen()
{
    settingsscreen = lv_obj_create(NULL);

    // Set background color (light gray)
    //lv_obj_set_style_bg_color(settingsscreen, lv_color_hex(0xDDDDDD), LV_PART_MAIN);
    lv_obj_set_style_bg_color(settingsscreen, lv_palette_main(LV_PALETTE_GREEN), LV_PART_MAIN);

    label3 = lv_label_create(settingsscreen);
    lv_label_set_text(label3, "Brightness");
    lv_obj_set_size(label3, 140, 60);
    lv_obj_align(label3, LV_ALIGN_TOP_MID, 0, 10);

    slider = lv_slider_create(settingsscreen);
    lv_obj_set_width(slider, 180);
    lv_obj_align(slider, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(slider, HandleBrightnessSlider, LV_EVENT_ALL, NULL);
    lv_slider_set_range(slider, 10, 100);

    slider_label = lv_label_create(settingsscreen);
    lv_label_set_text(slider_label, "0");
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
}

void InitializeDisplay()
{
    enterfunction("InitializeDisplay");

    // Initialise the TFT
    tft.begin();
    pinMode(TFT_BL, TFT_BACKLIGHT_ON);  // defined in User_Setup.h

    //tft.fillScreen(0x000000); //black
    // Example: fuschia
    uint16_t fuschia = tft.color565(255, 0, 255);

    //tft.fillScreen(fuschia);

    // Initialize LVGL
    lv_init();

    // Register print function for LVGL debugging
#if LV_USE_LOG != 0
    lv_log_register_print_cb(log_print);
#endif

    // register LVGL display using the built-in TFT_eSPI helper
    disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));

    // set display rotation for both tft and LVGL to match
    tft.setRotation(2);
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_180);

    CreateScreen1();
    // CreateScreen2();

    /*
lv_memory_buffer[0] = *(lv_obj_create(NULL));
screen1 = lv_memory_buffer[0];
lv_memory_buffer[1] = *(lv_obj_create(NULL));
screen2 = lv_memory_buffer[1];
*/
    logit("load screen1");
    lv_scr_load(screen1);
    logit("back from load screen1");

    // fill active screen with amber, useful for seeing image placement
    // for other predefines see https://docs.lvgl.io/8.0/overview/color.html
    // lv_obj_set_style_bg_color(lv_screen_active(), lv_palette_main(LV_PALETTE_AMBER), LV_PART_MAIN);
    // fill active screen with black

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
