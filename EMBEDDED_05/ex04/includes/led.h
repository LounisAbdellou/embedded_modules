#ifndef LED_H
#define LED_H

#include <avr/io.h>

void init_led(void);
void display_led(uint8_t byte);

#endif // LED_H
