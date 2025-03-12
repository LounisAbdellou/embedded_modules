#include "analogue.h"
#include "led.h"
#include "rgb.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  uint8_t adc_value;

  init_rgb();
  init_led();
  init_analogue();

  while (1) {
    ADCSRA |= (1 << ADSC);
    while (!(ADCSRA & (1 << ADIF)))
      ;
    ADCSRA |= (1 << ADIF);
    adc_value = ADCH;
    wheel(adc_value);
    display_led(adc_value);
    _delay_ms(20);
  }
}
