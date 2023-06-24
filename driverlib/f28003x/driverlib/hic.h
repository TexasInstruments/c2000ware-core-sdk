//###########################################################################
//
// FILE:   hic.h
//
// TITLE:  C28x Host Interface Controller (HIC) driver.
//
//###########################################################################
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
//###########################################################################

#ifndef HIC_H
#define HIC_H

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
//! \addtogroup hic_api HIC
//! \brief This module is used for Host Interface Controller(HIC) configuration
//! @{
//
//*****************************************************************************
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_hic.h"
#include "cpu.h"
#include "debug.h"

//
//Generic defines
//

//
//Number of Regions of Base addresses supported in HIC module
//
#define HIC_NUM_BASE_ADDRESS            8U //!< Number of Base Regions

//
//Number of Device to Host and Host to Device Buffer Registers of the module
//
#define HIC_NUM_BUFFER_REGS             16U //!< Number of D2H,H2D Buffers


//
//Used in HIC_enableHostInterface() API
//
#define HIC_HOST_INTERFACE_ENABLE       0x0AU //!< Host Interface Enable

//
//Used in HIC_enableLock() and HIC_disableLock() APIs
//
#define HIC_LOCK_WRITE_ENABLE_KEY       0x5A5AU //!< Write Enable Key
#define HIC_HOSTCR_WRITE_ENABLE_KEY     0xA5U //!< Host CR Reg Write Enable Key

//
//Flag for Unlocking in LOCK register
//
#define HIC_LOCK_UNLOCK             0x0U //!< Lock is Unlocked

//*****************************************************************************
//
//! Values that can be passed to HIC_setConfig() as \e flags or
//! used with HIC_getConfig() API return value parsing
//
//*****************************************************************************
//
//Enumerations for HICMODECR Register
//
#define HIC_MODE_DW_8BIT                0U //!< 8 Bit Mode
#define HIC_MODE_DW_16BIT               1U //!< 16 Bit Mode
#define HIC_MODE_DW_32BIT               2U //!< 32 Bit Mode

//
//For Read/Write Pin
//
#define HIC_MODE_RW_PIN_SEPARATE        0U    //!< RW Control Pins are separate
#define HIC_MODE_RW_PIN_SINGLE          0x10U //!< Single RnW Control Pin

//
//For Byte Enable BEn Pins
//
#define HIC_MODE_BEN_PRESENT            0x20U //!< Byte Enable Present
#define HIC_MODE_BEN_ABSENT             0U //!< Byte Enable not Present

//
//For Ready nRDY Pin
//
#define HIC_MODE_RDY_PRESENT            0x40U //!< nRDY Pin Present
#define HIC_MODE_RDY_ABSENT             0U    //!< nRDY Pin not Present

//
//For Host to Device Buffer Device Write Enable
//
#define HIC_MODE_H2DBUF_DEVWREN         0x100U  //!< H2D Buf Device Write Enable

//
//For Device to Host Buffer Host Write Enable
//
#define HIC_MODE_D2HBUF_HOST_WR_ENABLE  0x200U //!< D2H Buf Host Write Enable

//
//For Enabling Host Access to Device Region
//
#define HIC_MODE_DEVICE_HOST_ACCESS_ENABLE 0x400U //!< Host Access Enable

//
//For Enabling Host Write to EALLOWCTL Register
//
#define HIC_MODE_HOST_WREALLOW_ENABLE   0x800U //!< Host EALLOW Write Enable

//*****************************************************************************
//
//! Values that can be passed to HIC_setPinPolarity() API as \e flags or
//! used with HIC_getPinPolarity() API return value parsing
//
//*****************************************************************************
//
//For Pin Polarity Configuration
//Chip Select Pin (CS)
//
#define HIC_PIN_POLARITY_CS_HIGH        0x1U //!< Active High Chip Select
#define HIC_PIN_POLARITY_CS_LOW         0x0U //!< Active Low Chip Select

//
// Byte Enable Pin
//
#define HIC_PIN_POLARITY_BEN_HIGH       0x2U //!< Active High Byte Enable
#define HIC_PIN_POLARITY_BEN_LOW        0x0U //!< Active Low Byte Enable

//
// Output Enable OE Pin
//
#define HIC_PIN_POLARITY_OE_HIGH        0x4U //!< Active High Output Enable
#define HIC_PIN_POLARITY_OE_LOW         0x0U //!< Active Low Output Enable

//
// Write Enable (WE) Pin Polarity
//
#define HIC_PIN_POLARITY_WE_HIGH        0x8U //!< Active High Write Enable
#define HIC_PIN_POLARITY_WE_LOW         0x0U //!< Active Low Write Enable

//
// Ready Pin( RDY) Polarity
//
#define HIC_PIN_POLARITY_RDY_HIGH       0x10U //!< Active High Ready Pin
#define HIC_PIN_POLARITY_RDY_LOW        0x0U  //!< Active Low Ready Pin

//*****************************************************************************
//
//! Values that can be passed to HIC_configureHostAccessMode() API as \e config
//! or used with HIC_getHostAccessMode() API return value parsing
//
//*****************************************************************************
//
//Host Control Register
//
#define HIC_HOST_CONTROL_EALLOW_EN      1U //!< Host EALLOW Enable
#define HIC_HOST_CONTROL_EALLOW_DIS     0U //!< Host EALLOW Disable
//
//Access size of MMR registers
//
#define HIC_HOST_CONTROL_ACCSIZE_16BIT  0U //!< Device MMR Access size 16 bit
#define HIC_HOST_CONTROL_ACCSIZE_32BIT  2U //!< Device MMR Access size 32 bit
//
//Page selection via Pin/BASESEL Register
//
#define HIC_HOST_CONTROL_PAGESEL_REG    0U //!< Page selected via Register
#define HIC_HOST_CONTROL_PAGESEL_PIN    4U //!< Page selected via Pin

//*****************************************************************************
//
//! Values that can be passed to HIC_enableD2HInterrupt() API or
//! or used with HIC_disableD2HInterrupt() API to enable/disable interrupt
//! or with HIC_clearD2HInterrupt() API to clear interrupt
//
//*****************************************************************************
//
//SOC Internal Event Trigger (EVTTRIG)
//Refer Device TRM for details of the event(s)
//
#define HIC_EVTTRIG_EVENT_0      0x010000U //!< EVTTRIG0
#define HIC_EVTTRIG_EVENT_1      0x020000U //!< EVTTRIG1
#define HIC_EVTTRIG_EVENT_2      0x040000U //!< EVTTRIG2
#define HIC_EVTTRIG_EVENT_3      0x080000U //!< EVTTRIG3
#define HIC_EVTTRIG_EVENT_4      0x100000U //!< EVTTRIG4
#define HIC_EVTTRIG_EVENT_5      0x200000U //!< EVTTRIG5
#define HIC_EVTTRIG_EVENT_6      0x400000U //!< EVTTRIG6
#define HIC_EVTTRIG_EVENT_7      0x800000U //!< EVTTRIG7

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Returns the Revision of HIC Controller interface.
//!
//! This function returns the hardware revision of the Host Interface
//! controller module
//!
//! \return The Hardware Version number
//!         returns the content of HICREV register. Please refer to device TRM
//!         for field wise details.
//
//*****************************************************************************
static inline uint32_t
HIC_getRevision(void)
{
    return(HWREG(HIC_BASE + HIC_O_REV));
}

//*****************************************************************************
//
//! Enables the Host Access to the Device region and to the Mailbox
//!
//! \return none
//!
//! \n The Host interface Controller module provides two mechanisms of access
//! 1. Using Device Memory access, the host can access the memory directly
//!    read/write/poll for registers
//! 2. Using the Mailbox mechanism which can be used when the Host can write
//!     the parameters to the mailbox Host-to-Device buffer region and then
//!     trigger an interrupt to the Device. The HIC module with the
//!     other application running on device side can then be used
//!    to signal to the host, using the Device-to-Host buffer region
//! in response.
//!  This API enables the access to the Device region and Mailbox.
//!  This should be used as the first API in sequence of configuring
//! the HIC module.
//
//*****************************************************************************
static inline void
HIC_enableHostInterface(void)
{
    EALLOW;
    HWREG(HIC_BASE + HIC_O_GCR) = HIC_HOST_INTERFACE_ENABLE;
    EDIS;
}

//*****************************************************************************
//
//! Enables the Lock for the HIC module registers protected by Writes
//!
//! \n This API enables the lock, which protects the writes to registers
//! protected by Lock. Calling this API prevents writes to the write protected
//! registers.
//!
//! \return none
//
//*****************************************************************************
static inline void
HIC_enableLock(void)
{
    EALLOW;
    HWREG(HIC_BASE + HIC_O_LOCK) = (HIC_LOCK_LOCK |
                                 ((uint32_t)HIC_LOCK_WRITE_ENABLE_KEY <<
                                  HIC_LOCK_WRITE_ENABLE_KEY_S));
    EDIS;
}

//*****************************************************************************
//
//! Disables the Lock for the HIC module registers protected by Writes
//!
//! \n This API disables the lock(unlocks), which enables the writes
//!  to registers protected by Lock.
//! Calling this API enables writes to the write protected
//! registers.
//! This API must be called one time before calling any of these APIs
//! - HIC_setConfig()
//! - HIC_setPinPolarity()
//! - HIC_selectBaseAddress()
//!
//! \return None
//
//*****************************************************************************
static inline void
HIC_disableLock(void)
{

    EALLOW;
    HWREG(HIC_BASE + HIC_O_LOCK) = (HIC_LOCK_UNLOCK |
                                 ((uint32_t)HIC_LOCK_WRITE_ENABLE_KEY <<
                                  HIC_LOCK_WRITE_ENABLE_KEY_S));
    EDIS;
}

//*****************************************************************************
//
//! Sets the Host Interface Controller Configurations
//! \n This API configures the HICMODECR register for the selected configuration
//! HIC_disableLock() API should have been called prior to this API.
//!
//! \param flags specifies the ORed values of any of following flags.
//!
//! Any one of following values for Data Width
//! - \b HIC_MODE_DW_8BIT    -for 8bit Data
//! - \b HIC_MODE_DW_16BIT   -for 16bit Data
//! - \b HIC_MODE_DW_32BIT   -for 32bit Data
//!
//! Any one of following values for Read Write Pin
//! - \b HIC_MODE_RW_PIN_SEPARATE   - for Separate Read and Write Pin
//! - \b HIC_MODE_RW_PIN_SINGLE     - for Same Read and Write Pin
//!
//! Any one of following values for Byte Enable Pin configuration
//! - \b HIC_MODE_BEN_PRESENT   - for using Byte Enable Pin
//! - \b HIC_MODE_BEN_ABSENT    - for not using Byte Enable Pin
//!
//! Any one of following values for Ready Pin
//! - \b HIC_MODE_RDY_PRESENT   - for using Ready Pin for extended wait
//! - \b HIC_MODE_RDY_ABSENT    - for not using Extended Wait pin
//!
//! Other configurations:
//! - \b HIC_MODE_H2DBUF_DEVWREN    - for enabling Device access to
//! host to Device Buffers. If this is not enabled the device cannot write to
//! Host to Device buffers
//! - \b HIC_MODE_D2HBUF_HOST_WR_ENABLE - for enabling host access to
//! device to host buffers. If this is not enabled the host cannot write to
//! device to host buffers.
//! - \b HIC_MODE_DEVICE_HOST_ACCESS_ENABLE - for enabling access to the device
//! region. Only if this is enabled the regions selected by
//! Base select registers using the HIC_selectBaseAddress() API
//! shall be accessible.
//! Without this only the HIC registers and Mailbox registers will be
//! accessible for the host.
//! - \b HIC_MODE_HOST_WREALLOW_ENABLE - for enabling host access to write to
//! EALLOW bitfield using HIC_configureHostAccessMode() API. Without enabling
//! this HIC_configureHostAccessMode(HIC_HOSTCR_EALLOW_EN)
//!  will not work.

//
//! \return None
//
//*****************************************************************************
static inline void
HIC_setConfig(uint32_t flags)
{
    EALLOW;
    HWREG(HIC_BASE + HIC_O_MODECR) = flags;
    EDIS;
}

//*****************************************************************************
//
//! Returns the Host Interface Controller Configurations
//!
//! \return
//! 32-bit integer specifies the ORed values of following flags
//! Any one of following values for Data Width
//! - \b HIC_MODE_DW_8BIT    -for 8bit Data
//! - \b HIC_MODE_DW_16BIT   -for 16bit Data
//! - \b HIC_MODE_DW_32BIT   -for 32bit Data
//!
//! Following values for Other Configurations
//! - \b HIC_MODE_RW_PIN_SEPARATE/ HIC_MODE_RW_PIN_SINGLE  - for Read/Write Pin
//! - \b HIC_MODE_BEN_PRESENT/HIC_MODE_BEN_ABSENT  - for Byte Enable Pin Usage
//! - \b HIC_MODE_RDY_PRESENT/HIC_MODE_RDY_ABSENT  - for using Ready Pin for
//!  extended wait
//! - \b HIC_MODE_H2DBUF_DEVWREN- Device access to Host to Device Buffer Enabled
//! - \b HIC_MODE_D2HBUF_HOST_WR_ENABLE - Host access to Device to Host Buffer
//! enabled
//! - \b HIC_MODE_DEVICE_HOST_ACCESS_ENABLE - for enabling access to the device
//! - \b HIC_MODE_HOST_WREALLOW_ENABLE - for host access to write to EALLOW
//!
//! This API returns the current configuration of HIC module.
//! It can be used along with macros defined in hw_hic.h as below.
//! For querying the Data width use like in below examples
//! \n HIC_getConfig() & HIC_MODECR_DW_MODE_M == HIC_MODE_DW_8BIT for Data width
//! \n HIC_getConfig() & HIC_MODECR_RW_MODE == HIC_MODE_RW_PIN_SINGLE for RW Pin
//! \n HIC_getConfig() & HIC_MODECR_BEN_PRESENT == HIC_MODE_BEN_PRESENT
//! for BE Pin
//
//*****************************************************************************
static inline uint32_t
HIC_getConfig(void)
{

    return(HWREG(HIC_BASE + HIC_O_MODECR));
}

//*****************************************************************************
//
//! Sets the Host Interface Controller Pin Polarity.
//! This API configures the HICPINPOLCR register for the selected configuration.
//! HIC_disableLock() API should have been called prior to this API.
//!
//! \param flags specifies the ORed values of any of following flags
//!
//! Any one of following values for Chip Select Pin
//! - \b HIC_PIN_POLARITY_CS_HIGH   - for Active High Chip Select Pin
//! - \b HIC_PIN_POLARITY_CS_LOW    - for Active Low Chip Select Pin
//!
//! Any one of following values for Byte Enable Pin configuration
//! - \b HIC_PIN_POLARITY_BEN_HIGH   - for Active High Byte Enable
//! - \b HIC_PIN_POLARITY_BEN_LOW    - for Active Low Byte Enable
//!
//! Any one of following values for Output Enable Pin
//! - \b HIC_PIN_POLARITY_OE_HIGH   - for Active High Output Enable
//! - \b HIC_PIN_POLARITY_OE_LOW    - for Active Low Output Enable
//!
//! Any one of following values for Write Enable Pin
//! - \b HIC_PIN_POLARITY_WE_HIGH   - for Active High Write Enable
//! - \b HIC_PIN_POLARITY_WE_LOW    - for Active Low Write Enable
//!
//! Any one of following values for Ready Pin
//! - \b HIC_PIN_POLARITY_RDY_HIGH   - for Active High Write Enable
//! - \b HIC_PIN_POLARITY_RDY_LOW    - for Active Low Write Enable
//!
//! \return None
//
//*****************************************************************************
static inline void
HIC_setPinPolarity(uint16_t flags)
{

    EALLOW;
    HWREG(HIC_BASE + HIC_O_PINPOLCR) = flags;
    EDIS;
}

//*****************************************************************************
//
//! Returns the Host Interface Controller Pin Polarity Configurations
//!
//! This API returns the HICPINPOLCR register for the selected configuration
//!
//! \return
//! 32-bit integer specifies the ORed values of any of following flags
//! Following values for corresponding Pin Configuration
//! - \b HIC_PIN_POLARITY_CS_HIGH/ HIC_PIN_POLARITY_CS_HIGH  - for CS Pin
//! - \b HIC_PIN_POLARITY_BEN_HIGH/HIC_PIN_POLARITY_BEN_HIGH- for
//!    Byte Enable pin
//! - \b HIC_PIN_POLARITY_OE_HIGH/HIC_PIN_POLARITY_OE_LOW  - for OE Pin
//! - \b HIC_PIN_POLARITY_WE_HIGH/HIC_PIN_POLARITY_WE_LOW- for WE Pin
//! - \b HIC_PIN_POLARITY_RDY_HIGH/HIC_PIN_POLARITY_RDY_LOW - for RDY Pin
//!
//! This API returns the Pin Polarity.This can be used with the macros defined
//! in hw_hic.h as shown below
//! HIC_getPinPolarity & HIC_PINPOLCR_BEN_POL == HIC_PIN_POLARITY_BEN_HIGH for
//!   checking the status of Byte Enable Pin Polarity
//
//*****************************************************************************
static inline uint32_t
HIC_getPinPolarity(void)
{

    return(HWREG(HIC_BASE + HIC_O_PINPOLCR));
}

//*****************************************************************************
//
//! Selects the Base Address for the device memory access
//!
//! \param selectIndex specifies the index of Base address in the Base Address
//!        regions can vary from 0 to HIC_NUM_BASE_ADDRESS-1
//!
//! The Device memory region will be accessible by the region selected in this
//! API. Also look at HIC_configureHostAccessMode(HIC_HOSTCR_PAGESEL)
//!
//! \return None
//
//*****************************************************************************
static inline void
HIC_selectBaseAddress(uint16_t selectIndex)
{
    //
    //Check the arguments.
    //
    ASSERT(selectIndex < HIC_NUM_BASE_ADDRESS);

    HWREG(HIC_BASE + HIC_O_BASESEL) = selectIndex;
}

//*****************************************************************************
//
//! Returns the Selected Base address index for the device memory access
//!
//! The Device memory region will be accessible by the region selected in this
//! API. Also look at HIC_configureHostAccessMode(HIC_HOSTCR_PAGESEL)
//!
//! \return selected index of Base address in the Base Address
//!         regions. can vary from 0 to HIC_NUM_BASE_ADDRESS-1
//
//*****************************************************************************
static inline uint16_t
HIC_getSelectedBaseAddressIndex(void)
{
    return(HWREGH(HIC_BASE + HIC_O_BASESEL));
}

//*****************************************************************************
//
//! Configures the Host Access modes to the device region
//!
//! \param config logical OR of the following values
//! - \b HIC_HOSTCR_EALLOW_EN for enabling module writes to EALLOW Protected
//!      registers
//! - either of
//! <b>HIC_HOST_CONTROL_ACCSIZE_16BIT/HIC_HOST_CONTROL_ACCSIZE_32BIT </b>
//!    to select 16 bit or 32 bit device side master port accesses
//! - either of
//! <b> HIC_HOST_CONTROL_PAGESEL_REG/HIC_HOST_CONTROL_PAGESEL_PIN </b>
//!    to select Page/Region selection based on PAGESEL register
//!    programmed using HIC_selectBaseAddress()API or the PAGESEL Pin
//!
//! \return None
//
//*****************************************************************************
static inline void
HIC_configureHostAccessMode(uint16_t config)
{

    //
    //Needs a key to be written for the write to go through
    //
    HWREG(HIC_BASE + HIC_O_HOSTCR) = (config |
                                    HIC_HOSTCR_WRITE_ENABLE_KEY <<
                                    HIC_HOSTCR_HKEY_S);
}

//*****************************************************************************
//
//! Provides the Host Access modes configured currently
//!
//! \return Host Access mode value as configured
//!         HIC_configureHostAccessMode()
//!  API which is a logical OR of
//! - \b HIC_HOSTCR_EALLOW_EN for enabling module writes to EALLOW Protected
//!      registers
//! - either of
//! <b> HIC_HOST_CONTROL_ACCSIZE_16BIT/HIC_HOST_CONTROL_ACCSIZE_32BIT </b>
//!    for selected 16 bit or 32 bit device side master port accesses
//! - either of
//! <b> HIC_HOST_CONTROL_PAGESEL_REG/HIC_HOST_CONTROL_PAGESEL_PIN </b>
//!    for selected Page/Region selection based on PAGESEL register
//!     programmed using HIC_selectBaseAddress()API or the PAGESEL Pin
//!
//! This API can be used with few Macros defined in hw_hic.h as below
//! (HIC_getAccessMode() & HIC_HOSTCR_ACCSIZE) == HIC_HOST_CONTROL_ACCSIZE_32BIT
//! for Access size checking. Similarly it can be used for other bit fields.
//
//*****************************************************************************
static inline uint32_t
HIC_getHostAccessMode(void)
{

    //
    //Returns the lower 16 bits that contains the configuration
    //
    return(HWREGH(HIC_BASE + HIC_O_HOSTCR));
}

//*****************************************************************************
//
//! Returns the Host and Device side Status when an Error happened on interface
//!
//! \return returns the logical OR of the following
//! - 8 bit Host to Device Error Address when Host to Device Error happens
//! - 3 bit Base select value when Host to Device Error happens
//! - 8 bit Device to Host Error Address when Device to Host Error happens
//! - 3 bit Base select value when Device to Host Error Happens.
//! \n Please refer to TRM HICERRADDR register for more details on this.
//
//*****************************************************************************
static inline uint32_t
HIC_getErrorAddress(void)
{
    return(HWREG(HIC_BASE + HIC_O_ERRADDR));
}

//*****************************************************************************
//
//! Returns the token written by the token written onto the Host to Device Token
//!
//! \return the 32 bit Token value written into the register
//!
//! This API can be used while using the Mailbox mechanism.
//
//*****************************************************************************
static inline uint32_t
HIC_getH2DToken(void)
{

    return(HWREG(HIC_BASE + HIC_O_H2DTOKEN));
}

//*****************************************************************************
//
//! Writes the Token to the Host from Device
//!
//! \param token is the 32 bit token value to be written. It could be used
//! to denote the number of bytes written on to the Device-to-Host buffer
//!
//! \return None
//!
//! This API can be used while using the Mailbox mechanism.
//! Writing to this register could be used to trigger an interrupt
//! to the Host using the Device to Host
//! interrupt line(D2HINT) of the module.
//! It can be used to interrupt the external host.
//
//*****************************************************************************
static inline void
HIC_setD2HToken(uint32_t token)
{

    HWREG(HIC_BASE + HIC_O_D2HTOKEN) = token;
}

//*****************************************************************************
//
//! Returns the token written by the token written onto the Device to Host Token
//!
//! \return the 32 bit Token value written into the register
//!
//! This API can be used while using the Mailbox mechanism.
//
//*****************************************************************************
static inline uint32_t
HIC_getD2HToken(void)
{
    return(HWREG(HIC_BASE + HIC_O_D2HTOKEN));
}

//*****************************************************************************
//
//! Configures the Base Address of the region
//!
//! \param index specifies the index of the Device Region to be configured
//!        can be from 0 to HIC_NUM_BASE_ADDRESS-1
//!
//! \param baseAddress the 32 bit base address of the device region
//!        being configured
//!
//! The device memory which HIC module can access can be divided into multiple
//! 256 byte regions.
//! For Example: GSRAM in Region 0,
//!              ADC registers in Region 1
//!              FSI registers in Region 2,etc
//! This API helps to configure the base address for each region
//! The HIC address Pin can then be used to offset into the specific region
//! by the host
//!
//! \return None
//
//*****************************************************************************
static inline void
HIC_setBaseAddress(uint16_t index,
                uint32_t baseAddress)
{
    //
    //Check the arguments.
    //
    ASSERT(index < HIC_NUM_BASE_ADDRESS);

    EALLOW;
    HWREG(HIC_BASE + HIC_O_DBADDR0 + (index * 2)) = baseAddress;
    EDIS;
}

//*****************************************************************************
//
//! Returns the Base Address configured for the region
//!
//! \param index specifies the index of the Device Region to be configured
//!        can be from 0 to HIC_NUM_BASE_ADDRESS-1
//!
//! Returns the configured base address for the Region index provided
//!
//! \return 32 bit base address configured for the region
//
//*****************************************************************************
static inline uint32_t
HIC_getBaseAddress(uint16_t index)
{
    //
    //Check the arguments.
    //
    ASSERT(index < HIC_NUM_BASE_ADDRESS);

    return(HIC_BASE + HIC_O_DBADDR0 + (index * 2));
}

//*****************************************************************************
//
//! Enables the Interrupts from Host to Device
//!
//! \param flags specifies the logical ORed values below
//! - \b HIC_H2DINTEN_H2D_INTEN - Data Ready interrupt Enable
//! - \b HIC_H2DINTEN_BUSERR_INTEN - Bus error Interrupt Enable
//! - \b HIC_H2DINTEN_ILLWR_INTEN - Illegal Write Interrupt Enable
//! - \b HIC_H2DINTEN_ILLRD_INTEN - Illegal Read Interrupt Enable
//!
//! Enables the specified interrupts. This will result in a HIC interrupt
//! generated to the C28x core.
//!
//! \return None
//
//*****************************************************************************
static inline void
HIC_enableH2DInterrupt(uint32_t flags)
{

    HWREG(HIC_BASE + HIC_O_H2DINTEN) |= flags;
}

//*****************************************************************************
//
//! Disables the Interrupts from Host to Device
//!
//! \param flags specifies the logical ORed values below
//! - \b HIC_H2DINTEN_H2D_INTEN - Data Ready interrupt Enable
//! - \b HIC_H2DINTEN_BUSERR_INTEN - Bus error Interrupt Enable
//! - \b HIC_H2DINTEN_ILLWR_INTEN - Illegal Write Interrupt Enable
//! - \b HIC_H2DINTEN_ILLRD_INTEN - Illegal Read Interrupt Enable
//!
//! Disables the interrupt flags specified
//!
//! \return None
//
//*****************************************************************************
static inline void
HIC_disableH2DInterrupt(uint32_t flags)
{

    HWREG(HIC_BASE + HIC_O_H2DINTEN) &= ~flags;
}

//*****************************************************************************
//
//! Gives the status of Host to Device interrupts
//!
//! \return 32bit flag with the logical ORed values below
//! - \b HIC_H2DINTFLG_H2D_FLG - Data Ready interrupt Status
//! - \b HIC_H2DINTFLG_BUSERR_FLG - Bus error Interrupt Status
//! - \b HIC_H2DINTFLG_ILLWR_FLG - Illegal Write Interrupt Status
//! - \b HIC_H2DINTFLG_ILLRD_FLG - Illegal Read Interrupt Status.
//!
//! \n The Flag if Set indicates that the corresponding Interrupt is active
//! (has occured)
//
//*****************************************************************************
static inline uint32_t
HIC_getH2DInterruptStatus(void)
{

    return(HWREG(HIC_BASE + HIC_O_H2DINTFLG));
}

//*****************************************************************************
//
//! Clears the Interrupts from Host to Device
//!
//! \param flags specifies the logical ORed values below to be cleared
//! - \b HIC_H2DINTCLR_H2D_CLR - Data Ready interrupt Clear
//! - \b HIC_H2DINTCLR_BUSERR_CLR - Bus error Interrupt Clear
//! - \b HIC_H2DINTCLR_ILLWR_CLR - Illegal Write Interrupt Clear
//! - \b HIC_H2DINTCLR_ILLRD_CLR - Illegal Read Interrupt Clear
//!
//! Clears the interrupt flags specified
//!
//! \return None
//
//*****************************************************************************
static inline void
HIC_clearH2DInterrupt(uint32_t flags)
{

    HWREG(HIC_BASE + HIC_O_H2DINTCLR) = flags;
}

//*****************************************************************************
//
//! Forces the Interrupts from Host to Device
//!
//! \param flags specifies the logical ORed values below to be Forced
//! - \b HIC_H2DINTFRC_H2D_INTFRC - Data Ready interrupt Force
//! - \b HIC_H2DINTFRC_BUSERR_INTFRC - Bus error Interrupt Force
//! - \b HIC_H2DINTFRC_ILLWR_INTFRC - Illegal Write Interrupt Force
//! - \b HIC_H2DINTFRC_ILLRD_INTFRC - Illegal Read Interrupt Force
//!
//! Forces the interrupt flags specified. Can be used for Debug purpose.
//!
//! \return None
//
//*****************************************************************************
static inline void
HIC_forceH2DInterrupt(uint32_t flags)
{

    HWREG(HIC_BASE + HIC_O_H2DINTFRC) = flags;
}

//*****************************************************************************
//
//! Enables the Interrupts from Device to Host
//!
//! \param flags specifies the logical ORed values below
//! - \b HIC_D2HINTEN_D2H_INTEN - Data Ready interrupt Enable
//! - \b HIC_D2HINTEN_BUSERR_INTEN - Bus error Interrupt Enable
//! - \b HIC_D2HINTEN_ILLWR_INTEN - Illegal Write Interrupt Enable
//! - \b HIC_D2HINTEN_ILLRD_INTEN - Illegal Read Interrupt Enable
//! - \b HIC_D2HINTEN_ACCVIO_INTEN - Access Violation Interrupt Enable
//! - \b Event Trigger interrupt flags - The higher 16 bits when Set will enable
//!  corresponding D2H interrupts. Refer TRM for details.
//!
//! Enables the specified interrupts. This will result in a HIC interrupt
//! generated to the Host(D2HINT).
//!
//! \return None
//
//*****************************************************************************
static inline void
HIC_enableD2HInterrupt(uint32_t flags)
{

    HWREG(HIC_BASE + HIC_O_D2HINTEN) |= flags;
}

//*****************************************************************************
//
//! Disables the Interrupts from Device to Host
//!
//! \param flags specifies the logical ORed values below
//! - \b HIC_D2HINTEN_D2H_INTEN - Data Ready interrupt Enable
//! - \b HIC_D2HINTEN_BUSERR_INTEN - Bus error Interrupt Enable
//! - \b HIC_D2HINTEN_ILLWR_INTEN - Illegal Write Interrupt Enable
//! - \b HIC_D2HINTEN_ILLRD_INTEN - Illegal Read Interrupt Enable
//! - \b HIC_D2HINTEN_ACCVIO_INTEN - Access Violation Interrupt Enable
//! - <b> Event Trigger interrupt flags </b> - The higher 16 bits when set will
//! disable corresponding D2H interrupts. Refer TRM for details.
//!
//! Disables the interrupt flags specified
//!
//! \return None
//
//*****************************************************************************
static inline void
HIC_disableD2HInterrupt(uint32_t flags)
{

    HWREG(HIC_BASE + HIC_O_D2HINTEN) &= ~flags;
}

//*****************************************************************************
//
//! Gives the status of Device to Host interrupts
//!
//! \return 32bit flag with the logical ORed values below
//! - \b HIC_D2HINTFLG_D2H_FLG - Data Ready interrupt Status
//! - \b HIC_D2HINTFLG_BUSERR_FLG - Bus error Interrupt Status
//! - \b HIC_D2HINTFLG_ILLWR_FLG - Illegal Write Interrupt Status
//! - \b HIC_D2HINTFLG_ILLRD_FLG - Illegal Read Interrupt Status
//! - \b HIC_D2HINTFLG_ACCVIO_FLG - Access Violation Interrupt Status
//! - <b> Event Trigger Interrupt Flags </b>- The higher 16 bits give
//! the status of event Trigger Interrupt flags.
//! Refer TRM for the sources of these interrupts.
//!
//!  The Flag if Set indicates that the corresponding Interrupt is active
//! (has occurred)
//
//*****************************************************************************
static inline uint32_t
HIC_getD2HInterruptStatus(void)
{

    return(HWREG(HIC_BASE + HIC_O_D2HINTFLG));
}

//*****************************************************************************
//
//! Clears the Interrupts from Host to Device
//!
//! \param flags specifies the logical ORed values below to be cleared
//! - \b HIC_D2HINTCLR_D2H_CLR - Data Ready interrupt Clear
//! - \b HIC_D2HINTCLR_BUSERR_CLR - Bus error Interrupt Clear
//! - \b HIC_D2HINTCLR_ILLWR_CLR - Illegal Write Interrupt Clear
//! - \b HIC_D2HINTCLR_ILLRD_CLR - Illegal Read Interrupt Clear
//! - \b HIC_D2HINTCLR_ACCVIO_CLR - Access Violation Interrupt Clear
//! - <b> Event Trigger Interrupt Clear Flags </b> - The higher 16 bits
//! indicates event trigger flags to be cleared.
//! Refer TRM for the sources of these interrupts.
//!
//! Clears the interrupt flags specified
//!
//! \return None
//
//*****************************************************************************
static inline void
HIC_clearD2HInterrupt(uint32_t flags)
{

    HWREG(HIC_BASE + HIC_O_D2HINTCLR) = flags;
}

//*****************************************************************************
//
//! Forces the Interrupts from Host to Device
//!
//! \param flags specifies the logical ORed values below to be Forced
//! - \b HIC_D2HINTFRC_D2H_INTFRC - Data Ready interrupt Force
//! - \b HIC_D2HINTFRC_BUSERR_INTFRC - Bus error Interrupt Force
//! - \b HIC_D2HINTFRC_ILLWR_INTFRC - Illegal Write Interrupt Force
//! - \b HIC_D2HINTFRC_ILLRD_INTFRC - Illegal Read Interrupt Force
//! - \b HIC_D2HINTFRC_ACCVIO_INTFRC - Access violation Interrupt Force
//! - <b> Event Trigger Interrupt Force Flags </b> - The higher 16 bits
//! indicates event trigger flags to be cleared.
//! Refer TRM for the sources of these interrupts.
//!
//! Forces the interrupt flags specified. Can be used for Debug purposes.
//!
//! \return None
//
//*****************************************************************************
static inline void
HIC_forceD2HInterrupt(uint32_t flags)
{

    HWREG(HIC_BASE + HIC_O_D2HINTFRC) = flags;
}

//*****************************************************************************
//
//! Returns the Address when Access violation happened
//!
//! \return returns the 32 bit address when the Access violation happened
//!
//! While the HIC module internal access port accesses a memory, if there is
//! an access violation, the module updates the address in this register.
//
//*****************************************************************************
static inline uint32_t
HIC_getAccessViolationAddress(void)
{

    return(HWREG(HIC_BASE + HIC_O_ACCVIOADDR));
}

//*****************************************************************************
//
//! Returns the Host to Device Buffer for the offset specified
//!
//! \param offset specifies the offset of the H2D buffer
//!         can vary from 0 to HIC_NUM_BUFFER_REGS-1
//!
//! \return returns the 32 bit content of the Host to Device buffer.
//!
//! The Host to Device buffer can be used to implement a communication
//! scheme on which the Host writes the data to sent to the Control peripherals.
//! The MCU can pick it up and stream it over control peripherals.
//! The Device to Host Buffer can be used to write the response back.
//! The External host need not continuously wait for the data/response.
//
//*****************************************************************************
static inline uint32_t
HIC_readH2DBuffer(uint16_t offset)
{
    //
    //Check the arguments.
    //
    ASSERT(offset < HIC_NUM_BUFFER_REGS);

    return(HWREG(HIC_BASE + HIC_O_H2D_BUF0 + (offset * 2)));
}

//*****************************************************************************
//
//! Writes to the Host to Device buffer
//!
//! \param offset specifies the offset of the H2D buffer
//!         can vary from 0 to HIC_NUM_BUFFER_REGS-1
//! \param data the 32bit data to be written onto the buffer
//!
//! \return none
//!
//! This API should be used only when the Device write to Host buffer
//! is enabled, using HIC_setConfig(HIC_MODECR_H2DBUF_DEVWREN) API.
//
//*****************************************************************************
static inline void
HIC_writeH2DBuffer(uint16_t offset, uint32_t data)
{
    //
    //Check the arguments.
    //
    ASSERT(offset < HIC_NUM_BUFFER_REGS);

    HWREG(HIC_BASE + HIC_O_H2D_BUF0 + (offset * 2)) = data;
}

//*****************************************************************************
//
//! Clears the Host to Device buffer (by making it Zero)
//!
//! \param offset specifies the offset of the H2D buffer
//!         can vary from 0 to HIC_NUM_BUFFER_REGS-1
//!
//! \return none
//!
//! This API should be used only when the Device write to Host buffer
//! is enabled, using HIC_setConfig(HIC_MODECR_H2DBUF_DEVWREN) API.
//! This API can be used to clear the content of H2D Buffer
//
//*****************************************************************************
static inline void
HIC_clearH2DBuffer(uint16_t offset)
{
    //
    //Check the arguments.
    //
    ASSERT(offset < HIC_NUM_BUFFER_REGS);

    HWREG(HIC_BASE + HIC_O_H2D_BUF0 + (offset * 2)) = 0;
}

//*****************************************************************************
//
//! Returns the Device to Host Buffer for the offset specified
//!
//! \param offset specifies the offset of the D2H buffer
//!         can vary from 0 to HIC_NUM_BUFFER_REGS-1
//!
//! \return returns the 32 bit content of the Device to Host buffer
//!
//! The Device to Host Buffer can be used to write the response back to host
//! The External host need not continuously wait for the data/response.
//
//*****************************************************************************
static inline uint32_t
HIC_readD2HBuffer(uint16_t offset)
{
    //
    //Check the arguments.
    //
    ASSERT(offset < HIC_NUM_BUFFER_REGS);

    return(HWREG(HIC_BASE + HIC_O_D2H_BUF0 + (offset * 2)));
}

//*****************************************************************************
//
//! Writes to the Device to Host buffer
//!
//! \param offset specifies the offset of the D2H buffer
//!         can vary from 0 to HIC_NUM_BUFFER_REGS-1
//! \param data the 32bit data to be written onto the buffer
//!
//! \return none
//
//*****************************************************************************
static inline void
HIC_writeD2HBuffer(uint16_t offset, uint32_t data)
{
    //
    //Check the arguments.
    //
    ASSERT(offset < HIC_NUM_BUFFER_REGS);

    HWREG(HIC_BASE + HIC_O_D2H_BUF0 + (offset * 2)) = data;
}

//*****************************************************************************
//
//! Clears the Device to Host buffer (by making it Zero)
//!
//! \param offset specifies the offset of the D2H buffer
//!         can vary from 0 to HIC_NUM_BUFFER_REGS-1
//!
//! \return none
//!
//! This API can be used to clear the content of D2H Buffer
//
//*****************************************************************************
static inline void
HIC_clearD2HBuffer(uint16_t offset)
{
    //
    //Check the arguments.
    //
    ASSERT(offset < HIC_NUM_BUFFER_REGS);

    HWREG(HIC_BASE + HIC_O_D2H_BUF0 + (offset * 2)) = 0U;
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

#endif // HIC_H
