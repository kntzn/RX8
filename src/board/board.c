#include <stdbool.h>
#include <stddef.h>
#include <stm32f303xc.h>
#include <pinmap.h>

static void board_periph_clock_init (void);

void board_init (void)
{
    // clock init
    // TODO

    // periph clock init
    board_periph_clock_init ();
}

static void board_periph_clock_init (void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | 
                   RCC_AHBENR_GPIOBEN | 
                   RCC_AHBENR_GPIOCEN | 
                   RCC_AHBENR_GPIODEN |
                   RCC_AHBENR_GPIOEEN |
                   RCC_AHBENR_GPIOFEN;

    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
}
