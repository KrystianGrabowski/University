/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <avr/io.h>

#include <stdlib.h>
#include <stdio.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define mainLED_TASK_PRIORITY   2

#define mainSERIAL_TASK_PRIORITY  1

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vBlinkLed(void* pvParameters);

static void vSerial(void* pvParameters);

QueueHandle_t xQueue;

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
    xTaskHandle blink_handle;
    xTaskHandle serial_handle;
    xQueue = xQueueCreate( 10, sizeof( uint16_t ) );

    xTaskCreate
        (
         vSerial,
         "serial",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainSERIAL_TASK_PRIORITY,
         &serial_handle
        );

    xTaskCreate
        (
         vBlinkLed,
         "blink",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainLED_TASK_PRIORITY,
         &blink_handle
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
    uint16_t pxRxedMessage = 0;
    for ( ;; )
    {
        if( xQueue != 0 ) { 
            if(xQueueReceive( xQueue, &( pxRxedMessage ), ( TickType_t ) 10 ) )
            {
                printf("Odczytano %"PRIu16"\r\n", pxRxedMessage); 
                PORTB |= _BV(PB5);
                vTaskDelay(pxRxedMessage / portTICK_PERIOD_MS);
                PORTB &= ~_BV(PB5);
                vTaskDelay(500 / portTICK_PERIOD_MS);
            }
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
static void vSerial(void* pvParameters)
{
    uart_init();
    stdin = stdout = stderr = &uart_file;
    char buffer[4];
    char *ptr;
    for ( ;; )
    {
        if( xQueue != 0 ) {
            char input = 'e';
            for (uint8_t i = 0; i<4; i++)
            {
                buffer[i] = getchar();
            }
            uint16_t ll = (uint16_t)strtol(buffer, &ptr, 10);
            if(xQueueSend( xQueue, ( void * ) &ll, ( TickType_t ) 10) != pdPASS) {
                puts("Kolejka pelna!\r\n");
            }
        }
        
    }
}
