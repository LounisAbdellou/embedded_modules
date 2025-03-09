#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

uint8_t globalIncrement = 0;

void init(void) {
  DDRB = (1 << DDB1);

  TCCR0A = 0;
  TCCR0B = (1 << CS00) | (1 << CS02);
  TIMSK0 = (1 << TOIE0);

  TCCR1A = (1 << COM1A1) | (1 << WGM10);
  TCCR1B = (1 << WGM12) | (1 << CS10);

  sei();
}

int main(void) {
  init();

  while (1) {
  }
}

ISR(TIMER0_OVF_vect) {
  if (globalIncrement++ % 3 == 0) {
    if (globalIncrement > 30) {
      OCR1A -= 12;
    } else {
      OCR1A += 12;
    }
  }

  if (globalIncrement >= 60) {
    globalIncrement = 0;
  }
}
