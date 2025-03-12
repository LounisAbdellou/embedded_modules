#include "rgb.h"
#include <avr/io.h>

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {
  OCR0B = r;
  OCR0A = g;
  OCR2B = b;
}

void wheel(uint8_t pos) {
  pos = 255 - pos;

  if (pos < 85) {
    set_rgb(255 - pos * 3, 0, pos * 3);
  } else if (pos < 170) {
    pos = pos - 85;
    set_rgb(0, pos * 3, 255 - pos * 3);
  } else {
    pos = pos - 170;
    set_rgb(pos * 3, 255 - pos * 3, 0);
  }
}

void init_rgb(void) {
  DDRD = (1 << DDD5) | (1 << DDD6) | (1 << DDD3);

  TCCR0A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM01) | (1 << WGM00);
  TCCR0B = (1 << CS00);

  TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
  TCCR2B = (1 << CS20);
}
