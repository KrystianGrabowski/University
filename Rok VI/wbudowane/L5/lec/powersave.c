#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdio.h>

#define BAUD 9600                         // baudrate
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

// oczekiwanie na zakończenie transmisji
void uart_wait()
{
  while(!(UCSR0A & _BV(TXC0)));
}

FILE uart_file;

// inicjalizacja licznika 2
void timer2_init()
{
  // preskaler 1024
  TCCR2B = _BV(CS20) | _BV(CS21) | _BV(CS22);
  // odmaskowanie przerwania przepełnienia licznika
  TIMSK2 |= _BV(TOIE2);
}

void turn_led_on() {
  LED_PORT |= _BV(LED);
}

void turn_led_off() {
  LED_PORT &= ~_BV(LED);
}

// procedura obsługi przerwania przepełnienia licznika
ISR(TIMER2_OVF_vect) {
    printf("%"PRId8"\r\n", iter);
    if (buffer[iter] != 0) {
      turn_led_on();
    }
    if(buffer[iter] == 0){
      turn_led_off();
    }
    buffer[iter] = 0;
    _delay_ms(DELAY_LEN);
    if (debounce()){
      buffer[iter] = 1;
    }
    iter = next_iter(iter);
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj licznik 2
  timer2_init();
  // ustaw tryb uśpienia na tryb bezczynności
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);
  // odmaskuj przerwania

  // program testowy
  while(1) {
      sei();
    printf("X\r\n");
    uart_wait();    // poczekaj na UART zanim się uśpisz
    _delay_us(400); // poczekaj jeszcze trochę
    sleep_mode();
  }
}

