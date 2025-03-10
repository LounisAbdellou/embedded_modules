#include <analogue.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <uart.h>
#include <util/delay.h>

int main(void) {
  init_uart();
  init_analogue();

  while (1) {
    ADCSRA |= (1 << ADSC);
    while (!(ADCSRA & (1 << ADIF)))
      ;
    ADCSRA |= (1 << ADIF);
    uart_putnbr(ADCH, 16);
    uart_printstr("\r\n");
    _delay_ms(20);
  }
}
