#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "pid.h"
#include <util/delay.h>


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
  ADMUX = _BV(REFS0) | _BV(REFS1);

  DIDR0   = _BV(ADC0D) | _BV(ADC1D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}


/*! \brief P, I and D parameter values
 *
 * The K_P, K_I and K_D values (P, I and D gains)
 * need to be modified to adapt to the application at hand
 */
//! \xrefitem todo "Todo" "Todo list"
#define K_P     20.00
//! \xrefitem todo "Todo" "Todo list"
#define K_I     5.00
//! \xrefitem todo "Todo" "Todo list"
#define K_D     0.00

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

const uint16_t temps[16] = {18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33};
/*! \brief Read reference value.
 *
 * This function must return the reference value.
 * May be constant or varying
 */
int16_t Get_Reference(void)
{
  ADMUX = _BV(REFS0);
  ADCSRA |= _BV(ADSC); // wykonaj konwersję
  while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
  ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
  return temps[ADC>>6];
}

/*! \brief Read system process value
 *
 * This function must return the measured data
 */
int16_t Get_Measurement(void)
{
  ADMUX = _BV(REFS0) | _BV(REFS1) | _BV(MUX0);
  _delay_ms(150);
  ADCSRA |= _BV(ADSC); // wykonaj konwersję
  while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
  ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
  int16_t tempe = ((ADC* (1100/1024)) - 500) / 10;
  return tempe;
}

/*! \brief Set control input to system
 *
 * Set the output from the controller as input
 * to system.
 */

void meine_delete(int16_t inputValue) {
  for (uint16_t i=0; i<inputValue; i++) {
    _delay_ms(1);
  }
}

void Set_Input(int16_t inputValue)
{
  // if (inputValue < 0) {
  //   meine_delete(inputValue * -1);
  // }
  // else{
  //   LED_PORT |= _BV(LED);
  //   meine_delete(inputValue);
  //   LED_PORT &= ~_BV(LED);
  // }

}

FILE uart_file;

/*! \brief Demo of PID controller
 */
void main(void)
{
  int16_t referenceValue, measurementValue, inputValue;
  Init();
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj ADC
  adc_init();
  // mierz napięcie
  LED_DDR |= _BV(LED);
  sei();

  while(1){
    // Run PID calculations once every PID timer timeout
    if(gFlags.pidTimer)
    {
      measurementValue = Get_Measurement();
      referenceValue = Get_Reference();
      

      inputValue = pid_Controller(referenceValue, measurementValue, &pidData);

      printf("GET %"PRId16"\r\n", referenceValue);
      printf("TEMPP %"PRId16"\r\n", measurementValue);

      Set_Input(inputValue);

      gFlags.pidTimer = FALSE;
    }
    _delay_ms(10);
  }
}