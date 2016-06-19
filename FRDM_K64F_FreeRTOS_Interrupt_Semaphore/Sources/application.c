/*
 * application.c
 *
 *  Created on: Jun 17, 2016
 *      Author: fabioarnez
 */


#include "FRTOS1.h"
#include "application.h"

/* End <includes> initialization, DO NOT MODIFY LINES ABOVE */


static portTASK_FUNCTION(taskInt, pvParameters)
{
  /* Write your task initialization code here ... */
	portBASE_TYPE xStatus;

	RTT1_WriteString(0,"Task for Interrupt Starts!\r\n");

	xSemaphoreTake(binary_sem, 0);

  for(;;)
  {
    /* Write your task code here ... */
	  xStatus = xSemaphoreTake(binary_sem, portMAX_DELAY); // Wait for ever - task Blocked Until Signal received
	  RTT1_WriteString(0, "Switch Pressed!!!\r\n");
  }
  /* Destroy the task */
  vTaskDelete(taskInt);
}



void applicationRun(void)
{

	vSemaphoreCreateBinary(binary_sem);

  /*Create a Task*/
  if (FRTOS1_xTaskCreate
	(
      taskInt,  /* pointer to the task */
      "taskInt", /* task name for kernel awareness debugging */
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
}
