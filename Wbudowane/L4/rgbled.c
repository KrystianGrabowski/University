#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>
#include <time.h>
#include <stdlib.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

//Zadanie 3

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
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

FILE uart_file;

void timer1_init()
{
  //Non inverting
  TCCR0A = _BV(COM0A1) | _BV(COM0B1);
  //Fast PWM 
  TCCR0A |= _BV(WGM01) | _BV(WGM00);
  //Prescaler 1
  TCCR0B = _BV(CS00);

  DDRD |= _BV(PD5) | _BV(PD6);
}

void timer2_init() 
{
  //Non inverting
  TCCR2A = _BV(COM2A1);
  //Fast PWM 
  TCCR2A |= _BV(WGM21) | _BV(WGM20); 
  //Prescaler 1
  TCCR2B = _BV(CS20);

  DDRB |= _BV(PB3);
}

void hsv_to_rgb(int16_t h, int16_t* array) {
  int16_t i = h / 60;
  int16_t f = h % 60;
  int16_t v = 60;
  int16_t q = 60 - f;
  int16_t t = 60 - q;


  int32_t r_prim = 0, g_prim = 0, b_prim = 0;
  if (i == 0) {
    r_prim = v;
    g_prim = t;
  }
  if (i == 1) {
    r_prim = q;
    g_prim = v;
  }
  if (i == 2) {
    g_prim = v;
    b_prim = t;
  }
  if (i == 3) {
    g_prim = q;
    b_prim = v;
  }
  if (i == 4) {
    r_prim = t;
    b_prim = v;
  }
  if (i == 5) {
    r_prim = v;
    b_prim = q;
  }
  array[0] = 255 - (r_prim*255)/60;
  array[1] = 255 - (g_prim*255)/60;
  array[2] = 255 - (b_prim*255)/60;
} 

// OCR0A (PD6) -> Red
// OCR0B (PD5) -> Green
// OCR2A (PB3) -> Blue

int16_t value(int16_t c, int16_t add) {
  if (c + add > 255) {
    return 255;
  } 
  else {
    return c + add;
  }
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
  // mierz napięcie
  timer1_init();
  timer2_init();
  int16_t array[3];
  //uint16_t sleep_time = 1;
  uint16_t sat[] = {255, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 253, 253, 253, 253, 252, 252, 252, 251, 251, 251, 250, 250, 249, 249, 249, 248, 248, 247, 246, 246, 245, 245, 244, 243, 243, 242, 241, 241, 240, 239, 239, 238, 237, 236, 235, 235, 234, 233, 232, 231, 230, 229, 228, 227, 226, 225, 224, 223, 222, 221, 220, 219, 218, 217, 216, 215, 213, 212, 211, 210, 209, 208, 206, 205, 204, 203, 201, 200, 199, 197, 196, 195, 193, 192, 191, 189, 188, 187, 185, 184, 182, 181, 180, 178, 177, 175, 174, 172, 171, 169, 168, 166, 165, 163, 162, 160, 159, 157, 156, 154, 153, 151, 150, 148, 147, 145, 143, 142, 140, 139, 137, 136, 134, 132, 131, 129, 128, 126, 125, 123, 122, 120, 118, 117, 115, 114, 112, 111, 109, 107, 106, 104, 103, 101, 100, 98, 97, 95, 94, 92, 91, 89, 88, 86, 85, 83, 82, 80, 79, 77, 76, 74, 73, 72, 70, 69, 67, 66, 65, 63, 62, 61, 59, 58, 57, 55, 54, 53, 51, 50, 49, 48, 46, 45, 44, 43, 42, 41, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 19, 18, 17, 16, 15, 15, 14, 13, 13, 12, 11, 11, 10, 9, 9, 8, 8, 7, 6, 6, 5, 5, 5, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  srand(time(NULL));
  
  while(1) {
    int r = rand() % 360;
    hsv_to_rgb(r, array);
    for (int16_t i = 0; i < 256; i++) {
      //wartosci dla R, G, B
      OCR0A = value(array[0], (255-array[0]) * sat[i] / 255);
      OCR0B = value(array[1], (255-array[1]) * sat[i] / 255);
      OCR2A = value(array[2], (255-array[2]) * sat[i] / 255);
      _delay_ms(10);
    }
    for (int16_t i = 255; i >= 0; i--) {
      OCR0A = value(array[0], (255-array[0]) * sat[i] / 255);
      OCR0B = value(array[1], (255-array[1]) * sat[i] / 255);
      OCR2A = value(array[2], (255-array[2]) * sat[i] / 255);
      _delay_ms(10);
    }
  }
}

