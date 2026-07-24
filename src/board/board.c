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
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN |
                   RCC_AHBENR_GPIODEN;

                   //RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN |

    RCC->APB1ENR |= RCC_APB1ENR_UART5EN; //RCC_APB1ENR_USART2EN | 
    
    (void)RCC->AHBENR;
    (void)RCC->APB1ENR;
}

static void board_gpio_init ()
{
    // PC12 + PD2 set as UART5 (AF5 + AF5)
    GPIOC->MODER &= ~(3UL << GPIO_MODER_MODER12_Pos);
    GPIOC->MODER |=  (2UL << GPIO_MODER_MODER12_Pos);

    GPIOD->MODER &= ~(3UL << GPIO_MODER_MODER2_Pos);
    GPIOD->MODER |=  (2UL << GPIO_MODER_MODER2_Pos);

    GPIOC->AFR[1] &= ~(0xFUL << 16U);
    GPIOC->AFR[1] |= (5UL << 16U);
    GPIOD->AFR[0] &= ~(0xFUL << 8U);
    GPIOD->AFR[0] |= (5UL << 8U);
    
    GPIOC->OTYPER &= ~(1UL << 12U);
    GPIOC->PUPDR  &= ~(3UL << 24U);
    GPIOD->OTYPER &= ~(1UL << 2U);
    GPIOD->PUPDR  &= ~(3UL << 4U);

    /*
    // PA13 is configured as general output
    GPIOA->MODER &= ~(GPIO_MODER_MODER13_1 | GPIO_MODER_MODER13_0);
    GPIOA->MODER |= (GPIO_MODER_MODER13_0);
    GPIOA->OTYPER &= ~(1UL << 13U);
    GPIOA->PUPDR  &= ~(3UL << 26U);

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
