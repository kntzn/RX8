#include <stdbool.h>
#include <stddef.h>
#include <stm32f303xc.h>

#include "runtime.h"
#include "mcal/uart/uart.h"
#include "mcal/spi/spi.h"
#include "board.h"
#include "gpio.h"
#include "pinmap.h"
#include "hc12.h"
#include "console.h"

#include "debug.h"
#include "byte_stream.h"

#include "modules/command/command.h"

#include "core/notification_manager/notification_manager.h"
#include "core/event/event.h"

static bool application_init (void);

int main ()
{

    gpio_t dbg0;
    gpio_output_init (&dbg0, DEBUG_PIN0_PORT, DEBUG_PIN0_PIN, GPIO_STATE_LOW);

    if (!application_init())
        return 1;

    while (true)
    {
        // launch scheduled tasks
        // TODO: scheduler_run ();

        // launch handlers raised by hardware events
        notification_manager_dispatch();
        
        // launch handlers raised by software
        // TODO: event_manager ();
        event_dispatch (5);

        // launch low priority tasks
        // TODO: background ();

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
    static spi_instance_t cc1101_spi;

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
    spi_init (&cc1101_spi, SPI1);
    
    // Drivers
    hc12_init (&hc12, &hc12_uart, &hc12_set);
    console_init (&console, uart_get_stream (&console_uart));

    // ---------- Notification binding ---------- //

    // binding rx avil notification from uart to console
    uart_bind_rx_callback (&console_uart, 
        notification_manager_register_callback (console_rx_callback, &console));
    
    // ---------- Event binding ---------- //

    event_register_handler (EVENT_CONSOLE_LINE_READY, command_cli_callback, NULL);

    
    NVIC_ClearPendingIRQ (USART1_IRQn);
    NVIC_SetPriority (USART1_IRQn, 0);
    NVIC_EnableIRQ (USART1_IRQn);

    __enable_irq();

    return true;
}
