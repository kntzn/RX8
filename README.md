# RX8 - 8th gen receiver for eks8

# TODO:
1. event bitmask
2. hw_timer -> 500 Hz
3. runtime loop + budgets
4. control_input snapshot 
5. traction_control () + safe output
6. uart DMA + single control packet 
6.1. COM-TO-UART 
7. FSM + timeout+gfailsafe
8. DWT-profiler

# SRC structure
## BSP - board support protocol:
1. Configures GPIO
2. Configures RCC for peripherials (e.g. USART)

## MCAL - drivers for peripherials
1. GPIO
2. UART

## DRIVERS - modules' drivers (protocols, configuration)
1. HC12
2. CC1101
3. SD
4. ADXL

## CORE - High-level 
1. Event manager
2. FSM
3. Scheduler
4. Runtime

## Main:
1. Builds app:
1.1. Init BSP
1.2. Init MCAL
1.3. Init Drivers
1.4. Init Core
2. Starts Runtime