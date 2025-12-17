#include <lvgl.h>
#include <TJpg_Decoder.h>
#include <TFT_eSPI.h>
#include "logging.h"
//#include "LGFX_JustDisplay.h"
#include "leds.h"
#include "sdcard.h"
#include "display.h"
#include "touchinput.h"
#include "code.h"

// If LVGL logging is enabled, it will inform the user about what is happening in the library
void log_print(lv_log_level_t level, const char* buf)
{
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
}

void HandleButtonClick(lv_event_t* e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        logit("✅ Button Clicked!");
        listDir(SD, "/", 0);
    }
}

void setup()
{
    InitializeSerialCommunication("SKETCH CYD25");
    InitializeDisplay();
    sdcard_setup();
    InitializeTouch();

    // Register print function for LVGL debugging
    lv_log_register_print_cb(log_print);


logit("xxxxxxxxxxxx");
File jpegFile = SD.open("/btn1.jpg", FILE_READ);  // or, file handle reference for SD library
if (!jpegFile)
    {
        Serial.print("ERROR: File \"");
        Serial.print("/btn1.jpg");
        Serial.println("\" not found!");
        return;
    }
jpegFile.close();
logit("xxxxxxxxxxxx");




    // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
    TJpgDec.setJpgScale(1);

    // The decoder must be given the exact name of the rendering function above
    TJpgDec.setCallback(tft_output);

    lcd.drawCentreString("Touch Image -> next", lcd.width() / 2, 20, 2);
    lcd.drawCentreString("Touch Image -> next", lcd.width() / 2, 290, 2);

 lv_obj_t* btn = lv_button_create(lv_screen_active());
    lv_obj_center(btn);
    lv_obj_add_event_cb(btn, HandleButtonClick, LV_EVENT_ALL, NULL);

    //displayImage(fileNames[imageIndex]);

exitfunction("setup");
}

void loop()
{
     if (millis() - lastLvTick > LVGL_TICK_PERIOD)
    {
        lv_tick_inc(LVGL_TICK_PERIOD);  // tell LVGL how much time has passed
        lastLvTick = millis();
    }
    lv_task_handler();

    HandleTouch();
    delay(5);
}
