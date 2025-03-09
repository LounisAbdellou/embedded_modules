#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

uint8_t isReleased = 1;

int main(void) {
  DDRB = (1 << DDB0);
  PCICR = (1 << PCIE2);
  PCMSK2 = (1 << PCINT18);

  sei();

  while (1) {
  }
}

ISR(PCINT2_vect) {
  _delay_ms(50);

  if (!isReleased) {
    PORTB ^= (1 << PB0);
    isReleased = 1;
  } else {
    isReleased = 0;
  }

  _delay_ms(50);
}
