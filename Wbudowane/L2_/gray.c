#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#define RESET PB4
#define PREV PB3
#define NEXT PB2

#define BTN_DDR DDRB
#define BTN_PORT PORTB
#define BTN_PIN PINB

#define LED_DDR DDRD
#define LED_PORT PORTD

#define THRESHOLD 15
#define DEBOUNCE_TIME 1000

uint8_t debounce_reset(void) {
  if (~BTN_PIN & _BV(RESET)) {
    _delay_us(DEBOUNCE_TIME);
    if (~BTN_PIN & _BV(RESET)) {
      return (1); 
    }  
  }
  return (0);
}

uint8_t debounce_next(void) {
  if (~BTN_PIN & _BV(NEXT)) {
    _delay_us(DEBOUNCE_TIME);
    if (~BTN_PIN & _BV(NEXT)) {
      return (1); 
    }  
  }
  return (0);
}

uint8_t debounce_prev(void) {
  if (~BTN_PIN & _BV(PREV)) {
    _delay_us(DEBOUNCE_TIME);
    if (~BTN_PIN & _BV(PREV)) {
      return (1);
    }  
  }
  return (0);
}

uint8_t debounce_any(void) {
  uint8_t all_buttons = _BV(RESET) + _BV(PREV) + _BV(NEXT);
  if ((BTN_PIN & all_buttons) == all_buttons) {
    _delay_us(DEBOUNCE_TIME);                   /* button is pressed now */
    if (BTN_PIN & all_buttons) {
      return (1);                               /* still pressed */  
    }
  }
  return (0);
}

uint8_t BinaryToGray(uint8_t num)
{
    return num ^ (num >> 1);
}

int main() {
  //Zadanie3
  BTN_DDR = 0x00;
  BTN_PORT = 0xff;

  UCSR0B  &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR = 0xff;
  LED_PORT = 0xff;
  
  uint8_t push = 0;
  uint8_t iter = 0;
  while(1) {
    _delay_ms(10);
    if(debounce_reset()){
      LED_PORT = 0x00;
      iter = 0;
    }

    if(!push && debounce_next()){
      push = 1;
      if (iter == THRESHOLD){
        iter = 0;
      }
      else{
        iter += 1;
      }
      LED_PORT = BinaryToGray(iter);
    }

    if(!push && debounce_prev()){
      push = 1;
      if (iter == 0) {
        iter = THRESHOLD;
      }
      else{
        iter -= 1;
      }
    LED_PORT = BinaryToGray(iter);
    }

    if(debounce_any()){
        push = 0;
    }

  
  }

  return 0;
}