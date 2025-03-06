#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define RED (1 << PD5)
#define GREEN (1 << PD6)
#define BLUE (1 << PD3)

uint8_t i = 0;
int colors[] = {RED, GREEN, BLUE};

int main(void) {
  DDRD = (1 << DDD5) | (1 << DDD6) | (1 << DDD3);

  TCCR1A = (1 << COM1A0);
  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  OCR1A = 15625;

  sei();

  while (1) {
  }
}

ISR(TIMER1_COMPA_vect) {
  PORTD = colors[i++];

  if (i >= 3) {
    i = 0;
  }
}
