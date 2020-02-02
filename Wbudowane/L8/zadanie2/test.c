
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

#define mainREAD_UART_TASK_PRIORITY   1

#define mainLIGHT_LED_TASK_PRIORITY 2

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vReadUART(void* pvParameters);

static void vLightLED(void* pvParameters);
QueueHandle_t Queue_delay;

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
    xTaskHandle read_handle;
    xTaskHandle light_handle;
    Queue_delay = xQueueCreate( 10, sizeof( uint16_t ) );
    xTaskCreate
        (
         vReadUART,
         "uart",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainREAD_UART_TASK_PRIORITY,
         &read_handle
        );

    xTaskCreate
        (
         vLightLED,
         "led",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainLIGHT_LED_TASK_PRIORITY,
         &light_handle
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
 * \fn static void vReadUART(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vReadUART(void* pvParameters)
{
    uart_init();
    stdin = stdout = stderr = &uart_file;

    char input[6];
    uint8_t i = 0;
    char* endPtr;
    for ( ;; )
    {
        if(Queue_delay != 0){
                                                 /*V enter*/
            while(i == 0 || (i<6 && input[i-1] != 13 && input[i-1] != ' ')){
                input[i] = getchar();
                //printf("You wrote %c\r\n", input[i]); 
                i++;
            }
            i = 0;
            uint16_t value = (uint16_t)strtol(input,&endPtr,10);
            if(value>0){
                //printf("Number %"PRIu16"\r\n", value);       
                if (xQueueSend( Queue_delay,
                                (void *)&value,
                                (TickType_t) 10) 
                    != pdPASS)
                {

                }
            //uint16_t peek = 0;
           // if(xQueuePeek(
            //               Queue_delay,
            //               &peek,
           //                (TickType_t) 10)){}
                //printf("Peek:%"PRIu16"\r\n", peek); 
            }
        }
    }

}


/**************************************************************************//**
 * \fn static void vLightLED(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vLightLED(void* pvParameters)
{
    uint16_t pvBuffer = 0;
    for ( ;; )
    {
        if(Queue_delay !=0){
            if(xQueueReceive(
                           Queue_delay,
                           &pvBuffer,
                           (TickType_t) 10)){
                    if((uint16_t)pvBuffer > 0){
                        printf("Number rec:%"PRIu16"\r\n", pvBuffer);  
                        PORTB |= _BV(PB5);
                        vTaskDelay(pvBuffer / portTICK_PERIOD_MS);
                        PORTB &= ~_BV(PB5);
                        pvBuffer = 0;
                        vTaskDelay(1000 / portTICK_PERIOD_MS);
                    }
                }
            
       }
    }
}