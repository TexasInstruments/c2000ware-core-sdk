//###########################################################################
//
// FILE:   cmmpu.h
//
// TITLE:  Driver for the uDMA & EMAC memory protection unit (MPU).
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

#ifndef CMMPU_H
#define CMMPU_H

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
//! \addtogroup cmmpu_api CMMPU
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "debug.h"
#include "interrupt.h"
#include "inc/hw_cmmpu.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

//*****************************************************************************
//
// Defines for the API.
//
//*****************************************************************************
//*****************************************************************************
//
// Key for accessing Access Violation related registers.
//
//*****************************************************************************
#define CMMPU_ACC_VIO_KEY          0xA5A50000U //!< Key for ACC VIO Registers

//*****************************************************************************
//
// Flags for setting/clearing/returning the access violation interrupt flag
// status, to be passed to CMMPU_setAccessViolationFlags() &
// CMMPU_setAccessViolationFlags() as flags parameter & returned by
// CMMPU_getAccessViolationFlags().
//
//*****************************************************************************
#define CMMPU_ACC_VIO_FLAGS_READ   CMMPU_ACC_VIO_FLAGS_RD //!< Read Violation
#define CMMPU_ACC_VIO_FLAGS_WRITE  CMMPU_ACC_VIO_FLAGS_WR //!< Write Violation

//*****************************************************************************
//
// Values that can be passed to CMMPU_setRegionAttributes() and
// CMMPU_getRegionAttributes() as regionNum parameter.
//
//*****************************************************************************
#define CMMPU_RGN_0                0x0U //!< Select uDMA/EMAC MPU Region 0
#define CMMPU_RGN_1                0x1U //!< Select uDMA/EMAC MPU Region 1
#define CMMPU_RGN_2                0x2U //!< Select uDMA/EMAC MPU Region 2
#define CMMPU_RGN_3                0x3U //!< Select uDMA/EMAC MPU Region 3
#define CMMPU_RGN_4                0x4U //!< Select uDMA/EMAC MPU Region 4
#define CMMPU_RGN_5                0x5U //!< Select uDMA/EMAC MPU Region 5
#define CMMPU_RGN_6                0x6U //!< Select uDMA/EMAC MPU Region 6
#define CMMPU_RGN_7                0x7U //!< Select uDMA/EMAC MPU Region 7

//*****************************************************************************
//
// Flags to enable or disable a region, to be passed to
// CMMPU_setRegionAttributes().
//
//*****************************************************************************
#define CMMPU_RGN_ENABLE           0x1U //!< Enable MPU Region
#define CMMPU_RGN_DISABLE          0x0U //!< Disable MPU Region

//*****************************************************************************
//
// Flags for the access permissions to be passed to CMMPU_setRegionAttributes().
//
//*****************************************************************************
#define CMMPU_RGN_PERM_READ_ONLY   0x00U //!< Read Only Access
#define CMMPU_RGN_PERM_NO_ACCESS   0x20U //!< No Access(R/W)
#define CMMPU_RGN_PERM_FULL_ACCESS 0x10U //!< Full Access(R/W)

//*****************************************************************************
//
// Flags for the region size to be passed to CMMPU_setRegionAttributes().
//
//*****************************************************************************
#define CMMPU_RGN_SIZE_1K          (0x0U  << 8U) //!< Region Size is 1K-bytes
#define CMMPU_RGN_SIZE_2K          (0x1U  << 8U) //!< Region Size is 2K-bytes
#define CMMPU_RGN_SIZE_4K          (0x2U  << 8U) //!< Region Size is 4K-bytes
#define CMMPU_RGN_SIZE_8K          (0x3U  << 8U) //!< Region Size is 8K-bytes
#define CMMPU_RGN_SIZE_16K         (0x4U  << 8U) //!< Region Size is 16K-bytes
#define CMMPU_RGN_SIZE_32K         (0x5U  << 8U) //!< Region Size is 32K-bytes
#define CMMPU_RGN_SIZE_64K         (0x6U  << 8U) //!< Region Size is 64K-bytes
#define CMMPU_RGN_SIZE_128K        (0x7U  << 8U) //!< Region Size is 128K-bytes
#define CMMPU_RGN_SIZE_256K        (0x8U  << 8U) //!< Region Size is 256K-bytes
#define CMMPU_RGN_SIZE_512K        (0x9U  << 8U) //!< Region Size is 512K-bytes
#define CMMPU_RGN_SIZE_1M          (0xAU  << 8U) //!< Region Size is 1M-bytes
#define CMMPU_RGN_SIZE_2M          (0xBU  << 8U) //!< Region Size is 2M-bytes
#define CMMPU_RGN_SIZE_4M          (0xCU  << 8U) //!< Region Size is 4M-bytes
#define CMMPU_RGN_SIZE_8M          (0xDU  << 8U) //!< Region Size is 8M-bytes
#define CMMPU_RGN_SIZE_16M         (0xEU  << 8U) //!< Region Size is 16M-bytes
#define CMMPU_RGN_SIZE_32M         (0xFU  << 8U) //!< Region Size is 32M-bytes
#define CMMPU_RGN_SIZE_64M         (0x10U << 8U) //!< Region Size is 64M-bytes
#define CMMPU_RGN_SIZE_128M        (0x11U << 8U) //!< Region Size is 128M-bytes
#define CMMPU_RGN_SIZE_256M        (0x12U << 8U) //!< Region Size is 256M-bytes
#define CMMPU_RGN_SIZE_512M        (0x13U << 8U) //!< Region Size is 512M-bytes
#define CMMPU_RGN_SIZE_1G          (0x14U << 8U) //!< Region Size is 1G-bytes
#define CMMPU_RGN_SIZE_2G          (0x15U << 8U) //!< Region Size is 2G-bytes
#define CMMPU_RGN_SIZE_4G          (0x16U << 8U) //!< Region Size is 4G-bytes

//*****************************************************************************
//
// Flags for the sub-region to be passed to CMMPU_setRegionAttributes().
//
//*****************************************************************************
#define CMMPU_SUB_RGN_DISABLE_0    0x00010000U //!< Disable sub-region 0
#define CMMPU_SUB_RGN_DISABLE_1    0x00020000U //!< Disable sub-region 1
#define CMMPU_SUB_RGN_DISABLE_2    0x00040000U //!< Disable sub-region 2
#define CMMPU_SUB_RGN_DISABLE_3    0x00080000U //!< Disable sub-region 3
#define CMMPU_SUB_RGN_DISABLE_4    0x00100000U //!< Disable sub-region 4
#define CMMPU_SUB_RGN_DISABLE_5    0x00200000U //!< Disable sub-region 5
#define CMMPU_SUB_RGN_DISABLE_6    0x00400000U //!< Disable sub-region 6
#define CMMPU_SUB_RGN_DISABLE_7    0x00800000U //!< Disable sub-region 7

//*****************************************************************************
//
// Mask for MPU region attributes to be used by CMMPU_setRegionAttributes().
//
//*****************************************************************************

#define CMMPU_RGN_CONFIG_M    ((uint32_t)CMMPU_REGION0_CONFIG_ENABLE       |   \
                               (uint32_t)CMMPU_REGION0_CONFIG_PROT_TYPE_M  |   \
                               (uint32_t)CMMPU_REGION0_CONFIG_SIZE_M       |   \
                               (uint32_t)0xFF0000U)

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks the MPU module base address.
//!
//! \param base is the base address of the MPU instance used.
//!
//! This function determines if MPU module base address is valid. The paramater
//! \b base can take following values: DMPU_BASE, or EMPU_BASE.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
CMMPU_isBaseValid(uint32_t base)
{
    return((base == DMPU_BASE) || (base == EMPU_BASE));
}
#endif

//*****************************************************************************
//
//! Enables and configures the MPU for use.
//!
//! \param base is the base address of the MPU instance used.
//!
//! This function enables either the DMA or EMAC memory protection unit.
//! Prior to enabling the MPU, at least one region must be set by calling
//! CMMPU_setRegionAttributes(). Once the MPU is enabled, access violation
//! interrupts are generated if enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMMPU_enable(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMMPU_isBaseValid(base));

    //
    // Enable the MPU.
    //
    HWREG(base + CMMPU_O_MPU_CONTROL_REG) |= CMMPU_MPU_CONTROL_REG_ENABLE;
}

//*****************************************************************************
//
//! Disables the MPU for use.
//!
//! \param base is the base address of the MPU instance used.
//!
//! This function disables either the DMA or EMAC memory protection unit.
//! When the MPU is disabled, the default memory map is used and access
//! violation interrupts are not generated.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMMPU_disable(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMMPU_isBaseValid(base));

    //
    // Turn off the MPU enable bit.
    //
    HWREG(base + CMMPU_O_MPU_CONTROL_REG) &= ~CMMPU_MPU_CONTROL_REG_ENABLE;
}

//*****************************************************************************
//
//! Enables the MPU RD/WR Access Violation Interrupts.
//!
//! \param base is the base address of the MPU instance used.
//!
//! This function enables either the DMA or EMAC MPU read/write access
//! violation interrupts.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMMPU_enableAccessViolationInterrupt(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMMPU_isBaseValid(base));

    //
    // Enable the interrupts.
    //
    HWREG(base + CMMPU_O_ACC_VIO_INTEN) = (CMMPU_ACC_VIO_INTEN_INTEN |
                                           CMMPU_ACC_VIO_KEY);
}

//*****************************************************************************
//
//! Disables the MPU RD/WR Access Violation Interrupts.
//!
//! \param base is the base address of the MPU instance used.
//!
//! This function enables either the DMA or EMAC MPU read/write access
//! violation interrupts.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMMPU_disableAccessViolationInterrupt(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMMPU_isBaseValid(base));

    //
    // Disable the interrupts.
    //
    HWREG(base + CMMPU_O_ACC_VIO_INTEN) = (~CMMPU_ACC_VIO_INTEN_INTEN |
                                            CMMPU_ACC_VIO_KEY);
}

//*****************************************************************************
//
//! Gets the status of MPU RD/WR Access Violation Interrupts.
//!
//! \param base is the base address of the MPU instance used.
//!
//! This function return the status of either the DMA or EMAC MPU read/write
//! access violation interrupts.
//!
//! \return Returns the access violation interrupt status. It can return
//! following values: CMMPU_ACC_VIO_FLAGS_READ, CMMPU_ACC_VIO_FLAGS_WRITE
//
//*****************************************************************************
static inline uint32_t
CMMPU_getAccessViolationFlags(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMMPU_isBaseValid(base));

    //
    // Return the access violation interrupts flag status.
    //
    return(HWREG(base + CMMPU_O_ACC_VIO_FLAGS));
}

//*****************************************************************************
//
//! Sets the MPU RD/WR Access Violation Interrupts.
//!
//! \param base is the base address of the MPU instance used.
//! \param flags is the flag for rd/wr violation.
//!
//! This function sets either the DMA or EMAC MPU read/write access
//! violation interrupts. The parameter \b flags can take following values:
//! CMMPU_ACC_VIO_FLAGS_READ, or CMMPU_ACC_VIO_FLAGS_WRITE.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMMPU_setAccessViolationFlags(uint32_t base, uint32_t flags)
{
    //
    // Check the arguments.
    //
    ASSERT(CMMPU_isBaseValid(base));

    //
    // Return the access violation interrupts flag status.
    //
    HWREG(base + CMMPU_O_ACC_VIO_FLAGS_SET) = (flags | CMMPU_ACC_VIO_KEY);
}

//*****************************************************************************
//
//! Clears the MPU RD/WR Access Violation Interrupt Status.
//!
//! \param base is the base address of the MPU instance used.
//! \param flags is the flag for rd/wr violation.
//!
//! This function clears either the DMA or EMAC MPU read/write access
//! violation interrupt status.The parameter \e flags can take following values:
//! CMMPU_ACC_VIO_FLAGS_READ, or CMMPU_ACC_VIO_FLAGS_WRITE.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMMPU_clearAccessViolationFlags(uint32_t base, uint32_t flags)
{
    //
    // Check the arguments.
    //
    ASSERT(CMMPU_isBaseValid(base));

    //
    // Clear the access violation interrupts flag status.
    //
    HWREG(base + CMMPU_O_ACC_VIO_FLAGS_CLR) = (flags | CMMPU_ACC_VIO_KEY);
}

//*****************************************************************************
//
//! Gets the MPU RD/WR Access Violation Address.
//!
//! \param base is the base address of the MPU instance used.
//!
//! This function enables either the DMA or EMAC MPU read/write access
//! violation interrupts.
//!
//! \return Returns the MPU RD/WR access violation address.
//
//*****************************************************************************
static inline uint32_t
CMMPU_getAccessViolationAddr(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CMMPU_isBaseValid(base));

    //
    // Return the access violation address.
    //
    return(HWREG(base + CMMPU_O_ACC_VIO_ADDR_REG));
}

//*****************************************************************************
//
//! Sets up the access rules for a specific region.
//!
//! \param base is the base address of the MPU instance used.
//! \param regionNum is the region number to set up.
//! \param baseAddr is the base address of the region.  It must be aligned
//! according to the size of the region specified in attrFlags.
//! \param attrFlags is a set of flags to define the attributes of the region.
//!
//! This function sets up the protection rules for a region.  The region has
//! a base address and a set of attributes including the size.
//!
//! The region number parameter, \e regionNum specifies region number to setup.
//! Valid values for \e regionNum paramter are:
//! - \b CMMPU_RGN_0
//! - \b CMMPU_RGN_1
//! - \b CMMPU_RGN_2
//! - \b CMMPU_RGN_3
//! - \b CMMPU_RGN_4
//! - \b CMMPU_RGN_5
//! - \b CMMPU_RGN_6
//! - \b CMMPU_RGN_7
//!
//! The base address parameter, \e baseAddr, must be aligned according to the
//! size, and the size must be a power of 2.
//!
//! The \e attrFlags parameter is the logical OR of all of the attributes
//! of the region.  It is a combination of choices for region size, read/write
//! permissions, disabled sub-regions, and a flag to determine if the region is
//! enabled.
//!
//! The size flag determines the size of a region and must be one of the
//! following:
//! - \b CMMPU_RGN_SIZE_1K
//! - \b CMMPU_RGN_SIZE_2K
//! - \b CMMPU_RGN_SIZE_4K
//! - \b CMMPU_RGN_SIZE_8K
//! - \b CMMPU_RGN_SIZE_16K
//! - \b CMMPU_RGN_SIZE_32K
//! - \b CMMPU_RGN_SIZE_64K
//! - \b CMMPU_RGN_SIZE_128K
//! - \b CMMPU_RGN_SIZE_256K
//! - \b CMMPU_RGN_SIZE_512K
//! - \b CMMPU_RGN_SIZE_1M
//! - \b CMMPU_RGN_SIZE_2M
//! - \b CMMPU_RGN_SIZE_4M
//! - \b CMMPU_RGN_SIZE_8M
//! - \b CMMPU_RGN_SIZE_16M
//! - \b CMMPU_RGN_SIZE_32M
//! - \b CMMPU_RGN_SIZE_64M
//! - \b CMMPU_RGN_SIZE_128M
//! - \b CMMPU_RGN_SIZE_256M
//! - \b CMMPU_RGN_SIZE_512M
//! - \b CMMPU_RGN_SIZE_1G
//! - \b CMMPU_RGN_SIZE_2G
//! - \b CMMPU_RGN_SIZE_4G
//!
//! The read/write access permission flag must be one of the following:
//! - \b CMMPU_RGN_PERM_READ_ONLY- read only permission to MPU region
//! - \b CMMPU_RGN_PERM_NO_ACCESS- disables read/write permission to MPU region
//! - \b CMMPU_RGN_PERM_FULL_ACCESS- read/write permission to MPU region
//!
//! The region is automatically divided into 8 equally-sized sub-regions by
//! the MPU.  Sub-regions can only be used in regions of size 256 bytes
//! or larger.  Any of these 8 sub-regions can be disabled, allowing for
//! creation of "holes" in a region which can be left open, or overlaid
//! by another region with different attributes.  Any of the 8 sub-regions
//! can be disabled with a logical OR of any of the following flags:
//! - \b CMMPU_SUB_RGN_DISABLE_0
//! - \b CMMPU_SUB_RGN_DISABLE_1
//! - \b CMMPU_SUB_RGN_DISABLE_2
//! - \b CMMPU_SUB_RGN_DISABLE_3
//! - \b CMMPU_SUB_RGN_DISABLE_4
//! - \b CMMPU_SUB_RGN_DISABLE_5
//! - \b CMMPU_SUB_RGN_DISABLE_6
//! - \b CMMPU_SUB_RGN_DISABLE_7
//!
//! Finally, the region can be initially enabled or disabled with one of
//! the following flags:
//! - \b CMMPU_RGN_ENABLE
//! - \b CMMPU_RGN_DISABLE
//!
//! As an example, to set a region with the following attributes: size of
//! 32 KB, read-only access, one sub-region disabled, and initially enabled,
//! the \e attrFlags parameter would have the following value:
//! <code>
//! (CMMPU_RGN_SIZE_32K      | CMMPU_RGN_PERM_READ_ONLY |
//!  CMMPU_SUB_RGN_DISABLE_2 | CMMPU_RGN_ENABLE)
//! </code>
//!
//! \note This function writes to multiple registers and is not protected
//! from interrupts.  It is possible that an interrupt which accesses a
//! region may occur while that region is in the process of being changed.
//! The safest way to handle this is to disable a region before changing it.
//! Refer to the discussion of this in the API Detailed Description section.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMMPU_setRegionAttributes(uint32_t base, uint32_t regionNum, uint32_t baseAddr,
                          uint32_t attrFlags)
{
    uint32_t temp;

    //
    // Check the arguments.
    //
    ASSERT(CMMPU_isBaseValid(base));
    ASSERT(regionNum < 8U);

    //
    // Checking whether the region base address is aligned according to the
    // desired region size.
    //
    ASSERT(baseAddr == (baseAddr & (~(uint32_t)0U << (((attrFlags &
                        CMMPU_REGION0_CONFIG_SIZE_M) >>
                        CMMPU_REGION0_CONFIG_SIZE_S) + 1U))));

    //
    // Program the region start address.
    //
    HWREG(base + CMMPU_O_REGION0_STARTADDRESSS + (regionNum * 8U)) = baseAddr;

    //
    // Program the region attributes.
    //
    temp = CMMPU_RGN_CONFIG_M;
    HWREG(base + CMMPU_O_REGION0_CONFIG + (regionNum * 8U)) =
                 (HWREG(base + CMMPU_O_REGION0_CONFIG + (regionNum * 8U)) &
                  ~(temp)) | attrFlags;
}

//*****************************************************************************
//
//! Gets the current settings for a specific region.
//!
//! \param base is the base address of the MPU instance used.
//! \param regionNum is the region number to get.
//! \param baseAddr points to storage for the base address of the region.
//! \param attrFlags points to the attribute flags for the region.
//!
//! This function retrieves the configuration of a specific region.  The
//! meanings and format of the parameters is the same as that of the
//! CMMPU_setRegionAttributes() function.
//!
//! This function can be used to save the configuration of a region for later
//! use with the CMMPU_setRegionAttributes() function. The region's enable state
//! is preserved in the attributes that are saved.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMMPU_getRegionAttributes(uint32_t base, uint32_t regionNum, uint32_t *baseAddr,
                        uint32_t *attrFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(CMMPU_isBaseValid(base));
    ASSERT(regionNum < 8U);
    ASSERT(baseAddr != 0x0U);
    ASSERT(attrFlags != 0x0U);

    //
    // Read and store the start address for the region.
    //
    *baseAddr = HWREG(base + CMMPU_O_REGION0_STARTADDRESSS + (regionNum * 8U));

    //
    // Read and store the region attributes.
    //
    *attrFlags = HWREG(base + CMMPU_O_REGION0_CONFIG + (regionNum * 8U));
}

//*****************************************************************************
//
//! Enables a specific region.
//!
//! \param base is the base address of the MPU instance used.
//! \param regionNum is the region number to enable.
//!
//! This function is used to enable a memory protection region.  The region
//! should already be configured with the CMMPU_setRegionAttributes() function.
//! Once enabled, the memory protection rules of the region are applied and
//! access violations cause a bus fault.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMMPU_enableRegion(uint32_t base, uint32_t regionNum)
{
    //
    // Check the arguments.
    //
    ASSERT(CMMPU_isBaseValid(base));
    ASSERT(regionNum < 8U);

    //
    // Enable the region.
    //
    HWREG(base + CMMPU_O_REGION0_CONFIG + (regionNum * 8U)) |=
                                                   CMMPU_REGION0_CONFIG_ENABLE;
}

//*****************************************************************************
//
//! Disables a specific region.
//!
//! \param base is the base address of the MPU instance used.
//! \param regionNum is the region number to disable.
//!
//! This function is used to disable a previously enabled memory protection
//! region.  The region remains configured if it is not overwritten with
//! another call to CMMPU_setRegionAttributes(), and can be enabled again by
//! calling CMMPU_enableRegion().
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMMPU_disableRegion(uint32_t base, uint32_t regionNum)
{
    //
    // Check the arguments.
    //
    ASSERT(CMMPU_isBaseValid(base));
    ASSERT(regionNum < 8U);

    //
    // Modify the enable bit in the region attributes.
    //
    HWREG(base + CMMPU_O_REGION0_CONFIG + (regionNum * 8U)) &=
                                                  ~CMMPU_REGION0_CONFIG_ENABLE;
}

//*****************************************************************************
//
//! Registers an interrupt handler for the memory management fault.
//!
//! \param intNum is the interrupt number to be registered.
//! \param fnHandler is a pointer to the function to be called when the
//! memory management fault occurs.
//!
//! This function sets and enables the handler to be called when the MPU
//! generates a bus fault due to a protection region access violation.
//!
//! \sa Interrupt_registerHandler() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMMPU_registerHandler(uint32_t intNum, void (*fnHandler)(void))
{
    //
    // Check the arguments.
    //
    ASSERT(fnHandler);

    //
    // Register the interrupt handler.
    //
    Interrupt_registerHandler(intNum, fnHandler);

    //
    // Enable the memory management fault.
    //
    Interrupt_enable(intNum);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for the memory management fault.
//!
//! \param intNum is the interrupt number to be unregistered.
//!
//! This function disables and clears the handler to be called when a
//! memory management fault occurs.
//!
//! \sa Interrupt_registerHandler() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
CMMPU_unregisterHandler(uint32_t intNum)
{
    //
    // Disable the interrupt.
    //
    Interrupt_disable(intNum);

    //
    // Unregister the interrupt handler.
    //
    Interrupt_unregisterHandler(intNum);
}

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

#endif // CMMPU_H
