//###########################################################################
//
// FILE:   cla_crc8_cpu01.c
//
// TITLE:  CLA CRC8 Example for F2837xD.
//
//! \addtogroup cpu01_example_list
//! <h1>CLA CRC8 Table-Lookup Algorithm (cla_crc8_cpu01)</h1>
//!
//! This example implements a table lookup method of determining
//! the 8-bit CRC of a message sequence. The polynomial used is 0x07.
//!
//! \b Memory \b Allocation \n
//!  - CLA1 Data RAM 0(RAMLS0)
//!    - table - CRC Lookup table
//!  - CLA1 to CPU Message RAM
//!    - crc8_msg1 - CRC of message 1
//!    - crc8_msg2 - CRC of message 2
//!    - crc8_msg3 - CRC of message 3
//!    - crc8_msg4 - CRC of message 4
//!  - CPU to CLA1 Message RAM
//!    - msg1 - Test message 1
//!    - msg2 - Test message 2
//!    - msg3 - Test message 3
//!    - msg4 - Test message 4
//!
//! \b Watch \b Variables \n
//!  - crc8_msg1 - CRC of message 1
//!  - crc8_msg2 - CRC of message 2
//!  - crc8_msg3 - CRC of message 3
//!  - crc8_msg4 - CRC of message 4
//!  - pass
//!  - fail
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
#include "cla_crc8_shared.h"

//
// Defines
//
#define WAITSTEP     asm(" RPT #255 || NOP")

//
// Globals
//

//
//Task 1 (C) Variables
// NOTE: Do not initialize the Message RAM variables globally, they will be
// reset during the message ram initialization phase in the CLA memory
// configuration routine
//
#ifdef __cplusplus

#pragma DATA_SECTION("CLADataLS0")
uint16_t msg1[5] =  {0x5543, 0x3669, 0x3318, 0x5f57, 0x2ba2};
#pragma DATA_SECTION("CLADataLS0")
uint16_t msg2[12] = {0x1e18, 0x1842, 0x13e7, 0x77be, 0x4859, 0x20d7, 0x3c5d,
                     0x2efd, 0x2af7, 0x112c, 0x0f13, 0x06fa};

#pragma DATA_SECTION("CLADataLS0")
uint16_t msg3[5] =  {0x6bd9, 0x335f, 0x1dfc, 0x4d84, 0x17fd};
#pragma DATA_SECTION("CLADataLS0")
uint16_t msg4[12] = {0x00e4, 0x0af8, 0x6f37, 0x3d39, 0x1c63, 0x3702, 0x43c1,
                     0x38e3, 0x33cb, 0x6ed8, 0x4a56, 0x221a};

#else
#pragma DATA_SECTION(msg1,"CLADataLS0")
uint16_t msg1[5] =  {0x5543, 0x3669, 0x3318, 0x5f57, 0x2ba2};

#pragma DATA_SECTION(msg2,"CLADataLS0")
uint16_t msg2[12] = {0x1e18, 0x1842, 0x13e7, 0x77be, 0x4859, 0x20d7, 0x3c5d,
                     0x2efd, 0x2af7, 0x112c, 0x0f13, 0x06fa};
#pragma DATA_SECTION(msg3,"CLADataLS0")
uint16_t msg3[5] =  {0x6bd9, 0x335f, 0x1dfc, 0x4d84, 0x17fd};
#pragma DATA_SECTION(msg4,"CLADataLS0")
uint16_t msg4[12] = {0x00e4, 0x0af8, 0x6f37, 0x3d39, 0x1c63, 0x3702, 0x43c1,
                     0x38e3, 0x33cb, 0x6ed8, 0x4a56, 0x221a};

#endif //__cplusplus

#ifdef __cplusplus
#pragma DATA_SECTION("Cla1ToCpuMsgRAM")
uint16_t crc8_msg1;
#pragma DATA_SECTION("Cla1ToCpuMsgRAM")
uint16_t crc8_msg2;
#pragma DATA_SECTION("Cla1ToCpuMsgRAM")
uint16_t crc8_msg3;

#pragma DATA_SECTION("Cla1ToCpuMsgRAM")
uint16_t crc8_msg4
#else
#pragma DATA_SECTION(crc8_msg1,"Cla1ToCpuMsgRAM")
uint16_t crc8_msg1;
#pragma DATA_SECTION(crc8_msg2,"Cla1ToCpuMsgRAM")
uint16_t crc8_msg2;
#pragma DATA_SECTION(crc8_msg3,"Cla1ToCpuMsgRAM")
uint16_t crc8_msg3;
#pragma DATA_SECTION(crc8_msg4,"Cla1ToCpuMsgRAM")
uint16_t crc8_msg4;
#endif //__cplusplus

//
//Task 2 (C) Variables
//

//
//Task 3 (C) Variables
//

//
//Task 4 (C) Variables
//

//
//Task 5 (C) Variables
//

//
//Task 6 (C) Variables
//

//
//Task 7 (C) Variables
//

//
//Task 8 (C) Variables
//

//
//Common (C) Variables
//The Exponential table
//
#ifdef __cplusplus
#pragma DATA_SECTION("CLADataLS0")
#else
#pragma DATA_SECTION(table,"CLADataLS1")
#endif //__cplusplus
const uint16_t table[256] = {
  0x0000, 0x0007, 0x000E, 0x0009, 0x001C, 0x001B, 0x0012, 0x0015,
  0x0038, 0x003F, 0x0036, 0x0031, 0x0024, 0x0023, 0x002A, 0x002D,
  0x0070, 0x0077, 0x007E, 0x0079, 0x006C, 0x006B, 0x0062, 0x0065,
  0x0048, 0x004F, 0x0046, 0x0041, 0x0054, 0x0053, 0x005A, 0x005D,
  0x00E0, 0x00E7, 0x00EE, 0x00E9, 0x00FC, 0x00FB, 0x00F2, 0x00F5,
  0x00D8, 0x00DF, 0x00D6, 0x00D1, 0x00C4, 0x00C3, 0x00CA, 0x00CD,
  0x0090, 0x0097, 0x009E, 0x0099, 0x008C, 0x008B, 0x0082, 0x0085,
  0x00A8, 0x00AF, 0x00A6, 0x00A1, 0x00B4, 0x00B3, 0x00BA, 0x00BD,
  0x00C7, 0x00C0, 0x00C9, 0x00CE, 0x00DB, 0x00DC, 0x00D5, 0x00D2,
  0x00FF, 0x00F8, 0x00F1, 0x00F6, 0x00E3, 0x00E4, 0x00ED, 0x00EA,
  0x00B7, 0x00B0, 0x00B9, 0x00BE, 0x00AB, 0x00AC, 0x00A5, 0x00A2,
  0x008F, 0x0088, 0x0081, 0x0086, 0x0093, 0x0094, 0x009D, 0x009A,
  0x0027, 0x0020, 0x0029, 0x002E, 0x003B, 0x003C, 0x0035, 0x0032,
  0x001F, 0x0018, 0x0011, 0x0016, 0x0003, 0x0004, 0x000D, 0x000A,
  0x0057, 0x0050, 0x0059, 0x005E, 0x004B, 0x004C, 0x0045, 0x0042,
  0x006F, 0x0068, 0x0061, 0x0066, 0x0073, 0x0074, 0x007D, 0x007A,
  0x0089, 0x008E, 0x0087, 0x0080, 0x0095, 0x0092, 0x009B, 0x009C,
  0x00B1, 0x00B6, 0x00BF, 0x00B8, 0x00AD, 0x00AA, 0x00A3, 0x00A4,
  0x00F9, 0x00FE, 0x00F7, 0x00F0, 0x00E5, 0x00E2, 0x00EB, 0x00EC,
  0x00C1, 0x00C6, 0x00CF, 0x00C8, 0x00DD, 0x00DA, 0x00D3, 0x00D4,
  0x0069, 0x006E, 0x0067, 0x0060, 0x0075, 0x0072, 0x007B, 0x007C,
  0x0051, 0x0056, 0x005F, 0x0058, 0x004D, 0x004A, 0x0043, 0x0044,
  0x0019, 0x001E, 0x0017, 0x0010, 0x0005, 0x0002, 0x000B, 0x000C,
  0x0021, 0x0026, 0x002F, 0x0028, 0x003D, 0x003A, 0x0033, 0x0034,
  0x004E, 0x0049, 0x0040, 0x0047, 0x0052, 0x0055, 0x005C, 0x005B,
  0x0076, 0x0071, 0x0078, 0x007F, 0x006A, 0x006D, 0x0064, 0x0063,
  0x003E, 0x0039, 0x0030, 0x0037, 0x0022, 0x0025, 0x002C, 0x002B,
  0x0006, 0x0001, 0x0008, 0x000F, 0x001A, 0x001D, 0x0014, 0x0013,
  0x00AE, 0x00A9, 0x00A0, 0x00A7, 0x00B2, 0x00B5, 0x00BC, 0x00BB,
  0x0096, 0x0091, 0x0098, 0x009F, 0x008A, 0x008D, 0x0084, 0x0083,
  0x00DE, 0x00D9, 0x00D0, 0x00D7, 0x00C2, 0x00C5, 0x00CC, 0x00CB,
  0x00E6, 0x00E1, 0x00E8, 0x00EF, 0x00FA, 0x00FD, 0x00F4, 0x00F3,
};

uint16_t pass=0;
uint16_t fail=0;

//
// Function Prototypes
//
void CLA_runTest(void);
void CLA_configClaMemory(void);
void CLA_initCpu1Cla1(void);
__interrupt void cla1Isr1();
__interrupt void cla1Isr2();
__interrupt void cla1Isr3();
__interrupt void cla1Isr4();
__interrupt void cla1Isr5();
__interrupt void cla1Isr6();
__interrupt void cla1Isr7();
__interrupt void cla1Isr8();

//
// Main
//
void main(void)
{
//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
    InitSysCtrl();

//
// Step 2. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
    DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
//
    InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
    InitPieVectTable();

//
// Step 3. Configure the CLA memory spaces first followed by
// the CLA task vectors
//
    CLA_configClaMemory();
    CLA_initCpu1Cla1();

//
// Step 4. Enable global Interrupts and higher priority real-time debug events:
//
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

//
// Step 5. Run the test
//
    CLA_runTest();

//
// Software breakpoint
//
    asm(" ESTOP0");
}

//
// CLA_runTest - Execute CLA task tests for specified vectors
//
void CLA_runTest(void)
{
    uint16_t const gold1 = 0x0043;
    uint16_t const gold2 = 0x009f;
    uint16_t const gold3 = 0x00CE;
    uint16_t const gold4 = 0x00c0;

    Cla1ForceTask1andWait();

    (gold1 != crc8_msg1)? fail++ : pass++;
    (gold2 != crc8_msg2)? fail++ : pass++;
    (gold3 != crc8_msg3)? fail++ : pass++;
    (gold4 != crc8_msg4)? fail++ : pass++;

#if 0
    Cla1ForceTask2andWait();
    WAITSTEP;

    Cla1ForceTask3andWait();
    WAITSTEP;

    Cla1ForceTask4andWait();
    WAITSTEP;

    Cla1ForceTask5andWait();
    WAITSTEP;

    Cla1ForceTask6andWait();
    WAITSTEP;

    Cla1ForceTask7andWait();
    WAITSTEP;

    Cla1ForceTask8andWait();
    WAITSTEP;
#endif
}

//
// CLA_configClaMemory - Configure CLA memory sections
//
void CLA_configClaMemory(void)
{
    extern uint32_t Cla1funcsRunStart, Cla1funcsLoadStart, Cla1funcsLoadSize;
    EALLOW;

#ifdef _FLASH
    //
    // Copy over code from FLASH to RAM
    //
    memcpy((uint32_t *)&Cla1funcsRunStart, (uint32_t *)&Cla1funcsLoadStart,
           (uint32_t)&Cla1funcsLoadSize);
#endif //_FLASH

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

    //
    // Configure the vectors for the end-of-task interrupt for all
    // 8 tasks
    //
    PieVectTable.CLA1_1_INT = &cla1Isr1;
    PieVectTable.CLA1_2_INT = &cla1Isr2;
    PieVectTable.CLA1_3_INT = &cla1Isr3;
    PieVectTable.CLA1_4_INT = &cla1Isr4;
    PieVectTable.CLA1_5_INT = &cla1Isr5;
    PieVectTable.CLA1_6_INT = &cla1Isr6;
    PieVectTable.CLA1_7_INT = &cla1Isr7;
    PieVectTable.CLA1_8_INT = &cla1Isr8;

    //
    // Enable CLA interrupts at the group and subgroup levels
    //
    PieCtrlRegs.PIEIER11.all = 0xFFFF;
    IER |= (M_INT11 );
}

//
// cla1Isr1 - CLA1 ISR 1
//
__interrupt void cla1Isr1 ()
{
    //
    // Acknowledge the end-of-task interrupt for task 1
    //
    PieCtrlRegs.PIEACK.all = M_INT11;

    //
    // Uncomment to halt debugger and stop here
    //
//    asm(" ESTOP0");
}

//
// cla1Isr2 - CLA1 ISR 2
//
__interrupt void cla1Isr2 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr3 - CLA1 ISR 3
//
__interrupt void cla1Isr3 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr4 - CLA1 ISR 4
//
__interrupt void cla1Isr4 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr5 - CLA1 ISR 5
//
__interrupt void cla1Isr5 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr6 - CLA1 ISR 6
//
__interrupt void cla1Isr6 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr7 - CLA1 ISR 7
//
__interrupt void cla1Isr7 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr8 - CLA1 ISR 8
//
__interrupt void cla1Isr8 ()
{
    //
    // Acknowledge the end-of-task interrupt for task 8
    //
    PieCtrlRegs.PIEACK.all = M_INT11;

    //
    // Uncomment to halt debugger and stop here
    //
//    asm(" ESTOP0");
}

//
// End of file
//
