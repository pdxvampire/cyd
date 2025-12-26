#ifndef BAR_H
#define BAR_H

// this is fine as long as you define it someplace in a .cpp or .ino that includes bar.h
extern int my_global_int_two;

// these would cause a redefinition error:
//     int baz;
extern int baz;

// this will eventually cause a redefinition error:
//     int defined_in_bar_h = 999;
// this works
extern int varname;

void barfunction();

#endif