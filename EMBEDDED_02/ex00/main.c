#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define FCPU 16000000
#define BAUD 115200
#define UBRR FCPU / 16 / (BAUD - 1)

void uart_init(void) {
  UBRR0H = (UBRR >> 8);
  UBRR0L = UBRR;
  UCSR0B = (1 << TXEN0);
  UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void uart_tx(char c) {
  while (!(UCSR0A & (1 << UDRE0))) {
  }

  UDR0 = c;

  _delay_ms(1000);
}

int main(void) {
  uart_init();

  while (1) {
    uart_tx('Z');
  }
}
