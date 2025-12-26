#include <Arduino.h>
#include "bar.h"

int my_global_int_two = 2;

// this would not work:  baz = 333;
int baz = 333;

// this would cause an error:
//     extern int defined_in_bar_h = 666;
// this will cause a multiple definition error
//     extern int defined_in_bar_h;

// needs to look like the following:
// argh.h:  extern int varname;
// argh.cpp/blah.ino:
//            #include "argh.h"
//            varname = 666;
int varname = 666;

void barfunction()
{
    Serial.printf("[bar.cpp] - This is the value of 'int my_global_int_two' that is declared in the included 'bar.h', defined in bar.cpp and in this case called from the .ino:  %d\n", my_global_int_two);
    Serial.printf("[bar.cpp] - This is the value of 'int baz' that is declared AND DEFINED in the included 'bar.h', used in bar.cpp and called from the .ino:  %d\n", baz);
    Serial.printf("[bar.cpp] - This is the value of 'varname', from barfunction(): %d\n", varname);
}