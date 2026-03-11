//###########################################################################
//
// FILE:    f28p55x_npu.c
//
// TITLE:   NPU initialization and Support Functions.
//
//###########################################################################
//
//
// 
// C2000Ware v26.00.00.00
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
//###########################################################################

//
// Includes
//
#include <stdbool.h>
#include <stdint.h>
#include "driverlib.h"

//
// Defines
//
#define NPU_O_CTL5      0x20U    // Control Register 5 Offset
#define NPU_O_IMASK     0x08U    // Interrupt Mask Register

#pragma FUNCTION_OPTIONS(NPU_setInstrMem, "--opt_level=3 --opt_for_speed=5")
#pragma FUNCTION_OPTIONS(NPU_setParamMem, "--opt_level=3 --opt_for_speed=5")

// Returns the address of the first ACC register of the NPU module.
inline uint32_t NPU_getAccReg(void)
{
    return (ACC_BASE);
}

// Returns address of first CTL register of NPU module.
inline uint32_t NPU_getCtlReg(void)
{
    return (IPSPECIFIC_BASE + NPU_O_CTL5);
}


// Set the instruction memory of the NPU at the specified offset.
void NPU_setInstrMem(uint32_t byteOffset, uint32_t num, const uint32_t *src)
{
    volatile uint32_t *ins = (uint32_t *) (INSTRUCTION_BASE + byteOffset);

    int count_by_4 = num >> 2;
    int count_by_1 = num & 0x3;

    if (count_by_4 > 0)
    {
        while (count_by_4--)
        {
            * ins    = *src++;
            *(ins+2) = *src++;
            *(ins+4) = *src++;
            *(ins+6) = *src++;
            ins   += 8;       /* C28 16-bit addressable, access NPU memory accordingly */
        }
    }
    if (count_by_1 > 0)
    {
        while (count_by_1--)
        {
            *ins++ = *src++;
            ins++;             /* C28 16-bit addressable, access NPU memory accordingly */
        }
    }
}

// Set the parameter memory of the NPU at the specified offset.
void NPU_setParamMem(uint32_t byteOffset, uint32_t num, const uint32_t *src)
{
    volatile uint32_t *params = (uint32_t *) (RFDATA_BASE + byteOffset);

    int count_by_4 = num >> 2;
    int count_by_1 = num & 0x3;

    if (count_by_4 > 0)
    {
        while (count_by_4--)
            {
            * params    = *src++;
            *(params+2) = *src++;
            *(params+4) = *src++;
            *(params+6) = *src++;
            params   += 8;           /* C28 16-bit addressable, access NPU memory accordingly */
            }
    }
    if (count_by_1 > 0)
    {
        while (count_by_1--)
        {
            *params++ = *src++;
            params++;           /* C28 16-bit addressable, access NPU memory accordingly */
        }
    }
}

// Sets the interrupt handler for the NPU.
void NPU_setInterruptHandler(void (*handler)(void))
{
    Interrupt_disableGlobal();
    Interrupt_disable(INT_NPU);
    Interrupt_register(INT_NPU, handler);
    Interrupt_enable(INT_NPU);
    Interrupt_enableGlobal();
}

// Enables the interrupt for the NPU.
void NPU_enableInterrupt(void)
{
    HWREG(IPSTANDARD_BASE + NPU_O_IMASK) |= 0x1;
}

// Clears the interrupt ACK for the NPU.
void NPU_clearInterruptACK(void)
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}
