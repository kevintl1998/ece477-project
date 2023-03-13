#ifndef STM32_H
#define STM32_H

#include <stdint.h>

// GPIO functions

// button pins
void init_pc0(void);
void init_pc1(void);

// solenoid pins
void init_pb13(void);
void init_pc6(void);
void init_pc7(void);
void init_pc8(void);
void init_pc9(void);

// i2c pins
void init_pb6(void);
void init_pb7(void);

//led pins
void init_pb4(void);

//servo pins
void init_pa8(void);

//switches
void init_pa0(void);
void init_pa1(void);
void init_pa2(void);
void init_pa3(void);
void init_pa4(void);
void init_pb0(void);
void init_pb1(void);
void init_pc5(void);

// pin poll/set functions
int poll_pc0(void);
int poll_pc1(void);
void set_pb13(uint8_t val);
void set_pc6(uint8_t val);
void set_pc7(uint8_t val);
void set_pc8(uint8_t val);
void set_pc9(uint8_t val);
// timer functions




// I2C comm functions

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
