#ifndef STM32_H
#define STM32_H

#include <stdint.h>
#include "stm32f091xc.h"

// GPIO functions

// gpio test led
void init_pb12(void);

// button pins
// uses internal pull down resistors
// high=open | low=closed
void init_pc0(void);
void init_pc1(void);

//extra gpio pins
void init_pc4(void); // will be used for the third button to help control the main menu
void init_pa5(void);
void init_pa6(void);
void init_pa7(void);

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
// pulled up by internal resistor
void init_pa0(void);
void init_pa1(void);
void init_pa2(void);
void init_pa3(void);
void init_pb0(void);
void init_pb1(void);
void init_pc5(void);

// usart comms between mcu
void init_pb6(void); // tx
void init_pb7(void); // rx

// pin poll/set functions

// button poll functions
int poll_pc0(void);
int poll_pc1(void);
int poll_pc4(void);

// switch poll functions:
// returns 1 if open, 0 if closed
int poll_pa0(void);
int poll_pa1(void);
int poll_pa2(void);
int poll_pa3(void);
int poll_pb0(void);
int poll_pb1(void);
int poll_pc5(void);

// poll mcu comms
int poll_pb6(void);

void set_pb12(uint8_t val);
void set_pb13(uint8_t val);
void set_pc6(uint8_t val);
void set_pc7(uint8_t val);
void set_pc8(uint8_t val);
void set_pc9(uint8_t val);

// timer functions
void init_tim1(void);
void init_tim3(uint32_t dma_srcAddr);
void init_tim14(void);
void init_tim15(void);
void init_tim16(void);
void init_tim17(void);

void enable_timer(TIM_TypeDef *timer);
void disable_timer(TIM_TypeDef *timer);

// dma functions
void init_dma1_ch3(uint32_t memAddr, uint16_t memAddrLen, uint32_t periphAddr);
void enable_dma1_ch3();
void disable_dma1_ch3();

// usart functions
void init_usart(void);

void hard_reset(void);

#endif
