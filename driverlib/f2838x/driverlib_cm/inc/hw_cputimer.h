//###########################################################################
//
// FILE:    hw_cputimer.h
//
// TITLE:   Definitions for the CPUTIMER registers.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
//###########################################################################

#ifndef HW_CPUTIMER_H
#define HW_CPUTIMER_H

//*************************************************************************************************
//
// The following are defines for the CPUTIMER register offsets
//
//*************************************************************************************************
#define CPUTIMER_O_TIM   0x0U   // Timer counter register
#define CPUTIMER_O_PRD   0x4U   // Timer period register
#define CPUTIMER_O_TCR   0x8U   // Timer control register
#define CPUTIMER_O_TPR   0xCU   // Timer prescaler register


//*************************************************************************************************
//
// The following are defines for the bit fields in the TCR register
//
//*************************************************************************************************
#define CPUTIMER_TCR_TSS    0x10U     // Timer Stop Status
#define CPUTIMER_TCR_TRB    0x20U     // Timer Reload Bit
#define CPUTIMER_TCR_SOFT   0x400U    // SOFT stop enable
#define CPUTIMER_TCR_FREE   0x800U    // Free run enable
#define CPUTIMER_TCR_TIE    0x4000U   // Timer Interrupt Enable
#define CPUTIMER_TCR_TIF    0x8000U   // Timer Intrerrupt Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the TPR register
//
//*************************************************************************************************
#define CPUTIMER_TPR_TDDRL_S   0U
#define CPUTIMER_TPR_TDDRL_M   0xFFU         // Timer Divide Down Register Low
#define CPUTIMER_TPR_PSCL_S    8U
#define CPUTIMER_TPR_PSCL_M    0xFF00U       // Prescaler Counter low
#define CPUTIMER_TPR_TDDRH_S   16U
#define CPUTIMER_TPR_TDDRH_M   0xFF0000U     // Timer Divide Down Register High
#define CPUTIMER_TPR_PSCH_S    24U
#define CPUTIMER_TPR_PSCH_M    0xFF000000U   // Prescaler Counter high



#endif
