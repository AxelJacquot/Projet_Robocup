/*
 * UART.c
 *
 *  Created on: Jun 10, 2018
 *      Author: dwenm
 */

#include "UART.h"

void UART_Transmit_UC(unsigned char adr, unsigned char *data, unsigned char lenght){
	unsigned char i;
	while(SCIS1_TDRE == 0);
	SCID = adr;
	for(i=0;i<lenght;i++){
		delay(253);
		while(SCIS1_TDRE == 0);
		SCID = data[i];
	}
	return;
}

void delay(unsigned char delay){
	unsigned char i;
	for(i=0 ; i<delay ; i++);
}


