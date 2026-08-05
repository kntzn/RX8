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
      startup/startup_stm32f303xc.s \
	  startup/isr.c
	  
	  
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

size:
	arm-none-eabi-size build/firmware.elf -A

flash-lab:
	scp build/firmware* lab01:~/Develop/RX8/build
	ssh lab01 st-flash --connect-under-reset write Develop/RX8/build/firmware.bin 0x8000000

debug-lab:
	scp build/firmware* lab01:~/Develop/RX8/build
	#ssh lab01 openocd -f interface/stlink.cfg -f target/stm32f3x.cfg -c "program /home/kntzn/Develop/RX8/build/firmware.hex verify reset exit"
	ssh lab01 st-flash --connect-under-reset write Develop/RX8/build/firmware.bin 0x8000000
	ssh lab01 openocd -f interface/stlink.cfg -f target/stm32f3x.cfg

console-lab:
	ssh -tt lab01 picocom -b 115200 /dev/ttyUSB0

debug:
	gdb-multiarch build/firmware.elf

flash:
	st-flash --connect-under-reset write build/firmware.bin 0x8000000

clean:
	find . -type f -name "*.o" -delete

.PHONY: all clean