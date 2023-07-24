//###########################################################################
//
// FILE:    f28p65x_ecat_ss.h
//
// TITLE:   Definitions for the ECAT_SS registers.
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

#ifndef F28P65X_ECAT_SS_H
#define F28P65X_ECAT_SS_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// ECAT_SS Individual Register Bit Definitions:

struct ESCSS_IPREVNUM_BITS {            // bits description
    Uint16 IP_REV_MINOR:4;              // 3:0 Minor IP Revision Number
    Uint16 IP_REV_MAJOR:4;              // 7:4 Major IP Revision Number
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ESCSS_IPREVNUM_REG {
    Uint32  all;
    struct  ESCSS_IPREVNUM_BITS  bit;
};

struct ESCSS_INTR_RIS_BITS {            // bits description
    Uint16 SYNC0_RIS:1;                 // 0 SYNC0 feature RIS
    Uint16 SYNC1_RIS:1;                 // 1 SYNC1 feature RIS
    Uint16 IRQ_RIS:1;                   // 2 EtherCATSS IRQ RIS
    Uint16 DMA_DONE_RIS:1;              // 3 DMA Done RIS
    Uint16 TIMEOUT_ERR_RIS:1;           // 4 PDI bus Timeout Error RIS
    Uint16 MDEVICE_RESET_RIS:1;         // 5 ECAT RESET RIS
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ESCSS_INTR_RIS_REG {
    Uint32  all;
    struct  ESCSS_INTR_RIS_BITS  bit;
};

struct ESCSS_INTR_MASK_BITS {           // bits description
    Uint16 SYNC0_MASK:1;                // 0 SYNC0 feature Mask
    Uint16 SYNC1_MASK:1;                // 1 SYNC1 feature Mask
    Uint16 IRQ_MASK:1;                  // 2 EtherCATSS IRQ Mask
    Uint16 DMA_DONE_MASK:1;             // 3 DMA Done Mask
    Uint16 TIMEOUT_ERR_MASK:1;          // 4 PDI Access Timeout Error Mask
    Uint16 MDEVICE_RESET_MASK:1;        // 5 EtherCAT MainDevice Reset Mask
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ESCSS_INTR_MASK_REG {
    Uint32  all;
    struct  ESCSS_INTR_MASK_BITS  bit;
};

struct ESCSS_INTR_MIS_BITS {            // bits description
    Uint16 SYNC0_MIS:1;                 // 0 SYNC0 feature MIS
    Uint16 SYNC1_MIS:1;                 // 1 SYNC1 feature MIS
    Uint16 IRQ_MIS:1;                   // 2 EtherCATSS IRQ MIS
    Uint16 DMA_DONE_MIS:1;              // 3 DMA Done MIS
    Uint16 TIMEOUT_ERR_MIS:1;           // 4 PDI bus Timeout Error MIS
    Uint16 MDEVICE_RESET_MIS:1;         // 5 EtherCAT MainDevice Reset MIS
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ESCSS_INTR_MIS_REG {
    Uint32  all;
    struct  ESCSS_INTR_MIS_BITS  bit;
};

struct ESCSS_INTR_CLR_BITS {            // bits description
    Uint16 SYNC0_CLR:1;                 // 0 SYNC0 feature Clear
    Uint16 SYNC1_CLR:1;                 // 1 SYNC1 feature Clear
    Uint16 IRQ_CLR:1;                   // 2 EtherCATSS IRQ Clear
    Uint16 DMA_DONE_CLR:1;              // 3 DMA Done Clear
    Uint16 TIMEOUT_ERR_CLR:1;           // 4 PDI Access Timeout Error Clear
    Uint16 MDEVICE_RESET_CLR:1;         // 5 EtherCAT MainDevice Reset Clear
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ESCSS_INTR_CLR_REG {
    Uint32  all;
    struct  ESCSS_INTR_CLR_BITS  bit;
};

struct ESCSS_INTR_SET_BITS {            // bits description
    Uint16 SYNC0_SET:1;                 // 0 SYNC0 Set Emulate
    Uint16 SYNC1_SET:1;                 // 1 SYNC1 Set Emulate
    Uint16 IRQ_SET:1;                   // 2 EtherCATSS IRQ Set Emulate
    Uint16 DMA_DONE_SET:1;              // 3 DMA Done Set Emulate
    Uint16 TIMEOUT_ERR_SET:1;           // 4 PDI Access Timeout Error Set Emulate
    Uint16 MDEVICE_RESET_SET:1;         // 5 EtherCAT MainDevice Reset Emulate
    Uint16 rsvd1:2;                     // 7:6 Reserved
    Uint16 WRITE_KEY:8;                 // 15:8 Key to enable writing lock
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ESCSS_INTR_SET_REG {
    Uint32  all;
    struct  ESCSS_INTR_SET_BITS  bit;
};

struct ESCSS_LATCH_SEL_BITS {           // bits description
    Uint16 LATCH0_SELECT:5;             // 4:0 LATCH0 Inputs mux select
    Uint16 rsvd1:3;                     // 7:5 Reserved
    Uint16 LATCH1_SELECT:5;             // 12:8 LATCH1 Inputs mux select
    Uint16 rsvd2:3;                     // 15:13 Reserved
    Uint16 rsvd3:1;                     // 16 Reserved
    Uint16 rsvd4:15;                    // 31:17 Reserved
};

union ESCSS_LATCH_SEL_REG {
    Uint32  all;
    struct  ESCSS_LATCH_SEL_BITS  bit;
};

struct ESCSS_ACCESS_CTRL_BITS {         // bits description
    Uint16 WAIT_STATES:7;               // 6:0 Minimum Wait States for VBUS Bridge
    Uint16 EN_TIMEOUT:1;                // 7 PDI Timeout enable
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 ENABLE_DEBUG_ACCESS:1;       // 9 Debug access enable
    Uint16 ENABLE_PARALLEL_PORT_ACCESS:1; // 10 Parallel port access enable
    Uint16 rsvd2:5;                     // 15:11 Reserved
    Uint16 TIMEOUT_COUNT:12;            // 27:16 Max timecount programmed and count while enabled.
    Uint16 rsvd3:4;                     // 31:28 Reserved
};

union ESCSS_ACCESS_CTRL_REG {
    Uint32  all;
    struct  ESCSS_ACCESS_CTRL_BITS  bit;
};

struct ESCSS_GPIN_GRP_CAP_SEL_BITS {    // bits description
    Uint16 GPI_GRP_CAP_SEL0:3;          // 2:0 GPI7-0 capture trigger select
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 GPI_GRP_CAP_SEL1:3;          // 6:4 GPI15-8 capture trigger select
    Uint16 rsvd2:1;                     // 7 Reserved
    Uint16 GPI_GRP_CAP_SEL2:3;          // 10:8 GPI23-16 capture trigger select
    Uint16 rsvd3:1;                     // 11 Reserved
    Uint16 GPI_GRP_CAP_SEL3:3;          // 14:12 GPI31-24 capture trigger select
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union ESCSS_GPIN_GRP_CAP_SEL_REG {
    Uint32  all;
    struct  ESCSS_GPIN_GRP_CAP_SEL_BITS  bit;
};

struct ESCSS_GPOUT_GRP_CAP_SEL_BITS {   // bits description
    Uint16 GPO_GRP_CAP_SEL0:2;          // 1:0 GPO7-0 capture trigger select
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint16 GPO_GRP_CAP_SEL1:2;          // 5:4 GPO15-8 capture trigger select
    Uint16 rsvd2:2;                     // 7:6 Reserved
    Uint16 GPO_GRP_CAP_SEL2:2;          // 9:8 GPO23-16 capture trigger select
    Uint16 rsvd3:2;                     // 11:10 Reserved
    Uint16 GPO_GRP_CAP_SEL3:2;          // 13:12 GPO31-24 capture trigger select
    Uint16 rsvd4:2;                     // 15:14 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union ESCSS_GPOUT_GRP_CAP_SEL_REG {
    Uint32  all;
    struct  ESCSS_GPOUT_GRP_CAP_SEL_BITS  bit;
};

struct ESCSS_MEM_TEST_BITS {            // bits description
    Uint16 INITIATE_MEM_INIT:1;         // 0 Initialize memory init
    Uint16 MEM_INIT_DONE:1;             // 1 Memory Init done status
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ESCSS_MEM_TEST_REG {
    Uint32  all;
    struct  ESCSS_MEM_TEST_BITS  bit;
};

struct ESCSS_RESET_DEST_CONFIG_BITS {   // bits description
    Uint16 CPU_RESET_EN:1;              // 0 CPU reset enable for ResetOut
    Uint16 CPU_NMI_EN:1;                // 1 CPU NMI enable for ResetOut
    Uint16 CPU_INT_EN:1;                // 2 CPU Interrupt enable for ResetOut
    Uint16 rsvd1:4;                     // 6:3 Reserved
    Uint16 DEVICE_RESET_EN:1;           // 7 Enables RESET_OUT to impact the device reset
    Uint16 WRITE_KEY:8;                 // 15:8 Key to enable writing lock
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ESCSS_RESET_DEST_CONFIG_REG {
    Uint32  all;
    struct  ESCSS_RESET_DEST_CONFIG_BITS  bit;
};

struct ESCSS_SYNC0_CONFIG_BITS {        // bits description
    Uint16 C28x_PIE_EN:1;               // 0 Connects the SYNC0 to C28x PIE Interrupt
    Uint16 CLA_INT_EN:1;                // 1 Connects the SYNC0 to CLA Interrupt
    Uint16 C28x_DMA_EN:1;               // 2 Connects the SYNC0 to C28x DMA Trigger
    Uint16 CM4_NVIC_EN:1;               // 3 Connects the SYNC0 to CM4 NVIC Interrupt
    Uint16 uDMA_TRIG_EN:1;              // 4 Connects the SYNC0 to uDMA Trigger
    Uint16 rsvd1:3;                     // 7:5 Reserved
    Uint16 WRITE_KEY:8;                 // 15:8 Key to enable writing lock
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ESCSS_SYNC0_CONFIG_REG {
    Uint32  all;
    struct  ESCSS_SYNC0_CONFIG_BITS  bit;
};

struct ESCSS_SYNC1_CONFIG_BITS {        // bits description
    Uint16 C28x_PIE_EN:1;               // 0 Connects the SYNC1 to C28x PIE Interrupt
    Uint16 CLA_INT_EN:1;                // 1 Connects the SYNC1 to CLA Interrupt
    Uint16 C28x_DMA_EN:1;               // 2 Connects the SYNC1 to C28x DMA Trigger
    Uint16 CM4_NVIC_EN:1;               // 3 Connects the SYNC1 to CM4 NVIC Interrupt
    Uint16 uDMA_TRIG_EN:1;              // 4 Connects the SYNC1 to uDMA Trigger
    Uint16 rsvd1:3;                     // 7:5 Reserved
    Uint16 WRITE_KEY:8;                 // 15:8 Key to enable writing lock
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ESCSS_SYNC1_CONFIG_REG {
    Uint32  all;
    struct  ESCSS_SYNC1_CONFIG_BITS  bit;
};

struct ESCSS_REGS {
    union   ESCSS_IPREVNUM_REG               ESCSS_IPREVNUM;               // IP Revision Number
    union   ESCSS_INTR_RIS_REG               ESCSS_INTR_RIS;               // EtherCATSS Interrupt Raw Status
    union   ESCSS_INTR_MASK_REG              ESCSS_INTR_MASK;              // EtherCATSS Interrupt Mask
    union   ESCSS_INTR_MIS_REG               ESCSS_INTR_MIS;               // EtherCATSS Masked Interrupt Status
    union   ESCSS_INTR_CLR_REG               ESCSS_INTR_CLR;               // EtherCATSS Interrupt Clear
    union   ESCSS_INTR_SET_REG               ESCSS_INTR_SET;               // EtherCATSS Interrupt Set to emulate
    union   ESCSS_LATCH_SEL_REG              ESCSS_LATCH_SEL;              // Select for Latch0/1 inputs and LATCHIN input
    union   ESCSS_ACCESS_CTRL_REG            ESCSS_ACCESS_CTRL;            // PDI interface access control config.
    Uint32                                   ESCSS_GPIN_DAT;               // GPIN data capture for debug & override
    Uint32                                   ESCSS_GPIN_PIPE;              // GPIN pipeline select
    union   ESCSS_GPIN_GRP_CAP_SEL_REG       ESCSS_GPIN_GRP_CAP_SEL;       // GPIN pipe group capture trigger
    Uint32                                   ESCSS_GPOUT_DAT;              // GPOUT data capture for debug & override
    Uint32                                   ESCSS_GPOUT_PIPE;             // GPOUT pipeline select
    union   ESCSS_GPOUT_GRP_CAP_SEL_REG      ESCSS_GPOUT_GRP_CAP_SEL;      // GPOUT pipe group capture trigger
    union   ESCSS_MEM_TEST_REG               ESCSS_MEM_TEST;               // Memory Test Control
    union   ESCSS_RESET_DEST_CONFIG_REG      ESCSS_RESET_DEST_CONFIG;      // ResetOut impact or destination config
    union   ESCSS_SYNC0_CONFIG_REG           ESCSS_SYNC0_CONFIG;           // SYNC0 Configuration for various triggers
    union   ESCSS_SYNC1_CONFIG_REG           ESCSS_SYNC1_CONFIG;           // SYNC1 Configuration for various triggers
};

struct ESCSS_CONFIG_LOCK_BITS {         // bits description
    Uint16 LOCK_ENABLE:1;               // 0 Locking writes to ECATSS
    Uint16 rsvd1:3;                     // 3:1 Reserved
    Uint16 IO_CONFIG_ENABLE:1;          // 4 Locking the IO Configuration
    Uint16 rsvd2:3;                     // 7:5 Reserved
    Uint16 WRITE_KEY:8;                 // 15:8 Key to enable writing lock
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union ESCSS_CONFIG_LOCK_REG {
    Uint32  all;
    struct  ESCSS_CONFIG_LOCK_BITS  bit;
};

struct ESCSS_MISC_IO_CONFIG_BITS {      // bits description
    Uint16 RESETIN_GPIO_EN:1;           // 0 Enabled ResetIN from GPIO
    Uint16 EEPROM_I2C_IO_EN:1;          // 1 Enables the EEPROM I2C IOPAD connection
    Uint16 rsvd1:6;                     // 7:2 Reserved
    Uint16 WRITE_KEY:8;                 // 15:8 Key to enable writing lock
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ESCSS_MISC_IO_CONFIG_REG {
    Uint32  all;
    struct  ESCSS_MISC_IO_CONFIG_BITS  bit;
};

struct ESCSS_PHY_IO_CONFIG_BITS {       // bits description
    Uint16 rsvd1:2;                     // 1:0 Reserved
    Uint16 PHY_PORT_CNT:2;              // 3:2 Number of PHY port counts
    Uint16 PHY_INTF_IOPAD_SEL:2;        // 5:4 IO Combination select for PHY Interface
    Uint16 TX_CLK_AUTO_COMP:1;          // 6 Selects TX_CLK IO to do Auto compensation
    Uint16 rsvd2:1;                     // 7 Reserved
    Uint16 WRITE_KEY:8;                 // 15:8 Key to enable writing lock
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union ESCSS_PHY_IO_CONFIG_REG {
    Uint32  all;
    struct  ESCSS_PHY_IO_CONFIG_BITS  bit;
};

struct ESCSS_SYNC_IO_CONFIG_BITS {      // bits description
    Uint16 SYNC0_IOPAD_SEL:2;           // 1:0 SYNC0 IO PAD select option
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 SYNC0_GPIO_EN:1;             // 3 SYNC0 connection to OUT pad enabled
    Uint16 SYNC1_IOPAD_SEL:2;           // 5:4 SYNC1 IO PAD select option
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 SYNC1_GPIO_EN:1;             // 7 SYNC1 connection to OUT pad enabled
    Uint16 WRITE_KEY:8;                 // 15:8 Key to enable writing lock
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union ESCSS_SYNC_IO_CONFIG_REG {
    Uint32  all;
    struct  ESCSS_SYNC_IO_CONFIG_BITS  bit;
};

struct ESCSS_LATCH_IO_CONFIG_BITS {     // bits description
    Uint16 LATCH0_IOPAD_SEL:2;          // 1:0 LATCH0 IO PAD select option
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 LATCH0_GPIO_EN:1;            // 3 LATCH0 connection to IN pad enabled
    Uint16 LATCH1_IOPAD_SEL:2;          // 5:4 LATCH1 IO PAD select option
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 LATCH1_GPIO_EN:1;            // 7 LATCH1 connection to IN pad enabled
    Uint16 WRITE_KEY:8;                 // 15:8 Key to enable writing lock
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union ESCSS_LATCH_IO_CONFIG_REG {
    Uint32  all;
    struct  ESCSS_LATCH_IO_CONFIG_BITS  bit;
};

struct ESCSS_LED_CONFIG_BITS {          // bits description
    Uint16 LINKACT0:1;                  // 0 GPIO enable for LINKACT0 LED
    Uint16 LINKACT1:1;                  // 1 GPIO enable for LINKACT1 LED
    Uint16 STATE:1;                     // 2 GPIO enable for STATE LED
    Uint16 ERR:1;                       // 3 GPIO enable for ERR LED
    Uint16 RUN:1;                       // 4 GPIO enable for RUN LED
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 LINKACT0_IOPAD_SEL:2;        // 7:6 LINKACT0 LED IO PAD select
    Uint16 LINKACT1_IOPAD_SEL:2;        // 9:8 LINKACT1 LED IO PAD select
    Uint16 STATE_IOPAD_SEL:2;           // 11:10 STATE LED IO PAD select
    Uint16 ERR_IOPAD_SEL:2;             // 13:12 ERROR LED IO PAD select
    Uint16 RUN_IOPAD_SEL:2;             // 15:14 RUN LED IO PAD select
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ESCSS_LED_CONFIG_REG {
    Uint32  all;
    struct  ESCSS_LED_CONFIG_BITS  bit;
};

struct ESCSS_MISC_CONFIG_BITS {         // bits description
    Uint16 TX0_SHIFT_CONFIG:2;          // 1:0 TX Shift configuration for Port0
    Uint16 TX1_SHIFT_CONFIG:2;          // 3:2 TX Shift configuration for Port1
    Uint16 EEPROM_SIZE:1;               // 4 EEPROM Size bound select
    Uint16 PDI_EMULATION:1;             // 5 PDI Emulation enable
    Uint16 PHY_ADDR:5;                  // 10:6 PHY Address Offset
    Uint16 rsvd1:5;                     // 15:11 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ESCSS_MISC_CONFIG_REG {
    Uint32  all;
    struct  ESCSS_MISC_CONFIG_BITS  bit;
};

struct ESCSS_CONFIG_REGS {
    union   ESCSS_CONFIG_LOCK_REG            ESCSS_CONFIG_LOCK;            // EtherCATSS Configuration Lock
    union   ESCSS_MISC_IO_CONFIG_REG         ESCSS_MISC_IO_CONFIG;         // RESET_IN, EEPROM IO connections select
    union   ESCSS_PHY_IO_CONFIG_REG          ESCSS_PHY_IO_CONFIG;          // Control Register of ESCSS
    union   ESCSS_SYNC_IO_CONFIG_REG         ESCSS_SYNC_IO_CONFIG;         // SYNC Signals IO configurations
    union   ESCSS_LATCH_IO_CONFIG_REG        ESCSS_LATCH_IO_CONFIG;        // LATCH inputs IO pad select
    Uint32                                   ESCSS_GPIN_SEL;               // GPIN Select between IO PAD & tieoff
    Uint32                                   ESCSS_GPIN_IOPAD_SEL;         // GPIN IO pad Select
    Uint32                                   ESCSS_GPOUT_SEL;              // GPOUT IO pad connect select
    Uint32                                   ESCSS_GPOUT_IOPAD_SEL;        // GPOUT IO pad select
    union   ESCSS_LED_CONFIG_REG             ESCSS_LED_CONFIG;             // Selection of LED o/p connect to IO pad
    union   ESCSS_MISC_CONFIG_REG            ESCSS_MISC_CONFIG;            // Miscelleneous Configuration
};

//---------------------------------------------------------------------------
// ECAT_SS External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct ESCSS_REGS EscssRegs;
extern volatile struct ESCSS_CONFIG_REGS EscssConfigRegs;
#endif
#ifdef CPU2
extern volatile struct ESCSS_REGS EscssRegs;
extern volatile struct ESCSS_CONFIG_REGS EscssConfigRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
