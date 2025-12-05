// Define DEBUG true to enable debug output,
// or comment it out/set to false to disable it and save memory/processing time.
#if !defined(DEBUGMODE)
#define DEBUGMODE true
#endif

int loglevel = 0;

#if DEBUGMODE

void printindent(void)
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
    logit("Entering %s",x);
    incrementindent();
}

void exitfunction(const char* x)
{
    decrementindent();
    logit("Exiting %s", x);
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

#endif