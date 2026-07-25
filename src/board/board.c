#include <stm32f303xc.h>
#include <pinmap.h>

static void board_periph_clock_init ();
static void board_gpio_init ();

void board_init ()
{
    // clock init
    board_periph_clock_init ();
    // periph clock init

    // gpio init
    board_gpio_init ();
}



static void board_periph_clock_init ()
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

static void board_gpio_init ()
{
    // PA2 & PA3 as USART2 (AF7)

    // Set as AF
    GPIOA->MODER &= ~(3UL << GPIO_MODER_MODER2_Pos);
    GPIOA->MODER |=  (2UL << GPIO_MODER_MODER2_Pos);

    GPIOA->MODER &= ~(3UL << GPIO_MODER_MODER3_Pos);
    GPIOA->MODER |=  (2UL << GPIO_MODER_MODER3_Pos);

    // Set AF7
    GPIOA->AFR[0] &= ~(0xFUL << 8U);
    GPIOA->AFR[0] |= (7UL << 8U);
    GPIOA->AFR[0] &= ~(0xFUL << 12U);
    GPIOA->AFR[0] |= (7UL << 12U);
    
    // Clear push-pull
    GPIOA->OTYPER &= ~(1UL << 3U);
    GPIOA->PUPDR  &= ~(3UL << 6U);
    GPIOA->OTYPER &= ~(1UL << 2U);
    GPIOA->PUPDR  &= ~(3UL << 4U);

    
    // PB3 is configured as general output
    GPIOB->MODER &= ~(3UL << GPIO_MODER_MODER3_Pos);
    GPIOB->MODER |=  (1UL << GPIO_MODER_MODER3_Pos);
    GPIOB->OTYPER &= ~(1UL << 3U);
    GPIOB->PUPDR  &= ~(3UL << 6U);

    GPIOB->BSRR = GPIO_BSRR_BS_3;

    /*
    // PA14 + PA15 as UART2
    GPIOA->MODER &= ~(3UL << GPIO_MODER_MODER14_Pos);
    GPIOA->MODER |=  (2UL << GPIO_MODER_MODER14_Pos);

    GPIOA->MODER &= ~(3UL << GPIO_MODER_MODER15_Pos);
    GPIOA->MODER |=  (2UL << GPIO_MODER_MODER15_Pos);

    GPIOA->AFR[1] &= ~(0xFUL << 28U);
    GPIOA->AFR[1] |= (5UL << 28U);
    GPIOA->AFR[1] &= ~(0xFUL << 24U);
    GPIOA->AFR[1] |= (5UL << 24U);
    
    GPIOA->OTYPER &= ~(1UL << 14U);
    GPIOA->PUPDR  &= ~(3UL << 28U);
    GPIOA->OTYPER &= ~(1UL << 15U);
    GPIOA->PUPDR  &= ~(3UL << 30U);
 */
}
