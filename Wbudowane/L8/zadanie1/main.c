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

#define mainLED_TASK_PRIORITY   2

#define mainSERIAL_TASK_PRIORITY 1

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vBlinkLed(void* pvParameters);

static void vSerial(void* pvParameters);

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
  //Zadanie1
  DDRB = 0;
  PORTB |= _BV(PB4);
  DDRB |= _BV(PB5);

  int8_t buffer[100];
  int16_t iter = 0;

  for(int i=0; i<100; i++) {
    buffer[i] = 0;
  }

  while (1) {
    if (buffer[iter] != 0) {
      PORTB |= _BV(PB5);
    }
    if(buffer[iter] == 0){
      PORTB &= ~_BV(PB5);
    }
    buffer[iter] = 0;
    vTaskDelay(10 / portTICK_PERIOD_MS);
    if (~PINB & _BV(PB4)) {
      vTaskDelay(1 / portTICK_PERIOD_MS);
      if (~PINB & _BV(PB4)) {
        buffer[iter] = 1;
    }  
  }
    if (iter < 100 - 1) {
      ++iter;
    }
    else{
      iter = 0;
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
  UCSR0B  &= ~_BV(RXEN0) & ~_BV(TXEN0);
  DDRD = 0b11111111;

  //Wersja 1
  while(1) {
    for (int i=0; i<7; i++) {
      PORTD = (1 << i);
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    for (int i=7; i>0; i--) {
      PORTD = (1 << i);
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
  }
  return 0;
  
}
