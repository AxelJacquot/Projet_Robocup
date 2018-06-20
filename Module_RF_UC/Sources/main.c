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
#include "ADC.h"
#include "PTB.h"
#include "SCI.h"
#include "SPI_RF.h"
#include "RF.h"
#include "UART.h"
#include "CAN.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#define ADR_JEAN 0x69
#define ADR_NICO 0x42
#define LENGHT_JEAN 0x02
#define LENGHT_NICO 0x05

unsigned char test=0;
unsigned char RF_SEND[7]={0x55,0x56,0x57,0x58,0x59,0x5A,0x5B};
unsigned char RF_RECEIVE[7];
volatile unsigned char receive_data[2];
volatile unsigned char status_UART=0;
volatile unsigned char data_UART[4];
volatile unsigned char result;
volatile unsigned char receive;
unsigned char i;
unsigned char cpt=0;

ISR( Receive_UART) {									//fonction de lecture UART losrque le programme se trouve sur le microcontroleur du robot
	unsigned char status;
	unsigned char data;

	status=SCIS1;
	data=SCID;											//acquisition de la donnée reçu par l'UART

	if (cpt == 0 && data == ADR_JEAN){					//Vérification qu'il s'agit de la bonne adresse
		receive_data[0]=data;							//stockage de la donnée sur la premiere place du tableau si vrai
		cpt=1;	
	}
	else if(receive_data[0] == ADR_JEAN && cpt != 0){	//Si la premiere donnée reçu est la bonne adresse
		receive_data[cpt]=data;							//stockage de la donnée
		cpt++;	
	}
	else{												//si la première donnée est fausse on attent la fin de la transmission
		cpt++;
		if (cpt == LENGHT_JEAN)
			cpt=0;
		return;
	}

	if (cpt == LENGHT_JEAN){										//Si toutes les données on été reçu alors on léve un flag le signalant
		status_UART = 1;
		receive_data[0]=0;								//RàZ du premier octet du tableau correspondant à l'adresse
		cpt=0;											//RàZ du nombre de donnée reçu
	}	


	return;
	//0: The routine should include the following actions to obtain
	//       correct functionality of the hardware.
	// Receive and idle interrupt flag are cleared by reading the status register
	// and then reading the data register.
	// Example: Status = SCIS1;
	//          Data = SCID;

}

ISR(TPM1_IRQ)
{	
	if (status_UART == 1){
				status_UART = 0;								//RàZ du flag signalant la réception de l'UART
				RF_SEND[6]=receive_data[1];						//stockage de la donnée de JEAN pour l'envoie RF
	}
	result=RX_RF(&RF_RECEIVE[0],5);						//réception des données du module Rf
	Config_Register(WRITE_STATUS,0x70);				//RàZ du status du module
	if (result == 0x55){
		UART_Transmit_UC(ADR_NICO,&RF_RECEIVE[0],4);					//envoie des données des moteurs à NICO
		if(RF_RECEIVE[4] == 0x01)										//Vérification qu'une demainde de kick a été effectué
			UART_Transmit_UC(ADR_JEAN,&RF_RECEIVE[0],4);					//envoie de la demande de kick
	}
	Batterie(&RF_SEND[4]);								//Récupération du taux de charge de la baterie
	TX_RF(&RF_SEND[0],7);								//Transmission des données du robot vers le PC




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
