//#############################################################################
//
//! \file   f2802x/common/source/cpu.c
//!
//! \brief  Contains the various functions related to the central processing 
//!         unit (CPU) object
//
//  Group:          C2000
//  Target Device:  TMS320F2802x
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Included Files
//
#include "DSP28x_Project.h"
#include "cpu.h"

// 
// Globals
//
CPU_Obj cpu;

//
// CPU_clearIntFlags - 
//
void
CPU_clearIntFlags(CPU_Handle cpuHandle)
{
    //
    // clear the bits
    //
    IFR = 0;

    return;
}

//
// CPU_disableDebugInt - 
//
void
CPU_disableDebugInt(CPU_Handle cpuHandle)
{
    //
    // set the bit
    //
    asm(" setc DBGM");

    return;
}

//
// CPU_disableGlobalInts - 
//
void
CPU_disableGlobalInts(CPU_Handle cpuHandle)
{
    //
    // set the bit
    //
    asm(" setc INTM");

    return;
}

//
// CPU_disableInt -
//
void
CPU_disableInt(CPU_Handle cpuHandle, const CPU_IntNumber_e intNumber)
{
    //
    // clear the bit
    //
    IER &= (~intNumber);

    return;
}

//
// CPU_disableInts - 
//
void
CPU_disableInts(CPU_Handle cpuHandle)
{
    //
    // clear the bits
    //
    IER = 0;

    return;
}

//
// CPU_disableProtectedRegisterWrite - 
//
void
CPU_disableProtectedRegisterWrite(CPU_Handle cpuHandle)
{
    //
    // clear the bits
    //
    asm(" EDIS");

    return;
}

//
// CPU_enableDebugInt - 
//
void
CPU_enableDebugInt(CPU_Handle cpuHandle)
{
    //
    // clear the bit
    //
    asm(" clrc DBGM");

    return;
}

//
// CPU_enableGlobalInts -
//
void
CPU_enableGlobalInts(CPU_Handle cpuHandle)
{
    //
    // clear the bit
    //
    asm(" clrc INTM");

    return;
}

//
// CPU_enableInt - 
//
void
CPU_enableInt(CPU_Handle cpuHandle, const CPU_IntNumber_e intNumber)
{
    //
    // set the interrupt 
    //
    IER |= intNumber;

    return;
}

//
// CPU_enableProtectedRegisterWrite -
//
void
CPU_enableProtectedRegisterWrite(CPU_Handle cpuHandle)
{
    //
    // set the bits
    //
    asm(" EALLOW");

    return;
}

//
// CPU_init - 
//
CPU_Handle
CPU_init(void *pMemory, const size_t numBytes)
{
    CPU_Handle cpuHandle;

    if(numBytes < sizeof(CPU_Obj))
    {
        return((CPU_Handle)NULL);
    }

    //
    // assign the handle
    //
    cpuHandle = (CPU_Handle)pMemory;

    return(cpuHandle);
}

//
// End of file
//

