//#############################################################################
//
// FILE:   gateDriver.h
//
// TITLE:  Generic Gate Driver Header File
//
//#############################################################################
// $Copyright:
// Copyright (C) 2026 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef GATEDRIVER_H
#define GATEDRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MCPC029_GATE_DRIVER
#include "drv8329.h"
#include "drv8329_spi_hal.h"

// Interface APIs
#define DRV_Interface_ReadRegister      DRV8329_SPI_HAL_ReadRegister
#define DRV_Interface_WriteRegister     DRV8329_SPI_HAL_WriteRegister

// Gate Driver APIs
#define DRV_ConfigureParams             DRV8329_configureParams
#define DRV_ConfigureParamsDefault      DRV8329_configureParamsDefault
#define DRV_ResetFaultStatus            DRV8329_resetFaultStatus
#define DRV_GetFaultStatus              DRV8329_getFaultStatus
#define DRV_GetAllRegisters             DRV8329_getAllRegisters

#define DRV_ClearFaults                 DRV8329_clearFaults
#define DRV_DisableSnsFault             DRV8329_disableSnsFault
#define DRV_EnableSnsFault              DRV8329_enableSnsFault
#define DRV_DisableVdsFault             DRV8329_disableVdsFault
#define DRV_EnableVdsFault              DRV8329_enableVdsFault
#define DRV_DisableBstFault             DRV8329_disableBstFault
#define DRV_EnableBstFault              DRV8329_enableBstFault
#define DRV_DisableDrv                  DRV8329_disableDrv
#define DRV_EnableDrv                   DRV8329_enableDrv
#define DRV_DisableTcp                  DRV8329_disableTcp
#define DRV_EnableTcp                   DRV8329_enableTcp
#define DRV_SetOtsRecoveryMode          DRV8329_setOtsRecoveryMode
#define DRV_EnableVdsLevelSelection     DRV8329_enableVdsLevelSelectionThroughSpi
#define DRV_DisableVdsLevelSelection    DRV8329_disableVdsLevelSelectionThroughSpi
#define DRV_SetVdsLevel                 DRV8329_setVdsLevel

extern volatile DRV8329_FAULT_STATUS_T gateDriverFaultReport;
extern volatile DRV8329_FAULT_STATUS_T gateDriverFaultAction;

#endif

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* GATEDRIVER_H */
