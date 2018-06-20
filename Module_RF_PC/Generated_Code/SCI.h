/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : SCI.h
**     Project     : Module_RF_PC
**     Processor   : MC9S08QE8CLC
**     Component   : Init_SCI
**     Version     : Component 01.155, Driver 01.22, CPU db: 3.00.049
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-06-20, 13:24, # CodeGen: 0
**     Abstract    :
**          This component encapsulates Serial Communications Interface module
**          This modules allows asynchronous communications with peripheral
**          devices and other microcontroller units (MCU).
**     Settings    :
**          Component name                                 : SCI
**          Device                                         : SCI
**          Settings
**            Baud rate divisor                            : 6
**            Baud rate                                    : 103765.333 baud
**            Loop mode                                    : Disabled
**            Receiver source select                       : Loop mode
**            TxD1 pin direction                           : Input
**            Data Format                                  : 8 bits
**            Stop in Wait mode                            : Disabled
**            Wake up                                      : Idle line wakeup
**            Idle character counting                      : After start bit
**            Parity                                       : None
**            Send break                                   : Disabled
**          Pins
**            RxD pin allocation                           : Enabled
**            RxD pin                                      : PTB0_KBIP4_RxD_ADP4
**            RxD pin signal                               : 
**            TxD pin                                      : PTB1_KBIP5_TxD_ADP5
**            TxD pin signal                               : 
**          Interrupts
**            Tx interrupt
**              Interrupt                                  : Vscitx
**              Transmit interrupt                         : Disabled
**              Transmition complete interrupt             : Disabled
**              ISR name                                   : 
**            Rx interrupt                                 : 
**              Interrupt                                  : Vscirx
**              Receive interrupt                          : Enabled
**              Idle line interrupt                        : Disabled
**              ISR name                                   : Receive_UART
**            Error interrupt                              : 
**              Interrupt                                  : Vscierr
**              Receive framing error interrupt            : Disabled
**              Receive noise error interrupt              : Disabled
**              Receive overrun interrupt                  : Disabled
**              Receive parity error interrupt             : Disabled
**              ISR name                                   : 
**          Initialization                                 : 
**            Call Init in CPU init. code                  : yes
**            Transmitter                                  : Enabled
**            Receiver                                     : Enabled
**     Contents    :
**         Init - void SCI_Init(void);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file SCI.h
** @version 01.22
** @brief
**          This component encapsulates Serial Communications Interface module
**          This modules allows asynchronous communications with peripheral
**          devices and other microcontroller units (MCU).
*/         
/*!
**  @addtogroup SCI_module SCI module documentation
**  @{
*/         

#ifndef __SCI
#define __SCI

/* MODULE SCI. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited components */

#include "Cpu.h"




/*
** ===================================================================
** The interrupt service routine must be implemented by user in one
** of the user modules (see SCI.c file for more information).
** ===================================================================
*/
__interrupt void Receive_UART(void);
void SCI_Init(void);
/*
** ===================================================================
**     Method      :  SCI_Init (component Init_SCI)
**     Description :
**         This method initializes registers of the SCI module
**         according to this Peripheral Initialization Component settings.
**         Call this method in user code to initialize the module.
**         By default, the method is called by PE automatically; see
**         "Call Init method" property of the component for more details.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END SCI. */

#endif /* ifndef __SCI */
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