#include "foo.h"
#include "bar.h"

// In C++, a const variable has internal linkage by default, unlike C.
// So the following will generate a linker error:
//    library.h:
//        const int my_global_int = 255; //wrong way to make a definition of global const variable in C++, valid in C
//    main.cpp:
//        #include "library.h"
//        extern const int my_global_int; //declaration
// This is the correct way in C++:
//    library.h:
//        extern const int my_global_int; //declaration
//    library.cpp:
//        #include "library.h"
//        const int my_global_int = 255; //a definition of global const variable in C++
//    main.cpp:
//        #include "library.h"
//        extern const int my_global_int; <--- optional here as long as it's in library.h
//        make use of my_global_int somehow, like sum(my_global_int, 3)
// Also works for functions:
//    library.h
//        extern int sum(int, int);  // declaration, the function will be defined elsewhere (usually library.cpp)
//        extern const int my_global_int;
//    library.cpp
//        #include "library.h" // if you don't include library.h then you need to use 'extern const int my_global_int' in the .cpp
//        const int my_global_int = 255; // a definition of global const variable in C++
//        int sum(int a, int b) { return a + b; }
//    main.cpp
//        #include "library.h"
//        Serial.printf("Sum of 5 and my_global_int is %d\n", sum(5, my_global_int));

void setup()
{
    Serial.begin(115200);

    // Wait for the serial port to connect so the Serial Monitor printouts work consistently
    // This may not be necessary on Windows or Linux but with my Macbook Air M3 (2024) it is.
    delay(2000);

    Serial.println("");

    Serial.printf("[ExternTest.ino] - This is the value of 'const char* bar_in_foo' that is defined in the included 'foo.h':  %s\n", bar_in_foo);
    Serial.printf("[ExternTest.ino] - Sum of 5 and my_global_int is %d\n", sum(5, my_global_int));
    
    barfunction();

    functioninfoo();

    Serial.printf("[ExternTest.ino] - This is the value of 'int baz' that is declared AND DEFINED in the included 'bar.h', and in this case called from the .ino:  %d\n", baz);
}

void loop()
{
    // put your main code here, to run repeatedly:
}
