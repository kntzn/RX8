# -----------------------------------------------------------
# Makefile для STM32L010F4P (Cortex-M0)
# -----------------------------------------------------------

# Компилятор и инструменты
CC      = /usr/bin/arm-none-eabi-gcc
LD      = /usr/bin/arm-none-eabi-gcc
OBJCOPY = /usr/bin/arm-none-eabi-objcopy

# MCU и флаги
MCU     = cortex-m4
#CFLAGS  = -mcpu=$(MCU) -mthumb -Wall -Og -g -ffunction-sections -fdata-sections -DSTM32F10X_MD -DSTM32F103xB
CFLAGS  = -mcpu=$(MCU) -mthumb -Wall -Wextra -Werror -Og -g -ffunction-sections -fdata-sections -DSTM32F30X_MD -DSTM32F303xC
LDFLAGS = -mcpu=$(MCU) -mthumb -Wl,--gc-sections

# Пути к заголовкам
INC_DIRS := $(shell find Core/Include Include src -type d 2>/dev/null)
INC := $(addprefix -I, $(INC_DIRS))

# Исходники

# Находит все файлы .c в папке src и её поддиректориях
SRCS := $(shell find src -type f -name "*.c" 2>/dev/null)

SRC = $(SRCS) \
      startup/startup_stm32f303xc.s
	  
	  
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
	$(LD) $(LDFLAGS) -Tlinker/STM32F303RB_FLASH.ld -o $@ $^
	$(OBJCOPY) -O ihex $@ build/firmware.hex
	$(OBJCOPY) -O binary $@ build/firmware.bin

# Компиляция C
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Компиляция ASM
%.o: %.s
	$(CC) $(CFLAGS) -x assembler-with-cpp -c $< -o $@

fondue-flash:
	echo "Not implemented"

debug:
	gdb-multiarch build/firmware.elf

flash:
	st-flash --connect-under-reset write build/firmware.bin 0x8000000

# Очистка (не трогаем исходники)
clean:
	find . -type f -name "*.o" -delete

.PHONY: all clean