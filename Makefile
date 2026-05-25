# -----------------------------------------------------------
# Makefile для STM32L010F4P (Cortex-M0)
# -----------------------------------------------------------

# Компилятор и инструменты
CC      = /usr/bin/arm-none-eabi-gcc
LD      = /usr/bin/arm-none-eabi-gcc
OBJCOPY = /usr/bin/arm-none-eabi-objcopy

# MCU и флаги
MCU     = cortex-m3
CFLAGS  = -mcpu=$(MCU) -mthumb -Wall -Og -g -ffunction-sections -fdata-sections -DSTM32F10X_MD -DSTM32F103xB
LDFLAGS = -mcpu=$(MCU) -mthumb -Wl,--gc-sections

# Пути к заголовкам
INC = -ICore/Include \
	  -IInclude \
	  -Isrc \
	  -Isrc/core/event_queue \

# Исходники
SRC = src/main.c \
	  src/system_stm32f1xx.c \
      startup/startup_stm32f103xb.s \
	  src/core/event_queue/evqueue.c
	  
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

local:
	/usr/bin/gcc-11 src/test.c src/core/queue.c -Isrc/core/ -o build/test_run

flash:
	st-flash --connect-under-reset write build/firmware.bin 0x8000000

# Очистка (не трогаем исходники)
clean:
	rm -rf build/*.elf \
		   build/*.hex \
		   build/*.bin \
		   src/*.o

.PHONY: all clean