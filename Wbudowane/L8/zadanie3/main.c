/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include <avr/interrupt.h>
#include "queue.h"


#include <avr/io.h>


#include <stdio.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define mainLED_TASK_PRIORITY 1

#define mainSERIAL_TASK_PRIORITY 2

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vBlinkLed(void* pvParameters);

static void vSerial(void* pvParameters);

xTaskHandle blink_handle;
xTaskHandle serial_handle;
QueueHandle_t xQueueIn, xQueueOut;


ISR(USART_RX_vect) {
  if (xQueueIsQueueEmptyFromISR(xQueueOut) == pdFALSE) {
       uint8_t data = UDR0;
       BaseType_t xHigherPriorityTaskWoken = pdFALSE;
       xQueueSendFromISR( xQueueOut, &data, &xHigherPriorityTaskWoken );
  }

}

// ISR(USART_TX_vect) {

// }

ISR(USART_UDRE_vect) {
    if (xQueueIsQueueEmptyFromISR(xQueueIn) == pdFALSE) {
        char cRxedChar;
        BaseType_t xTaskWokenByReceive = pdFALSE;
        xQueueReceiveFromISR( xQueueIn,
                            ( void * ) &cRxedChar,
                            &xTaskWokenByReceive);
        UDR0 = cRxedChar;
    }
}

int uart_transmit(char data, FILE *stream) {
  // while (!(UCSR0A & _BV(UDRE0))) taskYIELD();
  // UDR0 = c;
  // return 0;
  // czekaj aż transmiter gotowy
  if (uxQueueSpacesAvailable(xQueueIn) == 0) {
    while(!(UCSR0A & _BV(UDRE0))) vTaskDelay(2 / portTICK_PERIOD_MS);
  }
  UCSR0B &= ~_BV(UDRIE0);
  if( xQueueIn != 0 ) {
    xQueueSend( xQueueIn, ( void * ) &data, ( TickType_t ) 10);
  }
  UCSR0B |= _BV(UDRIE0);
  return 0;
}

int uart_receive(FILE *stream) {
  // while (!(UCSR0A & _BV(RXC0))) taskYIELD();
  // return UDR0;
  //czekaj aż znak dostępny
  char c;
  uint8_t pxRxedMessage = 0;
  if (uxQueueSpacesAvailable(xQueueOut) == 10) {
    while (!(UCSR0A & _BV(RXC0))) vTaskDelay(2 / portTICK_PERIOD_MS);
    return UDR0;
  }
  else{
    UCSR0B &= ~_BV(RXCIE0);
    if (xQueueOut != 0) {
      if(xQueueReceive( xQueueOut, &( pxRxedMessage ), ( TickType_t ) 10 ) ) {
        c = pxRxedMessage;
      }
    }
    UCSR0B |= _BV(RXCIE0);    
  }

  return c;
}


/******************************************************************************
 * Public function definitions.
 ******************************************************************************/

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

    xQueueIn = xQueueCreate( 10, sizeof( uint8_t ) );
    xQueueOut = xQueueCreate( 10, sizeof( uint8_t ) );
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

    for ( ;; )
    {
        PORTB ^= _BV(PB5);
        vTaskDelay(500 / portTICK_PERIOD_MS);
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
    sei();
    char input;
    for ( ;; )
    {
        puts("Hello World\r\n");
        input = getchar();
        
        printf("You wrote %c\r\n", input); 
    }
}
