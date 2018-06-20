/*
 * UART.c
 *
 *  Created on: Jun 10, 2018
 *      Author: dwenm
 */

#include "UART.h"

void UART_Transmit_PC(unsigned char *data, unsigned char lenght){
	unsigned char i;
	for(i=0;i<lenght;i++){
		while(SCIS1_TDRE == 0);				//attente que le bus de transmission soit libre
		SCID=data[i];						//écriture de la donnée sur le bus
	}
}

void delay(unsigned char delay){
	unsigned char i;
	for(i=0 ; i<delay ; i++);
}


