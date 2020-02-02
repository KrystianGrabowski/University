#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

FILE uart_file;

int main() {
  UCSR0B  &= ~_BV(RXEN0) & ~_BV(TXEN0);
  DDRD = 0b11111111;

  //Wersja 1
  while(1) {
    for (int i=0; i<7; i++) {
      PORTD = (1 << i);
      _delay_ms(100);
    }

    for (int i=7; i>0; i--) {
      PORTD = (1 << i);
      _delay_ms(100);
    }
  }
  return 0;
  


  
}
