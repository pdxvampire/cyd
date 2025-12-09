const uint8_t DISPLAY_ORIENTATION_PORTRAIT = 2;

const uint8_t MAX_IMAGES = 10;
//String fileNames[MAX_IMAGES] = { "/panda.jpg", "/GrandPrismaticSpring_240_320_ys08_0398_P1020005.jpg" };
String fileNames[MAX_IMAGES] = { "/horn01.jpg", "/horn02.jpg", "/horn03.jpg", "/horn04.jpg", "/horn05.jpg", "/horn06.jpg", "/horn07.jpg", "/horn08.jpg", "/horn09.jpg", "/settings.jpg" };
uint8_t imageIndex = 0;


// This next function will be called during decoding of the jpeg file to
// render each block to the TFT.  If you use a different TFT library
// you will need to adapt this function to suit.
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
  // Stop further decoding as image is running off bottom of screen
  if (y >= lcd.height()) return 0;
/*
TFT_eSprite spr = TFT_eSprite(&lcd); // Create a sprite object
int crop_width = 50;
int crop_height = 50;
spr.createSprite(crop_width, crop_height);
// Assuming 'master_image_data' is a C array of a 100x100 image
// To crop the area starting at (20, 30) with size 50x50:
int src_x = 20;
int src_y = 30;
int master_image_width = 240;
int master_image_height = 320;

// Push to the sprite with negative offset relative to the sprite's top-left corner
spr.pushImage(-src_x, -src_y, master_image_width, master_image_height, (uint16_t *)bitmap);

int dest_x = 10;
int dest_y = 10;
spr.pushSprite(dest_x, dest_y);
spr.deleteSprite(); // Free memory
*/
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
