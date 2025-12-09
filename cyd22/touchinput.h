#include "CST820.h"
#define I2C_SDA 33
#define I2C_SCL 32
#define TP_RST 25 // Touch reset pin
#define TP_INT 21 // Touch interrupt pin

CST820 touch(I2C_SDA, I2C_SCL, TP_RST, TP_INT); // Create touch instance

uint16_t rawX, rawY;
uint8_t gesture;
int startX = 0, startY = 0;
int endX = 0, endY = 0;
bool touched_old = false;
const int TOUCH_THRESHOLD = 25;  // Minimum pixels to register as a swipe


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
    bool touched_new = touch.getTouch(&rawX, &rawY, &gesture);

    // If a touch is detected, get coordinates
    if (touched_new)
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
        lcd.fillCircle(x, y, 4, TFT_CYAN);

        //    imageIndex++;
        //if (imageIndex > (MAX_IMAGES - 1)) imageIndex = 0;
        //displayImage(fileNames[imageIndex]);

        if (touched_new != touched_old)
        {
            if (touched_new)
            {
                // Touch started, record initial position
                startX = x;
                startY = y;
            }
            else
            {
                // Touch released, record end position and check for swipe
                endX = x;
                endY = y;

                int dx = endX - startX;
                int dy = endY - startY;
                int adx = abs(dx);
                int ady = abs(dy);

                if (adx > ady && adx > TOUCH_THRESHOLD)
                {
                    // Horizontal swipe
                    if (dx < 0)
                    {
                        Serial.println("Swipe Right to Left");
                        // Handle left swipe action
                    }
                    else
                    {
                        Serial.println("Swipe Left to Right");
                        // Handle right swipe action
                    }
                }
                else if (ady > adx && ady > TOUCH_THRESHOLD)
                {
                    // Vertical swipe
                    if (dy < 0)
                    {  // Check your display's coordinate system for up/down
                        Serial.println("Swipe Bottom to Top (Up)");
                        // Handle up swipe action
                    }
                    else
                    {
                        Serial.println("Swipe Top to Bottom (Down)");
                        // Handle down swipe action
                    }
                }
            }
            touched_old = touched_new;
        }
    }
}