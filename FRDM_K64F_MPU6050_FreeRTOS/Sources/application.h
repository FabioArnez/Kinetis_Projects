/*
 * application.h
 *
 *  Created on: Jun 24, 2016
 *      Author: fabioarnez
 */

#ifndef SOURCES_APPLICATION_H_
	#define SOURCES_APPLICATION_H_

	/* Including needed modules to compile this module/procedure */
	#include "Cpu.h"
	#include "Events.h"
	#include "Pins1.h"
	#include "FRTOS1.h"
	#include "KSDK1.h"
	#include "UTIL1.h"
	#include "RTT1.h"
	#include "WAIT1.h"
	#include "SYS1.h"
	#include "GI2C1.h"
	#include "WAIT2.h"
	#include "CI2C1.h"
	/* Including shared modules, which are used for whole project */
	#include "PE_Types.h"
	#include "PE_Error.h"
	#include "PE_Const.h"
	#include "IO_Map.h"
	#include "PDD_Includes.h"
	#include "Init_Config.h"

	// Accelerometer Register Addresses
	#define ACCEL_X_MSB 0x3B
	#define ACCEL_X_LSB 0x3C
	#define ACCEL_Y_MSB 0x3D
	#define ACCEL_Y_LSB 0x3E
	#define ACCEL_Z_MSB 0x3F
	#define ACCEL_Z_LSB 0x40
	// Gyroscope Register Addresses
	#define GYRO_X_MSB 0x43
	#define GYRO_X_LSB 0x44
	#define GYRO_Y_MSB 0x45
	#define GYRO_Y_LSB 0x46
	#define GYRO_Z_MSB 0x47
	#define GYRO_Z_LSB 0x48

	typedef struct
	{
		int16 accX;
		int16 accY;
		int16 accZ;
	}accelData;

	typedef struct
	{
		int16 gyroX;
		int16 gyroY;
		int16 gyroZ;
	}gyroData;

	byte data_msb;
	byte data_lsb;

	//Mutex Handle
	xSemaphoreHandle myMutex;
	//QueueAccel Handle
	xQueueHandle accelQueue;
	//QueueGyro Handle
	xQueueHandle gyroQueue;


	accelData readAccelData(void);

	gyroData readGyroData(void);

	void applicationRun(void);

#endif /* SOURCES_APPLICATION_H_ */
