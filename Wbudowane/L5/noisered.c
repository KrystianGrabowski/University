// Zadanie 3
#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>

#include <avr/interrupt.h>
#include <stdlib.h>
#include <avr/sleep.h>

#define SAMPLE_SIZE 50
#define LOOP_SIZE 5
#define DEAD_LOOP_SIZE 10

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

FILE uart_file;

// inicjalizacja ADC
void adc_init()
{
  ADMUX = _BV(REFS0);
  //1.1V
  ADMUX |= _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
  ADCSRA |= _BV(ADIE); // Auto Adc_vect
}

void sleep_mode_init() {
  SMCR |= _BV(SE) | _BV(SM0);
}

volatile int32_t vcc = 0;
volatile int32_t buffer[SAMPLE_SIZE];


// OBLICZENIE WARIANCJI
int32_t count_var() {
  int32_t sum = 0;
  for(uint16_t i=0; i<SAMPLE_SIZE; i++) {
    sum += buffer[i];
  }
  int32_t avg = sum / SAMPLE_SIZE;
  int32_t result = 0;
  for (uint16_t i=0; i<SAMPLE_SIZE; i++) {
    int32_t val = (buffer[i] - avg);
    result += val * val;
  }
  return result/SAMPLE_SIZE;
}

// ODCZYT WARTOSCI 
ISR(ADC_vect) {
  ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
  vcc = 1125300L / ADC;
}

void regular_read() {
  ADCSRA |= _BV(ADSC); // wykonaj konwersję
  while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
  ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
  vcc = 1125300L / ADC;
}

// SERIE OCZYTÓW Z ORAZ BEZ NOISE REDUCTION
void adc_read() {
  for (uint16_t i=0; i<SAMPLE_SIZE; i++) {
    regular_read();
    buffer[i] = vcc;
  }
  printf("Regular: %"PRId32"\r\n", count_var());
  _delay_ms(100); 
}

void adc_read_noise_reduction() {
  for(uint16_t i=0; i<SAMPLE_SIZE; i++) {
    sleep_mode();
    cli();
    buffer[i] = vcc;
    sei();
  }
  printf("Noise:   %"PRId32"\r\n", count_var());
  _delay_ms(100);
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj ADC
  adc_init();
  // tryb uspienia
  sleep_mode_init();

  for (int16_t i=0; i<DEAD_LOOP_SIZE; i++) {
    regular_read();
  }

    cli();
    adc_read();
    sei();
    adc_read_noise_reduction();

  return 0;
}

/*void adc_read() {
  ADCSRA &= ~_BV(ADIE);
  regular_read();
  regular_read();
  regular_read();
  int32_t avg = 0;
  int32_t sum = 0;
  for (int i=0; i<SAMPLE_SIZE; i++) {
    regular_read();
    sum += (vcc * vcc);
    printf(", %"PRId32, vcc);
    avg += vcc;
    _delay_ms(100);  
  }
  sum /= SAMPLE_SIZE;
  avg /= SAMPLE_SIZE;
  int32_t result = sum - (avg * avg); 
  printf("Regular : %"PRId32"\r\n", sum);
  printf("Regular : %"PRId32"\r\n", avg * avg);
  printf("Regular : %"PRId32"\r\n", result);
}*/
