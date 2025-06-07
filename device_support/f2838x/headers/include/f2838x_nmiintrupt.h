//###########################################################################
//
// FILE:    f2838x_nmiintrupt.h
//
// TITLE:   Definitions for the NMIINTRUPT registers.
//
//###########################################################################
// 
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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

#ifndef F2838X_NMIINTRUPT_H
#define F2838X_NMIINTRUPT_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// NMIINTRUPT Individual Register Bit Definitions:

struct NMICFG_BITS {                    // bits description
    Uint16 NMIE:1;                      // 0 Global NMI Enable
    Uint16 rsvd1:15;                    // 15:1 Reserved
};

union NMICFG_REG {
    Uint16  all;
    struct  NMICFG_BITS  bit;
};

struct NMIFLG_BITS {                    // bits description
    Uint16 NMIINT:1;                    // 0 NMI Interrupt Flag
    Uint16 CLOCKFAIL:1;                 // 1 Clock Fail Interrupt Flag
    Uint16 RAMUNCERR:1;                 // 2 RAM Uncorrectable Error NMI Flag
    Uint16 FLUNCERR:1;                  // 3 Flash Uncorrectable Error NMI Flag
    Uint16 CPU1HWBISTERR:1;             // 4 HW BIST Error NMI Flag
    Uint16 CPU2HWBISTERR:1;             // 5 HW BIST Error NMI Flag
    Uint16 PIEVECTERR:1;                // 6 PIE Vector Fetch Error Flag
    Uint16 ERADNMI:1;                   // 7 ERAD Module NMI Flag
    Uint16 CLBNMI:1;                    // 8 Configurable Logic Block NMI Flag
    Uint16 CPU2WDRSn:1;                 // 9 CPU2 WDRSn Reset Indication Flag
    Uint16 CPU2NMIWDRSn:1;              // 10 CPU2 NMIWDRSn Reset Indication Flag
    Uint16 rsvd1:1;                     // 11 Reserved
    Uint16 CMNMIWDRSn:1;                // 12 CM NMI watch dog has timed out.
    Uint16 ECATNMIn:1;                  // 13 NMI from EtherCAT reset out
    Uint16 CRC_FAIL:1;                  // 14 CRC calculation failed.
    Uint16 MCAN_ERR:1;                  // 15 MCAN module generated an ECC error.
};

union NMIFLG_REG {
    Uint16  all;
    struct  NMIFLG_BITS  bit;
};

struct NMIFLGCLR_BITS {                 // bits description
    Uint16 NMIINT:1;                    // 0 NMIINT Flag Clear
    Uint16 CLOCKFAIL:1;                 // 1 CLOCKFAIL Flag Clear
    Uint16 RAMUNCERR:1;                 // 2 RAMUNCERR Flag Clear
    Uint16 FLUNCERR:1;                  // 3 FLUNCERR Flag Clear
    Uint16 CPU1HWBISTERR:1;             // 4 CPU1HWBISTERR Flag Clear
    Uint16 CPU2HWBISTERR:1;             // 5 CPU2HWBISTERR Flag Clear
    Uint16 PIEVECTERR:1;                // 6 PIEVECTERR Flag Clear
    Uint16 ERADNMI:1;                   // 7 ERADNMI Flag Clear
    Uint16 CLBNMI:1;                    // 8 CLBNMI Flag Clear
    Uint16 CPU2WDRSn:1;                 // 9 CPU2WDRSn Flag Clear
    Uint16 CPU2NMIWDRSn:1;              // 10 CPU2NMIWDRSn Flag Clear
    Uint16 rsvd1:1;                     // 11 Reserved
    Uint16 CMNMIWDRSn:1;                // 12 DCDCOLF Flag Clear
    Uint16 ECATNMIn:1;                  // 13 ECATNMIn flag clear
    Uint16 CRC_FAIL:1;                  // 14 CRC_FAIL flag clear
    Uint16 MCAN_ERR:1;                  // 15 MCAN_ERR flag clear
};

union NMIFLGCLR_REG {
    Uint16  all;
    struct  NMIFLGCLR_BITS  bit;
};

struct NMIFLGFRC_BITS {                 // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 CLOCKFAIL:1;                 // 1 CLOCKFAIL Flag Force
    Uint16 RAMUNCERR:1;                 // 2 RAMUNCERR Flag Force
    Uint16 FLUNCERR:1;                  // 3 FLUNCERR Flag Force
    Uint16 CPU1HWBISTERR:1;             // 4 CPU1HWBISTERR Flag Force
    Uint16 CPU2HWBISTERR:1;             // 5 CPU2HWBISTERR Flag Force
    Uint16 PIEVECTERR:1;                // 6 PIEVECTERR Flag Force
    Uint16 ERADNMI:1;                   // 7 ERADNMI Flag Force
    Uint16 CLBNMI:1;                    // 8 CLBNMI Flag Force
    Uint16 CPU2WDRSn:1;                 // 9 CPU2WDRSn Flag Force
    Uint16 CPU2NMIWDRSn:1;              // 10 CPU2NMIWDRSn Flag Force
    Uint16 rsvd2:1;                     // 11 Reserved
    Uint16 CMNMIWDRSn:1;                // 12 DCDCOLF Flag Force
    Uint16 ECATNMIn:1;                  // 13 ECATNMIn flag force
    Uint16 CRC_FAIL:1;                  // 14 CRC_FAIL flag force
    Uint16 MCAN_ERR:1;                  // 15 MCAN_ERR flag force
};

union NMIFLGFRC_REG {
    Uint16  all;
    struct  NMIFLGFRC_BITS  bit;
};

struct NMISHDFLG_BITS {                 // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 CLOCKFAIL:1;                 // 1 Shadow CLOCKFAIL Flag
    Uint16 RAMUNCERR:1;                 // 2 Shadow RAMUNCERR Flag
    Uint16 FLUNCERR:1;                  // 3 Shadow FLUNCERR Flag
    Uint16 CPU1HWBISTERR:1;             // 4 Shadow CPU1HWBISTERR Flag
    Uint16 CPU2HWBISTERR:1;             // 5 Shadow CPU2HWBISTERR Flag
    Uint16 PIEVECTERR:1;                // 6 Shadow PIEVECTERR Flag
    Uint16 ERADNMI:1;                   // 7 Shadow ERADNMI Flag
    Uint16 CLBNMI:1;                    // 8 Shadow CLBNMI Flag
    Uint16 CPU2WDRSn:1;                 // 9 Shadow CPU2WDRSn Flag
    Uint16 CPU2NMIWDRSn:1;              // 10 Shadow CPU2NMIWDRSn Flag
    Uint16 rsvd2:1;                     // 11 Reserved
    Uint16 CMNMIWDRSn:1;                // 12 Shadow DCDCOLF Flag
    Uint16 ECATNMIn:1;                  // 13 ECATNMIn flag
    Uint16 CRC_FAIL:1;                  // 14 CRC_FAIL flag
    Uint16 MCAN_ERR:1;                  // 15 MCAN_ERR flag
};

union NMISHDFLG_REG {
    Uint16  all;
    struct  NMISHDFLG_BITS  bit;
};

struct ERRORSTS_BITS {                  // bits description
    Uint16 ERROR:1;                     // 0 Error flag.
    Uint16 PINSTS:1;                    // 1 Error pin status.
    Uint16 rsvd1:14;                    // 15:2 Reserved
};

union ERRORSTS_REG {
    Uint16  all;
    struct  ERRORSTS_BITS  bit;
};

struct ERRORSTSCLR_BITS {               // bits description
    Uint16 ERROR:1;                     // 0 ERRORFLG.ERROR clear bit
    Uint16 rsvd1:15;                    // 15:1 Reserved
};

union ERRORSTSCLR_REG {
    Uint16  all;
    struct  ERRORSTSCLR_BITS  bit;
};

struct ERRORSTSFRC_BITS {               // bits description
    Uint16 ERROR:1;                     // 0 ERRORSTS.ERROR pin force.
    Uint16 rsvd1:15;                    // 15:1 Reserved
};

union ERRORSTSFRC_REG {
    Uint16  all;
    struct  ERRORSTSFRC_BITS  bit;
};

struct ERRORCTL_BITS {                  // bits description
    Uint16 ERRORPOLSEL:1;               // 0 ERROR pin polarity select
    Uint16 rsvd1:15;                    // 15:1 Reserved
};

union ERRORCTL_REG {
    Uint16  all;
    struct  ERRORCTL_BITS  bit;
};

struct ERRORLOCK_BITS {                 // bits description
    Uint16 ERRORCTL:1;                  // 0 ERRORCTL Lock bit
    Uint16 rsvd1:15;                    // 15:1 Reserved
};

union ERRORLOCK_REG {
    Uint16  all;
    struct  ERRORLOCK_BITS  bit;
};

struct NMI_INTRUPT_REGS {
    union   NMICFG_REG                       NMICFG;                       // NMI Configuration Register
    union   NMIFLG_REG                       NMIFLG;                       // NMI Flag Register (SYSRsn Clear)
    union   NMIFLGCLR_REG                    NMIFLGCLR;                    // NMI Flag Clear Register
    union   NMIFLGFRC_REG                    NMIFLGFRC;                    // NMI Flag Force Register
    Uint16                                   NMIWDCNT;                     // NMI Watchdog Counter Register
    Uint16                                   NMIWDPRD;                     // NMI Watchdog Period Register
    union   NMISHDFLG_REG                    NMISHDFLG;                    // NMI Shadow Flag Register
    union   ERRORSTS_REG                     ERRORSTS;                     // Error pin status
    union   ERRORSTSCLR_REG                  ERRORSTSCLR;                  // ERRORSTS clear register
    union   ERRORSTSFRC_REG                  ERRORSTSFRC;                  // ERRORSTS force register
    union   ERRORCTL_REG                     ERRORCTL;                     // Error pin control register
    union   ERRORLOCK_REG                    ERRORLOCK;                    // Lock register to Error pin registers.
};

//---------------------------------------------------------------------------
// NMIINTRUPT External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct NMI_INTRUPT_REGS NmiIntruptRegs;
#endif
#ifdef CPU2
extern volatile struct NMI_INTRUPT_REGS NmiIntruptRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
