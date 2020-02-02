//Zadanie1

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define BUZZ PB1
#define BUZZ_DDR DDRB
#define BUZZ_PORT PORTB

#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988

#define SONG_LEN 35

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


void my_delay_us(int us)
{
  while (0 < us)
  {  
    _delay_us(1);
    --us;
  }
}

int main() {
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // program testowy

  static const uint16_t notes[SONG_LEN] PROGMEM = { NOTE_G5, NOTE_E5, NOTE_G5, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_F5,
                              NOTE_F5, NOTE_D5, NOTE_F5, NOTE_D5, NOTE_F5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_E5,
                              NOTE_G5, NOTE_G5, NOTE_E5, NOTE_G5, NOTE_G5, NOTE_E5, NOTE_G5, NOTE_C5, NOTE_B5, NOTE_A5, NOTE_G5 ,NOTE_A5,
                              NOTE_B5, NOTE_B5, NOTE_B5};
  static const uint16_t noteDurations[SONG_LEN] PROGMEM = { 1000, 1000, 1000, 1000, 1000, 500, 500, 500, 500, 1000,
                          1000, 1000, 1000, 1000, 1000, 500, 500, 500, 500, 1000,
                          500, 500, 1000, 500, 500, 1000, 1000, 500, 500, 500, 500, 1000,
                          1000, 1000, 2000};
  BUZZ_DDR |= _BV(BUZZ);
  while (1) {
    for (int i=0; i<SONG_LEN; i++){
      uint16_t step = (uint16_t)((1.0/pgm_read_word(&notes[i])) * 1000000);
      uint16_t delay = pgm_read_word(&noteDurations[i]);
      for (uint16_t i = 0; i < (uint32_t)1000 * (delay) / (step) / 2; i++) { 
        BUZZ_PORT |= _BV(BUZZ); 
        my_delay_us(step);
        BUZZ_PORT &= ~_BV(BUZZ);
        my_delay_us(step);
      }
      
    }

  }
}
