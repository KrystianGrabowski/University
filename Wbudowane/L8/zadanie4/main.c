/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include <avr/interrupt.h>
#include <avr/io.h>


#include <stdio.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define mainADC0_TASK_PRIORITY 1

#define mainADC1_TASK_PRIORITY 1

#define mainADC2_TASK_PRIORITY 1


/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vAdc0(void* pvParameters);

static void vAdc1(void* pvParameters);

static void vAdc2(void* pvParameters);

xTaskHandle xCurrentTask;

SemaphoreHandle_t xSemaphore1;
SemaphoreHandle_t xSemaphore2;

/******************************************************************************
 * Public function definitions.
 ******************************************************************************/

// inicjalizacja ADC
void adc_init()
{
  ADMUX = _BV(REFS0);
  //1.1V
  DIDR0   = _BV(ADC0D) | _BV(ADC1D) | _BV(ADC2D);
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
  ADCSRA |= _BV(ADIE); // Auto Adc_vect
}


uint16_t readADC(uint8_t mux) {
    ADMUX &= ~(0b00001111);
    ADMUX |= mux;
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    xSemaphoreTake( xSemaphore2, portMAX_DELAY );
    uint16_t data = ADC;
    //vTaskDelay(600 / portTICK_PERIOD_MS);
    return data;

}

// ODCZYT WARTOSCI 
ISR(ADC_vect) {
    xSemaphoreGiveFromISR( xSemaphore2, pdFALSE );
    //xTaskAbortDelay(xCurrentTask);
}

/**************************************************************************//**
 * \fn int main(void)
 *
 * \brief Main function.
 *
 * \return
 ******************************************************************************/
    xTaskHandle adc0_handle;
    xTaskHandle adc1_handle;
    xTaskHandle adc2_handle;
int main(void)
{
    // Create task.
    // xTaskHandle adc0_handle;
    // xTaskHandle adc1_handle;
    // xTaskHandle adc2_handle;
    uart_init();
    stdin = stdout = stderr = &uart_file;
    sei();
    adc_init();
    xSemaphore1 = xSemaphoreCreateMutex();
    xSemaphore2 = xSemaphoreCreateCounting( 1, 0 );


    xTaskCreate
        (
         vAdc0,
         "adc0",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainADC0_TASK_PRIORITY,
         &adc0_handle
        );

    xTaskCreate
        (
         vAdc1,
         "adc1",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainADC1_TASK_PRIORITY,
         &adc1_handle
        );

    xTaskCreate
        (
         vAdc2,
         "adc2",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainADC2_TASK_PRIORITY,
         &adc2_handle
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
static void vAdc0(void* pvParameters)
{
    char buff[5];
    for ( ;; ) {
        if( xSemaphoreTake( xSemaphore1, 0 ) == pdTRUE ) {
            //xCurrentTask = adc0_handle;
            uint16_t data = readADC(0);
            utoa(data, buff, 10);
            puts("Odczytano z ADC0:\r");
            puts(buff);
            puts("\r\n");
            xSemaphoreGive( xSemaphore1 );
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}


/**************************************************************************//**
 * \fn static void vSerial(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vAdc1(void* pvParameters)
{
    char buff[5];
    for ( ;; )
    {
        if( xSemaphoreTake( xSemaphore1, 0 ) == pdTRUE ) {
            //xCurrentTask = adc1_handle;
            uint16_t data = readADC(1);
            utoa(data, buff, 10);
            puts("Odczytano z ADC1:\r");
            puts(buff);
            puts("\r\n");
            xSemaphoreGive( xSemaphore1 );
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}

/**************************************************************************//**
 * \fn static void vSerial(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vAdc2(void* pvParameters)
{
    char buff[5];
    for ( ;; )
    {
        if( xSemaphoreTake( xSemaphore1, 0 ) == pdTRUE ) {
            //xCurrentTask = adc2_handle;
            uint16_t data = readADC(2);
            utoa(data, buff, 10);
            puts("Odczytano z ADC2:\r");
            puts(buff);
            puts("\r\n");
            xSemaphoreGive( xSemaphore1 );
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}
