/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>


#include <stdio.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define mainLED_TASK_PRIORITY   1

#define mainSERIAL_TASK_PRIORITY 1

#define TH 1

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vBlinkLed(void* pvParameters);

static void vSerial(void* pvParameters);

uint16_t threshold = 20;
uint16_t curr_temp = 0;

/******************************************************************************
 * Public function definitions.
 ******************************************************************************/

// inicjalizacja ADC
void adc_init()
{
  ADMUX = _BV(REFS0) | _BV(REFS1);

  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

/**************************************************************************//**
 * \fn int main(void)
 *
 * \brief Main function.
 *
 * \return
 ******************************************************************************/
int main(void)
{
    // Create task.
    xTaskHandle blink_handle;
    xTaskHandle serial_handle;

    xTaskCreate
        (
         vBlinkLed,
         "blink",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainLED_TASK_PRIORITY,
         &blink_handle
        );

    xTaskCreate
        (
         vSerial,
         "serial",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainSERIAL_TASK_PRIORITY,
         &serial_handle
        );

    // Start scheduler.
    vTaskStartScheduler();

    return 0;
}

/**************************************************************************//**
 * \fn static vApplicationIdleHook(void)
 *
 * \brief
 ******************************************************************************/
void vApplicationIdleHook(void)
{

}

/******************************************************************************
 * Private function definitions.
 ******************************************************************************/

/**************************************************************************//**
 * \fn static void vBlinkLed(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vBlinkLed(void* pvParameters)
{
    DDRB |= _BV(PB5);
    adc_init();
    
    for ( ;; )
    {

        ADCSRA |= _BV(ADSC); // wykonaj konwersję
        while (!(ADCSRA & _BV(ADIF))) taskYIELD(); // czekaj na wynik
        ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
        curr_temp = ((ADC* (1100/1024)) - 500) / 10;
        if (curr_temp < threshold - TH) {
            PORTB |= _BV(PB5);
        }
        else {
            PORTB &= ~_BV(PB5);
        }
    
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}


/**************************************************************************//**
 * \fn static void vSerial(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vSerial(void* pvParameters)
{
    uart_init();
    stdin = stdout = stderr = &uart_file;
    // zainicjalizuj ADC
    char input;
    char d[4];
    char buff[4];
    puts("[g-get, s-set (2dig)]\r");

    for ( ;; )
    {
        input = getchar();
        if (input == 'g') {
            puts("GET TEMP\r");
            utoa(curr_temp, buff, 10);
            puts(buff);
            puts("\r");
        }
        else if (input == 's') {
            puts("SET TEMP: \r");
            d[0] = getchar();
            d[1] = getchar();
            d[2] = ' ';
            d[3] = 0;
            threshold = ((d[0] - '0') * 10) + (d[1] - '0');
            puts(d);
            puts("\r");
        }
        else {
            puts("BLAD\r");
        }
        
    }
}
