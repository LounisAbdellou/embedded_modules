#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void init_analogue(void) {
  ADMUX = (1 << REFS0) | (1 << ADLAR);
  ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
}
