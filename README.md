# RX8 - 8th gen receiver for eks8

## Project structure
- Sources
    - src
    - inc
    - .ld
    - Makefile
- Hardware
    - KiCad pro
    - KiCad sch
    - KiCad pcb
    - gerbers
- Misc
    - Renders
    - Img

## external dependencies
[cmsis-device-f1](https://github.com/STMicroelectronics/cmsis-device-f1/tree/master)
[CMSIS_5](https://github.com/ARM-software/CMSIS_5)

## gen 8 bring up plan
1. Bring-up RX MCU
    1.1. RCC setup
    1.2. 2xUART config
    1.3. PPM/PWM config
2. Bring-up TX MCU
    2.1. RCC setup
    2.2. ADC setup
    2.3. UART setup
3. Setup comm. proto
    3.1. SOF + LEN + PLD + CRC
    3.2. 

## Bring-up plan
1. Initialize Clocks
2. Init Peripherials
3. Test UART/SPI/PPM
4. Configure DMA
5. Configure timers
 
