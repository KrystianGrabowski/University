#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

uint16_t v;

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
}

void timer1_init()
{
  // ustaw tryb licznika
  // COM1A = 10   -- non-inverting mode
  // WGM1  = 1110 -- fast PWM top=ICR1
  // CS1   = 101  -- prescaler 1024
  // ICR1  = 15624
  // częstotliwość 16e6/(256*(1+99)) = 625 Hz
  // wzór: datasheet 20.12.3 str. 164
  ICR1 = 99;
  TCCR1A = _BV(COM1A1) | _BV(WGM11);
  TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS12);
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB |= _BV(PB1);
}

FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  uint16_t data[16] = {50, 35, 30, 20, 18 ,15, 12, 10, 10, 12, 15, 18, 20, 30, 35, 50}; 

  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // uruchom licznik
  timer1_init();
  adc_init();
  // ustaw wypełnienie 50%
  OCR1A = ICR1/2;
  DDRD |= _BV(PD4) | _BV(PD5);
  PORTD |= _BV(PD4);
  PORTD &= ~_BV(PD5);

  uint16_t v;
  uint16_t shifted;
  while(1) {
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    v = ADC; // weź zmierzoną wartość (0..1023)
    shifted = v>>6;
    if (shifted > 7) {
      PORTD |= _BV(PD4);
      PORTD &= ~_BV(PD5);
    }
    else {
      PORTD |= _BV(PD5);
      PORTD &= ~_BV(PD4);
    }
    OCR1A = data[shifted];
    printf("Odczytano: %"PRIu16"\r\n",  v>>6);
  }
}

