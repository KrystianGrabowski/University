#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include "i2c.h"
#include <util/delay.h>
#include <stdlib.h>
#include <stdlib.h>

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

const uint8_t eeprom_addr = 0xd0;
const uint8_t century = 0x20;

uint8_t validate(uint8_t val, uint8_t max_val) {
  if ((val & 0x0f) > 9 || ((val & 0xf0) >> 4) > 9 || val > max_val) {
    return 1;
  }
  return 0;
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj I2C
  i2cInit();
  // program testowy
  uint16_t addr_time = 0;
  uint16_t addr_date = 4;
  char mode[10];
  #define i2cCheck(code, msg) \
    if ((TWSR & 0xf8) != (code)) { \
      printf(msg " failed, status: %.2x\r\n", TWSR & 0xf8); \
      i2cReset(); \
      continue; \
    }
  while(1) {
    scanf("%s", mode);
    if (!strcmp(mode, "set")) {
      printf("set ");
      char mode2[10];
      char *ptr;
      scanf(" %s", mode2);
      if (!strcmp(mode2, "date")) {
        i2cStart(); 
        i2cCheck(0x08, "I2C start")
        i2cSend(eeprom_addr | ((addr_date & 0x100) >> 7));
        i2cCheck(0x18, "I2C EEPROM write request")
        i2cSend(addr_date & 0xff);
        i2cCheck(0x28, "I2C EEPROM set address")

        printf("date ");
        uint8_t d, m ,y;
        char hex_num[5];
        scanf(" %3c", &hex_num[0], &hex_num[1], &hex_num[2]);
        d = (uint8_t)strtol(hex_num, &ptr, 16);
        if (hex_num[2] != '-' || validate(d, 0x31)) {
          printf("\r\nBledne dane, zerowanie\r\n");
          d = 0;
        }
        scanf("%3c", &hex_num[0], &hex_num[1], &hex_num[2]);
        m = (uint8_t)strtol(hex_num, &ptr, 16);
        if (hex_num[2] != '-' || validate(m, 0x12)) {
          printf("\r\nBledne dane, zerowanie\r\n");
          m = 0;
        }
        scanf("%4c", &hex_num[0], &hex_num[1], &hex_num[2], &hex_num[3]);
        if (hex_num[1] == '1') {
          m |= 0x80;
        }
        hex_num[0] = '0';
        hex_num[1] = '0';
        y = (uint8_t)strtol(hex_num, &ptr, 16);
        if (validate(y, 0x99)) {
          printf("\r\nBledne dane, zerowanie\r\n");
          y = 0;
        }
        printf("%x-%x-%x\r\n", d, m & 0x7f, y);

        i2cSend(d);
        i2cCheck(0x28, "I2C EEPROM write data")
        i2cSend(m);
        i2cCheck(0x28, "I2C EEPROM write data")
        i2cSend(y);
        i2cCheck(0x28, "I2C EEPROM write data")
        i2cStop();
        i2cCheck(0xf8, "I2C stop")
      }
      else if (!strcmp(mode2, "time")) {
        i2cStart(); 
        i2cCheck(0x08, "I2C start")
        i2cSend(eeprom_addr | ((addr_time & 0x100) >> 7));
        i2cCheck(0x18, "I2C EEPROM write request")
        i2cSend(addr_time & 0xff);
        i2cCheck(0x28, "I2C EEPROM set address")

        printf("time ");
        uint8_t h, m ,s;
        char hex_num[5];
        scanf(" %3c", &hex_num[0], &hex_num[1], &hex_num[2]);
        h = (uint8_t)strtol(hex_num, &ptr, 16);
        if (hex_num[2] != ':' || validate(h, 0x23)) {
          printf("\r\nBledne dane, zerowanie\r\n");
          h = 0;
        }
        scanf("%3c", &hex_num[0], &hex_num[1], &hex_num[2]);
        m = (uint8_t)strtol(hex_num, &ptr, 16);
        if (hex_num[2] != ':' || validate(m, 0x59)) {
          printf("\r\nBledne dane, zerowanie\r\n");
          m = 0;
        }
        scanf("%2c", &hex_num[0], &hex_num[1]);
        s = (uint8_t)strtol(hex_num, &ptr, 16);
        if (hex_num[2] != ':' || validate(s, 0x59)) {
          printf("\r\nBledne dane, zerowanie\r\n");
          s = 0;
        }
        printf("%x:%x:%x\r\n", h, m, s);

        i2cSend(s);
        i2cCheck(0x28, "I2C EEPROM write data")
        i2cSend(m);
        i2cCheck(0x28, "I2C EEPROM write data")
        i2cSend(h);
        i2cCheck(0x28, "I2C EEPROM write data")
        i2cStop();
        i2cCheck(0xf8, "I2C stop")
      }
      else {
        printf("ERROR_IN\r\n");
      }
    }
    
    else if (!strcmp(mode, "time")) {
      printf("time\r\n");
      i2cStart();
      i2cCheck(0x08, "I2C start")
      i2cSend(eeprom_addr | ((addr_time & 0x100) >> 7));
      i2cCheck(0x18, "I2C EEPROM write request")
      i2cSend(addr_time & 0xff);
      i2cCheck(0x28, "I2C EEPROM set address")
      i2cStart();
      i2cCheck(0x10, "I2C second start")
      i2cSend(eeprom_addr | 0x1 | ((addr_time & 0x100) >> 7));
      i2cCheck(0x40, "I2C EEPROM read request")
      uint8_t seconds = i2cReadAck();
      i2cCheck(0x50, "I2C EEPROM read")
      uint8_t minutes = i2cReadAck();
      i2cCheck(0x50, "I2C EEPROM read")
      uint8_t hours = i2cReadNoAck();
      i2cCheck(0x58, "I2C EEPROM read")

      i2cStop();
      i2cCheck(0xf8, "I2C stop")
      printf("%.2x:%.2x:%.2x\r\n", hours, minutes, seconds);

    }
    else if (!strcmp(mode, "date")) {
      printf("date\r\n");
      i2cStart();
      i2cCheck(0x08, "I2C start")
      i2cSend(eeprom_addr | ((addr_date & 0x100) >> 7));
      i2cCheck(0x18, "I2C EEPROM write request")
      i2cSend(addr_date & 0xff);
      i2cCheck(0x28, "I2C EEPROM set address")
      i2cStart();
      i2cCheck(0x10, "I2C second start")
      i2cSend(eeprom_addr | 0x1 | ((addr_date & 0x100) >> 7));
      i2cCheck(0x40, "I2C EEPROM read request")
      uint8_t day = i2cReadAck();
      i2cCheck(0x50, "I2C EEPROM read")
      uint8_t month = i2cReadAck();
      i2cCheck(0x50, "I2C EEPROM read")
      uint8_t year = i2cReadNoAck();
      i2cCheck(0x58, "I2C EEPROM read")

      i2cStop();
      i2cCheck(0xf8, "I2C stop")
      printf("%.2x-%.2x-%.2x%.2x\r\n", day, month & 0x7F, century + ((month & 0x80) >> 7) , year);
    }
    else {
      printf("ERROR\r\n");
    }


  }
}

