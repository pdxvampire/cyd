// Including this library will also include lvgl.h and TFT_eSPI.h 
#include <LVGL_CYD.h>

void setup() {
  
  // Start Serial and lvgl, set everything up for this device
  // Will also do Serial.begin(115200), lvgl.init(), set up the touch driver
  // and the lvgl timer.
  LVGL_CYD::begin(USB_LEFT);

  // Create single button in center of active screen
//  lv_obj_t * button = lv_button_create(lv_scr_act());
//  lv_obj_set_size(button, 100, 100); // Set size if using all three src parts

 // lv_obj_align(button, LV_ALIGN_CENTER, 0, 0);

  // Put text in button
 // lv_obj_t * button_label = lv_label_create(button);
 // lv_label_set_text(button_label, "Oh yeah?");

  // Set a callback to print to serial port when button is clicked.
  //   For those unfamiliar: The "[]() ->" thing is an "anonymous function". It lets
  //   you define a function in place instead pointing to one named elsewhere.
  ///lv_obj_add_event_cb(button, [](lv_event_t * e) -> void {
  //  Serial.println("Hell yeah!");
  //}, LV_EVENT_CLICKED, NULL);


    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);

    /*Create a white label, set its text and align it to the center*/
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Hello world");
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void loop() {

  // lvgl needs this to be called in a loop to run the interface
  lv_task_handler();

}