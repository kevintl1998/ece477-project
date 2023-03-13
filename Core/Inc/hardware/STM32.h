#ifndef STM32_H
#define STM32_H

#include <stdint.h>

void init_i2c_p2(void);
void init_i2c_p1(void);

void i2c_waitidle_send(void);
void i2c_waitidle_recv(void);

void i2c_start_send(uint32_t devaddr, uint8_t size, uint8_t dir);
void i2c_start_recv(uint32_t devaddr, uint8_t size, uint8_t dir);

void i2c_stop(void);
int i2c_checknack(void);
void i2c_clearnack(void);
int i2c_senddata(uint8_t devaddr, const void *data, uint8_t size);
int i2c_recvdata(uint8_t devaddr, void *data, uint8_t size);

#endif
