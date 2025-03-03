MCU = atmega328p
F_CPU = 16000000UL  # Fréquence d'horloge (16 MHz)
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU)
TARGET = main

SRC_DIR = ./

SRCS = $(addprefix $(SRC_DIR)/, main.c)
OBJS = $(SRCS:.c=.o)

all: flash

# Règle pour générer le fichier .bin
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Règle pour générer le fichier .elf
$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Règle pour compiler les fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour générer le fichier .hex à partir du .bin
hex: $(TARGET).hex

$(TARGET).hex: $(TARGET).bin
	$(OBJCOPY) -I binary -O ihex $< $@

# Règle pour flasher le fichier .hex
flash: $(TARGET).hex
	avrdude -c arduino -p $(MCU) -P /dev/ttyUSB0 -b 115200 -U flash:w:$<

# Règle pour nettoyer le projet
clean:
	rm -f *.o *.elf *.bin *.hex

.PHONY: all hex flash clean
