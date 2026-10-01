//#############################################################################
//
// FILE:   drv8329.h
//
// TITLE:  Drivers for DRV8329 with generic communication interface
//
//#############################################################################
// $Copyright:
// Copyright (C) 2026 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef DRV8329_H
#define DRV8329_H

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
//! \addtogroup drv8329_api DRV8329 APIs
//! \brief This module is used for DRV8329 configurations.
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "hw_drv8329.h"

//*****************************************************************************
//
// Defines for IC_CTRL register default config values and masks
//
//*****************************************************************************

#define DRV8329_CTRL1_REG_DEFAULT_CONFIG        0x00
#define DRV8329_CTRL2_REG_DEFAULT_CONFIG        0x00

#define DRV8329_CTRL1_REG_DEFAULT_MASK          0xFE
#define DRV8329_CTRL2_REG_DEFAULT_MASK          0x78

//*****************************************************************************
//
// GATE DRIVER FAULT REPORT Bit positions
//
// PWR_ON | OTS_FAULT | OCP_VDS_FAULT | OCP_SNS_FAULT | BST_UV_FAULT | GVDD_UV_FLT | DRVOFF | FAULT |
// RSVD   | RSVD      | RSVD          | RSVD          | RSVD         | RSVD        | RSVD   | RSVD  |
// RSVD   | RSVD      | RSVD          | RSVD          | RSVD         | RSVD        | RSVD   | RSVD  |
// RSVD   | RSVD      | RSVD          | RSVD          | RSVD         | RSVD        | RSVD   | RSVD  |
//
//*****************************************************************************
typedef union
{
    struct gateDrvFlt
    {
        uint32_t
        rsvd1       :24,
        fault_common:1,
        drvoff      :1,
        gvdd_uv_flt :1,
        bst_uv_flt  :1,
        ocp_sns_flt :1,
        ocp_vds_flt :1,
        ots_flt     :1,
        pwr_on      :1;

   }b;
    uint32_t w;
} DRV8329_FAULT_STATUS_T;

//*****************************************************************************
//
// GATE DRIVER FAULT REPORT Bit Positions, Masks & Initialization Values
//
//*****************************************************************************

#define DRV8329_FAULT_STATUS_MASK           0xFF000000
#define DRV8329_FAULT_STATUS_DEFAULT        0x80000000

#define DRV8329_FAULT_STATUS_PWR_ON         0x80000000
#define DRV8329_FAULT_STATUS_OTS            0x40000000
#define DRV8329_FAULT_STATUS_OCP_VDS        0x20000000
#define DRV8329_FAULT_STATUS_OCP_SNS        0x10000000
#define DRV8329_FAULT_STATUS_BST_UV         0x08000000
#define DRV8329_FAULT_STATUS_GVDD_UV        0x04000000
#define DRV8329_FAULT_STATUS_DRVOFF         0x02000000
#define DRV8329_FAULT_STATUS_FAULT_COMMON   0x01000000

//*****************************************************************************
//
// DRV8329 Configuration Register Set 1 - Bit Positions
// Covers Registers CTRL1 and CTRL2
//
//*****************************************************************************
typedef union
{
    struct drv8329Cfg1
    {
        uint32_t
        selVdsLvl       : 4,
        selVdsSpi       : 1,
        disVdsFlt       : 1,
        disSnsFlt       : 1,
        disDrv          : 1,
        disTcp          : 1,
        otsAutoRecover  : 1,
        disBstFlt       : 1,
        rsvd1           : 20,
        parity          : 1;
   }b;
    uint32_t w;
} DRV8329_CFG1_T;

//*****************************************************************************
//
// DRV8329 Configuration Register Set 1 -  Bit Positions & Masks
// Covers Registers CTRL1 and CTRL2
//
//*****************************************************************************

#define GD1_CTRL1_MASK                  0x0000007F
#define GD1_CTRL1_SHIFT                 0

#define GD1_CTRL2_MASK                  0x00000078
#define GD1_CTRL2_SHIFT                 7

//*****************************************************************************
//
// DRV8329 Register Configuration
//
//*****************************************************************************
typedef struct drv8329Configuration
{
    DRV8329_CFG1_T    gateDrvCfg1;
} DRV8329_CONFIG_T;

#ifdef DEBUG
//*****************************************************************************
//
// DRV8329 STATUS Register
//
//*****************************************************************************
typedef union
{
    struct drv8329StatusReg
    {
        uint16_t
        fault           : 1,    //!< Any fault condition active
        drvoff          : 1,    //!< Gate driver outputs disabled
        gvdd_uv_flt     : 1,    //!< GVDD undervoltage fault
        bst_uv_flt      : 1,    //!< Bootstrap undervoltage fault
        ocp_sns_flt     : 1,    //!< VSENSE overcurrent fault
        ocp_vds_flt     : 1,    //!< VDS overcurrent fault
        ots_flt         : 1,    //!< Overtemperature shutdown fault
        pwr_on          : 1,    //!< Power-on indicator
        rsvd            : 8;
    } b;
    uint16_t w;
} DRV8329_STATUS_REG_T;

//*****************************************************************************
//
// DRV8329 CTRL1 Register
//
//*****************************************************************************
typedef union
{
    struct drv8329Ctrl1Reg
    {
        uint16_t
        rsvd1           : 1,    //!< Reserved
        sel_vdslvl      : 4,    //!< VDS overcurrent threshold level
        sel_vds_spi     : 1,    //!< Enable VDS level selection via SPI
        dis_vds_flt     : 1,    //!< Disable VDS overcurrent fault
        dis_sns_flt     : 1,    //!< Disable VSENSE overcurrent fault
        rsvd2           : 8;
    } b;
    uint16_t w;
} DRV8329_CTRL1_REG_T;

//*****************************************************************************
//
// DRV8329 CTRL2 Register
//
//*****************************************************************************
typedef union
{
    struct drv8329Ctrl2Reg
    {
        uint16_t
        rsvd1           : 3,    //!< Reserved
        dis_drv         : 1,    //!< Disable gate driver outputs
        dis_tcp         : 1,    //!< Disable trickle charge pump
        ots_auto_recover: 1,    //!< Enable OTS auto-recovery
        dis_bst_flt     : 1,    //!< Disable bootstrap undervoltage fault
        rsvd2           : 9;
    } b;
    uint16_t w;
} DRV8329_CTRL2_REG_T;

//*****************************************************************************
//
// DRV8329 Register Readback Data
//
//*****************************************************************************
typedef struct drv8329Registers
{
    DRV8329_STATUS_REG_T  status;   //!< STATUS register readback
    DRV8329_CTRL1_REG_T   ctrl1;    //!< CTRL1 register readback
    DRV8329_CTRL2_REG_T   ctrl2;    //!< CTRL2 register readback
} DRV8329_REGS_T;
#endif // DEBUG

//*****************************************************************************
//
//! Values that can be passed to DRV8329_setVdsLevel() as the \e level parameter.
//! These values set the MOSFET VDS overcurrent monitor threshold voltage.
//
//*****************************************************************************
typedef enum
{
    DRV8329_VDSLVL_0_06V = 0x00U,   //!< VDS threshold = 0.06V
    DRV8329_VDSLVL_0_12V = 0x01U,   //!< VDS threshold = 0.12V
    DRV8329_VDSLVL_0_18V = 0x02U,   //!< VDS threshold = 0.18V
    DRV8329_VDSLVL_0_24V = 0x03U,   //!< VDS threshold = 0.24V
    DRV8329_VDSLVL_0_30V = 0x04U,   //!< VDS threshold = 0.3V
    DRV8329_VDSLVL_0_36V = 0x05U,   //!< VDS threshold = 0.36V
    DRV8329_VDSLVL_0_42V = 0x06U,   //!< VDS threshold = 0.42V
    DRV8329_VDSLVL_0_48V = 0x07U,   //!< VDS threshold = 0.48V
    DRV8329_VDSLVL_0_60V = 0x08U,   //!< VDS threshold = 0.6V
    DRV8329_VDSLVL_0_80V = 0x09U,   //!< VDS threshold = 0.8V
    DRV8329_VDSLVL_1_00V = 0x0AU,   //!< VDS threshold = 1.0V
    DRV8329_VDSLVL_1_20V = 0x0BU,   //!< VDS threshold = 1.2V
    DRV8329_VDSLVL_1_40V = 0x0CU,   //!< VDS threshold = 1.4V
    DRV8329_VDSLVL_1_60V = 0x0DU,   //!< VDS threshold = 1.6V
    DRV8329_VDSLVL_1_80V = 0x0EU,   //!< VDS threshold = 1.8V
    DRV8329_VDSLVL_2_00V = 0x0FU    //!< VDS threshold = 2.0V
} DRV8329_VdsLevel;

//*****************************************************************************
//
//! Values that can be passed to DRV8329_setOtsRecoveryMode() as the \e option
//! parameter.
//
//*****************************************************************************
typedef enum
{
    DRV8329_OTS_LATCH_FAULT     = 0x00, //!< Latch fault on OTS
    DRV8329_OTS_AUTO_RECOVER    = 0x20, //!< Enable OTS Auto-Recovery
} DRV8329_OtsRecoveryMode;


//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Clear DRV8329 faults
//!
//! This function clears the latched faults in the DRV8329
//!
//! DRV_ClearFaults() maps directly to this function
//! 
//! \return None
//
//*****************************************************************************
void DRV8329_clearFaults(void);

//*****************************************************************************
//
//! Disable all DRV8329 Gate Driver Outputs
//!
//! This function disables all the DRV8329 outputs (GHx and GLx)
//!
//! DRV_DisableDrv() maps directly to this function
//!
//! \return None
//
//*****************************************************************************
void DRV8329_disableDrv(void);

//*****************************************************************************
//
//! Enable all DRV8329 Gate Driver Outputs
//!
//! This function enables all the DRV8329 outputs (GHx and GLx)
//!
//! DRV_EnableDrv() maps directly to this function
//!
//! \return None
//
//*****************************************************************************
void DRV8329_enableDrv(void);

//*****************************************************************************
//
//! Disable VSENSE Overcurrent Protection fault detection
//!
//! This function disables the RSHUNT OCP fault detection
//!
//! DRV_DisableSnsFault() maps directly to this function
//!
//! \return None
//
//*****************************************************************************
void DRV8329_disableSnsFault(void);

//*****************************************************************************
//
//! Enable VSENSE Overcurrent Protection fault detection
//!
//! This function enables the RSHUNT OCP fault detection
//!
//! DRV_EnableSnsFault() maps directly to this function
//!
//! \return None
//
//*****************************************************************************
void DRV8329_enableSnsFault(void);

//*****************************************************************************
//
//! Disable VDS Overcurrent Protection fault detection
//!
//! This function disables the VDS OCP fault detection
//!
//! DRV_DisableVdsFault() maps directly to this function
//!
//! \return None
//
//*****************************************************************************
void DRV8329_disableVdsFault(void);

//*****************************************************************************
//
//! Enable VDS Overcurrent Protection fault detection
//!
//! This function enables the VDS OCP fault detection
//!
//! DRV_EnableVdsFault() maps directly to this function
//!
//! \return None
//
//*****************************************************************************
void DRV8329_enableVdsFault(void);

//*****************************************************************************
//
//! Disable Bootstrap (BST) Undervoltage fault detection
//!
//! This function disables the BST fault detection
//!
//! DRV_DisableBstFault() maps directly to this function
//!
//! \return None
//
//*****************************************************************************
void DRV8329_disableBstFault(void);

//*****************************************************************************
//
//! Enable Bootstrap (BST) Undervoltage fault detection
//!
//! This function enables the BST fault detection
//!
//! DRV_EnableBstFault() maps directly to this function
//!
//! \return None
//
//*****************************************************************************
void DRV8329_enableBstFault(void);

//*****************************************************************************
//
//! Disable Trickle Charge Pump (TCP)
//!
//! This function disables the TCP for all high-side outputs
//!
//! DRV_DisableTcp() maps directly to this function
//!
//! \return None
//*****************************************************************************
void DRV8329_disableTcp(void);

//*****************************************************************************
//
//! Enable Trickle Charge Pump (TCP)
//!
//! This function enables the TCP for all high-side outputs
//!
//! DRV_EnableTcp() maps directly to this function
//!
//! \return None
//*****************************************************************************
void DRV8329_enableTcp(void);

//*****************************************************************************
//
//! Set Thermal Shutdown (OTS) Auto-Recovery option
//!
//! \param option is the OTS recovery option to set (DRV8329_OtsRecoveryMode)
//!
//! This function configures the OTS auto-recovery behavior to either latch
//! the fault or enable auto-recovery
//!
//! DRV_SetOtsRecoveryMode() maps directly to this function
//!
//! \return None
//
//*****************************************************************************
void DRV8329_setOtsRecoveryMode(DRV8329_OtsRecoveryMode option);

//*****************************************************************************
//
//! Disable VDS Level Selection through SPI
//!
//! This function disables SPI writes to SEL_VDSLVL bits
//!
//! DRV_DisableVdsLevelSelection() maps directly to this function
//!
//! \return None
//*****************************************************************************
void DRV8329_disableVdsLevelSelectionThroughSpi(void);

//*****************************************************************************
//
//! Enable VDS Level Selection through SPI
//!
//! This function enables SPI writes to SEL_VDSLVL bits.
//!
//! DRV_EnableVdsLevelSelection() maps directly to this function
//!
//! \return None
//*****************************************************************************
void DRV8329_enableVdsLevelSelectionThroughSpi(void);

//*****************************************************************************
//
//! Set the VDS Overcurrent Detection Threshold
//!
//! \param level is the VDSLVL value to set (DRV8329_VdsLevel)
//!
//! This function configures the threshold for VDS overcurrent detection.
//! Ensure DRV8329_enableVdsLevelSelectionThroughSpi has been called prior to
//! using this function to allow SPI writes to the SEL_VDSLVL bits
//!
//! DRV_SetVdsLevel() maps directly to this function
//!
//! \return None
//
//*****************************************************************************
void DRV8329_setVdsLevel(DRV8329_VdsLevel level);

//*****************************************************************************
//
//! Update DRV8329 parameters
//!
//! \param config is a pointer to the DRV8329 Register configuration structure
//!
//! This function updates the DRV8329 register settings based on the provided
//! configurations and updates fault status flags
//!
//! DRV_ConfigureParams() maps directly to this function
//!
//! \return None
//
//*****************************************************************************
void DRV8329_configureParams(DRV8329_CONFIG_T *config);

//*****************************************************************************
//
//! Update DRV8329 with default settings
//!
//! This function configures all DRV8329 CTRLx registers with their default
//! values as defined by the DRV8329_CTRLx_REG_DEFAULT_CONFIG constants
//!
//! DRV_ConfigureParamsDefault() maps directly to this function
//!
//! \return None
//
//*****************************************************************************
void DRV8329_configureParamsDefault(void);

//*****************************************************************************
//
//! Reset DRV8329 fault status
//!
//! This function clears the DRV8329 faults, and resets the fault report and
//! action registers to their default values
//!
//! DRV_ResetFaultStatus() maps directly to this function
//!
//! \return None
//
//*****************************************************************************
void DRV8329_resetFaultStatus(void);

//*****************************************************************************
//
//! Read DRV8329 fault status
//!
//! This function reads the fault status from the DRV8329_STATUS register
//! and returns the fault status as a 32-bit value with appropriate fault bits
//! set
//!
//! DRV_GetFaultStatus() maps directly to this function
//!
//! \return Returns the fault status with fault bits set in position 31:24
//
//*****************************************************************************
uint32_t DRV8329_getFaultStatus(void);

//*****************************************************************************
//
//! Read all DRV8329 registers into array
//!
//! \param registerArray is a pointer to the array where register values will
//! be stored
//!
//! This function reads the values of STATUS, CTRL1, and CTRL2 registers into
//! the provided array
//!
//! DRV_GetAllRegisters() maps directly to this function
//!
//! \return None
//
//*****************************************************************************
void DRV8329_getAllRegisters(uint16_t* registerArray);

#ifdef DEBUG
//*****************************************************************************
//
//! Read all DRV8329 registers into a struct
//!
//! \param pRegs is a pointer to a DRV8329_REGS_T structure where the register
//! values will be stored
//!
//! This function reads the STATUS, CTRL1, and CTRL2 registers and stores
//! their values in the corresponding fields of the provided structure
//!
//! \return None
//
//*****************************************************************************
void DRV8329_readbackRegisters(DRV8329_REGS_T *pRegs);
#endif // DEBUG


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

#ifdef __cplusplus
}
#endif // extern "C"

#endif // end of DRV8329_H definition
