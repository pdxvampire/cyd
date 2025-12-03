LGFX_JustDisplay lcd;

static lv_color_t buf1[240 * 10];
static lv_display_t* disp;

#define LVGL_TICK_PERIOD 5
unsigned long lastLvTick = 0;

void SetBrightnessFull(void)
{
    // Set the backlight brightness in the range 0-255
    lcd.setBrightness(255);
}

void SetBrightnessHalf(void)
{
    lcd.setBrightness(128);
}

void InitializeBacklight(void)
{
    enterfunction("InitializeBacklight");

    // Enable backlight (GPIO 27 must be HIGH)
    pinMode(27, OUTPUT);
    digitalWrite(27, HIGH);

    SetBrightnessFull();

    exitfunction("InitializeBacklight");
}

void InitializeDisplay(void)
{
    enterfunction("InitializeDisplay");

    TurnOffOnboardLEDs();

    lcd.init();
    lcd.setRotation(2);  // Use native portrait orientationv
    // Set the color mode as needed. (Initial value is 16)
    // 16 - Faster, but the red and blue tones are 5 bits.
    // 24 - Slower, but the gradation expression is cleaner.
    //lcd.setColorDepth(16);  // Set to 16 bits of RGB565
    lcd.setColorDepth(24);  // Set to 24 bits for RGB888 - Note that the actual
                            // number of colors displayed may be 18 bits (RGB666)
                            // depending on the display hardware.

    InitializeBacklight();

    exitfunction("InitializeDisplay");
}
