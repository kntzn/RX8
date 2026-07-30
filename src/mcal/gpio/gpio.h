#include <stdint.h>
#include <stdbool.h>

#include <stm32f303xc.h>

typedef struct 
{
    GPIO_TypeDef* port;
    uint32_t pin;
} gpio_t;

typedef enum 
{
    GPIO_PUSH_PULL = 0,
    GPIO_OPEN_DRAIN
} gpio_output_type_t;

typedef enum 
{
    GPIO_PULL_NONE = 0,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN
} gpio_pull_t;

typedef enum 
{
    GPIO_SPEED_LOW = 0,
    GPIO_SPEED_MEDIUM,
    GPIO_SPEED_HIGH
} gpio_speed_t;

typedef enum 
{
    GPIO_STATE_LOW = 0,
    GPIO_STATE_HIGH
} gpio_state_t;

bool gpio_input_init           (gpio_t*            self,
                                GPIO_TypeDef*      port,
                                uint32_t           pin);

bool gpio_input_init_advanced  (gpio_t*            self,
                                GPIO_TypeDef*      port,
                                uint32_t           pin,
                                gpio_pull_t        pull_type);

bool gpio_output_init          (gpio_t*            self, 
                                GPIO_TypeDef*      port, 
                                uint32_t           pin, 
                                gpio_state_t       initial_state);

bool gpio_output_init_advanced (gpio_t*            self,
                                GPIO_TypeDef*      port,
                                uint32_t           pin,
                                gpio_state_t       initial_state, 
                                gpio_output_type_t output_type,
                                gpio_pull_t        pull_type,
                                gpio_speed_t       speed);

bool gpio_af_init              (gpio_t*            self,
                                GPIO_TypeDef*      port,
                                uint32_t           pin,
                                uint32_t           af);

bool gpio_af_init_advanced     (gpio_t*            self,
                                GPIO_TypeDef*      port, 
                                uint32_t           pin, 
                                uint32_t           af, 
                                gpio_output_type_t output_type, 
                                gpio_pull_t        pull_type,
                                gpio_speed_t       speed);

bool gpio_analog_init          (gpio_t*            self,
                                GPIO_TypeDef*      port, 
                                uint32_t           pin);

gpio_state_t gpio_read (const gpio_t* self);

void gpio_write (const gpio_t* self, gpio_state_t level);

void gpio_toggle (const gpio_t* self);