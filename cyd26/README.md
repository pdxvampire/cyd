# cyd13 - LVGL touch using CST820 and SD card

## Setup
In Arduino IDE turn on Serial Monitor via Tools -> Serial Monitor.

## Expected Behavior When Running The Sketch
* The display will show a button and slider that can be interacted with.
* The SD card directory listing will be printed out in the Serial Monitor. Due to driver limitations it must run before anything else and won't work after the display or touch are initialized.
* Logging will appear in the Serial Monitor.