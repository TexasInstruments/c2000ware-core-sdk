#ifndef _PLL_H_
#define _PLL_H_

//#############################################################################
//
//! \file   f2802x/common/include/pll.h
//!
//! \brief  Contains public interface to various functions related
//!         to the phase-locked loop (PLL) object 
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
#include "cpu.h"

//!
//! \defgroup PLL

//!
//! \ingroup PLL
//@{

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//

//! \brief Defines the base address of the phase lock loop (PLL) registers
//!
#define  PLL_BASE_ADDR                   (0x00007011)

//! \brief Defines the location of the DIV bits in the PLLCR register
//!
#define  PLL_PLLCR_DIV_BITS              (15 << 0)

//! \brief Defines the location of the PLLLOCKS bits in the PLLSTS register
//!
#define PLL_PLLSTS_PLLLOCKS_BITS         (1 << 0)

//! \brief Defines the location of the PLLOFF bits in the PLLSTS register
//!
#define PLL_PLLSTS_PLLOFF_BITS           (1 << 2)

//! \brief Defines the location of the MCLKSTS bits in the PLLSTS register
//!
#define PLL_PLLSTS_MCLKSTS_BITS          (1 << 3)

//! \brief Defines the location of the MCLKCLR bits in the PLLSTS register
//!
#define PLL_PLLSTS_MCLKCLR_BITS          (1 << 4)

//! \brief Defines the location of the OSCOFF bits in the PLLSTS register
//!
#define PLL_PLLSTS_OSCOFF_BITS           (1 << 5)

//! \brief Defines the location of the MCLKOFF bits in the PLLSTS register
//!
#define PLL_PLLSTS_MCLKOFF_BITS          (1 << 6)

//! \brief Defines the location of the DIVSEL bits in the PLLSTS register
//!
#define PLL_PLLSTS_DIVSEL_BITS           (3 << 7)

//! \brief Defines the location of the NORMRDYE bits in the PLLSTS register
//!
#define PLL_PLLSTS_NORMRDYE_BITS         (1 << 15)

//
// Typedefs
//

//! \brief Enumeration to define the phase lock loop (PLL) clock frequency
//!
typedef enum
{
    PLL_Multiplier_1 = (1 << 0),      //!< Denotes a multiplier of 1 
    PLL_Multiplier_2 = (2 << 0),      //!< Denotes a multiplier of 2 
    PLL_Multiplier_3 = (3 << 0),      //!< Denotes a multiplier of 3 
    PLL_Multiplier_4 = (4 << 0),      //!< Denotes a multiplier of 4 
    PLL_Multiplier_5 = (5 << 0),      //!< Denotes a multiplier of 5 
    PLL_Multiplier_6 = (6 << 0),      //!< Denotes a multiplier of 6 
    PLL_Multiplier_7 = (7 << 0),      //!< Denotes a multiplier of 7 
    PLL_Multiplier_8 = (8 << 0),      //!< Denotes a multiplier of 8 
    PLL_Multiplier_9 = (9 << 0),      //!< Denotes a multiplier of 9 
    PLL_Multiplier_10 = (10 << 0),    //!< Denotes a multiplier of 10 
    PLL_Multiplier_11 = (11 << 0),    //!< Denotes a multiplier of 11 
    PLL_Multiplier_12 = (12 << 0)     //!< Denotes a multiplier of 12 
} PLL_Multiplier_e;

//! \brief Enumeration to define the phase lock loop (PLL) divide select
//!
typedef enum
{
    PLL_DivideSelect_ClkIn_by_4=(0 << 7),   //!< Denotes a divide select of CLKIN/4
    PLL_DivideSelect_ClkIn_by_2=(2 << 7),   //!< Denotes a divide select of CLKIN/2
    PLL_DivideSelect_ClkIn_by_1=(3 << 7)    //!< Denotes a divide select of CLKIN/1
} PLL_DivideSelect_e;

//! \brief Enumeration to define the phase lock loop (PLL) clock status
//!
typedef enum
{
    PLL_ClkStatus_Normal=(0 << 3),     //!< Denotes a normal clock
    PLL_ClkStatus_Missing=(1 << 3)     //!< Denotes a missing clock
} PLL_ClkStatus_e;

//! \brief Enumeration to define the phase lock loop (PLL) clock lock status
//!
typedef enum
{
    PLL_LockStatus_Locking=(0 << 0),   //!< Denotes that the system is locking to the clock
    PLL_LockStatus_Done=(1 << 0)       //!< Denotes that the system is locked to the clock
} PLL_LockStatus_e;

//! \brief Defines the phase lock loop (PLL) object
//!
typedef struct _PLL_Obj_
{
    volatile uint16_t   PLLSTS;       //!< PLL Status Register
    volatile uint16_t   rsvd_1;       //!< Reserved
    volatile uint16_t   PLLLOCKPRD;   //!< PLL Lock Period Register
    volatile uint16_t   rsvd_2[13];   //!< Reserved
    volatile uint16_t   PLLCR;        //!< PLL Control Register
} PLL_Obj;

//! \brief Defines the phase lock loop (PLL) handle
//!
typedef struct _PLL_Obj_ *PLL_Handle;

//
// Function Prototypes
//

//! \brief     Disables the phase lock loop (PLL)
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
void PLL_disable(PLL_Handle pllHandle);

//! \brief     Disables the clock detect logic
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
void PLL_disableClkDetect(PLL_Handle pllHandle);

//! \brief     Disables the NORMRDY signal
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
void PLL_disableNormRdy(PLL_Handle pllHandle);

//! \brief     Disables the oscillator
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
void PLL_disableOsc(PLL_Handle pllHandle);

//! \brief     Enables the phase lock loop (PLL)
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
void PLL_enable(PLL_Handle pllHandle);

//! \brief     Enables the clock detect logic
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
void PLL_enableClkDetect(PLL_Handle pllHandle);

//! \brief     Enables the NORMRDY signal
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
void PLL_enableNormRdy(PLL_Handle pllHandle);

//! \brief     Enables the oscillator
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
void PLL_enableOsc(PLL_Handle pllHandle);

//! \brief     Gets the phase lock loop (PLL) clock frequency
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
//! \return    The clock frequency
PLL_Multiplier_e PLL_getMultiplier(PLL_Handle pllHandle);

//! \brief     Gets the phase lock loop (PLL) clock status
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
//! \return    The clock status
PLL_ClkStatus_e PLL_getClkStatus(PLL_Handle pllHandle);

//! \brief     Gets the phase lock loop (PLL) divide select value
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
//! \return    The divide select value
PLL_DivideSelect_e PLL_getDivider(PLL_Handle pllHandle);

//! \brief     Gets the phase lock loop (PLL) lock status
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
//! \return    The lock status
PLL_LockStatus_e PLL_getLockStatus(PLL_Handle pllHandle);

//! \brief     Initializes the phase lock loop (PLL) object handle
//! \param[in] pMemory     A pointer to the base address of the PLL registers
//! \param[in] numBytes    The number of bytes allocated for the PLL object, 
//! bytes
//! \return    The phase lock loop (PLL) object handle
PLL_Handle PLL_init(void *pMemory, const size_t numBytes);

//! \brief     Resets the phase lock loop (PLL) clock detect logic
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
void PLL_resetClkDetect(PLL_Handle pllHandle);

//! \brief     Sets the phase lock loop (PLL) clock frequency
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
//! \param[in] freq       The clock frequency
void PLL_setMultiplier(PLL_Handle pllHandle, const PLL_Multiplier_e freq);

//! \brief     Sets the phase lock loop (PLL) divide select value
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
//! \param[in] divSelect  The divide select value
void PLL_setDivider(PLL_Handle pllHandle, const PLL_DivideSelect_e divSelect);

//! \brief     Sets the phase lock loop (PLL) divider and multiplier
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
//! \param[in] clkMult    The clock multiplier value
//! \param[in] divSelect  The divide select value
void PLL_setup(PLL_Handle pllHandle, const PLL_Multiplier_e clkMult, 
               const PLL_DivideSelect_e divSelect);

//! \brief     Sets the phase lock loop (PLL) lock time
//! \param[in] pllHandle  The phase lock loop (PLL) object handle
//! \param[in] lockPeriod The lock period, cycles
void PLL_setLockPeriod(PLL_Handle pllHandle, const uint16_t lockPeriod);

#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

#endif  // end of _PLL_H_ definition

//
// End of File
//

