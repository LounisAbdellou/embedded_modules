#ifndef UART_H
#define UART_H

#define FCPU 16000000
#define BAUD 115200
#define UBRR FCPU / 16 / (BAUD - 1)
#define BUFFER_SIZE 7

void init_uart(void);

#endif // !UART_H
