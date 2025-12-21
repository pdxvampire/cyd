void InitializeSerialCommunication(const char* title)
{
    Serial.begin(115200);

    // Wait for the serial port to connect so the Serial Monitor printouts work consistently
    // This may not be necessary on Windows or Linux but with my Macbook Air M3 (2024) it is.
    delay(2000);

    logit("");  // insert a newline after the random garbage that gets printed on connection/powerup

    logheader(title);
    loglevel++;  // would normally be part of the call to enterfunction for InitializeSerialCommunication()

    logit("####### Done initializing serial communication. ################################");
    exitfunction("InitializeSerialCommunication");
}

void ShowPopupLabelBriefly(const char* msg)
{
    lv_obj_add_style(popuplabel, &popuplabelstyle, 0);
    lv_label_set_text(popuplabel, msg);
    lv_obj_align(popuplabel, LV_ALIGN_CENTER, 0, 0);
    lv_obj_clear_flag(popuplabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_parent(popuplabel, lv_screen_active());
    lv_obj_move_foreground(popuplabel);

    // This creates a timer that runs the callback after 3000 milliseconds (3 seconds).
    lv_timer_create(hide_object_timer_cb, 1050, popuplabel);
}