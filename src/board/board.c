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
                   RCC_AHBENR_GPIOCEN;

    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    (void)RCC->AHBENR;
    (void)RCC->APB1ENR;
    (void)RCC->APB2ENR;
}