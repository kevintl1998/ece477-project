#include "util.h"
#include "stm32f0xx.h"
#include <string.h>
#include <stdint.h>


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

uint32_t digits_to_arr(uint32_t number, uint32_t* arr, uint32_t arr_size) {
	if(number == 0) {
		arr[0] = 0;
		return 1;
	}
    uint32_t digits = 0;
        while (number > 0) {
        if(digits == arr_size) {
        	break;
        }
        arr[digits] = number % 10;
        number = number / 10;
        digits++;
    }
    return digits;
}
