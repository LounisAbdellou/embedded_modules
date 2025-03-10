#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

uint8_t isFirstReleased = 1;
uint8_t isSecondReleased = 1;
uint8_t globalByte = 0;

void init(void) {
  DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB4);

  EICRA = (1 << ISC00);
  EIMSK = (1 << INT0);

  PCICR = (1 << PCIE2);
  PCMSK2 = (1 << PCINT20);

  sei();
}

void displayByte() {
  uint8_t display = 0x00;

  if (globalByte & (1 << PB0)) {
    display |= (1 << PB0);
  }

  if (globalByte & (1 << PB1)) {
    display |= (1 << PB1);
  }

  if (globalByte & (1 << PB2)) {
    display |= (1 << PB2);
  }

  if (globalByte & ((1 << PB4) >> 1)) {
    display |= (1 << PB4);
  }

  PORTB = display;
}

int main(void) {
  init();

  while (1) {
  }
}

ISR(INT0_vect) {
  _delay_ms(50);

  if (!isFirstReleased) {
    globalByte++;
    displayByte();
    isFirstReleased = 1;
  } else {
    isFirstReleased = 0;
  }

  _delay_ms(50);
}

ISR(PCINT2_vect) {
  _delay_ms(50);

  if (!isSecondReleased) {
    globalByte--;
    displayByte();
    isSecondReleased = 1;
  } else {
    isSecondReleased = 0;
  }

  _delay_ms(50);
}
