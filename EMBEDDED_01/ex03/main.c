#include <avr/io.h>
#include <util/delay.h>

void setRegister(uint8_t mult) {
  OCR1A = (ICR1 / 10) * mult;
  _delay_ms(10);
}

int main(void) {
  DDRB = (1 << DDB1);
  TCCR1A = (1 << COM1A1) | (1 << WGM11);
  TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS12) | (1 << CS10);

  ICR1 = 15624;
  OCR1A = ICR1 / 10;

  uint8_t mult = 1;
  uint8_t isPressed = 0;
  while (1) {
    if (!(PIND & (1 << DDD2)) && mult < 10 && !isPressed) {
      isPressed = 1;
      setRegister(++mult);
    } else if (!(PIND & (1 << DDD4)) && mult > 1 && !isPressed) {
      isPressed = 1;
      setRegister(--mult);
    } else if ((PIND & (1 << DDD2)) && (PIND & (1 << DDD4))) {
      isPressed = 0;
    }
  }
}
