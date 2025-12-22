#ifndef LOGGING_H
#define LOGGING_H

// Define DEBUG true to enable debug output,
// or comment it out/set to false to disable it and save memory/processing time.
#if !defined(DEBUGMODE)
#define DEBUGMODE true
#endif

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

#endif // DEBUGMODE

#endif // LOGGING_H