#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

//Zadanie 1

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

void timer1_init()
{
  // ustaw tryb licznika
  // WGM1  = 0000 -- normal
  // CS1   = 001  -- prescaler 1
  TCCR1B = _BV(CS10);
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
  // program testowy

  volatile int8_t a_8bit = 66, b_8bit = 31, c_8bit = 0;
  volatile int16_t a_16bit = 66, b_16bit = 31, c_16bit = 0;
  volatile int32_t a_32bit = 66, b_32bit = 31, c_32bit = 0;
  volatile int64_t a_64bit = 66, b_64bit = 31, c_64bit = 0;
  volatile float a_float = 66.0f, b_float = 31.0f, c_float = 0.0;

  uint16_t time_t0, time_t1;

  printf("--------INT8_T--------\r\n");
  time_t0 = TCNT1;
  c_8bit = a_8bit + b_8bit;
  time_t1 = TCNT1;
  printf("Zmierzony czas dodawania: %"PRIu16" cykli\r\n", time_t1 - time_t0);
  time_t0 = TCNT1;
  c_8bit = a_8bit * b_8bit;
  time_t1 = TCNT1;
  printf("Zmierzony czas mnożenia: %"PRIu16" cykli\r\n", time_t1 - time_t0);
  time_t0 = TCNT1;
  c_8bit = a_8bit / b_8bit;
  time_t1 = TCNT1;
  printf("Zmierzony czas dzielenia: %"PRIu16" cykli\r\n", time_t1 - time_t0);

  printf("--------INT16_T--------\r\n");
  time_t0 = TCNT1;
  c_16bit = a_16bit + b_16bit;
  time_t1 = TCNT1;
  printf("Zmierzony czas dodawania: %"PRIu16" cykli\r\n", time_t1 - time_t0);
  time_t0 = TCNT1;
  c_16bit = a_16bit * b_16bit;
  time_t1 = TCNT1;
  printf("Zmierzony czas mnożenia: %"PRIu16" cykli\r\n", time_t1 - time_t0);
  time_t0 = TCNT1;
  c_16bit = a_16bit / b_16bit;
  time_t1 = TCNT1;
  printf("Zmierzony czas dzielenia: %"PRIu16" cykli\r\n", time_t1 - time_t0);

  printf("--------INT32_T--------\r\n");
  time_t0 = TCNT1;
  c_32bit = a_32bit + b_32bit;
  time_t1 = TCNT1;
  printf("Zmierzony czas dodawania: %"PRIu16" cykli\r\n", time_t1 - time_t0);
  time_t0 = TCNT1;
  c_32bit = a_32bit * b_32bit;
  time_t1 = TCNT1;
  printf("Zmierzony czas mnożenia: %"PRIu16" cykli\r\n", time_t1 - time_t0);
  time_t0 = TCNT1;
  c_32bit = a_32bit / b_32bit;
  time_t1 = TCNT1;
  printf("Zmierzony czas dzielenia: %"PRIu16" cykli\r\n", time_t1 - time_t0);

  printf("--------INT64_T--------\r\n");
  time_t0 = TCNT1;
  c_64bit = a_64bit + b_64bit;
  time_t1 = TCNT1;
  printf("Zmierzony czas dodawania: %"PRIu16" cykli\r\n", time_t1 - time_t0);
  time_t0 = TCNT1;
  c_64bit = a_64bit * b_64bit;
  time_t1 = TCNT1;
  printf("Zmierzony czas mnożenia: %"PRIu16" cykli\r\n", time_t1 - time_t0);
  time_t0 = TCNT1;
  c_64bit = a_64bit / b_64bit;
  time_t1 = TCNT1;
  printf("Zmierzony czas dzielenia: %"PRIu16" cykli\r\n", time_t1 - time_t0);

  printf("--------FLOAT--------\r\n");
  time_t0 = TCNT1;
  c_float = a_float + b_float;
  time_t1 = TCNT1;
  printf("Zmierzony czas dodawania: %"PRIu16" cykli\r\n", time_t1 - time_t0);
  time_t0 = TCNT1;
  c_float = a_float * b_float;
  time_t1 = TCNT1;
  printf("Zmierzony czas mnożenia: %"PRIu16" cykli\r\n", time_t1 - time_t0);
  time_t0 = TCNT1;
  c_float = a_float / b_float;
  time_t1 = TCNT1;
  printf("Zmierzony czas dzielenia: %"PRIu16" cykli\r\n", time_t1 - time_t0);

  //Warningi "variable set but not used"
  c_8bit++;
  c_16bit++;
  c_32bit++;
  c_64bit++;
  c_float++;

}

