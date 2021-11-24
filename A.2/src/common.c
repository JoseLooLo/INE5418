#include <stdio.h>
#include <stdlib.h>
#include <common.h>

void check(int value, char* name, int _exit) {
    if (value < 0) {
        debug("Check failed! %s returned the value %d.\n", name, value);
        if (_exit)
            exit(value);
    }
}