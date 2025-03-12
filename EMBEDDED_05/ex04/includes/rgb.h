#ifndef RGB_H
#define RGB_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void init_rgb(void);
void wheel(uint8_t pos);

#endif // !RGB_H
