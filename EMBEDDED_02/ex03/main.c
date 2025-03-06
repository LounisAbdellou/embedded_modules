#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define FCPU 16000000
#define BAUD 115200
#define UBRR FCPU / 16 / (BAUD - 1)

void uart_init(void) {
  UBRR0H = (UBRR >> 8);
  UBRR0L = UBRR;
  UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);
  UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

  sei();
}

void uart_tx(char c) {
  while (!(UCSR0A & (1 << UDRE0))) {
  }

  if (isupper(c))
    UDR0 = c + 32;
  else if (islower(c))
    UDR0 = c - 32;
  else
    UDR0 = c;

  _delay_ms(25);
}

void uart_clear(void) {
  UDR0 = 0;
  _delay_ms(25);
}

int main(void) {
  uart_init();

  while (1) {
  }
}

ISR(USART_RX_vect) {
  char c = UDR0;

  uart_clear();
  uart_tx(c);
}
