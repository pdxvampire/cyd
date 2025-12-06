#include "LGFX_JustDisplay.h"
#include <lvgl.h>
#include "logging.h"
#include "sdcard.h"

LGFX_JustDisplay lcd;

void setup()
{
  Serial.begin(115200);
  delay(2000);
  Serial.println("");


 // Enable backlight (GPIO 27 must be HIGH)
    pinMode(27, OUTPUT);
    digitalWrite(27, HIGH);


 lcd.init();
    lcd.setRotation(2);  // Use native portrait orientationv
    // Set the color mode as needed. (Initial value is 16)
    // 16 - Faster, but the red and blue tones are 5 bits.
    // 24 - Slower, but the gradation expression is cleaner.
    //lcd.setColorDepth(16);  // Set to 16 bits of RGB565
    lcd.setColorDepth(24);  // Set to 24 bits for RGB888 - Note that the actual
                            // number of colors displayed may be 18 bits (RGB666)
                            // depending on the display hardware.
// start lvgl
lv_init();

lcd.fillScreen(lcd.color888(255, 0, 0));


}
void loop()
{
    //HandleTouch();
    delay(500);  // Wait for 500 milliseconds (adjust for desired speed)
}