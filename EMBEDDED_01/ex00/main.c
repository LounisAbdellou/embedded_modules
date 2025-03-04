#include <avr/io.h>

int main(void) {
  DDRB = 1 << DDB1;
  unsigned long long counter = 0;

  while (1) {
    // use of a counter to match cpu clock cycles
    if (counter >= 320000) {
      // target PB1 in PORTB and switch its value on/off
      PORTB ^= (1 << PB1);
      counter = 0;
    }

    counter++;
  }
}
