#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "i2c.h"
#include <string.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
#define BUFF_LEN 32

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

const uint8_t eeprom_addr = 0xa0;

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
  char mode[10];
  uint16_t addr = 0;
  uint8_t value = 0;
  #define i2cCheck(code, msg) \
    if ((TWSR & 0xf8) != (code)) { \
      printf(msg " failed, status: %.2x\r\n", TWSR & 0xf8); \
      i2cReset(); \
      continue; \
    }

  while(1) {
    scanf("%s", mode);
    char hex_num[2];
    char addr_num[4];
    char *ptr;

    if (!strcmp(mode, "write")) {
      printf("## Write mode ##\r\n");
      while (1) {
        
        uint8_t ll, rr, dt, cc;
        //length
        scanf(" %2c", &hex_num[0], &hex_num[1]);
        ll = (uint8_t)strtol(hex_num, &ptr, 16);
        printf(":%.2x", ll);
        if ((ll & BUFF_LEN-1) != ll) {
          printf("Rozmiar przekroczony, spróbuj ponownie\r\n");
          i2cReset();
          break;
        }
        
        //addr
        scanf(" %4c", &addr_num[0], &addr_num[1], &addr_num[2], &addr_num[3]);
        addr = (uint8_t)strtol(addr_num, &ptr, 16);
        printf("%.4x", addr);

        //mode
        scanf(" %2c", &hex_num[0], &hex_num[1]);
        rr = (uint8_t)strtol(hex_num, &ptr, 16);
        printf("%.2x", rr);

        //data
        uint8_t sum = ll + addr + rr;
        uint8_t buff[BUFF_LEN];
        for (int i=0; i<ll; i++) {
            scanf(" %2c", &hex_num[0], &hex_num[1]);
            dt = (uint8_t)strtol(hex_num, &ptr, 16);
            buff[i] = dt;
            printf("%.2x", buff[i]);
            sum += buff[i];
          }

        //checksum
        scanf(" %2c", &hex_num[0], &hex_num[1]);
        cc = (uint8_t)strtol(hex_num, &ptr, 16);
        if (cc != sum) {
          printf("Suma niepoprawna, dobra suma: %"PRIu8"\r\n", sum);
          i2cReset();
          break;
        }
        printf("%.2x\r\n", cc);

      
        uint8_t org_val = 0; 
        while (org_val < ll) {
          i2cStart(); 
          i2cCheck(0x08, "I2C start")
          i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
          i2cCheck(0x18, "I2C EEPROM write request")
          i2cSend(addr & 0xff);
          i2cCheck(0x28, "I2C EEPROM set address")
          uint8_t new_val = ll-org_val;
          if (new_val > 16) {new_val = 16;} 
          if (new_val > 16 && org_val == 0) {new_val = 0x10 - (addr & 0xF);}
          for (int i=0; i<new_val; i++) {
            i2cSend(buff[org_val]);
            i2cCheck(0x28, "I2C EEPROM write data")
            org_val++; 
          }
          addr += new_val;
          i2cStop();
          i2cCheck(0xf8, "I2C stop")
          printf("Zapisano %"PRIu8" wartosci od adresu %.3x\r\n", new_val, addr-new_val);
        }

        if (rr == 1) {
          break;
        }
      }
    }
    else if (!strcmp(mode, "read")) {
      printf("## Read mode ##\r\n");
      scanf("%"SCNu16" %"SCNu8, &addr, &value);
      printf("%.2x", value);
      printf("%.4x", addr);
      printf("%.2x", 0);
      uint8_t checksum = value + addr;
      i2cStart(); 
      i2cCheck(0x08, "I2C start")
      i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
      i2cCheck(0x18, "I2C EEPROM write request")
      i2cSend(addr & 0xff);
      i2cCheck(0x28, "I2C EEPROM set address")
      i2cStart();
      i2cCheck(0x10, "I2C second start")
      i2cSend(eeprom_addr | 0x1 | ((addr & 0x100) >> 7));
      i2cCheck(0x40, "I2C EEPROM read request")
      uint8_t org_val = 0; 
      while (org_val != value) {
        uint8_t data = i2cReadAck();
        i2cCheck(0x50, "I2C EEPROM read")
        checksum += data;
        printf("%.2x", data);
        org_val++;
      }
      i2cReadNoAck();
      i2cCheck(0x58, "I2C EEPROM read")
      i2cStop();
      i2cCheck(0xf8, "I2C stop")
      printf("%.2x\r\n", checksum);
    }
    else {
      printf("ERROR");
    }
  }
}