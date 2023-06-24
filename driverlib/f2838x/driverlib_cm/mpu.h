//###########################################################################
//
// FILE:   mpu.h
//
// TITLE:  Driver for the memory protection unit (MPU).
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

#ifndef MPU_H
#define MPU_H

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
//! \addtogroup mpu_api MPU
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "debug.h"
#include "interrupt.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"

//*****************************************************************************
//
// Defines for the API.
//
//*****************************************************************************
//*****************************************************************************
//
// Values that can be passed to MPU_enable() as config parameter.
//
//*****************************************************************************
#define MPU_CONFIG_PRIV_DEFAULT     0x4U //!< Enable default memory map as bg
                                         //!< region for priv sw access.
#define MPU_CONFIG_HARDFLT_NMI      0x2U //!< MPU is enabled during hard fault,
                                         //!< NMI and FAULTMASK handlers.
#define MPU_CONFIG_NONE             0x0U //!< None of the above configurations.

//*****************************************************************************
//
// Values that can be passed to MPU_setRegionAttributes() and
// MPU_getRegionAttributes() as regionNum parameter.
//
//*****************************************************************************
#define MPU_RGN_0                0x0U
#define MPU_RGN_1                0x1U
#define MPU_RGN_2                0x2U
#define MPU_RGN_3                0x3U
#define MPU_RGN_4                0x4U
#define MPU_RGN_5                0x5U
#define MPU_RGN_6                0x6U
#define MPU_RGN_7                0x7U

//*****************************************************************************
//
// Flags for the region size to be passed to MPU_setRegionAttributes().
//
//*****************************************************************************
#define MPU_RGN_SIZE_32B           (4U << 1U)  //!< Region Size is 32-bytes
#define MPU_RGN_SIZE_64B           (5U << 1U)  //!< Region Size is 64-bytes
#define MPU_RGN_SIZE_128B          (6U << 1U)  //!< Region Size is 128-bytes
#define MPU_RGN_SIZE_256B          (7U << 1U)  //!< Region Size is 256-bytes
#define MPU_RGN_SIZE_512B          (8U << 1U)  //!< Region Size is 512-bytes
#define MPU_RGN_SIZE_1K            (9U << 1U)  //!< Region Size is 1K-bytes
#define MPU_RGN_SIZE_2K            (10U << 1U) //!< Region Size is 2K-bytes
#define MPU_RGN_SIZE_4K            (11U << 1U) //!< Region Size is 4K-bytes
#define MPU_RGN_SIZE_8K            (12U << 1U) //!< Region Size is 8K-bytes
#define MPU_RGN_SIZE_16K           (13U << 1U) //!< Region Size is 16K-bytes
#define MPU_RGN_SIZE_32K           (14U << 1U) //!< Region Size is 32K-bytes
#define MPU_RGN_SIZE_64K           (15U << 1U) //!< Region Size is 64K-bytes
#define MPU_RGN_SIZE_128K          (16U << 1U) //!< Region Size is 128K-bytes
#define MPU_RGN_SIZE_256K          (17U << 1U) //!< Region Size is 256K-bytes
#define MPU_RGN_SIZE_512K          (18U << 1U) //!< Region Size is 512K-bytes
#define MPU_RGN_SIZE_1M            (19U << 1U) //!< Region Size is 1M-bytes
#define MPU_RGN_SIZE_2M            (20U << 1U) //!< Region Size is 2M-bytes
#define MPU_RGN_SIZE_4M            (21U << 1U) //!< Region Size is 4M-bytes
#define MPU_RGN_SIZE_8M            (22U << 1U) //!< Region Size is 8M-bytes
#define MPU_RGN_SIZE_16M           (23U << 1U) //!< Region Size is 16M-bytes
#define MPU_RGN_SIZE_32M           (24U << 1U) //!< Region Size is 32M-bytes
#define MPU_RGN_SIZE_64M           (25U << 1U) //!< Region Size is 64M-bytes
#define MPU_RGN_SIZE_128M          (26U << 1U) //!< Region Size is 128M-bytes
#define MPU_RGN_SIZE_256M          (27U << 1U) //!< Region Size is 256M-bytes
#define MPU_RGN_SIZE_512M          (28U << 1U) //!< Region Size is 512M-bytes
#define MPU_RGN_SIZE_1G            (29U << 1U) //!< Region Size is 1G-bytes
#define MPU_RGN_SIZE_2G            (30U << 1U) //!< Region Size is 2G-bytes
#define MPU_RGN_SIZE_4G            (31U << 1U) //!< Region Size is 4G-bytes

//*****************************************************************************
//
// Flags for the permissions to be passed to MPU_setRegionAttributes().
//
//*****************************************************************************
#define MPU_RGN_PERM_EXEC           0x00000000U //!< Inst. fetches are enabled
#define MPU_RGN_PERM_NOEXEC         0x10000000U //!< Inst. fetches are disabled
#define MPU_RGN_PERM_PRV_NO_USR_NO  0x00000000U //!< No access to privileged &
                                                //!< unprivileged access
#define MPU_RGN_PERM_PRV_RW_USR_NO  0x01000000U //!< R/W to privileged sw, no
                                                //!< access to unprivileged sw
#define MPU_RGN_PERM_PRV_RW_USR_RO  0x02000000U //!< R/W access to priv sw, no
                                                //!< access to unpriv sw
#define MPU_RGN_PERM_PRV_RW_USR_RW  0x03000000U //!< R/W access to priv sw, R/W
                                                //!< access to unpriv sw
#define MPU_RGN_PERM_PRV_RO_USR_NO  0x05000000U //!< RO access to priv sw, no
                                                //!< access to unpriv sw
#define MPU_RGN_PERM_PRV_RO_USR_RO  0x06000000U //!< RO access to priv sw, RO
                                                //!< access to unpriv sw

//*****************************************************************************
//
// Flags for the sub-region to be passed to MPU_setRegionAttributes().
//
//*****************************************************************************
#define MPU_SUB_RGN_DISABLE_0       0x00000100U //!< Disable sub-region 0
#define MPU_SUB_RGN_DISABLE_1       0x00000200U //!< Disable sub-region 1
#define MPU_SUB_RGN_DISABLE_2       0x00000400U //!< Disable sub-region 2
#define MPU_SUB_RGN_DISABLE_3       0x00000800U //!< Disable sub-region 3
#define MPU_SUB_RGN_DISABLE_4       0x00001000U //!< Disable sub-region 4
#define MPU_SUB_RGN_DISABLE_5       0x00002000U //!< Disable sub-region 5
#define MPU_SUB_RGN_DISABLE_6       0x00004000U //!< Disable sub-region 6
#define MPU_SUB_RGN_DISABLE_7       0x00008000U //!< Disable sub-region 7

//*****************************************************************************
//
// Flags to enable or disable a region, to be passed to
// MPU_setRegionAttributes().
//
//*****************************************************************************
#define MPU_RGN_ENABLE              1U //!< Enable MPU Region
#define MPU_RGN_DISABLE             0U //!< Disable MPU Region

//*****************************************************************************
//
// Mask for MPU region attributes to be used by MPU_setRegionAttributes().
//
//*****************************************************************************

#define MPU_RGN_CONFIG_M    ((uint32_t)NVIC_MPU_RASR_ENABLE |                  \
                             (uint32_t)NVIC_MPU_RASR_SIZE_M |                  \
                             (uint32_t)NVIC_MPU_RASR_SRD_M  |                  \
                             (uint32_t)NVIC_MPU_RASR_B      |                  \
                             (uint32_t)NVIC_MPU_RASR_C      |                  \
                             (uint32_t)NVIC_MPU_RASR_S      |                  \
                             (uint32_t)NVIC_MPU_RASR_TEX_M  |                  \
                             (uint32_t)NVIC_MPU_RASR_AP_M   |                  \
                             (uint32_t)NVIC_MPU_RASR_XN)

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
//*****************************************************************************
//
//! Enables and configures the MPU for use.
//!
//! \param config is the logical OR of the possible configurations.
//!
//! This function enables the Cortex-M memory protection unit.  It also
//! configures the default behavior when in privileged mode and while handling
//! a hard fault or NMI.  Prior to enabling the MPU, at least one region must
//! be set by calling MPU_setRegionAttributes() or else by enabling the default
//! region for privileged mode by passing the \b MPU_CONFIG_PRIV_DEFAULT flag
//! to MPU_enable().  Once the MPU is enabled, a memory management fault is
//! generated for memory access violations.
//!
//! The \e config parameter should be the logical OR of any of the
//! following:
//! - \b MPU_CONFIG_PRIV_DEFAULT enables the default memory map when in
//! privileged mode and when no other regions are defined.  If this option
//! is not enabled, then there must be at least one valid region already
//! defined when the MPU is enabled.
//! - \b MPU_CONFIG_HARDFLT_NMI enables the MPU while in a hard fault or NMI
//! exception handler.  If this option is not enabled, then the MPU is
//! disabled while in one of these exception handlers and the default
//! memory map is applied.
//! - \b MPU_CONFIG_NONE chooses none of the above options.  In this case,
//! no default memory map is provided in privileged mode, and the MPU is not
//! enabled in the fault handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MPU_enable(uint32_t config)
{
    //
    // Check the arguments.
    //
    ASSERT((config & ~(MPU_CONFIG_PRIV_DEFAULT |
                               MPU_CONFIG_HARDFLT_NMI)) == 0U);

    //
    // Set the MPU control bits according to the flags passed by the user,
    // and also set the enable bit.
    //
    HWREG(NVIC_BASE + NVIC_O_MPU_CTRL) |= (config | NVIC_MPU_CTRL_ENABLE);
}

//*****************************************************************************
//
//! Disables the MPU for use.
//!
//! \param None
//!
//! This function disables the Cortex-M memory protection unit.  When the
//! MPU is disabled, the default memory map is used and memory management
//! faults are not generated.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MPU_disable(void)
{
    //
    // Turn off the MPU enable bit.
    //
    HWREG(NVIC_BASE + NVIC_O_MPU_CTRL) &= ~NVIC_MPU_CTRL_ENABLE;
}

//*****************************************************************************
//
//! Gets the count of regions supported by the MPU.
//!
//! \param None
//!
//! This function is used to get the total number of regions that are supported
//! by the MPU, including regions that are already programmed.
//!
//! \return The number of memory protection regions that are available
//! for programming using MPU_setRegionAttributes().
//
//*****************************************************************************
static inline uint32_t
MPU_getRegionCount(void)
{
    //
    // Read the DREGION field of the MPU type register and mask off
    // the bits of interest to get the count of regions.
    //
    return((HWREG(NVIC_BASE + NVIC_O_MPU_TYPE) & NVIC_MPU_TYPE_DREGION_M) >>
           NVIC_MPU_TYPE_DREGION_S);
}

//*****************************************************************************
//
//! Enables a specific region.
//!
//! \param regionNum is the region number to enable.
//!
//! This function is used to enable a memory protection region.  The region
//! should already be configured with the MPU_setRegionAttributes() function.
//! Once enabled, the memory protection rules of the region are applied and
//! access violations cause a memory management fault.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MPU_enableRegion(uint32_t regionNum)
{
    //
    // Check the arguments.
    //
    ASSERT(regionNum < 8U);

    //
    // Select the region to modify.
    //
    HWREG(NVIC_BASE + NVIC_O_MPU_RNR) = (HWREG(NVIC_BASE + NVIC_O_MPU_RNR) &
                                         ~NVIC_MPU_RNR_REGION_M) | regionNum;

    //
    // Modify the enable bit in the region attributes.
    //
    HWREG(NVIC_BASE + NVIC_O_MPU_RASR) |= NVIC_MPU_RASR_ENABLE;
}

//*****************************************************************************
//
//! Disables a specific region.
//!
//! \param regionNum is the region number to disable.
//!
//! This function is used to disable a previously enabled memory protection
//! region.  The region remains configured if it is not overwritten with
//! another call to MPU_setRegionAttributes(), and can be enabled again by
//! calling MPU_enableRegion().
//!
//! \return None.
//
//*****************************************************************************
static inline void
MPU_disableRegion(uint32_t regionNum)
{
    //
    // Check the arguments.
    //
    ASSERT(regionNum < 8U);

    //
    // Select the region to modify.
    //
    HWREG(NVIC_BASE + NVIC_O_MPU_RNR) = (HWREG(NVIC_BASE + NVIC_O_MPU_RNR) &
                                         ~NVIC_MPU_RNR_REGION_M) | regionNum;

    //
    // Modify the enable bit in the region attributes.
    //
    HWREG(NVIC_BASE + NVIC_O_MPU_RASR) &= ~NVIC_MPU_RASR_ENABLE;
}

//*****************************************************************************
//
//! Sets up the access rules for a specific region.
//!
//! \param regionNum is the region number to set up.
//! \param baseAddr is the base address of the region.  It must be aligned
//! according to the size of the region specified in attrFlags.
//! \param attrFlags is a set of flags to define the attributes of the region.
//!
//! This function sets up the protection rules for a region.  The region has
//! a base address and a set of attributes including the size.
//!
//! The region number parameter, \e regionNum specifies the region number to be
//! setup. Valid values for \e regionNum parameter are:
//! - \b MPU_RGN_0
//! - \b MPU_RGN_1
//! - \b MPU_RGN_2
//! - \b MPU_RGN_3
//! - \b MPU_RGN_4
//! - \b MPU_RGN_5
//! - \b MPU_RGN_6
//! - \b MPU_RGN_7
//!
//! The base address parameter, \e baseAddr, must be aligned according to the
//! size, and the size must be a power of 2.
//!
//! The \e attrFlags parameter is the logical OR of all of the attributes
//! of the region.  It is a combination of choices for region size,
//! execute permission, read/write permissions, disabled sub-regions,
//! and a flag to determine if the region is enabled.
//!
//! The size flag determines the size of a region and must be one of the
//! following:
//! - \b MPU_RGN_SIZE_32B
//! - \b MPU_RGN_SIZE_64B
//! - \b MPU_RGN_SIZE_128B
//! - \b MPU_RGN_SIZE_256B
//! - \b MPU_RGN_SIZE_512B
//! - \b MPU_RGN_SIZE_1K
//! - \b MPU_RGN_SIZE_2K
//! - \b MPU_RGN_SIZE_4K
//! - \b MPU_RGN_SIZE_8K
//! - \b MPU_RGN_SIZE_16K
//! - \b MPU_RGN_SIZE_32K
//! - \b MPU_RGN_SIZE_64K
//! - \b MPU_RGN_SIZE_128K
//! - \b MPU_RGN_SIZE_256K
//! - \b MPU_RGN_SIZE_512K
//! - \b MPU_RGN_SIZE_1M
//! - \b MPU_RGN_SIZE_2M
//! - \b MPU_RGN_SIZE_4M
//! - \b MPU_RGN_SIZE_8M
//! - \b MPU_RGN_SIZE_16M
//! - \b MPU_RGN_SIZE_32M
//! - \b MPU_RGN_SIZE_64M
//! - \b MPU_RGN_SIZE_128M
//! - \b MPU_RGN_SIZE_256M
//! - \b MPU_RGN_SIZE_512M
//! - \b MPU_RGN_SIZE_1G
//! - \b MPU_RGN_SIZE_2G
//! - \b MPU_RGN_SIZE_4G
//!
//! The execute permission flag must be one of the following:
//! - \b MPU_RGN_PERM_EXEC enables the region for execution of code
//! - \b MPU_RGN_PERM_NOEXEC disables the region for execution of code
//!
//! The read/write access permissions are applied separately for the
//! privileged and user modes.  The read/write access flags must be one
//! of the following:
//! - \b MPU_RGN_PERM_PRV_NO_USR_NO - no access in privileged or user mode
//! - \b MPU_RGN_PERM_PRV_RW_USR_NO - privileged read/write, user no access
//! - \b MPU_RGN_PERM_PRV_RW_USR_RO - privileged read/write, user read-only
//! - \b MPU_RGN_PERM_PRV_RW_USR_RW - privileged read/write, user read/write
//! - \b MPU_RGN_PERM_PRV_RO_USR_NO - privileged read-only, user no access
//! - \b MPU_RGN_PERM_PRV_RO_USR_RO - privileged read-only, user read-only
//!
//! The region is automatically divided into 8 equally-sized sub-regions by
//! the MPU.  Sub-regions can only be used in regions of size 256 bytes
//! or larger.  Any of these 8 sub-regions can be disabled, allowing for
//! creation of ``holes'' in a region which can be left open, or overlaid
//! by another region with different attributes.  Any of the 8 sub-regions
//! can be disabled with a logical OR of any of the following flags:
//! - \b MPU_SUB_RGN_DISABLE_0
//! - \b MPU_SUB_RGN_DISABLE_1
//! - \b MPU_SUB_RGN_DISABLE_2
//! - \b MPU_SUB_RGN_DISABLE_3
//! - \b MPU_SUB_RGN_DISABLE_4
//! - \b MPU_SUB_RGN_DISABLE_5
//! - \b MPU_SUB_RGN_DISABLE_6
//! - \b MPU_SUB_RGN_DISABLE_7
//!
//! Finally, the region can be initially enabled or disabled with one of
//! the following flags:
//! - \b MPU_RGN_ENABLE
//! - \b MPU_RGN_DISABLE
//!
//! As an example, to set a region with the following attributes: size of
//! 32 KB, execution enabled, read-only for both privileged and user, one
//! sub-region disabled, and initially enabled; the \e attrFlags parameter
//! would have the following value:
//!
//! <code>
//! (MPU_RGN_SIZE_32K | MPU_RGN_PERM_EXEC | MPU_RGN_PERM_PRV_RO_USR_RO |
//!  MPU_SUB_RGN_DISABLE_2 | MPU_RGN_ENABLE)
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
MPU_setRegionAttributes(uint32_t regionNum, uint32_t baseAddr,
                        uint32_t attrFlags)
{
    uint32_t temp;

    //
    // Check the arguments.
    //
    ASSERT(regionNum < 8U);

    //
    // Checking whether the region base address is aligned according to the
    // desired region size.
    //
    ASSERT(baseAddr == (baseAddr & (~(uint32_t)0U <<
                        (((attrFlags & NVIC_MPU_RASR_SIZE_M) >>
                        NVIC_MPU_RASR_SIZE_S) + 1U))));

    //
    // Select region to be configured.
    //
    HWREG(NVIC_BASE + NVIC_O_MPU_RNR) = (regionNum & NVIC_MPU_RNR_REGION_M) >>
                                         NVIC_MPU_RNR_REGION_S;

    //
    // Program the region attributes.
    //
    temp = MPU_RGN_CONFIG_M;
    HWREG(NVIC_BASE + NVIC_O_MPU_RASR) = (HWREG(NVIC_BASE + NVIC_O_MPU_RASR) &
                                          ~(temp)) | attrFlags;

    //
    // Program the base address of the region.
    //
    HWREG(NVIC_BASE + NVIC_O_MPU_RBAR) = baseAddr;
}

//*****************************************************************************
//
//! Gets the current settings for a specific region.
//!
//! \param regionNum is the region number to get.
//! \param baseAddr points to storage for the base address of the region.
//! \param attrFlags points to the attribute flags for the region.
//!
//! This function retrieves the configuration of a specific region.  The
//! meanings and format of the parameters is the same as that of the
//! MPU_setRegionAttributes() function.
//!
//! This function can be used to save the configuration of a region for later
//! use with the MPU_setRegionAttributes() function.  The region's enable state
//! is preserved in the attributes that are saved.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MPU_getRegionAttributes(uint32_t regionNum, uint32_t *baseAddr,
                        uint32_t *attrFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(regionNum < 8U);
    ASSERT(baseAddr != 0U);
    ASSERT(attrFlags != 0U);

    //
    // Select the region to get.
    //
    HWREG(NVIC_BASE + NVIC_O_MPU_RNR) = regionNum;

    //
    // Read and store the base address for the region.
    //
    *baseAddr = HWREG(NVIC_BASE + NVIC_O_MPU_RBAR) & NVIC_MPU_RBAR_ADDR_M;

    //
    // Read and store the region attributes.
    //
    *attrFlags = HWREG(NVIC_BASE + NVIC_O_MPU_RASR);
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
//! generates a memory management fault due to a protection region access
//! violation. The param intNum can take value FAULT_MPU.
//!
//! \sa Interrupt_registerHandler() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MPU_registerHandler(uint32_t intNum, void (*fnHandler)(void))
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
//! memory management fault occurs. The param intNum can take value FAULT_MPU.
//!
//! \sa Interrupt_registerHandler() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MPU_unregisterHandler(uint32_t intNum)
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

#endif // MPU_H
