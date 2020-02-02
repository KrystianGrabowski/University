#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#define BUFF_LEN 10

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

uint8_t i1=0, i2=0;
uint8_t j1=0, j2=0;
uint8_t rec_size = 0;
uint8_t tra_size = 0;
uint8_t REC_BUFF[BUFF_LEN];
uint8_t TRA_BUFF[BUFF_LEN];

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
  if (tra_size == BUFF_LEN) {
    while(!(UCSR0A & _BV(UDRE0)));
  }
  UCSR0B &= ~_BV(UDRIE0);
  TRA_BUFF[i1] = data;
  tra_size++;
  
  i1++;
  if (i1 == BUFF_LEN) {
    i1 = 0;
  }
  UCSR0B |= _BV(UDRIE0);

  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  //czekaj aż znak dostępny
  char c;
  if (rec_size == 0) {
    while (!(UCSR0A & _BV(RXC0)));
    return UDR0;
  }
  else{
    UCSR0B &= ~_BV(RXCIE0);
    c = REC_BUFF[j2];
    rec_size--;
    j2++;
    
    if (j2 == BUFF_LEN) {
      j2 = 0;
    }
    UCSR0B |= _BV(RXCIE0);    

  }

  return c;
}

ISR(USART_RX_vect) {
  if (rec_size > 0) {
    REC_BUFF[j1] = UDR0;
    j1++;
    if (j1 == BUFF_LEN) {
      j1 = 0;
    }
    rec_size++;
  }

}

ISR(USART_TX_vect) {

}

ISR(USART_UDRE_vect) {
  if (tra_size > 0) {
    UDR0 = TRA_BUFF[i2];
    i2++;
    if (i2 == BUFF_LEN) {
      i2 = 0;
    }
    tra_size--;
  }
}


FILE uart_file;


int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  //odmaskuj przerwania
  sei();
  UCSR0B |= _BV(RXCIE0) | _BV(TXCIE0) | _BV(UDRIE0);
  // program testowy
  for (uint8_t i=0; i<10; i++) {
    printf("Hello world!\r\n");  
  }
  
  _delay_ms(15);
  while(1) {
    int16_t a = 1;
    scanf("%"SCNd16, &a);
    printf("Odczytano: %"PRId16"\r\n", a);
    _delay_ms(15);
  }
}

