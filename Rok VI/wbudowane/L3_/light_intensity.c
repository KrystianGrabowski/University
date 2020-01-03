//Zadanie3

#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>


#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

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
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D) | _BV(ADC1D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

FILE uart_file;

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
  uint16_t sleep_time = 1;
  uint16_t light_time = 1;
  uint16_t delay_durations[] = {90, 64, 32, 16, 8, 4, 2 ,1};
  LED_DDR |= _BV(LED);
  LED_PORT |= _BV(LED);
  while(1) {
    ADMUX   = _BV(REFS0) | _BV(MUX0);
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    uint16_t v = ADC; // weź zmierzoną wartość (0..1023)
    //printf("%"PRId16"\r\n", v);

    uint8_t shifted_value = v>>7;
    sleep_time = delay_durations[shifted_value];
    light_time = delay_durations[7-shifted_value];

    for (int i=0; i<100; i++){
      LED_PORT |= _BV(LED);
      for(int i=0; i<light_time; i++){
        _delay_us(1);
      }
      LED_PORT &= ~_BV(LED);
      for(int i=0; i<sleep_time; i++){
        _delay_us(1);
      }
    }

    ADMUX &= ~_BV(MUX0);
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    uint16_t c = ADC; // weź zmierzoną wartość (0..1023)
    printf("%"PRId16"\r\n", c);
    ADMUX = _BV(REFS0);


    ADMUX |= _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)

    uint16_t adc = ADC;
    uint16_t vcc = 1125300L / adc;

    //arytmetyka stalopozycyjna
    printf("VCC: %"PRId16"\r\n", vcc);
  
    ADMUX = _BV(REFS0);

  }
}

