#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include "hd44780.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
#define LINE_SIZE 16
#define ROW_MAX 1
#define ROW_MIN 0
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

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

FILE uart_file;



int hd44780_transmit(char data, FILE *stream)
{
  LCD_WriteData(data);
  return 0;
}



FILE hd44780_file;

int main()
{
    // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, NULL, uart_receive, _FDEV_SETUP_READ);
  stdin = &uart_file;
  // zainicjalizuj SPI

  // skonfiguruj wyświetlacz
  LCD_Initialize();
  LCD_Clear();
  // skonfiguruj strumienie wyjściowe
  fdev_setup_stream(&hd44780_file, hd44780_transmit, NULL, _FDEV_SETUP_WRITE);
  stdout = stderr = &hd44780_file;

  char c;
  char buff[LINE_SIZE] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
  uint8_t col = 0;
  uint8_t row = 0;
  uint8_t save_flag = 0;
  LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_ON | HD44780_CURSOR_BLINK);
  while(1) {
    LCD_GoTo(col, row);
    scanf("%c", &c);
    if (c == '\r') {
      save_flag = 1;
      if (row == ROW_MAX) {
        LCD_Clear();
        LCD_GoTo(0, 0);
        for (uint8_t i=0; i<LINE_SIZE; i++) {
          printf("%c", buff[i]);
          buff[i] = ' ';
        }
      }
      row = ROW_MAX;
      col = 0;

    }
    else {
      if (col == 16) {
        save_flag = 1;
        LCD_GoTo(0, 0);
        LCD_Clear();
        for (uint8_t i=0; i<LINE_SIZE; i++) {
          printf("%c", buff[i]);
          buff[i] = ' ';
        }
        row = ROW_MAX;
        col = 0;
        LCD_GoTo(0, ROW_MAX);
      }
      if (save_flag) {
        buff[col] = c;
      }
      printf("%c", c);
      _delay_ms(100);
      col++;
    }
    
  }
}

