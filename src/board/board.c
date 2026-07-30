#include <stdbool.h>
#include <stddef.h>
#include <stm32f303xc.h>
#include <pinmap.h>

#define BOARD_GPIO_INPUT  0U
#define BOARD_GPIO_OUTPUT 1U
#define BOARD_GPIO_AF     2U
#define BOARD_GPIO_ANALOG 3U


static void board_periph_clock_init (void);
static void board_gpio_init (void);

static bool board_configure_output (GPIO_TypeDef* port, 
                                    uint32_t      pin,
                                    uint32_t      output_type,
                                    uint32_t      pull_type,
                                    uint32_t      speed,
                                    uint32_t      initial_state);

static bool board_configure_input  (GPIO_TypeDef* port, 
                                    uint32_t      pin,
                                    uint32_t      pull_type);

static bool board_configure_af     (GPIO_TypeDef *port,
                                    uint32_t      pin,
                                    uint32_t      af,
                                    uint32_t      output_type,
                                    uint32_t      pull_type,
                                    uint32_t      speed);

static bool board_configure_analog (GPIO_TypeDef* port, 
                                    uint32_t      pin);

void board_init (void)
{
    // clock init
    // TODO

    // periph clock init
    board_periph_clock_init ();
    

    // gpio init
    board_gpio_init ();
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

static void board_gpio_init (void)
{
    /* --------- DBG PINS --------- */
    board_configure_output (DEBUG_PIN0_PORT,
                            DEBUG_PIN0_PIN,
                            DEBUG_PIN0_OTYPE,
                            DEBUG_PIN0_PULL,
                            DEBUG_PIN0_SPEED,
                            DEBUG_PIN0_STATE);

    board_configure_output (DEBUG_PIN1_PORT,
                            DEBUG_PIN1_PIN,
                            DEBUG_PIN1_OTYPE,
                            DEBUG_PIN1_PULL,
                            DEBUG_PIN1_SPEED,
                            DEBUG_PIN1_STATE);

    board_configure_output (DEBUG_PIN2_PORT,
                            DEBUG_PIN2_PIN,
                            DEBUG_PIN2_OTYPE,
                            DEBUG_PIN2_PULL,
                            DEBUG_PIN2_SPEED,
                            DEBUG_PIN2_STATE);

   /* ----------  HC-12 ---------- */
    board_configure_af (HC12_UART_PORT, 
                        HC12_UART_TX_PIN,
                        HC12_UART_TX_AF,
                        HC12_UART_TX_OTYPE,
                        HC12_UART_TX_PULL,
                        HC12_UART_TX_SPEED);

    board_configure_af (HC12_UART_PORT, 
                        HC12_UART_RX_PIN,
                        HC12_UART_RX_AF,
                        HC12_UART_RX_OTYPE,
                        HC12_UART_RX_PULL,
                        HC12_UART_RX_SPEED);
    
    board_configure_output (HC12_SET_PORT,
                            HC12_SET_PIN,
                            HC12_SET_OTYPE,
                            HC12_SET_PULL,
                            HC12_SET_SPEED,
                            HC12_SET_STATE);

    /* ---------- CONSOLE --------- */
    board_configure_af (CONSOLE_UART_PORT, 
                        CONSOLE_UART_TX_PIN,
                        CONSOLE_UART_TX_AF,
                        CONSOLE_UART_TX_OTYPE,
                        CONSOLE_UART_TX_PULL,
                        CONSOLE_UART_TX_SPEED);

    board_configure_af (CONSOLE_UART_PORT, 
                        CONSOLE_UART_RX_PIN,
                        CONSOLE_UART_RX_AF,
                        CONSOLE_UART_RX_OTYPE,
                        CONSOLE_UART_RX_PULL,
                        CONSOLE_UART_RX_SPEED);    

    
}

static bool board_configure_output (GPIO_TypeDef* port, 
                                    uint32_t      pin,
                                    uint32_t      output_type,
                                    uint32_t      pull_type,
                                    uint32_t      speed,
                                    uint32_t      initial_state)
{
    if ((port == NULL)      ||
        (pin >= 16U)        ||
        (output_type >= 2U) ||
        (pull_type >= 3U)   ||
        (speed >= 4U)       ||
        (initial_state >= 2U)) 
    {
        return false;
    }

    const uint32_t mode_pos = pin * 2U;

    if (initial_state != 0U)
        port->BSRR = 1UL << pin;
    else
        port->BSRR = 1UL << (pin + 16U);

    port->OTYPER &= ~(1UL << pin);
    port->OTYPER |=  (output_type << pin);

    port->PUPDR &= ~(3UL << mode_pos);
    port->PUPDR |=  (pull_type << mode_pos);

    port->OSPEEDR &= ~(3UL << mode_pos);
    port->OSPEEDR |=  (speed << mode_pos);

    port->MODER &= ~(3UL << mode_pos);
    port->MODER |=  (BOARD_GPIO_OUTPUT << mode_pos);

    return true;
}

static bool board_configure_input  (GPIO_TypeDef* port, 
                                    uint32_t      pin,
                                    uint32_t      pull_type)
{
    if ((port == NULL)      ||
        (pin >= 16U)        ||
        (pull_type >= 3U))
    {
        return false;
    }

    const uint32_t mode_pos = pin * 2U;

    port->PUPDR &= ~(3UL << mode_pos);
    port->PUPDR |=  (pull_type << mode_pos);

    port->MODER &= ~(3UL   << mode_pos);
    port->MODER |=  (BOARD_GPIO_INPUT << mode_pos);

    return true;
}

static bool board_configure_af     (GPIO_TypeDef* port,
                                    uint32_t      pin,
                                    uint32_t      af,
                                    uint32_t      output_type,
                                    uint32_t      pull_type,
                                    uint32_t      speed)
{
    if ((port == NULL)      ||
        (pin >= 16U)        ||
        (af >= 16U)         ||
        (output_type >= 2U) ||
        (pull_type >= 3U)   ||
        (speed >= 4U)) 
    {
        return false;
    }

    const uint32_t mode_pos = pin * 2U;
    const uint32_t af_pos   = (pin % 8U) * 4U;
    const uint32_t afr_idx  = pin / 8U;

    port->AFR[afr_idx] &= ~(0xFUL << af_pos);
    port->AFR[afr_idx] |=  (af << af_pos);

    port->OTYPER &= ~(1UL << pin);
    port->OTYPER |=  (output_type << pin);

    port->PUPDR &= ~(3UL << mode_pos);
    port->PUPDR |=  (pull_type << mode_pos);

    port->OSPEEDR &= ~(3UL << mode_pos);
    port->OSPEEDR |=  (speed << mode_pos);

    port->MODER &= ~(3UL << mode_pos);
    port->MODER |=  (BOARD_GPIO_AF << mode_pos);

    return true;
}

static bool board_configure_analog (GPIO_TypeDef* port, 
                                    uint32_t      pin)
{
    if ((port == NULL) ||
        (pin >= 16U))
    {
        return false;
    }

    const uint32_t mode_pos = pin * 2U;

    port->PUPDR &= ~(3UL << mode_pos);

    port->MODER &= ~(3UL << mode_pos);
    port->MODER |=  (BOARD_GPIO_ANALOG << mode_pos);

    return true;
}