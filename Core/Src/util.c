#include "util.h"
#include "stm32f0xx.h"
#include <string.h>


void nano_wait(unsigned int n) {
    asm(    "        mov r0,%0\n"
            "repeat: sub r0,#83\n"
            "        bgt repeat\n" : : "r"(n) : "r0", "cc");
}

uint8_t str_contains_char(char* s, char c) {
    return strchr(s, c) != NULL ? 1 : 0;
}

int abs(int n) {
    return n < 0 ? -n : n;
}

int sign(int n) {
//    return n > 0 ? 1 : n == 0 ? 0 : -1;
    return n > 0 ? 1 : -1;
}
