#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>


int main() {
  //Zadanie1
  DDRB = 0;
  PORTB |= _BV(PB4);
  DDRB |= _BV(PB5);

  int8_t buffer[100];
  int16_t iter = 0;

  for(int i=0; i<100; i++) {
    buffer[i] = 0;
  }

  while (1) {
    if (buffer[iter] != 0) {
      PORTB |= _BV(PB5);
    }
    if(buffer[iter] == 0){
      PORTB &= ~_BV(PB5);
    }
    buffer[iter] = 0;
    _delay_ms(10);
    if (~PINB & _BV(PB4)) {
      _delay_ms(1);
      if (~PINB & _BV(PB4)) {
        buffer[iter] = 1;
    }  
  }
    if (iter < 100 - 1) {
      ++iter;
    }
    else{
      iter = 0;
    }
  }
}