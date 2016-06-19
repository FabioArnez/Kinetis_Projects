/*
 * application.c
 *
 *  Created on: Jun 19, 2016
 *      Author: fabioarnez
 */
#include "FRTOS1.h"
#include "application.h"

/* End <includes> initialization, DO NOT MODIFY LINES ABOVE */

void accessSuperValuableResource(void)
{
	RTT1_WriteString(0,"	>>> Using Super Valuable Resource -_-' !!!\r\n");
}

static portTASK_FUNCTION(Task1, pvParameters)
{
  /* Write your task initialization code here ... */
	RTT1_WriteString(0,"Task1 Starts!\r\n");
	int item;
	portBASE_TYPE xStatus;
  for(;;)
  {
    /* Write your task code here ... */
	  xStatus = xSemaphoreTake(myMutex, 500/portTICK_RATE_MS);
	  if(xStatus)
	  {
		  RTT1_WriteString(0, "Task 1 Got Access:		");
		  accessSuperValuableResource();
		  xSemaphoreGive(myMutex);
	  }
	  else
	  {
		  RTT1_WriteString(0, "Task 1 FAILED to Get Access within 500 ms\r\n");
	  }

	  vTaskDelay(1000/portTICK_RATE_MS);
  }
  /* Destroy the task */
  vTaskDelete(Task1);
}


static portTASK_FUNCTION(Task2, pvParameters)
{
  /* Write your task initialization code here ... */
	RTT1_WriteString(0,"Task2 Starts!\r\n");
	int item;
	portBASE_TYPE xStatus;
  for(;;)
  {
    /* Write your task code here ... */
	  xStatus = xSemaphoreTake(myMutex, 500/portTICK_RATE_MS);
	  if(xStatus)
	  {
		  RTT1_WriteString(0, "Task 2 Got Access:		");
		  accessSuperValuableResource();
		  xSemaphoreGive(myMutex);
	  }
	  else
	  {
		  RTT1_WriteString(0, "Task 2 FAILED to Get Access within 500 ms\r\n");
	  }

	  vTaskDelay(1000/portTICK_RATE_MS);
  }
  /* Destroy the task */
  vTaskDelete(Task2);
}



void applicationRun(void)
{
	myMutex = xSemaphoreCreateMutex();

  /*Create a Task*/
  if (FRTOS1_xTaskCreate(
     Task1,  /* pointer to the task */
      "Task1", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE + 100, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 1,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }

  /*Create a Task*/
  if (FRTOS1_xTaskCreate(
     Task2,  /* pointer to the task */
      "Task2", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE + 100, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 2,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }
}

