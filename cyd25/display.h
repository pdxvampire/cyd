//LGFX_JustDisplay lcd;
TFT_eSPI lcd = TFT_eSPI();  // Invoke custom library


//static lv_color_t buf1[240 * 10];
/* LVGL will render to this 1/10 screen sized buffer for 2 bytes/pixel */
static uint8_t buf[320 * 240 / 10 * 2];
static lv_display_t* display;


#define LVGL_TICK_PERIOD 5
unsigned long lastLvTick = 0;

const uint8_t DISPLAY_ORIENTATION_PORTRAIT = 2;

#define SCREEN_ORIENTATION USB_LEFT  // for lvgl

const uint8_t MAX_IMAGES = 5;
//String fileNames[MAX_IMAGES] = { "/panda.jpg", "/GrandPrismaticSpring_240_320_ys08_0398_P1020005.jpg" };
String fileNames[MAX_IMAGES] = { "/pic01-1.jpg", "/pic02-1.jpg", "/pic03-1.jpg", "/pic04-1.jpg", "/pic05-1.jpg" };
uint8_t imageIndex = 0;


// This next function will be called during decoding of the jpeg file to
// render each block to the TFT.  If you use a different TFT library
// you will need to adapt this function to suit.
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
    // Stop further decoding as image is running off bottom of screen
    if (y >= lcd.height()) return 0;

    // This function will clip the image block rendering automatically at the TFT boundaries
    lcd.pushImage(x, y, w, h, bitmap);

    // This might work instead if you adapt the sketch to use the Adafruit_GFX library
    // tft.drawRGBBitmap(x, y, bitmap, w, h);

    // Return 1 to decode next block
    return 1;
}


void displayImage(String imagename)
{
    Serial.printf("displayImage filename: %s\n", imagename);
    lcd.fillScreen(TFT_BLACK);
    // Get the width and height in pixels of the jpeg if you wish
    uint16_t w = 0, h = 0;
    TJpgDec.getSdJpgSize(&w, &h, imagename);
    Serial.print("Width = ");
    Serial.print(w);
    Serial.print(", height = ");
    Serial.println(h);

    // Draw the image, top left at 0,0
    TJpgDec.drawSdJpg(0, 0, imagename);

    //displayImage(fileNames[imageIndex]);
    lcd.drawCentreString("Touch Image -> next", lcd.width() / 2, 20, 2);
    lcd.drawCentreString("Touch Image -> next", lcd.width() / 2, 290, 2);
    //displayImage(fileNames[imageIndex]);
}



// LVGL flush callback
void lv_flush_cb(lv_display_t* disp, const lv_area_t* area, uint8_t* pixelmap)
{
    int16_t x;
    int16_t y;
    uint16_t w;
    uint16_t h;

    x = area->x1;
    y = area->y1;
    w = area->x2 - area->x1 + 1;
    h = area->y2 - area->y1 + 1;

    if (y >= lcd.height()) return;

    lcd.pushImage(x, y, w, h, pixelmap);

    /* Indicate that the buffer is available.
     * If DMA were used, call in the DMA complete interrupt. */
    lv_display_flush_ready(disp);
}
void my_disp_flush (lv_display_t *disp, const lv_area_t *area, uint8_t *pixelmap)
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    if (LV_COLOR_16_SWAP) {
        size_t len = lv_area_get_size( area );
        lv_draw_sw_rgb565_swap( pixelmap, len );
    }

    lcd.startWrite();
    lcd.setAddrWindow( area->x1, area->y1, w, h );
    lcd.pushColors( (uint16_t*) pixelmap, w * h, true );
    lcd.endWrite();

    lv_disp_flush_ready( disp );
}

/* // only in LGFX_JustDisplay, not TFT_eSPI
void SetBrightnessFull(void)
{
    // Set the backlight brightness in the range 0-255
    lcd.setBrightness(255);
}

void SetBrightnessHalf(void)
{
    lcd.setBrightness(128);
}
*/

void InitializeBacklight(void)
{
    enterfunction("InitializeBacklight");

    // Enable backlight (GPIO 27 must be HIGH)
    pinMode(27, OUTPUT);
    digitalWrite(27, HIGH);

    // only in LGFX_JustDisplay, not TFT_eSPI
    //SetBrightnessFull();

    exitfunction("InitializeBacklight");
}

void InitializeDisplay(void)
{
    enterfunction("InitializeDisplay");

    TurnOffOnboardLEDs();

    lcd.init();
    lcd.setRotation(DISPLAY_ORIENTATION_PORTRAIT);  // Use native portrait orientationv
    // Set the color mode as needed. (Initial value is 16)
    // 16 - Faster, but the red and blue tones are 5 bits.
    // 24 - Slower, but the gradation expression is cleaner.
    //lcd.setColorDepth(16);  // Set to 16 bits of RGB565
    ////lcd.setColorDepth(24);  // Set to 24 bits for RGB888 - Note that the actual
    // number of colors displayed may be 18 bits (RGB666)
    // depending on the display hardware.
    lcd.setTextColor(0xFFFF, 0x0000);
    lcd.fillScreen(TFT_BLACK);
    lcd.setSwapBytes(true);

    InitializeBacklight();

    // LVGL init
    lv_init();

    //display = lv_display_create(320, 240);
    
// initialize display using TFT_eSPI library
  display = lv_tft_espi_create(240, 320, buf, sizeof(buf));
  //lv_display_set_rotation(display, rotation);
  //lv_display_set_buffers(display, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);

    /* This callback will display the rendered image */
    lv_display_set_flush_cb(display, lv_flush_cb);
    //lv_display_set_flush_cb(display, my_disp_flush);

    exitfunction("InitializeDisplay");
}
