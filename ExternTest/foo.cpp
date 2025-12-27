#include <Arduino.h>
#include "foo.h"
#include "bar.h"

// these are all declared in foo.h and defined here

const char* bar_in_foo = "foo bar baz";
int my_global_int = 255;

void functioninfoo()
{
    Serial.printf("[foo.cpp] - This is the value of 'const char* bar_in_foo' that is declared in the included 'foo.h', defined in this .cpp and in this case called from the .ino:  %s\n", bar_in_foo);
    Serial.printf("[foo.cpp] - This is the value of 'int my_global_int_two' that is declared in the included 'bar.h', defined in bar.cpp and in this case called from the .ino:  %d\n", my_global_int_two);
    Serial.printf("[foo.cpp] - This is the value of 'int varname' that is declared in the included 'bar.h', defined in bar.cpp and in this case called from the .ino:  %d\n", varname);

    Serial.printf("[foo.cpp] - var_to_be_set_only_in_a_function %d\n", var_to_be_set_only_in_a_function);
}

int sum(int a, int b)
{
    return a + b;
}