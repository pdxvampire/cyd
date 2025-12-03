LGFX_JustDisplay lcd;

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

void TestDisplayJustLGFX()
{
    enterfunction("TestDisplayJustLGFX");

    lcd.setTextColor(0xFFFF, 0x0000);
    lcd.fillScreen(TFT_RED);
    lcd.drawCentreString("Hello World", lcd.width() / 2, 20, 2);
    lcd.setSwapBytes(true);  // We need to swap the colour bytes (endianess)
    delay(1000);
    SetBrightnessHalf();
    lcd.fillScreen(TFT_GREEN);
    lcd.drawCentreString("Hello World", lcd.width() / 2, 200, 1);
    delay(1000);
    SetBrightnessFull();
    lcd.fillScreen(TFT_BLUE);
    lcd.setCursor(lcd.width() / 4, (lcd.height() / 2) - 30);
    lcd.setFont(&fonts::Font4);
    lcd.println("Hello");
    lcd.setCursor(lcd.width() / 4, lcd.height() / 2);
    lcd.println("LovyanGFX!");

    exitfunction("TestDisplayJustLGFX");
}