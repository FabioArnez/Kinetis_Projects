/*
 * application.c
 *
 *  Created on: Jun 24, 2016
 *      Author: fabioarnez
 */
#include "FRTOS1.h"
#include "application.h"

accelData readAccelData(void)
{
	accelData myAccel;

	GI2C1_SelectSlave(0x68);
	//Read Accel X
	GI2C1_ReadByteAddress8(0x68, ACCEL_X_MSB, &data_msb);
	GI2C1_ReadByteAddress8(0x68, ACCEL_X_LSB, &data_lsb);
	WAIT1_Waitms(10);
	myAccel.accX = (int16)(((int8)data_msb<<8)|(int8)data_lsb);
	//Read Accel Y
	GI2C1_ReadByteAddress8(0x68, ACCEL_Y_MSB, &data_msb);
	GI2C1_ReadByteAddress8(0x68, ACCEL_Y_LSB, &data_lsb);
	WAIT1_Waitms(10);
	myAccel.accY = (int16)(((int8)data_msb<<8)|(int8)data_lsb);
	//Read Accel Z
	GI2C1_ReadByteAddress8(0x68, ACCEL_Z_MSB, &data_msb);
	GI2C1_ReadByteAddress8(0x68, ACCEL_Z_LSB, &data_lsb);
	WAIT1_Waitms(10);
	myAccel.accZ = (int16)(((int8)data_msb<<8)|(int8)data_lsb);

	GI2C1_UnselectSlave();

	return myAccel;
}

gyroData readGyroData(void)
{
	gyroData myGyro;

	GI2C1_SelectSlave(0x68);
	//Read Gyro X
	GI2C1_ReadByteAddress8(0x68, GYRO_X_MSB, &data_msb);
	GI2C1_ReadByteAddress8(0x68, GYRO_X_LSB, &data_lsb);
	WAIT1_Waitms(10);
	myGyro.gyroX = (int16)(((int8)data_msb<<8)|(int8)data_lsb);
	//Read Gyro Y
	GI2C1_ReadByteAddress8(0x68, GYRO_Y_MSB, &data_msb);
	GI2C1_ReadByteAddress8(0x68, GYRO_Y_LSB, &data_lsb);
	WAIT1_Waitms(10);
	myGyro.gyroY = (int16)(((int8)data_msb<<8)|(int8)data_lsb);
	//Read Gyro Z
	GI2C1_ReadByteAddress8(0x68, GYRO_Z_MSB, &data_msb);
	GI2C1_ReadByteAddress8(0x68, GYRO_Z_LSB, &data_lsb);
	WAIT1_Waitms(10);
	myGyro.gyroZ = (int16)(((int8)data_msb<<8)|(int8)data_lsb);

	GI2C1_UnselectSlave();

	return myGyro;
}

static portTASK_FUNCTION(taskAccel, pvParameters)
{
  /* Write your task initialization code here ... */
	RTT1_WriteString(0,"taskAccel Starts!\r\n");
	accelData myAccelItem;
	portBASE_TYPE xStatus;

  for(;;)
  {
    /* Write your task code here ... */
	  // Take Mutex for I2C Bus
	  xStatus = xSemaphoreTake(myMutex, 100/portTICK_RATE_MS);
	  if(xStatus)
	  {
		  //RTT1_WriteString(0, "'taskAccel' Got Access to I2C-Bus:\r\n");
		  myAccelItem = readAccelData();
		  xSemaphoreGive(myMutex);
	  }
	  else
	  {
		  RTT1_WriteString(0, "'taskAccel' FAILED to Get Access to I2C-Bus within 100 ms\r\n");
	  }

	  // Send accelData
	  xStatus = xQueueSend(accelQueue, &myAccelItem, 50/portTICK_RATE_MS);

	  vTaskDelay(10/portTICK_RATE_MS);
  }
  /* Destroy the task */
  vTaskDelete(taskAccel);
}


static portTASK_FUNCTION(taskGyro, pvParameters)
{
  /* Write your task initialization code here ... */
	RTT1_WriteString(0,"taskGyro Starts!\r\n");
	gyroData myGyroItem;
	portBASE_TYPE xStatus;

  for(;;)
  {
    /* Write your task code here ... */
	  // Take Mutex for I2C Bus
	  xStatus = xSemaphoreTake(myMutex, 100/portTICK_RATE_MS);
	  if(xStatus)
	  {
		  //RTT1_WriteString(0, "'taskGyro' Got Access to I2C-Bus:\r\n");
		  myGyroItem = readGyroData();
		  xSemaphoreGive(myMutex);
	  }
	  else
	  {
		  RTT1_WriteString(0, "'taskGyro' FAILED to Get Access to I2C-Bus within 100 ms\r\n");
	  }

	  // Send gyroData
	  xStatus = xQueueSend(gyroQueue, &myGyroItem, 50/portTICK_RATE_MS);

	  vTaskDelay(10/portTICK_RATE_MS);
  }
  /* Destroy the task */
  vTaskDelete(taskGyro);
}


static portTASK_FUNCTION(taskPrint, pvParameters)
{
  /* Write your task initialization code here ... */
	RTT1_WriteString(0,"taskPrint Starts!\r\n");
	gyroData rcvGyroItem;
	accelData rcvAccelItem;
	char dataS[10];
	portBASE_TYPE xStatus;

  for(;;)
  {
    /* Write your task code here ... */
	  xStatus = xQueueReceive(accelQueue, &rcvAccelItem, 10/portTICK_RATE_MS);
	  xStatus = xQueueReceive(gyroQueue, &rcvGyroItem, 10/portTICK_RATE_MS);

	  UTIL1_Num16sToStr(dataS, sizeof(dataS), rcvAccelItem.accX);
	  RTT1_WriteString(0, "AccX is:	");
	  RTT1_WriteString(0, dataS);
	  RTT1_WriteString(0, "\r\n");

	  UTIL1_Num16sToStr(dataS, sizeof(dataS), rcvGyroItem.gyroX);
	  RTT1_WriteString(0, "GyroX is:	");
	  RTT1_WriteString(0, dataS);
	  RTT1_WriteString(0, "\r\n");

	  vTaskDelay(1000/portTICK_RATE_MS);
  }
  /* Destroy the task */
  vTaskDelete(taskPrint);
}


static portTASK_FUNCTION(TaskHWInit, pvParameters)
{
  /* Write your task initialization code here ... */
	RTT1_WriteString(0,"TaskHWInit Starts!\r\n");
	GI2C1_Init();

	//Wake Up MPU6050!
	GI2C1_SelectSlave(0x68);
	GI2C1_WriteByteAddress8(0x68, 0x6B, 0x00);
	GI2C1_UnselectSlave();

	RTT1_WriteString(0,"MPU6050 Started!!!\r\n");

	//Suspend Task!!
	RTT1_WriteString(0,"Preparing To Suspend Task!\r\n");
	vTaskSuspend(NULL); //'NULL to suspend this task'

  for(;;)
  {
    /* Write your task code here ... */
	  vTaskDelay(1000/portTICK_RATE_MS);
  }
  /* Destroy the task */
  vTaskDelete(TaskHWInit);
}


void applicationRun(void)
{

	myMutex = xSemaphoreCreateMutex();

	accelQueue = xQueueCreate(2, sizeof(accelData));
	gyroQueue = xQueueCreate(2, sizeof(gyroData));

  /*Create a Task*/
  if (FRTOS1_xTaskCreate(
     taskAccel,  /* pointer to the task */
      "taskAccel", /* task name for kernel awareness debugging */
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
     taskGyro,  /* pointer to the task */
      "taskGyro", /* task name for kernel awareness debugging */
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
     taskPrint,  /* pointer to the task */
      "taskPrint", /* task name for kernel awareness debugging */
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

  /*Create a Task*/
  if (FRTOS1_xTaskCreate(
     TaskHWInit,  /* pointer to the task */
      "TaskHWInit", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE + 0, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 3,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }

}
