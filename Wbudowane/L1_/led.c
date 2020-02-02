#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB
#define MAX_LIMIT 20 
#define FACTOR 500

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

char* translate_to_morse(char x) {
  switch (x)
  {
    case 'a': 
      return ".-"; 
    case 'b': 
      return "-..."; 
    case 'c': 
      return "-.-."; 
    case 'd': 
      return "-.."; 
    case 'e': 
      return "."; 
    case 'f': 
      return "..-."; 
    case 'g': 
      return "--."; 
    case 'h': 
      return "...."; 
    case 'i': 
      return ".."; 
    case 'j': 
      return ".---"; 
    case 'k': 
      return "-.-"; 
    case 'l': 
      return ".-.."; 
    case 'm': 
      return "--"; 
    case 'n': 
      return "-."; 
    case 'o': 
      return "---"; 
    case 'p': 
      return ".--."; 
    case 'q': 
      return "--.-"; 
    case 'r': 
      return ".-."; 
    case 's': 
      return "..."; 
    case 't': 
      return "-"; 
    case 'u': 
      return "..-"; 
    case 'v': 
      return "...-"; 
    case 'w': 
      return ".--"; 
    case 'x': 
      return "-..-"; 
    case 'y': 
      return "-.--"; 
    case 'z': 
      return "--.."; 
    default:
      return "space";

  }
}

void dot() {
  //printf("dot\r\n");
  LED_PORT |= _BV(LED);
  _delay_ms(1 * FACTOR);
  LED_PORT &= ~_BV(LED);
}

void dash() {
  //printf("dash\r\n");
  LED_PORT |= _BV(LED);
  _delay_ms(3 * FACTOR);
  LED_PORT &= ~_BV(LED);
}

//elements
void inner_element_gap() {
  //printf("inner\r\n");
  _delay_ms(1 * FACTOR);
}

//letters
void short_gap() {
  //printf("short\r\n");
  _delay_ms(3 * FACTOR);
}

//words
void medium_gap() {
  //printf("medium\r\n");
  _delay_ms(7 * FACTOR);
}

int translate_letter(char* morse_code) {
  int i = 0;
  while((int)morse_code[i] != 0) {
    if (morse_code[i] == '.') {
      dot();
    }
    if (morse_code[i] == '-') {
      dash();
    }
    i++;
    if ((int)morse_code[i] != 0) {
      inner_element_gap();
    }
  }
  return 0;
}

int translate(char str[], int arr_size) {
  int i = 0;
  char* s = "space";
  while (i<arr_size && (int)str[i] != 0 ) {  //&& (((int)str[i] >= 97 && (int)str[i] <= 122) || (int)str[i] == 32)) {
    char* morse_code = translate_to_morse(str[i]);
    if (strcmp(morse_code, s) == 0) {
      medium_gap();
    }
    else{
      translate_letter(morse_code);
      if (i+1 < arr_size && (int)str[i+1] != 32){
        short_gap();
      }
    }
    i++;
  }
  return 0;
} 

int main() {
  
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // program testowy

  LED_DDR |= _BV(LED);
  char str[MAX_LIMIT];
  while(1){
    printf("Enter text:\r\n");
    scanf("%[^\r\n]%*c", str);
    //scanf("%s", str); 
    printf("Processing... \r\n");
    int arr_size = sizeof(str)/sizeof(str[0]);  
    translate(str, arr_size);
  }
  return 0;


  
}
