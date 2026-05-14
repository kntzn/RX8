# -----------------------------------------------------------
# Makefile для STM32L010F4P (Cortex-M0)
# -----------------------------------------------------------

# Компилятор и инструменты
CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# MCU и флаги
MCU     = cortex-m3
CFLAGS  = -mcpu=$(MCU) -mthumb -Wall -Og -g -ffunction-sections -fdata-sections -DSTM32F10X_MD -DSTM32F103xB
LDFLAGS = -mcpu=$(MCU) -mthumb -Wl,--gc-sections

# Пути к заголовкам
INC = -I/home/kntzn/Develop/Common/CMSIS_5-develop/CMSIS/Core/Include \
	  -I/home/kntzn/Develop/Common/cmsis-device-f1-master/Include \
	  -Isrc \

# Исходники
SRC = src/main.c \
      startup/startup_stm32f103xb.s \
	  /home/kntzn/Develop/Common/cmsis-device-f1-master/Source/Templates/system_stm32f1xx.c \
      
# Объектные файлы
OBJ = $(SRC:.c=.o)
OBJ := $(OBJ:.s=.o)

# Название прошивки
TARGET = build/firmware.elf

# -----------------------------------------------------------
# Правила сборки
# -----------------------------------------------------------

all: $(TARGET)

# Линковка
$(TARGET): $(OBJ)
	@mkdir -p build
	$(LD) $(LDFLAGS) -Tlinker/STM32F103CB_FLASH.ld -o $@ $^
	$(OBJCOPY) -O ihex $@ build/firmware.hex
	$(OBJCOPY) -O binary $@ build/firmware.bin

# Компиляция C
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Компиляция ASM
%.o: %.s
	$(CC) $(CFLAGS) -x assembler-with-cpp -c $< -o $@
	
flash:
	st-flash --connect-under-reset write build/firmware.bin 0x8000000

# Очистка (не трогаем исходники)
clean:
	rm -rf build/*.elf \
		   build/*.hex \
		   build/*.bin

.PHONY: all clean