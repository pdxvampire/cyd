#include <FS.h>
//#ifdef ESP32
//#include "SPIFFS.h"  // ESP32 only
//#endif

#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library
#include <lvgl.h>

// Prevent stack overflow reboot loops.
SET_LOOP_TASK_STACK_SIZE(32 * 1024);

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

#include "logging.h"
#include "sdcard.h"
#include "touchinput.h"
#include "display.h"
#include "code.h"

// Image button callback function
void button_event_callback(lv_event_t *e)
{
    // Handle button click here
    logit("Image button clicked!");
}

void create_image_button_from_sd()
{
    enterfunction("create_image_button_from_sd");
    // Time recorded for test purposes
    uint32_t t = millis();

#if DEBUGMODE
    // Test to make sure we can read the image.
    File jpegFile = SD.open("/horn06.jpg", FILE_READ);  // or, file handle reference for SD library
    if (!jpegFile)
    {
        Serial.print("ERROR: File \"");
        Serial.print("/horn06.jpg");
        Serial.println("\" not found!");
        return;
    }
    jpegFile.close();
#endif

    // 1. Create the image button object and align it
    lv_obj_t *imgbtnsdcard = lv_imagebutton_create(lv_screen_active());
    lv_image_set_src(imgbtnsdcard, "A:/horn06.jpg");
    lv_obj_center(imgbtnsdcard);

    //  lv_obj_set_size(imgbtn, 100, 100); // Set size if using all three src parts
    //


    // 2. Set the image sources for different states
    lv_imagebutton_set_src(imgbtnsdcard, LV_IMAGEBUTTON_STATE_RELEASED, NULL, "A:/horn07.jpg", NULL);
    lv_imagebutton_set_src(imgbtnsdcard, LV_IMAGEBUTTON_STATE_PRESSED, NULL, "A:/horn08.jpg", NULL);
    // ... set for other states like DISABLED, CHECKED, etc.


    // 3. Optional: Add a callback function for button press event
    lv_obj_add_event_cb(imgbtnsdcard, button_event_callback, LV_EVENT_CLICKED, NULL);

    // How much time did rendering take
    t = millis() - t;
    logit("Rendered in %d ms.", t);

    exitfunction("create_image_button_from_sd");
}

void setup()
{
    InitializeSerialCommunication("SKETCH CYD29");

    sdcard_setup();

    lv_init();
    // Register print function for LVGL debugging
#if LV_USE_LOG != 0
    lv_log_register_print_cb(log_print);
#endif

    // Initialise the TFT
    tft.begin();

    /* 1. Register display using the built-in TFT_eSPI helper */
    disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));

    /* 2. Optional: Set display rotation */
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_0);

    InitializeTouch();

    create_image_button_from_sd();


    /*
    

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_text_letter_space(&style, 5);

    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "Hello LVGL with\nimages and styles!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 100);
    lv_obj_align_to(label, imgarr, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);
*/
}

void loop()
{
    //lv_display_flush_ready(disp);
    lv_timer_handler();
    lv_tick_inc(5);

    delay(5);
}
