#include "CST820.h"
CST820 touch(33, 32, 25, 21);  // Touch: SDA, SCL, RST, INT
uint16_t rawX, rawY;


void HandleButtonClick2(lv_event_t* e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        logit("✅ Button2 Clicked!");
        //listDir(SD, "/", 0);
    }
}
// Button event callback
void HandleButtonClick(lv_event_t* e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        logit("✅ Button Clicked!");
        listDir(SD, "/", 0);

        //imageIndex++;
        //       if (imageIndex > (MAX_IMAGES - 1)) imageIndex = 0;
        //       displayImage(fileNames[imageIndex]);


       // lv_obj_t* wp;
       // logit("create wp");
       /// String imagename = fileNames[0];
       // wp = lv_image_create(lv_screen_active());
       // logit("get imagename as const void*");
        /* Assuming a File system is attached to letter 'A'
     * E.g. set LV_USE_FS_STDIO 'A' in lv_conf.h */
       // const void* void_ptr = imagename.c_str();
        //logit("Got: %s", void_ptr);
        //logit("image set src");
       // lv_image_set_src(wp, "/pic01-1.jpg");
       // logit("center image");
      //  lv_obj_center(wp);

    //    logit("add click handler");
        //lv_obj_t* btn = lv_button_create(lv_screen_active());
        //lv_obj_center(btn);
  //      lv_obj_add_event_cb(wp, HandleButtonClick2, LV_EVENT_ALL, NULL);

//lv_obj_t * tempBtn = lv_imgbtn_create(lv_scr_act());
  //      lv_imgbtn_set_src(tempBtn, LV_IMGBTN_STATE_RELEASED, "/pic01-1.jpg", "/pic01-1.jpg", "/pic01-1.jpg");

//    lv_obj_align(tempBtn, LV_ALIGN_CENTER, 0, 0);

   lv_obj_t * imgbtn = lv_imagebutton_create(lv_screen_active());
    lv_obj_center(imgbtn); // Center the button on the screen
lv_imagebutton_set_src(imgbtn, LV_IMGBTN_STATE_RELEASED, NULL, "A:/pic01-1.jpg", NULL);
// Set size automatically based on content
    lv_obj_set_size(imgbtn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        logit("done");
    }
}

// Touch input for LVGL
void HandleTouch(lv_indev_t* indev, lv_indev_data_t* data)
{
    uint16_t rawX, rawY;
    if (touch.getTouch(&rawX, &rawY))
    {
        data->state = LV_INDEV_STATE_PRESSED;
        //data->point.x = rawY;
        //data->point.y = 240 - rawX;
        //data->point.x = rawY;
        data->point.x = 240 - rawX - 1;
        //data->point.y = 240 - tmp - 1;
        data->point.y = 320 - rawY - 1;

        logit("🖐 LVGL Touch at (%d, %d) | Raw: (%d, %d)",
              data->point.x, data->point.y, rawX, rawY);
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void InitializeTouch(void)
{
    // Initialize touchscreen
    touch.begin();
    logit("🔍 Touch Chip ID: 0x%02X", touch.readChipID());

    // LVGL Input device (touch)
    lv_indev_t* indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, HandleTouch);
}

void SetupTestTouch(void)
{
    /*
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_YELLOW);
    tft.setTextSize(2);
    tft.setCursor(10, 100);
    tft.println("Touch to draw");
    */

    // Set background color (light gray)
    //lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0xDDDDDD), LV_PART_MAIN);
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);


    // Create centered button with label
    lv_obj_t* btn = lv_button_create(lv_screen_active());
    lv_obj_center(btn);
    lv_obj_add_event_cb(btn, HandleButtonClick, LV_EVENT_ALL, NULL);

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, "Hello LVGL Touch");
    lv_obj_center(label);

    // Create slider below the button
    lv_obj_t* slider = lv_slider_create(lv_screen_active());
    lv_slider_set_range(slider, 0, 100);
    lv_obj_set_width(slider, 200);                                 // Width of the slider
    lv_obj_align_to(slider, btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);  // Position under button

    // Slider release event
    lv_obj_add_event_cb(
        slider, [](lv_event_t* e)
        {
            if (lv_event_get_code(e) == LV_EVENT_RELEASED)
            {
                lv_obj_t* slider = (lv_obj_t*)lv_event_get_target(e);  // Cast required in LVGL v9
                int val = lv_slider_get_value(slider);
                Serial.printf("🎚 Slider released, value: %d\n", val);
            }
        },
        LV_EVENT_ALL, NULL);
}

void HandleTouchBasic(void)
{
    // If a touch is detected, get coordinates
    if (touch.getTouch(&rawX, &rawY))
    {
        // Map raw touchscreen coordinates to screen orientation
        //  uint16_t x = rawY;        // Y becomes X (landscape)
        //   uint16_t y = 240 - rawX;  // Flip vertical axis
        uint16_t x = 240 - rawX;
        //data->point.y = 240 - tmp - 1;
        uint16_t y = 320 - rawY;
        // Debug output - I was unable to get Gestures Working so Just X, Y Touches for now.
        logit("👉 Touch at x=%d, y=%d (raw: %d,%d)", x, y, rawX, rawY);

        // Draw a small circle where the user touched
        tft.fillCircle(x, y, 4, TFT_CYAN);
    }
}