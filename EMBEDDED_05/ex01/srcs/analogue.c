#include <analogue.h>

void init_analogue(void) {
  ADMUX = (1 << REFS0) | (1 << ADLAR);
  ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
}

void read_analogue(uint8_t mux) {
  ADMUX = (1 << REFS0) | (1 << ADLAR) | mux;

  ADCSRA |= (1 << ADSC);
  while (!(ADCSRA & (1 << ADIF)))
    ;

  ADCSRA |= (1 << ADIF);
}
