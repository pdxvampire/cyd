LGFX_JustDisplay lcd;

static lv_color_t buf1[240 * 10];
static lv_display_t* disp;

#define LVGL_TICK_PERIOD 5
unsigned long lastLvTick = 0;

const uint8_t MAX_IMAGES = 5;
String fileNames[MAX_IMAGES] = { "/pic01-1.jpg", "/pic02-1.jpg", "/pic03-1.jpg", "/pic04-1.jpg", "/pic05-1.jpg" };
uint8_t imageIndex = -1;


// LVGL flush callback
void lv_flush_cb(lv_display_t* disp, const lv_area_t* area, uint8_t* color_p)
{
    lcd.pushImage(area->x1, area->y1,
                  area->x2 - area->x1 + 1,
                  area->y2 - area->y1 + 1,
                  (lgfx::rgb565_t*)color_p);
    lv_display_flush_ready(disp);
}

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

    // LVGL init
    lv_init();

    static lv_color_t buf1[240 * 10];
    static lv_display_t* disp = lv_display_create(240, 320);
    lv_display_set_flush_cb(disp, lv_flush_cb);
    lv_display_set_buffers(disp, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    exitfunction("InitializeDisplay");
}


void displayImage(String imagename) 
{
  logit("displayImage filename: %s", imagename);
  // Get the width and height in pixels of the jpeg if you wish
  //uint16_t w = 0, h = 0;
  //TJpgDec.getSdJpgSize(&w, &h, imagename);
  //Serial.print("Width = ");
  //Serial.print(w);
  //Serial.print(", height = ");
  //Serial.println(h);
  // Draw the image, top left at 0,0
  //TJpgDec.drawSdJpg(0, 0, imagename);
  lv_obj_t * wp;

    wp = lv_image_create(lv_screen_active());
    /* Assuming a File system is attached to letter 'A'
     * E.g. set LV_USE_FS_STDIO 'A' in lv_conf.h */
     const void* void_ptr = imagename.c_str();
    lv_image_set_src(wp, void_ptr);
    lv_obj_center(wp);
}
