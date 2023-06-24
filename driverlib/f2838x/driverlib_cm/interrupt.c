//###########################################################################
//
// FILE:   interrupt.c
//
// TITLE:  Driver for the NVIC Interrupt Controller.
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

#include "interrupt.h"

//*****************************************************************************
//
// RAM Vector Table to be used as srcVectorTable in
// Interrupt_initRAMVectorTable(). Set the size of the vector table to the
// largest number of interrupts of any device.
//
//*****************************************************************************
#ifndef USE_RTOS
#pragma DATA_ALIGN(vectorTableRAM, 1024U)
#pragma DATA_SECTION(vectorTableRAM, ".vtable")
#pragma WEAK(vectorTableRAM)
void (*vectorTableRAM[NUM_INTERRUPTS])(void);
#endif

//*****************************************************************************
//
// Interrupt_enable()
//
//*****************************************************************************
void
Interrupt_enable(uint32_t interruptNum)
{
    //
    // Check the arguments.
    //
    ASSERT(interruptNum < NUM_INTERRUPTS);

    //
    // Enable the interrupt.
    //
    if(interruptNum == FAULT_MPU)
    {
        HWREG(NVIC_BASE + NVIC_O_SHCSRS) |= NVIC_SHCSRS_MEMFAULTENA;
    }
    else if(interruptNum == FAULT_BUS)
    {
        HWREG(NVIC_BASE + NVIC_O_SHCSRS) |= NVIC_SHCSRS_BUSFAULTENA;
    }
    else if(interruptNum == FAULT_USAGE)
    {
        HWREG(NVIC_BASE + NVIC_O_SHCSRS) |= NVIC_SHCSRS_USGFAULTENA;
    }
    else if(interruptNum == FAULT_SYSTICK)
    {
        HWREG(NVIC_BASE + NVIC_O_SYST_CSR) |= NVIC_SYST_CSR_TICKINT;
    }
    else if(interruptNum >= 16U)
    {
        HWREG(NVIC_BASE + NVIC_O_ISER0 +
              (NVIC_OFFSET_INC * ((interruptNum - 16U) / 32U))) =
        (uint32_t)1U << ((interruptNum - 16U) & 0x1FU);
    }
    else
    {
        //
        // Do Nothing.
        //
    }
}

//*****************************************************************************
//
// Interrupt_disable()
//
//*****************************************************************************
void
Interrupt_disable(uint32_t interruptNum)
{
    //
    // Check the arguments.
    //
    ASSERT(interruptNum <= NUM_INTERRUPTS);

    //
    // Disable the interrupt.
    //
    if(interruptNum == FAULT_MPU)
    {
        HWREG(NVIC_BASE + NVIC_O_SHCSRS)   &= ~NVIC_SHCSRS_MEMFAULTENA;
    }
    else if(interruptNum == FAULT_BUS)
    {
        HWREG(NVIC_BASE + NVIC_O_SHCSRS)   &= ~NVIC_SHCSRS_BUSFAULTENA;
    }
    else if(interruptNum == FAULT_USAGE)
    {
        HWREG(NVIC_BASE + NVIC_O_SHCSRS)   &= ~NVIC_SHCSRS_USGFAULTENA;
    }
    else if(interruptNum == FAULT_SYSTICK)
    {
        HWREG(NVIC_BASE + NVIC_O_SYST_CSR) &= ~NVIC_SYST_CSR_TICKINT;
    }
    else if(interruptNum >= 16U)
    {
        HWREG(NVIC_BASE + NVIC_O_ICER0 +
              (NVIC_OFFSET_INC * ((interruptNum - 16U) / 32U))) =
        (uint32_t)1U << ((interruptNum - 16U) & 0x1FU);
    }
    else
    {
        //
        // Do Nothing.
        //
    }
}

//*****************************************************************************
//
// Interrupt_isEnabled()
//
//*****************************************************************************
bool
Interrupt_isEnabled(uint32_t interruptNum)
{
    uint32_t status;

    //
    // Check the arguments.
    //
    ASSERT(interruptNum <= NUM_INTERRUPTS);

    //
    // Return the interrupt status
    //
    if(interruptNum == FAULT_MPU)
    {
        status = HWREG(NVIC_BASE + NVIC_O_SHCSRS) & NVIC_SHCSRS_MEMFAULTENA;
    }
    else if(interruptNum == FAULT_BUS)
    {
        status = HWREG(NVIC_BASE + NVIC_O_SHCSRS) & NVIC_SHCSRS_BUSFAULTENA;
    }
    else if(interruptNum == FAULT_USAGE)
    {
        status = HWREG(NVIC_BASE + NVIC_O_SHCSRS) & NVIC_SHCSRS_USGFAULTENA;
    }
    else if(interruptNum == FAULT_SYSTICK)
    {
        status = HWREG(NVIC_BASE + NVIC_O_SYST_CSR) & NVIC_SYST_CSR_TICKINT;
    }
    else if(interruptNum >= 16U)
    {
        status = HWREG(NVIC_BASE + (uint32_t)NVIC_O_ISER0 +
                       (NVIC_OFFSET_INC * ((interruptNum - 16U) / 32U))) &
                 (1U << ((interruptNum - 16U) & 0x1FU));
    }
    else
    {
        status = 0U;
    }

    //
    // Return peripheral interrupt status.
    //
    return(status != 0U);
}

//*****************************************************************************
//
// Interrupt_pend()
//
//*****************************************************************************
void
Interrupt_pend(uint32_t interruptNum)
{
    //
    // Check the arguments.
    //
    ASSERT(interruptNum <= NUM_INTERRUPTS);

    //
    // Pends the corresponding channel interrupt.
    //
    if(interruptNum == FAULT_NMI)
    {
        HWREG(NVIC_BASE + NVIC_O_ICSR) |= NVIC_ICSR_NMIPENDSET;
    }
    else if(interruptNum == FAULT_PENDSV)
    {
        HWREG(NVIC_BASE + NVIC_O_ICSR) |= NVIC_ICSR_PENDSVSET;
    }
    else if(interruptNum == FAULT_SYSTICK)
    {
        HWREG(NVIC_BASE + NVIC_O_ICSR) |= NVIC_ICSR_PENDSTSET;
    }
    else if(interruptNum == FAULT_SVCALL)
    {
        HWREG(NVIC_BASE + NVIC_O_SHCSRS) |= NVIC_SHCSRS_SVCALLPENDED;
    }
    else if(interruptNum == FAULT_BUS)
    {
        HWREG(NVIC_BASE + NVIC_O_SHCSRS) |= NVIC_SHCSRS_BUSFAULTPENDED;
    }
    else if(interruptNum == FAULT_MPU)
    {
        HWREG(NVIC_BASE + NVIC_O_SHCSRS) |= NVIC_SHCSRS_MEMFAULTPENDED;
    }
    else if(interruptNum == FAULT_USAGE)
    {
        HWREG(NVIC_BASE + NVIC_O_SHCSRS) |= NVIC_SHCSRS_USGFAULTPENDED;
    }
    else if(interruptNum >= 16U)
    {
        HWREG(NVIC_BASE + NVIC_O_ISPR0 +
              (NVIC_OFFSET_INC * ((interruptNum - 16U) / 32U))) =
        (uint32_t)1U << ((interruptNum - 16U) & 0x1FU);
    }
    else
    {
        //
        // Do Nothing.
        //
    }
}

//*****************************************************************************
//
// Interrupt_unpend()
//
//*****************************************************************************
void
Interrupt_unpend(uint32_t interruptNum)
{
    //
    // Check the arguments.
    //
    ASSERT(interruptNum <= NUM_INTERRUPTS);

    //
    // Unpends the corresponding channel interrupt.
    //
    if(interruptNum == FAULT_PENDSV)
    {
        HWREG(NVIC_BASE + NVIC_O_ICSR) |= NVIC_ICSR_PENDSVCLR;
    }
    else if(interruptNum == FAULT_SYSTICK)
    {
        HWREG(NVIC_BASE + NVIC_O_ICSR) |= NVIC_ICSR_PENDSTCLR;
    }
    else if(interruptNum == FAULT_SVCALL)
    {
        HWREG(NVIC_BASE + NVIC_O_SHCSRS) &= ~NVIC_SHCSRS_SVCALLPENDED;
    }
    else if(interruptNum == FAULT_BUS)
    {
        HWREG(NVIC_BASE + NVIC_O_SHCSRS) &= ~NVIC_SHCSRS_BUSFAULTPENDED;
    }
    else if(interruptNum == FAULT_MPU)
    {
        HWREG(NVIC_BASE + NVIC_O_SHCSRS) &= ~NVIC_SHCSRS_MEMFAULTPENDED;
    }
    else if(interruptNum == FAULT_USAGE)
    {
        HWREG(NVIC_BASE + NVIC_O_SHCSRS) &= ~NVIC_SHCSRS_USGFAULTPENDED;
    }
    else if(interruptNum >= 16U)
    {
        HWREG(NVIC_BASE + NVIC_O_ICPR0 +
              (NVIC_OFFSET_INC * ((interruptNum - 16U) / 32U))) =
        (uint32_t)1U << ((interruptNum - 16U) & (uint32_t)0x1FU);
    }
    else
    {
        //
        // Do Nothing.
        //
    }
}

//*****************************************************************************
//
// Interrupt_setPriority()
//
//*****************************************************************************
void
Interrupt_setPriority(uint32_t interruptNum, uint32_t priority)
{
    uint32_t offset, shift, mask;

    //
    // Check the arguments.
    //
    ASSERT((interruptNum >= 4U) && (interruptNum < NUM_INTERRUPTS));

    //
    // Set the interrupt priority.
    //
    if(interruptNum == FAULT_MPU)
    {
        HWREG(NVIC_BASE + NVIC_O_SHPR1) = (HWREG(NVIC_BASE + NVIC_O_SHPR1) &
                                           ~(uint32_t)NVIC_SHPR1_PRI_4_M) |
                                          (priority << NVIC_SHPR1_PRI_4_S);
    }
    else if(interruptNum == FAULT_BUS)
    {
        HWREG(NVIC_BASE + NVIC_O_SHPR1) = (HWREG(NVIC_BASE + NVIC_O_SHPR1) &
                                           ~(uint32_t)NVIC_SHPR1_PRI_5_M) |
                                           (priority << NVIC_SHPR1_PRI_5_S);
    }
    else if(interruptNum == FAULT_USAGE)
    {
        HWREG(NVIC_BASE + NVIC_O_SHPR1) = (HWREG(NVIC_BASE + NVIC_O_SHPR1) &
                                           ~(uint32_t)NVIC_SHPR1_PRI_6_M) |
                                          (priority << NVIC_SHPR1_PRI_6_S);
    }
    else if(interruptNum == FAULT_SVCALL)
    {
        HWREG(NVIC_BASE + NVIC_O_SHPR2) = (HWREG(NVIC_BASE + NVIC_O_SHPR2) &
                                           ~(uint32_t)NVIC_SHPR2_PRI_11_M) |
                                          (priority << NVIC_SHPR2_PRI_11_S);
    }
    else if(interruptNum == FAULT_PENDSV)
    {
        HWREG(NVIC_BASE + NVIC_O_SHPR3) = (HWREG(NVIC_BASE + NVIC_O_SHPR3) &
                                           ~(uint32_t)NVIC_SHPR3_PRI_14_M) |
                                          (priority << NVIC_SHPR3_PRI_14_S);
    }
    else if(interruptNum == FAULT_SYSTICK)
    {
        HWREG(NVIC_BASE + NVIC_O_SHPR3) = (HWREG(NVIC_BASE + NVIC_O_SHPR3) &
                                           ~(uint32_t)NVIC_SHPR3_PRI_15_M) |
                                          (priority << NVIC_SHPR3_PRI_15_S);
    }
    else if(interruptNum >= 16U)
    {
        offset = (uint32_t)NVIC_OFFSET_INC * ((interruptNum - 16U) / 4U);
        shift  = ((uint32_t)8U * (interruptNum & 0x3U)) + NVIC_IPR0_PRI_0_S;
        mask   = (uint32_t)NVIC_IPR0_PRI_0_M << (8U * (interruptNum & 0x3U));

        HWREG(NVIC_BASE + NVIC_O_IPR0 + offset) =
                (HWREG(NVIC_BASE + (uint32_t)NVIC_O_IPR0 + offset) & ~mask) |
                (priority << shift);
    }
    else
    {
        //
        // Do Nothing.
        //
    }
}

//*****************************************************************************
//
// Interrupt_getPriority()
//
//*****************************************************************************
uint32_t
Interrupt_getPriority(uint32_t interruptNum)
{
    uint32_t offset, shift, status;

    //
    // Check the arguments.
    //
    ASSERT((interruptNum >= 4U) && (interruptNum < NUM_INTERRUPTS));

    //
    // Set the interrupt priority.
    //
    if(interruptNum == FAULT_MPU)
    {
        status = (HWREG(NVIC_BASE + NVIC_O_SHPR1) & NVIC_SHPR1_PRI_4_M) >>
                 NVIC_SHPR1_PRI_4_S;
    }
    else if(interruptNum == FAULT_BUS)
    {
        status = (HWREG(NVIC_BASE + NVIC_O_SHPR1) & NVIC_SHPR1_PRI_5_M) >>
                 NVIC_SHPR1_PRI_5_S;
    }
    else if(interruptNum == FAULT_USAGE)
    {
        status = (HWREG(NVIC_BASE + NVIC_O_SHPR1) & NVIC_SHPR1_PRI_6_M) >>
                 NVIC_SHPR1_PRI_6_S;
    }
    else if(interruptNum == FAULT_SVCALL)
    {
        status = (HWREG(NVIC_BASE + NVIC_O_SHPR2) & NVIC_SHPR2_PRI_11_M) >>
                 NVIC_SHPR2_PRI_11_S;
    }
    else if(interruptNum == FAULT_PENDSV)
    {
        status = (HWREG(NVIC_BASE + NVIC_O_SHPR3) & NVIC_SHPR3_PRI_14_M) >>
                 NVIC_SHPR3_PRI_14_S;
    }
    else if(interruptNum == FAULT_SYSTICK)
    {
        status = (HWREG(NVIC_BASE + NVIC_O_SHPR3) & NVIC_SHPR3_PRI_15_M) >>
                 NVIC_SHPR3_PRI_15_S;
    }
    else if(interruptNum >= 16U)
    {
        offset = (uint32_t)NVIC_OFFSET_INC * ((interruptNum - 16U) / 4U);
        shift = ((uint32_t)8U * (interruptNum & 0x3U)) + 5U;

        status = (HWREG(NVIC_BASE + (uint32_t)NVIC_O_IPR0 + offset) >> shift) &
                 0xFFU;
    }
    else
    {
        status = 0U;
    }
    return(status);
}

//*****************************************************************************
//
// Interrupt_initRAMVectorTable()
//
//*****************************************************************************
void
Interrupt_initRAMVectorTable(void (*srcVectorTable[])(void),
                             void (*dstVectorTable[])(void))
{
    uint32_t index;

    //
    // Check whether dstVectorTable lies in RAM and is correctly aligned.
    //
    ASSERT((uint32_t)dstVectorTable >= 0x20000000U);
    ASSERT(((uint32_t)dstVectorTable & 0x000003FFU) == 0U);

    if(HWREG(NVIC_BASE + NVIC_O_VTOR) != (uint32_t)dstVectorTable)
    {
        //
        // Point the NVIC at the RAM vector table.
        //
        HWREG(NVIC_BASE + NVIC_O_VTOR) = (uint32_t)dstVectorTable;
    }

    //
    // Copy the ISRs from temp vector table to RAM vector table.
    //
    for(index = 0U; index < NUM_INTERRUPTS; index++)
    {
        dstVectorTable[index] = srcVectorTable[index];
    }
}
//*****************************************************************************
//
// Interrupt_registerHandler()
//
//*****************************************************************************
void
Interrupt_registerHandler(uint32_t interruptNum, void (*intHandler)(void))
{
    uint32_t index, value;

    //
    // Check the arguments.
    //
    ASSERT(interruptNum < NUM_INTERRUPTS);

    //
    // Make sure that the RAM vector table is correctly aligned.
    // Check vector table alignment in device datasheet.
    //
    ASSERT(((uint32_t)vectorTableRAM & 0x000003FFU) == 0U);

    //
    // See if the RAM vector table has been initialized.
    //
    if(HWREG(NVIC_BASE + NVIC_O_VTOR) != (uint32_t)vectorTableRAM)
    {
        //
        // Copy the vector table from the beginning of FLASH to the RAM vector
        // table.
        //
        value = HWREG(NVIC_BASE + NVIC_O_VTOR);
        for(index = 0U; index < NUM_INTERRUPTS; index++)
        {
            vectorTableRAM[index] = (void (*)(void))HWREG((index * 4U) + value);
        }

        //
        // Point the NVIC at the RAM vector table.
        //
        HWREG(NVIC_BASE + NVIC_O_VTOR) = (uint32_t)vectorTableRAM;
    }

    //
    // Save the interrupt handler.
    //
    vectorTableRAM[interruptNum] = intHandler;
}
