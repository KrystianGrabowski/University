#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR DDRD
#define LED_PORT PORTD
#define DELAY_TIME 100

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

int main() {
  
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // program testowy
  UCSR0B  &= ~_BV(RXEN0) & ~_BV(TXEN0);
  LED_DDR = 0b11111111;

  //Wersja 1
  /*while(1) {
    for (int i=0; i<7; i++) {
      LED_PORT = (1 << i);
      _delay_ms(DELAY_TIME);
    }

    for (int i=7; i>0; i--) {
      LED_PORT = (1 << i);
      _delay_ms(DELAY_TIME);
    }
  }*/

  // Wersja 2
  while(1) {
    LED_PORT = 0b00000001;
    _delay_ms(DELAY_TIME);
    for (int i=1; i<3; i++) {
      LED_PORT |= (1 << i);
      _delay_ms(DELAY_TIME);
    }
    for (int i=1; i<8; i++) {
      LED_PORT = (LED_PORT << 1);
      _delay_ms(DELAY_TIME);
    }

    for (int i=1; i<3; i++) {
      LED_PORT |= (128 >> i);
      _delay_ms(DELAY_TIME);
    }
      for (int i=1; i<7; i++) {
      LED_PORT = (LED_PORT >> 1);
      _delay_ms(DELAY_TIME);
    }
  }
  return 0;
  


  
}
