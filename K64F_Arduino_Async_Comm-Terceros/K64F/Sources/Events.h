/* ###################################################################
**     Filename    : Events.h
**     Project     : Ex3_UART
**     Processor   : MK64FN1M0VLL12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-06-03, 16:18, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMI - void Cpu_OnNMI(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Pins1.h"
#include "MySerial.h"
#include "ASerialLdd1.h"
#include "L_blue.h"
#include "BitIoLdd1.h"
#include "L_red.h"
#include "BitIoLdd2.h"
#include "L_green.h"
#include "BitIoLdd3.h"
#include "MyInt.h"
#include "ExtIntLdd1.h"
#include "UTIL1.h"
#include "KSDK1.h"
#include "MyWait.h"
#include "Sw3.h"
#include "ExtIntLdd2.h"

#include "helpIncludes.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Cpu_OnNMI (module Events)
**
**     Component   :  Cpu [MK64FN1M0LL12]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMI(void);


void MyInt_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  MyInt_OnInterrupt (module Events)
**
**     Component   :  MyInt [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  MySerial_OnError (module Events)
**
**     Component   :  MySerial [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void MySerial_OnError(void);

/*
** ===================================================================
**     Event       :  MySerial_OnRxChar (module Events)
**
**     Component   :  MySerial [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void MySerial_OnRxChar(void);

/*
** ===================================================================
**     Event       :  MySerial_OnTxChar (module Events)
**
**     Component   :  MySerial [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void MySerial_OnTxChar(void);

/*
** ===================================================================
**     Event       :  MySerial_OnFullRxBuf (module Events)
**
**     Component   :  MySerial [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void MySerial_OnFullRxBuf(void);

/*
** ===================================================================
**     Event       :  MySerial_OnFreeTxBuf (module Events)
**
**     Component   :  MySerial [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void MySerial_OnFreeTxBuf(void);

void Sw3_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  Sw3_OnInterrupt (module Events)
**
**     Component   :  Sw3 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
