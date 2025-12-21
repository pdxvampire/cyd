#include <array>
#include "core/lv_obj_pos.h"
#include "misc/lv_types.h"
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define LVGL_TICK_PERIOD 2
unsigned long lastLvTick = 0;

/* Draw buffer for LVGL */
static uint8_t draw_buf[SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8)];


/*
    Page 1                  Page 2
    ------                  ------

    /========\/========\    /========\/========\
    |  13,5  || 128,5  |    |  13,5  || 128,5  |
    |    1   ||    2   |    |    7   ||    8   |
    |        ||        |    |        ||        |
    \========/\========/    \========/\========/
    /========\/========\    /========\/========\
    | 13,110 || 128,110|    | 13,110 || 128,110|
    |    3   ||    4   |    |    9   ||   10   |
    |        ||        |    |        ||        |
    \========/\========/    \========/\========/
    /========\/========\    /========\/========\
    | 13,215 || 128,215|    | 13,215 || 128,215|
    |    5   ||    6   |    |   11   ||   12   |
    |        ||        |    |        ||        |
    \========/\========/    \========/\========/
*/


int curpage = 0;

// 0 index not used since customers will count buttons
// starting at 1 and therefore when looking at code
// we won't have to take into account that 1=0, 2=1, etc.
// size 13 because of that
// currently not using anything in button IDs 11 & 12
horns.assign({
    NULL,  // array index 0 not used, see above comment
    (struct Horn){ 1, 1, "A:/horn01.jpg", 13, 5 },
    (struct Horn){ 2, 1, "A:/horn02.jpg", 128, 5 },
    (struct Horn){ 3, 1, "A:/horn03.jpg", 13, 110 },
    (struct Horn){ 4, 1, "A:/horn04.jpg", 128, 110 },
    (struct Horn){ 5, 1, "A:/horn05.jpg", 13, 215 },
    (struct Horn){ 6, 1, "A:/horn06.jpg", 128, 215 },
    (struct Horn){ 7, 2, "A:/horn07.jpg", 13, 5 },
    (struct Horn){ 8, 2, "A:/horn08.jpg", 128, 5 },
    (struct Horn){ 9, 2, "A:/horn09.jpg", 13, 110 },
    (struct Horn){ 10, 2, "A:/settings.jpg", 128, 110 },
    NULL,  //(struct Horn){ 11, 2, "A:/horn11.jpg", 13, 215 },
    NULL   //(struct Horn){ 12, 2, "A:/horn12.jpg", 128, 215 },
});

void
create_image_button_from_sd(int id)
{
    enterfunction("create_image_button_from_sd");

    const char *imagepath = horns[id].name;
    lv_obj_t *imgbtnsdcard;

    // create the image button object
    switch (horns[id].page)
    {
        case 1:
            imgbtnsdcard = lv_imagebutton_create(screen1);
            break;
        case 2:
            imgbtnsdcard = lv_imagebutton_create(screen2);
            break;
    }

    // set the image sources for different states
    // load the main image from SD card, use NULL for left/right sides because we don't care about those

    lv_imagebutton_set_src(imgbtnsdcard, LV_IMAGEBUTTON_STATE_RELEASED, NULL, horns[id].name, NULL);  // horn icons

    // for testing use mona lisa when pressed
    // lv_imagebutton_set_src(imgbtnsdcard, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "A:/btn1.jpg", NULL);  // mona lisa

    // set the position based on the array defined at the top of this file
    lv_obj_set_pos(imgbtnsdcard, horns[id].xcoord, horns[id].xcoord);

    // darken the button when pressed
    static lv_style_t style_pr;
    lv_style_init(&style_pr);
    lv_style_set_img_recolor_opa(&style_pr, LV_OPA_20);
    lv_style_set_img_recolor(&style_pr, lv_color_black());
    lv_obj_add_style(imgbtnsdcard, &style_pr, LV_STATE_PRESSED);

    // add a callback function for button press event
    // add the filename as user data to identify the button in the event handler
    lv_obj_add_event_cb(imgbtnsdcard, HandleButtonClick, LV_EVENT_CLICKED, (void *)id);

    exitfunction("create_image_button_from_sd");
}
/*
void btn1_event_callback(lv_event_t *e)
{
    logit("button 1 clicked!");
    // CreateScreen2();
    //lv_screen_load(screen2);
    lv_screen_load_anim(screen2, LV_SCREEN_LOAD_ANIM_MOVE_LEFT, 200, 0, false);
    //   lv_obj_del_async(screen1);
    lv_display_flush_ready(disp);
}

void btn2_event_callback(lv_event_t *e)
{
    logit("button 2 clicked!");
    //   CreateScreen1();
    lv_screen_load_anim(screen1, LV_SCREEN_LOAD_ANIM_MOVE_RIGHT, 200, 0, false);
    lv_display_flush_ready(disp);
}
*/
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
    lv_obj_set_style_bg_color(settingsscreen, lv_color_hex(0xDDDDDD), LV_PART_MAIN);

    lv_obj_set_style_bg_color(settingsscreen, lv_palette_main(LV_PALETTE_GREEN), LV_PART_MAIN);

    label3 = lv_label_create(settingsscreen);
    lv_label_set_text(label3, "Brightness");
    lv_obj_set_size(label3, 140, 60);
    lv_obj_center(label3);

    slider = lv_slider_create(settingsscreen);
    lv_slider_set_range(slider, 10, 100);
    lv_obj_set_width(slider, 200);                                    // Width of the slider
    lv_obj_align_to(slider, label3, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);  // Position under button

    // Slider release event
    lv_obj_add_event_cb(
        slider, [](lv_event_t *e)
        {
            if (lv_event_get_code(e) == LV_EVENT_RELEASED)
            {
                lv_obj_t *slider = (lv_obj_t *)lv_event_get_target(e);  // Cast required in LVGL v9
                int val = lv_slider_get_value(slider);
                Serial.printf("🎚 Slider released, value: %d\n", val);
            }
        },
        LV_EVENT_ALL, NULL);
}

void InitializeDisplay()
{
    enterfunction("InitializeDisplay");

    // Initialise the TFT
    tft.begin();
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
    CreateScreen2();

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
    /*
    lv_style_init(&popuplabelstyle);
    lv_style_set_text_color(&popuplabelstyle, lv_palette_main(LV_PALETTE_RED));
    // Set the background color and ensure it's visible
    lv_style_set_bg_color(&popuplabelstyle, lv_color_black());
    lv_style_set_bg_opa(&popuplabelstyle, LV_OPA_COVER);

    //lv_style_set_text_letter_space(&popuplabelstyle, 5); // more space between letters
    lv_style_set_text_font(&popuplabelstyle, &lv_font_montserrat_30); // Set a larger font

    popuplabel = lv_label_create(lv_screen_active());
    //lv_obj_set_pos(popuplabel, 200,200);
    lv_obj_center(popuplabel);
    lv_obj_add_flag(popuplabel, LV_OBJ_FLAG_HIDDEN);  // Hide the object

*/

    exitfunction("InitializeDisplay");
}
