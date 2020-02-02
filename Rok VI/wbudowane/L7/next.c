#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <inttypes.h>

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

#define SCK_PIN PD6
#define MOSI_PIN PD5
#define MISO_PIN PD4
#define SS_PIN PD7

FILE uart_file;

// inicjalizacja SPI
void spi_init()
{
    // MISO jako wyjscie
    DDRB |= _BV(DDB4);
    // 
    DDRD |= _BV(MOSI_PIN) | _BV(SCK_PIN) | _BV(SS_PIN);
    //
    PORTD |= _BV(SS_PIN);
    // włącz SPI
    SPCR = _BV(SPE);
}

// // transfer jednego bajtu
// uint8_t spi_transfer(uint8_t data)
// {
//     // rozpocznij transmisję
//     SPDR = data;
//     // czekaj na ukończenie transmisji
//     while (!(SPSR & _BV(SPIF)));
//     // wyczyść flagę przerwania
//     SPSR |= _BV(SPIF);
//     // zwróć otrzymane dane
//     return SPDR;
// }

void send_8bit_serial_data(uint8_t data) {
  //SS na low
  PORTD &= ~_BV(SS_PIN);
  uint8_t rec = 0;
  //wysylanie bitow 7..0
  for (int i = 0; i < 8; i++) {
    // consider leftmost bit
    // set line high if bit is 1, low if bit is 0
    if (data & 0x80)
      PORTD |= _BV(MOSI_PIN);
    else
      PORTD &= ~_BV(MOSI_PIN);

    // pulse clock to indicate that bit value should be read
    PORTD |= _BV(SCK_PIN);

    if(PIND & _BV(MISO_PIN)) {
      rec |= _BV(7-i);
    }
    else {
      rec &= ~_BV(7-i);
    }

    PORTD &= ~_BV(SCK_PIN);


    // shift byte left so next bit will be leftmost
    data <<= 1;
   }

  printf("Odczytano: %"PRId8"\r\n", rec);

  //SS na high
  PORTD |= _BV(SS_PIN);
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj SPI
  spi_init();
  uint8_t iter = 0;
  while(1) {
    send_8bit_serial_data(iter);
    while (!(SPSR & _BV(SPIF)));
    SPSR |= _BV(SPIF);
    //printf("Odczytano: %"PRId8"\r\n", SPDR);
    _delay_ms(1000);
    iter++;
  }
}

