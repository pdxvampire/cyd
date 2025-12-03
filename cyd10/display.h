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

    pinMode(27, OUTPUT);
    digitalWrite(27, HIGH);

    SetBrightnessFull();
    exitfunction("InitializeBacklight");
}

// LVGL flush callback
void lv_flush_cb(lv_display_t* disp, const lv_area_t* area, uint8_t* color_p)
{
    lcd.pushImage(area->x1, area->y1,
                  area->x2 - area->x1 + 1,
                  area->y2 - area->y1 + 1,
                  (lgfx::rgb565_t*)color_p);
    lv_display_flush_ready(disp);
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

    // LVGL init
    lv_init();

    disp = lv_display_create(240, 320);
    lv_display_set_flush_cb(disp, lv_flush_cb);
    lv_display_set_buffers(disp, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

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

void TestDisplayLVGL(void)
{
    enterfunction("TestDisplayLVGL");

    // Set background color (light gray)
    lv_obj_set_style_bg_color(lv_screen_active(),
                              lv_color_hex(0xDDDDDD), LV_PART_MAIN);

    // Create centered button with label
    lv_obj_t* btn = lv_button_create(lv_screen_active());
    lv_obj_center(btn);
    //lv_obj_add_event_cb(btn, on_button_event, LV_EVENT_ALL, NULL);

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, "Hello LVGL!");
    lv_obj_center(label);

    exitfunction("TestDisplayLVGL");
}