# <div align="center">$${\color{lime}Cheap \space Yellow \space Display}$$</div>

**PRO TIP:**  IF YOU RUN INTO SOMETHING FUNKY LIKE A SKETCH THAT WORKED BEFORE BUT DOESN'T NOW AND YOU DIDN'T CHANGE ANYTHING THAT YOU CAN RECALL, CHECK THAT NOTHING CHANGED FROM WORKING ON A DIFFERENT SKETCH, SUCH AS IN YOUR LIBRARIES, _LV\_CONF.H_, AND _USER\_SETUP.H_.  IF NOTHING HAS CHANGED, CLOSE OUT OF ARDUINO IDE AND CLEAR THE CACHE DIRECTORY.

**NOTE:**  I ALWAYS ENABLE THE SERIAL MONITOR (_TOOLS->SERIAL MONITOR_) AND LOG TO IT SO IF A SKETCH COMPILES AND UPLOADS BUT APPEARS TO DO NOTHING, CHECK
THE SERIAL MONITOR FOR OUTPUT THERE.

## $${\color{yellow}cyd01}$$
Basic framework to test the board, includes pretty logging in Serial Monitor, suitable for using as a template for future projects. Just blinks the onboard LEDs a few times and writes to the log.
**$${\color{green}WORKS}$$**

## $${\color{yellow}cyd02 - cyd06}$$
Don't use, only saving JIC and will be deleted once I have the rest of the samples cleaned up and checked in.
***$${\color{red}Does not work.}$$***

## $${\color{yellow}cyd07}$$
Bunch of code jumbled together.  Not left in a working state because I realized I needed desperately to get things into source control after losing a "it all works" piece of code when I lost power during a save and it zeroed out the file.  This will get sliced and diced into further small modules that each work, then eventually all put back into one sketch.
***$${\color{red}Does not work.}$$***

## $${\color{yellow}cyd08}$$
SD card - read the contents and display in Serial Monitor. **USED TO WORK, SOMETHING CHANGED IN THE LIBRARIES AND I WASN'T TRACKING THEM AT THIS POINT.**
***$${\color{red}Does not work.}$$***

## $${\color{yellow}cyd09}$$
turn on the display using LovyanGFX (just display, no interaction)
**$${\color{green}WORKS}$$**

## $${\color{yellow}cyd10}$$
turn on the display using LVGL on top of LovyanGFX (just display, no interaction)
**$${\color{green}WORKS}$$**

## $${\color{yellow}cyd11}$$
basic touch using CST820 and LGFX_JustDisplay, drag your finger on the screen to draw
**$${\color{green}WORKS}$$**

## $${\color{yellow}cyd12}$$
LVGL touch using CST820
**$${\color{green}WORKS}$$**

## $${\color{yellow}cyd13}$$
LVGL touch using CST820 with SD card.
**$${\color{green}WORKS}$$**

## $${\color{yellow}cyd14}$$
LVGL touch using CST820 with SD card and loading a JPG (JPEGDecoder) or PNG (PNGdec) image from the card.
***$${\color{red}Does not work.}$$***

## $${\color{yellow}cyd15}$$
Trying to get LittleFS + LovyanGFX + png to work.
***$${\color{red}Does not work.}$$***

## $${\color{yellow}cyd17$$}
Binary read and write SD card.
**$${\color{green}WORKS}$$**
also 20??



## $${\color{yellow}cyd21}$$
Trying TFT_eSPI + TJpgDec + touch + sd card.
***$${\color{red}Does not work.}$$***

## $${\color{yellow}cyd22}$$
TFT\_eSPI + lvgl + touch + TJpgDec as individual buttons (create\_image\_button\_from\_sd).  Was working, this is where I discovered something else I did had changed the libraries and it no longer works but its code didn't change as far as I can recall. Touch is working, display lights up, but that's it. ***$${\color{red}Does not work.}$$***
