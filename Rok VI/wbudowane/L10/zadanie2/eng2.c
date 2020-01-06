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

void timer1_init()
{
  // ustaw tryb licznika
  // COM1A = 10   -- non-inverting mode
  // WGM1  = 1110 -- fast PWM top=ICR1
  // CS1   = 101  -- prescaler 1024
  // ICR1  = 15624
  // częstotliwość 16e6/(256*(1+99)) = 625 Hz
  // wzór: datasheet 20.12.3 str. 164
  ICR1 = 49;
  TCCR1A = _BV(COM1A1);
  TCCR1B = _BV(WGM13) | _BV(CS12);
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB |= _BV(PB1);
  TIMSK1 |= _BV(TOIE1) | _BV(ICIE1);
}

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
  ADCSRA |= _BV(ADIE); //Przerwania ADC
}

uint16_t data[16] = {3, 5, 7, 9, 11, 13, 15, 17, 20, 22, 24, 26, 28, 32, 35, 49};

ISR(TIMER1_OVF_vect) {
  ADCSRA |= _BV(ADSC);
  TIFR1 |= _BV(TOV1);
}

ISR(TIMER1_CAPT_vect) {
  ADCSRA |= _BV(ADSC);
  TIFR1 |= _BV(ICF1);
}

ISR(ADC_vect) {
  v = ADC;
  OCR1A = data[v>>6];
  ADCSRA |= _BV(ADIF);
  printf("%"PRIu32"mV\r\n", (uint32_t) (1024 * 1100 / (v | 1)));
}

FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  //uint16_t data[16] = {1, 2, 3, 4, 5 ,6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}; 

  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // uruchom licznik
  timer1_init();
  adc_init();
  sei();
  // ustaw wypełnienie 50%
  OCR1A = ICR1/2;
  set_sleep_mode(SLEEP_MODE_IDLE);

  while(1) {
    sleep_mode();
  }
}

