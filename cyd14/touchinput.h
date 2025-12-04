CST820 touch(33, 32, 25, 21);  // Touch: SDA, SCL, RST, INT
uint16_t rawX, rawY;

// Button event callback
void HandleButtonClick(lv_event_t* e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED)
    {
        logit("✅ Button Clicked!");
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

void SetupTestTouch(void)
{
    /*
    lcd.fillScreen(TFT_BLACK);
    lcd.setTextColor(TFT_YELLOW);
    lcd.setTextSize(2);
    lcd.setCursor(10, 100);
    lcd.println("Touch to draw");
    */

    // Set background color (light gray)
    lv_obj_set_style_bg_color(lv_screen_active(),
                              lv_color_hex(0xDDDDDD), LV_PART_MAIN);

    // Create centered button with label
    lv_obj_t* btn = lv_button_create(lv_screen_active());
    lv_obj_center(btn);
    lv_obj_add_event_cb(btn, HandleButtonClick, LV_EVENT_ALL, NULL);

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, "Hello LVGL Touch");
    lv_obj_center(label);

    // Create slider below the button
    lv_obj_t* slider = lv_slider_create(lv_screen_active());
    lv_slider_set_range(slider, 0, 100);
    lv_obj_set_width(slider, 200);                                 // Width of the slider
    lv_obj_align_to(slider, btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);  // Position under button

    // Slider release event
    lv_obj_add_event_cb(
        slider, [](lv_event_t* e)
        {
            if (lv_event_get_code(e) == LV_EVENT_RELEASED)
            {
                lv_obj_t* slider = (lv_obj_t*)lv_event_get_target(e);  // Cast required in LVGL v9
                int val = lv_slider_get_value(slider);
                Serial.printf("🎚 Slider released, value: %d\n", val);
            }
        },
        LV_EVENT_ALL, NULL);
}

void HandleTouchBasic(void)
{
    // If a touch is detected, get coordinates
    if (touch.getTouch(&rawX, &rawY))
    {
        // Map raw touchscreen coordinates to screen orientation
        //  uint16_t x = rawY;        // Y becomes X (landscape)
        //   uint16_t y = 240 - rawX;  // Flip vertical axis
        uint16_t x = 240 - rawX;
        //data->point.y = 240 - tmp - 1;
        uint16_t y = 320 - rawY;
        // Debug output - I was unable to get Gestures Working so Just X, Y Touches for now.
        logit("👉 Touch at x=%d, y=%d (raw: %d,%d)", x, y, rawX, rawY);

        // Draw a small circle where the user touched
        lcd.fillCircle(x, y, 4, TFT_CYAN);
    }
}