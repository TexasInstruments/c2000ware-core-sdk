//###########################################################################
//
// FILE:   cmpss.c
//
// TITLE:  C28x CMPSS driver.
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

#include "cmpss.h"

//*****************************************************************************
//
// CMPSS_configFilterHigh
//
//*****************************************************************************
void
CMPSS_configFilterHigh(uint32_t base, uint32_t samplePrescale,
                       uint16_t sampleWindow, uint16_t threshold)
{
    uint16_t regValue;

    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(samplePrescale <= 16777215UL);
    ASSERT((sampleWindow >= 1U) && (sampleWindow <= 64U));
    ASSERT((threshold - 1U) >= ((sampleWindow - 1U) / 2U));

    //
    // Shift the sample window and threshold values into the correct positions
    // and write them to the appropriate register.
    //
    regValue = ((sampleWindow - 1U) << CMPSS_CTRIPHFILCTL_SAMPWIN_S) |
               ((threshold - 1U) << CMPSS_CTRIPHFILCTL_THRESH_S);

    EALLOW;

    HWREGH(base + CMPSS_O_CTRIPHFILCTL) =
        (HWREGH(base + CMPSS_O_CTRIPHFILCTL) &
         ~(CMPSS_CTRIPHFILCTL_SAMPWIN_M | CMPSS_CTRIPHFILCTL_THRESH_M)) |
        regValue;

    //
    // Set the filter sample clock prescale for the high comparator.
    //
    HWREGH(base + CMPSS_O_CTRIPHFILCLKCTL)  = (uint16_t)samplePrescale;
    HWREGH(base + CMPSS_O_CTRIPHFILCLKCTL2) = (uint16_t)(samplePrescale >> 16U);

    EDIS;
}

//*****************************************************************************
//
// CMPSS_configFilterLow
//
//*****************************************************************************
void
CMPSS_configFilterLow(uint32_t base, uint32_t samplePrescale,
                      uint16_t sampleWindow, uint16_t threshold)
{
    uint16_t regValue;

    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(samplePrescale <= 16777215UL);
    ASSERT((sampleWindow >= 1U) && (sampleWindow <= 64U));
    ASSERT((threshold - 1U) >= ((sampleWindow - 1U) / 2U));

    //
    // Shift the sample window and threshold values into the correct positions
    // and write them to the appropriate register.
    //
    regValue = ((sampleWindow - 1U) << CMPSS_CTRIPLFILCTL_SAMPWIN_S) |
               ((threshold - 1U) << CMPSS_CTRIPLFILCTL_THRESH_S);

    EALLOW;

    HWREGH(base + CMPSS_O_CTRIPLFILCTL) =
        (HWREGH(base + CMPSS_O_CTRIPLFILCTL) &
         ~(CMPSS_CTRIPLFILCTL_SAMPWIN_M | CMPSS_CTRIPLFILCTL_THRESH_M)) |
        regValue;

    //
    // Set the filter sample clock prescale for the low comparator.
    //
    HWREGH(base + CMPSS_O_CTRIPLFILCLKCTL) = (uint16_t)samplePrescale;
    HWREGH(base + CMPSS_O_CTRIPLFILCLKCTL2) = (uint16_t)(samplePrescale >> 16U);

    EDIS;
}

//*****************************************************************************
//
// CMPSS_configLatchOnPWMSYNC
//
//*****************************************************************************
void
CMPSS_configLatchOnPWMSYNC(uint32_t base, bool highEnable, bool lowEnable)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));

    //
    // If the highEnable is true, set the bit that will enable PWMSYNC to reset
    // the high comparator digital filter latch. If not, clear the bit.
    //
    EALLOW;

    if(highEnable)
    {
        HWREGH(base + CMPSS_O_COMPSTSCLR) |= CMPSS_COMPSTSCLR_HSYNCCLREN;
    }
    else
    {
        HWREGH(base + CMPSS_O_COMPSTSCLR) &= ~CMPSS_COMPSTSCLR_HSYNCCLREN;
    }

    //
    // If the lowEnable is true, set the bit that will enable PWMSYNC to reset
    // the low comparator digital filter latch. If not, clear the bit.
    //
    if(lowEnable)
    {
        HWREGH(base + CMPSS_O_COMPSTSCLR) |= CMPSS_COMPSTSCLR_LSYNCCLREN;
    }
    else
    {
        HWREGH(base + CMPSS_O_COMPSTSCLR) &= ~CMPSS_COMPSTSCLR_LSYNCCLREN;
    }

    EDIS;
}

//*****************************************************************************
//
// CMPSS_configRamp
//
//*****************************************************************************
void
CMPSS_configRamp(uint32_t base, uint16_t maxRampVal, uint16_t decrementVal,
                 uint16_t delayVal, uint16_t pwmSyncSrc, bool useRampValShdw)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(delayVal <= CMPSS_RAMPHDLYS_DELAY_M);
    ASSERT((pwmSyncSrc >= 1U) && (pwmSyncSrc <= 18U));

    EALLOW;

    //
    // Write the ramp generator source to the register
    //
    HWREGH(base + CMPSS_O_COMPDACHCTL) =
        (HWREGH(base + CMPSS_O_COMPDACHCTL) &
         ~CMPSS_COMPDACHCTL_RAMPSOURCE_M) |
        ((uint16_t)(pwmSyncSrc - 1U) << CMPSS_COMPDACHCTL_RAMPSOURCE_S);

    //
    // Set or clear the bit that determines from where the max ramp value
    // should be loaded.
    //
    if(useRampValShdw)
    {
        HWREGH(base + CMPSS_O_COMPDACHCTL) |= CMPSS_COMPDACHCTL_RAMPLOADSEL;
    }
    else
    {
        HWREGH(base + CMPSS_O_COMPDACHCTL) &= ~CMPSS_COMPDACHCTL_RAMPLOADSEL;
    }

    EDIS;

    //
    // Write the maximum ramp value to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPHREFS) = maxRampVal;

    //
    // Write the ramp decrement value to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPHSTEPVALS) = decrementVal;

    //
    // Write the ramp delay value to the shadow register.
    //
    HWREGH(base + CMPSS_O_RAMPHDLYS) = delayVal;
}

//*****************************************************************************
//
// CMPSS_configRampHigh
//
//*****************************************************************************
void
CMPSS_configRampHigh(uint32_t base, CMPSS_RampDirection rampDir,
                     uint16_t rampRef, uint16_t stepVal, uint16_t delayVal,
                     uint16_t pwmSyncSrc, bool useRampValShdw)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(delayVal <= CMPSS_RAMPHDLYS_DELAY_M);
    ASSERT((pwmSyncSrc >= 1U) && (pwmSyncSrc <= 18U));
    //
    // Configure ramp direction
    //
    CMPSS_setRampDirectionHigh(base, rampDir);

    //
    // Write the ramp generator sync source to the register
    //
    CMPSS_configureSyncSourceHigh(base, pwmSyncSrc);

    EALLOW;

    //
    // Set or clear the bit that determines from where the ramp reference value
    // should be loaded.
    //
    if(useRampValShdw)
    {
        HWREGH(base + CMPSS_O_COMPDACHCTL) |= CMPSS_COMPDACHCTL_RAMPLOADSEL;
    }
    else
    {
        HWREGH(base + CMPSS_O_COMPDACHCTL) &= ~CMPSS_COMPDACHCTL_RAMPLOADSEL;
    }

    EDIS;

    //
    // Write the ramp reference value to the shadow register.
    //
    CMPSS_setRampReferenceHigh(base, rampRef);

    //
    // Write the ramp step value to the shadow register.
    //
    CMPSS_setRampStepHigh(base, stepVal);

    //
    // Write the ramp delay value to the shadow register.
    //
    CMPSS_setRampDelayHigh(base, delayVal);
}

//*****************************************************************************
//
// CMPSS_configRampLow
//
//*****************************************************************************
void
CMPSS_configRampLow(uint32_t base, CMPSS_RampDirection rampDir,
                    uint16_t rampRef, uint16_t stepVal, uint16_t delayVal,
                    uint16_t pwmSyncSrc, bool useRampValShdw)
{
    //
    // Check the arguments.
    //
    ASSERT(CMPSS_isBaseValid(base));
    ASSERT(delayVal <= CMPSS_RAMPLDLYS_DELAY_M);
    ASSERT((pwmSyncSrc >= 1U) && (pwmSyncSrc <= 18U));

    //
    // Configure ramp direction
    //
    CMPSS_setRampDirectionLow(base, rampDir);

    //
    // Write the ramp generator sync source to the register
    //
    CMPSS_configureSyncSourceLow(base, pwmSyncSrc);

    EALLOW;

    //
    // Set or clear the bit that determines from where the ramp reference value
    // should be loaded.
    //
    if(useRampValShdw)
    {
        HWREGH(base + CMPSS_O_COMPDACHCTL) |= CMPSS_COMPDACHCTL_RAMPLOADSEL;
    }
    else
    {
        HWREGH(base + CMPSS_O_COMPDACHCTL) &= ~CMPSS_COMPDACHCTL_RAMPLOADSEL;
    }

    EDIS;

    //
    // Write the ramp reference value to the shadow register.
    //
    CMPSS_setRampReferenceLow(base, rampRef);

    //
    // Write the ramp step value to the shadow register.
    //
    CMPSS_setRampStepLow(base, stepVal);

    //
    // Write the ramp delay value to the shadow register.
    //
    CMPSS_setRampDelayLow(base, delayVal);
}
