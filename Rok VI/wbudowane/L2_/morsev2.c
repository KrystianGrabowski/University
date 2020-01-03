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
#define RATE 1000
#define EPSILON 1000;

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

FILE uart_file;

void turn_led_on() {
  LED_PORT |= _BV(LED);
}

void turn_led_off() {
  LED_PORT &= ~_BV(LED);
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

char decode(char morse_code[], int8_t len) {
  const char *letter = "**ETIANMSURWDKGOHVF?L?PJBXCYZQ??";
  int iter = 1;
  for(int i=0; i<len; i++) {
    if(morse_code[i] == '.') {
      iter = 2 * iter;
    } 
    else{
      iter = 2 * iter + 1;
    }
  }
  return letter[iter];
}

int low(int x) {
  return x - EPSILON;
}

int high(int x) {
  return x + EPSILON;
}

void wink() {
  turn_led_on();
  _delay_ms(DELAY_LEN);
  turn_led_off();
}

int main() {
    //Zadanie2
    // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  LED_DDR = 0;
  BTN_PORT |= _BV(BTN);
  LED_DDR |= _BV(LED);

  char buffer[BUFF_LEN];
  int16_t iter = 0;
  int8_t push = 0;
  int16_t ms = 0;
  int8_t flag;

  while (1) {
    flag = 0;
    if (push && ms >= low(3 * RATE) && ms < 3 * RATE) {
      wink();
      flag = 1;
    }

    if (!push && ms >= low(3 * RATE) && ms < 3 * RATE) {
      wink();
      flag = 1;
    }

    if (!push && ms >= low(7 * RATE) && ms < 7 * RATE) {
      wink();
      flag = 1;
    }

    if(!flag) {
      _delay_ms(DELAY_LEN);
    }

    
    ms += 10;
    if (BTN_PIN & _BV(BTN) && push){
      push = 0;
      if (ms > low(1 * RATE) && ms < high(1 * RATE)) {
        buffer[iter] = '.';
        iter += 1;
      }
      if (ms > low(3 * RATE) && ms < high(3 * RATE)) {
        buffer[iter] = '-';
        iter += 1;
      }
      ms = 0;
      if (iter >= 4)
        printf("buffer error");
    }
    if(debounce() && !push){
      push = 1;
      if (ms > low(1 * RATE) && ms < high(1 * RATE)) {
      }
      if (ms > low(3 * RATE) && ms < high(3 * RATE)) {
        printf("%c", decode(buffer, iter));
        iter = 0;
      }
      if (ms > low(7 * RATE) && ms < high(7 * RATE)) {
        printf("%c", decode(buffer, iter));
        printf(" ");
        iter = 0;
        
      }
      ms = 0;
    }
    
    
  }
  return 0;
}