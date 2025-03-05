#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define FCPU 16000000
#define BAUD 115200
#define UBRR FCPU / 16 / (BAUD - 1)
#define BUFFER_SIZE 128

void uart_init(void) {
  UBRR0H = (UBRR >> 8);
  UBRR0L = UBRR;
  UCSR0B = (1 << TXEN0) | (1 << TXCIE0);
  UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
  TIMSK1 = (1 << OCIE1A);
  OCR1A = 15624;
  sei();
}

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

int main(void) {
  uart_init();

  while (1) {
  }
}

ISR(TIMER1_COMPA_vect) { uart_printstr("Hello World!\r\n"); }
