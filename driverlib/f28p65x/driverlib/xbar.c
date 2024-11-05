//###########################################################################
//
// FILE:   xbar.c
//
// TITLE:  C28x X-BAR driver.
//
//###########################################################################
// 
// C2000Ware v5.04.00.00
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

#include "xbar.h"

//*****************************************************************************
//
// XBAR_setOutputMuxConfig
//
//*****************************************************************************
void
XBAR_setOutputMuxConfig(uint32_t base, XBAR_OutputNum output,
                        XBAR_OutputMuxConfig muxConfig)
{
    //
    // Check the arguments.
    //
    ASSERT(XBAR_isBaseValid(base));
    if(base == CLBOUTPUTXBAR_BASE)
    {
        ASSERT((uint32_t)muxConfig < 0x4000U);
    }

    uint32_t shift;
    uint16_t offset;

    //
    // Depending on the configuration of MUX selected, we'll need different
    // values to index into the config registers.
    //
    if(base == OUTPUTXBAR_BASE)
    {
        if(((uint32_t)muxConfig & 0x6000U) == 0x6000U)
        {
            offset = ((uint16_t)output << 1U) + 6U;
        }
        else if (((uint32_t)muxConfig & 0x4000U) != 0U)
        {
            offset = ((uint16_t)output << 1U) + 4U;
        }
        else if (((uint32_t)muxConfig & 0x2000U) != 0U)
        {
            offset = ((uint16_t)output << 1U) + 2U;
        }
        else
        {
            offset = (uint16_t)output << 1U;
        }
    }
    else
    {
        if (((uint32_t)muxConfig & 0x2000U) != 0U)
        {
            offset = (uint16_t)output + 2U;
        }
        else
        {
            offset = (uint16_t)output;
        }
    }


    //
    // Extract the shift from the input value.
    //
    shift = ((uint32_t)muxConfig >> 8U) & 0x1FU;

    //
    // Write the requested muxing value for this XBAR output.
    //
    EALLOW;

    if(base == OUTPUTXBAR_BASE)
    {
        HWREG(base + XBAR_O_OUTPUT1MUX0TO15CFG + (uint32_t)offset) =
            (HWREG(base + XBAR_O_OUTPUT1MUX0TO15CFG + (uint32_t)offset) &
             ~(0x3UL << shift)) |
            (((uint32_t)muxConfig & 0x3UL) << shift);
    }
    else
    {
        HWREG(base + CLBXBAR_O_OUTPUT1MUX0TO15CFG + offset) =
            (HWREG(base + CLBXBAR_O_OUTPUT1MUX0TO15CFG + offset) &
             ~(0x3UL << shift)) |
            (((uint32_t)muxConfig & 0x3UL) << shift);
    }

    EDIS;
}

//*****************************************************************************
//
// XBAR_setEPWMMuxConfig
//
//*****************************************************************************
void
XBAR_setEPWMMuxConfig(XBAR_TripNum trip, XBAR_EPWMMuxConfig muxConfig)
{
    uint32_t shift;
    uint16_t offset;

    uint32_t base;
    uint16_t tripSel = (uint16_t)trip;
    if (tripSel <= (uint16_t)XBAR_TRIP8)
    {
        base = XBARA_EPWM_CFG_REG_BASE;
    }
    else
    {
        base = XBARB_EPWM_CFG_REG_BASE;
        tripSel = tripSel - 32U;
    }

    //
    // Depending on the configuration of MUX selected, we'll need different
    // values to index into the config registers.
    //
    if(((uint32_t)muxConfig & 0x6000U) == 0x6000U)
    {
        offset = (tripSel << 1U) + 6U;
    }
    else if (((uint32_t)muxConfig & 0x4000U) != 0U)
    {
        offset = (tripSel << 1U) + 4U;
    }
    else if (((uint32_t)muxConfig & 0x2000U) != 0U)
    {
        offset = (tripSel << 1U) + 2U;
    }
    else
    {
        offset = tripSel << 1U;
    }


    //
    // Extract the shift from the input value.
    //
    shift = ((uint32_t)muxConfig >> 8U) & 0x1FU;

    //
    // Write the requested muxing value for this XBAR trip.
    //
    EALLOW;

    HWREG(base + (uint32_t)offset) =
        (HWREG(base + (uint32_t)offset) & ~(0x3UL << shift)) |
        (((uint32_t)muxConfig & 0x3UL) << shift);

    EDIS;
}

//*****************************************************************************
//
// XBAR_setCLBMuxConfig
//
//*****************************************************************************
void
XBAR_setCLBMuxConfig(XBAR_AuxSigNum auxSignal, XBAR_CLBMuxConfig muxConfig)
{
    uint32_t shift;
    uint16_t offset;

    //
    // If the configuration is for MUX16-31, we'll need an odd value to index
    // into the config registers.
    //
    if(((uint32_t)muxConfig & 0x2000U) != 0U)
    {
        offset = ((uint16_t)auxSignal << 1U) + 2U;
    }
    else
    {
        offset = (uint16_t)auxSignal << 1U;
    }

    //
    // Extract the shift from the input value.
    //
    shift = ((uint32_t)muxConfig >> 8U) & 0x1FU;

    //
    // Write the requested muxing value for this XBAR auxSignal.
    //
    EALLOW;


    HWREG(XBAR_CLB_CFG_REG_BASE + (uint32_t)offset) =
        (HWREG(XBAR_CLB_CFG_REG_BASE + (uint32_t)offset) & ~(0x3UL << shift)) |
        (((uint32_t)muxConfig & 0x3UL) << shift);

    EDIS;
}

//*****************************************************************************
//
// XBAR_getInputFlagStatus
//
//*****************************************************************************
bool
XBAR_getInputFlagStatus(XBAR_InputFlag inputFlag)
{
    uint32_t offset;
    uint32_t inputMask;

    //
    // Determine flag register offset.
    //
    switch((uint16_t)inputFlag & XBAR_INPUT_FLG_REG_M)
    {
        case XBAR_INPUT_FLG_REG_1:
            offset = XBAR_O_FLG1;
            break;

        case XBAR_INPUT_FLG_REG_2:
            offset = XBAR_O_FLG2;
            break;

        case XBAR_INPUT_FLG_REG_3:
            offset = XBAR_O_FLG3;
            break;

        case XBAR_INPUT_FLG_REG_4:
            offset = XBAR_O_FLG4;
            break;

        case XBAR_INPUT_FLG_REG_5:
            offset = XBAR_O_FLG5;
            break;

        case XBAR_INPUT_FLG_REG_6:
            offset = XBAR_O_FLG6;
            break;

        case XBAR_INPUT_FLG_REG_7:
            offset = XBAR_O_FLG7;
            break;

        case XBAR_INPUT_FLG_REG_8:
            offset = XBAR_O_FLG8;
            break;

        case XBAR_INPUT_FLG_REG_9:
            offset = XBAR_O_FLG9;
            break;

        case XBAR_INPUT_FLG_REG_10:
            offset = XBAR_O_FLG10;
            break;

        case XBAR_INPUT_FLG_REG_11:
            offset = XBAR_O_FLG11;
            break;

        case XBAR_INPUT_FLG_REG_12:
            offset = XBAR_O_FLG12;
            break;

        case XBAR_INPUT_FLG_REG_13:
            offset = XBAR_O_FLG13;
            break;

        case XBAR_INPUT_FLG_REG_14:
            offset = XBAR_O_FLG14;
            break;

        case XBAR_INPUT_FLG_REG_15:
            offset = XBAR_O_FLG15;
            break;

        case XBAR_INPUT_FLG_REG_16:
            offset = XBAR_O_FLG16;
            break;
        default:
            //
            // This should never happen if a valid inputFlag value is used.
            //
            offset = 0U;
            break;
    }

    //
    // Get the status of the X-BAR input latch.
    //
    inputMask = (uint32_t)1U << ((uint32_t)inputFlag & XBAR_INPUT_FLG_INPUT_M);

    return((HWREG(XBAR_BASE + offset) & inputMask) != 0U);
}

//*****************************************************************************
//
// XBAR_clearInputFlag
//
//*****************************************************************************
void
XBAR_clearInputFlag(XBAR_InputFlag inputFlag)
{
    uint32_t offset;
    uint32_t inputMask;

    //
    // Determine flag clear register offset.
    //
    switch((uint16_t)inputFlag & XBAR_INPUT_FLG_REG_M)
    {
        case XBAR_INPUT_FLG_REG_1:
            offset = XBAR_O_CLR1;
            break;

        case XBAR_INPUT_FLG_REG_2:
            offset = XBAR_O_CLR2;
            break;

        case XBAR_INPUT_FLG_REG_3:
            offset = XBAR_O_CLR3;
            break;

        case XBAR_INPUT_FLG_REG_4:
            offset = XBAR_O_CLR4;
            break;

        case XBAR_INPUT_FLG_REG_5:
            offset = XBAR_O_CLR5;
            break;

       case XBAR_INPUT_FLG_REG_6:
            offset = XBAR_O_CLR6;
            break;

        case XBAR_INPUT_FLG_REG_7:
            offset = XBAR_O_CLR7;
            break;

        case XBAR_INPUT_FLG_REG_8:
            offset = XBAR_O_CLR8;
            break;

        case XBAR_INPUT_FLG_REG_9:
            offset = XBAR_O_CLR9;
            break;

        case XBAR_INPUT_FLG_REG_10:
            offset = XBAR_O_CLR10;
            break;

        case XBAR_INPUT_FLG_REG_11:
            offset = XBAR_O_CLR11;
            break;

        case XBAR_INPUT_FLG_REG_12:
            offset = XBAR_O_CLR12;
            break;

        case XBAR_INPUT_FLG_REG_13:
            offset = XBAR_O_CLR13;
            break;

        case XBAR_INPUT_FLG_REG_14:
            offset = XBAR_O_CLR14;
            break;

        case XBAR_INPUT_FLG_REG_15:
            offset = XBAR_O_CLR15;
            break;

        case XBAR_INPUT_FLG_REG_16:
            offset = XBAR_O_CLR16;
            break;
        default:
            //
            // This should never happen if a valid inputFlag value is used.
            //
            offset = 0U;
            break;
    }

    //
    // Set the bit that clears the X-BAR input latch.
    //
    inputMask = 1UL << ((uint32_t)inputFlag & XBAR_INPUT_FLG_INPUT_M);
    HWREG(XBAR_BASE + offset) = inputMask;
}
