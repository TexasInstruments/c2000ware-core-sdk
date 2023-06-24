//###########################################################################
//
// FILE:   memcfg.c
//
// TITLE:  CM SRAM config driver.
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

#include "memcfg.h"

//*****************************************************************************
//
// MemCfg_lockConfig
//
//*****************************************************************************
void
MemCfg_lockConfig(uint32_t memSections)
{
    //
    // Check the arguments.
    //
    ASSERT(((memSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_CX)     ||
           ((memSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_SX)     ||
           ((memSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_ROM)    ||
           ((memSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_PERIMEM)||
           ((memSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_CMMSGX) ||
           (memSections == MEMCFG_SECT_ALL));

    //
    // Set the bit that blocks writes to the sections' configuration registers.
    //
    switch(memSections & MEMCFG_SECT_TYPE_MASK)
    {
        case MEMCFG_SECT_TYPE_CX:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_CXLOCK) |= (MEMCFG_SECT_NUM_MASK &
                                                       memSections);
            break;

        case MEMCFG_SECT_TYPE_CMMSGX:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_CMMSGXLOCK) |= (MEMCFG_SECT_NUM_MASK
                                                           & memSections);
            break;

        case MEMCFG_SECT_TYPE_SX:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_SXGROUP1_LOCK) |=
                                          (MEMCFG_SECT_NUM_MASK & memSections);
            break;

        case MEMCFG_SECT_TYPE_ROM:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_ROM_LOCK) |= (MEMCFG_SECT_NUM_MASK &
                                                         memSections);
            break;

        case MEMCFG_SECT_TYPE_PERIMEM:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_LOCK) |=
                                          (MEMCFG_SECT_NUM_MASK & memSections);
            break;

        case MEMCFG_SECT_TYPE_MASK:
            //
            // Lock configuration for all sections.
            //
            HWREG(CMMEMCFG_BASE + MEMCFG_O_CXLOCK)  |=
                               (MEMCFG_SECT_NUM_MASK & MEMCFG_SECT_CX_ALL);

            HWREG(CMMEMCFG_BASE + MEMCFG_O_CMMSGXLOCK) |=
                               (MEMCFG_SECT_NUM_MASK & MEMCFG_SECT_CMMSGX_ALL);

            HWREG(CMMEMCFG_BASE + MEMCFG_O_SXGROUP1_LOCK) |=
                               (MEMCFG_SECT_NUM_MASK & MEMCFG_SECT_SX_ALL);

            HWREG(CMMEMCFG_BASE + MEMCFG_O_ROM_LOCK) |=
                               (MEMCFG_SECT_NUM_MASK & MEMCFG_SECT_ROM);

            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_LOCK) |=
                               (MEMCFG_SECT_NUM_MASK & MEMCFG_SECT_PERIMEM_ALL);
            break;

        default:
            //
            // Do nothing. Invalid memSections. Make sure you aren't OR-ing
            // values for two different types of RAM.
            //
            break;
    }
}

//*****************************************************************************
//
// MemCfg_unlockConfig
//
//*****************************************************************************
void
MemCfg_unlockConfig(uint32_t memSections)
{
    //
    // Check the arguments.
    //
    ASSERT(((memSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_CX)     ||
           ((memSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_SX)     ||
           ((memSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_ROM)    ||
           ((memSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_PERIMEM)||
           ((memSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_CMMSGX) ||
           (memSections == MEMCFG_SECT_ALL));

    //
    // Clear the bit that blocks writes to the sections' configuration
    // registers.
    //
    switch(memSections & MEMCFG_SECT_TYPE_MASK)
    {
        case MEMCFG_SECT_TYPE_CX:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_CXLOCK) &=
                                         ~(MEMCFG_SECT_NUM_MASK & memSections);
            break;

        case MEMCFG_SECT_TYPE_CMMSGX:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_CMMSGXLOCK) &=
                                         ~(MEMCFG_SECT_NUM_MASK & memSections);
            break;

        case MEMCFG_SECT_TYPE_SX:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_SXGROUP1_LOCK) &=
                                         ~(MEMCFG_SECT_NUM_MASK & memSections);
            break;

        case MEMCFG_SECT_TYPE_ROM:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_ROM_LOCK) &=
                                         ~(MEMCFG_SECT_NUM_MASK & memSections);
            break;

        case MEMCFG_SECT_TYPE_PERIMEM:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_LOCK) &=
                                         ~(MEMCFG_SECT_NUM_MASK & memSections);
            break;

        case MEMCFG_SECT_TYPE_MASK:
            //
            // Lock configuration for all sections.
            //
            HWREG(CMMEMCFG_BASE + MEMCFG_O_CXLOCK)             &= ~((uint32_t)
                              (MEMCFG_SECT_NUM_MASK & MEMCFG_SECT_CX_ALL));

            HWREG(CMMEMCFG_BASE + MEMCFG_O_CMMSGXLOCK)         &= ~((uint32_t)
                              (MEMCFG_SECT_NUM_MASK & MEMCFG_SECT_CMMSGX_ALL));

            HWREG(CMMEMCFG_BASE + MEMCFG_O_SXGROUP1_LOCK)      &= ~((uint32_t)
                              (MEMCFG_SECT_NUM_MASK & MEMCFG_SECT_SX_ALL));

            HWREG(CMMEMCFG_BASE + MEMCFG_O_ROM_LOCK)           &= ~((uint32_t)
                              (MEMCFG_SECT_NUM_MASK & MEMCFG_SECT_ROM));

            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_LOCK) &= ~((uint32_t)
                              (MEMCFG_SECT_NUM_MASK & MEMCFG_SECT_PERIMEM_ALL));
            break;

        default:
            //
            // Do nothing. Invalid memSections. Make sure you aren't OR-ing
            // values for two different types of RAM.
            //
            break;
    }
}

//*****************************************************************************
//
// MemCfg_setTestMode
//
//*****************************************************************************
void
MemCfg_setTestMode(uint32_t memSection, MemCfg_TestMode testMode)
{
    uint32_t shiftVal = 0U;
    uint32_t maskVal;
    uint32_t regVal;
    uint32_t sectionNum;

    //
    // Check the arguments.
    //
    ASSERT(((memSection & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_CX)  ||
           ((memSection & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_SX)  ||
           ((memSection & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_ROM) ||
           ((memSection & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_CMMSGX));

    //
    // Calculate how far the protect mode value needs to be shifted. Each
    // section number is represented by a bit in the lower word of memSection
    // and 2 bits in the corresponding TEST register.
    //
    sectionNum = memSection & MEMCFG_SECT_NUM_MASK;

    while(sectionNum != 1U)
    {
        sectionNum = sectionNum >> 1U;
        shiftVal += 2U;
    }

    maskVal = (uint32_t)MEMCFG_TESTMODE_M << shiftVal;
    regVal =  ((uint32_t)testMode) << shiftVal;

    //
    // Write the test mode into the appropriate field
    //
    switch(memSection & MEMCFG_SECT_TYPE_MASK)
    {
        case MEMCFG_SECT_TYPE_CX:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_CXTEST) =
                ((HWREG(CMMEMCFG_BASE + MEMCFG_O_CXTEST) & ~maskVal) | regVal);
            break;

        case MEMCFG_SECT_TYPE_CMMSGX:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_CMMSGXTEST) =
            ((HWREG(CMMEMCFG_BASE + MEMCFG_O_CMMSGXTEST) & ~maskVal) | regVal);
            break;

        case MEMCFG_SECT_TYPE_SX:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_SXGROUP1_TEST) =
                ((HWREG(CMMEMCFG_BASE + MEMCFG_O_CXTEST) & ~maskVal) | regVal);
            break;

        case MEMCFG_SECT_TYPE_ROM:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_ROM_TEST) =
              ((HWREG(CMMEMCFG_BASE + MEMCFG_O_ROM_TEST) & ~maskVal) | regVal);
            break;

        default:
            //
            // Do nothing. Invalid memSection.
            //
            break;
    }
}

//*****************************************************************************
//
// MemCfg_initSections
//
//*****************************************************************************
void
MemCfg_initSections(uint32_t ramSections)
{
    //
    // Check the arguments.
    //
    ASSERT(((ramSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_CX)     ||
           ((ramSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_SX)     ||
           ((ramSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_CMMSGX) ||
           (ramSections == MEMCFG_SECT_ALL));

    //
    // Set the bit in the various initialization registers that starts
    // initialization.
    //
    switch(ramSections & MEMCFG_SECT_TYPE_MASK)
    {
        case MEMCFG_SECT_TYPE_CX:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_CXINIT)        |=
                                          (MEMCFG_SECT_NUM_MASK & ramSections);
            break;

        case MEMCFG_SECT_TYPE_CMMSGX:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_CMMSGXINIT)    |=
                                          (MEMCFG_SECT_NUM_MASK & ramSections);
            break;

        case MEMCFG_SECT_TYPE_SX:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_SXGROUP1_INIT) |=
                                          (MEMCFG_SECT_NUM_MASK & ramSections);
            break;

        case MEMCFG_SECT_TYPE_MASK:
            //
            // Initialize all sections.
            //
            HWREG(CMMEMCFG_BASE + MEMCFG_O_CXINIT)        |=
                               (MEMCFG_SECT_NUM_MASK & MEMCFG_SECT_CX_ALL);

            HWREG(CMMEMCFG_BASE + MEMCFG_O_CMMSGXINIT)    |=
                               (MEMCFG_SECT_NUM_MASK & MEMCFG_SECT_CMMSGX_ALL);

            HWREG(CMMEMCFG_BASE + MEMCFG_O_SXGROUP1_INIT) |=
                               (MEMCFG_SECT_NUM_MASK & MEMCFG_SECT_SX_ALL);
            break;

        default:
            //
            // Do nothing. Invalid ramSections. Make sure you aren't OR-ing
            // values for two different types of RAM.
            //
            break;
    }
}

//*****************************************************************************
//
// MemCfg_getInitStatus
//
//*****************************************************************************
bool
MemCfg_getInitStatus(uint32_t ramSections)
{
    uint32_t status;

    //
    // Check the arguments.
    //
    ASSERT(((ramSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_CX)     ||
           ((ramSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_SX)     ||
           ((ramSections & MEMCFG_SECT_TYPE_MASK) == MEMCFG_SECT_TYPE_CMMSGX) ||
           (ramSections == MEMCFG_SECT_ALL));

    //
    // Read registers containing the initialization complete status.
    //
    switch(ramSections & MEMCFG_SECT_TYPE_MASK)
    {
        case MEMCFG_SECT_TYPE_CX:
            status = HWREG(CMMEMCFG_BASE + MEMCFG_O_CXINITDONE);
            break;

        case MEMCFG_SECT_TYPE_CMMSGX:
            status = HWREG(CMMEMCFG_BASE + MEMCFG_O_CMMSGXINITDONE);
            break;

        case MEMCFG_SECT_TYPE_SX:
            status = HWREG(CMMEMCFG_BASE + MEMCFG_O_SXGROUP1_INITDONE);
            break;

        case MEMCFG_SECT_TYPE_MASK:
            //
            // Return the overall status.
            //
            if((HWREG(CMMEMCFG_BASE + MEMCFG_O_CXINITDONE) ==
                MEMCFG_SECT_CX_ALL)     &&
               (HWREG(CMMEMCFG_BASE + MEMCFG_O_CMMSGXINITDONE) ==
                MEMCFG_SECT_CMMSGX_ALL) &&
               (HWREG(CMMEMCFG_BASE + MEMCFG_O_SXGROUP1_INITDONE) ==
                MEMCFG_SECT_SX_ALL))
            {
                status = MEMCFG_SECT_NUM_MASK;
            }
            else
            {
                status = 0x0U;
            }
            break;

        default:
            //
            // Invalid ramSections. Make sure you aren't OR-ing values for two
            // different types of RAM.
            //
            status = 0x0U;
            break;
    }
    return((ramSections & status) == (ramSections & MEMCFG_SECT_NUM_MASK));
}

//*****************************************************************************
//
// MemCfg_forceMemError
//
//*****************************************************************************
void
MemCfg_forceMemError(uint32_t memTypes)
{
    //
    // Check the arguments.
    //
    ASSERT((memTypes == MEMCFG_SECT_ROM) ||
           (memTypes == MEMCFG_SECT_PERIMEM_EMAC) ||
           (memTypes == MEMCFG_SECT_PERIMEM_ETHERCAT) ||
           (memTypes == MEMCFG_SECT_ALL));

    //
    // Forces error in the selected memory.
    //
    switch(memTypes)
    {
        case MEMCFG_SECT_ROM:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_ROM_FORCE_ERROR) |=
                         MEMCFG_ROM_FORCE_ERROR_FORCE_BOOTROM_ERROR;
            break;

        case MEMCFG_SECT_PERIMEM_EMAC:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_CONTROL) |=
                         MEMCFG_PERI_MEM_TEST_CONTROL_EMAC_MEM_FORCE_ERROR;
            break;

        case MEMCFG_SECT_PERIMEM_ETHERCAT:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_CONTROL) |=
                         MEMCFG_PERI_MEM_TEST_CONTROL_ETHERCAT_MEM_FORCE_ERROR;
            break;

        case MEMCFG_SECT_ALL:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_ROM_FORCE_ERROR) |=
                         MEMCFG_ROM_FORCE_ERROR_FORCE_BOOTROM_ERROR;

            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_CONTROL)  |=
                         MEMCFG_PERI_MEM_TEST_CONTROL_EMAC_MEM_FORCE_ERROR;

            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_CONTROL)      |=
                         MEMCFG_PERI_MEM_TEST_CONTROL_ETHERCAT_MEM_FORCE_ERROR;
            break;

        default:
            //
            // Do nothing. Invalid memory.
            //
            break;
    }
}

//*****************************************************************************
//
// MemCfg_enablePeriMemTestMode
//
//*****************************************************************************
void
MemCfg_enablePeriMemTestMode(uint32_t memTypes)
{
    //
    // Check the arguments.
    //
    ASSERT((memTypes == MEMCFG_SECT_PERIMEM_EMAC)     ||
           (memTypes == MEMCFG_SECT_PERIMEM_ETHERCAT) ||
           (memTypes == MEMCFG_SECT_PERIMEM_ALL));

    //
    // Enables test mode for selected memory type.
    //
    switch(memTypes)
    {
        case MEMCFG_SECT_PERIMEM_EMAC:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_CONTROL) |=
                                 MEMCFG_PERI_MEM_TEST_CONTROL_EMAC_TEST_ENABLE;
            break;

        case MEMCFG_SECT_PERIMEM_ETHERCAT:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_CONTROL) |=
                             MEMCFG_PERI_MEM_TEST_CONTROL_ETHERCAT_TEST_ENABLE;
            break;

        case MEMCFG_SECT_PERIMEM_ALL:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_CONTROL) |=
                                 MEMCFG_PERI_MEM_TEST_CONTROL_EMAC_TEST_ENABLE;

            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_CONTROL) |=
                             MEMCFG_PERI_MEM_TEST_CONTROL_ETHERCAT_TEST_ENABLE;
            break;

        default:
            //
            // Do nothing. Invalid memory type.
            //
            break;
    }
}

//*****************************************************************************
//
// MemCfg_disablePeriMemTestMode
//
//*****************************************************************************
void
MemCfg_disablePeriMemTestMode(uint32_t memTypes)
{
    //
    // Check the arguments.
    //
    ASSERT((memTypes == MEMCFG_SECT_PERIMEM_EMAC)     ||
           (memTypes == MEMCFG_SECT_PERIMEM_ETHERCAT) ||
           (memTypes == MEMCFG_SECT_PERIMEM_ALL));

    //
    // Disables test mode for selected memory type.
    //
    switch(memTypes)
    {
        case MEMCFG_SECT_PERIMEM_EMAC:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_CONTROL) &=
                                ~MEMCFG_PERI_MEM_TEST_CONTROL_EMAC_TEST_ENABLE;
            break;

        case MEMCFG_SECT_PERIMEM_ETHERCAT:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_CONTROL) &=
                            ~MEMCFG_PERI_MEM_TEST_CONTROL_ETHERCAT_TEST_ENABLE;
            break;

        case MEMCFG_SECT_PERIMEM_ALL:
            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_CONTROL) &=
                            ~MEMCFG_PERI_MEM_TEST_CONTROL_EMAC_TEST_ENABLE;

            HWREG(CMMEMCFG_BASE + MEMCFG_O_PERI_MEM_TEST_CONTROL) &=
                            ~MEMCFG_PERI_MEM_TEST_CONTROL_ETHERCAT_TEST_ENABLE;
            break;

        default:
            //
            // Do nothing. Invalid memory type.
            //
            break;
    }
}

//*****************************************************************************
//
// MemCfg_getUncorrErrorAddress
//
//*****************************************************************************
uint32_t
MemCfg_getUncorrErrorAddress(uint32_t stsFlag)
{
    uint32_t errAddress;

    //
    // Gets address location of selected uncorrectable read/write error.
    //
    switch(stsFlag)
    {
    case MEMCFG_UCERR_M4READ:
    case MEMCFG_UCERR_M4WRITE:
        errAddress = HWREG(CMMEMORYERROR_BASE + MEMCFG_O_UCM4EADDR);
        break;

    case MEMCFG_UCERR_EMACREAD:
        errAddress = HWREG(CMMEMORYERROR_BASE + MEMCFG_O_UCEMACEADDR);
        break;

    case MEMCFG_UCERR_UDMAREAD:
    case MEMCFG_UCERR_UDMAWRITE:
        errAddress = HWREG(CMMEMORYERROR_BASE + MEMCFG_O_UCUDMAEADDR);
        break;

    case MEMCFG_UCERR_ETHERCATMEMREAD:
        errAddress = HWREG(CMMEMORYERROR_BASE + MEMCFG_O_UCETHERCATMEMREADDR);
        break;

    case MEMCFG_UCERR_EMACMEMREAD:
        errAddress = HWREG(CMMEMORYERROR_BASE + MEMCFG_O_UCEMACMEMREADDR);
        break;

    default:
        //
        // Invalid stsFlag.
        //
        errAddress = 0x0U;
        break;
    }
    return(errAddress);
}

//*****************************************************************************
//
// MemCfg_getCorrErrorAddress
//
//*****************************************************************************
uint32_t
MemCfg_getCorrErrorAddress(uint32_t stsFlag)
{
    uint32_t errAddress;

    //
    // Gets address location of selected uncorrectable read/write error.
    //
    switch(stsFlag)
    {
        case MEMCFG_CERR_M4READ:
        case MEMCFG_CERR_M4WRITE:
            errAddress = HWREG(CMMEMORYERROR_BASE + MEMCFG_O_CM4EADDR);
            break;

        case MEMCFG_CERR_EMACREAD:
            errAddress = HWREG(CMMEMORYERROR_BASE + MEMCFG_O_CEMACEADDR);
            break;

        case MEMCFG_CERR_UDMAREAD:
        case MEMCFG_CERR_UDMAWRITE:
            errAddress = HWREG(CMMEMORYERROR_BASE + MEMCFG_O_CUDMAEADDR);
            break;

        default:
            //
            // Invalid stsFlag.
            //
            errAddress = 0x0U;
            break;
    }
    return(errAddress);
}

//*****************************************************************************
//
// MemCfg_getBusFaultAddress
//
//*****************************************************************************
uint32_t
MemCfg_getBusFaultAddress(uint32_t busMaster)
{
    uint32_t offset, temp;

    //
    // Calculate the address offset for selected bus master.
    //
    offset = 0U;
    temp = busMaster;
    while(temp > 1U)
    {
        temp = temp >> 1U;
        offset += (uint32_t)(MEMCFG_O_UDMABUSFAULTADDR -
                             MEMCFG_O_M4BUSFAULTADDR);
    }

    //
    // Read and return the bus fault address at the calculated offset.
    //
    return(HWREG(CMMEMORYERROR_BASE + (uint32_t)MEMCFG_O_M4BUSFAULTADDR +
                 offset));
}
