#include <analogue.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <uart.h>
#include <util/delay.h>

int main(void) {
  init_uart();
  init_analogue();

  while (1) {
    read_analogue(0);
    uart_putnbr(ADC, 10);
    uart_printstr(", ");

    read_analogue(1 << MUX0);
    uart_putnbr(ADC, 10);
    uart_printstr(", ");

    read_analogue(1 << MUX1);
    uart_putnbr(ADC, 10);
    uart_printstr("\r\n");

    _delay_ms(20);
  }
}
