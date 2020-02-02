#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include "hd44780.h"

int hd44780_transmit(char data, FILE *stream)
{
  LCD_WriteData(data);
  return 0;
}

FILE hd44780_file;

int main()
{
  // skonfiguruj wyświetlacz
  LCD_Initialize();
  LCD_Clear();
  // skonfiguruj strumienie wyjściowe
  fdev_setup_stream(&hd44780_file, hd44780_transmit, NULL, _FDEV_SETUP_WRITE);
  stdout = stderr = &hd44780_file;
  // program testowy
  uint16_t v = 0;
  uint8_t address = 0x40;
  uint8_t init_val = 0b00010000;
  uint8_t curr_val = init_val;
  for (uint8_t i=0; i<5; i++) {
    LCD_WriteCommand(address);
    curr_val |= ( init_val >> i );
    for (uint8_t j=0; j<8; j++) {
      LCD_WriteData(curr_val);
    }
    address += 8;
  }

  uint8_t col = 0;
  uint8_t row = 0;
  for (uint8_t i=3; i>0; i--) {
    LCD_GoTo(8, 0);
    printf("%"PRIu16, i);
    _delay_ms(1000);
  }
  LCD_Clear();
  _delay_ms(1000);
  for (uint8_t i=0; i<16; i++) {
    for (uint8_t k=0; k<5; k++) {
      LCD_GoTo(col, row);
      printf("%c", k);
      _delay_ms(1000);
    }
    col += 1;
  }
}

