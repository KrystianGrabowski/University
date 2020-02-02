#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB


#define BUFF_LEN 100
#define DELAY_LEN 10
#define DEBOUNCE_TIME 1000


void turn_led_on() {
  LED_PORT |= _BV(LED);
}

void turn_led_off() {
  LED_PORT &= ~_BV(LED);
}


int8_t next_iter(int8_t num) {
  if (num < BUFF_LEN - 1) {
    return ++num;
  }
  else{
    return 0;
  }
}

uint8_t debounce(void) {
  if (~BTN_PIN & _BV(BTN)) {
    _delay_us(DEBOUNCE_TIME);
    if (~BTN_PIN & _BV(BTN)) {
      return (1);
    }  
  }
  return (0);
}  

int main() {
  //Zadanie1
  LED_DDR = 0;
  BTN_PORT |= _BV(BTN);
  LED_DDR |= _BV(LED);

  int8_t buffer[BUFF_LEN];
  int16_t iter = 0;

  for(int i=0; i<BUFF_LEN; i++) {
    buffer[i] = 0;
  }

  while (1) {
    if (buffer[iter] != 0) {
      turn_led_on();
    }
    if(buffer[iter] == 0){
      turn_led_off();
    }
    buffer[iter] = 0;
    _delay_ms(DELAY_LEN);
    if (debounce()){
      buffer[iter] = 1;
    }
    iter = next_iter(iter);
  }
}