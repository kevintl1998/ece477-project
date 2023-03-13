#include "hardware/TFT_LCD.h"
#include "stm32f0xx.h"
#include "hardware/TFT_LCD_legacy.h"


void init_led_spi(void) {
//    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
//
//    GPIOB->MODER |= (1<<(8*2)) | (1<<(11*2)) | (1<<(14*2)); // PB8,PB11,PB14 => output
//
//    GPIOB->BSRR = 0x4900;
//
//    GPIOB->MODER |= (2<<(3*2)) | (2<<(5*2)); // PB3,PB5 => alternate function
//
//    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
//    SPI1->CR1 &= ~SPI_CR1_SPE;
//    SPI1->CR1 &= ~(SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2);
//    SPI1->CR1 |= SPI_CR1_MSTR;
//    SPI1->CR2 = SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2;
//    SPI1->CR1 |= SPI_CR1_SSM;
//    SPI1->CR1 |= SPI_CR1_SSI;
//    SPI1->CR1 |= SPI_CR1_SPE;



}


void init_lcd_spi(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    GPIOB->MODER |= (1<<(8*2)) | (1<<(11*2)) | (1<<(14*2)); // PB8,PB11,PB14 => output

    GPIOB->BSRR = 0x4900;

    GPIOB->MODER |= (2<<(3*2)) | (2<<(5*2)); // PB3,PB5 => alternate function

    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    SPI1->CR1 &= ~SPI_CR1_SPE;
    SPI1->CR1 &= ~(SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2);
    SPI1->CR1 |= SPI_CR1_MSTR;
    SPI1->CR2 = SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2;
    SPI1->CR1 |= SPI_CR1_SSM;
    SPI1->CR1 |= SPI_CR1_SSI;
    SPI1->CR1 |= SPI_CR1_SPE;
}


void init_tft_lcd() {
    init_lcd_spi();
    LCD_Setup();
}
