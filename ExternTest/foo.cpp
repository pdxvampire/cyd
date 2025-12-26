#include <Arduino.h>
#include "foo.h"

// these are all declared in foo.h and defined here

const char* bar = "foo bar baz";
const int my_global_int = 255;

void functioninfoo()
{
    Serial.printf("[foo.cpp] - This is the value of 'const char* bar' that is declared in the included 'foo.h', defined in this .cpp and in this case called from the .ino:  %s\n", bar);
}

int sum(int a, int b)
{
    return a + b;
}