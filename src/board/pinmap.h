#pragma once

/**
 * Pin Map Configuration File
 * Defines pinout of the exact board
 * 
 */

//#define PINMAP

#define YES 1
#define NO 0

#define INPUT  0U
#define OUTPUT 1U
#define AF     2U
#define ANALOG 3U

#define PUSH_PULL  0U
#define OPEN_DRAIN 1U

#define PULL_NONE 0U
#define PULL_UP   1U
#define PULL_DOWN 2U

#define SPEED_LOW  0U
#define SPEED_MED  1U
#define SPEED_HIGH 2U

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

// PC0 - DEBUG0
#define DEBUG_PIN0_PORT   GPIOC
#define DEBUG_PIN0_PIN    0U
#define DEBUG_PIN0_AF     0U
#define DEBUG_PIN0_OTYPE  0U
#define DEBUG_PIN0_PUPD   0U

// PC1 - DEBUG1
#define DEBUG_PIN0_PORT   GPIOC
#define DEBUG_PIN0_PIN    0U
#define DEBUG_PIN0_AF     0U
#define DEBUG_PIN0_OTYPE  0U
#define DEBUG_PIN0_PUPD   0U

// PC2 - DEBUG2

// PA0 - GPIO HC12 SET
// PA2 - USART2_TX HC12 
// PA3 - USART2_RX HC12 .............DMA

// PF4 - SS0 SPI1 - CC1101
// PA4 - SS1 SPI1 - ADXL
// PA5 - SCK_SPI1
// PA6 - MSIO_SPI1 .............DMA
// PA7 - MOSI_SPI1 .............DMA
// PC4 - EXTI GDO0 - CC1101
// PC5 - EXTI GDO2 - CC1101

// PB12 - SS SPI2   - SD CARD
// PB13 - SCK SPI2  - SD CARD
// PB14 - MISO SPI2 - SD CARD .............DMA
// PB15 - MOSI SPI2 - SD CARD .............DMA

// PA9  - USART1_TX - CONSOLE 
// PA10 - USART1_RX - CONSOLE

// PB10 - USART3_TX - BMS
// PB11 - USART3_RX - BMS

// PA13 - SWDIO
// PA14 - SWDCLK
// PB3  - SWO

// PC10 - UART4_TX     - VESC .............DMA
// PC11 - UART4_RX     - VESC .............DMA

// PC12 - UART5_TX     - 1Wire

// PB4 - TIM3_CH1      - PPM

// PA1 - TIM2_CH2 DMA  - WS2812B
// PB6 - TIM4_CH1 DMA  - WS2812B

// PB8 - CAN
// PB9 - CAN

// PC14 - OSC32
// PC15 - OSC32
// PF0  - OSC
// PF1  - OSC

#undef YES
#undef NO