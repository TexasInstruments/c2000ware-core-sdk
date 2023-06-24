//#############################################################################
//
// FILE:   dcsm.c
//
// TITLE:  C28x Driver for the DCSM security module.
//
//#############################################################################
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

#include "dcsm.h"

//*****************************************************************************
//
// DCSM_unlockZone1CSM
//
//*****************************************************************************
void
DCSM_unlockZone1CSM(const DCSM_CSMPasswordKey * const psCMDKey)
{
    uint32_t linkPointer;
    uint32_t zsbBase = (DCSMBANK0_Z1OTP_BASE + 0x20U); //base address of the ZSB
    int32_t bitPos = 28;
    int32_t zeroFound = 0;

    linkPointer = HWREG(DCSMBANK0_Z1_BASE + DCSM_O_B0_Z1_LINKPOINTER);

    //
    // Bits 31 and 30 as most-significant 0 are invalid LinkPointer options
    //
    linkPointer = linkPointer << 3;

    while((zeroFound == 0) && (bitPos > -1))
    {
        if( (linkPointer & 0x80000000U) == 0U)
        {
            zeroFound = 1;
            zsbBase = (DCSMBANK0_Z1OTP_BASE +
                      (((uint32_t)bitPos + 3U) * 0x10U));
        }
        else
        {
            bitPos--;
            linkPointer = linkPointer << 1;
        }
    }

    //
    // Perform dummy reads on the 128-bit password
    // Using linkPointer because it is no longer needed
    //
    linkPointer = HWREG(zsbBase + DCSM_O_Z1_CSMPSWD0);
    linkPointer = HWREG(zsbBase + DCSM_O_Z1_CSMPSWD1);
    linkPointer = HWREG(zsbBase + DCSM_O_Z1_CSMPSWD2);
    linkPointer = HWREG(zsbBase + DCSM_O_Z1_CSMPSWD3);

    HWREG(DCSMBANK0_Z1_BASE + DCSM_O_Z1_CSMKEY0) = psCMDKey->csmKey0;
    HWREG(DCSMBANK0_Z1_BASE + DCSM_O_Z1_CSMKEY1) = psCMDKey->csmKey1;
    HWREG(DCSMBANK0_Z1_BASE + DCSM_O_Z1_CSMKEY2) = psCMDKey->csmKey2;
    HWREG(DCSMBANK0_Z1_BASE + DCSM_O_Z1_CSMKEY3) = psCMDKey->csmKey3;
}

//*****************************************************************************
//
// DCSM_unlockZone2CSM
//
//*****************************************************************************
void
DCSM_unlockZone2CSM(const DCSM_CSMPasswordKey * const psCMDKey)
{
    uint32_t linkPointer;
    uint32_t zsbBase = (DCSMBANK0_Z2OTP_BASE + 0x20U); //base address of the ZSB
    int32_t bitPos = 28;
    int32_t zeroFound = 0;

    linkPointer = HWREG(DCSMBANK0_Z2_BASE + DCSM_O_B0_Z2_LINKPOINTER);

    //
    // Bits 31 and 30 as most-sigificant 0 are invalid LinkPointer options
    //
    linkPointer = linkPointer << 3;
    while((zeroFound == 0) && (bitPos > -1))
    {
        if( (linkPointer & 0x80000000U) == 0U)
        {
            zeroFound = 1;
            zsbBase = (DCSMBANK0_Z2OTP_BASE +
                      (((uint32_t)bitPos + 3U) * 0x10U));
        }
        else
        {
            bitPos--;
            linkPointer = linkPointer << 1;
        }
    }

    //
    // Perform dummy reads on the 128-bit password
    // Using linkPointer because it is no longer needed
    //
    linkPointer = HWREG(zsbBase + DCSM_O_Z2_CSMPSWD0);
    linkPointer = HWREG(zsbBase + DCSM_O_Z2_CSMPSWD1);
    linkPointer = HWREG(zsbBase + DCSM_O_Z2_CSMPSWD2);
    linkPointer = HWREG(zsbBase + DCSM_O_Z2_CSMPSWD3);

    HWREG(DCSMBANK0_Z2_BASE + DCSM_O_Z2_CSMKEY0) = psCMDKey->csmKey0;
    HWREG(DCSMBANK0_Z2_BASE + DCSM_O_Z2_CSMKEY1) = psCMDKey->csmKey1;
    HWREG(DCSMBANK0_Z2_BASE + DCSM_O_Z2_CSMKEY2) = psCMDKey->csmKey2;
    HWREG(DCSMBANK0_Z2_BASE + DCSM_O_Z2_CSMKEY3) = psCMDKey->csmKey3;
}

//*****************************************************************************
//
// DCSM_getZone1FlashEXEStatus
//
//*****************************************************************************
DCSM_EXEOnlyStatus
DCSM_getZone1FlashEXEStatus(DCSM_Sector sector)
{
    uint16_t regValue, statusBitShift;
    DCSM_EXEOnlyStatus status;

    //
    // Check if sector belongs to this zone
    //
    if(DCSM_getFlashSectorZone(sector) != DCSM_MEMORY_ZONE1)
    {
        status = DCSM_INCORRECT_ZONE;
    }
    else
    {
        //
        // Get the EXE status register for bank 0
        //
        regValue = HWREGH(DCSMBANK0_Z1_BASE + DCSM_O_B0_Z1_EXEONLYSECTR);
        statusBitShift = (uint16_t)sector;

        //
        // Get the EXE status of the Flash Sector
        //
        status = (DCSM_EXEOnlyStatus)((uint16_t)((regValue >> statusBitShift) &
                                       0x01U));
    }
    return(status);
}

//*****************************************************************************
//
// DCSM_getZone1RAMEXEStatus
//
//*****************************************************************************
DCSM_EXEOnlyStatus
DCSM_getZone1RAMEXEStatus(DCSM_RAMModule module)
{
    DCSM_EXEOnlyStatus status;

    //
    // Check if module belongs to this zone
    //
    if(DCSM_getRAMZone(module) != DCSM_MEMORY_ZONE1)
    {
        status = DCSM_INCORRECT_ZONE;
    }
    else
    {
        //
        // Get the EXE status of the RAM Module
        //
        status = (DCSM_EXEOnlyStatus)(uint16_t)((HWREGH(DCSMBANK0_Z1_BASE +
               DCSM_O_Z1_EXEONLYRAMR) >> (uint16_t)module) & 0x01U);
    }
    return(status);
}

//*****************************************************************************
//
// DCSM_getZone2FlashEXEStatus
//
//*****************************************************************************
DCSM_EXEOnlyStatus
DCSM_getZone2FlashEXEStatus(DCSM_Sector sector)
{
    uint16_t regValue, statusBitShift;
    DCSM_EXEOnlyStatus status;

    //
    // Check if sector belongs to this zone
    //
    if(DCSM_getFlashSectorZone(sector) != DCSM_MEMORY_ZONE2)
    {
        status = DCSM_INCORRECT_ZONE;
    }

    //
    // Get the EXE status register for the specific bank
    //
    else
    {
        regValue = HWREGH(DCSMBANK0_Z2_BASE + DCSM_O_B0_Z2_EXEONLYSECTR);
        statusBitShift = (uint16_t)sector;

        //
        // Get the EXE status of the Flash Sector
        //
        status = (DCSM_EXEOnlyStatus)(uint16_t)((regValue >> statusBitShift) &
                                      0x01U);
    }
    return(status);
}

//*****************************************************************************
//
// DCSM_getZone2RAMEXEStatus
//
//*****************************************************************************
DCSM_EXEOnlyStatus
DCSM_getZone2RAMEXEStatus(DCSM_RAMModule module)
{
    DCSM_EXEOnlyStatus status;

    //
    // Check if module belongs to this zone
    //
    if(DCSM_getRAMZone(module) != DCSM_MEMORY_ZONE2)
    {
        status = DCSM_INCORRECT_ZONE;
    }
    else
    {
        //
        // Get the EXE status of the RAM Module
        //
        status = (DCSM_EXEOnlyStatus)(uint16_t)((HWREGH(DCSMBANK0_Z2_BASE +
               DCSM_O_Z2_EXEONLYRAMR) >> (uint16_t)module) & 0x01U);
    }
    return(status);
}

//*****************************************************************************
//
// DCSM_claimZoneSemaphore
//
//*****************************************************************************
bool
DCSM_claimZoneSemaphore(DCSM_SemaphoreZone zone)
{
    //
    // FLSEM register address.
    //
    uint32_t regAddress = DCSMCOMMON_BASE + DCSM_O_FLSEM;

    EALLOW;

    //
    // Write 0xA5 to the key and write the zone that is attempting to claim the
    // Flash Pump Semaphore to the semaphore bits.
    //
    HWREGH(regAddress) = ((uint16_t)FLSEM_KEY << DCSM_FLSEM_KEY_S) |
                         (uint16_t)zone;
    EDIS;

    //
    // If the calling function was unable to claim the zone semaphore, then
    // return false
    //
    return(((HWREGH(regAddress) & DCSM_FLSEM_SEM_M) == (uint16_t)zone) ?
                true : false);
}

//*****************************************************************************
//
// DCSM_releaseZoneSemaphore
//
//*****************************************************************************
bool
DCSM_releaseZoneSemaphore(void)
{
    //
    // FLSEM register address.
    //
    uint32_t regAddress = DCSMCOMMON_BASE + DCSM_O_FLSEM;

    EALLOW;

    //
    // Write 0xA5 to the key and write the zone that is attempting to claim the
    // Flash Pump Semaphore to the semaphore bits.
    //
    HWREGH(regAddress) = ((uint16_t)FLSEM_KEY << DCSM_FLSEM_KEY_S);
    EDIS;

    //
    // If the calling function was unable to release the zone semaphore, then
    // return false
    //
    return(((HWREGH(regAddress) & DCSM_FLSEM_SEM_M) == 0x0U) ? true : false);
}
