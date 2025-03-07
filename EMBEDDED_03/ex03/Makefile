MCU = atmega328p
F_CPU = 16000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU) -Iincludes
TARGET = main

SRC_DIR = srcs

SRCS = $(addprefix $(SRC_DIR)/, main.c rgb.c uart.c)
OBJS = $(SRCS:.c=.o)

all: flash

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

hex: $(TARGET).hex

$(TARGET).hex: $(TARGET).bin
	$(OBJCOPY) -I binary -O ihex $< $@

flash: $(TARGET).hex
	avrdude -c arduino -p $(MCU) -P /dev/ttyUSB0 -b 115200 -U flash:w:$<

clean:
	rm -f srcs/*.o *.elf *.bin *.hex

.PHONY: all hex flash clean
