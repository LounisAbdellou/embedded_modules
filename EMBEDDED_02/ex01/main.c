#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define FCPU 16000000
#define BAUD 115200
#define UBRR FCPU / 16 / BAUD
#define BUFFER_SIZE 128

uint8_t readPos;
uint8_t writePos;
char buffer[BUFFER_SIZE];

void uart_init(void) {
  UBRR0H = (UBRR >> 8);
  UBRR0L = UBRR;
  UCSR0B = (1 << TXEN0) | (1 << TXCIE0);
  UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void append(char c) {
  buffer[writePos++] = c;

  if (writePos >= BUFFER_SIZE) {
    writePos = 0;
  }
}

void write(char c[]) {}

void uart_printstr() {
  // "Hello World!\r\n"
}

int main(void) {
  uart_init();
  sei();

  while (1) {
    /* uart_printstr(); */
    /* _delay_ms(2000); */
  }
}

ISR(USART_TX_vect) {}
