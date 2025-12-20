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
    |        ||        |    |        ||        |
    |    0   ||    3   |    |    6   ||    9   |
    |        ||        |    |        ||        |
    \========/\========/    \========/\========/
    /========\/========\    /========\/========\
    |        ||        |    |        ||        |
    |    1   ||    4   |    |    7   ||   10   |
    |        ||        |    |        ||        |
    \========/\========/    \========/\========/
    /========\/========\    /========\/========\
    |        ||        |    |        ||        |
    |    2   ||    5   |    |    8   ||   11   |
    |        ||        |    |        ||        |
    \========/\========/    \========/\========/
*/

#define NUMPAGES 2
#define NUMPAGEIMGS 6
#define NUMIMGS = NUMPAGEIMGS * NUMPAGES;
#define NUMIMAGESUSED 10

int curpage = 0;
int arrxpos[12] = { 13, 13, 13, 128, 128, 128, 13, 13, 13, 128, 128, 128 };
int arrypos[12] = {
    5,
    110,
    215,
    5,
    110,
    215,
    5,
    110,
    215,
    5,
    110,
    215,
};

// This isn't an oversight, there is room for 12 images but we only have 10.
static const char *filenames[NUMIMAGESUSED] = {
    "A:/horn01.jpg", "A:/horn02.jpg", "A:/horn03.jpg", "A:/horn04.jpg", "A:/horn05.jpg", "A:/horn07.jpg",
    "A:/horn08.jpg", "A:/horn06.jpg", "A:/horn09.jpg", "A:/settings.jpg"
};

// Image button callback function
void button_event_callback(lv_event_t *e)
{
    const char *whichone = (const char *)lv_event_get_user_data(e);
    logit("Image button '%s' clicked!", whichone);
}

void create_image_button_from_sd(int imgidx)
{
    enterfunction("create_image_button_from_sd");

    const char *imagepath = filenames[imgidx];

    // Test to make sure we can read the image.
    /*
    this needs just /foo.jpg, the lvimg needs A:/foo.jpg
    File jpegFile = SD.open(imagepath, FILE_READ);  // or, file handle reference for SD library
    if (!jpegFile)
    {
        logit("ERROR: File \"%s\" not found!", imagepath);
        return;
    }
    jpegFile.close();
    */

    // create the image button object
    lv_obj_t *imgbtnsdcard = lv_imagebutton_create(lv_screen_active());

    // set the image sources for different states
    // load the main image from SD card, use NULL for left/right sides because we don't care about those
    lv_imagebutton_set_src(imgbtnsdcard, LV_IMAGEBUTTON_STATE_RELEASED, NULL, imagepath, NULL);     // horn icons
    lv_imagebutton_set_src(imgbtnsdcard, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "A:/btn1.jpg", NULL);  // mona lisa

    // set the position based on the array defined at the top of this file
    lv_obj_set_pos(imgbtnsdcard, arrxpos[imgidx], arrypos[imgidx]);
    //lv_obj_set_pos(imgbtnsdcard, 10, 10);
    //logit("image %s would be at %d,%d", imagepath, arrxpos[imgidx], arrypos[imgidx]);

    // darken the button when pressed
    static lv_style_t style_pr;
    lv_style_init(&style_pr);
    lv_style_set_img_recolor_opa(&style_pr, LV_OPA_20);
    lv_style_set_img_recolor(&style_pr, lv_color_black());
    lv_obj_add_style(imgbtnsdcard, &style_pr, LV_STATE_PRESSED);

    // add a callback function for button press event
    // add the filename as user data to identify the button in the event handler
    lv_obj_add_event_cb(imgbtnsdcard, HandleButtonClick, LV_EVENT_CLICKED, (void *)filenames[imgidx]);

    exitfunction("create_image_button_from_sd");
}

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

void CreateScreen1()
{
    enterfunction("CreateScreen1");

    screen1 = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen1, lv_color_black(), LV_PART_MAIN);


    btn1 = lv_button_create(screen1);
    label1 = lv_label_create(btn1);
    lv_label_set_text(label1, "goto screen 2");
    lv_obj_set_size(btn1, 140, 60);
    lv_obj_center(label1);
    lv_obj_center(btn1);
    lv_obj_add_event_cb(btn1, btn1_event_callback, LV_EVENT_CLICKED, NULL);

    logit("add gesture event handler to screen1");
    lv_obj_add_event_cb(screen1, HandleGesture, LV_EVENT_GESTURE, NULL);
    logit("back from add gesture handler");

    exitfunction("CreateScreen1");
}

void CreateScreen2()
{
    enterfunction("CreateScreen2");

    screen2 = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen2, lv_palette_main(LV_PALETTE_AMBER), LV_PART_MAIN);

    btn2 = lv_button_create(screen2);
    label2 = lv_label_create(btn2);
    lv_label_set_text(label2, "goto screen 1");
    lv_obj_set_size(btn2, 140, 60);
    lv_obj_center(label2);
    lv_obj_center(btn2);
    lv_obj_add_event_cb(btn2, btn2_event_callback, LV_EVENT_CLICKED, NULL);

    logit("add gesture event handler to screen1");
    lv_obj_add_event_cb(screen2, HandleGesture, LV_EVENT_GESTURE, NULL);
    logit("back from add gesture handler");

    exitfunction("CreateScreen2");
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
