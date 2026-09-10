#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <stm32f303xc.h>

#include "gpio.h"


// ---------- Private declarations ---------- //
static bool init_configure_output (GPIO_TypeDef* port, 
                                    uint32_t      pin,
                                    uint32_t      output_type,
                                    uint32_t      pull_type,
                                    uint32_t      speed,
                                    uint32_t      initial_state);

static bool init_configure_input  (GPIO_TypeDef* port, 
                                    uint32_t      pin,
                                    uint32_t      pull_type);

static bool init_configure_af     (GPIO_TypeDef *port,
                                    uint32_t      pin,
                                    uint32_t      af,
                                    uint32_t      output_type,
                                    uint32_t      pull_type,
                                    uint32_t      speed);

static bool init_configure_analog (GPIO_TypeDef* port, 
                                    uint32_t      pin);


// ---------- Public defenitions ---------- //

bool gpio_input_init (gpio_t* self, GPIO_TypeDef* port, uint32_t pin)
{
    if (self != NULL)
    {
        self->port = port;
        self->pin  = pin;
    }

    return init_configure_input (port, pin, GPIO_PULL_NONE);
}

bool gpio_input_init_advanced (gpio_t* self, GPIO_TypeDef* port, uint32_t pin, gpio_pull_t pull_type)
{
    if (self != NULL)
    {
        self->port = port;
        self->pin  = pin;
    }

    return init_configure_input (port, pin, (uint32_t)pull_type);
}

bool gpio_output_init (gpio_t* self, GPIO_TypeDef* port, uint32_t pin, gpio_state_t initial_state)
{
    if (self != NULL)
    {
        self->port = port;
        self->pin  = pin;
    }

    return init_configure_output (port, pin, GPIO_PUSH_PULL, GPIO_PULL_NONE, GPIO_SPEED_LOW,
                                  (uint32_t) initial_state);
}

bool gpio_output_init_advanced (gpio_t* self, GPIO_TypeDef* port, uint32_t pin, gpio_state_t initial_state, 
                                gpio_output_type_t output_type, gpio_pull_t pull_type, gpio_speed_t speed)
{
    if (self != NULL)
    {
        self->port = port;
        self->pin  = pin;
    }

    return init_configure_output (port, pin, (uint32_t) output_type, (uint32_t) pull_type,
                                  (uint32_t) speed, (uint32_t) initial_state);
}

bool gpio_af_init (gpio_t* self, GPIO_TypeDef* port, uint32_t pin, uint32_t af)
{
    if (self != NULL)
    {
        self->port = port;
        self->pin  = pin;
    }

    return init_configure_af (port, pin, af, GPIO_PUSH_PULL, GPIO_PULL_NONE, GPIO_SPEED_LOW);
}

bool gpio_af_init_advanced (gpio_t* self, GPIO_TypeDef* port, uint32_t pin, uint32_t af, 
                            gpio_output_type_t output_type, gpio_pull_t pull_type, gpio_speed_t speed)
{
    if (self != NULL)
    {
        self->port = port;
        self->pin  = pin;
    }

    return init_configure_af (port, pin, af, (uint32_t) output_type, (uint32_t) pull_type,
                              (uint32_t) speed);
}

bool gpio_analog_init (gpio_t* self, GPIO_TypeDef* port, uint32_t pin)
{
    if (self != NULL)
    {
        self->port = port;
        self->pin  = pin;
    }

    return init_configure_analog (port, pin);
}


gpio_state_t gpio_read (const gpio_t* self)
{
    if (!self)
        return GPIO_STATE_LOW;
    if ((self->port->IDR & (1U << self->pin)))
        return GPIO_STATE_HIGH;
    else
        return GPIO_STATE_LOW;
}

void gpio_write (const gpio_t* self, gpio_state_t level)
{
    if (self == NULL)
        return;

    if (level == GPIO_STATE_HIGH)
    {
        self->port->BSRR = (1UL << self->pin);
        return;
    }
    if (level == GPIO_STATE_LOW)
    {
        self->port->BSRR = (1UL << (self->pin + 16U));
        return;
    }
}

void gpio_toggle (const gpio_t* self)
{
    (void)self; // TODO
}

// ---------- Private Defenitions ---------- //


static bool init_configure_output (GPIO_TypeDef* port, 
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
    port->MODER |=  (GPIO_PIN_FUNCTION_OUTPUT << mode_pos);

    return true;
}

static bool init_configure_input  (GPIO_TypeDef* port, 
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
    port->MODER |=  (GPIO_PIN_FUNCTION_INPUT << mode_pos);

    return true;
}

static bool init_configure_af     (GPIO_TypeDef* port,
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
    port->MODER |=  (GPIO_PIN_FUNCTION_AF << mode_pos);

    return true;
}

static bool init_configure_analog (GPIO_TypeDef* port, 
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
    port->MODER |=  (GPIO_PIN_FUNCTION_ANALOG << mode_pos);

    return true;
}