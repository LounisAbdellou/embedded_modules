#include "uart.h"

void uart_tx(char c) {
  while (!(UCSR0A & (1 << UDRE0))) {
  }

  UDR0 = c;
}

void uart_putnbr(int nbr, uint8_t base) {
  unsigned int nb = nbr;

  if (nbr < 0) {
    nb = -nbr;
    uart_tx('-');
  }

  if (nbr >= base) {
    uart_putnbr(nb / base, base);
    uart_putnbr(nb % base, base);
  } else {
    uart_tx(nb + (nb >= 10 ? 87 : 48));
  }
}

void uart_printstr(const char *str) {
  uint8_t i = 0;

  while (str[i] != '\0') {
    uart_tx(str[i]);
    i++;
  }
}

void init_uart(void) {
  UBRR0H = (UBRR >> 8);
  UBRR0L = UBRR;
  UCSR0B = (1 << TXEN0);
  UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}
