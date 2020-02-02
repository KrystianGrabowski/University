// Zadanie 1
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/sleep.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BUFF_LEN 61
#define DEBOUNCE_TIME 1000

#define BTN PB4
#define BTN_DDR DDRB
#define BTN_PIN PINB
#define BTN_PORT PORTB


int8_t buffer[BUFF_LEN];
static int16_t iter = 0;

void io_init()
{
  
  // pull-up PB4
	BTN_DDR = 0;
	BTN_PORT |= _BV(BTN);

  // ustaw wyjście na PB5
  LED_DDR |= _BV(LED);
}

// inicjalizacja licznika 2
void timer2_init()
{
  // preskaler 1024
  TCCR2B = _BV(CS20) | _BV(CS21) | _BV(CS22);
  // odmaskowanie przerwania przepełnienia licznika
  TIMSK2 |= _BV(TOIE2);
}

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


ISR(TIMER2_OVF_vect) {
    if (buffer[iter] != 0) {
      turn_led_on();
    }
    if(buffer[iter] == 0){
      turn_led_off();
    }
    buffer[iter] = 0;
    if (debounce()){
      buffer[iter] = 1;
    }
    iter = next_iter(iter);
    printf("%"PRId8"\r\n", (BTN_PIN & _BV(BTN)) == 0);
}



int main()
{
	// 16000000÷1024 = 15625 cykli/s
	// liczik = 255 (8bit) <- co tyle przerwanie
	// więc 15625 / 255 = 61,274509804 ~ 61 el

  // zainicjalizuj wejścia/wyjścia
  io_init();

  // ustaw tryb uśpienia na tryb bezczynności
  set_sleep_mode(SLEEP_MODE_IDLE);

  // odmaskuj przerwania
  sei();

  for(int i=0; i<BUFF_LEN; i++) {
    buffer[i] = 0;
  }

  //zainicjalizuj timer
  timer2_init();

  while(1) {
    sleep_mode();
  }
}