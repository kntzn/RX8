#include <stdbool.h>
#include <stddef.h>
#include <stm32f303xc.h>

#include "runtime.h"
#include "uart.h"
#include "board.h"
#include "gpio.h"
#include "pinmap.h"
#include "hc12.h"
#include "console.h"
#include "notification_manager.h"
#include "debug.h"
#include "byte_stream.h"

static bool application_init (void);

int main ()
{

    gpio_t dbg0;
    gpio_output_init (&dbg0, DEBUG_PIN0_PORT, DEBUG_PIN0_PIN, GPIO_STATE_LOW);

    if (!application_init())
        return 1;

    while (true)
    {
        notification_manager_dispatch();
        
        __WFI ();
    }    
    
    //runtime_run_once();    

    return 0;
}


static bool application_init (void)
{
    static gpio_t hc12_set;
    static hc12_t hc12;
    static console_t console;
    static uart_instance_t hc12_uart;
    static uart_instance_t console_uart;
    static byte_stream_t* hc12_stream;

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
    hc12_stream = uart_get_stream (&console_uart);

    // Drivers
    NVIC_ClearPendingIRQ (USART1_IRQn);
    NVIC_SetPriority (USART1_IRQn, 0);
    NVIC_EnableIRQ (USART1_IRQn);

    hc12_init (&hc12, &hc12_uart, &hc12_set);
    console_init (&console, hc12_stream);

    //notification_manager_register_callback (IRQ_EVENT_UART_2, NULL, NULL);
    //notification_manager_register_callback (IRQ_EVENT_UART_1, console_rx_callback, &console);

    uart_bind_rx_callback (&console_uart, 
        notification_manager_register_callback (console_rx_callback));


    // ----- Place init functions here ----- //
    __enable_irq();

    return true;
}
