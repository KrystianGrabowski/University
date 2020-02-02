#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR DDRD
#define LED_PORT PORTD
#define DELAY_TIME 100

int main() {
  //Zadanie4
  UCSR0B  &= ~_BV(RXEN0) & ~_BV(TXEN0);
  DDRC = 0b00000011;
  PORTC = 0b00000001;
  int8_t dig[] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000};
  LED_DDR = 0b11111111;
  int8_t i = 5;
  int8_t j = 9;

  while(1) {
    
    for(int k=0; k<250; k++) {
      PORTC = 0b00000010;
      LED_PORT = dig[i];
      _delay_ms(2);
      PORTC = 0b00000001;
      LED_PORT = dig[j];
      _delay_ms(2);

    }
    j -= 1;
    if (j < 0) {
      j = 9;
    }
    if (j == 9) {
      i -= 1;
    }
    if (i < 0) {
      i = 5;
    }
  }

  return 0;
  


  
}
