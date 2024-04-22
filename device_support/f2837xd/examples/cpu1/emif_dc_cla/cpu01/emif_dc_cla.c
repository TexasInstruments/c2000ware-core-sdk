//###########################################################################
//
// FILE:   emif_dc_cla.c
//
// TITLE:  EMIF Daughtercard CLA Transfer
//
//! \addtogroup cpu01_example_list
//! <h1>EMIF Daughtercard CLA Transfer (emif_dc_cla)</h1>
//!
//!  This example runs on an EMIF Daughtercard that connects through the
//!  high density connector on F2837X evaluation boards with EMIF2 access:
//!    - TMDSCNCD28379D
//!
//!  Block data is transferred from internal memory to EMIF2 CS2 ASRAM
//!  using the CLA and verified after transfer. CLA can only access
//!  EMIF2 CS2.
//!
//!  The source and destination locations can be changed using the
//!  DATA_SECTION pragmas.
//!
//!  The following values must match the target evaluation board:
//!    - EMIF_NUM (emif_dc_cla.c)
//!    - EMIF_DC_F2837X_LAUNCHPAD_V1 (emif_dc.h)
//!    - _LAUNCHXL_F28377S or _LAUNCHXL_F28379D (Predefined Symbols)
//!
//
//###########################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Included Files
//
#include "F28x_Project.h"
#include "emif_dc.h"
#include "cla_memcpy16.h"

//
// Constants
//
#define EMIF_NUM      EMIF_DC_F2837X_CONTROLCARD_EMIF_NUM
#define BUFFER_WORDS  256

//
// Global Variabls
//
#pragma DATA_SECTION(srcBuffer, "CLADataLS0");
#pragma DATA_SECTION(dstBuffer, ".em2_cs2");
Uint16 srcBuffer[BUFFER_WORDS];
Uint16 dstBuffer[BUFFER_WORDS];

#pragma DATA_SECTION(ClaSrcAddr, "CpuToCla1MsgRAM");
Uint16 ClaSrcAddr;

#pragma DATA_SECTION(ClaDstAddr, "CpuToCla1MsgRAM");
Uint16 ClaDstAddr;

#pragma DATA_SECTION(Cla16bWords, "CpuToCla1MsgRAM");
Uint32 Cla16bWords;

//
// Local Function Prototypes
//
void CLA_configClaMemory(void);
void CLA_initCpu1Cla1(void);

//
// Main
//
void main(void)
{
    Uint16 word;
    Uint16 errors;

    //
    // Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    //
    InitSysCtrl();

    //
    // Initialize EMIF module for use with daughtercard
    //
    EMIF_DC_setupPinmux(EMIF_NUM, GPIO_MUX_CPU1);
    EMIF_DC_initModule(EMIF_NUM);
    EMIF_DC_initCS0(EMIF_NUM);
    EMIF_DC_initCS2(EMIF_NUM, EMIF_DC_ASRAM);

    //
    // Initialize CLA module for transfer
    //
    CLA_configClaMemory();
    CLA_initCpu1Cla1();

    ClaSrcAddr  = (Uint16)srcBuffer;
    ClaDstAddr  = (Uint16)dstBuffer;
    Cla16bWords = BUFFER_WORDS;

    //
    // Initialize data buffers
    //
    for(word=0; word<BUFFER_WORDS; word++)
    {
        srcBuffer[word] = word;
        dstBuffer[word] = 0;
    }

    //
    // Verify that data buffers have correct starting values
    // If buffers are not initialized correctly, check the following:
    //      EMIF_NUM (emif_dc_cla.c)
    //      EMIF_DC_F2837X_LAUNCHPAD_V1 (emif_dc.h)
    //      _LAUNCHXL_F28377S or _LAUNCHXL_F28379D (Predefined Symbols)
    //
    errors = 0;

    for(word=0; word<BUFFER_WORDS; word++)
    {
        if(srcBuffer[word] != word)
        {
            errors++;
            ESTOP0;
            break;
        }
        if(dstBuffer[word] != 0)
        {
            errors++;
            ESTOP0;
            break;
        }
    }

    //
    // Execute and wait for block data transfer by forcing CLA trigger
    //
    Cla1ForceTask2andWait();

    //
    // Verify that block data has been transferred
    //
    for(word=0; word<BUFFER_WORDS; word++)
    {
        if(srcBuffer[word] != word)
        {
            errors++;
            ESTOP0;
            break;
        }

        if(dstBuffer[word] != word)
        {
            errors++;
            ESTOP0;
            break;
        }
    }

    if(errors == 0)
    {
        ESTOP0; // PASS
    }
    else
    {
        ESTOP0; // FAIL
    }
}

//
// CLA_configClaMemory - Configure CLA memory sections
//
void CLA_configClaMemory(void)
{
    EALLOW;

    //
    // Initialize and wait for CLA1ToCPUMsgRAM
    //
    MemCfgRegs.MSGxINIT.bit.INIT_CLA1TOCPU = 1;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CLA1TOCPU != 1){};

    //
    // Initialize and wait for CPUToCLA1MsgRAM
    //
    MemCfgRegs.MSGxINIT.bit.INIT_CPUTOCLA1 = 1;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CPUTOCLA1 != 1){};

    //
    // Select LS4RAM and LS5RAM to be the programming space for the CLA
    // First configure the CLA to be the master for LS4 and LS5 and then
    // set the space to be a program block
    //
    MemCfgRegs.LSxMSEL.bit.MSEL_LS4 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS4 = 1;

    MemCfgRegs.LSxMSEL.bit.MSEL_LS5 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS5 = 1;

    //
    // Next configure LS0RAM and LS1RAM as data spaces for the CLA
    // First configure the CLA to be the master for LS0(1) and then
    // set the spaces to be code blocks
    //
    MemCfgRegs.LSxMSEL.bit.MSEL_LS0 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS0 = 0;

    MemCfgRegs.LSxMSEL.bit.MSEL_LS1 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS1 = 0;

    EDIS;
}

//
// CLA_initCpu1Cla1 - Initialize CLA1 task vectors and end of task interrupts
//
void CLA_initCpu1Cla1(void)
{
    //
    // Compute all CLA task vectors
    // On Type-1 CLAs the MVECT registers accept full 16-bit task addresses as
    // opposed to offsets used on older Type-0 CLAs
    //
    EALLOW;
    Cla1Regs.MVECT1 = (uint16_t)(&Cla1Task1);
    Cla1Regs.MVECT2 = (uint16_t)(&Cla1Task2);
    Cla1Regs.MVECT3 = (uint16_t)(&Cla1Task3);
    Cla1Regs.MVECT4 = (uint16_t)(&Cla1Task4);
    Cla1Regs.MVECT5 = (uint16_t)(&Cla1Task5);
    Cla1Regs.MVECT6 = (uint16_t)(&Cla1Task6);
    Cla1Regs.MVECT7 = (uint16_t)(&Cla1Task7);
    Cla1Regs.MVECT8 = (uint16_t)(&Cla1Task8);

    //
    // Enable the IACK instruction to start a task on CLA in software
    // for all  8 CLA tasks. Also, globally enable all 8 tasks (or a
    // subset of tasks) by writing to their respective bits in the
    // MIER register
    //
    Cla1Regs.MCTL.bit.IACKE = 1;
    Cla1Regs.MIER.all = 0x00FF;
}

//
// End of file
//
