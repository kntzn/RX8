#pragma once

/**
 * Pin Map Configuration File
 * Defines pinout of the exact board
 * 
 */

//#define PINMAP

// Example

#define DEBUG_UART_INSTANCE USART2
#define DEBUG_UART_PORT     GPIOA
#define DEBUG_UART_TX_PIN   2U
#define DEBUG_UART_RX_PIN   3U
#define DEBUG_UART_RX_AF    7U
#define DEBUG_UART_TX_AF    7U

#define PPM_TIMER_INSTANCE  TIM2
#define PPM_TIMER_CHANNEL   1U
#define PPM_TIMER_PORT      GPIOA
#define PPM_TIMER_PIN       1U
#define PPM_TIMER_PIN_AF    1U