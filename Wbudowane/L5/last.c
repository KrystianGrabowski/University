// Zadanie 4
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

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

int16_t iit = 0;
int32_t sec_iter = 0;

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

ISR(TIMER1_CAPT_vect) {
  iit++;
}

// procedura obsługi przerwania przepełnienia licznika counter2
ISR(TIMER2_OVF_vect) {
    sec_iter++;
  if (sec_iter == 60) {
    printf("Hz : %"PRId16"\r\n", iit);
    sec_iter = 0;
    iit=0;
  }
}

void timer1_init()
{
  TCCR1B = _BV(CS10);
  TIMSK1 |=_BV(ICIE1); 
  PORTB |= _BV(PB0);
}

void timer2_init()
{
  TCCR2B = _BV(CS20) | _BV(CS21) | _BV(CS22);
  TIMSK2 |= _BV(TOIE2);
}
FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj licznik
  timer1_init();
  timer2_init();
  // program testowy
  set_sleep_mode(SLEEP_MODE_IDLE);
  sei();

  while(1) {
    sleep_mode();
  }
}