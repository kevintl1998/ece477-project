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

#endif
