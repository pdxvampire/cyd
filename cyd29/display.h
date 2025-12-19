#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define LVGL_TICK_PERIOD 5
unsigned long lastLvTick = 0;

/* Draw buffer for LVGL */
static uint8_t draw_buf[SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8)];

// main display object for LVGL
lv_display_t *disp;

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
int curimg = 0;
int arrxpos[12] = { 10, 10, 10, 120, 120, 120, 10, 10, 10, 120, 120, 120 };
int arrypos[12] = { 0, 110, 220, 0, 110, 220, 0, 110, 220, 0, 110, 220 };
const uint8_t NUMIMGS = 10;
const char * filenames[NUMIMGS] = { "A:/horn01.jpg", "A:/horn02.jpg", "/horn03.jpg", "/horn04.jpg", "/horn05.jpg", "/horn06.jpg", "/horn07.jpg", "/horn08.jpg", "/horn09.jpg", "/settings.jpg" };

void create_image_button_from_sd(int imgidx)
{
    enterfunction("create_image_button_from_sd");
    // Time recorded for test purposes
    uint32_t t = millis();

    const char* imagepath = filenames[imgidx];

    // Test to make sure we can read the image.
    File jpegFile = SD.open(imagepath, FILE_READ);  // or, file handle reference for SD library
    if (!jpegFile)
    {
        logit("ERROR: File \"%s\" not found!", imagepath);
        return;
    }
    jpegFile.close();

    // create the image button object and align it
    lv_obj_t* imgbtnsdcard = lv_imagebutton_create(lv_screen_active());
lv_image_set_src(imgbtnsdcard, "A:/horn09.jpg");
    //lv_image_set_src(imgbtnsdcard, imagepath);

lv_obj_center(imgbtnsdcard);
    //lv_obj_set_pos(imgbtnsdcard, arrxpos[imgidx], arrypos[imgidx]);

    // darken the button when pressed
    static lv_style_t style_pr;
    lv_style_init(&style_pr);
    lv_style_set_img_recolor_opa(&style_pr, LV_OPA_50);
    lv_style_set_img_recolor(&style_pr, lv_color_black());
    lv_obj_add_style(imgbtnsdcard, &style_pr, LV_STATE_PRESSED);

    // add a callback function for button press event
    // add the filename as user data to identify the button in the event handler
    lv_obj_add_event_cb(imgbtnsdcard, HandleButtonClick, LV_EVENT_CLICKED, (void*)filenames[imgidx]);

    // How much time did rendering take
    t = millis() - t;
    logit("Rendered in %d ms.", t);

    exitfunction("create_image_button_from_sd");
}