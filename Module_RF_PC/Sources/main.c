/* ###################################################################
 **     Filename    : main.c
 **     Project     : Module_RF_Multi
 **     Processor   : MC9S08QE8CLC
 **     Version     : Driver 01.12
 **     Compiler    : CodeWarrior HCS08 C Compiler
 **     Date/Time   : 2018-06-06, 09:14, # CodeGen: 0
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
 ** @version 01.12
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
#include "SPI.h"
#include "PTA.h"
#include "TPM1.h"
#include "PTB.h"
#include "SCI.h"
#include "SPI_RF.h"
#include "RF.h"
#include "UART.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

unsigned char test=0;
unsigned char Test_RF[]={0x55,0x56,0x57,0x58,0x59};
unsigned char RF_RECEIVE[8];
volatile unsigned char receive_data[5];
volatile unsigned char status_UART=0;
volatile unsigned char data_UART[4];
volatile unsigned char result;
volatile unsigned char receive;
unsigned char i;
unsigned char cpt=0;

ISR( Receive_UART){								//fonction de lecture UART losrque le programme se trouve sur le microcontroleur du pc
		unsigned char status;
		
		
		status=SCIS1;
		receive_data[cpt]=SCID;					//récupération de la donnée se trouvant 
		cpt++; 									//passage à la donnée suivante pour la stockée
		if (cpt == 5){							//si cpt équivaut à cela signifit que la réception est fini 
			status_UART = 1;					//lever d'un flag pour signaler la fin de la réception 
			cpt=0;								//placement sur le premier espace mémoire du tableau
		}			
		return;
		
  // NOTE: The routine should include the following actions to obtain
  //       correct functionality of the hardware.
  // Receive and idle interrupt flag are cleared by reading the status register
  // and then reading the data register.
  // Example: Status = SCIS1;
  //          Data = SCID;

}

ISR(TPM1_IRQ)
{
	result=RX_RF(&RF_RECEIVE[0],7);						//réception des données du module Rf
	Config_Register(WRITE_STATUS,0x70);				//RàZ du status du module
	if (result == 0x55 || result == 0xff){
		UART_Transmit_PC(&RF_RECEIVE[0],8);					//envoie des données vers le pc
	}
	if (status_UART == 1){
		status_UART = 0;								//RàZ du flag signalant la réception de l'UART
		TX_RF(&receive_data[0],5);						//envoie des données reçu via l'UART vers le robot
	}

	// NOTE: The routine should include the following actions to obtain
	//       correct functionality of the hardware.
	//
	//       The TPM1SC register should be read and
	//       TOF bit must be set to 0 to clear the interrupt request.
	//       Example: TPM1SC;
	//                TPM1SC_TOF = 0;
}

void main(void){
	/* Write your local variable definition here */
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/
	RF_Init();				//Initiialisation du module RF
	TX_ADDR();				//Réglage de l'adresse de transmission du module
	RX_ADDR();				//Réglage de l'adresse de réception du module
	
	RF_RECEIVE[7]='\0';			//réglage d'un octet de fin de transmission pour l'UART
	/* Write your code here */
	/* For example: for(;;) { } */
	for(;;){
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
 **     This file was created by Processor Expert 10.3 [05.09]
 **     for the Freescale HCS08 series of microcontrollers.
 **
 ** ###################################################################
 */
