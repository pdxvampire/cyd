#include <lvgl.h>
#include <TFT_eSPI.h>  // Include the display driver library
#include <XPT2046_Touchscreen.h>

uint8_t cardType;
uint64_t cardSize;

int blinkctr = 0;
int ledPins[] = { 4, 16, 17 };

bool blinkflag = true;

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#define FONT_SIZE 2

#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];


#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

int x, y, z;

// Define display object
TFT_eSPI tft = TFT_eSPI();

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

void InitializeSerialCommunication(void)
{
    Serial.begin(115200);

    String LVGL_Arduino = String("LVGL Library Version: ") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println(LVGL_Arduino);
    delay(1000);
}

void InitializeOnboardLEDs(void)
{
    // set up onboard LED pins so we can get visual feedback that at least that much is working
    for (int p : ledPins) pinMode(p, OUTPUT);
}

void TurnOnOnboardLEDs(void)
{
    for (int p : ledPins)
    {
        Serial.printf("Turning on GPIO %d\n", p);
        digitalWrite(p, LOW);
    }
}

void TurnOffOnboardLEDs(void)
{
    for (int p : ledPins)
    {
        Serial.printf("Turning off GPIO %d\n", p);
        digitalWrite(p, HIGH);
    }
}

void BlinkOnboardLEDs(void)
{
    TurnOnOnboardLEDs();
    delay(300);
    TurnOffOnboardLEDs();
}

/* Change to your display resolution */
static const uint16_t screenWidth = 320;
static const uint16_t screenHeight = 240;

static lv_display_t* disp;

// If logging is enabled, it will inform the user about what is happening in the library
void log_print(lv_log_level_t level, const char* buf)
{
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
}

// Get the Touchscreen data
void touchscreen_read(lv_indev_t* indev, lv_indev_data_t* data)
{
    // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z)
    if (touchscreen.tirqTouched() && touchscreen.touched())
    {
        // Get Touchscreen points
        TS_Point p = touchscreen.getPoint();
        // Calibrate Touchscreen points with map function to the correct width and height
        x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
        y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
        z = p.z;

        data->state = LV_INDEV_STATE_PRESSED;

        // Set the coordinates
        data->point.x = x;
        data->point.y = y;

        // Print Touchscreen info about X, Y and Pressure (Z) on the Serial Monitor
        Serial.print("X = ");
        Serial.print(x);
        Serial.print(" | Y = ");
        Serial.print(y);
        Serial.print(" | Pressure = ");
        Serial.print(z);
        Serial.println();
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}
/* Buffer for LVGL */
static lv_color_t buf[screenWidth * 10];

void my_display_flush(lv_display_t* disp, const lv_area_t* area, uint8_t* px_map)
{
    tft.pushImage(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (uint16_t*)px_map);
}

static void event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("Clicked");
    }
    else if (code == LV_EVENT_VALUE_CHANGED)
    {
        LV_LOG_USER("Toggled");
    }
}

void TestDisplay(void)
{
    tft.begin();
    tft.setRotation(1);                      // Depending of the use-case.
    tft.setTextSize(1);                      // No size multiplier
    tft.fillScreen(TFT_BLACK);               // Fill the screen with back colour
    tft.setTextColor(TFT_GREEN, TFT_BLACK);  // Set text color to green and padding to back

    tft.drawString(" !\"#$%&'()*+,-./0123456", 0, 0, 2);  // draw top left
    tft.drawString("789:;<=>?@ABCDEFGHIJKL", 0, 16, 2);
    tft.drawString("MNOPQRSTUVWXYZ[\\]^_`", 0, 32, 2);
    tft.drawString("abcdefghijklmnopqrstuvw", 0, 48, 2);

    delay(1000);

    lv_obj_t* text_label = lv_label_create(lv_screen_active());
    lv_label_set_long_mode(text_label, LV_LABEL_LONG_WRAP);  // Breaks the long lines
    lv_label_set_text(text_label, "Hello, world!");
    lv_obj_set_width(text_label, 150);  // Set smaller width to make the lines wrap
    lv_obj_set_style_text_align(text_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(text_label, LV_ALIGN_CENTER, 0, -90);
    //
}
int btn1_count = 0;
// Callback that is triggered when btn1 is clicked
static void event_handler_btn1(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        btn1_count++;
        LV_LOG_USER("Button clicked %d%", (int)btn1_count);
    }
}

// Callback that is triggered when btn2 is clicked/toggled
static void event_handler_btn2(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = (lv_obj_t*)lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED)
    {
        LV_UNUSED(obj);
        LV_LOG_USER("Toggled %s", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "on" : "off");
    }
}

static lv_obj_t* slider_label;
// Callback that prints the current slider value on the TFT display and Serial Monitor for debugging purposes
static void slider_event_callback(lv_event_t* e)
{
    lv_obj_t* slider = (lv_obj_t*)lv_event_get_target(e);
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
    lv_label_set_text(slider_label, buf);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    LV_LOG_USER("Slider changed to %d%%", (int)lv_slider_get_value(slider));
}


void lv_create_main_gui(void)
{
    // Create a text label aligned center on top ("Hello, world!")
    lv_obj_t* text_label = lv_label_create(lv_screen_active());
    lv_label_set_long_mode(text_label, LV_LABEL_LONG_WRAP);  // Breaks the long lines
    lv_label_set_text(text_label, "Hello, world!");
    lv_obj_set_width(text_label, 150);  // Set smaller width to make the lines wrap
    lv_obj_set_style_text_align(text_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(text_label, LV_ALIGN_CENTER, 0, -90);

    lv_obj_t* btn_label;
    // Create a Button (btn1)
    lv_obj_t* btn1 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(btn1, event_handler_btn1, LV_EVENT_ALL, NULL);
    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -50);
    lv_obj_remove_flag(btn1, LV_OBJ_FLAG_PRESS_LOCK);

    btn_label = lv_label_create(btn1);
    lv_label_set_text(btn_label, "Button");
    lv_obj_center(btn_label);

    // Create a Toggle button (btn2)
    lv_obj_t* btn2 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(btn2, event_handler_btn2, LV_EVENT_ALL, NULL);
    lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 10);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_height(btn2, LV_SIZE_CONTENT);

    btn_label = lv_label_create(btn2);
    lv_label_set_text(btn_label, "Toggle");
    lv_obj_center(btn_label);

    // Create a slider aligned in the center bottom of the TFT display
    lv_obj_t* slider = lv_slider_create(lv_screen_active());
    lv_obj_align(slider, LV_ALIGN_CENTER, 0, 60);
    lv_obj_add_event_cb(slider, slider_event_callback, LV_EVENT_VALUE_CHANGED, NULL);
    lv_slider_set_range(slider, 0, 100);
    lv_obj_set_style_anim_duration(slider, 2000, 0);

    // Create a label below the slider to display the current slider value
    slider_label = lv_label_create(lv_screen_active());
    lv_label_set_text(slider_label, "0%");
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}
