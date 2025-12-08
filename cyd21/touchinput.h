#include "CST820.h"
CST820 touch(33, 32, 25, 21);  // Touch: SDA, SCL, RST, INT
uint16_t rawX, rawY;

void InitializeTouch(void)
{
    // Initialize touchscreen
    touch.begin();
}

void SetupTestTouch(void)
{
    lcd.fillScreen(TFT_BLACK);
    lcd.setTextColor(TFT_YELLOW);
    lcd.setTextSize(2);
    lcd.setCursor(10, 100);
    lcd.println("Touch to draw");
}

void HandleTouch(void)
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
        Serial.printf("👉 Touch at x=%d, y=%d (raw: %d,%d)\n", x, y, rawX, rawY);

        // Draw a small circle where the user touched
        //lcd.fillCircle(x, y, 4, TFT_CYAN);

        imageIndex++;
    if (imageIndex > (MAX_IMAGES - 1)) imageIndex = 0;
    displayImage(fileNames[imageIndex]);
    }
}