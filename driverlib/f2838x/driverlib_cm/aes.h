//###########################################################################
//
// FILE:   aes.h
//
// TITLE:  Driver for the AES module.
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

#ifndef AES_H
#define AES_H

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
//! \addtogroup aes_api AES
//! @{
//
//*****************************************************************************
#include <stdbool.h>
#include <stdint.h>
#include "debug.h"
#include "interrupt.h"
#include "inc/hw_aes.h"
#include "inc/hw_aes_ss.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

//*****************************************************************************
//
// Interrupt flags for use with AES_enableInterrupt(), AES_disableInterrupt(),
// AES_clearInterruptStatus() & AES_getInterruptStatus() functions.
//
//*****************************************************************************
#define AES_INT_CONTEXT_IN       0x00000001U //!< Context-In Interrupt
#define AES_INT_CONTEXT_OUT      0x00000008U //!< Context-Out Interrupt
#define AES_INT_DATA_IN          0x00000002U //!< Data-In Interrupt
#define AES_INT_DATA_OUT         0x00000004U //!< Data-Out Interrupt
#define AES_INT_DMA_CONTEXT_IN   0x00010000U //!< DMA Context-In Done Interrupt
#define AES_INT_DMA_CONTEXT_OUT  0x00080000U //!< DMA Context-Out Done Interrupt
#define AES_INT_DMA_DATA_IN      0x00020000U //!< DMA Data-In Done Interrupt
#define AES_INT_DMA_DATA_OUT     0x00040000U //!< DMA Data-Out Done Interrupt

//*****************************************************************************
//
// Mask to specify AES-core related interrupts. It is the logical OR of all the
// AES only interrupts.
//
//*****************************************************************************
#define AES_AESINT_M             (AES_INT_CONTEXT_IN  |                        \
                                  AES_INT_CONTEXT_OUT |                        \
                                  AES_INT_DATA_IN     |                        \
                                  AES_INT_DATA_OUT)

//*****************************************************************************
//
// Mask to specify all the DMA-Done related interrupts. It is the logical OR
// of all the individual DMA-Done interrupts.
//
//*****************************************************************************
#define AES_DMAINT_M             (AES_INT_DMA_CONTEXT_IN  |                    \
                                  AES_INT_DMA_CONTEXT_OUT |                    \
                                  AES_INT_DMA_DATA_IN     |                    \
                                  AES_INT_DMA_DATA_OUT)

//*****************************************************************************
//
// Mask to specify all the AES related interrupts. It is the logical OR
// of all the individual AES module and AES wrapper related DMA-Done interrupts.
//
//*****************************************************************************
#define AES_INT_ALL_M            (AES_INT_CONTEXT_IN | AES_INT_CONTEXT_OUT   | \
                                  AES_INT_DATA_IN  | AES_INT_DMA_CONTEXT_IN  | \
                                  AES_INT_DATA_OUT | AES_INT_DMA_CONTEXT_OUT | \
                                  AES_INT_DMA_DATA_IN | AES_INT_DMA_DATA_OUT)

//*****************************************************************************
//
// Defines that can be used for enabling and disabling DMA requests in the
// AES_enableDMARequest() and AES_disableDMARequest() functions.
//
//*****************************************************************************
#define AES_DMA_EN_DATA_IN       0x00000020U //!<Enable DMA for data i/p request
#define AES_DMA_EN_DATA_OUT      0x00000040U //!<Enable DMA for data o/p request
#define AES_DMA_EN_CONTEXT_IN    0x00000080U //!<Enable DMA for ctx i/p request
#define AES_DMA_EN_CONTEXT_OUT   0x00000100U //!<Enable DMA for ctx o/p request

//*****************************************************************************
//
// Mask to specify all the possible DMA requests. It is the logical OR
// of all the individual DMA requests..
//
//*****************************************************************************
#define AES_DMA_EN_M      (AES_DMA_EN_DATA_IN    | AES_DMA_EN_DATA_OUT |       \
                           AES_DMA_EN_CONTEXT_IN | AES_DMA_EN_CONTEXT_OUT)

//*****************************************************************************
//
// Define to specify the mask for the AES configurations related fields.
//
//*****************************************************************************
#define AES_CONFIG_M  ((uint32_t)AES_CTRL_DIRECTION   |                        \
                       (uint32_t)AES_CTRL_MODE        |                        \
                       (uint32_t)AES_CTRL_KEY_SIZE_M  |                        \
                       (uint32_t)AES_CTRL_CTR         |                        \
                       (uint32_t)AES_CTRL_CTR_WIDTH_M |                        \
                       (uint32_t)AES_CTRL_ICM         |                        \
                       (uint32_t)AES_CTRL_CFB         |                        \
                       (uint32_t)AES_CTRL_XTS_M       |                        \
                       (uint32_t)AES_CTRL_F8          |                        \
                       (uint32_t)AES_CTRL_F9          |                        \
                       (uint32_t)AES_CTRL_CBCMAC      |                        \
                       (uint32_t)AES_CTRL_GCM_M       |                        \
                       (uint32_t)AES_CTRL_CCM         |                        \
                       (uint32_t)AES_CTRL_CCM_L_M     |                        \
                       (uint32_t)AES_CTRL_CCM_M_M)

//*****************************************************************************
//
//! Values that can be passed to AES_configureModule() as the \e config
//! parameter's \e direction member.
//
//*****************************************************************************
typedef enum
{
    AES_DIRECTION_DECRYPT  = 0x00000000U, //!< Select Decryption Mode
    AES_DIRECTION_ENCRYPT  = 0x00000004U  //!< Select Encryption Mode
} AES_Direction;

//*****************************************************************************
//
//! Values that can be passed to AES_configureModule() as the \e config
//! parameter's \e keySize member.
//
//*****************************************************************************
typedef enum
{
    AES_KEY_SIZE_128BIT    = 0x00000008U, //!< Select 128-bit key
    AES_KEY_SIZE_192BIT    = 0x00000010U, //!< Select 192-bit key
    AES_KEY_SIZE_256BIT    = 0x00000018U  //!< Select 256-bit key
} AES_KeySize;

//*****************************************************************************
//
//! Values that can be passed to AES_configureModule() as the \e config
//! parameter's \e opMode member.
//
//*****************************************************************************
typedef enum
{
    AES_OPMODE_ECB             = 0x00000000U, //!< Select ECB mode
    AES_OPMODE_CBC             = 0x00000020U, //!< Select CBC mode
    AES_OPMODE_CTR             = 0x00000040U, //!< Select CTR mode
    AES_OPMODE_ICM             = 0x00000200U, //!< Select ICM mode
    AES_OPMODE_CFB             = 0x00000400U, //!< Select CFB mode
    AES_OPMODE_XTS_TWEAKJL     = 0x00000800U, //!< Select XTS TWEAKJL mode
    AES_OPMODE_XTS_K2NJL       = 0x00001000U, //!< Select XTS K2IJL mode
    AES_OPMODE_XTS_K2NLJ0      = 0x00001800U, //!< Select XTS K2ILJ0 mode
    AES_OPMODE_F8              = 0x00002000U, //!< Select F8 mode
    AES_OPMODE_F9              = 0x20004000U, //!< Select F9 mode
    AES_OPMODE_CBCMAC          = 0x20008000U, //!< Select CBC-MAC mode
    AES_OPMODE_GCM_HLY0ZERO    = 0x20010000U, //!< Select GCM HLY0ZERO mode
    AES_OPMODE_GCM_HLY0CALC    = 0x20020040U, //!< Select GCM HLY0CALC mode
    AES_OPMODE_GCM_HY0CALC     = 0x20030040U, //!< Select GCM HY0CALC mode
    AES_OPMODE_CCM             = 0x20040040U  //!< Select CCM mode
} AES_OpMode;

//*****************************************************************************
//
//! Values that can be passed to AES_configureModule() as the \e config
//! parameter's \e ctrWidth member.
//
//*****************************************************************************
typedef enum
{
    AES_CTR_WIDTH_32BIT     = 0x00000000U, //!< Select 32-bit counter
    AES_CTR_WIDTH_64BIT     = 0x00000080U, //!< Select 64-bit counter
    AES_CTR_WIDTH_96BIT     = 0x00000100U, //!< Select 96-bit counter
    AES_CTR_WIDTH_128BIT    = 0x00000180U  //!< Select 128-bit counter
} AES_CounterWidth;

//*****************************************************************************
//
//! Values that can be passed to AES_configureModule() as the \e config
//! parameter's \e ccmLenWidth member.
//
//*****************************************************************************
typedef enum
{
    AES_CCM_L_1     = 0x00000000U, //!< CCM Length width = 1 byte
    AES_CCM_L_2     = 0x00080000U, //!< CCM Length width = 2 bytes
    AES_CCM_L_4     = 0x00180000U, //!< CCM Length width = 4 bytes
    AES_CCM_L_8     = 0x00380000U  //!< CCM Length width = 8 bytes
} AES_CCMLenWidth;

//*****************************************************************************
//
//! Values that can be passed to AES_configureModule() as the \e config
//! parameter's \e ccmAuthLenWidth member.
//
//*****************************************************************************
typedef enum
{
    AES_CCM_M_0      = 0x00000000U, //!< CCM Auth Length width at reset
    AES_CCM_M_4      = 0x00400000U, //!< CCM Auth Length width = 4 bytes
    AES_CCM_M_6      = 0x00800000U, //!< CCM Auth Length width = 6 bytes
    AES_CCM_M_8      = 0x00C00000U, //!< CCM Auth Length width = 8 bytes
    AES_CCM_M_10     = 0x01000000U, //!< CCM Auth Length width = 10 bytes
    AES_CCM_M_12     = 0x01400000U, //!< CCM Auth Length width = 12 bytes
    AES_CCM_M_14     = 0x01800000U, //!< CCM Auth Length width = 14 bytes
    AES_CCM_M_16     = 0x01C00000U  //!< CCM Auth Length width = 16 bytes
} AES_CCMAuthLenWidth;

//*****************************************************************************
//
//! Values that can be passed to AES_configureModule() as the \e config
//! parameter.
//
//*****************************************************************************
typedef struct
{
    AES_Direction       direction;        //!< AES Direction Mode
    AES_KeySize         keySize;          //!< AES Key Size
    AES_OpMode          opMode;           //!< AES Mode
    AES_CounterWidth    ctrWidth;         //!< Counter Width (for CTR Mode)
    AES_CCMLenWidth     ccmLenWidth;      //!< Length Width (for CCM Mode)
    AES_CCMAuthLenWidth ccmAuthLenWidth;  //!< Auth Length Width (for CCM Mode)
} AES_ConfigParams;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks the AES module base address.
//!
//! \param base is the base address of the AES instance used.
//!
//! This function determines if AES module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
AES_isBaseValid(uint32_t base)
{
    return(base == AES_BASE);



}
#endif

//*****************************************************************************
//
//! \internal
//! Checks AES module wrapper base address.
//!
//! \param configBase is the base address of the used AES wrapper instance.
//!
//! This function determines if AES wrapper base address is valid.
//!
//! \return Returns \b true if the wrapper address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
AES_isWrapperBaseValid(uint32_t wrapperBase)
{
    return(wrapperBase == AESW_BASE);
}
#endif

//*****************************************************************************
//
//! Resets the AES module.
//!
//! \param base is the base address of the AES module.
//!
//! This function performs a soft-reset of the AES module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
AES_performSoftReset(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // Trigger the reset.
    //
    HWREG_BP(base + AES_O_SYSCONFIG) |= AES_SYSCONFIG_SOFTRESET;

    //
    // Wait for the reset to finish.
    //
    while((HWREG_BP(base + AES_O_SYSSTATUS) &
            AES_SYSSTATUS_RESETDONE) != AES_SYSSTATUS_RESETDONE)
    {
    }
}

//*****************************************************************************
//
//! Used to set the write crypto data length in the AES module.
//!
//! \param base is the base address of the AES module.
//! \param length is the crypto data length in bytes.
//!
//! This function stores the cryptographic data length in blocks for all modes.
//! Data lengths up to (2^61 - 1) bytes are allowed.  For GCM, any value up
//! to (2^36 - 32) bytes are allowed because a 32-bit block counter is used.
//! For basic modes (ECB/CBC/CTR/ICM/CFB128), zero can be programmed into the
//! length field, indicating that the length is infinite.
//!
//! When this function is called, the engine is triggered to start using
//! this context.
//!
//! \note This length does not include the authentication-only data used in
//! some modes.  Use the AES_setAuthDataLength() function to specify the
//! authentication data length.
//!
//! \return None
//
//*****************************************************************************
static inline void
AES_setDataLength(uint32_t base, uint64_t length)
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // Write the length register by shifting the 64-bit length.
    //
    HWREG_BP(base + AES_O_C_LENGTH_0) = (uint32_t)(length);
    HWREG_BP(base + AES_O_C_LENGTH_1) = (uint32_t)(length >> 32U);
}

//*****************************************************************************
//
//! Sets the authentication data length in the AES module.
//!
//! \param base is the base address of the AES module.
//! \param authLength is the authentication data length in bytes.
//!
//! This function is only used to write the authentication data length in the
//! combined modes (GCM or CCM) and XTS mode.  Supported AAD lengths for CCM
//! are from 0 to (2^16 - 2^8) bytes.  For GCM, any value up to (2^32 - 1) can
//! be used.  For XTS mode, this register is used to load j.  Loading of j is
//! only required if j != 0.  j represents the sequential number of the 128-bit
//! blocks inside the data unit.  Consequently, j must be multiplied by 16
//! before it is passed to this function, thereby placing the block number in
//! bits [31:4] of the register.
//!
//! When this function is called, the engine is triggered to start using
//! this context for GCM and CCM.
//!
//! \return None
//
//*****************************************************************************
static inline void
AES_setAuthDataLength(uint32_t base, uint32_t authLength)
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));

    //
    // Write the length into the register.
    //
    HWREG_BP(base + AES_O_AUTH_LENGTH) = authLength;
}

//*****************************************************************************
//
//! Enables AES module interrupts.
//!
//! \param base is the base address of the AES module.
//! \param wrapperBase is the base address of the AES module wrapper.
//! \param intFlags is a bit mask of the interrupt sources to enable.
//!
//! This function enables the interrupts in the AES module.  The
//! \e intFlags parameter is the logical OR of any of the following:
//!
//! - \b AES_INT_CONTEXT_IN      - Context interrupt
//! - \b AES_INT_CONTEXT_OUT     - Authentication tag (and IV) interrupt
//! - \b AES_INT_DATA_IN         - Data input interrupt
//! - \b AES_INT_DATA_OUT        - Data output interrupt
//! - \b AES_INT_DMA_CONTEXT_IN  - Context DMA done interrupt
//! - \b AES_INT_DMA_CONTEXT_OUT - Authentication tag (and IV) DMA done
//!   interrupt
//! - \b AES_INT_DMA_DATA_IN     - Data input DMA done interrupt
//! - \b AES_INT_DMA_DATA_OUT    - Data output DMA done interrupt
//!
//! \note Interrupts that have been previously been enabled are not disabled
//! when this function is called.
//!
//! \return None.
//
//*****************************************************************************
static inline void
AES_enableInterrupt(uint32_t base, uint32_t wrapperBase, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));
    ASSERT(AES_isWrapperBaseValid(wrapperBase));
    ASSERT((intFlags & AES_INT_ALL_M) != 0U);

    //
    // Enable the Interrupts. Shifting the intFlags by 16U to get the correct
    // bit position for DMA related interrupts.
    //
    HWREG_BP(base + AES_O_IRQENABLE) |= (intFlags & AES_AESINT_M);
    HWREG_BP(wrapperBase + AES_SS_O_AESDMAINTEN) |= ((intFlags >> 16U) &
                                                  AES_AESINT_M);
}

//*****************************************************************************
//
//! Disables AES module interrupts.
//!
//! \param base is the base address of the AES module.
//! \param wrapperBase is the base address of the AES module wrapper.
//! \param intFlags is a bit mask of the interrupt sources to disable.
//!
//! This function disables the interrupt sources in the AES module.  The
//! \e intFlags parameter is the logical OR of any of the following:
//!
//! - \b AES_INT_CONTEXT_IN      - Context interrupt
//! - \b AES_INT_CONTEXT_OUT     - Authentication tag (and IV) interrupt
//! - \b AES_INT_DATA_IN         - Data input interrupt
//! - \b AES_INT_DATA_OUT        - Data output interrupt
//! - \b AES_INT_DMA_CONTEXT_IN  - Context DMA done interrupt
//! - \b AES_INT_DMA_CONTEXT_OUT - Authentication tag (and IV) DMA done
//!   interrupt
//! - \b AES_INT_DMA_DATA_IN     - Data input DMA done interrupt
//! - \b AES_INT_DMA_DATA_OUT    - Data output DMA done interrupt
//!
//! \note The DMA done interrupts are the only interrupts that can be cleared.
//! The remaining interrupts can be disabled instead using
//! AES_disableInterrupt().
//!
//! \return None.
//
//*****************************************************************************
static inline void
AES_disableInterrupt(uint32_t base, uint32_t wrapperBase, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));
    ASSERT(AES_isWrapperBaseValid(wrapperBase));
    ASSERT((intFlags & AES_INT_ALL_M) != 0U);

    //
    // Disable the Interrupts. Shifting the intFlags by 16U to get the correct
    // bit position for DMA related interrupts.
    //
    HWREG_BP(base + AES_O_IRQENABLE) &= ~(intFlags & AES_AESINT_M);
    HWREG_BP(wrapperBase + AES_SS_O_AESDMAINTEN) &= ~((intFlags >> 16U) &
                                                   AES_AESINT_M);
}

//*****************************************************************************
//
//! Clears AES module interrupts.
//!
//! \param wrapperBase is the base address of the AES module wrapper.
//! \param intFlags is a bit mask of the interrupt sources to disable.
//!
//! This function clears the interrupt sources in the AES module.  The
//! \e intFlags parameter is the logical OR of any of the following:
//!
//! - \b AES_INT_DMA_CONTEXT_IN  - Context DMA done interrupt
//! - \b AES_INT_DMA_CONTEXT_OUT - Authentication tag (and IV) DMA done
//!   interrupt
//! - \b AES_INT_DMA_DATA_IN     - Data input DMA done interrupt
//! - \b AES_INT_DMA_DATA_OUT    - Data output DMA done interrupt
//!
//! \note Only the DMA done interrupts can be cleared.  The remaining
//! interrupts should be disabled with AES_disableInterrupt().
//!
//! \return None.
//
//*****************************************************************************
static inline void
AES_clearInterruptStatus(uint32_t wrapperBase, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isWrapperBaseValid(wrapperBase));
    ASSERT((intFlags & AES_DMAINT_M) != 0U);

    //
    // Clear DMA Done Interrupts. Shifting the intFlags by 16U to get the
    // correct bit position for DMA related interrupts.
    //
    HWREG_BP(wrapperBase + AES_SS_O_AESDMASTATUSCLR) = (intFlags >> 16U) &
                                                     AES_AESINT_M;
}

//*****************************************************************************
//
//! Registers an interrupt handler for the AES module.
//!
//! \param intNum is the interrupt number for AES interrupt.
//! \param fnHandler is a pointer to the function to be called when the
//! enabled AES interrupts occur.
//!
//! This function registers the interrupt handler in the interrupt vector
//! table, and enables AES interrupts on the interrupt controller; specific AES
//! interrupt sources must be enabled using AES_enableInterrupt(). The interrupt
//! handler being registered must clear the source of the interrupt using
//! AES_clearInterruptStatus().
//!
//! If the application is using a static interrupt vector table stored in
//! flash, then it is not necessary to register the interrupt handler this way.
//! Instead, Interrupt_enable() is used to enable AES interrupts on the
//! interrupt controller.
//!
//! The \e intNum parameter can take following value: AES_INT
//!
//! \sa Interrupt_registerHandler() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
AES_registerInterrupt(uint32_t intNum, void (*fnHandler)(void))
{
    //
    // Register the interrupt handler.
    //
    Interrupt_registerHandler(intNum, fnHandler);

    //
    // Enable the interrupt
    //
    Interrupt_enable(intNum);
}
//*****************************************************************************
//
//! Unregisters an interrupt handler for the AES module.
//!
//! \param intNum is the interrupt number for AES interrupt.
//!
//! This function unregisters the previously registered interrupt handler and
//! disables the interrupt in the interrupt controller.
//!
//! The \e intNum parameter can take following value: AES_INT
//!
//! \sa Interrupt_registerHandler() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
AES_unregisterInterrupt(uint32_t intNum)
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
//! Enables uDMA requests for the AES module.
//!
//! \param base is the base address of the AES module.
//! \param reqFlags is a bit mask of the uDMA requests to be enabled.
//!
//! This function enables the uDMA request sources in the AES module.
//! The \e reqFlags parameter is the logical OR of any of the following:
//!
//! - \b AES_DMA_EN_DATA_IN
//! - \b AES_DMA_EN_DATA_OUT
//! - \b AES_DMA_EN_CONTEXT_IN
//! - \b AES_DMA_EN_CONTEXT_OUT
//!
//! \return None.
//
//*****************************************************************************
static inline void
AES_enableDMARequest(uint32_t base, uint32_t reqFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));
    ASSERT((reqFlags & AES_DMA_EN_M) != 0U);

    //
    // Enable DMA requests.
    //
    HWREG_BP(base + AES_O_SYSCONFIG) |= reqFlags;
}

//*****************************************************************************
//
//! Disables uDMA requests for the AES module.
//!
//! \param base is the base address of the AES module.
//! \param reqFlags is a bit mask of the uDMA requests to be disabled.
//!
//! This function disables the uDMA request sources in the AES module.
//! The \e reqFlags parameter is the logical OR of any of the
//! following:
//!
//! - \b AES_DMA_EN_DATA_IN
//! - \b AES_DMA_EN_DATA_OUT
//! - \b AES_DMA_EN_CONTEXT_IN
//! - \b AES_DMA_EN_CONTEXT_OUT
//!
//! \return None.
//
//*****************************************************************************
static inline void
AES_disableDMARequest(uint32_t base, uint32_t reqFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(AES_isBaseValid(base));
    ASSERT((reqFlags & AES_DMA_EN_M) != 0U);

    //
    // Disable DMA requests.
    //
    HWREG_BP(base + AES_O_SYSCONFIG) &= ~reqFlags;
}

//*****************************************************************************
//
//! Configures the AES module.
//!
//! \param base is the base address of the AES module.
//! \param config is the configuration of the AES module.
//!
//! This function configures the AES module based on the specified parameters.
//! It does not change any DMA- or interrupt-related parameters.
//!
//! The config parameter is a structure with members specifying valid AES mode
//! configurations.
//!
//! The direction of the operation is specified with following enum members:
//!
//! - \b AES_DIRECTION_ENCRYPT - Encryption mode
//! - \b AES_DIRECTION_DECRYPT - Decryption mode
//!
//! The key size is specified with following enum members:
//!
//! - \b AES_KEY_SIZE_128BIT - Key size of 128 bits
//! - \b AES_KEY_SIZE_192BIT - Key size of 192 bits
//! - \b AES_KEY_SIZE_256BIT - Key size of 256 bits
//!
//! The mode of operation is specified with following enum members:
//!
//! - \b AES_OPMODE_ECB - Electronic codebook mode
//! - \b AES_OPMODE_CBC - Cipher-block chaining mode
//! - \b AES_OPMODE_CFB - Cipher feedback mode
//! - \b AES_OPMODE_CTR - Counter mode
//! - \b AES_OPMODE_ICM - Integer counter mode
//! - \b AES_OPMODE_XTS_TWEAKJL - XEX-based tweaked-codebook mode with
//!   ciphertext stealing with previous/intermediate tweak value and j loaded
//! - \b AES_OPMODE_XTS_K2IJL - XEX-based tweaked-codebook mode with
//!   ciphertext stealing with key2, i and j loaded
//! - \b AES_OPMODE_XTS_K2ILJ0 - XEX-based tweaked-codebook mode with
//!   ciphertext stealing with key2 and i loaded, j = 0
//! - \b AES_OPMODE_F8 - F8 mode
//! - \b AES_OPMODE_F9 - F9 mode
//! - \b AES_OPMODE_CBCMAC - Cipher block chaining message authentication
//!   code mode
//! - \b AES_OPMODE_GCM_HLY0ZERO - Galois/counter mode with GHASH with H
//!   loaded, Y0-encrypted forced to zero and counter is not enabled.
//! - \b AES_OPMODE_GCM_HLY0CALC - Galois/counter mode with GHASH with H
//!   loaded, Y0-encrypted calculated internally and counter is enabled.
//! - \b AES_OPMODE_GCM_HY0CALC - Galois/Counter mode with autonomous GHASH
//!   (both H and Y0-encrypted calculated internally) and counter is enabled.
//! - \b AES_OPMODE_CCM - Counter with CBC-MAC mode
//!
//! The following enums are used to specify the counter width.  It is only
//! required to be defined when using CTR, CCM, or GCM modes, only one of the
//! following defines must be used to specify the counter width length:
//!
//! - \b AES_CTR_WIDTH_32BIT - Counter is 32 bits
//! - \b AES_CTR_WIDTH_64BIT - Counter is 64 bits
//! - \b AES_CTR_WIDTH_96BIT - Counter is 96 bits
//! - \b AES_CTR_WIDTH_128BIT - Counter is 128 bits
//!
//! Only one of the following defines must be used to specify the length field
//! for CCM operations (L):
//!
//! - \b AES_CCM_L_1 - 1 byte
//! - \b AES_CCM_L_2 - 2 bytes
//! - \b AES_CCM_L_4 - 4 bytes
//! - \b AES_CCM_L_8 - 8 bytes
//!
//! Only one of the following enum members must be used to specify the length
//! of authentication field for CCM operations (M) through the \e config
//! argument member in the AES_configureModule() function:
//!
//! - \b AES_CCM_M_0  - reset value
//! - \b AES_CCM_M_4  - 4 bytes
//! - \b AES_CCM_M_6  - 6 bytes
//! - \b AES_CCM_M_8  - 8 bytes
//! - \b AES_CCM_M_10 - 10 bytes
//! - \b AES_CCM_M_12 - 12 bytes
//! - \b AES_CCM_M_14 - 14 bytes
//! - \b AES_CCM_M_16 - 16 bytes
//!
//! \note When performing a basic GHASH operation for used with GCM mode, use
//! the \b AES_OPMODE_GCM_HLY0ZERO and do not specify a direction.
//!
//! \return None.
//
//*****************************************************************************
extern void
AES_configureModule(uint32_t base, const AES_ConfigParams *config);

//*****************************************************************************
//
//! Writes the key 1 configuration registers, which are used for encryption or
//! decryption.
//!
//! \param base is the base address for the AES module.
//! \param key is an array of 32-bit words, containing the key to be
//! configured.  The least significant word is at the 0th index. The key array
//! data values are expected to be in big-endian format.
//! \param keySize is the size of the key, which must be one of the
//! following enum values:  \b AES_KEY_SIZE_128BIT, \b AES_KEY_SIZE_192BIT, or
//! \b AES_KEY_SIZE_256BIT.
//!
//! This function writes key 1 configuration registers based on the key
//! size.  This function is used in all modes.
//!
//! \return None.
//
//*****************************************************************************
extern void
AES_setKey1(uint32_t base, const uint32_t key[], AES_KeySize keySize);

//*****************************************************************************
//
//! Writes the key 2 configuration registers, which are used for encryption or
//! decryption.
//!
//! \param base is the base address for the AES module.
//! \param key is an array of 32-bit words, containing the key to be
//! configured.  The least significant word in the 0th index. The key array
//! data values are expected to be in big-endian format.
//! \param keySize is the size of the key, which must be one of the
//! following enum values:  \b AES_KEY_SIZE_128BIT, \b AES_KEY_SIZE_192BIT, or
//! \b AES_KEY_SIZE_256BIT.
//!
//! This function writes the key 2 configuration registers based on the key
//! size.  This function is used in the F8, F9, XTS, CCM, and CBC-MAC modes.
//!
//! \return None.
//
//*****************************************************************************
extern void
AES_setKey2(uint32_t base, const uint32_t key[], AES_KeySize keySize);

//*****************************************************************************
//
//! Writes key 3 configuration registers, which are used for encryption or
//! decryption.
//!
//! \param base is the base address for the AES module.
//! \param key is a pointer to an array of 4 words (128 bits), containing
//! the key to be configured.  The least significant word is in the 0th index.
//! The key array data values are expected to be in big-endian format.
//!
//! This function writes the key 2 configuration registers with key 3 data
//! used in CBC-MAC and F8 modes.  This key is always 128 bits.
//!
//! \return None.
//
//*****************************************************************************
extern void
AES_setKey3(uint32_t base, const uint32_t key[]);

//*****************************************************************************
//
//! Writes the Initial Vector (IV) register, needed in some of the AES Modes.
//!
//! \param base is the base address of the AES module.
//! \param iniVector is an array of 4 words (128 bits), containing the IV
//! value to be configured.  The least significant word is in the 0th index.
//! The IV array data values are expected to be in big-endian format.
//!
//! This function writes the initial vector registers in the AES module.
//!
//! \return None.
//
//*****************************************************************************
extern void
AES_setInitializationVector(uint32_t base, const uint32_t iniVector[]);

//*****************************************************************************
//
//! Saves the Initial Vector (IV) registers to a user-defined location.
//!
//! \param base is the base address of the AES module.
//! \param iniVector is pointer to the location that stores the IV data. The
//! least significant word is in the 0th index. The IV data values are
//! expected to be in big-endian format.
//!
//! This function stores the IV for use in authenticated encryption and
//! decryption operations.  It is assumed that the AES_CTRL_SAVE_CONTEXT
//! bit is set in the AES_CTRL register.
//!
//! \return None.
//
//*****************************************************************************
extern void
AES_readInitializationVector(uint32_t base, uint32_t iniVector[]);

//*****************************************************************************
//
//! Saves the tag registers to a user-defined location.
//!
//! \param base is the base address of the AES module.
//! \param tagData is pointer to the location that stores the tag data. The
//! least significant word is in the 0th index. The tag array data values are
//! expected to be in big-endian format.
//!
//! This function stores the tag data for use in authenticated encryption and
//! decryption operations.  It is assumed that the AES_CTRL_SAVE_CONTEXT
//! bit is set in the AES_CTRL register.
//!
//! \return None.
//
//*****************************************************************************
extern void
AES_readTag(uint32_t base, uint32_t tagData[]);

//*****************************************************************************
//
//! Reads plaintext/ciphertext from data registers without blocking.
//!
//! \param base is the base address of the AES module.
//! \param destArray is a pointer to an array of words of data. The least
//! significant word is in the 0th index. The read data values are expected to
//! be in big-endian format.
//!
//! This function reads a block of either plaintext or ciphertext out of the
//! AES module.  If the output data is not ready, the function returns
//! false.  If the read completed successfully, the function returns true.
//! A block is 16 bytes or 4 words.
//!
//! \return Returns true or false.
//
//*****************************************************************************
extern bool
AES_readDataNonBlocking(uint32_t base, uint32_t destArray[]);

//*****************************************************************************
//
//! Reads plaintext/ciphertext from data registers with blocking.
//!
//! \param base is the base address of the AES module.
//! \param destArray is a pointer to an array of words. The least significant
//! word is in the 0th index. The read data values are expected to
//! be in big-endian format.
//!
//! This function reads a block of either plaintext or ciphertext out of the
//! AES module.  If the output is not ready, the function waits until it is
//! ready.  A block is 16 bytes or 4 words.
//!
//! \return None.
//
//*****************************************************************************
extern void
AES_readDataBlocking(uint32_t base, uint32_t destArray[]);

//*****************************************************************************
//
//! Writes plaintext/ciphertext to data registers without blocking.
//!
//! \param base is the base address of the AES module.
//! \param srcArray is a pointer to an array of words of data. The least
//! significant word is in the 0th index. The input data values are expected to
//! be in big-endian format.
//!
//! This function writes a block of either plaintext or ciphertext into the
//! AES module.  If the input is not ready, the function returns false.  If the
//! write completed successfully, the function returns true.  A block is 16
//! bytes or 4 words.
//!
//! \return True or false.
//
//*****************************************************************************
extern bool
AES_writeDataNonBlocking(uint32_t base, const uint32_t srcArray[]);

//*****************************************************************************
//
//! Writes plaintext/ciphertext to data registers with blocking.
//!
//! \param base is the base address of the AES module.
//! \param srcArray is a pointer to an array of bytes. The least significant
//! word is in the 0th index. The input data values are expected to
//! be in big-endian format.
//!
//! This function writes a block of either plaintext or ciphertext into the
//! AES module.  If the input is not ready, the function waits until it is
//! ready before performing the write.  A block is 16 bytes or 4 words.
//!
//! \return None.
//
//*****************************************************************************
extern void
AES_writeDataBlocking(uint32_t base, const uint32_t srcArray[]);

//*****************************************************************************
//
//! Used to process(transform) blocks of data, either encrypt or decrypt it.
//!
//! \param base is the base address of the AES module.
//! \param srcArray is a pointer to the memory location where the input data
//! is stored.  The data must be padded to the 16-byte boundary. The input data
//! values are expected to be in big-endian format.
//! \param destArray is a pointer to the memory location output is written.
//! The space for written data must be rounded up to the 16-byte boundary. The
//! output data values are expected to be in big-endian format.
//! \param dataLength is the length of the cryptographic data in bytes.
//!
//! This function iterates the encryption or decryption mechanism number over
//! the data length.  Before calling this function, ensure that the AES
//! module is properly configured the key, data size, mode, and so on.  Only
//! ECB, CBC, CTR, ICM, CFB, XTS and F8 operating modes should be used.  The
//! data is processed in 4-word (16-byte) blocks.
//!
//! \return Returns true if data was processed successfully.  Returns false
//! if data processing failed.
//
//*****************************************************************************
extern bool
AES_processData(uint32_t base, const uint32_t srcArray[], uint32_t destArray[],
                uint64_t dataLength);

//*****************************************************************************
//
//! Used to authenticate blocks of data by generating a hash tag.
//!
//! \param base is the base address of the AES module.
//! \param srcArray is a pointer to the memory location where the input data
//! is stored.  The data must be padded to the 16-byte boundary. The input data
//! values are expected to be in big-endian format.
//! \param dataLength  is the length of the cryptographic data in bytes.
//! \param tagArray is a pointer to a 4-word array where the hash tag is
//! written. The output data values are to be expected in big-endian format.
//!
//! This function processes data to produce a hash tag that can be used tor
//! authentication.   Before calling this function, ensure that the AES
//! module is properly configured the key, data size, mode, and so on.  Only
//! CBC-MAC and F9 modes should be used.
//!
//! \return Returns true if data was processed successfully.  Returns false
//! if data processing failed.
//
//*****************************************************************************
extern bool
AES_authenticateData(uint32_t base, const uint32_t srcArray[],
                     uint64_t dataLength, uint32_t tagArray[]);

//*****************************************************************************
//
//! Processes and authenticates blocks of data, either encrypts it or decrypts
//! it.
//!
//! \param base  is the base address of the AES module.
//! \param srcArray is a pointer to the memory location where the input data
//! is stored.  The data must be padded to the 16-byte boundary. The input data
//! values are expected to be in big-endian format.
//! \param destArray is a pointer to the memory location where the output is
//! written. The space for written data must be rounded up to the 16-byte
//! boundary. The output data values are to be expected in big-endian format.
//! \param dataLength is the length of the cryptographic data in bytes.
//! \param authDataArray is a pointer to the memory location where the
//! additional authentication data is stored.  The data must be padded to the
//! 16-byte boundary. The output data values are to be expected in big-endian
//! format.
//! \param authDataLength is the length of the additional authentication
//! data in bytes.
//! \param tagArray is a pointer to a 4-word array where the hash tag is
//! written. The output data values are to be expected in big-endian format.
//!
//! This function encrypts or decrypts blocks of data in addition to
//! authentication data.  A hash tag is also produced.  Before calling this
//! function, ensure that the AES module is properly configured the key,
//! data size, mode, and so on.  Only CCM and GCM modes should be used.
//!
//! \return Returns true if data was processed successfully. Returns false
//! if data processing failed.
//
//*****************************************************************************
extern bool
AES_processDatainAuthMode(uint32_t base, const uint32_t srcArray[],
                          uint32_t destArray[], uint64_t dataLength,
                          const uint32_t authDataArray[],
                          uint32_t authDataLength, uint32_t tagArray[]);

//*****************************************************************************
//
//! Returns the current AES module interrupt status.
//!
//! \param base is the base address of the AES module.
//! \param wrapperBase is the base address of the AES module wrapper.
//! \param intMask is \b false if the raw interrupt status is required and
//! \b true if the masked interrupt status is required.
//!
//! \return Returns a bit mask of the interrupt sources, which is a logical OR
//! of any of the following:
//!
//! - \b AES_INT_CONTEXT_IN      - Context interrupt
//! - \b AES_INT_CONTEXT_OUT     - Authentication tag (and IV) interrupt.
//! - \b AES_INT_DATA_IN         - Data input interrupt
//! - \b AES_INT_DATA_OUT        - Data output interrupt
//! - \b AES_INT_DMA_CONTEXT_IN  - Context DMA done interrupt
//! - \b AES_INT_DMA_CONTEXT_OUT - Authentication tag (and IV) DMA done
//!   interrupt
//! - \b AES_INT_DMA_DATA_IN     - Data input DMA done interrupt
//! - \b AES_INT_DMA_DATA_OUT    - Data output DMA done interrupt
//
//*****************************************************************************
extern uint32_t
AES_getInterruptStatus(uint32_t base, uint32_t wrapperBase, bool intMask);

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

#endif // AES_H
