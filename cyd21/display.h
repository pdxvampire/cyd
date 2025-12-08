const uint8_t DISPLAY_ORIENTATION_PORTRAIT = 2;

const uint8_t MAX_IMAGES = 5;
//String fileNames[MAX_IMAGES] = { "/panda.jpg", "/GrandPrismaticSpring_240_320_ys08_0398_P1020005.jpg" };
String fileNames[MAX_IMAGES] = { "/pic01-1.jpg", "/pic02-1.jpg", "/pic03-1.jpg", "/pic04-1.jpg", "/pic05-1.jpg" };
uint8_t imageIndex = 0;


// This next function will be called during decoding of the jpeg file to
// render each block to the TFT.  If you use a different TFT library
// you will need to adapt this function to suit.
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
  // Stop further decoding as image is running off bottom of screen
  if (y >= lcd.height()) return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
  lcd.pushImage(x, y, w, h, bitmap);

  // This might work instead if you adapt the sketch to use the Adafruit_GFX library
  // tft.drawRGBBitmap(x, y, bitmap, w, h);

  // Return 1 to decode next block
  return 1;
}


void displayImage(String imagename) {
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
