// Zadanie 2
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/sleep.h>


#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
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

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
  ADCSRA |= _BV(ADIE); //Auto Adc_vect
  ADCSRA |= _BV(ADATE); //Auto trigger

  ADCSRB |= _BV(ADTS1); // External Interrupt Request 0
}

FILE uart_file;

void io_init()
{
  // ustaw pull-up na PD2 i PD3 (INT0 i INT1)
  PORTD |= _BV(PORTD2);
  // ustaw wyzwalanie przerwania na INT0 i INT1 zboczem narastającym
  EICRA |= _BV(ISC00) | _BV(ISC01);
  // odmaskuj przerwania dla INT0 i INT1
  EIMSK |= _BV(INT0);
}

int16_t adc_value = 0;

ISR(INT0_vect) {
}

ISR(ADC_vect) {
  ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
  adc_value = ADC;
}


int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  io_init();
  sei();



  // zainicjalizuj ADC
  adc_init();
  // mierz napięcie
  while(1) {
    uint16_t vcc = 0;
    uint16_t res = 0;
    vcc = (adc_value / 1024.0 )* 5000.0;

    res = (10000 * 5000.0 / vcc) - 10000;
    printf("Odczytano: %"PRIu16" przy adc: %"PRIu16"\r\n", res, vcc);
  }
}