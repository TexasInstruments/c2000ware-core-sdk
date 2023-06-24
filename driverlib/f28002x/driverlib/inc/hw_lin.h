//###########################################################################
//
// FILE:    hw_lin.h
//
// TITLE:   Definitions for the LIN registers.
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

#ifndef HW_LIN_H
#define HW_LIN_H

//*************************************************************************************************
//
// The following are defines for the LIN register offsets
//
//*************************************************************************************************
#define LIN_O_SCIGCR0          0x0U    // Global Control Register 0
#define LIN_O_SCIGCR1          0x4U    // Global Control Register 1
#define LIN_O_SCIGCR2          0x8U    // Global Control Register 2
#define LIN_O_SCISETINT        0xCU    // Interrupt Enable Register
#define LIN_O_SCICLEARINT      0x10U   // Interrupt Disable Register
#define LIN_O_SCISETINTLVL     0x14U   // Set Interrupt Level Register
#define LIN_O_SCICLEARINTLVL   0x18U   // Clear Interrupt Level Register
#define LIN_O_SCIFLR           0x1CU   // Flag Register
#define LIN_O_SCIINTVECT0      0x20U   // Interrupt Vector Offset Register 0
#define LIN_O_SCIINTVECT1      0x24U   // Interrupt Vector Offset Register 1
#define LIN_O_SCIFORMAT        0x28U   // Length Control Register
#define LIN_O_BRSR             0x2CU   // Baud Rate Selection Register
#define LIN_O_SCIED            0x30U   // Emulation buffer Register
#define LIN_O_SCIRD            0x34U   // Receiver data buffer Register
#define LIN_O_SCITD            0x38U   // Transmit data buffer Register
#define LIN_O_SCIPIO0          0x3CU   // Pin control Register 0
#define LIN_O_SCIPIO2          0x44U   // Pin control Register 2
#define LIN_O_COMP             0x60U   // Compare register
#define LIN_O_RD0              0x64U   // Receive data register 0
#define LIN_O_RD1              0x68U   // Receive data register 1
#define LIN_O_MASK             0x6CU   // Acceptance mask register
#define LIN_O_ID               0x70U   // LIN ID Register
#define LIN_O_TD0              0x74U   // Transmit Data Register 0
#define LIN_O_TD1              0x78U   // Transmit Data Register 1
#define LIN_O_MBRSR            0x7CU   // Maximum Baud Rate Selection Register
#define LIN_O_IODFTCTRL        0x90U   // IODFT for LIN
#define LIN_O_GLB_INT_EN       0xE0U   // LIN Global Interrupt Enable Register
#define LIN_O_GLB_INT_FLG      0xE4U   // LIN Global Interrupt Flag Register
#define LIN_O_GLB_INT_CLR      0xE8U   // LIN Global Interrupt Clear Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the SCIGCR0 register
//
//*************************************************************************************************
#define LIN_SCIGCR0_RESET   0x1U   // LIN Module reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCIGCR1 register
//
//*************************************************************************************************
#define LIN_SCIGCR1_COMMMODE       0x1U         // SCI/LIN communications mode bit
#define LIN_SCIGCR1_TIMINGMODE     0x2U         // SCI timing mode bit. Should be set to 1 for SCI
                                                // mode.
#define LIN_SCIGCR1_PARITYENA      0x4U         // Parity enable
#define LIN_SCIGCR1_PARITY         0x8U         // SCI parity odd/even selection
#define LIN_SCIGCR1_STOP           0x10U        // SCI number of stop bits
#define LIN_SCIGCR1_CLK_MASTER     0x20U        // LIN Master/Slave selection and SCI clock enable
#define LIN_SCIGCR1_LINMODE        0x40U        // LIN Mode enable/disable
#define LIN_SCIGCR1_SWNRST         0x80U        // Software reset
#define LIN_SCIGCR1_SLEEP          0x100U       // SCI sleep (SCI compatibility mode)
#define LIN_SCIGCR1_ADAPT          0x200U       // Automatic baudrate adjustment control(LIN mode)
#define LIN_SCIGCR1_MBUFMODE       0x400U       // Multi-buffer mode
#define LIN_SCIGCR1_CTYPE          0x800U       // Checksum type (LIN mode)
#define LIN_SCIGCR1_HGENCTRL       0x1000U      // Mask filtering comparison control (LIN mode)
#define LIN_SCIGCR1_STOPEXTFRAME   0x2000U      // Stop extended frame communication (LIN mode)
#define LIN_SCIGCR1_LOOPBACK       0x10000U     // Digital loopback mode
#define LIN_SCIGCR1_CONT           0x20000U     // Continue on suspend
#define LIN_SCIGCR1_RXENA          0x1000000U   // Receive enable
#define LIN_SCIGCR1_TXENA          0x2000000U   // Transmit enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCIGCR2 register
//
//*************************************************************************************************
#define LIN_SCIGCR2_POWERDOWN   0x1U       // Low-power mode PowerDown bit
#define LIN_SCIGCR2_GENWU       0x100U     // Generate Wakeup
#define LIN_SCIGCR2_SC          0x10000U   // Send Checksum (LIN mode)
#define LIN_SCIGCR2_CC          0x20000U   // Compare Checksum (LIN mode)

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCISETINT register
//
//*************************************************************************************************
#define LIN_SCISETINT_SETBRKDTINT      0x1U          // Set Break-detect Interrupt (SCI compatible
                                                     // mode)
#define LIN_SCISETINT_SETWAKEUPINT     0x2U          // Set Wake-up Interrupt
#define LIN_SCISETINT_SETTIMEOUTINT    0x10U         // Set Timeout Interrupt (LIN only)
#define LIN_SCISETINT_SETTOAWUSINT     0x40U         // Set Timeout After Wakeup Signal Interrupt
                                                     // (LIN only)
#define LIN_SCISETINT_SETTOA3WUSINT    0x80U         // Set Timeout After 3 Wakeup Signals
                                                     // Interrupt (LIN only)
#define LIN_SCISETINT_SETTXINT         0x100U        // Set Transmitter Interrupt
#define LIN_SCISETINT_SETRXINT         0x200U        // Se Receiver Interrupt
#define LIN_SCISETINT_SETIDINT         0x2000U       // Set Identifier Interrupt (LIN only)
#define LIN_SCISETINT_SET_TX_DMA       0x10000U      // Set transmit DMA
#define LIN_SCISETINT_SET_RX_DMA       0x20000U      // Set receiver DMA
#define LIN_SCISETINT_SET_RX_DMA_ALL   0x40000U      // Set receiver DMA for Address & Data frames
#define LIN_SCISETINT_SETPEINT         0x1000000U    // Set Parity Interrupt
#define LIN_SCISETINT_SETOEINT         0x2000000U    // Set Overrun-Error Interrupt
#define LIN_SCISETINT_SETFEINT         0x4000000U    // Set Framing-Error Interrupt
#define LIN_SCISETINT_SETNREINT        0x8000000U    // Set No-Response-Error Interrupt (LIN only)
#define LIN_SCISETINT_SETISFEINT       0x10000000U   // Set Inconsistent-Sync-Field-Error Interrupt
                                                     // (LIN only)
#define LIN_SCISETINT_SETCEINT         0x20000000U   // Set Checksum-error Interrupt (LIN only)
#define LIN_SCISETINT_SETPBEINT        0x40000000U   // Set Physical Bus Error Interrupt (LIN only)
#define LIN_SCISETINT_SETBEINT         0x80000000U   // Set Bit Error Interrupt (LIN only)

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCICLEARINT register
//
//*************************************************************************************************
#define LIN_SCICLEARINT_CLRBRKDTINT     0x1U          // Clear Break-detect Interrupt (SCI
                                                      // compatible mode
#define LIN_SCICLEARINT_CLRWAKEUPINT    0x2U          // Clear Wake-up Interrupt
#define LIN_SCICLEARINT_CLRTIMEOUTINT   0x10U         // Clear Timeout Interrupt (LIN only)
#define LIN_SCICLEARINT_CLRTOAWUSINT    0x40U         // Clear Timeout After Wakeup Signal
                                                      // Interrupt (LIN only)
#define LIN_SCICLEARINT_CLRTOA3WUSINT   0x80U         // Clear Timeout After 3 Wakeup Signals
                                                      // Interrupt (LIN only)
#define LIN_SCICLEARINT_CLRTXINT        0x100U        // Clear Transmitter Interrupt
#define LIN_SCICLEARINT_CLRRXINT        0x200U        // Clear Receiver Interrupt
#define LIN_SCICLEARINT_CLRIDINT        0x2000U       // Clear Identifier Interrupt (LIN only)
#define LIN_SCICLEARINT_CLRTXDMA        0x10000U      // Clear transmit DMA
#define LIN_SCICLEARINT_SETRXDMA        0x20000U      // Clear receiver DMA
#define LIN_SCICLEARINT_CLRPEINT        0x1000000U    // Clear Parity Interrupt
#define LIN_SCICLEARINT_CLROEINT        0x2000000U    // Clear Overrun-Error Interrupt
#define LIN_SCICLEARINT_CLRFEINT        0x4000000U    // Clear Framing-Error Interrupt
#define LIN_SCICLEARINT_CLRNREINT       0x8000000U    // Clear No-Response-Error Interrupt (LIN
                                                      // only)
#define LIN_SCICLEARINT_CLRISFEINT      0x10000000U   // Clear Inconsistent-Sync-Field-Error
                                                      // Interrupt (LIN only)
#define LIN_SCICLEARINT_CLRCEINT        0x20000000U   // Clear Checksum-error Interrupt (LIN only)
#define LIN_SCICLEARINT_CLRPBEINT       0x40000000U   // Clear Physical Bus Error Interrupt (LIN
                                                      // only)
#define LIN_SCICLEARINT_CLRBEINT        0x80000000U   // Clear Bit Error Interrupt (LIN only)

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCISETINTLVL register
//
//*************************************************************************************************
#define LIN_SCISETINTLVL_SETBRKDTINTLVL     0x1U          // Set Break-detect Interrupt Level (SCI
                                                          // compatible mode)
#define LIN_SCISETINTLVL_SETWAKEUPINTLVL    0x2U          // Set Wake-up Interrupt Level
#define LIN_SCISETINTLVL_SETTIMEOUTINTLVL   0x10U         // Set Timeout Interrupt Level (LIN only)
#define LIN_SCISETINTLVL_SETTOAWUSINTLVL    0x40U         // Set Timeout After Wakeup Signal
                                                          // Interrupt Level (LIN only)
#define LIN_SCISETINTLVL_SETTOA3WUSINTLVL   0x80U         // Set Timeout After 3 Wakeup Signals
                                                          // Interrupt Level
#define LIN_SCISETINTLVL_SETTXINTLVL        0x100U        // Set Transmitter Interrupt Level
#define LIN_SCISETINTLVL_SETRXINTOVO        0x200U        // Receiver Interrupt Enable Level
#define LIN_SCISETINTLVL_SETIDINTLVL        0x2000U       // Set Identifier Interrupt Level (LIN
                                                          // only)
#define LIN_SCISETINTLVL_SETPEINTLVL        0x1000000U    // Set Parity Interrupt Level
#define LIN_SCISETINTLVL_SETOEINTLVL        0x2000000U    // Set Overrun-Error Interrupt Level
#define LIN_SCISETINTLVL_SETFEINTLVL        0x4000000U    // Set Framing-Error Interrupt Level
#define LIN_SCISETINTLVL_SETNREINTLVL       0x8000000U    // Set No-Response-Error Interrupt Level
                                                          // (LIN only)
#define LIN_SCISETINTLVL_SETISFEINTLVL      0x10000000U   // Set Inconsistent-Sync-Field-Error
                                                          // Interrupt Level
#define LIN_SCISETINTLVL_SETCEINTLVL        0x20000000U   // Set Checksum-error Interrupt Level
                                                          // (LIN only)
#define LIN_SCISETINTLVL_SETPBEINTLVL       0x40000000U   // Set Physical Bus Error Interrupt Level
                                                          // (LIN only)
#define LIN_SCISETINTLVL_SETBEINTLVL        0x80000000U   // Set Bit Error Interrupt Level (LIN
                                                          // only)

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCICLEARINTLVL register
//
//*************************************************************************************************
#define LIN_SCICLEARINTLVL_CLRBRKDTINTLVL     0x1U          // Clear Break-detect Interrupt Level
                                                            // (SCI compatible mode)
#define LIN_SCICLEARINTLVL_CLRWAKEUPINTLVL    0x2U          // Clear Wake-up Interrupt Level
#define LIN_SCICLEARINTLVL_CLRTIMEOUTINTLVL   0x10U         // Clear Timeout Interrupt Level (LIN
                                                            // only)
#define LIN_SCICLEARINTLVL_CLRTOAWUSINTLVL    0x40U         // Clear Timeout After Wakeup Signal
                                                            // Interrupt Level (LIN only)
#define LIN_SCICLEARINTLVL_CLRTOA3WUSINTLVL   0x80U         // Clear Timeout After 3 Wakeup Signals
#define LIN_SCICLEARINTLVL_CLRTXINTLVL        0x100U        // Clear Transmitter Interrupt Level
#define LIN_SCICLEARINTLVL_CLRRXINTLVL        0x200U        // Clear Receiver interrupt Level.
#define LIN_SCICLEARINTLVL_CLRIDINTLVL        0x2000U       // Clear Identifier Interrupt Level
                                                            // (LIN only)
#define LIN_SCICLEARINTLVL_CLRPEINTLVL        0x1000000U    // Clear Parity Interrupt Level
#define LIN_SCICLEARINTLVL_CLROEINTLVL        0x2000000U    // Clear Overrun-Error Interrupt Level
#define LIN_SCICLEARINTLVL_CLRFEINTLVL        0x4000000U    // Clear Framing-Error Interrupt Level
#define LIN_SCICLEARINTLVL_CLRNREINTLVL       0x8000000U    // Clear No-Response-Error Interrupt
                                                            // Level (LIN only)
#define LIN_SCICLEARINTLVL_CLRISFEINTLVL      0x10000000U   // Clear Inconsistent-Sync-Field-Error
#define LIN_SCICLEARINTLVL_CLRCEINTLVL        0x20000000U   // Clear Checksum-error Interrupt Level
                                                            // (LIN only)
#define LIN_SCICLEARINTLVL_CLRPBEINTLVL       0x40000000U   // Clear Physical Bus Error Interrupt
                                                            // Level (LIN only)
#define LIN_SCICLEARINTLVL_CLRBEINTLVL        0x80000000U   // Clear Bit Error Interrupt Level (LIN
                                                            // only)

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCIFLR register
//
//*************************************************************************************************
#define LIN_SCIFLR_BRKDT      0x1U          // Break-detect Flag (SCI compatible mode)
#define LIN_SCIFLR_WAKEUP     0x2U          // Wake-up Flag
#define LIN_SCIFLR_IDLE       0x4U          // SCI receiver in idle state (SCI compatible mode)
#define LIN_SCIFLR_BUSY       0x8U          // Busy Flag
#define LIN_SCIFLR_TIMEOUT    0x10U         // LIN Bus IDLE timeout Flag (LIN only)
#define LIN_SCIFLR_TOAWUS     0x40U         // Timeout After Wakeup Signal Flag (LIN only)
#define LIN_SCIFLR_TOA3WUS    0x80U         // Timeout After 3 Wakeup Signals Flag (LIN only)
#define LIN_SCIFLR_TXRDY      0x100U        // Transmitter Buffer Ready Flag
#define LIN_SCIFLR_RXRDY      0x200U        // Receiver Buffer Ready Flag
#define LIN_SCIFLR_TXWAKE     0x400U        // SCI Transmitter Wakeup Method Select
#define LIN_SCIFLR_TXEMPTY    0x800U        // Transmitter Empty Flag
#define LIN_SCIFLR_RXWAKE     0x1000U       // Receiver Wakeup Detect Flag
#define LIN_SCIFLR_IDTXFLAG   0x2000U       // Identifier On Transmit Flag (LIN only)
#define LIN_SCIFLR_IDRXFLAG   0x4000U       // Identifier on Receive Flag
#define LIN_SCIFLR_PE         0x1000000U    // Parity Error Flag
#define LIN_SCIFLR_OE         0x2000000U    // Overrun Error Flag
#define LIN_SCIFLR_FE         0x4000000U    // Framing Error Flag
#define LIN_SCIFLR_NRE        0x8000000U    // No-Response Error Flag (LIN only)
#define LIN_SCIFLR_ISFE       0x10000000U   // Inconsistent Sync Field Error Flag (LIN only)
#define LIN_SCIFLR_CE         0x20000000U   // Checksum Error Flag (LIN only)
#define LIN_SCIFLR_PBE        0x40000000U   // Physical Bus Error Flag (LIN only)
#define LIN_SCIFLR_BE         0x80000000U   // Bit Error Flag (LIN only)

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCIINTVECT0 register
//
//*************************************************************************************************
#define LIN_SCIINTVECT0_INTVECT0_S   0U
#define LIN_SCIINTVECT0_INTVECT0_M   0x1FU   // LIN Module reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCIINTVECT1 register
//
//*************************************************************************************************
#define LIN_SCIINTVECT1_INTVECT1_S   0U
#define LIN_SCIINTVECT1_INTVECT1_M   0x1FU   // LIN Module reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCIFORMAT register
//
//*************************************************************************************************
#define LIN_SCIFORMAT_CHAR_S     0U
#define LIN_SCIFORMAT_CHAR_M     0x7U       // Character Length Control Bits
#define LIN_SCIFORMAT_LENGTH_S   16U
#define LIN_SCIFORMAT_LENGTH_M   0x70000U   // Frame Length Control Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the BRSR register
//
//*************************************************************************************************
#define LIN_BRSR_SCI_LIN_PSL_S   0U
#define LIN_BRSR_SCI_LIN_PSL_M   0xFFFFU       // 24-Bit Integer Prescaler Select (Low Bits)
#define LIN_BRSR_SCI_LIN_PSH_S   16U
#define LIN_BRSR_SCI_LIN_PSH_M   0xFF0000U     // 24-Bit Integer Prescaler Select (High Bits)
#define LIN_BRSR_M_S             24U
#define LIN_BRSR_M_M             0xF000000U    // M 4-bit Fractional Divider selection
#define LIN_BRSR_U_S             28U
#define LIN_BRSR_U_M             0x70000000U   // U Superfractional divider Selection

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCIED register
//
//*************************************************************************************************
#define LIN_SCIED_ED_S   0U
#define LIN_SCIED_ED_M   0xFFU   // Receiver Emulation Data.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCIRD register
//
//*************************************************************************************************
#define LIN_SCIRD_RD_S   0U
#define LIN_SCIRD_RD_M   0xFFU   // Received Data.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCITD register
//
//*************************************************************************************************
#define LIN_SCITD_TD_S   0U
#define LIN_SCITD_TD_M   0xFFU   // Transmit data

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCIPIO0 register
//
//*************************************************************************************************
#define LIN_SCIPIO0_RXFUNC   0x2U   // LINRX pin function
#define LIN_SCIPIO0_TXFUNC   0x4U   // LINTX pin function

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCIPIO2 register
//
//*************************************************************************************************
#define LIN_SCIPIO2_RXIN   0x2U   // SCIRX pin value
#define LIN_SCIPIO2_TXIN   0x4U   // SCITX pin value

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINCOMP register
//
//*************************************************************************************************
#define LIN_COMP_SBREAK_S   0U
#define LIN_COMP_SBREAK_M   0x7U     // Sync Break Extend
#define LIN_COMP_SDEL_S     8U
#define LIN_COMP_SDEL_M     0x300U   // Sync Delimiter Compare

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINRD0 register
//
//*************************************************************************************************
#define LIN_RD0_RD3_S   0U
#define LIN_RD0_RD3_M   0xFFU         // Receive Buffer 3
#define LIN_RD0_RD2_S   8U
#define LIN_RD0_RD2_M   0xFF00U       // Receive Buffer 2
#define LIN_RD0_RD1_S   16U
#define LIN_RD0_RD1_M   0xFF0000U     // Receive Buffer 1
#define LIN_RD0_RD0_S   24U
#define LIN_RD0_RD0_M   0xFF000000U   // Receive Buffer 0

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINRD1 register
//
//*************************************************************************************************
#define LIN_RD1_RD7_S   0U
#define LIN_RD1_RD7_M   0xFFU         // Receive Buffer 3
#define LIN_RD1_RD6_S   8U
#define LIN_RD1_RD6_M   0xFF00U       // Receive Buffer 2
#define LIN_RD1_RD5_S   16U
#define LIN_RD1_RD5_M   0xFF0000U     // Receive Buffer 1
#define LIN_RD1_RD4_S   24U
#define LIN_RD1_RD4_M   0xFF000000U   // Receive Buffer 0

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINMASK register
//
//*************************************************************************************************
#define LIN_MASK_TXIDMASK_S   0U
#define LIN_MASK_TXIDMASK_M   0xFFU       // TX ID Mask bits (LIN only)
#define LIN_MASK_RXIDMASK_S   16U
#define LIN_MASK_RXIDMASK_M   0xFF0000U   // RX ID Mask bits (LIN only)

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINID register
//
//*************************************************************************************************
#define LIN_ID_IDBYTE_S            0U
#define LIN_ID_IDBYTE_M            0xFFU       // LIN message ID (LIN only)
#define LIN_ID_IDSLAVETASKBYTE_S   8U
#define LIN_ID_IDSLAVETASKBYTE_M   0xFF00U     // ID  Slave Task byte (LIN only)
#define LIN_ID_RECEIVEDID_S        16U
#define LIN_ID_RECEIVEDID_M        0xFF0000U   // Current Message ID (LIN only)

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINTD0 register
//
//*************************************************************************************************
#define LIN_TD0_TD3_S   0U
#define LIN_TD0_TD3_M   0xFFU         // TRANSMIT Buffer 3
#define LIN_TD0_TD2_S   8U
#define LIN_TD0_TD2_M   0xFF00U       // TRANSMIT Buffer 2
#define LIN_TD0_TD1_S   16U
#define LIN_TD0_TD1_M   0xFF0000U     // TRANSMIT Buffer 1
#define LIN_TD0_TD0_S   24U
#define LIN_TD0_TD0_M   0xFF000000U   // TRANSMIT Buffer 0

//*************************************************************************************************
//
// The following are defines for the bit fields in the LINTD1 register
//
//*************************************************************************************************
#define LIN_TD1_TD7_S   0U
#define LIN_TD1_TD7_M   0xFFU         // TRANSMIT Buffer 7
#define LIN_TD1_TD6_S   8U
#define LIN_TD1_TD6_M   0xFF00U       // TRANSMIT Buffer 6
#define LIN_TD1_TD5_S   16U
#define LIN_TD1_TD5_M   0xFF0000U     // TRANSMIT Buffer 5
#define LIN_TD1_TD4_S   24U
#define LIN_TD1_TD4_M   0xFF000000U   // TRANSMIT Buffer 4

//*************************************************************************************************
//
// The following are defines for the bit fields in the MBRSR register
//
//*************************************************************************************************
#define LIN_MBRSR_MBR_S   0U
#define LIN_MBRSR_MBR_M   0x1FFFU   // Received Data.

//*************************************************************************************************
//
// The following are defines for the bit fields in the IODFTCTRL register
//
//*************************************************************************************************
#define LIN_IODFTCTRL_RXPENA            0x1U          // Analog Loopback Via Receive Pin Enable
#define LIN_IODFTCTRL_LPBENA            0x2U          // Module Loopback Enable
#define LIN_IODFTCTRL_IODFTENA_S        8U
#define LIN_IODFTCTRL_IODFTENA_M        0xF00U        // IO DFT Enable Key
#define LIN_IODFTCTRL_TXSHIFT_S         16U
#define LIN_IODFTCTRL_TXSHIFT_M         0x70000U      // Transmit Delay Shift
#define LIN_IODFTCTRL_PINSAMPLEMASK_S   19U
#define LIN_IODFTCTRL_PINSAMPLEMASK_M   0x180000U     // TX Pin Sample Mask
#define LIN_IODFTCTRL_BRKDTERRENA       0x1000000U    // Break Detect Error Enable (SCI
                                                      // compatibility mode)
#define LIN_IODFTCTRL_PERRENA           0x2000000U    // Parity Error Enable (SCI compatibility
                                                      // mode)
#define LIN_IODFTCTRL_FERRENA           0x4000000U    // Frame Error Enable (SCI compatibility
                                                      // mode)
#define LIN_IODFTCTRL_ISFERRENA         0x10000000U   // Inconsistent Sync Field Error Enable (LIN
                                                      // mode)
#define LIN_IODFTCTRL_CERRENA           0x20000000U   // Checksum Error Enable(LIN mode)
#define LIN_IODFTCTRL_PBERRENA          0x40000000U   // Physical Bus Error Enable (LIN mode)
#define LIN_IODFTCTRL_BERRENA           0x80000000U   // Bit Error Enable (LIN mode)

//*************************************************************************************************
//
// The following are defines for the bit fields in the LIN_GLB_INT_EN register
//
//*************************************************************************************************
#define LIN_GLB_INT_EN_GLBINT0_EN   0x1U   // Global Interrupt Enable for LIN INT0
#define LIN_GLB_INT_EN_GLBINT1_EN   0x2U   // Global Interrupt Enable for LIN INT1

//*************************************************************************************************
//
// The following are defines for the bit fields in the LIN_GLB_INT_FLG register
//
//*************************************************************************************************
#define LIN_GLB_INT_FLG_INT0_FLG   0x1U   // Global Interrupt Flag for LIN INT0
#define LIN_GLB_INT_FLG_INT1_FLG   0x2U   // Global Interrupt Flag for LIN INT1

//*************************************************************************************************
//
// The following are defines for the bit fields in the LIN_GLB_INT_CLR register
//
//*************************************************************************************************
#define LIN_GLB_INT_CLR_INT0_FLG_CLR   0x1U   // Global Interrupt flag clear for LIN INT0
#define LIN_GLB_INT_CLR_INT1_FLG_CLR   0x2U   // Global Interrupt flag  clear for LIN INT1



#endif
