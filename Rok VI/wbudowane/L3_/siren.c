//Zadanie1

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define BUZZ PB5
#define BUZZ_DDR DDRB
#define BUZZ_PORT PORTB

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
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
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

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
