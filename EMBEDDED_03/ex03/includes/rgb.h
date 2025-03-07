#ifndef RGB_H
#define RGB_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void init_rgb(void);
void set_red(char *color);
void set_green(char *color);
void set_blue(char *color);

#endif // !RGB_H
