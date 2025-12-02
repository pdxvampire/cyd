#define LVGL_TICK_PERIOD 5
unsigned long lastLvTick = 0;
//LGFX_JustDisplay tft;

//CST820 touch(33, 32, 25, 21);  // SDA, SCL, RST, INT

//const char* cities[3] = { "New York", "Los Angeles", "Chicago" };
//char* buttonnames[10];  // not const because the function we use it in won't accept anything but 'void *'
char buttonnames[10][70];

//const char *pressed = "A:/Users/jordysimpson/Desktop/code/lv_port_pc_vscode/images/48.png";

// LVGL flush callback
void lv_flush_cb(lv_display_t* disp, const lv_area_t* area, uint8_t* color_p)
{
    tft.pushImage(area->x1, area->y1,
                  area->x2 - area->x1 + 1,
                  area->y2 - area->y1 + 1,
                  (lgfx::rgb565_t*)color_p);
    lv_display_flush_ready(disp);
}
