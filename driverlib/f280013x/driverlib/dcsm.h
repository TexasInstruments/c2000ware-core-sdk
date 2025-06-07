//#############################################################################
//
// FILE:   dcsm.h
//
// TITLE:  C28x Driver for the DCSM security module.
//
//#############################################################################
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef DCSM_H
#define DCSM_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup dcsm_api DCSM
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_dcsm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// Defines for the unlockZone1CSM() and unlockZone2CSM().
// These are not parameters for any function.
// These are not intended for application code.
//
//*****************************************************************************

#define DCSM_O_Z1_CSMPSWD0              0x00U //!< Z1 CSMPSWD0 offset
#define DCSM_O_Z1_CSMPSWD1              0x02U //!< Z1 CSMPSWD1 offset
#define DCSM_O_Z1_CSMPSWD2              0x04U //!< Z1 CSMPSWD2 offset
#define DCSM_O_Z1_CSMPSWD3              0x06U //!< Z1 CSMPSWD3 offset
#define DCSM_O_Z2_CSMPSWD0              0x00U //!< Z2 CSMPSWD0 offset
#define DCSM_O_Z2_CSMPSWD1              0x02U //!< Z2 CSMPSWD1 offset
#define DCSM_O_Z2_CSMPSWD2              0x04U //!< Z2 CSMPSWD2 offset
#define DCSM_O_Z2_CSMPSWD3              0x06U //!< Z2 CSMPSWD3 offset

//*****************************************************************************
//
// Register key defines.
//
//*****************************************************************************
#define FLSEM_KEY                       0xA5U //!< Zone semaphore key
#define DCSM_FORCE_SECERR_KEY                0x5A5AU

//*****************************************************************************
//
//! Data structures to hold password keys.
//
//*****************************************************************************
typedef struct
{
    uint32_t csmKey0;
    uint32_t csmKey1;
    uint32_t csmKey2;
    uint32_t csmKey3;
} DCSM_CSMPasswordKey;

//*****************************************************************************
//
//! Values to distinguish the status of RAM or FLASH sectors. These values
//! describe which zone the memory location belongs too.
//! These values can be returned from DCSM_getRAMZone(),
//! DCSM_getFlashSectorZone().
//
//*****************************************************************************
typedef enum
{
    DCSM_MEMORY_INACCESSIBLE, //!< Inaccessible
    DCSM_MEMORY_ZONE1,        //!< Zone 1
    DCSM_MEMORY_ZONE2,        //!< Zone 2
    DCSM_MEMORY_FULL_ACCESS   //!< Full access
} DCSM_MemoryStatus;

//*****************************************************************************
//
//! Values to pass to DCSM_claimZoneSemaphore(). These values are used
//! to describe the zone that can write to Flash Wrapper registers.
//
//*****************************************************************************
typedef enum
{
    DCSM_FLSEM_ZONE1 = 0x01U, //!< Flash semaphore Zone 1
    DCSM_FLSEM_ZONE2 = 0x02U  //!< Flash semaphore Zone 2
} DCSM_SemaphoreZone;

//*****************************************************************************
//
//! Values to distinguish the security status of the zones.
//! These values can be returned from DCSM_getZone1CSMSecurityStatus(),
//! DCSM_getZone2CSMSecurityStatus().
//
//*****************************************************************************
typedef enum
{
    DCSM_STATUS_SECURE,   //!< Secure
    DCSM_STATUS_UNSECURE, //!< Unsecure
    DCSM_STATUS_LOCKED,   //!< Locked
    DCSM_STATUS_BLOCKED   //!< Blocked
} DCSM_SecurityStatus;

//*****************************************************************************
//
// Values to distinguish the status of the Control Registers. These values
// describe can be used with the return values of
// DCSM_getZone1ControlStatus(), and DCSM_getZone2ControlStatus().
//
//*****************************************************************************
#define DCSM_ALLZERO     0x08U  //!< CSM Passwords all zeros
#define DCSM_ALLONE      0x10U  //!< CSM Passwords all ones
#define DCSM_UNSECURE    0x20U  //!< Zone is secure/unsecure
#define DCSM_ARMED       0x40U  //!< CSM is armed

//*****************************************************************************
//
//! Values to decribe the EXEONLY Status.
//! These values are returned from  to DCSM_getZone1RAMEXEStatus(),
//! DCSM_getZone2RAMEXEStatus(), DCSM_getZone1FlashEXEStatus(),
//! DCSM_getZone2FlashEXEStatus().
//
//*****************************************************************************
typedef enum
{
    DCSM_PROTECTED,      //!< Protected
    DCSM_UNPROTECTED,    //!< Unprotected
    DCSM_INCORRECT_ZONE  //!< Incorrect Zone
}DCSM_EXEOnlyStatus;

//*****************************************************************************
//
//! Values to distinguish RAM Module.
//! These values can be passed to DCSM_getZone1RAMEXEStatus()
//! DCSM_getZone2RAMEXEStatus(), DCSM_getRAMZone().
//
//*****************************************************************************
typedef enum
{
    //
    //C28x RAMs
    //
    DCSM_RAMLS0_SECA, //!< RAMLS0 Section A
    DCSM_RAMLS0_SECB, //!< RAMLS0 Section B
    DCSM_RAMLS0_SECC, //!< RAMLS0 Section C
    DCSM_RAMLS0_SECD, //!< RAMLS0 Section D
    DCSM_RAMLS1_SECA, //!< RAMLS1 Section A
    DCSM_RAMLS1_SECB, //!< RAMLS1 Section B
    DCSM_RAMLS1_SECC, //!< RAMLS1 Section C
    DCSM_RAMLS1_SECD, //!< RAMLS1 Section D
    DCSM_CLA    = 14U //!<Offset of CLA field in in RAMSTAT divided by two
} DCSM_RAMModule;

//*****************************************************************************
//
//! Values to distinguish Flash Sector.
//! These values can be passed to DCSM_getZone1FlashEXEStatus()
//! DCSM_getZone2FlashEXEStatus(), DCSM_getFlashSectorZone().
//
//*****************************************************************************


typedef enum
{
    DCSM_SECTOR_0,        //!< Sector 0
    DCSM_SECTOR_1,        //!< Sector 1
    DCSM_SECTOR_2,        //!< Sector 2
    DCSM_SECTOR_3,        //!< Sector 3
    DCSM_SECTOR_4,        //!< Sector 4
    DCSM_SECTOR_5,        //!< Sector 5
    DCSM_SECTOR_6,        //!< Sector 6
    DCSM_SECTOR_7,        //!< Sector 7
    DCSM_SECTOR_8,        //!< Sector 8
    DCSM_SECTOR_9,        //!< Sector 9
    DCSM_SECTOR_10,       //!< Sector 10
    DCSM_SECTOR_11,       //!< Sector 11
    DCSM_SECTOR_12,       //!< Sector 12
    DCSM_SECTOR_13,       //!< Sector 13
    DCSM_SECTOR_14,       //!< Sector 14
    DCSM_SECTOR_15,       //!< Sector 15
    DCSM_SECTOR_16,       //!< Sector 16
    DCSM_SECTOR_17,       //!< Sector 17
    DCSM_SECTOR_18,       //!< Sector 18
    DCSM_SECTOR_19,       //!< Sector 19
    DCSM_SECTOR_20,       //!< Sector 20
    DCSM_SECTOR_21,       //!< Sector 21
    DCSM_SECTOR_22,       //!< Sector 22
    DCSM_SECTOR_23,       //!< Sector 23
    DCSM_SECTOR_24,       //!< Sector 24
    DCSM_SECTOR_25,       //!< Sector 25
    DCSM_SECTOR_26,       //!< Sector 26
    DCSM_SECTOR_27,       //!< Sector 27
    DCSM_SECTOR_28,       //!< Sector 28
    DCSM_SECTOR_29,       //!< Sector 29
    DCSM_SECTOR_30,       //!< Sector 30
    DCSM_SECTOR_31,       //!< Sector 31
    DCSM_SECTOR_39_32,    //!< Sector 39-32
    DCSM_SECTOR_47_40,    //!< Sector 47-40
    DCSM_SECTOR_55_48,    //!< Sector 55-48
    DCSM_SECTOR_63_56,    //!< Sector 63-56
    DCSM_SECTOR_71_64,    //!< Sector 71-64
    DCSM_SECTOR_79_72,    //!< Sector 79-72
    DCSM_SECTOR_87_80,    //!< Sector 87-80
    DCSM_SECTOR_95_88,    //!< Sector 95-88
    DCSM_SECTOR_103_96,   //!< Sector 103-96
    DCSM_SECTOR_111_104,  //!< Sector 111-104
    DCSM_SECTOR_119_112,  //!< Sector 119-112
    DCSM_SECTOR_127_120   //!< Sector 127-120
} DCSM_Sector;

//*****************************************************************************
//
//! The following are values that can be passed to
//! DCSM_getZone1OTPSecureLockStatus() & DCSM_getZone2OTPSecureLockStatus()
//! as \e lockType parameter.
//
//*****************************************************************************
typedef enum
{
    //! JTAG Lock Status
    DCSM_OTPSECLOCK_JTAG = 0x0U,
    //! Zone Password Lock
    DCSM_OTPSECLOCK_PSWDLOCK = 0x1U,

} DCSM_OTPLock;
//*****************************************************************************
//
// Defines for the EXEONLYSECTxR register.
// These values can be used in the DCSM_getZone1FlashEXEStatus() &
// DCSM_getZone2FlashEXEStatus().
//
//*****************************************************************************

#define DCSM_EXEONLYSECTR_M             0x0000FFFFU
#define DCSM_EXEONLYSECTR_S             16U

//*****************************************************************************
//
// Defines for the Z1_CR  & Z2_CR register.
// These values can be used in the DCSM_getZone1ControlStatus() &
// DCSM_getZone2ControlStatus().
//
//*****************************************************************************

#define DCSM_ZX_CR_S                    16U

//*****************************************************************************
//
// Defines for the OTPSECLOCK register.
// These values can be used in the DCSM_getZone1OTPSecureLockStatus()
// & DCSM_getZone2OTPSecureLockStatus()
//
//*****************************************************************************

#define DCSM_Z1_OTPSECLOCK_JTAGLOCK_M             0x1U
#define DCSM_Z1_OTPSECLOCK_JTAGLOCK_S             0U
#define DCSM_OTPSECLOCK_INVALID                   0xFFFFU

//*****************************************************************************
//
// DCSM functions
//
//*****************************************************************************

//*****************************************************************************
//
//! Secures zone 1 by setting the FORCESEC bit of Z1_CR register
//!
//! This function resets the state of the zone. If the zone is unlocked,
//! it will lock(secure) the zone and also reset all the bits in the
//! Control Register.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCSM_secureZone1(void)
{
    //
    // Write to the FORCESEC bit.
    //
    HWREG(DCSM_Z1_BASE + DCSM_O_Z1_CR)|= DCSM_Z1_CR_FORCESEC;
}

//*****************************************************************************
//
//! Secures zone 2 by setting the FORCESEC bit of Z2_CR register
//!
//! This function resets the state of the zone. If the zone is unlocked,
//! it will lock(secure) the zone and also reset all the bits in the
//! Control Register.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCSM_secureZone2(void)
{
    //
    // Write to the FORCESEC bit.
    //
    HWREG(DCSM_Z2_BASE + DCSM_O_Z2_CR)|= DCSM_Z2_CR_FORCESEC;
}

//*****************************************************************************
//
//! Returns the CSM security status of zone 1
//!
//! This function returns the security status of zone 1 CSM
//!
//! \return Returns security status as an enumerated type DCSM_SecurityStatus.
//
//*****************************************************************************
static inline DCSM_SecurityStatus
DCSM_getZone1CSMSecurityStatus(void)
{
    uint32_t status;
    DCSM_SecurityStatus returnStatus;
    status = HWREG(DCSM_Z1_BASE + DCSM_O_Z1_CR);

    //
    // if ARMED bit is set and UNSECURED bit is set then CSM is unsecured.
    // Else it is secure.
    //
    if(((status & DCSM_Z1_CR_ARMED) != 0U) &&
       ((status & DCSM_Z1_CR_UNSECURE) != 0U))
    {
        returnStatus = DCSM_STATUS_UNSECURE;
    }
    else if((status & DCSM_Z1_CR_ALLONE) == DCSM_Z1_CR_ALLONE)
    {
        returnStatus = DCSM_STATUS_BLOCKED;
    }
    else if((status & DCSM_Z1_CR_ALLZERO) == DCSM_Z1_CR_ALLZERO)
    {
        returnStatus = DCSM_STATUS_LOCKED;
    }
    else
    {
        returnStatus = DCSM_STATUS_SECURE;
    }

    return(returnStatus);
}

//*****************************************************************************
//
//! Returns the CSM security status of zone 2
//!
//! This function returns the security status of zone 2 CSM
//!
//! \return Returns security status as an enumerated type DCSM_SecurityStatus.
//
//*****************************************************************************
static inline DCSM_SecurityStatus
DCSM_getZone2CSMSecurityStatus(void)
{
    uint32_t status;
    DCSM_SecurityStatus returnStatus;
    status = HWREG(DCSM_Z2_BASE + DCSM_O_Z2_CR);

    //
    // if ARMED bit is set and UNSECURED bit is set then CSM is unsecured.
    // Else it is secure.
    //
    if(((status & DCSM_Z2_CR_ARMED) != 0U) &&
       ((status & DCSM_Z2_CR_UNSECURE) != 0U))
    {
        returnStatus = DCSM_STATUS_UNSECURE;
    }
    else if((status & DCSM_Z2_CR_ALLONE) == DCSM_Z2_CR_ALLONE)
    {
        returnStatus = DCSM_STATUS_BLOCKED;
    }
    else if((status & DCSM_Z2_CR_ALLZERO) == DCSM_Z2_CR_ALLZERO)
    {
        returnStatus = DCSM_STATUS_LOCKED;
    }
    else
    {
        returnStatus = DCSM_STATUS_SECURE;
    }

    return(returnStatus);
}

//*****************************************************************************
//
//! Returns the Control Status of zone 1
//!
//! This function returns the Control Status of zone 1 CSM
//!
//! \return Returns the contents of the Control Register which can be
//! used with provided defines.
//
//*****************************************************************************
static inline uint16_t
DCSM_getZone1ControlStatus(void)
{
    uint32_t stat;
    //
    // Return the contents of the CR register.
    //

    stat = ((HWREG(DCSM_Z1_BASE + DCSM_O_Z1_CR)) >> DCSM_ZX_CR_S);

    return((uint16_t)stat);

}

//*****************************************************************************
//
//! Returns the Control Status of zone 2
//!
//! This function returns the Control Status of zone 2 CSM
//!
//! \return Returns the contents of the Control Register which can be
//! used with the provided defines.
//
//*****************************************************************************
static inline uint16_t
DCSM_getZone2ControlStatus(void)
{
    uint32_t stat;
    //
    // Return the contents of the CR register.
    //
    stat = ((HWREG(DCSM_Z2_BASE + DCSM_O_Z2_CR)) >> DCSM_ZX_CR_S);

    return((uint16_t)stat);
}

//*****************************************************************************
//
//! Returns the security zone a RAM section belongs to
//!
//! \param module is the RAM module value. Valid values are type DCSM_RAMModule
//! C28x RAMs :
//! - \b DCSM_RAMLS0_SECA
//! - \b DCSM_RAMLS0_SECB
//! - \b DCSM_RAMLS0_SECC
//! - \b DCSM_RAMLS0_SECD
//! - \b DCSM_RAMLS1_SECA
//! - \b DCSM_RAMLS1_SECB
//! - \b DCSM_RAMLS1_SECC
//! - \b DCSM_RAMLS1_SECD
//!
//! This function returns the security zone a RAM section belongs to.
//!
//! \return Returns DCSM_MEMORY_INACCESSIBLE if the section is inaccessible,
//! DCSM_MEMORY_ZONE1 if the section belongs to zone 1, DCSM_MEMORY_ZONE2 if
//! the section belongs to zone 2 and DCSM_MEMORY_FULL_ACCESS if the section
//! doesn't  belong to any zone (or if the section is unsecure).
//
//*****************************************************************************
static inline DCSM_MemoryStatus
DCSM_getRAMZone(DCSM_RAMModule module)
{
    uint16_t shift = (uint16_t)module * 2U;
    uint32_t ramStatus;
    //
    //Read the RAMSTAT register for the specific RAM Module.
    //
    ramStatus = ((HWREG(DCSMCOMMON_BASE + DCSM_O_RAMSTAT1) >>
                                shift) & 0x03U);
    return((DCSM_MemoryStatus)ramStatus);
}

//*****************************************************************************
//
//! Returns the security zone a flash sector belongs to
//!
//! \param sector is the flash sector value.  Use DCSM_Sector type.
//!
//! This function returns the security zone a flash sector belongs to.
//!
//! \return Returns DCSM_MEMORY_INACCESSIBLE if the section is inaccessible ,
//! DCSM_MEMORY_ZONE1 if the section belongs to zone 1, DCSM_MEMORY_ZONE2 if
//! the section belongs to zone 2 and DCSM_MEMORY_FULL_ACCESS if the section
//! doesn't  belong to any zone (or if the section is unsecure)..
//
//*****************************************************************************
static inline DCSM_MemoryStatus
DCSM_getFlashSectorZone(DCSM_Sector sector)
{
    uint32_t sectStat;
    uint16_t shift;

    //
    // Get the Sector status register for the specific bank
    //
    if(sector <= DCSM_SECTOR_15)
    {
        sectStat = HWREG(DCSMCOMMON_BASE + DCSM_O_SECTSTAT1);
        shift = (uint16_t)sector * 2U;
    }
    else if(sector <= DCSM_SECTOR_31)
    {
        sectStat = HWREG(DCSMCOMMON_BASE + DCSM_O_SECTSTAT2);
        shift = ((uint16_t)sector & 0xFU) * (uint16_t)2U;
    }
    else
    {
        sectStat = HWREG(DCSMCOMMON_BASE + DCSM_O_SECTSTAT3);
        shift = ((uint16_t)sector & 0xFU) * (uint16_t)2U;
    }

    //
    //Read the SECTSTAT register for the specific Flash Sector.
    //
    return((DCSM_MemoryStatus)((uint16_t)((sectStat >> shift) & 0x3U)));
}

//*****************************************************************************
//
//! Read Zone 1 Link Pointer Error
//!
//! A non-zero value indicates an error on the bit position that is set to 1.
//!
//! \return Returns the value of the Zone 1 Link Pointer error.
//
//*****************************************************************************
static inline uint32_t
DCSM_getZone1LinkPointerError(void)
{
    //
    // Return the LinkPointer Error for specific bank
    //
    return(HWREG(DCSM_Z1_BASE + DCSM_O_Z1_LINKPOINTERERR));
}

//*****************************************************************************
//
//! Read Zone 2 Link Pointer Error
//!
//! A non-zero value indicates an error on the bit position that is set to 1.
//!
//! \return Returns the value of the Zone 2 Link Pointer error.
//
//*****************************************************************************
static inline uint32_t
DCSM_getZone2LinkPointerError(void)
{
    //
    // Return the LinkPointer Error for specific bank
    //
    return(HWREG(DCSM_Z2_BASE + DCSM_O_Z2_LINKPOINTERERR));
}

//*****************************************************************************
//
//! Get the status of the security configuration load from USER-OTP or sector
//! error status
//!
//! \return Returns 0 if no error in loading security information from
//! USER-OTP, 1 if an error has occurred in the load from USER-OTP.
//
//*****************************************************************************
static inline bool
DCSM_getFlashErrorStatus(void)
{
    return((bool)(HWREG(DCSMCOMMON_BASE + DCSM_O_SECERRSTAT) &
                  DCSM_SECERRSTAT_ERR));
}

//*****************************************************************************
//
//! Clear the Flash Error Status bit
//!
//! Write a '1' to the clear bit to clear the sector error status bit.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCSM_clearFlashErrorStatus(void)
{
    HWREG(DCSMCOMMON_BASE + DCSM_O_SECERRCLR) |= DCSM_SECERRCLR_ERR;
}

//*****************************************************************************
//
//! Set the force Flash Error Status bit
//!
//! Write a '1' to force bit to set the sector error status bit.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCSM_forceFlashErrorStatus(void)
{
    HWREG(DCSMCOMMON_BASE +
          DCSM_O_SECERRFRC) = DCSM_SECERRFRC_ERR |
                              ((uint32_t)DCSM_FORCE_SECERR_KEY
                               << DCSM_SECERRFRC_KEY_S);
}

//*****************************************************************************
//
//! Returns the OTP secure Lock status of zone 1
//!
//! \param lockType is the  OTP secure Lock feature type .
//!
//! The \e lockType parameter can have one of the following values of the
//! DCSM_CPUSel type:
//! - \b DCSM_OTPSECLOCK_JTAG -  JTAG Lock Status
//! - \b DCSM_OTPSECLOCK_PSWDLOCK - Zone Password Lock
//!
//! This function takes in a valid OTP secure Lock feature type and
//! returns the status of zone 1 lock feature
//!
//! \return Returns security lock status can be:
//! For JTAG lock :  0 - JTAG is not locked , 1 - JTAG is locked
//!
//! For Zone Password Lock : 1111 - CSM Pwd locations in the OTP are not
//! protected and can be read from the debugger as well as code running
//! from anywhere.
//! Other Value : CSM Pwd locations in the OTP are protected and can't be read
//! without unlocking CSM of that zone.
//!
//! For Zone CRC Lock : 1111 : VCU has ability to calculate CRC
//! on secure memories.
//! Other Value : VCU doesn't have the ability to calculate CRC on
//! secure memories.
//
//*****************************************************************************
static inline uint32_t
DCSM_getZone1OTPSecureLockStatus(DCSM_OTPLock lockType)
{
    uint32_t status, returnStatus;
    status = HWREG(DCSM_Z1_BASE + DCSM_O_Z1_OTPSECLOCK);

    //
    // Reflects the state of the OTP Sec LOCK feature.
    //
    if(lockType == DCSM_OTPSECLOCK_JTAG)
    {
        returnStatus = (status & DCSM_Z1_OTPSECLOCK_JTAGLOCK_M) >>
                        DCSM_Z1_OTPSECLOCK_JTAGLOCK_S;
    }
    else if(lockType == DCSM_OTPSECLOCK_PSWDLOCK)
    {
        returnStatus = (status & DCSM_Z1_OTPSECLOCK_PSWDLOCK_M) >>
                        DCSM_Z1_OTPSECLOCK_PSWDLOCK_S;
    }
    else
    {
        returnStatus = (uint32_t)DCSM_OTPSECLOCK_INVALID;
    }

    return(returnStatus);
}

//*****************************************************************************
//
//! Returns the OTP secure Lock status of zone 2
//!
//! \param lockType is the  OTP secure Lock feature type .
//!
//! The \e lockType parameter can have one of the following values of the
//! DCSM_CPUSel type:
//! - \b DCSM_OTPSECLOCK_PSWDLOCK - Zone Password Lock
//!
//! This function takes in a valid OTP secure Lock feature type and
//! returns the status of zone 2 lock feature
//!
//! \return Returns security lock status can be:
//!
//! For Zone Password Lock : 1111 - CSM Pwd locations in the OTP are not
//! protected and can be read from the debugger as well as code running
//! from anywhere.
//! Other Value : CSM Pwd locations in the OTP are protected and can't be read
//! without unlocking CSM of that zone.
//!
//! For Zone CRC Lock : 1111 : VCU has ability to calculate CRC
//! on secure memories.
//! Other Value : VCU doesn't have the ability to calculate CRC on
//! secure memories.
//
//*****************************************************************************
static inline uint32_t
DCSM_getZone2OTPSecureLockStatus(DCSM_OTPLock lockType)
{
    uint32_t status, returnStatus;
    status = HWREG(DCSM_Z2_BASE + DCSM_O_Z2_OTPSECLOCK);

    //
    // Reflects the state of the OTP Sec LOCK feature.
    //
    if(lockType == DCSM_OTPSECLOCK_PSWDLOCK)
    {
        returnStatus = (status & DCSM_Z2_OTPSECLOCK_PSWDLOCK_M) >>
                        DCSM_Z2_OTPSECLOCK_PSWDLOCK_S;
    }
    else
    {
        returnStatus = (uint32_t)DCSM_OTPSECLOCK_INVALID;
    }

    return(returnStatus);
}

//*****************************************************************************
//
//! Returns the status of Deny Code register
//!
//! This function returns the status of Deny Code register
//!
//! \return Returns the Status of Deny Code register which can be
//! used with the provided defines.
//
//*****************************************************************************
static inline uint16_t
DCSM_getFlashDenyCodeStatus(void)
{
    return((uint16_t)(HWREG(DCSMCOMMON_BASE + DCSM_O_DENYCODE) & 0xFFU));
}

//*****************************************************************************
//
//! Get the status of the RAM Security after device initialization phase
//!
//! \return Returns 0 if Normal RAM security rule applies, 1 if all
//!  secured RAMs have become unsecured.
//
//*****************************************************************************
static inline bool
DCSM_getRAMOpenStatus(void)
{
    return((bool)(HWREG(DCSMCOMMON_BASE + DCSM_O_RAMOPENSTAT) &
                  DCSM_RAMOPENSTAT_RAMOPEN));

}

//*****************************************************************************
//
//! Set the RAM open bit
//!
//! Write a '1' to RAM open set bit to enable the RAM open mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCSM_forceRAMOpenStatus(void)
{
    HWREG(DCSMCOMMON_BASE +
         DCSM_O_RAMOPENFRC) = (uint32_t)DCSM_RAMOPENFRC_SET |
                              ((uint32_t)DCSM_FORCE_SECERR_KEY <<
                              DCSM_RAMOPENFRC_KEY_S);
}

//*****************************************************************************
//
//! Clear the RAM open Status bit
//!
//! Write a '1' to the clear bit to cme out of RAM open mode
//!
//! \return None.
//
//*****************************************************************************
static inline void
DCSM_clearRAMOpenStatus(void)
{
    HWREG(DCSMCOMMON_BASE +
         DCSM_O_RAMOPENCLR) = (uint32_t)DCSM_RAMOPENCLR_CLEAR |
                              ((uint32_t)DCSM_FORCE_SECERR_KEY <<
                              DCSM_RAMOPENCLR_KEY_S);
}

//*****************************************************************************
//
//! Set the RAM open lock bit
//!
//! If this bit is set, writes to RAMOPENFRC register is not allowed.
//!
//! \return None
//
//*****************************************************************************
static inline void
DCSM_setRAMOpenLockStatus(void)
{
    HWREG(DCSMCOMMON_BASE + DCSM_O_RAMOPENLOCK) |= DCSM_RAMOPENLOCK_LOCK;
}

//*****************************************************************************
//
//! Unlocks Zone 1 CSM.
//!
//! \param psCMDKey is a pointer to the DCSM_CSMPasswordKey struct that has the
//! CSM  password for zone 1.
//!
//! This function unlocks the CSM password. It first reads the
//! four password locations in the User OTP. If any of the password values is
//! different from 0xFFFFFFFF, it unlocks the device by writing the provided
//! passwords into CSM Key registers
//!
//! \return None.
//!
//! \note This function should not be called in an actual application,
//! should only be used for once to program the OTP memory. Ensure flash data
//! cache is disabled before calling this function(Flash_disableCache).
//
//*****************************************************************************
extern void
DCSM_unlockZone1CSM(const DCSM_CSMPasswordKey * const psCMDKey);

//*****************************************************************************
//
//! Unlocks Zone 2 CSM.
//!
//! \param psCMDKey is a pointer to the CSMPSWDKEY that has the CSM
//!  password for zone 2.
//!
//! This function unlocks the CSM password. It first reads
//! the four password locations in the User OTP. If any of the password values
//! is different from 0xFFFFFFFF, it unlocks the device by writing the
//! provided passwords into CSM Key registers
//!
//! \return None.
//!
//! \note This function should not be called in an actual application,
//! should only be used for once to program the OTP memory. Ensure flash data
//! cache is disabled before calling this function(Flash_disableCache).
//
//*****************************************************************************
extern void
DCSM_unlockZone2CSM(const DCSM_CSMPasswordKey * const psCMDKey);
//*****************************************************************************
//
//! Write Zone 1 CSM.
//!
//! \param psCMDKey is a pointer to the CSMPSWDKEY that has the CSM
//!  password for zone 1.
//!
//! Password match flow is essentially a sequence of dummy reads
//! from password locations (PWL) followed by writes to CSMKEY registers.
//! This function helps writing the provided passwords into the CSM Key
//! registers. The DCSM_readZone1CSMPwd() should be called
//! by CPU1 before calling this API.
//!
//! \return None.
//
//*****************************************************************************
extern void
DCSM_writeZone1CSM(const DCSM_CSMPasswordKey * const psCMDKey);

//*****************************************************************************
//
//! Write Zone 2 CSM.
//!
//! \param psCMDKey is a pointer to the CSMPSWDKEY that has the CSM
//!  password for zone 2.
//!
//! Password match flow is essentially a sequence of dummy reads
//! from password locations (PWL) followed by writes to CSMKEY registers.
//! This function helps writing the provided passwords into the CSM Key
//! registers. The DCSM_readZone2CSMPwd() should be called
//! by CPU1 before calling this API.
//!
//! \return None.
//
//*****************************************************************************
extern void
DCSM_writeZone2CSM(const DCSM_CSMPasswordKey * const psCMDKey);
//*****************************************************************************
//
//! Returns the EXE-ONLY status of zone 1 for a flash sector
//!
//! \param sector is the flash sector value.  Use DCSM_Sector type.
//!
//! This function takes in a valid sector value and returns the status of EXE
//! ONLY security protection for the sector.
//!
//! \return Returns DCSM_PROTECTED if the sector is EXE-ONLY protected,
//! DCSM_UNPROTECTED if the sector is not EXE-ONLY protected,
//! DCSM_INCORRECT_ZONE if sector does not belong to this zone.
//
//*****************************************************************************
extern DCSM_EXEOnlyStatus
DCSM_getZone1FlashEXEStatus(DCSM_Sector sector);

//*****************************************************************************
//
//! Returns the EXE-ONLY status of zone 1 for a RAM module
//!
//! \param module is the RAM module value. Valid values are type DCSM_RAMModule
//! C28x RAMs :
//! - \b DCSM_RAMLS0_SECA
//! - \b DCSM_RAMLS0_SECB
//! - \b DCSM_RAMLS0_SECC
//! - \b DCSM_RAMLS0_SECD
//! - \b DCSM_RAMLS1_SECA
//! - \b DCSM_RAMLS1_SECB
//! - \b DCSM_RAMLS1_SECC
//! - \b DCSM_RAMLS1_SECD
//!
//! This function takes in a valid module value and returns the status of EXE
//! ONLY security protection for that module.  DCSM_CLA is an invalid module
//! value.  There is no EXE-ONLY available for DCSM_CLA.
//!
//! \return Returns DCSM_PROTECTED if the module is EXE-ONLY protected,
//! DCSM_UNPROTECTED if the module is not EXE-ONLY protected,
//! DCSM_INCORRECT_ZONE if module does not belong to this zone.
//
//*****************************************************************************
extern DCSM_EXEOnlyStatus
DCSM_getZone1RAMEXEStatus(DCSM_RAMModule module);

//*****************************************************************************
//
//! Returns the EXE-ONLY status of zone 2 for a flash sector
//!
//! \param sector is the flash sector value. Use DCSM_Sector type.
//!
//! This function takes in a valid sector value and returns the status of EXE
//! ONLY security protection for the sector.
//!
//! \return Returns DCSM_PROTECTED if the sector is EXE-ONLY protected,
//! DCSM_UNPROTECTED if the sector is not EXE-ONLY protected,
//! DCSM_INCORRECT_ZONE if sector does not belong to this zone.
//
//*****************************************************************************
extern DCSM_EXEOnlyStatus
DCSM_getZone2FlashEXEStatus(DCSM_Sector sector);

//*****************************************************************************
//
//! Returns the EXE-ONLY status of zone 2 for a RAM module
//!
//! \param module is the RAM module value. Valid values are type DCSM_RAMModule
//! C28x RAMs :
//! - \b DCSM_RAMLS0_SECA
//! - \b DCSM_RAMLS0_SECB
//! - \b DCSM_RAMLS0_SECC
//! - \b DCSM_RAMLS0_SECD
//! - \b DCSM_RAMLS1_SECA
//! - \b DCSM_RAMLS1_SECB
//! - \b DCSM_RAMLS1_SECC
//! - \b DCSM_RAMLS1_SECD
//!
//! This function takes in a valid module value and returns the status of EXE
//! ONLY security protection for that module.  DCSM_CLA is an invalid module
//! value.  There is no EXE-ONLY available for DCSM_CLA.
//!
//! \return Returns DCSM_PROTECTED if the module is EXE-ONLY protected,
//! DCSM_UNPROTECTED if the module is not EXE-ONLY protected,
//! DCSM_INCORRECT_ZONE if module does not belong to this zone.
//
//*****************************************************************************
extern DCSM_EXEOnlyStatus
DCSM_getZone2RAMEXEStatus(DCSM_RAMModule module);

//*****************************************************************************
//
//! Claims the zone semaphore which allows access to the Flash Wrapper register
//! for that zone.
//!
//! \param zone is the zone which is trying to claim the semaphore which allows
//! access to the Flash Wrapper registers.
//!
//! \return Returns true for a successful semaphore capture, false if it was
//! unable to capture the semaphore.
//
//*****************************************************************************
extern bool
DCSM_claimZoneSemaphore(DCSM_SemaphoreZone zone);

//*****************************************************************************
//
//! Releases the zone semaphore.
//!
//! \return Returns true if it was successful in releasing the zone semaphore
//! and false if it was unsuccessful in releasing the zone semaphore.
//!
//! \note  If the calling function is not in the right zone to be able
//!        to access this register, it will return a false.
//
//*****************************************************************************
extern bool
DCSM_releaseZoneSemaphore(void);

//*****************************************************************************
//
//! Perform dummy reads on the 128-bit Zone 1 CSM password.
//!
//! This function reads the four password locations in the User OTP
//! needed to be done as part of the Password Match Flow before
//! writes to the CSMKEY registers.
//! This would need to be done before a DCSM_writeZone1CSM().
//!
//! \return None.
//!
//! \note This API to be called from CPU1.
//
//*****************************************************************************
extern void
DCSM_readZone1CSMPwd(void);

//*****************************************************************************
//
//! Perform dummy reads on the 128-bit Zone 2 CSM password.
//!
//! This function reads the four password locations in the User OTP
//! needed to be done as part of the Password Match Flow before
//! writes to the CSMKEY registers.
//! This would need to be done before a DCSM_writeZone2CSM().
//!
//! \return None.
//!
//! \note This API to be called from CPU1.
//
//*****************************************************************************
extern void
DCSM_readZone2CSMPwd(void);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  DCSM_H
