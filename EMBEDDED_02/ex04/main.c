#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define FCPU 16000000
#define BAUD 115200
#define UBRR FCPU / 16 / (BAUD - 1)
#define BUFFER_SIZE 128

#define USERNAME "solid"
#define PASSWORD "solid123"

int strcmp(const char *first, const char *second);
char *strcpy(char *destination, const char *source);

uint8_t writePos = 0;
uint8_t isStageTwo = 0;

char buffer[BUFFER_SIZE];
char usernameBuffer[BUFFER_SIZE];

void led_init() {
  DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB4);

  while (1) {
    PORTB ^= (1 << PB0);
    _delay_ms(500);
    PORTB ^= (1 << PB1);
    _delay_ms(500);
    PORTB ^= (1 << PB2);
    _delay_ms(500);
    PORTB ^= (1 << PB4);
    _delay_ms(500);
  }
}

void uart_init(void) {
  UBRR0H = (UBRR >> 8);
  UBRR0L = UBRR;
  UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);
  UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

  sei();
}

void uart_clear(void) {
  UDR0 = 0;
  _delay_ms(25);
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

void uart_reset(void) {
  writePos = 0;
  isStageTwo = 0;

  uart_printstr("Enter your login:\r\n");
  uart_printstr("\tusername: ");
}

void uart_enter(void) {
  if (!isStageTwo) {
    buffer[writePos] = '\0';
    strcpy(usernameBuffer, buffer);
    uart_printstr("\r\n\tpassword: ");
    isStageTwo = 1;
  } else if (strcmp(usernameBuffer, USERNAME) == 0 &&
             strcmp(buffer, PASSWORD) == 0) {
    uart_printstr("\r\nYou logged in successfully.\r\n");
    led_init();
  } else {
    uart_printstr("\r\nBad combinaison username/password.\r\n\r\n");
    uart_reset();
  }

  writePos = 0;
}

int main(void) {
  uart_init();
  uart_reset();

  while (1) {
  }
}

ISR(USART_RX_vect) {
  char c = UDR0;

  uart_clear();

  if (c == 127 && writePos > 0) {
    uart_printstr("\b \b");
    writePos--;
  } else if (c == 13 && writePos > 0) {
    uart_enter();
  } else if (writePos < BUFFER_SIZE - 1 && c >= 32 && c <= 126) {
    buffer[writePos++] = c;
    uart_tx(!isStageTwo ? c : '*');
  }
}
