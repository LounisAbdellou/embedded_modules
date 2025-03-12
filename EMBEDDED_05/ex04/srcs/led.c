#include "led.h"

void init_led(void) {
  DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB4);
}

void display_led(uint8_t byte) {
  uint8_t display = 0x00;

  if (byte >= 64) {
    display |= (1 << PB0);
  }

  if (byte >= 128) {
    display |= (1 << PB1);
  }

  if (byte >= 192) {
    display |= (1 << PB2);
  }

  if (byte >= 255) {
    display |= (1 << PB4);
  }

  PORTB = display;
}
