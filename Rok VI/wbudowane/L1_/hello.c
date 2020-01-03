#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>

#define PRId64    "lld"
#define SCNd64    "lld"
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

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // program testowy


  printf("int8_t!\r\n");
  int8_t a = 1;
  int8_t b = 1;
  scanf("%"SCNd8, &a);
  scanf("%"SCNd8, &b);
  printf("Wynik dodawania: %"PRId8"\r\n", a + b);
  printf("Wynik mnożenia: %"PRId8"\r\n", a * b);
  printf("Wynik dzielenia: %"PRId8"\r\n", a / b);

  printf("int16_t!\r\n");
  int16_t c = 1;
  int16_t d = 1;
  scanf("%"SCNd16, &c);
  scanf("%"SCNd16, &d);
  printf("Wynik dodawania: %"PRId16"\r\n", c + d);
  printf("Wynik mnożenia: %"PRId16"\r\n", c * d);
  printf("Wynik dzielenia: %"PRId16"\r\n", c / d);

  printf("int32_t!\r\n");
  int32_t e = 1;
  int32_t f = 1;
  scanf("%"SCNd32, &e);
  scanf("%"SCNd32, &f);
  printf("Wynik dodawania: %"PRId32"\r\n", e + f);
  printf("Wynik mnożenia: %"PRId32"\r\n", e * f);
  printf("Wynik dzielenia: %"PRId32"\r\n", e / f);

  //Problemy z działaniam dla 64 bitów
  /*printf("int64_t!\r\n");
  int64_t g = 1;
  int64_t h = 1;
  scanf("%llu", &g);
  scanf("%llu", &h);
  printf("Wynik dodawania: %llu\r\n", g + h);
  printf("Wynik mnożenia: %llu\r\n", g * h);
  printf("Wynik dzielenia: %llu\r\n", g / h);*/

  printf("float!\r\n");
  float i = 1;
  float j = 1;
  scanf("%f", &i);
  scanf("%f", &j);
  printf("Wynik dodawania: %f\r\n", i + j);
  printf("Wynik mnożenia: %f\r\n", i * j);
  printf("Wynik dzielenia: %f\r\n", i / j);

  return 0;


}

