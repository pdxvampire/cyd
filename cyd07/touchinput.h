// Touch input for LVGL
void touchpad_read_cb(lv_indev_t* indev, lv_indev_data_t* data)
{
    uint16_t rawX, rawY, tmp;
    if (touch.getTouch(&rawX, &rawY))
    {
        data->state = LV_INDEV_STATE_PRESSED;
        // data->point.x = rawY;
        // data->point.y = 240 - rawX;

        tmp = rawX;
        //data->point.x = rawY;
        data->point.x = 240 - rawX - 1;
        //data->point.y = 240 - tmp - 1;
        data->point.y = 320 - rawY - 1;

        // top left is 0,0, raw is 240,320
        // bottom left is 0,320, raw is 240,0
        // top right is 240,0, raw is 0,320
        // bottom right is 240,320, raw is 0,0
        //touchX = 240 - rawX;
        //touchY = 320 - rawY;

        Serial.printf("🖐 LVGL Touch at (%d, %d) | Raw: (%d, %d)\n", data->point.x, data->point.y, rawX, rawY);
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}