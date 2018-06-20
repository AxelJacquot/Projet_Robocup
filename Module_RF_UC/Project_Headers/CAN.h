/*
 * CAN.h
 *
 *  Created on: Jun 10, 2018
 *      Author: dwenm
 */

#ifndef CAN_H_
#define CAN_H_

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "ADC.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

void Batterie(unsigned char *bat);

#endif /* CAN_H_ */
