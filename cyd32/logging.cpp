#include <Arduino.h>  // Automatically included in .ino files
#include <lvgl.h>
#include "logging.h"

/* Serial debugging for LVGL */
#if LV_USE_LOG != 0
void log_print(lv_log_level_t level, const char* buf)
{
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
}
#endif

#if DEBUGMODE

void logheader(const char* title)
{
    int i = strlen(title);
    i += 12;  // some padding on each side

    for (int x = 0; x < i - 1; x++)
    {
        Serial.print("=");
    }
    Serial.println("=");

    Serial.print("      ");  // padding left
    Serial.print(title);
    Serial.println("      ");  // padding right

    for (int x = 0; x < i - 1; x++)
    {
        Serial.print("=");
    }
    Serial.println("=");
}

void printindent()
{
    for (int ctr = 1; ctr <= loglevel; ctr++)
    {
        Serial.print("    ");
    }
}

void incrementindent()
{
    loglevel++;
}

void decrementindent()
{
    loglevel--;
}

// == == == == == == ==== == == == == == ==
// from https:  //arduino.stackexchange.com/questions/56517/formatting-strings-in-arduino-for-output
// by Jan Turoň - https:  //arduino.stackexchange.com/users/28317/jan-turo%c5%88
// I renamed it to logit() and added printindent();
#include <stdarg.h>
//void Serialprintln(const char* input...)
void logit(const char* input...)
{
    printindent();

    va_list args;
    va_start(args, input);
    for (const char* i = input; *i != 0; ++i)
    {
        if (*i != '%')
        {
            Serial.print(*i);
            continue;
        }
        switch (*(++i))
        {
            case '%': Serial.print('%'); break;
            case 's': Serial.print(va_arg(args, char*)); break;
            case 'd': Serial.print(va_arg(args, int), DEC); break;
            case 'b': Serial.print(va_arg(args, int), BIN); break;
            case 'o': Serial.print(va_arg(args, int), OCT); break;
            case 'x': Serial.print(va_arg(args, int), HEX); break;
            case 'f': Serial.print(va_arg(args, double), 2); break;
        }
    }
    Serial.println();
    va_end(args);
}

void logitnonewline(const char* input...)
{
    printindent();

    va_list args;
    va_start(args, input);
    for (const char* i = input; *i != 0; ++i)
    {
        if (*i != '%')
        {
            Serial.print(*i);
            continue;
        }
        switch (*(++i))
        {
            case '%': Serial.print('%'); break;
            case 's': Serial.print(va_arg(args, char*)); break;
            case 'd': Serial.print(va_arg(args, int), DEC); break;
            case 'b': Serial.print(va_arg(args, int), BIN); break;
            case 'o': Serial.print(va_arg(args, int), OCT); break;
            case 'x': Serial.print(va_arg(args, int), HEX); break;
            case 'f': Serial.print(va_arg(args, double), 2); break;
        }
    }
    // Serial.println();
    va_end(args);
}

void logitnoindent(const char* input...)
{
    va_list args;
    va_start(args, input);
    for (const char* i = input; *i != 0; ++i)
    {
        if (*i != '%')
        {
            Serial.print(*i);
            continue;
        }
        switch (*(++i))
        {
            case '%': Serial.print('%'); break;
            case 's': Serial.print(va_arg(args, char*)); break;
            case 'd': Serial.print(va_arg(args, int), DEC); break;
            case 'b': Serial.print(va_arg(args, int), BIN); break;
            case 'o': Serial.print(va_arg(args, int), OCT); break;
            case 'x': Serial.print(va_arg(args, int), HEX); break;
            case 'f': Serial.print(va_arg(args, double), 2); break;
        }
    }
    Serial.println();
    va_end(args);
}
// == == == == == == ==== == == == == == ==

void enterfunction(const char* x)
{
    logit("Entering %s", x);
    incrementindent();
}

void exitfunction(const char* x)
{
    decrementindent();
    logit("Exiting %s", x);
}

void showmemstats()
{
    logit("Total heap:  %d", ESP.getHeapSize());
    logit("Free heap:   %d", ESP.getFreeHeap());
    logit("Total PSRAM: %d", ESP.getPsramSize());
    logit("Free PSRAM:  %d", ESP.getFreePsram());
}

#else

// Don't take up any memory or processing for production.
#define logit(x)
#define logitnonewline(x)
#define logitnoindent(x)
#define enterfunction(x)
#define exitfunction(x)
#define incrementindent()
#define decrementindent()
#define printindent()
#define showmemstats()
#define logheader(x)

#endif  // DEBUGMODE