#define LVGL_TICK_PERIOD 5
unsigned long lastLvTick = 0;
LGFX_JustDisplay tft;

CST820 touch(33, 32, 25, 21);  // SDA, SCL, RST, INT

const uint8_t MAX_IMAGES = 2;
//String fileNames[MAX_IMAGES] = { "/panda.jpg", "/GrandPrismaticSpring_240_320_ys08_0398_P1020005.jpg" };
String fileNames[MAX_IMAGES] = { "/btn1.jpg", "/btn1.jpg" };
uint8_t imageIndex = 0;

//const char* cities[3] = { "New York", "Los Angeles", "Chicago" };
//char* buttonnames[10];  // not const because the function we use it in won't accept anything but 'void *'
char buttonnames[10][70];

const char *pressed = "A:/Users/jordysimpson/Desktop/code/lv_port_pc_vscode/images/48.png";

// LVGL flush callback
void lv_flush_cb(lv_display_t* disp, const lv_area_t* area, uint8_t* color_p)
{
    tft.pushImage(area->x1, area->y1,
                  area->x2 - area->x1 + 1,
                  area->y2 - area->y1 + 1,
                  (lgfx::rgb565_t*)color_p);
    lv_display_flush_ready(disp);
}

// from https:  //randomnerdtutorials.com/esp32-microsd-card-arduino/
void listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if (!root)
    {
        Serial.println("Failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if (levels)
            {
                listDir(fs, file.name(), levels - 1);
            }
        }
        else
        {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}
