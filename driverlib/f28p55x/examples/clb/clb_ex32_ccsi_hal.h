//#############################################################################
//
// FILE:   clb_ex32_ccsi_hal.h
//
// TITLE:  Prototype definitions for CCSI hardware abstraction layer.
//
//#############################################################################
// $TI Release: $
// 
// 
// C2000Ware v5.03.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

#include <clb_ex32_lp5891.h>
#include <clb_ex32_system_info.h>
#include "driverlib.h"
#include "board.h"

#ifndef CCSI_HAL_H_
#define CCSI_HAL_H_

extern uint32_t clbXmtBuffer[MAX_DATA_LENGTH]; //Stores the data bytes to be sent
extern uint16_t clbRcvBuffer[MAX_DATA_LENGTH]; //Stores the bytes received
extern volatile uint16_t clbXmtDone;

void CCSI_HAL_initClbLogic(void);
void CCSI_HAL_setupInterrupts(void);
void CCSI_HAL_startLedClocks(void);
void CCSI_HAL_clbTransferBlocking(uint32_t *xmtBuffer, uint32_t numXmtWords);
void CCSI_HAL_clbTransferNonBlocking(uint32_t *xmtBuffer, uint32_t numXmtWords);
int16_t CCSI_HAL_clbRxRingBuffRead (uint16_t *data);
void CCSI_HAL_clbSyncTransferStart(void);
void CCSI_HAL_ringBufferReset(void);
void CCSI_HAL_enableClbReceiver(void);
void CCSI_HAL_disableClbReceiver(void);

#endif /* CCSI_HAL_H_ */
