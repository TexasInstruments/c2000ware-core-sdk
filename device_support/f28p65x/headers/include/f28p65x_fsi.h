//###########################################################################
//
// FILE:    f28p65x_fsi.h
//
// TITLE:   Definitions for the FSI registers.
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

#ifndef F28P65X_FSI_H
#define F28P65X_FSI_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// FSI Individual Register Bit Definitions:

struct TX_MAIN_CTRL_BITS {              // bits description
    Uint16 CORE_RST:1;                  // 0 Transmitter Main Core Reset
    Uint16 FLUSH:1;                     // 1 Flush Operation Start
    Uint16 rsvd1:6;                     // 7:2 Reserved
    Uint16 KEY:8;                       // 15:8 Write Key
};

union TX_MAIN_CTRL_REG {
    Uint16  all;
    struct  TX_MAIN_CTRL_BITS  bit;
};

struct TX_CLK_CTRL_BITS {               // bits description
    Uint16 CLK_RST:1;                   // 0 Soft Reset for the Clock Divider
    Uint16 CLK_EN:1;                    // 1 Clock Divider Enable
    Uint16 PRESCALE_VAL:8;              // 9:2 Prescale value
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union TX_CLK_CTRL_REG {
    Uint16  all;
    struct  TX_CLK_CTRL_BITS  bit;
};

struct TX_OPER_CTRL_LO_BITS {           // bits description
    Uint16 DATA_WIDTH:2;                // 1:0 Transmit Data width
    Uint16 SPI_MODE:1;                  // 2 SPI Mode Select
    Uint16 START_MODE:3;                // 5:3 Transmission Start Mode Select
    Uint16 SW_CRC:1;                    // 6 CRC Source Select
    Uint16 PING_TO_MODE:1;              // 7 Ping Counter Reset Mode Select
    Uint16 SEL_PLLCLK:1;                // 8 Input Clock Select
    Uint16 TDM_ENABLE:1;                // 9 Transmit TDM Mode Enable
    Uint16 SEL_TDM_IN:1;                // 10 Input TDM Port Select
    Uint16 rsvd1:5;                     // 15:11 Reserved
};

union TX_OPER_CTRL_LO_REG {
    Uint16  all;
    struct  TX_OPER_CTRL_LO_BITS  bit;
};

struct TX_OPER_CTRL_HI_BITS {           // bits description
    Uint16 rsvd1:5;                     // 4:0 Reserved
    Uint16 FORCE_ERR:1;                 // 5 Error Frame Force
    Uint16 ECC_SEL:1;                   // 6 ECC Data Width Select
    Uint16 EXT_TRIG_SEL:7;              // 13:7 External Trigger Select
    Uint16 rsvd2:2;                     // 15:14 Reserved
};

union TX_OPER_CTRL_HI_REG {
    Uint16  all;
    struct  TX_OPER_CTRL_HI_BITS  bit;
};

struct TX_FRAME_CTRL_BITS {             // bits description
    Uint16 FRAME_TYPE:4;                // 3:0 Transmit Frame Type
    Uint16 N_WORDS:4;                   // 7:4 Number of Words to be Transmitted
    Uint16 rsvd1:7;                     // 14:8 Reserved
    Uint16 START:1;                     // 15 Start Transmission
};

union TX_FRAME_CTRL_REG {
    Uint16  all;
    struct  TX_FRAME_CTRL_BITS  bit;
};

struct TX_FRAME_TAG_UDATA_BITS {        // bits description
    Uint16 FRAME_TAG:4;                 // 3:0 Frame Tag
    Uint16 rsvd1:4;                     // 7:4 Reserved
    Uint16 USER_DATA:8;                 // 15:8 User Data
};

union TX_FRAME_TAG_UDATA_REG {
    Uint16  all;
    struct  TX_FRAME_TAG_UDATA_BITS  bit;
};

struct TX_BUF_PTR_LOAD_BITS {           // bits description
    Uint16 BUF_PTR_LOAD:4;              // 3:0 Buffer Pointer Force Load
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union TX_BUF_PTR_LOAD_REG {
    Uint16  all;
    struct  TX_BUF_PTR_LOAD_BITS  bit;
};

struct TX_BUF_PTR_STS_BITS {            // bits description
    Uint16 CURR_BUF_PTR:4;              // 3:0 Current Buffer Pointer Index
    Uint16 rsvd1:4;                     // 7:4 Reserved
    Uint16 CURR_WORD_CNT:5;             // 12:8 Remaining Words in Buffer
    Uint16 rsvd2:3;                     // 15:13 Reserved
};

union TX_BUF_PTR_STS_REG {
    Uint16  all;
    struct  TX_BUF_PTR_STS_BITS  bit;
};

struct TX_PING_CTRL_BITS {              // bits description
    Uint16 CNT_RST:1;                   // 0 Ping Counter Reset
    Uint16 TIMER_EN:1;                  // 1 Ping Counter Enable
    Uint16 EXT_TRIG_EN:1;               // 2 External Trigger Enable
    Uint16 EXT_TRIG_SEL:7;              // 9:3 External Trigger Select
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union TX_PING_CTRL_REG {
    Uint16  all;
    struct  TX_PING_CTRL_BITS  bit;
};

struct TX_PING_TAG_BITS {               // bits description
    Uint16 TAG:4;                       // 3:0 Ping Frame Tag
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union TX_PING_TAG_REG {
    Uint16  all;
    struct  TX_PING_TAG_BITS  bit;
};

struct TX_INT_CTRL_BITS {               // bits description
    Uint16 INT1_EN_FRAME_DONE:1;        // 0 Enable Frame Done Interrupt to INT1
    Uint16 INT1_EN_BUF_UNDERRUN:1;      // 1 Enable Buffer Underrun Interrupt to INT1
    Uint16 INT1_EN_BUF_OVERRUN:1;       // 2 Enable Buffer Overrun Interrupt to INT1
    Uint16 INT1_EN_PING_TO:1;           // 3 Enable Ping Timer Interrupt to INT1
    Uint16 rsvd1:4;                     // 7:4 Reserved
    Uint16 INT2_EN_FRAME_DONE:1;        // 8 Enable Frame Done Interrupt to INT2
    Uint16 INT2_EN_BUF_UNDERRUN:1;      // 9 Enable Buffer Underrun Interrupt to INT2
    Uint16 INT2_EN_BUF_OVERRUN:1;       // 10 Enable Buffer Overrun Interrupt to INT2
    Uint16 INT2_EN_PING_TO:1;           // 11 Enable Ping Timer Interrupt to INT2
    Uint16 rsvd2:4;                     // 15:12 Reserved
};

union TX_INT_CTRL_REG {
    Uint16  all;
    struct  TX_INT_CTRL_BITS  bit;
};

struct TX_DMA_CTRL_BITS {               // bits description
    Uint16 DMA_EVT_EN:1;                // 0 DMA Event Enable
    Uint16 rsvd1:15;                    // 15:1 Reserved
};

union TX_DMA_CTRL_REG {
    Uint16  all;
    struct  TX_DMA_CTRL_BITS  bit;
};

struct TX_LOCK_CTRL_BITS {              // bits description
    Uint16 LOCK:1;                      // 0 Control Register Lock Enable
    Uint16 rsvd1:7;                     // 7:1 Reserved
    Uint16 KEY:8;                       // 15:8 Write Key
};

union TX_LOCK_CTRL_REG {
    Uint16  all;
    struct  TX_LOCK_CTRL_BITS  bit;
};

struct TX_EVT_STS_BITS {                // bits description
    Uint16 FRAME_DONE:1;                // 0 Frame Done Flag
    Uint16 BUF_UNDERRUN:1;              // 1 Buffer Underrun Flag
    Uint16 BUF_OVERRUN:1;               // 2 Buffer Overrun Flag
    Uint16 PING_TRIGGERED:1;            // 3 Ping Frame Triggered Flag
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union TX_EVT_STS_REG {
    Uint16  all;
    struct  TX_EVT_STS_BITS  bit;
};

struct TX_EVT_CLR_BITS {                // bits description
    Uint16 FRAME_DONE:1;                // 0 Frame Done Flag Clear
    Uint16 BUF_UNDERRUN:1;              // 1 Buffer Underrun Flag Clear
    Uint16 BUF_OVERRUN:1;               // 2 Buffer Overrun Flag Clear
    Uint16 PING_TRIGGERED:1;            // 3 Ping Frame Triggered Flag Clear
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union TX_EVT_CLR_REG {
    Uint16  all;
    struct  TX_EVT_CLR_BITS  bit;
};

struct TX_EVT_FRC_BITS {                // bits description
    Uint16 FRAME_DONE:1;                // 0 Frame Done Flag Force
    Uint16 BUF_UNDERRUN:1;              // 1 Buffer Underrun Flag Force
    Uint16 BUF_OVERRUN:1;               // 2 Buffer Overrun Flag Force
    Uint16 PING_TRIGGERED:1;            // 3 Ping Frame Triggered Flag Force
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union TX_EVT_FRC_REG {
    Uint16  all;
    struct  TX_EVT_FRC_BITS  bit;
};

struct TX_USER_CRC_BITS {               // bits description
    Uint16 USER_CRC:8;                  // 7:0 User-defined CRC
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union TX_USER_CRC_REG {
    Uint16  all;
    struct  TX_USER_CRC_BITS  bit;
};

struct TX_ECC_DATA_BITS {               // bits description
    Uint16 DATA_LOW:16;                 // 15:0 ECC Data Lower 16 Bits
    Uint16 DATA_HIGH:16;                // 31:16 ECC Data Upper 16 Bits
};

union TX_ECC_DATA_REG {
    Uint32  all;
    struct  TX_ECC_DATA_BITS  bit;
};

struct TX_ECC_VAL_BITS {                // bits description
    Uint16 ECC_VAL:7;                   // 6:0 Computed ECC Value
    Uint16 rsvd1:9;                     // 15:7 Reserved
};

union TX_ECC_VAL_REG {
    Uint16  all;
    struct  TX_ECC_VAL_BITS  bit;
};

struct TX_DLYLINE_CTRL_BITS {           // bits description
    Uint16 TXCLK_DLY:5;                 // 4:0 Delay Line Tap Select for TXCLK
    Uint16 TXD0_DLY:5;                  // 9:5 Delay Line Tap Select for TXD0
    Uint16 TXD1_DLY:5;                  // 14:10 Delay Line Tap Select for TXD1
    Uint16 rsvd1:1;                     // 15 Reserved
};

union TX_DLYLINE_CTRL_REG {
    Uint16  all;
    struct  TX_DLYLINE_CTRL_BITS  bit;
};

struct FSI_TX_REGS {
    union   TX_MAIN_CTRL_REG                 TX_MAIN_CTRL;                 // Transmit main control register
    Uint16                                   rsvd1;                        // Reserved
    union   TX_CLK_CTRL_REG                  TX_CLK_CTRL;                  // Transmit clock control register
    Uint16                                   rsvd2;                        // Reserved
    union   TX_OPER_CTRL_LO_REG              TX_OPER_CTRL_LO;              // Transmit operation control register low
    union   TX_OPER_CTRL_HI_REG              TX_OPER_CTRL_HI;              // Transmit operation control register high
    union   TX_FRAME_CTRL_REG                TX_FRAME_CTRL;                // Transmit frame control register
    union   TX_FRAME_TAG_UDATA_REG           TX_FRAME_TAG_UDATA;           // Transmit frame tag and user data register
    union   TX_BUF_PTR_LOAD_REG              TX_BUF_PTR_LOAD;              // Transmit buffer pointer control load register
    union   TX_BUF_PTR_STS_REG               TX_BUF_PTR_STS;               // Transmit buffer pointer control status register
    union   TX_PING_CTRL_REG                 TX_PING_CTRL;                 // Transmit ping control register
    union   TX_PING_TAG_REG                  TX_PING_TAG;                  // Transmit ping tag register
    Uint32                                   TX_PING_TO_REF;               // Transmit ping timeout counter reference
    Uint32                                   TX_PING_TO_CNT;               // Transmit ping timeout current count
    union   TX_INT_CTRL_REG                  TX_INT_CTRL;                  // Transmit interrupt event control register
    union   TX_DMA_CTRL_REG                  TX_DMA_CTRL;                  // Transmit DMA event control register
    union   TX_LOCK_CTRL_REG                 TX_LOCK_CTRL;                 // Transmit lock control register
    Uint16                                   rsvd3;                        // Reserved
    union   TX_EVT_STS_REG                   TX_EVT_STS;                   // Transmit event and error status flag register
    Uint16                                   rsvd4;                        // Reserved
    union   TX_EVT_CLR_REG                   TX_EVT_CLR;                   // Transmit event and error clear register
    union   TX_EVT_FRC_REG                   TX_EVT_FRC;                   // Transmit event and error flag force register
    union   TX_USER_CRC_REG                  TX_USER_CRC;                  // Transmit user-defined CRC register
    Uint16                                   rsvd5[7];                     // Reserved
    union   TX_ECC_DATA_REG                  TX_ECC_DATA;                  // Transmit ECC data register
    union   TX_ECC_VAL_REG                   TX_ECC_VAL;                   // Transmit ECC value register
    Uint16                                   rsvd6;                        // Reserved
    union   TX_DLYLINE_CTRL_REG              TX_DLYLINE_CTRL;              // Transmit delay Line control register
    Uint16                                   rsvd7[27];                    // Reserved
    Uint16                                   TX_BUF_BASE[16];              // Base address for transmit buffer
};

struct RX_MAIN_CTRL_BITS {              // bits description
    Uint16 CORE_RST:1;                  // 0 Receiver Main Core Reset
    Uint16 INT_LOOPBACK:1;              // 1 Internal Loopback Enable
    Uint16 SPI_PAIRING:1;               // 2 Clock Pairing for SPI-like Behaviour
    Uint16 INPUT_ISOLATE:1;             // 3 ISOLATE Input signals
    Uint16 DATA_FILTER_EN:1;            // 4 Data Filter Enable
    Uint16 rsvd1:3;                     // 7:5 Reserved
    Uint16 KEY:8;                       // 15:8 Write Key
};

union RX_MAIN_CTRL_REG {
    Uint16  all;
    struct  RX_MAIN_CTRL_BITS  bit;
};

struct RX_OPER_CTRL_BITS {              // bits description
    Uint16 DATA_WIDTH:2;                // 1:0 Receive Data Width Select
    Uint16 SPI_MODE:1;                  // 2 SPI Mode Enable
    Uint16 N_WORDS:4;                   // 6:3 Number of Words to be Received
    Uint16 ECC_SEL:1;                   // 7 ECC Data Width Select
    Uint16 PING_WD_RST_MODE:1;          // 8 Ping Watchdog Timeout Mode Select
    Uint16 rsvd1:7;                     // 15:9 Reserved
};

union RX_OPER_CTRL_REG {
    Uint16  all;
    struct  RX_OPER_CTRL_BITS  bit;
};

struct RX_FRAME_INFO_BITS {             // bits description
    Uint16 FRAME_TYPE:4;                // 3:0 Received Frame Type
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union RX_FRAME_INFO_REG {
    Uint16  all;
    struct  RX_FRAME_INFO_BITS  bit;
};

struct RX_FRAME_TAG_UDATA_BITS {        // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 FRAME_TAG:4;                 // 4:1 Received Frame Tag
    Uint16 rsvd2:3;                     // 7:5 Reserved
    Uint16 USER_DATA:8;                 // 15:8 Received User Data
};

union RX_FRAME_TAG_UDATA_REG {
    Uint16  all;
    struct  RX_FRAME_TAG_UDATA_BITS  bit;
};

struct RX_DMA_CTRL_BITS {               // bits description
    Uint16 DMA_EVT_EN:1;                // 0 DMA Event Enable
    Uint16 rsvd1:15;                    // 15:1 Reserved
};

union RX_DMA_CTRL_REG {
    Uint16  all;
    struct  RX_DMA_CTRL_BITS  bit;
};

struct RX_EVT_STS_BITS {                // bits description
    Uint16 PING_WD_TO:1;                // 0 Ping Watchdog Timeout Flag
    Uint16 FRAME_WD_TO:1;               // 1 Frame Watchdog Timeout Flag.
    Uint16 CRC_ERR:1;                   // 2 CRC Error Flag
    Uint16 TYPE_ERR:1;                  // 3 Frame Type Error Flag
    Uint16 EOF_ERR:1;                   // 4 End-of-Frame Error Flag
    Uint16 BUF_OVERRUN:1;               // 5 Receive Buffer Overrun Flag
    Uint16 FRAME_DONE:1;                // 6 Frame Done Flag
    Uint16 BUF_UNDERRUN:1;              // 7 Receive Buffer Underrun Flag
    Uint16 ERR_FRAME:1;                 // 8 Error Frame Received Flag
    Uint16 PING_FRAME:1;                // 9 Ping Frame Received Flag
    Uint16 FRAME_OVERRUN:1;             // 10 Frame Overrun Flag
    Uint16 DATA_FRAME:1;                // 11 Data Frame Received Flag
    Uint16 PING_TAG_MATCH:1;            // 12 Ping Tag Match Flag
    Uint16 DATA_TAG_MATCH:1;            // 13 Data Tag Match Flag
    Uint16 ERROR_TAG_MATCH:1;           // 14 Error Tag Match Flag
    Uint16 rsvd1:1;                     // 15 Reserved
};

union RX_EVT_STS_REG {
    Uint16  all;
    struct  RX_EVT_STS_BITS  bit;
};

struct RX_CRC_INFO_BITS {               // bits description
    Uint16 RX_CRC:8;                    // 7:0 Received CRC Value
    Uint16 CALC_CRC:8;                  // 15:8 Hardware Calculated CRC
};

union RX_CRC_INFO_REG {
    Uint16  all;
    struct  RX_CRC_INFO_BITS  bit;
};

struct RX_EVT_CLR_BITS {                // bits description
    Uint16 PING_WD_TO:1;                // 0 Ping Watchdog Timeout Flag Clear
    Uint16 FRAME_WD_TO:1;               // 1 Frame Watchdog Timeout Flag Clear
    Uint16 CRC_ERR:1;                   // 2 CRC Error Flag Clear
    Uint16 TYPE_ERR:1;                  // 3 Frame Type Error Flag Clear
    Uint16 EOF_ERR:1;                   // 4 End-of-Frame Error Flag Clear
    Uint16 BUF_OVERRUN:1;               // 5 Receive Buffer Overrun Flag Clear
    Uint16 FRAME_DONE:1;                // 6 Frame Done Flag Clear
    Uint16 BUF_UNDERRUN:1;              // 7 Receive Buffer Underrun Flag Clear
    Uint16 ERR_FRAME:1;                 // 8 Error Frame Received Flag Clear
    Uint16 PING_FRAME:1;                // 9 PING Frame Received Flag Clear
    Uint16 FRAME_OVERRUN:1;             // 10 Frame Overrun Flag Clear
    Uint16 DATA_FRAME:1;                // 11 Data Frame Received Flag Clear
    Uint16 PING_TAG_MATCH:1;            // 12 Ping Tag Match Flag Clear
    Uint16 DATA_TAG_MATCH:1;            // 13 Data Tag Match Flag Clear
    Uint16 ERROR_TAG_MATCH:1;           // 14 Error Tag Match Flag Clear
    Uint16 rsvd1:1;                     // 15 Reserved
};

union RX_EVT_CLR_REG {
    Uint16  all;
    struct  RX_EVT_CLR_BITS  bit;
};

struct RX_EVT_FRC_BITS {                // bits description
    Uint16 PING_WD_TO:1;                // 0 Ping Watchdog Timeout Flag Force
    Uint16 FRAME_WD_TO:1;               // 1 Frame Watchdog Timeout Flag Force
    Uint16 CRC_ERR:1;                   // 2 CRC Error Flag Force
    Uint16 TYPE_ERR:1;                  // 3 Frame Type Error Flag Force
    Uint16 EOF_ERR:1;                   // 4 End-of-Frame Error Flag Force
    Uint16 BUF_OVERRUN:1;               // 5 Receive Buffer Overrun Flag Force
    Uint16 FRAME_DONE:1;                // 6 Frame Done Flag Force
    Uint16 BUF_UNDERRUN:1;              // 7 Receive Buffer Underrun Flag Force
    Uint16 ERR_FRAME:1;                 // 8 Error Frame Received Flag Force
    Uint16 PING_FRAME:1;                // 9 Ping Frame Received Flag Force
    Uint16 FRAME_OVERRUN:1;             // 10 Frame Overrun Flag Force
    Uint16 DATA_FRAME:1;                // 11 Data Frame Received Flag Force
    Uint16 PING_TAG_MATCH:1;            // 12 Ping Tag Match Flag Force
    Uint16 DATA_TAG_MATCH:1;            // 13 Data Tag Match Flag Force
    Uint16 ERROR_TAG_MATCH:1;           // 14 Error Tag Match Flag Force
    Uint16 rsvd1:1;                     // 15 Reserved
};

union RX_EVT_FRC_REG {
    Uint16  all;
    struct  RX_EVT_FRC_BITS  bit;
};

struct RX_BUF_PTR_LOAD_BITS {           // bits description
    Uint16 BUF_PTR_LOAD:4;              // 3:0 Load value for receive buffer pointer
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union RX_BUF_PTR_LOAD_REG {
    Uint16  all;
    struct  RX_BUF_PTR_LOAD_BITS  bit;
};

struct RX_BUF_PTR_STS_BITS {            // bits description
    Uint16 CURR_BUF_PTR:4;              // 3:0 Current Buffer Pointer Index
    Uint16 rsvd1:4;                     // 7:4 Reserved
    Uint16 CURR_WORD_CNT:5;             // 12:8 Available Words in Buffer
    Uint16 rsvd2:3;                     // 15:13 Reserved
};

union RX_BUF_PTR_STS_REG {
    Uint16  all;
    struct  RX_BUF_PTR_STS_BITS  bit;
};

struct RX_FRAME_WD_CTRL_BITS {          // bits description
    Uint16 FRAME_WD_CNT_RST:1;          // 0 Frame Watchdog Counter Reset
    Uint16 FRAME_WD_EN:1;               // 1 Frame Watchdog Counter Enable
    Uint16 rsvd1:14;                    // 15:2 Reserved
};

union RX_FRAME_WD_CTRL_REG {
    Uint16  all;
    struct  RX_FRAME_WD_CTRL_BITS  bit;
};

struct RX_PING_WD_CTRL_BITS {           // bits description
    Uint16 PING_WD_RST:1;               // 0 Ping Watchdog Counter Reset
    Uint16 PING_WD_EN:1;                // 1 Ping Watchdog Counter Enable
    Uint16 rsvd1:14;                    // 15:2 Reserved
};

union RX_PING_WD_CTRL_REG {
    Uint16  all;
    struct  RX_PING_WD_CTRL_BITS  bit;
};

struct RX_PING_TAG_BITS {               // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 PING_TAG:4;                  // 4:1 Ping Frame Tag
    Uint16 rsvd2:11;                    // 15:5 Reserved
};

union RX_PING_TAG_REG {
    Uint16  all;
    struct  RX_PING_TAG_BITS  bit;
};

struct RX_INT1_CTRL_BITS {              // bits description
    Uint16 INT1_EN_PING_WD_TO:1;        // 0 Enable Ping Watchdog Timeout Interrupt to INT1
    Uint16 INT1_EN_FRAME_WD_TO:1;       // 1 Enable Frame Watchdog Timeout Interrupt to INT1
    Uint16 INT1_EN_CRC_ERR:1;           // 2 Enable CRC Error Interrupt to INT1
    Uint16 INT1_EN_TYPE_ERR:1;          // 3 Enable Frame Type Error Interrupt to INT1
    Uint16 INT1_EN_EOF_ERR:1;           // 4 Enable End-of-Frame Error Interrupt to INT1
    Uint16 INT1_EN_OVERRUN:1;           // 5 Enable Receive Buffer Overrun Interrupt to INT1
    Uint16 INT1_EN_FRAME_DONE:1;        // 6 Enable Frame Done Interrupt to INT1
    Uint16 INT1_EN_UNDERRUN:1;          // 7 Enable Buffer Underrun Interrupt to INT1
    Uint16 INT1_EN_ERR_FRAME:1;         // 8 Enable Error Frame Received Interrupt to INT1
    Uint16 INT1_EN_PING_FRAME:1;        // 9 Enable Ping Frame Received Interrupt to INT1
    Uint16 INT1_EN_FRAME_OVERRUN:1;     // 10 Enable Frame Overrun Interrupt to INT1
    Uint16 INT1_EN_DATA_FRAME:1;        // 11 Enable Data Frame Received Interrupt to INT1
    Uint16 INT1_EN_PING_TAG_MATCH:1;    // 12 Enable Ping Frame Tag Matched Interrupt to INT1
    Uint16 INT1_EN_DATA_TAG_MATCH:1;    // 13 Enable Data Frame Tag Matched Interrupt to INT1
    Uint16 INT1_EN_ERROR_TAG_MATCH:1;   // 14 Enable Error Frame Tag Matched Interrupt to INT1
    Uint16 rsvd1:1;                     // 15 Reserved
};

union RX_INT1_CTRL_REG {
    Uint16  all;
    struct  RX_INT1_CTRL_BITS  bit;
};

struct RX_INT2_CTRL_BITS {              // bits description
    Uint16 INT2_EN_PING_WD_TO:1;        // 0 Enable Ping Watchdog Timeout Interrupt to INT2
    Uint16 INT2_EN_FRAME_WD_TO:1;       // 1 Enable Frame Watchdog Timeout Interrupt to INT2
    Uint16 INT2_EN_CRC_ERR:1;           // 2 Enable CRC Errror Interrupt to INT2
    Uint16 INT2_EN_TYPE_ERR:1;          // 3 Enable Frame Type Error Interrupt to INT2
    Uint16 INT2_EN_EOF_ERR:1;           // 4 Enable End-of-Frame Error Interrupt to INT2
    Uint16 INT2_EN_OVERRUN:1;           // 5 Enable Buffer Overrun Interrupt to INT2
    Uint16 INT2_EN_FRAME_DONE:1;        // 6 Enable Frame Done Interrupt to INT2
    Uint16 INT2_EN_UNDERRUN:1;          // 7 Enable Buffer Underrun Interrupt to INT2
    Uint16 INT2_EN_ERR_FRAME:1;         // 8 Enable Error Frame Received Interrupt to INT2
    Uint16 INT2_EN_PING_FRAME:1;        // 9 Enable Ping Frame Received Interrupt to INT2
    Uint16 INT2_EN_FRAME_OVERRUN:1;     // 10 Enable Frame Overrun Interrupt to INT2
    Uint16 INT2_EN_DATA_FRAME:1;        // 11 Enable Data Frame Received Interrupt to INT2
    Uint16 INT2_EN_PING_TAG_MATCH:1;    // 12 Enable Ping Frame Tag Matched Interrupt to INT2
    Uint16 INT2_EN_DATA_TAG_MATCH:1;    // 13 Enable Data Frame Tag Matched Interrupt to INT2
    Uint16 INT2_EN_ERROR_TAG_MATCH:1;   // 14 Enable Error Frame Tag Matched Interrupt to INT2
    Uint16 rsvd1:1;                     // 15 Reserved
};

union RX_INT2_CTRL_REG {
    Uint16  all;
    struct  RX_INT2_CTRL_BITS  bit;
};

struct RX_LOCK_CTRL_BITS {              // bits description
    Uint16 LOCK:1;                      // 0 Control Register Lock Enable
    Uint16 rsvd1:7;                     // 7:1 Reserved
    Uint16 KEY:8;                       // 15:8 Write Key
};

union RX_LOCK_CTRL_REG {
    Uint16  all;
    struct  RX_LOCK_CTRL_BITS  bit;
};

struct RX_ECC_DATA_BITS {               // bits description
    Uint16 DATA_LOW:16;                 // 15:0 ECC Data Lower 16 Bits
    Uint16 DATA_HIGH:16;                // 31:16 ECC Data Upper 16 Bits
};

union RX_ECC_DATA_REG {
    Uint32  all;
    struct  RX_ECC_DATA_BITS  bit;
};

struct RX_ECC_VAL_BITS {                // bits description
    Uint16 ECC_VAL:7;                   // 6:0 Computed ECC Value
    Uint16 rsvd1:9;                     // 15:7 Reserved
};

union RX_ECC_VAL_REG {
    Uint16  all;
    struct  RX_ECC_VAL_BITS  bit;
};

struct RX_ECC_LOG_BITS {                // bits description
    Uint16 SBE:1;                       // 0 Single Bit Error Detected
    Uint16 MBE:1;                       // 1 Multiple Bit Errors Detected
    Uint16 rsvd1:14;                    // 15:2 Reserved
};

union RX_ECC_LOG_REG {
    Uint16  all;
    struct  RX_ECC_LOG_BITS  bit;
};

struct RX_FRAME_TAG_CMP_BITS {          // bits description
    Uint16 TAG_REF:4;                   // 3:0 Frame Tag Reference
    Uint16 TAG_MASK:4;                  // 7:4 Frame Tag Mask
    Uint16 CMP_EN:1;                    // 8 Frame Tag Compare Enable
    Uint16 BROADCAST_EN:1;              // 9 Broadcast Enable
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union RX_FRAME_TAG_CMP_REG {
    Uint16  all;
    struct  RX_FRAME_TAG_CMP_BITS  bit;
};

struct RX_PING_TAG_CMP_BITS {           // bits description
    Uint16 TAG_REF:4;                   // 3:0 Ping Tag Reference
    Uint16 TAG_MASK:4;                  // 7:4 Ping Tag Mask
    Uint16 CMP_EN:1;                    // 8 Ping Tag Compare Enable
    Uint16 BROADCAST_EN:1;              // 9 Broadcast Enable
    Uint16 rsvd1:6;                     // 15:10 Reserved
};

union RX_PING_TAG_CMP_REG {
    Uint16  all;
    struct  RX_PING_TAG_CMP_BITS  bit;
};

struct RX_TRIG_CTRL_0_BITS {            // bits description
    Uint16 TRIG_EN:1;                   // 0 Enable Trigger Function
    Uint16 TRIG_SEL:4;                  // 4:1 Input Select for Trigger
    Uint16 rsvd1:3;                     // 7:5 Reserved
    Uint32 RX_TRIG_DLY:24;              // 31:8 Delay for Trigger generation
};

union RX_TRIG_CTRL_0_REG {
    Uint32  all;
    struct  RX_TRIG_CTRL_0_BITS  bit;
};

struct RX_TRIG_WIDTH_0_BITS {           // bits description
    Uint16 RX_TRIG_WIDTH:16;            // 15:0 Output Pulse Width
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union RX_TRIG_WIDTH_0_REG {
    Uint32  all;
    struct  RX_TRIG_WIDTH_0_BITS  bit;
};

struct RX_DLYLINE_CTRL_BITS {           // bits description
    Uint16 RXCLK_DLY:5;                 // 4:0 Delay Line Tap Select for RXCLK
    Uint16 RXD0_DLY:5;                  // 9:5 Delay Line Tap Select for RXD0
    Uint16 RXD1_DLY:5;                  // 14:10 Delay Line Tap Select for RXD1
    Uint16 rsvd1:1;                     // 15 Reserved
};

union RX_DLYLINE_CTRL_REG {
    Uint16  all;
    struct  RX_DLYLINE_CTRL_BITS  bit;
};

struct RX_TRIG_CTRL_1_BITS {            // bits description
    Uint16 TRIG_EN:1;                   // 0 Enable Trigger Function
    Uint16 TRIG_SEL:4;                  // 4:1 Input Select for Trigger
    Uint16 rsvd1:3;                     // 7:5 Reserved
    Uint32 RX_TRIG_DLY:24;              // 31:8 Delay for Trigger generation
};

union RX_TRIG_CTRL_1_REG {
    Uint32  all;
    struct  RX_TRIG_CTRL_1_BITS  bit;
};

struct RX_TRIG_CTRL_2_BITS {            // bits description
    Uint16 TRIG_EN:1;                   // 0 Enable Trigger Function
    Uint16 TRIG_SEL:4;                  // 4:1 Input Select for Trigger
    Uint16 rsvd1:3;                     // 7:5 Reserved
    Uint32 RX_TRIG_DLY:24;              // 31:8 Delay for Trigger generation
};

union RX_TRIG_CTRL_2_REG {
    Uint32  all;
    struct  RX_TRIG_CTRL_2_BITS  bit;
};

struct RX_TRIG_CTRL_3_BITS {            // bits description
    Uint16 TRIG_EN:1;                   // 0 Enable Trigger Function
    Uint16 TRIG_SEL:4;                  // 4:1 Input Select for Trigger
    Uint16 rsvd1:3;                     // 7:5 Reserved
    Uint32 RX_TRIG_DLY:24;              // 31:8 Delay for Trigger generation
};

union RX_TRIG_CTRL_3_REG {
    Uint32  all;
    struct  RX_TRIG_CTRL_3_BITS  bit;
};

struct RX_VIS_1_BITS {                  // bits description
    Uint16 rsvd1:3;                     // 2:0 Reserved
    Uint16 RX_CORE_STS:1;               // 3 Receiver Core Status
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union RX_VIS_1_REG {
    Uint32  all;
    struct  RX_VIS_1_BITS  bit;
};

struct RX_UDATA_FILTER_BITS {           // bits description
    Uint16 UDATA_REF:8;                 // 7:0 UserData reference value
    Uint16 UDATA_MASK:8;                // 15:8 UserData mask  value
};

union RX_UDATA_FILTER_REG {
    Uint16  all;
    struct  RX_UDATA_FILTER_BITS  bit;
};

struct FSI_RX_REGS {
    union   RX_MAIN_CTRL_REG                 RX_MAIN_CTRL;                 // Receive main control register
    Uint16                                   rsvd1[3];                     // Reserved
    union   RX_OPER_CTRL_REG                 RX_OPER_CTRL;                 // Receive operation control register
    Uint16                                   rsvd2;                        // Reserved
    union   RX_FRAME_INFO_REG                RX_FRAME_INFO;                // Receive frame control register
    union   RX_FRAME_TAG_UDATA_REG           RX_FRAME_TAG_UDATA;           // Receive frame tag and user data register
    union   RX_DMA_CTRL_REG                  RX_DMA_CTRL;                  // Receive DMA event control register
    Uint16                                   rsvd3;                        // Reserved
    union   RX_EVT_STS_REG                   RX_EVT_STS;                   // Receive event and error status flag register
    union   RX_CRC_INFO_REG                  RX_CRC_INFO;                  // Receive CRC info of received and computed CRC
    union   RX_EVT_CLR_REG                   RX_EVT_CLR;                   // Receive event and error clear register
    union   RX_EVT_FRC_REG                   RX_EVT_FRC;                   // Receive event and error flag force register
    union   RX_BUF_PTR_LOAD_REG              RX_BUF_PTR_LOAD;              // Receive buffer pointer load register
    union   RX_BUF_PTR_STS_REG               RX_BUF_PTR_STS;               // Receive buffer pointer status register
    union   RX_FRAME_WD_CTRL_REG             RX_FRAME_WD_CTRL;             // Receive frame watchdog control register
    Uint16                                   rsvd4;                        // Reserved
    Uint32                                   RX_FRAME_WD_REF;              // Receive frame watchdog counter reference
    Uint32                                   RX_FRAME_WD_CNT;              // Receive frame watchdog current count
    union   RX_PING_WD_CTRL_REG              RX_PING_WD_CTRL;              // Receive ping watchdog control register
    union   RX_PING_TAG_REG                  RX_PING_TAG;                  // Receive ping tag register
    Uint32                                   RX_PING_WD_REF;               // Receive ping watchdog counter reference
    Uint32                                   RX_PING_WD_CNT;               // Receive pingwatchdog current count
    union   RX_INT1_CTRL_REG                 RX_INT1_CTRL;                 // Receive interrupt control register for RX_INT1
    union   RX_INT2_CTRL_REG                 RX_INT2_CTRL;                 // Receive interrupt control register for RX_INT2
    union   RX_LOCK_CTRL_REG                 RX_LOCK_CTRL;                 // Receive lock control register
    Uint16                                   rsvd5;                        // Reserved
    union   RX_ECC_DATA_REG                  RX_ECC_DATA;                  // Receive ECC data register
    union   RX_ECC_VAL_REG                   RX_ECC_VAL;                   // Receive ECC value register
    Uint16                                   rsvd6;                        // Reserved
    Uint32                                   RX_ECC_SEC_DATA;              // Receive ECC corrected data register
    union   RX_ECC_LOG_REG                   RX_ECC_LOG;                   // Receive ECC log and status register
    Uint16                                   rsvd7;                        // Reserved
    union   RX_FRAME_TAG_CMP_REG             RX_FRAME_TAG_CMP;             // Receive frame tag compare register
    union   RX_PING_TAG_CMP_REG              RX_PING_TAG_CMP;              // Receive ping tag compare register
    Uint16                                   rsvd8[2];                     // Reserved
    union   RX_TRIG_CTRL_0_REG               RX_TRIG_CTRL_0;               // Receive Trigger Control register 0
    union   RX_TRIG_WIDTH_0_REG              RX_TRIG_WIDTH_0;              // Receive Trigger Wdith register 0
    union   RX_DLYLINE_CTRL_REG              RX_DLYLINE_CTRL;              // Receive delay line control register
    Uint16                                   rsvd9;                        // Reserved
    union   RX_TRIG_CTRL_1_REG               RX_TRIG_CTRL_1;               // Receive Trigger Control register 1
    union   RX_TRIG_CTRL_2_REG               RX_TRIG_CTRL_2;               // Receive Trigger Control register 2
    union   RX_TRIG_CTRL_3_REG               RX_TRIG_CTRL_3;               // Receive Trigger Control register 3
    union   RX_VIS_1_REG                     RX_VIS_1;                     // Receive debug visibility register 1
    union   RX_UDATA_FILTER_REG              RX_UDATA_FILTER;              // Receive User Data Filter Control register
    Uint16                                   rsvd10[5];                    // Reserved
    Uint16                                   RX_BUF_BASE[16];              // Base address for receive data buffer
};

//---------------------------------------------------------------------------
// FSI External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct FSI_TX_REGS FsiTxaRegs;
extern volatile struct FSI_RX_REGS FsiRxaRegs;
extern volatile struct FSI_TX_REGS FsiTxbRegs;
extern volatile struct FSI_RX_REGS FsiRxbRegs;
extern volatile struct FSI_RX_REGS FsiRxcRegs;
extern volatile struct FSI_RX_REGS FsiRxdRegs;
#endif
#ifdef CPU2
extern volatile struct FSI_TX_REGS FsiTxaRegs;
extern volatile struct FSI_RX_REGS FsiRxaRegs;
extern volatile struct FSI_TX_REGS FsiTxbRegs;
extern volatile struct FSI_RX_REGS FsiRxbRegs;
extern volatile struct FSI_RX_REGS FsiRxcRegs;
extern volatile struct FSI_RX_REGS FsiRxdRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
