#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "pid.h"
#include <util/delay.h>
#include <avr/sleep.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem


uint16_t pot = 0;
uint16_t up = 0;
uint16_t down = 0;
uint8_t pot_f = 0;
uint8_t up_f = 0;
uint8_t down_f = 0;

uint16_t regulator = 0;

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
  ICR1 = 1023;
  TCCR1A = _BV(COM1A1);
  TCCR1B = _BV(WGM13) | _BV(CS11);
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB |= _BV(PB1);
  TIMSK1 |= _BV(TOIE1) | _BV(ICIE1);
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
  ADCSRA |= _BV(ADIE); //Przerwania ADC
}


/*! \brief P, I and D parameter values
 *
 * The K_P, K_I and K_D values (P, I and D gains)
 * need to be modified to adapt to the application at hand
 */
  #define K_P 0.5
  #define K_I 0.3
  #define K_D 0.3

// #define K_P     0.05
// #define K_I     0.001
// #define K_D     0.05

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

/*! \brief Flags for status information
 */
struct GLOBAL_FLAGS {
  //! True when PID control loop should run one time
  uint8_t pidTimer:1;
  uint8_t dummy:7;
} gFlags = {1, 7};

//! Parameters for regulator
struct PID_DATA pidData;

/*! \brief Sampling Time Interval
 *
 * Specify the desired PID sample time interval
 * With a 8-bit counter (255 cylces to overflow), the time interval value is calculated as follows:
 * TIME_INTERVAL = ( desired interval [sec] ) * ( frequency [Hz] ) / 255
 */
//! \xrefitem todo "Todo" "Todo list"
#define TIME_INTERVAL   157

/*! \brief Timer interrupt to control the sampling interval
 */
// #pragma vector = TIMER0_OVF_vect
// __interrupt void TIMER0_OVF_ISR( void )
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

ISR(TIMER1_OVF_vect) {
  ADMUX   = _BV(REFS0) | _BV(MUX0);
  ADCSRA |= _BV(ADSC);
  up_f = 1;
  down_f = 0;
  pot_f = 0;
}

ISR(TIMER1_CAPT_vect) {
  ADMUX   = _BV(REFS0) | _BV(MUX0);
  ADCSRA |= _BV(ADSC);
  up_f = 0;
  down_f = 1;
  pot_f = 0;

}

ISR(ADC_vect) {
    if (up_f) {
      up = ADC;
    }
    if (down_f) {
      down = ADC;
    }
    if (pot_f) {
      pot = ADC;
    }
    else {
      ADMUX   = _BV(REFS0);
      ADCSRA |= _BV(ADSC);
      pot_f  = 1;
      up_f  = 0;
      down_f  = 0;
    }
}


/*! \brief Init of PID controller demo
 */
void Init(void)
{
  pid_Init(K_P * SCALING_FACTOR, K_I * SCALING_FACTOR , K_D * SCALING_FACTOR , &pidData);

  // Set up timer, enable timer/counte 0 overflow interrupt
  TCCR0B = _BV(CS00);
  TIMSK0 = _BV(TOIE0);
  TCNT0 = 0;
}

//const uint16_t temps[16] = {18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33};
/*! \brief Read reference value.
 *
 * This function must return the reference value.
 * May be constant or varying
 */
int16_t Get_Reference(void)
{
  return pot;
}

/*! \brief Read system process value
 *
 * This function must return the measured data
 */
int16_t Get_Measurement(void)
{
  return down;
}

/*! \brief Set control input to system
 *
 * Set the output from the controller as input
 * to system.
 */

void Set_Input(int16_t inputValue)
{
  inputValue *= -1;
  if ((regulator + inputValue) < 0) {
    regulator = 0;
  }
  if ((regulator + inputValue) > 1023) {
    regulator = 1023;
  }
  else {
    regulator += inputValue;
  }
  OCR1A = regulator;
}

FILE uart_file;

/*! \brief Demo of PID controller
 */
int main(void)
{
  int16_t referenceValue = 0, measurementValue = 0, inputValue = 0;
  Init();
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
  //set_sleep_mode(SLEEP_MODE_IDLE);
  while(1) {
    //sleep_mode();
    if(gFlags.pidTimer)
    {

      
      measurementValue = Get_Measurement();
      referenceValue = Get_Reference();
      inputValue = pid_Controller(measurementValue, referenceValue, &pidData);
  		inputValue = ((uint32_t)inputValue * 1024) / MAX_INT;
      if (inputValue < 0) {inputValue = 0;}
			OCR1A = inputValue;
      //printf("INPUT: %"PRId16"\r\n", inputValue);
			
      //Set_Input(inputValue);
      
      gFlags.pidTimer = FALSE;

    }
    //printf("UP -> %"PRIu32"mV DOWN-> %"PRIu32"mV OCR1A-> %"PRId16"\r\n",(uint32_t) (up * (5000 / 1024.0)),  (uint32_t) (down * (5000 / 1024.0)), inputValue);
    printf("EXPECTED: %"PRId16" CURRENT: %"PRId16" OCR1A: %"PRId16"\r\n", referenceValue, measurementValue, inputValue);
    //_delay_ms(10);D

  }
}