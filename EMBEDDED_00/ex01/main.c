#include <avr/io.h>

int main(void) {
  // target DDB0 in DDRB and set it in output
  DDRB = (1 << DDB0);
  // target PB0 in PORTB and set it as on
  PORTB = (1 << PB0);
}
