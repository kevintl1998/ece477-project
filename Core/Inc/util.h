#ifndef __UTIL_H__
#define __UTIL_H__
#include <stdint.h>

#define ONE_BILLION 1000000000
#define ONE_MILLION 1000000
#define ONE_THOUSAND 1000

void nano_wait(unsigned int n);
uint8_t str_contains_char(char* s, char c);
int abs(int n);
int sign(int n);

// puts each of the digits in the number into the array in reverse order
// returns the number of digits placed in the array
uint32_t digits_to_arr(uint32_t number, uint32_t* arr, uint32_t arr_size);

void update_debounce_history(uint8_t* history, uint8_t curr_val, uint8_t max_hold);

#endif
