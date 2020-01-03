#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define MEASUREMENTS 10

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

void noise_reduction_init() {
	SMCR = _BV(SM0) | _BV(SE);
}

// inicjalizacja ADC
void adc_init()
{
    ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
	ADMUX  |= _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  	DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  	// częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  	ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
	ADCSRA |= _BV(ADIE); // ADC interrupt enable
  	ADCSRA |= _BV(ADEN); // włącz ADC
}

ISR(ADC_vect) {
	ADCSRA |= _BV(ADIF);
}

int16_t avg(uint16_t numbers[MEASUREMENTS]) {
	int32_t sum = 0;
	for (uint8_t i = 0; i < MEASUREMENTS; i++)
		sum += numbers[i];

	return sum / MEASUREMENTS;
}

int16_t var(uint16_t numbers[MEASUREMENTS]) {
	int16_t numbers_avg = avg(numbers);
	int32_t var = 0;
	for (uint8_t i = 0; i < MEASUREMENTS; i++) {
		int32_t tmp = (int32_t)numbers[i] - (int32_t)numbers_avg;
		var += tmp * tmp;
	}
	return var / MEASUREMENTS;
}

int16_t without_noise_reduction() {
	uint16_t result[MEASUREMENTS];
	for (uint8_t i = 0; i < MEASUREMENTS; i++) {
		ADCSRA |= _BV(ADSC); // wykonaj konwersję
    	while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    	ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
		result[i] = 1126400L / ADC; // 1024 * 1100mV
		//printf("V: %"PRIu16"\r\n", result[i]);
	}
	return var(result);
}

int16_t with_noise_reduction() {
	uint16_t result[MEASUREMENTS];
	for (uint8_t i = 0; i < MEASUREMENTS; i++) {
		ADCSRA |= _BV(ADSC); // wykonaj konwersję
		sleep_mode();
		result[i] = 1126400L / ADC; // 1024 * 1100mV
	//	printf("V: %"PRIu16"\r\n", result[i]);
	}
	return var(result);
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
	noise_reduction_init();
  	while(1) {
		cli();
    	printf("Wariancja bez noise reduction: %"PRId16"mV\r\n", without_noise_reduction());
		_delay_ms(100);
		sei();
		printf("Wariancja z noise reduction: %"PRId16"mV\r\n", with_noise_reduction());
		_delay_ms(1000);
  	}
}