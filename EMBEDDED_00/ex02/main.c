#include <avr/io.h>

int main(void) {
  // target DDB0 in DDRB and set it in output
  DDRB = (1 << DDB0);

  while (1) {
    // check if DDD2 is true inside PIND (has been pressed)
    if (!(PIND & (1 << DDD2))) {
      // if pressed target PB0 in PORTB and set it on
      PORTB |= (1 << PB0);
    } else {
      // if not pressed target PB0 in PORTB and set it off
      PORTB &= ~(1 << PB0);
    }
  }
}
