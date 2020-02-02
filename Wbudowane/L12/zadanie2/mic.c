#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <math.h>


#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

uint16_t v = 0;

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

void timer1_init() {
  // ustaw tryb licznika
  // COM1A = 10   -- non-inverting mode
  // WGM1  = 1110 -- fast PWM top=ICR1
  // CS1   = 101  -- prescaler 1024
  // ICR1  = 15624
  // częstotliwość 16e6/(256*(1+99)) = 625 Hz
  // wzór: datasheet 20.12.3 str. 164
  ICR1 = 1999;
  TCCR1A = _BV(COM1A1) | _BV(WGM11);
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB |= _BV(PB1);
}

ISR(ADC_vect){
  v = ADC; // weź zmierzoną wartość (0..1023)
  ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
  printf("ENTER");
}


ISR(TIMER1_OVF_vect){
  //ADCSRA |= _BV(ADSC); // konwersja ADC z portu ADC1
}

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0) | _BV(MUX0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D) | _BV(ADC1D);
  //DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
  ADCSRA |= _BV(ADIE); // przerwania ADC
}

FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();

  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  adc_init();
  set_sleep_mode(SLEEP_MODE_IDLE);
  sei();
  timer1_init();
  while(1) {
    sleep_mode();
    printf("Odczytano: %"PRIu16"\r\n",  v);
  }
}

