# $${\color{lime}Cheap \space Yellow \space Display}$$

**PRO TIP:**<br>
IF YOU RUN INTO SOMETHING FUNKY LIKE A SKETCH THAT WORKED BEFORE BUT DOESN'T NOW AND YOU DIDN'T CHANGE ANYTHING THAT YOU CAN RECALL, CHECK THAT NOTHING CHANGED FROM WORKING ON A DIFFERENT SKETCH, SUCH AS IN YOUR LIBRARIES, _LV\_CONF.H_, AND _USER\_SETUP.H_.  IF NOTHING HAS CHANGED, CLOSE OUT OF ARDUINO IDE AND CLEAR THE CACHE DIRECTORY.

**NOTE:**<br>
I ALWAYS ENABLE THE SERIAL MONITOR (_TOOLS->SERIAL MONITOR_) AND LOG TO IT SO IF A SKETCH COMPILES AND UPLOADS BUT APPEARS TO DO NOTHING, CHECK
THE SERIAL MONITOR FOR OUTPUT THERE.

## $${\color{yellow}cyd01}$$

Basic framework to test the board, includes pretty logging in Serial Monitor, suitable for using as a template for future projects. Just blinks the onboard LEDs a few times and writes to the log.
<br>$${\color{green}WORKS}$$

## $${\color{yellow}cyd02 - cyd06}$$

Don't use, only saving JIC and will be deleted once I have the rest of the samples cleaned up and checked in.
<br>$${\color{red}Does \space not \space work.}$$

## $${\color{yellow}cyd07}$$

Bunch of code jumbled together.  Not left in a working state because I realized I needed desperately to get things into source control after losing an _it all works_ piece of code when I lost power during a save and it zeroed out the file. This will get sliced and diced into further small modules that each work, then eventually all put back into one sketch.
<br>$${\color{red}Does \space not \space work.}$$

## $${\color{yellow}cyd08}$$

Read the contents of the SD card and display in Serial Monitor. **USED TO WORK, SOMETHING CHANGED IN THE LIBRARIES AND I WASN'T TRACKING THEM AT THIS POINT.**
<br>$${\color{red}Does \space not \space work.}$$

## $${\color{yellow}cyd09}$$

turn on the display using LovyanGFX (just display, no interaction)
<br>$${\color{green}WORKS \space as \space of \space commit \space 968c5e646512c533c3665fcf6c1a62293220fff5}$$

## $${\color{yellow}cyd10}$$

turn on the display using LVGL on top of LovyanGFX (just display, no interaction)
<br>$${\color{green}WORKS \space as \space of \space commit \space 968c5e646512c533c3665fcf6c1a62293220fff5}$$

## $${\color{yellow}cyd11}$$

basic touch using CST820 and LGFX_JustDisplay, drag your finger on the screen to draw
<br>$${\color{green}WORKS \space as \space of \space commit \space 968c5e646512c533c3665fcf6c1a62293220fff5}$$

## $${\color{yellow}cyd12}$$

LVGL touch using CST820
<br>$${\color{green}WORKS \space as \space of \space commit \space 968c5e646512c533c3665fcf6c1a62293220fff5}$$

## $${\color{yellow}cyd13}$$

LVGL touch using CST820 with SD card.
<br>$${\color{green}WORKS \space as \space of \space commit \space 968c5e646512c533c3665fcf6c1a62293220fff5}$$

## $${\color{yellow}cyd14}$$

LVGL touch using CST820 with SD card and loading a JPG (JPEGDecoder) or PNG (PNGdec) image from the card.  This is where I discovered that there is no working code online for the capacitive touch + display + sd card.  So the touch and display work on this but not the card unless you flip the init order, in which case the card works but not the display.  It is possible to load things from the card and then have the touch + display work, but there isn't enough memory on this board without a hardward mod to add PSRAM which I have not done to my board.
<br>$${\color{red}Does \space not \space work.}$$

## $${\color{yellow}cyd15}$$

Trying to get LittleFS \+ LovyanGFX \+ png to work.
<br>$${\color{red}Does \space not \space work.}$$

## $${\color{yellow}cyd16}$$

Draw JPG from binary data array. Runs into linker memory issue trying to include everything.  Remove LVGL and it has enough.  Abandoned after trying all suggestions I could find online.
<br>$${\color{red}Does \space not \space work.}$$

## $${\color{yellow}cyd17}$$

Binary read and write SD card.
<br>$${\color{green}WORKS \space as \space of \space commit \space 968c5e646512c533c3665fcf6c1a62293220fff5}$$

## $${\color{yellow}cyd18}$$

Trying to get everything to work using memory.  Abandoned after trying all suggestions I could find online.
<br>$${\color{red}Does \space not \space work.}$$

## $${\color{yellow}cyd19}$$

Playing with LodePNG attempting to blink an eye.  Abandoned for now, will come back after getting JPG working as PNG adds yet another level of complexity.
<br>$${\color{red}Does \space not \space work.}$$

## $${\color{yellow}cyd20}$$

Added showmemstats trying to see how much memory I have to work with. That part works.
<br>$${\color{green}WORKS \space as \space of \space commit \space 968c5e646512c533c3665fcf6c1a62293220fff5}$$

## $${\color{yellow}cyd21}$$

Trying TFT\_eSPI \+ TJpgDec \+ touch \+ sd card. Requires JPG images in root of sd card to work (not included in repo because any 100x100 images will do). Was working, this is where I discovered something else I did had changed the libraries and it no longer works but its code didn't change as far as I can recall. I have a great video of this working with Fallout images but right now can't get it to work again.  Will try and rebuild as a new sketch later after finishing this README and repo cleanup.
<br>$${\color{red}Does \space not \space work.}$$

## $${\color{yellow}cyd22}$$

TFT\_eSPI \+ lvgl \+ touch \+ TJpgDec as individual buttons (create\_image\_button\_from\_sd).  Was working, this is where I discovered something else I did had changed the libraries and it no longer works but its code didn't change as far as I can recall. Touch is working, display lights up, but that's it.
<br>$${\color{red}Does \space not \space work.}$$

## $${\color{yellow}cyd23}$$

Playing with LVGL\_CYD.  Abandoned after discovering yet other library changes killed what I had working at one point earlier.  THE LVGL BUTTON IS THERE AND RESPONDS BUT THERE IS ONLY A BLANK DISPLAY. Based on that I'm marking it as not working.
<br>$${\color{red}Does \space not \space work.}$$

## $${\color{yellow}cyd24}$$

Trying to manually create what LGVL\_CYD does.  Same not working as cyd23. Does write what it has to Serial Monitor. Abandoned at leat for now.
<br>$${\color{red}Does \space not \space work.}$$

## $${\color{yellow}cyd25}$$

Trying to recreate the nuka cola that worked (cyd21) and figure out what I did to the libraries.
<br>$${\color{blue}IN \space PROGRESS}$$