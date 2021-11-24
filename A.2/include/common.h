#ifndef COMMON_H
#define COMMON_H

    #define TRUE  (1)
    #define FALSE (0)

    #ifdef DEBUG
        #define debug(...) printf(__VA_ARGS__); fflush(stdout);
    #else
        #define debug(...)
    #endif


    #define LINE "---------------------------------\n"

    #define BUFFER_SIZE (1024)
    #define OPERATION_SIZE (2)

    void check(int value, char* name, int _exit);

#endif