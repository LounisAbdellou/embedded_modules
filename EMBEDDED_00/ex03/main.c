#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  int toggled;
  // target DDB0 in DDRB and set it in output
  DDRB = (1 << DDB0);

  while (1) {
    // check if DDD2 is true inside PIND and if
    // it has changed since the last loop iteration
    if (!(PIND & (1 << DDD2)) && toggled) {
      continue;
    } else if (!(PIND & (1 << DDD2)) && !toggled) {
      toggled = 1;
      // if pressed target PB0 in PORTB and invert its value
      PORTB ^= (1 << PB0);
      // add delay to prevent bounce effect;
      _delay_ms(250);
    } else {
      // else DDD2 has been released
      toggled = 0;
    }
  }
}
