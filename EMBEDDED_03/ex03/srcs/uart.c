#include "uart.h"
#include "rgb.h"
#include <ctype.h>

uint8_t writePos = 0;
char buffer[BUFFER_SIZE];

void uart_tx(char c) {
  while (!(UCSR0A & (1 << UDRE0))) {
  }

  UDR0 = c;
}

void uart_printstr(const char *str) {
  uint8_t i = 0;

  while (str[i] != '\0') {
    uart_tx(str[i]);
    i++;
  }
}

void uart_clear(void) {
  UDR0 = 0;
  _delay_ms(25);
}

uint8_t check_buffer(void) {
  if (writePos < BUFFER_SIZE - 1) {
    return 0;
  }

  for (uint8_t i = 0; buffer[i] != '\0'; i++) {
    if (!isdigit(buffer[i]) && !isupper(buffer[i]) && !islower(buffer[i])) {
      return 0;
    }
  }

  return 1;
}

void uart_enter(void) {
  if (!check_buffer()) {
    uart_printstr("\r\nInvalid color given.\r\n");
  } else {
    set_red(buffer);
    set_green(buffer);
    set_blue(buffer);
    uart_printstr("\r\nColor was successfully changed.\r\n");
  }

  uart_printstr("\r\nEnter color: #");
  writePos = 0;
}

void init_uart(void) {
  UBRR0H = (UBRR >> 8);
  UBRR0L = UBRR;
  UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);
  UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

  buffer[BUFFER_SIZE - 1] = '\0';
  uart_printstr("Enter color: #");

  sei();
}

ISR(USART_RX_vect) {
  char c = UDR0;
  uart_clear();

  if (c == 127 && writePos > 0) {
    uart_printstr("\b \b");
    writePos--;
  } else if (c == 13) {
    uart_enter();
  } else if (writePos < BUFFER_SIZE - 1 && isalnum(c)) {
    buffer[writePos++] = c;
    uart_tx(c);
  }
}
