//###########################################################################
//
// FILE:    f28p65x_bgcrc.h
//
// TITLE:   Definitions for the BGCRC registers.
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

#ifndef F28P65X_BGCRC_H
#define F28P65X_BGCRC_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// BGCRC Individual Register Bit Definitions:

struct BGCRC_EN_BITS {                  // bits description
    Uint16 START:4;                     // 3:0 Start Bit used to  Kick-off CRC calculations
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:15;                    // 30:16 Reserved
    Uint16 RUN_STS:1;                   // 31 CRC module activity monitor
};

union BGCRC_EN_REG {
    Uint32  all;
    struct  BGCRC_EN_BITS  bit;
};

struct BGCRC_CTRL1_BITS {               // bits description
    Uint16 rsvd1:4;                     // 3:0 Reserved
    Uint16 FREE_SOFT:1;                 // 4 emulation control bit
    Uint16 rsvd2:11;                    // 15:5 Reserved
    Uint16 NMIDIS:4;                    // 19:16 NMI disable configuration
    Uint16 rsvd3:12;                    // 31:20 Reserved
};

union BGCRC_CTRL1_REG {
    Uint32  all;
    struct  BGCRC_CTRL1_BITS  bit;
};

struct BGCRC_CTRL2_BITS {               // bits description
    Uint16 BLOCK_SIZE:10;               // 9:0 block size for memory check
    Uint16 rsvd1:2;                     // 11:10 Reserved
    Uint16 TEST_HALT:4;                 // 15:12 TEST_HALT configuration
    Uint16 SCRUB_MODE:4;                // 19:16 Scrub mode configuration
    Uint16 rsvd2:12;                    // 31:20 Reserved
};

union BGCRC_CTRL2_REG {
    Uint32  all;
    struct  BGCRC_CTRL2_BITS  bit;
};

struct BGCRC_WD_CFG_BITS {              // bits description
    Uint16 WDDIS:4;                     // 3:0 CRC Watchdog disable
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union BGCRC_WD_CFG_REG {
    Uint32  all;
    struct  BGCRC_WD_CFG_BITS  bit;
};

struct BGCRC_NMIFLG_BITS {              // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 CRC_FAIL:1;                  // 2 CRC computation failed
    Uint16 UNCORRECTABLE_ERR:1;         // 3 Uncorrectable error obtained during memory data read.
    Uint16 CORRECTABLE_ERR:1;           // 4 Correctable ECC error obtained during memory data read.
    Uint16 WD_UNDERFLOW:1;              // 5 CRC/scrubbing completed before BGCRC_WD_MIN
    Uint16 WD_OVERFLOW:1;               // 6 CRC/scrubbing did not complete within BGCRC_WD_MAX
    Uint16 rsvd3:9;                     // 15:7 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union BGCRC_NMIFLG_REG {
    Uint32  all;
    struct  BGCRC_NMIFLG_BITS  bit;
};

struct BGCRC_NMICLR_BITS {              // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 CRC_FAIL:1;                  // 2 CRC_FAIL NMI flag clear
    Uint16 UNCORRECTABLE_ERR:1;         // 3 UNCORRECTABLE_ERR NMI flag clear
    Uint16 CORRECTABLE_ERR:1;           // 4 CORRECTABLE_ERR NMI flag clear
    Uint16 WD_UNDERFLOW:1;              // 5 WD_UNDERFLOW NMI flag clear
    Uint16 WD_OVERFLOW:1;               // 6 WD_OVERFLOW NMI flag clear
    Uint16 rsvd3:9;                     // 15:7 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union BGCRC_NMICLR_REG {
    Uint32  all;
    struct  BGCRC_NMICLR_BITS  bit;
};

struct BGCRC_NMIFRC_BITS {              // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 CRC_FAIL:1;                  // 2 CRC_FAIL NMI force
    Uint16 UNCORRECTABLE_ERR:1;         // 3 UNCORRECTABLE_ERR NMI force
    Uint16 CORRECTABLE_ERR:1;           // 4 CORRECTABLE_ERR NMI force
    Uint16 WD_UNDERFLOW:1;              // 5 WD_UNDERFLOW NMI force
    Uint16 WD_OVERFLOW:1;               // 6 WD_OVERFLOW NMI force
    Uint16 rsvd3:9;                     // 15:7 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union BGCRC_NMIFRC_REG {
    Uint32  all;
    struct  BGCRC_NMIFRC_BITS  bit;
};

struct BGCRC_INTEN_BITS {               // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 TEST_DONE:1;                 // 1 TEST_DONE interrupt enable register
    Uint16 CRC_FAIL:1;                  // 2 CRC_FAIL interrupt enable register
    Uint16 UNCORRECTABLE_ERR:1;         // 3 UNCORRECTABLE_ERR interrupt enable register
    Uint16 CORRECTABLE_ERR:1;           // 4 CORRECTABLE_ERR interrupt enable register
    Uint16 WD_UNDERFLOW:1;              // 5 WD_UNDERFLOW interrupt enable register
    Uint16 WD_OVERFLOW:1;               // 6 WD_OVERFLOW interrupt enable register
    Uint16 rsvd2:9;                     // 15:7 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union BGCRC_INTEN_REG {
    Uint32  all;
    struct  BGCRC_INTEN_BITS  bit;
};

struct BGCRC_INTFLG_BITS {              // bits description
    Uint16 INT:1;                       // 0 Global Interrupt status flag
    Uint16 TEST_DONE:1;                 // 1 TEST_DONE Interrupt status flag
    Uint16 CRC_FAIL:1;                  // 2 CRC computation failed
    Uint16 UNCORRECTABLE_ERR:1;         // 3 Uncorrectable error obtained during memory data read.
    Uint16 CORRECTABLE_ERR:1;           // 4 Correctable ECC error obtained during memory data read.
    Uint16 WD_UNDERFLOW:1;              // 5 CRC/scrubbing completed before BGCRC_WD_MIN
    Uint16 WD_OVERFLOW:1;               // 6 CRC/scrubbing did not complete within BGCRC_WD_MAX
    Uint16 rsvd1:9;                     // 15:7 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union BGCRC_INTFLG_REG {
    Uint32  all;
    struct  BGCRC_INTFLG_BITS  bit;
};

struct BGCRC_INTCLR_BITS {              // bits description
    Uint16 INT:1;                       // 0 Global Interrupt clear
    Uint16 TEST_DONE:1;                 // 1 TEST_DONE Interrupt clear
    Uint16 CRC_FAIL:1;                  // 2 CRC_FAIL interrupt clear
    Uint16 UNCORRECTABLE_ERR:1;         // 3 UNCORRECTABLE_ERR interrupt clear
    Uint16 CORRECTABLE_ERR:1;           // 4 CORRECTABLE_ERR interrupt clear
    Uint16 WD_UNDERFLOW:1;              // 5 WD_UNDERFLOW interrupt clear
    Uint16 WD_OVERFLOW:1;               // 6 WD_OVERFLOW interrupt clear
    Uint16 rsvd1:9;                     // 15:7 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union BGCRC_INTCLR_REG {
    Uint32  all;
    struct  BGCRC_INTCLR_BITS  bit;
};

struct BGCRC_INTFRC_BITS {              // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 TEST_DONE:1;                 // 1 TEST_DONE Interrupt force
    Uint16 CRC_FAIL:1;                  // 2 CRC_FAIL interrupt force
    Uint16 UNCORRECTABLE_ERR:1;         // 3 UNCORRECTABLE_ERR interrupt force
    Uint16 CORRECTABLE_ERR:1;           // 4 CORRECTABLE_ERR interrupt force
    Uint16 WD_UNDERFLOW:1;              // 5 WD_UNDERFLOW interrupt force
    Uint16 WD_OVERFLOW:1;               // 6 WD_OVERFLOW interrupt force
    Uint16 rsvd2:9;                     // 15:7 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union BGCRC_INTFRC_REG {
    Uint32  all;
    struct  BGCRC_INTFRC_BITS  bit;
};

struct BGCRC_LOCK_BITS {                // bits description
    Uint16 BGCRC_EN:1;                  // 0 Register lock configuration
    Uint16 BGCRC_CTRL1:1;               // 1 Register lock configuration
    Uint16 BGCRC_CTRL2:1;               // 2 Register lock configuration
    Uint16 BGCRC_START_ADDR:1;          // 3 Register lock configuration
    Uint16 BGCRC_SEED:1;                // 4 Register lock configuration
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 BGCRC_GOLDEN:1;              // 7 Register lock configuration
    Uint16 rsvd3:1;                     // 8 Reserved
    Uint16 rsvd4:1;                     // 9 Reserved
    Uint16 rsvd5:1;                     // 10 Reserved
    Uint16 rsvd6:1;                     // 11 Reserved
    Uint16 rsvd7:1;                     // 12 Reserved
    Uint16 rsvd8:1;                     // 13 Reserved
    Uint16 BGCRC_WD_CFG:1;              // 14 Register lock configuration
    Uint16 BGCRC_WD_MIN:1;              // 15 Register lock configuration
    Uint16 BGCRC_WD_MAX:1;              // 16 Register lock configuration
    Uint16 rsvd9:1;                     // 17 Reserved
    Uint16 rsvd10:1;                    // 18 Reserved
    Uint16 rsvd11:1;                    // 19 Reserved
    Uint16 rsvd12:1;                    // 20 Reserved
    Uint16 rsvd13:1;                    // 21 Reserved
    Uint16 rsvd14:1;                    // 22 Reserved
    Uint16 BGCRC_NMIFRC:1;              // 23 Register lock configuration
    Uint16 rsvd15:1;                    // 24 Reserved
    Uint16 rsvd16:1;                    // 25 Reserved
    Uint16 BGCRC_INTEN:1;               // 26 Register lock configuration
    Uint16 rsvd17:1;                    // 27 Reserved
    Uint16 rsvd18:1;                    // 28 Reserved
    Uint16 BGCRC_INTFRC:1;              // 29 Register lock configuration
    Uint16 rsvd19:1;                    // 30 Reserved
    Uint16 rsvd20:1;                    // 31 Reserved
};

union BGCRC_LOCK_REG {
    Uint32  all;
    struct  BGCRC_LOCK_BITS  bit;
};

struct BGCRC_COMMIT_BITS {              // bits description
    Uint16 BGCRC_EN:1;                  // 0 Register lock committed
    Uint16 BGCRC_CTRL1:1;               // 1 Register lock committed
    Uint16 BGCRC_CTRL2:1;               // 2 Register lock committed
    Uint16 BGCRC_START_ADDR:1;          // 3 Register lock committed
    Uint16 BGCRC_SEED:1;                // 4 Register lock committed
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 BGCRC_GOLDEN:1;              // 7 Register lock committed
    Uint16 rsvd3:1;                     // 8 Reserved
    Uint16 rsvd4:1;                     // 9 Reserved
    Uint16 rsvd5:1;                     // 10 Reserved
    Uint16 rsvd6:1;                     // 11 Reserved
    Uint16 rsvd7:1;                     // 12 Reserved
    Uint16 rsvd8:1;                     // 13 Reserved
    Uint16 BGCRC_WD_CFG:1;              // 14 Register lock committed
    Uint16 BGCRC_WD_MIN:1;              // 15 Register lock committed
    Uint16 BGCRC_WD_MAX:1;              // 16 Register lock committed
    Uint16 rsvd9:1;                     // 17 Reserved
    Uint16 rsvd10:1;                    // 18 Reserved
    Uint16 rsvd11:1;                    // 19 Reserved
    Uint16 rsvd12:1;                    // 20 Reserved
    Uint16 rsvd13:1;                    // 21 Reserved
    Uint16 rsvd14:1;                    // 22 Reserved
    Uint16 BGCRC_NMIFRC:1;              // 23 Register lock committed
    Uint16 rsvd15:1;                    // 24 Reserved
    Uint16 rsvd16:1;                    // 25 Reserved
    Uint16 BGCRC_INTEN:1;               // 26 Register lock committed
    Uint16 rsvd17:1;                    // 27 Reserved
    Uint16 rsvd18:1;                    // 28 Reserved
    Uint16 BGCRC_INTFRC:1;              // 29 Register lock committed
    Uint16 rsvd19:1;                    // 30 Reserved
    Uint16 rsvd20:1;                    // 31 Reserved
};

union BGCRC_COMMIT_REG {
    Uint32  all;
    struct  BGCRC_COMMIT_BITS  bit;
};

struct BGCRC_REGS {
    union   BGCRC_EN_REG                     BGCRC_EN;                     // BGCRC Enable
    union   BGCRC_CTRL1_REG                  BGCRC_CTRL1;                  // BGCRC Control register 1
    union   BGCRC_CTRL2_REG                  BGCRC_CTRL2;                  // BGCRC Control register 2
    Uint32                                   BGCRC_START_ADDR;             // Start address for the BGCRC check
    Uint32                                   BGCRC_SEED;                   // Seed for CRC calculation
    Uint16                                   rsvd1[4];                     // Reserved
    Uint32                                   BGCRC_GOLDEN;                 // Golden CRC to be compared against
    Uint32                                   BGCRC_RESULT;                 // CRC calculated
    Uint32                                   BGCRC_CURR_ADDR;              // Current address regsiter
    Uint16                                   rsvd2[8];                     // Reserved
    union   BGCRC_WD_CFG_REG                 BGCRC_WD_CFG;                 // BGCRC windowed watchdog configuration
    Uint32                                   BGCRC_WD_MIN;                 // BGCRC windowed watchdog min value
    Uint32                                   BGCRC_WD_MAX;                 // BGCRC windowed watchdog max value
    Uint32                                   BGCRC_WD_CNT;                 // BGCRC windowed watchdog count
    Uint16                                   rsvd3[6];                     // Reserved
    union   BGCRC_NMIFLG_REG                 BGCRC_NMIFLG;                 // BGCRC NMI flag register
    union   BGCRC_NMICLR_REG                 BGCRC_NMICLR;                 // BGCRC NMI flag clear register
    union   BGCRC_NMIFRC_REG                 BGCRC_NMIFRC;                 // BGCRC NMI flag force register
    Uint16                                   rsvd4[4];                     // Reserved
    union   BGCRC_INTEN_REG                  BGCRC_INTEN;                  // Interrupt enable
    union   BGCRC_INTFLG_REG                 BGCRC_INTFLG;                 // Interrupt flag
    union   BGCRC_INTCLR_REG                 BGCRC_INTCLR;                 // Interrupt flag clear
    union   BGCRC_INTFRC_REG                 BGCRC_INTFRC;                 // Interrupt flag force
    union   BGCRC_LOCK_REG                   BGCRC_LOCK;                   // BGCRC register map lockconfiguration
    union   BGCRC_COMMIT_REG                 BGCRC_COMMIT;                 // BGCRC register map commit configuration
};

//---------------------------------------------------------------------------
// BGCRC External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct BGCRC_REGS BgcrcCpuRegs;
extern volatile struct BGCRC_REGS BgcrcClaRegs;
#endif
#ifdef CPU2
extern volatile struct BGCRC_REGS BgcrcCpuRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
