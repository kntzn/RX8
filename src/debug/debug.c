#include "debug.h"

#include "pinmap.h"
#include "gpio.h"

static gpio_t fault_pin;
static gpio_t realtime_pin;
static gpio_t rsrvd_pin;

void debug_init ()
{

    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    gpio_output_init (&fault_pin, DEBUG_PIN0_PORT, DEBUG_PIN0_PIN, GPIO_STATE_LOW);
    gpio_output_init (&realtime_pin, DEBUG_PIN1_PORT, DEBUG_PIN1_PIN, GPIO_STATE_LOW);
    gpio_output_init (&rsrvd_pin, DEBUG_PIN2_PORT, DEBUG_PIN2_PIN, GPIO_STATE_LOW);
}

void debug_raise_fault (fault_t fault)
{
    (void)fault;

    gpio_write (&fault_pin, GPIO_STATE_HIGH);
}

void debug_assertion_failed ()
{
    debug_raise_fault(FAULT_ASSERTION_FAILED);

    __disable_irq();

    while (true)
    {
    }
}