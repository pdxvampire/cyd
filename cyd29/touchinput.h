#include "CST820.h"
CST820 touch(33, 32, 25, 21);  // Touch: SDA, SCL, RST, INT
uint16_t rawX, rawY;

// Button event callback
void HandleButtonClick(lv_event_t* e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        logit("✅ Button Clicked!");

        //imageIndex++;
        //       if (imageIndex > (MAX_IMAGES - 1)) imageIndex = 0;
        //       displayImage(fileNames[imageIndex]);

lv_obj_t * btn = (lv_obj_t*)lv_event_get_target(e); // Get the object that triggered the event
// Now 'btn' points to the specific button that was clicked
        // You can use 'btn' to identify the button
        lv_obj_t * user_obj = (lv_obj_t*) lv_event_get_user_data(e);
const char* button_id = (const char*) user_obj;

logit("button id:  %s", button_id);

   /*
    

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_text_letter_space(&style, 5);

    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "Hello LVGL with\nimages and styles!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 100);
    lv_obj_align_to(label, imgarr, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);
*/
//lv_style_set_text_font(&my_style, LV_STATE_DEFAULT, &lv_font_montserrat_28);  /*Set a larger font*/
    }
}

// Touch input for LVGL
void HandleTouch(lv_indev_t* indev, lv_indev_data_t* data)
{
    uint16_t rawX, rawY;
    if (touch.getTouch(&rawX, &rawY))
    {
        data->state = LV_INDEV_STATE_PRESSED;
        //data->point.x = rawY;
        //data->point.y = 240 - rawX;
        //data->point.x = rawY;
        data->point.x = 240 - rawX - 1;
        //data->point.y = 240 - tmp - 1;
        data->point.y = 320 - rawY - 1;

        logit("🖐 LVGL Touch at (%d, %d) | Raw: (%d, %d)",
              data->point.x, data->point.y, rawX, rawY);
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void InitializeTouch(void)
{
    // Initialize touchscreen
    touch.begin();
    logit("🔍 Touch Chip ID: 0x%02X", touch.readChipID());

    // LVGL Input device (touch)
    lv_indev_t* indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, HandleTouch);
}