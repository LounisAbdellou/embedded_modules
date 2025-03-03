#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

void displayByte(uint8_t byte) {
  uint8_t display = 0x00;

  // compare byte to led port if true set it as true in PORTB
  if (byte & (1 << PB0)) {
    display |= (1 << PB0);
  }

  if (byte & (1 << PB1)) {
    display |= (1 << PB1);
  }

  if (byte & (1 << PB2)) {
    display |= (1 << PB2);
  }

  // same here but had to swap right to match byte
  if (byte & ((1 << PB4) >> 1)) {
    display |= (1 << PB4);
  }

  PORTB = display;
  _delay_ms(250);
}

int main(void) {
  uint8_t byte = 0x00;
  // set all used led as output
  DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB4);

  while (1) {
    // check if DDD2 is true inside PIND
    if (!(PIND & (1 << DDD2))) {
      byte++;
      displayByte(byte);
      // check if DDD4 is true inside PIND
    } else if (!(PIND & (1 << DDD4))) {
      byte--;
      displayByte(byte);
    }
  }
}
