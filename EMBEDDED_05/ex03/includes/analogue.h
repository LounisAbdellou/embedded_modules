#ifndef ANALOGUE_H
#define ANALOGUE_H

#include <avr/io.h>

void init_analogue(void);
void read_analogue(uint8_t mux);

#endif // !ANALOGUE_H
