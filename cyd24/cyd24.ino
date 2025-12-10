#include <lvgl.h>
#include <TFT_eSPI.h>
#include <spi_lcd_read.h>

TFT_eSPI tft = TFT_eSPI();
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// capacitive touch
#include <Wire.h>
#define I2C_SDA         33
#define I2C_SCL         32
#define TP_RST          25
#define TP_INT          21
#define I2C_ADDR_CST820 0x15

SPIClass touchSPI = SPIClass(VSPI);

// spi_lcd_read
SPIClass displaySPI = SPIClass(HSPI);
SPI_LCD_READ slr;

static void touch_read(lv_indev_t * indev, lv_indev_data_t * data) {

  int x, y;

  lv_disp_t * display = lv_disp_get_default();

 uint8_t touchdata[5];
    Wire.begin(I2C_SDA, I2C_SCL);
    Wire.beginTransmission(I2C_ADDR_CST820);
    Wire.write(0x02);
    Wire.endTransmission(false);
    Wire.requestFrom(I2C_ADDR_CST820, 5);
    for (int i = 0; i < 5; i++) {
      touchdata[i] = Wire.read();
    }
    Wire.end();

    if (touchdata[0] == 0 || touchdata[0] == 0xFF) {
      data->state = LV_INDEV_STATE_RELEASED;
      return;
    }
    x = ((touchdata[1] & 0x0f) << 8) | touchdata[2];
    y = ((touchdata[3] & 0x0f) << 8) | touchdata[4];

// Correct for orientation.
  // (Mostly done by LVGL, it just has the axes inverted in landscape somehow.)
  lv_display_rotation_t rotation = lv_display_get_rotation(display);
  if (rotation == LV_DISPLAY_ROTATION_90 || rotation == LV_DISPLAY_ROTATION_270) {
    x = SCREEN_WIDTH - x;
    y = SCREEN_HEIGHT - y;
  }

  data->point.x = x;
  data->point.y = y;
  data->state = LV_INDEV_STATE_PRESSED;

   Serial.printf("Processed: x=%i, y=%i\n", x, y);

}



void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
delay(2000);
Serial.println("1");
pinMode(27, OUTPUT);
Serial.println("2");
tft.begin();
Serial.println("3");
tft.fillScreen(0x0000);  //backfill black
Serial.println("4");
lv_init();
Serial.println("5");
lv_disp_t * display = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
Serial.println("6");
lv_display_set_rotation(display, LV_DISPLAY_ROTATION_90);
Serial.println("7");
lv_display_get_driver_data(display);
Serial.println("8");
 lv_indev_t * indev = lv_indev_create();
 Serial.println("9");
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    Serial.println("10");
    // Set the callback function to read Touchscreen input
    lv_indev_set_read_cb(indev, touch_read);
    Serial.println("11");

/*Change the active screen's background color*/
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);
Serial.println("12");
    /*Create a white label, set its text and align it to the center*/
    lv_obj_t * label = lv_label_create(lv_screen_active());
    Serial.println("13");
    lv_label_set_text(label, "Hello world");
    Serial.println("14");
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
    Serial.println("15");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
Serial.println("16");
tft.fillScreen(0xFF00FF);
Serial.println("17");
}

void loop() {
  // put your main code here, to run repeatedly:
// lvgl needs this to be called in a loop to run the interface
  lv_task_handler();

}
