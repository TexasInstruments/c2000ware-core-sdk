//###########################################################################
//
// FILE:   sysctl.c
//
// TITLE:  CM system control driver.
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

#include "sysctl.h"

//*****************************************************************************
//
// SysCtl_delay()
//
//*****************************************************************************

//
//SYSCTL_DELAY define for delay of fixed cycles.
//
SYSCTL_DELAY

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
// SysCtl_resetPeripheral()
//
//*****************************************************************************

void
SysCtl_resetPeripheral(SysCtl_PeripheralSOFTPRES peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;
    uint32_t clearvalue;

    //
    // Decode the peripheral variable.
    //
    regIndex = (uint16_t)4U * ((uint16_t)peripheral &
                               (uint16_t)SYSCTL_PERIPH_REG_M);
    bitIndex = ((uint16_t)peripheral & SYSCTL_PERIPH_BIT_M) >>
                SYSCTL_PERIPH_BIT_S;

    //
    //Write will succeed only if a matching key value is written
    //to the KEY field
    //Sets the appropriate reset bit and then clears it.
    //
    HWREG(CMSYSCTL_BASE + SYSCTL_O_CMSOFTPRESET0 + regIndex) |=
                    (((uint32_t)1U << bitIndex) |
                    (((uint32_t)SYSCTL_CMSYSCTL_KEY << 16U ) &
                     SYSCTL_CMSOFTPRESET0_KEY_M));

    clearvalue = HWREG(CMSYSCTL_BASE + SYSCTL_O_CMSOFTPRESET0 + regIndex);
    clearvalue &= ~((uint32_t)1U << bitIndex);
    HWREG(CMSYSCTL_BASE + SYSCTL_O_CMSOFTPRESET0 + regIndex) =
                   (((uint32_t)SYSCTL_CMSYSCTL_KEY << 16U) &
                    SYSCTL_CMPCLKCR0_KEY_M) | clearvalue;

}

//*****************************************************************************
//
// SysCtl_enablePeripheral()
//
//*****************************************************************************

void
SysCtl_enablePeripheral(SysCtl_PeripheralPCLOCKCR peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Decode the peripheral variable.
    //
    regIndex = (uint16_t)4U * ((uint16_t)peripheral &
                              (uint16_t)SYSCTL_PERIPH_REG_M);
    bitIndex = ((uint16_t)peripheral & SYSCTL_PERIPH_BIT_M) >>
                SYSCTL_PERIPH_BIT_S;

    //
    // Write will succeed only if a matching key value is written to
    // the KEY field
    // Turn on the module clock.
    //
    HWREG(CMSYSCTL_BASE + SYSCTL_O_CMPCLKCR0 + regIndex) |=
                          (((uint32_t)1U << bitIndex) |
                          (((uint32_t)SYSCTL_CMSYSCTL_KEY << 16U ) &
                           SYSCTL_CMPCLKCR0_KEY_M));


}


//*****************************************************************************
//
// SysCtl_disablePeripheral()
//
//*****************************************************************************

void
SysCtl_disablePeripheral(SysCtl_PeripheralPCLOCKCR peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;
    uint32_t clearvalue;

    //
    // Decode the peripheral variable.
    //
    regIndex = (uint16_t)4U * ((uint16_t)peripheral &
               (uint16_t)SYSCTL_PERIPH_REG_M);
    bitIndex = ((uint16_t)peripheral & SYSCTL_PERIPH_BIT_M) >>
                SYSCTL_PERIPH_BIT_S;

    //
    //Write will succeed only if a matching key value is written
    // to the KEY field
    // Turn off the module clock.
    //
    clearvalue = HWREG(CMSYSCTL_BASE + SYSCTL_O_CMPCLKCR0 + regIndex);
    clearvalue &= ~((uint32_t)1U << bitIndex);
    HWREG(CMSYSCTL_BASE + SYSCTL_O_CMPCLKCR0 + regIndex) =
                   (((uint32_t)SYSCTL_CMSYSCTL_KEY << 16U) &
                   SYSCTL_CMPCLKCR0_KEY_M) | clearvalue;

}


//*****************************************************************************
//
// SysCtl_requestPeripheralClockStop()
//
//*****************************************************************************

void
SysCtl_requestPeripheralClockStop(SysCtl_PeripheralCMCLKSTOPREQ peripheral,
                                  uint16_t enable)
{
    uint16_t regIndex;
    uint16_t bitIndex;
    uint32_t clearvalue;

    //
    // Decode the peripheral variable.
    //
    regIndex = (uint16_t)4U * ((uint16_t)peripheral &
               (uint16_t)SYSCTL_PERIPH_REG_M);
    bitIndex = ((uint16_t)peripheral & SYSCTL_PERIPH_BIT_M) >>
                SYSCTL_PERIPH_BIT_S;

    //
    //Write will succeed only if a matching key value is written
    //to the KEY field
    // Request to stop the clock
    //

    if(enable == 1U) //enable the peripheral clock Stop
    {
        HWREG(CMSYSCTL_BASE + SYSCTL_O_CMCLKSTOPREQ0 + regIndex) |=
                    (((uint32_t)1U << bitIndex) |
                    (((uint32_t)SYSCTL_CMSYSCTL_KEY << 16U) &
                    SYSCTL_CMCLKSTOPREQ0_KEY_M));
    }
    else //disable the peripheral clock Stop
    {
        clearvalue = HWREG(CMSYSCTL_BASE + SYSCTL_O_CMCLKSTOPREQ0 + regIndex);
        clearvalue &= ~((uint32_t)1U << bitIndex);
        HWREG(CMSYSCTL_BASE + SYSCTL_O_CMCLKSTOPREQ0 + regIndex) =
                       (((uint32_t)SYSCTL_CMSYSCTL_KEY << 16U) &
                       SYSCTL_CMCLKSTOPREQ0_KEY_M) | clearvalue;

    }
}

//*****************************************************************************
//
// SysCtl_isPeripheralClockStopAcked()
//
//*****************************************************************************

bool
SysCtl_isPeripheralClockStopAcked(SysCtl_PeripheralCMCLKSTOPACK peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Decode the peripheral variable.
    //
    regIndex = (uint16_t)4U * ((uint16_t)peripheral &
               (uint16_t)SYSCTL_PERIPH_REG_M);
    bitIndex = ((uint16_t)peripheral & SYSCTL_PERIPH_BIT_M) >>
               SYSCTL_PERIPH_BIT_S;

    //
    // Read the register and return true if the clk stop Req is acked or not.
    //
    return((HWREGH(CMSYSCTL_BASE + SYSCTL_O_CMCLKSTOPACK1 + regIndex) &
          ((uint32_t)1U << bitIndex)) != 0U);
}

//*****************************************************************************
//
// SysCtl_getPeripheralClockStop()
//
//*****************************************************************************

uint16_t
SysCtl_getPeripheralClockStop(SysCtl_PeripheralCMCLKSTOPREQ peripheral)
{
    uint16_t regIndex;

    //
    // Decode the peripheral variable.
    //
    regIndex = (uint16_t)4U * ((uint16_t)peripheral &
               (uint16_t)SYSCTL_PERIPH_REG_M);

    //
    // Read the register and return the value of clk stop Req
    //
     return(HWREGH(CMSYSCTL_BASE + SYSCTL_O_CMCLKSTOPREQ0 + regIndex));
}

