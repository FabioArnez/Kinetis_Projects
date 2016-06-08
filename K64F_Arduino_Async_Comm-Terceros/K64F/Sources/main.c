/* ###################################################################
**     Filename    : main.c
**     Project     : Ex3_UART
**     Processor   : MK64FN1M0VLL12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-06-03, 16:18, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
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
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
#include "helpIncludes.h"

/* User includes (#include below this line is not maintained by Processor Expert) */


volatile bool flag=FALSE;
volatile bool flag2=FALSE;
volatile bool serialGPSRxFlag=FALSE;
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  for(;;) {

	  if(flag==FALSE && flag2==FALSE ){
		  L_green_NegVal();
		  MyWait_Waitms(500);


	  }
	  else{
		  if(flag==TRUE){
			  printf("Interrupcion1 \r\n");
			  L_red_PutVal(0);
			  MyWait_Waitms(500);
			  L_red_PutVal(1);
			  MyWait_Waitms(500);
			  flag=FALSE;
			  strcpy(arduinotx,"Hola Arduino        ");
			  MySerial_SendBlock(arduinotx,sizeof(arduinotx),&tx);
			  printf("%s \r\n",arduinotx);

		  }
		  else{
			  if(flag2==TRUE){
				  printf("Interrupcion2 \r\n");
				  L_blue_PutVal(0);
				  MyWait_Waitms(500);
				  L_blue_PutVal(1);
				  MyWait_Waitms(500);
				  flag2=FALSE;
				  strcpy(arduinotx,"Hola Fabio          ");
				  MySerial_SendBlock(arduinotx,sizeof(arduinotx),&tx);
				  printf("%s \r\n",arduinotx);

			  }
		  }

	  }

	  if(serialGPSRxFlag==TRUE){
		  printf("en main \r\n");
		  serialGPSRxFlag=false;
		  strncpy(arduinorxBuffer,arduinorx,sizeof(arduinorxBuffer));
		  printf("%s \r\n",arduinorxBuffer);


	  }




  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
