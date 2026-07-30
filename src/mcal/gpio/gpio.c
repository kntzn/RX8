#include <stdint.h>
#include <stdbool.h>

#include <stm32f303xc.h>

#include "gpio.h"

bool gpio_input_init           (gpio_t*            self,
                                GPIO_TypeDef*      port,
                                uint32_t           pin)
{
    self->port = port;
    self->pin  = pin;
}

bool gpio_input_init_advanced  (gpio_t*            self,
                                GPIO_TypeDef*      port,
                                uint32_t           pin,
                                gpio_pull_t        pull_type)
{
    self->port = port;
    self->pin  = pin;
}

bool gpio_output_init          (gpio_t*            self, 
                                GPIO_TypeDef*      port, 
                                uint32_t           pin, 
                                gpio_state_t       initial_state)
{
    self->port = port;
    self->pin  = pin;
}

bool gpio_output_init_advanced (gpio_t*            self,
                                GPIO_TypeDef*      port,
                                uint32_t           pin,
                                gpio_state_t       initial_state, 
                                gpio_output_type_t output_type,
                                gpio_pull_t        pull_type,
                                gpio_speed_t       speed)
{
    
}

bool gpio_af_init              (gpio_t*            self,
                                GPIO_TypeDef*      port,
                                uint32_t           pin,
                                uint32_t           af)
{
    
}

bool gpio_af_init_advanced     (gpio_t*            self,
                                GPIO_TypeDef*      port, 
                                uint32_t           pin, 
                                uint32_t           af, 
                                gpio_output_type_t output_type, 
                                gpio_pull_t        pull_type,
                                gpio_speed_t       speed)
{
    
}

bool gpio_analog_init          (gpio_t*            self,
                                GPIO_TypeDef*      port, 
                                uint32_t           pin)
{
    
}

gpio_state_t gpio_read (const gpio_t* self)
{
    
}

void gpio_write (const gpio_t* self, gpio_state_t level)
{
    
}

void gpio_toggle (const gpio_t* self)
{
    
}