#include <avr/io.h>
#include <util/twi.h>

#define F_CPU 16000000
#define F_SCL 100000
#define BAUD 115200
#define UBRR F_CPU / 16 / (BAUD - 1)
#define BUFFER_SIZE 128

void uart_init(void) {
  UBRR0H = (UBRR >> 8);
  UBRR0L = UBRR;
  UCSR0B = (1 << TXEN0) | (1 << TXCIE0);
  UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
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

void i2c_init(void) { TWBR = (F_CPU / (F_SCL * 2)) - 8; }

void i2c_start(void) {
  TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTA);
  while (!(TWCR & (1 << TWINT)))
    ;
  uart_putnbr((TWSR & 0xF8), 16);
  uart_printstr("\r\n");

  TWDR = 0B01110000;
  TWCR = _BV(TWINT) | _BV(TWEN);
  while (!(TWCR & (1 << TWINT)))
    ;
  uart_putnbr((TWSR & 0xF8), 16);
  uart_printstr("\r\n");
}

void i2c_stop(void) {
  TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
  uart_putnbr((TWSR & 0xF8), 16);
  uart_printstr("\r\n");
}

int main(void) {
  i2c_init();
  uart_init();

  while (1) {
    i2c_start();
    i2c_stop();
  }
}
