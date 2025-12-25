#ifndef LOGGING_H
#define LOGGING_H

#include <lvgl.h>

// Define DEBUG true to enable debug output,
// or comment it out/set to false to disable it and save memory/processing time.
#if !defined(DEBUGMODE)
#define DEBUGMODE true
#endif

extern int loglevel;

#if DEBUGMODE

void logheader(const char* title);
void printindent();
void incrementindent();
void decrementindent();
void logit(const char* input...);
void logitnonewline(const char* input...);
void logitnoindent(const char* input...);
void enterfunction(const char* x);
void exitfunction(const char* x);
void showmemstats();
void log_print(lv_log_level_t level, const char* buf);

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
void log_print(lv_log_level_t level, const char* buf);

#endif  // DEBUGMODE

#endif  // LOGGING_H