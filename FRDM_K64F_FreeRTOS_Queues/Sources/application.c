/*
 * application.c
 *
 *  Created on: Jun 17, 2016
 *      Author: fabioarnez
 */

#include "FRTOS1.h"
#include "application.h"

/* End <includes> initialization, DO NOT MODIFY LINES ABOVE */

static portTASK_FUNCTION(taskTx, pvParameters)
{
  /* Write your task initialization code here ... */
	RTT1_WriteString(0,"TaskTx Starts!\r\n");
	int item;
	portBASE_TYPE xStatus;
  for(;;)
  {
    /* Write your task code here ... */
	  RTT1_WriteString(0, "Tx Send to 'myQueue'! \r\n");
	  xStatus = xQueueSend(myQueue, &item, 500/portTICK_RATE_MS); // 500 ticks to wait

	  if(xStatus)
	  {
		  RTT1_WriteString(0, "Data Sent: OK!\r\n\r\n");
	  }
	  else
	  {
		  RTT1_WriteString(0, "Data Sent: FAILED!\r\n\r\n");
	  }

	  vTaskDelay(500/portTICK_RATE_MS);
  }
  /* Destroy the task */
  vTaskDelete(taskTx);
}


static portTASK_FUNCTION(taskRx, pvParameters)
{
  /* Write your task initialization code here ... */
	RTT1_WriteString(0,"TaskRx Starts!\r\n");
	int item;
	portBASE_TYPE xStatus;
  for(;;)
  {
    /* Write your task code here ... */
	  xStatus = xQueueReceive(myQueue,&item, 500/portTICK_RATE_MS);
	  if(xStatus)
	  {
		  RTT1_WriteString(0, "				Data Receive: OK!\r\n\r\n");
	  }
	  else
	  {
		  RTT1_WriteString(0, "			Data Receive: FAILED!\r\n\r\n");
	  }
  }
  /* Destroy the task */
  vTaskDelete(taskRx);
}



void applicationRun(void)
{
	myQueue = xQueueCreate(2, sizeof(int));

  /*Create a Task*/
  if (FRTOS1_xTaskCreate(
     taskTx,  /* pointer to the task */
      "TaskTx", /* task name for kernel awareness debugging */
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
     taskRx,  /* pointer to the task */
      "TaskRx", /* task name for kernel awareness debugging */
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
