#include <avr/io.h>

int main(void) {
  DDRB = (1 << DDB1);
  TCCR1A = (1 << COM1A1) | (1 << WGM11);
  TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS12) | (1 << CS10);
  ICR1 = 15624;
  OCR1A = ICR1 / 10;

  while (1) {
  }
}
