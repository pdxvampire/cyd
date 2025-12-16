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

void setup()
{
    InitializeSerialCommunication("SKETCH CYD25");
    InitializeDisplay();
    sdcard_setup();
    InitializeTouch();

    // Register print function for LVGL debugging
    lv_log_register_print_cb(log_print);

    // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
    TJpgDec.setJpgScale(1);

    // The decoder must be given the exact name of the rendering function above
    TJpgDec.setCallback(tft_output);

    lcd.drawCentreString("Touch Image -> next", lcd.width() / 2, 20, 2);
    lcd.drawCentreString("Touch Image -> next", lcd.width() / 2, 290, 2);

    displayImage(fileNames[imageIndex]);
}

void loop()
{
    // put your main code here, to run repeatedly:
    //lv_task_handler();

    HandleTouch();
    delay(5);
}
