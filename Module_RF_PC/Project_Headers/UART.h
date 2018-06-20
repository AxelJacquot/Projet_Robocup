/*
 * UART.h
 *
 *  Created on: Jun 10, 2018
 *      Author: dwenm
 */

#ifndef UART_H_
#define UART_H_

#include "Cpu.h"
#include "Events.h"
#include "SCI.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

void UART_Transmit_UC(unsigned char adr, unsigned char *data, unsigned char lenght);
void UART_Transmit_PC(unsigned char *data, unsigned char lenght);
void delay(unsigned char delay);


#endif /* UART_H_ */
