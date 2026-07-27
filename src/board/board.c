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
   /* ---------- USART2 ---------- */
    /* PA2 -> USART2_TX (AF7) */
    GPIOA->MODER &= ~(3UL << GPIO_MODER_MODER2_Pos);
    GPIOA->MODER |=  (2UL << GPIO_MODER_MODER2_Pos);

    /* PA3 -> USART2_RX (AF7) */
    GPIOA->MODER &= ~(3UL << GPIO_MODER_MODER3_Pos);
    GPIOA->MODER |=  (2UL << GPIO_MODER_MODER3_Pos);

    /* AF7 */
    GPIOA->AFR[0] &= ~(0xFUL << GPIO_AFRL_AFRL2_Pos);
    GPIOA->AFR[0] |=  (7UL   << GPIO_AFRL_AFRL2_Pos);

    GPIOA->AFR[0] &= ~(0xFUL << GPIO_AFRL_AFRL3_Pos);
    GPIOA->AFR[0] |=  (7UL   << GPIO_AFRL_AFRL3_Pos);

    /* Push-pull, no pull-up/down */
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_2 | GPIO_OTYPER_OT_3);
    GPIOA->PUPDR  &= ~((3UL << GPIO_PUPDR_PUPDR2_Pos) |
                    (3UL << GPIO_PUPDR_PUPDR3_Pos));


    /* ---------- HC12 SET ---------- */
    /* PA0 -> GPIO output */
    GPIOA->MODER &= ~(3UL << GPIO_MODER_MODER0_Pos);
    GPIOA->MODER |=  (1UL << GPIO_MODER_MODER0_Pos);

    GPIOA->OTYPER &= ~GPIO_OTYPER_OT_0;
    GPIOA->PUPDR  &= ~(3UL << GPIO_PUPDR_PUPDR0_Pos);

    /* SET = High (normal mode) */
    GPIOA->BSRR = GPIO_BSRR_BS_0;


    /* ---------- USART1 ---------- */
    /* PA9 -> USART1_TX (AF7) */
    GPIOA->MODER &= ~(3UL << GPIO_MODER_MODER9_Pos);
    GPIOA->MODER |=  (2UL << GPIO_MODER_MODER9_Pos);

    GPIOA->AFR[1] &= ~(0xFUL << GPIO_AFRH_AFRH1_Pos);
    GPIOA->AFR[1] |=  (7UL   << GPIO_AFRH_AFRH1_Pos);

    /* PA10 -> USART1_RX (AF7) */
    GPIOA->MODER &= ~(3UL << GPIO_MODER_MODER10_Pos);
    GPIOA->MODER |=  (2UL << GPIO_MODER_MODER10_Pos);

    GPIOA->AFR[1] &= ~(0xFUL << GPIO_AFRH_AFRH2_Pos);
    GPIOA->AFR[1] |=  (7UL   << GPIO_AFRH_AFRH2_Pos);

    /* Push-pull, no pull-up/down */
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_9 | GPIO_OTYPER_OT_10);
    GPIOA->PUPDR  &= ~((3UL << GPIO_PUPDR_PUPDR9_Pos) |
                   (3UL << GPIO_PUPDR_PUPDR10_Pos));
    


}
