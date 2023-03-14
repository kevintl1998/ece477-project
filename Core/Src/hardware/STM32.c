#include "./hardware/STM32.h"
#include "stm32f0xx.h"
#include "settings.h"
#include "util.h"
#include "hardware/TFT_LCD_legacy.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_gpio.h"



void init_pc0(void) {
	// button 0
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef init_struct;
	init_struct.Pin = GPIO_PIN_0;
	init_struct.Mode = GPIO_MODE_INPUT;
	init_struct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &init_struct);
}

void init_pc1(void) {
	// button 1
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef init_struct;
	init_struct.Pin = GPIO_PIN_1;
	init_struct.Mode = GPIO_MODE_INPUT;
	init_struct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &init_struct);

}

void init_pa8(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODER8;
	GPIOA->MODER |= GPIO_MODER_MODER8_1;
	GPIOA->AFR[1] |= (2 << (0 * 4)); // af mode 2(b10), pin 8
}

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

int poll_pc0(void) {
    uint8_t val = (GPIOC->IDR & GPIO_IDR_0) >> 0;
    return val;
}

int poll_pc1(void) {
    uint8_t val = (GPIOC->IDR & GPIO_IDR_1) >> 1;
    return val;
}



void set_pin(uint8_t val, GPIO_TypeDef *gpio_typedef, uint8_t pin_num) {
    if (val == 1) {
        gpio_typedef->BSRR |= 1 << pin_num;
    } else if (val == 0) {
        gpio_typedef->BSRR |= 1 << (pin_num + 16);
    }
}

void set_pb13(uint8_t val) {
	set_pin(val, GPIOB, 13);
}

void set_pc6(uint8_t val) {
	set_pin(val, GPIOC, 6);
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
