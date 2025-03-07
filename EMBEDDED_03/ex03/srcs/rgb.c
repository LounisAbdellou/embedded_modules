#include "rgb.h"
#include <ctype.h>

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {
  OCR0B = r;
  OCR0A = g;
  OCR2B = b;
}

uint8_t hex_to_dec(char c) {
  if (isalpha(c) && isupper(c)) {
    return (c - 65) + 10;
  } else if (isalpha(c) && islower(c)) {
    return (c - 97) + 10;
  } else if (isdigit(c)) {
    return c - 48;
  }

  return 0;
}

void set_red(char *color) {
  uint8_t red = 0;

  red += hex_to_dec(color[0]);
  red += hex_to_dec(color[1]);

  OCR0B = red;
}

void set_green(char *color) {
  uint8_t green = 0;

  green += hex_to_dec(color[2]);
  green += hex_to_dec(color[3]);

  OCR0A = green;
}

void set_blue(char *color) {
  uint8_t blue = 0;

  blue += hex_to_dec(color[4]);
  blue += hex_to_dec(color[5]);

  OCR2B = blue;
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
