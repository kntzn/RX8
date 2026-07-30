#include <stdbool.h>
#include <stddef.h>
#include <stm32f303xc.h>

#include "runtime.h"
#include "uart.h"
#include "board.h"
#include "gpio.h"
#include "pinmap.h"
#include "hc12.h"

static bool application_init (void);

// TODO!!!!
static uart_instance_t hc12_uart;
static uart_instance_t console_uart;

int main ()
{
    if (!application_init())
        return 1;

    uint32_t idx = 0;
    uint8_t buffer [128] = {};

    uart_instance_t* UART = &console_uart;
    uart_instance_t* HC_UART = &hc12_uart;

    while (true)
    {
        if (uart_ready (UART))
        {
            uint8_t byte = uart_read_byte (UART);
            
            if (byte != 0x7F)
            {
                uart_write_byte (UART, byte);
                buffer [idx] = byte;          
                idx++;
            }
            else
            {
                idx--;
                uart_write_blocking (UART, (uint8_t*)"\b \b", 3);
            }
            

            if (byte == '\r')
            {
                uart_write_byte (UART, '\n');


                uart_write_blocking (UART, buffer, idx);
                uart_write_byte (UART, '\n');

                uart_write_blocking (HC_UART, buffer, idx);

                idx = 0;
            }
        }
    }    
    
    //runtime_run_once();    

    return 0;
}


static bool application_init (void)
{
    static gpio_t hc12_set;
    static hc12_t hc12;


    __disable_irq();
    // ----- Place init functions here ----- //

    board_init ();

    // GPIO
    gpio_output_init (&hc12_set, HC12_SET_PORT, HC12_SET_PIN, GPIO_STATE_HIGH);
    gpio_af_init (NULL, HC12_UART_PORT, HC12_UART_RX_PIN, HC12_UART_RX_AF);
    gpio_af_init (NULL, HC12_UART_PORT, HC12_UART_TX_PIN, HC12_UART_TX_AF);

    gpio_af_init (NULL, CONSOLE_UART_PORT, CONSOLE_UART_RX_PIN, CONSOLE_UART_RX_AF);
    gpio_af_init (NULL, CONSOLE_UART_PORT, CONSOLE_UART_TX_PIN, CONSOLE_UART_TX_AF);

    // Periph
    uart_init (&console_uart, CONSOLE_UART_INSTANCE, SystemCoreClock, 115200);
    uart_init (&hc12_uart, HC12_UART_INSTANCE, SystemCoreClock, 9600);

    // Drivers
    hc12_init (&hc12, &hc12_uart, &hc12_set);



    // ----- Place init functions here ----- //
    __enable_irq();

    return true;
}