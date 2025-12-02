#include <TFT_eSPI.h>
#include "code.h"

void setup()
{
    InitializeSerialCommunication();
    InitializeOnboardLEDs();

    // Start LVGL
    lv_init();
    // Register print function for debugging
    lv_log_register_print_cb(log_print);

    touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touchscreen.begin(touchscreenSPI);
    touchscreen.setRotation(1);

    disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);

    lv_indev_t* indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, touchscreen_read);

    lv_create_main_gui();
    //    TestDisplay();
}

void loop()
{
    //lv_timer_handler();  // Let LVGL do its internal processing
    //delay(5);
    lv_task_handler();  // let the GUI do its work
    lv_tick_inc(5);     // tell LVGL how much time has passed
    delay(5);           // let this time pass
    if (blinkflag)
    {
        BlinkOnboardLEDs();
        blinkctr++;

        if (blinkctr >= 5)
        {
            blinkflag = false;
        }
        delay(300);
    }
}