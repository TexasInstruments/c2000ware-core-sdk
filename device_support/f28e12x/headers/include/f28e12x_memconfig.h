//###########################################################################
//
// FILE:    f28e12x_memconfig.h
//
// TITLE:   Definitions for the MEMCONFIG registers.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F28E12X_MEMCONFIG_H
#define F28E12X_MEMCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// MEMCONFIG Individual Register Bit Definitions:

struct DxLOCK_BITS {                    // bits description
    Uint16 LOCK_M0:1;                   // 0 M0 RAM Lock bits
    Uint16 LOCK_M1:1;                   // 1 M1 RAM Lock bits
    Uint16 LOCK_PIEVECT:1;              // 2 PIEVECT RAM Lock bits
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DxLOCK_REG {
    Uint32  all;
    struct  DxLOCK_BITS  bit;
};

struct DxCOMMIT_BITS {                  // bits description
    Uint16 COMMIT_M0:1;                 // 0 M0 RAM Permanent Lock bits
    Uint16 COMMIT_M1:1;                 // 1 M1 RAM Permanent Lock bits
    Uint16 COMMIT_PIEVECT:1;            // 2 PIEVECT RAM Permanent Lock bits
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DxCOMMIT_REG {
    Uint32  all;
    struct  DxCOMMIT_BITS  bit;
};

struct DxTEST_BITS {                    // bits description
    Uint16 TEST_M0:2;                   // 1:0 Selects the different modes for M0 RAM
    Uint16 TEST_M1:2;                   // 3:2 Selects the different modes for M1 RAM
    Uint16 TEST_PIEVECT:2;              // 5:4 Selects the different modes for PIEVECT RAM
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DxTEST_REG {
    Uint32  all;
    struct  DxTEST_BITS  bit;
};

struct DxINIT_BITS {                    // bits description
    Uint16 INIT_M0:1;                   // 0 RAM Initialization control for M0 RAM.
    Uint16 INIT_M1:1;                   // 1 RAM Initialization control for M1 RAM.
    Uint16 INIT_PIEVECT:1;              // 2 RAM Initialization control for PIEVECT RAM.
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DxINIT_REG {
    Uint32  all;
    struct  DxINIT_BITS  bit;
};

struct DxINITDONE_BITS {                // bits description
    Uint16 INITDONE_M0:1;               // 0 RAM Initialization status for M0 RAM.
    Uint16 INITDONE_M1:1;               // 1 RAM Initialization status for M1 RAM.
    Uint16 INITDONE_PIEVECT:1;          // 2 RAM Initialization status for PIEVECT RAM.
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DxINITDONE_REG {
    Uint32  all;
    struct  DxINITDONE_BITS  bit;
};

struct DxRAMTEST_LOCK_BITS {            // bits description
    Uint16 M0_TEST:1;                   // 0 M0_TEST_LOCK
    Uint16 M1_TEST:1;                   // 1 M1_TEST_LOCK
    Uint16 PIEVECT_TEST:1;              // 2 PIEVECT_TEST_LOCK
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 Key:16;                      // 31:16 Key for writing DxRAMTEST lock
};

union DxRAMTEST_LOCK_REG {
    Uint32  all;
    struct  DxRAMTEST_LOCK_BITS  bit;
};

struct GSxLOCK_BITS {                   // bits description
    Uint16 LOCK_GS0:1;                  // 0 GS0 RAM Lock bits
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:14;                    // 15:2 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union GSxLOCK_REG {
    Uint32  all;
    struct  GSxLOCK_BITS  bit;
};

struct GSxCOMMIT_BITS {                 // bits description
    Uint16 COMMIT_GS0:1;                // 0 GS0 RAM Permanent Lock bits
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:14;                    // 15:2 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union GSxCOMMIT_REG {
    Uint32  all;
    struct  GSxCOMMIT_BITS  bit;
};

struct GSxTEST_BITS {                   // bits description
    Uint16 TEST_GS0:2;                  // 1:0 Selects the different modes for GS0 RAM
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union GSxTEST_REG {
    Uint32  all;
    struct  GSxTEST_BITS  bit;
};

struct GSxINIT_BITS {                   // bits description
    Uint16 INIT_GS0:1;                  // 0 RAM Initialization control for GS0 RAM.
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:14;                    // 15:2 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union GSxINIT_REG {
    Uint32  all;
    struct  GSxINIT_BITS  bit;
};

struct GSxINITDONE_BITS {               // bits description
    Uint16 INITDONE_GS0:1;              // 0 RAM Initialization status for GS0 RAM.
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:14;                    // 15:2 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union GSxINITDONE_REG {
    Uint32  all;
    struct  GSxINITDONE_BITS  bit;
};

struct GSxRAMTEST_LOCK_BITS {           // bits description
    Uint16 GS0_TEST:1;                  // 0 GS0_TEST_LOCK
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:14;                    // 15:2 Reserved
    Uint16 Key:16;                      // 31:16 Key for writing GSxRAMTEST lock
};

union GSxRAMTEST_LOCK_REG {
    Uint32  all;
    struct  GSxRAMTEST_LOCK_BITS  bit;
};

struct ROM_LOCK_BITS {                  // bits description
    Uint16 Lock_BOOTROM_SECUREROM:1;    // 0  BOOTROM and SECURE ROM lock bits
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 KEY:16;                      // 31:16 Key for writing ROM LOCK
};

union ROM_LOCK_REG {
    Uint32  all;
    struct  ROM_LOCK_BITS  bit;
};

struct ROM_TEST_BITS {                  // bits description
    Uint16 TEST_BOOTROM_SECUREROM:2;    // 1:0 Selects the different modes for BOOTROM and SECURE ROM
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ROM_TEST_REG {
    Uint32  all;
    struct  ROM_TEST_BITS  bit;
};

struct ROM_FORCE_ERROR_BITS {           // bits description
    Uint16 FORCE_BOOTROM_SECUREROM_ERROR:1; // 0 Force Bootrom_SECUREROM Parity Error
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ROM_FORCE_ERROR_REG {
    Uint32  all;
    struct  ROM_FORCE_ERROR_BITS  bit;
};

struct MEM_CFG_REGS {
    union   DxLOCK_REG                       DxLOCK;                       // Dedicated RAM config Lock Register
    union   DxCOMMIT_REG                     DxCOMMIT;                     // Dedicated RAM config Lock Commit Register
    union   DxTEST_REG                       DxTEST;                       // Dedicated RAM TEST Register
    union   DxINIT_REG                       DxINIT;                       // Dedicated RAM Init Register
    union   DxINITDONE_REG                   DxINITDONE;                   // Dedicated RAM InitDone Status Register
    union   DxRAMTEST_LOCK_REG               DxRAMTEST_LOCK;               // Dedicated RAM TEST Lock Register
    Uint16                                   rsvd1[20];                    // Reserved
    union   GSxLOCK_REG                      GSxLOCK;                      // Global Shared RAM Config Lock Register
    union   GSxCOMMIT_REG                    GSxCOMMIT;                    // Global Shared RAM conffig Lock Commit Register
    union   GSxTEST_REG                      GSxTEST;                      // Global Shared RAM TEST Register
    union   GSxINIT_REG                      GSxINIT;                      // Global Shared RAM Init Register
    union   GSxINITDONE_REG                  GSxINITDONE;                  // Global Shared RAM InitDone Status Register
    union   GSxRAMTEST_LOCK_REG              GSxRAMTEST_LOCK;              // Global Shared  RAM TEST Lock Register
    Uint16                                   rsvd2[4];                     // Reserved
    union   ROM_LOCK_REG                     ROM_LOCK;                     // Rom configuration lock register
    union   ROM_TEST_REG                     ROM_TEST;                     // ROM  TEST Register
    union   ROM_FORCE_ERROR_REG              ROM_FORCE_ERROR;              // ROM Force Error register
};

struct UCERRFLG_BITS {                  // bits description
    Uint16 CPU_READ_ERR:1;              // 0 CPU  Uncorrectable Read Error Flag
    Uint16 DMA_READ_ERR:1;              // 1 DMA  Uncorrectable Read Error Flag
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:10;                    // 15:6 Reserved
    Uint16 rsvd6:16;                    // 31:16 Reserved
};

union UCERRFLG_REG {
    Uint32  all;
    struct  UCERRFLG_BITS  bit;
};

struct UCERRSET_BITS {                  // bits description
    Uint16 CPU_READ_ERR:1;              // 0 CPU  Uncorrectable Read Error Flag  set
    Uint16 DMA_READ_ERR:1;              // 1 DMA  Uncorrectable Read Error Flag set
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:10;                    // 15:6 Reserved
    Uint16 rsvd6:16;                    // 31:16 Reserved
};

union UCERRSET_REG {
    Uint32  all;
    struct  UCERRSET_BITS  bit;
};

struct UCERRCLR_BITS {                  // bits description
    Uint16 CPU_READ_ERR:1;              // 0 CPU  Uncorrectable Read Error Flag  clear
    Uint16 DMA_READ_ERR:1;              // 1 DMA  Uncorrectable Read Error Flag clear
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:10;                    // 15:6 Reserved
    Uint16 rsvd6:16;                    // 31:16 Reserved
};

union UCERRCLR_REG {
    Uint32  all;
    struct  UCERRCLR_BITS  bit;
};

struct FLUCERRSTATUS_BITS {             // bits description
    Uint16 UNC_ERR_L:1;                 // 0 Lower 64 bits Uncorrectable error occurred
    Uint16 DIAG_L_FAIL:1;               // 1 Diagnostics of ECC on lower 64 bits.
    Uint16 rsvd1:6;                     // 7:2 Reserved
    Uint16 UNC_ERR_H:1;                 // 8 Upper 64 bits Uncorrectable error occurred
    Uint16 DIAG_H_FAIL:1;               // 9 Diagnostics of ECC on upper 64 bits.
    Uint16 rsvd2:6;                     // 15:10 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union FLUCERRSTATUS_REG {
    Uint32  all;
    struct  FLUCERRSTATUS_BITS  bit;
};

struct FLCERRSTATUS_BITS {              // bits description
    Uint16 FAIL_0_L:1;                  // 0 Lower 64bits Single Bit Error Corrected Value 0
    Uint16 FAIL_1_L:1;                  // 1 Lower 64bits Single Bit Error Corrected Value 1
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 FAIL_0_H:1;                  // 3 Upper 64bits Single Bit Error Corrected Value 0
    Uint16 FAIL_1_H:1;                  // 4 Upper 64bits Single Bit Error Corrected Value 1
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 rsvd3:10;                    // 15:6 Reserved
    Uint16 ERR_POS_L:6;                 // 21:16 Bit Position of Single bit Error in lower 64 bits
    Uint16 ERR_TYPE_L:1;                // 22 Error Type in lower 64 bits
    Uint16 ERR_POS_H:6;                 // 28:23 Bit Position of Single bit Error in upper 64 bits
    Uint16 ERR_TYPE_H:1;                // 29 Error Type in upper 64 bits
    Uint16 rsvd4:2;                     // 31:30 Reserved
};

union FLCERRSTATUS_REG {
    Uint32  all;
    struct  FLCERRSTATUS_BITS  bit;
};

struct CERRFLG_BITS {                   // bits description
    Uint16 CPU_READ_ERR:1;              // 0 CPU  correctable Read Error Flag
    Uint16 DMA_READ_ERR:1;              // 1 DMA  correctable Read Error Flag
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:10;                    // 15:6 Reserved
    Uint16 rsvd6:16;                    // 31:16 Reserved
};

union CERRFLG_REG {
    Uint32  all;
    struct  CERRFLG_BITS  bit;
};

struct CERRSET_BITS {                   // bits description
    Uint16 CPU_READ_ERR_SET:1;          // 0 CPU  correctable Read Error Flag  set
    Uint16 DMA_READ_ERR_SET:1;          // 1 DMA  correctable Read Error Flag set
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:10;                    // 15:6 Reserved
    Uint16 rsvd6:16;                    // 31:16 Reserved
};

union CERRSET_REG {
    Uint32  all;
    struct  CERRSET_BITS  bit;
};

struct CERRCLR_BITS {                   // bits description
    Uint16 CPU_READ_ERR_CLR:1;          // 0 CPU correctable Read Error Flag  clear
    Uint16 DMA_READ_ERR_CLR:1;          // 1 DMA  correctable Read Error Flag clear
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:10;                    // 15:6 Reserved
    Uint16 rsvd6:16;                    // 31:16 Reserved
};

union CERRCLR_REG {
    Uint32  all;
    struct  CERRCLR_BITS  bit;
};

struct CERRTHRES_BITS {                 // bits description
    Uint16 CERRTHRES:16;                // 15:0 Correctable error threshold
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CERRTHRES_REG {
    Uint32  all;
    struct  CERRTHRES_BITS  bit;
};

struct CEINTFLG_BITS {                  // bits description
    Uint16 CEINTFLAG:1;                 // 0 Total corrected error count exceeded threshold flag.
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CEINTFLG_REG {
    Uint32  all;
    struct  CEINTFLG_BITS  bit;
};

struct CEINTCLR_BITS {                  // bits description
    Uint16 CEINTCLR:1;                  // 0 Total corrected error count exceeded flag clear
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CEINTCLR_REG {
    Uint32  all;
    struct  CEINTCLR_BITS  bit;
};

struct CEINTSET_BITS {                  // bits description
    Uint16 CEINTSET:1;                  // 0 Total corrected error count exceeded flag set
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CEINTSET_REG {
    Uint32  all;
    struct  CEINTSET_BITS  bit;
};

struct CEINTEN_BITS {                   // bits description
    Uint16 CEINTEN:1;                   // 0 Total corrected error count exceeded flag enable
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CEINTEN_REG {
    Uint32  all;
    struct  CEINTEN_BITS  bit;
};

struct MEMORY_ERROR_REGS {
    union   UCERRFLG_REG                     UCERRFLG;                     // Uncorrectable Error Flag Register
    union   UCERRSET_REG                     UCERRSET;                     // Uncorrectable Error Flag Set Register
    union   UCERRCLR_REG                     UCERRCLR;                     // Uncorrectable Error Flag Clear Register
    Uint32                                   UCCPUREADDR;                  // Uncorrectable CPU Error Address
    Uint32                                   UCDMAREADDR;                  // Uncorrectable DMA Error Address
    Uint16                                   rsvd1[6];                     // Reserved
    union   FLUCERRSTATUS_REG                FLUCERRSTATUS;                // Flash read uncorrectable ecc err status
    union   FLCERRSTATUS_REG                 FLCERRSTATUS;                 // Flash read correctable ecc err status
    Uint16                                   rsvd2[12];                    // Reserved
    union   CERRFLG_REG                      CERRFLG;                      // Correctable Error Flag Register
    union   CERRSET_REG                      CERRSET;                      // Correctable Error Flag Set Register
    union   CERRCLR_REG                      CERRCLR;                      // Correctable Error Flag Clear Register
    Uint32                                   CCPUREADDR;                   // Correctable CPU  Error Address
    Uint32                                   CDMAREADDR;                   // Correctable DMA Error Address
    Uint16                                   rsvd3[6];                     // Reserved
    Uint32                                   CERRCNT;                      // Correctable Error Count Register
    union   CERRTHRES_REG                    CERRTHRES;                    // Correctable Error Threshold Value Register
    union   CEINTFLG_REG                     CEINTFLG;                     // Correctable Error Interrupt Flag Status Register
    union   CEINTCLR_REG                     CEINTCLR;                     // Correctable Error Interrupt Flag Clear Register
    union   CEINTSET_REG                     CEINTSET;                     // Correctable Error Interrupt Flag Set Register
    union   CEINTEN_REG                      CEINTEN;                      // Correctable Error Interrupt Enable Register
};

struct ROMWAITSTATE_BITS {              // bits description
    Uint16 WSDISABLE:1;                 // 0 ROM Wait State Enable/Disable Control
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ROMWAITSTATE_REG {
    Uint32  all;
    struct  ROMWAITSTATE_BITS  bit;
};

struct ROM_WAIT_STATE_REGS {
    union   ROMWAITSTATE_REG                 ROMWAITSTATE;                 // ROM Wait State Configuration Register
};

struct CPU_RAM_TEST_ERROR_STS_BITS {    // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 UNC_ERROR:1;                 // 1 UNC_ERROR flag
    Uint16 rsvd2:14;                    // 15:2 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CPU_RAM_TEST_ERROR_STS_REG {
    Uint32  all;
    struct  CPU_RAM_TEST_ERROR_STS_BITS  bit;
};

struct CPU_RAM_TEST_ERROR_STS_CLR_BITS {// bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 UNC_ERROR:1;                 // 1 UNC_ERROR flag clear bit
    Uint16 rsvd2:14;                    // 15:2 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CPU_RAM_TEST_ERROR_STS_CLR_REG {
    Uint32  all;
    struct  CPU_RAM_TEST_ERROR_STS_CLR_BITS  bit;
};

struct TEST_ERROR_REGS {
    union   CPU_RAM_TEST_ERROR_STS_REG       CPU_RAM_TEST_ERROR_STS;       // Ram Test: Error Status Register
    union   CPU_RAM_TEST_ERROR_STS_CLR_REG   CPU_RAM_TEST_ERROR_STS_CLR;   // Ram Test: Error Status Clear Register
    Uint32                                   CPU_RAM_TEST_ERROR_ADDR;      // Ram Test: Error address register
};

//---------------------------------------------------------------------------
// MEMCONFIG External References & Function Declarations:
//
extern volatile struct MEM_CFG_REGS MemCfgRegs;
extern volatile struct MEMORY_ERROR_REGS MemoryErrorRegs;
extern volatile struct ROM_WAIT_STATE_REGS RomWaitStateRegs;
extern volatile struct TEST_ERROR_REGS TestErrorRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
