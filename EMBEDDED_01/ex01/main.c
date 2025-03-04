#include <avr/io.h>

int main(void) {
  DDRB = (1 << DDB1);
  TCCR1A = (1 << COM1A0);
  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
  OCR1A = 7812.5;

  while (1) {
  }
}
