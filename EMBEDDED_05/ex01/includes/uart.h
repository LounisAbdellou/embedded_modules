#ifndef UART_H
#define UART_H

#include <avr/io.h>

#define FCPU 16000000
#define BAUD 115200
#define UBRR FCPU / 16 / (BAUD - 1)

void init_uart(void);
void uart_tx(char c);
void uart_putnbr(int nbr, uint8_t base);
void uart_printstr(const char *str);

#endif // !UART_H
