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
                    RCC_AHBENR_GPIOCEN |
                    RCC_AHBENR_GPIODEN;

    RCC->APB1ENR |= RCC_APB1ENR_UART5EN; //RCC_APB1ENR_USART2EN |
                   
}

static void board_gpio_init ()
{
    // PC12 + PD2 set as UART5 (AF5 + AF5)
    GPIOC->MODER &= ~(GPIO_MODER_MODER12_1 | GPIO_MODER_MODER12_0);
    GPIOC->MODER |= (GPIO_MODER_MODER12_1);
    GPIOD->MODER &= ~(GPIO_MODER_MODER2_1 | GPIO_MODER_MODER2_0);
    GPIOD->MODER |= (GPIO_MODER_MODER2_1);

    
    GPIOC->AFR[1] &= ~(15UL << GPIO_AFRH_AFRH4_Pos);
    GPIOC->AFR[1] |= (5UL << GPIO_AFRH_AFRH4_Pos);
    
    GPIOD->AFR[0] &= ~(15UL << GPIO_AFRL_AFRL2_Pos);
    GPIOD->AFR[0] |= (5UL << GPIO_AFRL_AFRL2_Pos);

    // PA13 is configured as general output
    //GPIOA->MODER &= ~(GPIO_MODER_MODER13_1 | GPIO_MODER_MODER13_0);
    //GPIOA->MODER |= (GPIO_MODER_MODER13_0);
    
    // PA14 + PA15 as UART2


}
