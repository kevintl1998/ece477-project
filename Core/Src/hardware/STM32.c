#include "hardware/STM32.h"

#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_gpio.h"
#include "stm32f0xx_ll_dma.h"
#include "core_cm0.h"

#include "settings.h"
#include "util.h"


GPIO_InitTypeDef pc0_init;
GPIO_InitTypeDef pc1_init;
GPIO_InitTypeDef pb4_init;


void init_pb12(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    GPIOB->MODER &= ~GPIO_MODER_MODER12; // reset moder value
    GPIOB->MODER |= 1 << (12 * 2); // set moder to output
    GPIOB->PUPDR |= 2 << (12 * 2); // set internal pull-down resistor
}

// ==================================

void init_pc0(void) {
	// button 0
	__HAL_RCC_GPIOC_CLK_ENABLE();
	pc0_init.Pin = GPIO_PIN_0;
	pc0_init.Mode = GPIO_MODE_INPUT;
//	pc0_init.Pull = GPIO_NOPULL;
	pc0_init.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOC, &pc0_init);
}

void init_pc1(void) {
	// button 1
	__HAL_RCC_GPIOC_CLK_ENABLE();
	pc1_init.Pin = GPIO_PIN_1;
	pc1_init.Mode = GPIO_MODE_INPUT;
//	pc1_init.Pull = GPIO_NOPULL;
	pc1_init.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOC, &pc1_init);

}

// ==================================

void init_pc4(void) { // used for third button
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

	GPIOC->MODER &= ~(3 << (4 * 2)); // input mode
	GPIOC->PUPDR |= 2 << (4 * 2); // pull down resistor
}

void init_pa5(void) {
	// currently unused
}

void init_pa6(void) {
	// currently unused
}

void init_pa7(void) {
	// currently unused
}

// ==================================

void init_pb4(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;



	GPIOB->MODER &= ~GPIO_MODER_MODER4;
	GPIOB->MODER |= GPIO_MODER_MODER4_1; //	GPIOB->MODER |= 1 << (4 * 2);
	GPIOB->AFR[0] |= (1 << (4 * 4)); // af mode: TIM3_CH1

//	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
//	pb4_init.Pin = GPIO_PIN_6;
//	pb4_init.Speed = GPIO_SPEED_FREQ_HIGH;
//	pb4_init.Mode = GPIO_MODE_OUTPUT_PP;
//	pb4_init.Pull = GPIO_NOPULL;
//
//	HAL_GPIO_Init(GPIOB, &pb4_init);
}

// ==================================

void init_pa8(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODER8;
	GPIOA->MODER |= GPIO_MODER_MODER8_1;
	GPIOA->AFR[1] |= (2 << (0 * 4)); // af mode: TIM1_CH1;
}

// ==================================

void init_pa0(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    GPIOA->MODER &= ~(3 << (0 * 2)); // set moder to input
//    GPIOA->PUPDR |= (2 << (2 * 2)); // set internal pull-down
    GPIOA->PUPDR &= ~(3 << (2 * 2)); // set no pull-up or pull-down
}

void init_pa1(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOA->MODER &= ~(3 << (1 * 2)); // set moder to input
//	GPIOA->PUPDR |= (2 << (2 * 2)); // set internal pull-down resistor
	GPIOA->PUPDR &= ~(3 << (2 * 2)); // set no pull-up or pull-down
}

void init_pa2(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOA->MODER &= ~(3 << (2 * 2)); // set moder to input
//	GPIOA->PUPDR |= (2 << (2 * 2)); // set internal pull-down resistor
	GPIOA->PUPDR &= ~(3 << (2 * 2)); // set no pull-up or pull-down
}

void init_pa3(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOA->MODER &= ~(3 << (3 * 2)); // set moder to input
//	GPIOA->PUPDR |= (2 << (3 * 2)); // no pull-up/pull-down resistor
	GPIOA->PUPDR &= ~(3 << (3 * 2)); // set no pull-up or pull-down
}

void init_pb0(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	GPIOB->MODER &= ~(3 << (0 * 2)); // set moder to input
//	GPIOB->PUPDR |= (2 << (0 * 2)); // set internal pull-down resistor
	GPIOB->PUPDR &= ~(3 << (0 * 2)); // set no pull-up or pull-down
}

void init_pb1(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	GPIOB->MODER &= ~(3 << (1 * 2)); // set moder to input
//	GPIOB->PUPDR |= (2 << (1 * 2)); // set internal pull-down resistor
	GPIOB->PUPDR &= ~(3 << (1 * 2)); // set no pull-up or pull-down
}

void init_pc5(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

	GPIOC->MODER &= ~(3 << (5 * 2)); // set moder to input
//	GPIOC->PUPDR |= (2 << (5 * 2)); // set internal pull-down resistor
	GPIOC->PUPDR &= ~(3 << (5 * 2)); // set no pull-up or pull-down
}

// ==================================

void init_pb13(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // enable clock
    GPIOB->MODER &= ~GPIO_MODER_MODER13; // reset moder value
    GPIOB->MODER |= 1 << (13 * 2); // set moder to output
    GPIOB->PUPDR |= 2 << (13 * 2); // set internal pull-down resistor

}

void init_pc6(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // enable clock
    GPIOC->MODER &= ~GPIO_MODER_MODER6; // reset moder value
    GPIOC->MODER |= 1 << (6 * 2); // set moder to output
    GPIOC->PUPDR |= 2 << (6 * 2); // set internal pull-down resistor
}

void init_pc7(void) {
    GPIOC->MODER &= ~GPIO_MODER_MODER7; // reset moder value
    GPIOC->MODER |= 1 << (7 * 2); // set moder to output
    GPIOC->PUPDR |= 2 << (7 * 2); // set internal pull-down resistor
}

void init_pc8(void) {
    GPIOC->MODER &= ~GPIO_MODER_MODER8; // reset moder value
    GPIOC->MODER |= 1 << (8 * 2); // set moder to output
    GPIOC->PUPDR |= 2 << (8 * 2); // set internal pull-down resistor
}

void init_pc9(void) {
    GPIOC->MODER &= ~GPIO_MODER_MODER9; // reset moder value
    GPIOC->MODER |= 1 << (9 * 2); // set moder to output
    GPIOC->PUPDR |= 2 << (9 * 2); // set internal pull-down resistor
}

// ==================================

void init_pb6(void) {
	// THIS CODE IS FOR TESTING IF THE PIN WORKS CORRECTLY
	// UPDATE WITH PROPER I2C CODE
    GPIOB->MODER &= ~GPIO_MODER_MODER6; // reset moder value
    GPIOB->MODER |= 1 << (6 * 2); // set moder to output
    GPIOB->PUPDR |= 2 << (6 * 2); // set internal pull-down resistor
}

void init_pb7(void) {
	// THIS CODE IS FOR TESTING IF THE PIN WORKS CORRECTLY
	// UPDATE WITH PROPER I2C CODE
    GPIOB->MODER &= ~GPIO_MODER_MODER7; // reset moder value
    GPIOB->MODER |= 1 << (7 * 2); // set moder to output
    GPIOB->PUPDR |= 2 << (7 * 2); // set internal pull-down resistor
}

// ==================================

// buttons
int poll_pc0(void) {
    return (GPIOC->IDR & GPIO_IDR_0) >> 0;
}
int poll_pc1(void) {
    return (GPIOC->IDR & GPIO_IDR_1) >> 1;
}
int poll_pc4(void) {
	return (GPIOC->IDR & GPIO_IDR_4) >> 4;
}

// switches
int poll_pa0(void) {
	return (GPIOA->IDR & GPIO_IDR_0) >> 0;
}
int poll_pa1(void) {
	return (GPIOA->IDR & GPIO_IDR_1) >> 1;
}
int poll_pa2(void) {
	return (GPIOA->IDR & GPIO_IDR_2) >> 2;
}
int poll_pa3(void) {
	return (GPIOA->IDR & GPIO_IDR_3) >> 3;
}
int poll_pb0(void) {
	return (GPIOB->IDR & GPIO_IDR_0) >> 0;
}
int poll_pb1(void) {
	return (GPIOB->IDR & GPIO_IDR_1) >> 1;
}
int poll_pc5(void) {
	return (GPIOC->IDR & GPIO_IDR_5) >> 5;
}


void set_pin(uint8_t val, GPIO_TypeDef *gpio_typedef, uint8_t pin_num) {
    if (val == 1) {
        gpio_typedef->BSRR |= 1 << pin_num;
    } else if (val == 0) {
        gpio_typedef->BSRR |= 1 << (pin_num + 16);
    }
}

void set_pb12(uint8_t val) {
	set_pin(val, GPIOB, 12);
}

void set_pb13(uint8_t val) {
	set_pin(val, GPIOB, 13);
}

void set_pc6(uint8_t val) {
	set_pin(val, GPIOC, 6);
}

void set_pc7(uint8_t val) {
	set_pin(val, GPIOC, 7);
}

void set_pc8(uint8_t val) {
	set_pin(val, GPIOC, 8);
}

void set_pc9(uint8_t val) {
	set_pin(val, GPIOC, 9);
}

void init_tim1(void) {
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

	// init timer
	TIM1->PSC = 48-1;     // Set prescaler to 48-1
	TIM1->ARR = 20000-1;  // Set auto reload register to 20000-1

	// init pwm
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;   // Set PWM mode 1
	TIM1->CCER |= TIM_CCER_CC1E;   // Enable capture/compare 1 output
    TIM1->BDTR |= TIM_BDTR_MOE;
	TIM1->CCR1 = 500;

	// enable timer
	TIM1->CR1 |= TIM_CR1_CEN;

}

void init_tim3(uint32_t dma_srcAddr) {
	// init tim3 pwm and dma for output on pb4

	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	TIM3->PSC = 1-1;
	TIM3->ARR = 60-1;

	TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;   // Set PWM mode 1
	TIM3->CCER |= TIM_CCER_CC1E;   // Enable capture/compare 1 output
	TIM3->BDTR |= TIM_BDTR_MOE;
	TIM3->CCR1 = 0;

	TIM3->DIER |= TIM_DIER_UDE;

	// set tim3 dmr_dba to tim3_cr1 (default value)
	// set tim3 dmr_dbl to 1 transfer (default value)

	TIM3->CR1 |= TIM_CR1_CEN;
	NVIC_SetPriority(TIM3_IRQn, 0);
	NVIC_EnableIRQ(TIM3_IRQn);

}

void init_tim14(void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;

	TIM14->PSC = 1000-1;
	TIM14->ARR = 1000-1;

	TIM14->DIER |= TIM_DIER_UIE;

	TIM14->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM14_IRQn);
}

void init_tim15(void) {
	RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;

	// timer freq = stm clock freq (48MHz) / ((ARR + 1) * (PSC + 1))
	// 48Mhz / (1000 * 500) = 96hz
	TIM15->PSC = 1000-1;
	TIM15->ARR = 500-1;

	TIM15->DIER |= TIM_DIER_UIE;
	TIM15->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM15_IRQn);
}

void init_tim16(void) {
	RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;

	TIM16->PSC = 1000-1;
	TIM16->ARR = 500-1;

	TIM16->DIER |= TIM_DIER_UIE;
	TIM16->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM16_IRQn);
}

void init_tim17(void) {
	// for bit banging mcu comms
}

void enable_timer(TIM_TypeDef *timer) {
	timer->CR1 |= TIM_CR1_CEN;
}

void disable_timer(TIM_TypeDef *timer) {
	timer->CR1 &= ~TIM_CR1_CEN;
}

extern uint16_t ws_io_buffer[];
void init_dma1_ch3(uint32_t memAddr, uint16_t memAddrLen, uint32_t periphAddr) {
	// init dma1 for use with tim1 ch1

	RCC->AHBENR |= RCC_AHBENR_DMAEN;

//	DMA1_Channel4->CCR |= DMA_CCR_MSIZE_0; // mem size = 16 bits
//	DMA1_Channel4->CCR |= DMA_CCR_PSIZE_0; //periph size = 16 bits
//	DMA1_Channel4->CCR |= DMA_CCR_MINC; // enable mem increment mode
//	DMA1_Channel4->CCR |= DMA_CCR_CIRC; // enable circular mode (disable for sending data to LEDs)
//	DMA1_Channel4->CCR |= DMA_CCR_DIR; // set direction to mem2periph
//	DMA1_Channel4->CCR |= DMA_CCR_TCIE; // enable transfer complete interrupt
//	DMA1_Channel4->CNDTR = memAddrLen;
//	DMA1_Channel4->CPAR = periphAddr;
//	DMA1_Channel4->CMAR = memAddr;
//	NVIC_EnableIRQ(DMA1_Ch4_7_DMA2_Ch3_5_IRQn);

	DMA1_Channel3->CCR |= DMA_CCR_MSIZE_0; // mem size = 16 bits
	DMA1_Channel3->CCR |= DMA_CCR_PSIZE_0; //periph size = 16 bits
	DMA1_Channel3->CCR |= DMA_CCR_MINC; // enable mem increment mode
	DMA1_Channel3->CCR |= DMA_CCR_CIRC; // enable circular mode (disable for sending data to LEDs)
	DMA1_Channel3->CCR |= DMA_CCR_DIR; // set direction to mem2periph
	DMA1_Channel3->CCR |= DMA_CCR_TCIE; // enable transfer complete interrupt
	DMA1_Channel3->CNDTR = memAddrLen;
	DMA1_Channel3->CPAR = periphAddr;
	DMA1_Channel3->CMAR = &ws_io_buffer;
	NVIC_EnableIRQ(DMA1_Ch2_3_DMA2_Ch1_2_IRQn);

}

void enable_dma1_ch3() {
	DMA1_Channel3->CCR |= DMA_CCR_EN;
}
void disable_dma1_ch3() {
	while(DMA1_Channel3->CNDTR); // wait for channel to finish any ongoing transfers
	DMA1_Channel3->CCR &= ~DMA_CCR_EN;
}


void init_i2c_p1(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    GPIOB->MODER |= 2<<(2*6) | 2<<(2*7);
    GPIOB->AFR[0] |= 1<<(4*6) | 1<<(4*7);

    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    I2C1->CR1 &= ~I2C_CR1_PE;       // Disable PE bit before changing things
    I2C1->CR1 &= ~I2C_CR1_ANFOFF;   // Turn off Analog noise filter
    I2C1->CR1 &= ~I2C_CR1_ERRIE;    // Disable Error interrupt
    I2C1->CR1 &= ~I2C_CR1_NOSTRETCH;    // Enable clock stretching

    // Timingr register
    I2C1->TIMINGR = 0;
    I2C1->TIMINGR &= ~I2C_TIMINGR_PRESC; // Clear prescaler
    I2C1->TIMINGR |= 0 << 28;           // Set prescaler to 0
    I2C1->TIMINGR |= 3 << 20;           // SCLDEL
    I2C1->TIMINGR |= 1 << 16;           // SCADEL
    I2C1->TIMINGR |= 3 << 8;            // SCLH

    I2C1->OAR1 |= I2C_OAR1_OA1EN;      // Enable own address 1

    I2C1->OAR1 = I2C_OAR1_OA1EN | (P1_I2C_ADDRESS << 1);  // Set 7-bit own address to P1_I2C_ADDRESS

    I2C1->OAR2 &= ~I2C_OAR2_OA2EN;      // Disable own address 2

    I2C1->CR2 &= ~I2C_CR2_ADD10;        // 0 = 7-bit mode; 1 = 10 bit
    I2C1->CR2 |= I2C_CR2_AUTOEND;       // Enable the auto end
    //I2C1->CR2 |= I2C_CR2_NACK;

    I2C1->CR1 |= I2C_CR1_PE;    // Enable I2C1

}

void init_i2c_p2(void) {
        RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

        GPIOB->MODER |= 2<<(2*6) | 2<<(2*7);
        GPIOB->AFR[0] |= 1<<(4*6) | 1<<(4*7);

        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

        I2C1->CR1 &= ~I2C_CR1_PE;       // Disable PE bit before changing things
        I2C1->CR1 &= ~I2C_CR1_ANFOFF;   // Turn off Analog noise filter
        I2C1->CR1 &= ~I2C_CR1_ERRIE;    // Disable Error interrupt
        I2C1->CR1 &= ~I2C_CR1_NOSTRETCH;    // Enable clock stretching

        // Timingr register
        I2C1->TIMINGR = 0;
        I2C1->TIMINGR &= ~I2C_TIMINGR_PRESC; // Clear prescaler
        I2C1->TIMINGR |= 0 << 28;           // Set prescaler to 0
        I2C1->TIMINGR |= 3 << 20;           // SCLDEL
        I2C1->TIMINGR |= 1 << 16;           // SCADEL
        I2C1->TIMINGR |= 3 << 8;            // SCLH

        I2C1->OAR1 |= I2C_OAR1_OA1EN;      // Enable own address 1

        I2C1->OAR1 = I2C_OAR1_OA1EN | (P2_I2C_ADDRESS << 1);  // Set 7-bit own address to P2_I2C_ADDRESS

        I2C1->OAR2 &= ~I2C_OAR2_OA2EN;      // Disable own address 2

        I2C1->CR2 &= ~I2C_CR2_ADD10;        // 0 = 7-bit mode; 1 = 10 bit
        I2C1->CR2 |= I2C_CR2_AUTOEND;       // Enable the auto end
        //I2C1->CR2 |= I2C_CR2_NACK;

        I2C1->CR1 |= I2C_CR1_PE;    // Enable I2C1
}


void i2c_waitidle_send(void) {
    while ((I2C1->ISR & I2C_ISR_BUSY) == I2C_ISR_BUSY);
}

void i2c_waitidle_recv(void) {
    while ((I2C1->ISR & I2C_ISR_BUSY) != I2C_ISR_BUSY);
}
/*
void i2c_start_send(uint32_t devaddr, uint8_t size, uint8_t dir) {
    uint32_t tmpreg = I2C1->CR2;
    tmpreg &= ~();

    uint32_t tmpreg = I2C1->CR2;
    tmpreg &= ~(I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND |I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
    if (dir == 1) {
        tmpreg |= I2C_CR2_RD_WRN;
    } else {
        tmpreg &= ~I2C_CR2_RD_WRN;
        tmpreg |= ((devaddr<<1) & I2C_CR2_SADD) | ((size << 16) & I2C_CR2_NBYTES);
        tmpreg |= I2C_CR2_START;
        I2C1->CR2 = tmpreg;
    }
}

void i2c_start_recv(uint32_t devaddr, uint8_t size, uint8_t dir) {
    uint32_t tmpreg = I2C1->CR2;
    tmpreg &= ~(I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND |I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
    if (dir == 1) {
        tmpreg |= I2C_CR2_RD_WRN;
    } else {
        tmpreg &= ~I2C_CR2_RD_WRN;
        tmpreg |= ((devaddr<<1) & I2C_CR2_SADD) | ((size << 16) & I2C_CR2_NBYTES);
        tmpreg |= I2C_CR2_START;
        I2C1->CR2 = tmpreg;
    }
}

void i2c_stop(void) {
    if (I2C1->ISR & I2C_ISR_STOPF)
        return;
    I2C1->CR2 |= I2C_CR2_STOP;
    while( (I2C1->ISR & I2C_ISR_STOPF) == 0);
    I2C1->ICR |= I2C_ICR_STOPCF;
}

int i2c_checknack(void) {
    return ((I2C1->ISR >> 4) & 1);
}

void i2c_clearnack(void) {
    I2C1->ICR |= 0x10;
}

int i2c_senddata(uint8_t devaddr, const void *data, uint8_t size) {
    int i;
    if (size <= 0 || data == 0) return -1;
    uint8_t *udata = (uint8_t*)data;
    i2c_waitidle_send();
    i2c_start(devaddr, size, 0);
    for (i=0; i<size; i++) {
        int count = 0;
        while ((I2C1->ISR & I2C_ISR_TXIS) == 0) {
            count += 1;
            if (count > 1000000) return -1;
            if (i2c_checknack()) { i2c_clearnack(); i2c_stop(); return -1;}
        }
        I2C1->TXDR = udata[i] & I2C_TXDR_TXDATA;
    }
    while((I2C1->ISR & I2C_ISR_TC) == 0 && (I2C1->ISR & I2C_ISR_NACKF) == 0);

    if ((I2C1->ISR & I2C_ISR_NACKF) != 0)
        return -1;
    i2c_stop();
    return 0;
}

int i2c_recvdata(uint8_t devaddr, void *data, uint8_t size) {
    int i;
    if (size <= 0 || data == 0) return -1;
    uint8_t *udata = (uint8_t*)data;
    i2c_waitidle();
    i2c_start(devaddr, size, 1);

    for (i=0; i<size;i++) {
        int count = 0;
        while ((I2C1->ISR & I2C_ISR_RXNE) == 0) {
            count += 1;
            if (count > 1000000) return -2;
            if ( i2c_checknack() ){
                i2c_clearnack();
                i2c_stop();
                return -3;
            }
        }
        udata[i] = I2C1->RXDR;
    }
    while ((I2C1->ISR & I2C_ISR_TC) == 0 && (I2C1->ISR & I2C_ISR_NACKF) == 0);
    if ((I2C1->ISR & I2C_ISR_NACKF) != 0) {
        return -1;
    }
    i2c_stop();
    return 0;
}

*/

void hard_reset(void) {
	NVIC_SystemReset();
}
