#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "pid.h"
#include <util/delay.h>
#include <avr/sleep.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

int16_t regulator = 0;

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
  ICR1 = 1023;
  TCCR1A = _BV(COM1A1);
  TCCR1B = _BV(WGM13) | _BV(CS11);
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB |= _BV(PB1);
}

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D) | _BV(ADC1D);
  //DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

// #define K_P     0.6
// #define K_I     0.005
// #define K_D     0.001

// #define K_P 3
// #define K_I 0.5
// #define K_D 0.05

#define K_P 0.3
#define K_I 0.01
#define K_D 0.5

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

struct GLOBAL_FLAGS {
  uint8_t pidTimer:1;
  uint8_t dummy:7;
} gFlags = {1, 7};

struct PID_DATA pidData;

#define TIME_INTERVAL   157

volatile uint16_t ida = 0;

ISR(TIMER0_OVF_vect){
  if(ida < TIME_INTERVAL)
    ida++;
  else{
    gFlags.pidTimer = TRUE;
    ida = 0;
  }
}

//uint16_t data[16] = {0, 5, 7, 9, 11, 13, 15, 17, 20, 22, 24, 26, 28, 32, 35, 49};

void Init(void)
{
  pid_Init(K_P * SCALING_FACTOR, K_I * SCALING_FACTOR , K_D * SCALING_FACTOR , &pidData);

  TCCR0B = _BV(CS00);
  TIMSK0 = _BV(TOIE0);
  TCNT0 = 0;
}

int16_t Get_Reference(void)
{
  ADMUX = _BV(REFS0);
  ADCSRA |= _BV(ADSC); // wykonaj konwersję
  while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
  ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
  ADMUX |=  _BV(REFS0) | _BV(MUX0) | _BV(REFS1);
  return ADC;
}

int16_t Get_Measurement(void)
{
  ADCSRA |= _BV(ADSC); // wykonaj konwersję
  while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
  ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
  return ADC;
}

void Set_Input(int16_t inputValue) {
   regulator += inputValue;
   if ( regulator < 0) {
     regulator = 0;
   }
   if (regulator > 1023) {
     regulator = 1023;
   }
   OCR1A = regulator;
}

FILE uart_file;

int main(void)
{
  int16_t referenceValue, measurementValue, inputValue, mes_temp, ref_temp;
  Init();
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  timer1_init();
  // zainicjalizuj ADC
  adc_init();
  // mierz napięcie
  LED_DDR |= _BV(LED);
  sei();

  //uint16_t data[16] = {1, 2, 3, 4, 5 ,6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}; 

  //set_sleep_mode(SLEEP_MODE_IDLE);
  while(1) {

  //sleep_mode();
    if(gFlags.pidTimer)
    {
      measurementValue = Get_Measurement();
      referenceValue = Get_Reference();
      
      mes_temp = ((measurementValue* (1100 >> 10)) - 500) / 10;
      ref_temp = ((referenceValue* (1100 >> 10)) - 500) / 10;

      inputValue = pid_Controller(referenceValue, measurementValue, &pidData);


      Set_Input(inputValue);

      gFlags.pidTimer = FALSE;
    }
    printf("%"PRId16"(%"PRId16") -> %"PRId16"(%"PRId16")   PID: %"PRId16" OCR1A: %"PRId16" \r\n", mes_temp, measurementValue, ref_temp, referenceValue, inputValue, OCR1A);

    //_delay_ms(1);
    //printf("UP -> %"PRIu32"mV DOWN-> %"PRIu32"mV\r\n",(uint32_t) (up * (5000 / 1024.0)),  (uint32_t) (down * (5000 / 1024.0)));
    

  }
}