/*
 * application.h
 *
 *  Created on: Jun 17, 2016
 *      Author: fabioarnez
 */

#ifndef SOURCES_APPLICATION_H_
#define SOURCES_APPLICATION_H_

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "RTT1.h"
#include "WAIT1.h"
#include "KSDK1.h"
#include "SYS1.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include "EInt1.h"
#include "ExtIntLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"

xSemaphoreHandle binary_sem;

void applicationRun(void);

#endif /* SOURCES_APPLICATION_H_ */
