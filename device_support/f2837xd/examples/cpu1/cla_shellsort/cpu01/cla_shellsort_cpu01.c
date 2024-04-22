//###########################################################################
//
// FILE:   cla_shellsort_cpu01.c
//
// TITLE:  Shell Sort Example for F2837xD.
//
//! \addtogroup cpu01_example_list
//! <h1>CLA Shell Sort (cla_shellsort_cpu01)</h1>
//!
//! In this example, Task 1 will perform the shell sort iteratively. Task 2
//! will do the same with mswapf intrinsic and Task 3 will also implement an
//! in-place sort on an integer vector
//!
//! \b Memory \b Allocation \n
//!  - CLA1 Data RAM 1 (RAML2)
//!    - vector3 - Input/Output to task 3(in-place sorting)
//!  - CLA1 to CPU Message RAM
//!    - vector1_sorted - Sorted output Task 1
//!    - vector2_sorted - Sorted output Task 2
//!  - CPU to CLA1 Message RAM
//!    - vector1 - Input vector to task 1
//!    - vector2 - Input vector to task 2
//!
//! \b Watch \b Variables \n
//! - vector3 - Input/Output to task 3(in-place sorting)
//! - vector1_sorted - Sorted output Task 1
//! - vector2_sorted - Sorted output Task 2
//! - vector1 - Input vector to task 1
//! - vector2 - Input vector to task 2
//! - pass - pass counter
//! - fail - fail counter
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
#include "cla_shellsort_shared.h"

//
// Defines
//
#define WAITSTEP     asm(" RPT #255 || NOP")

//
// Globals
//
#ifdef __cplusplus
//
//Task 1 (C) Variables
//
#pragma DATA_SECTION("CpuToCla1MsgRAM");
float  vector1[5];// CLA Input Data

#pragma DATA_SECTION("Cla1ToCpuMsgRAM");
float   vector1_sorted[LENGTH1];// CLA Output Data

//
//Task 2 (C) Variables
//
#pragma DATA_SECTION("CpuToCla1MsgRAM");
float  vector2[10];// CLA Input Data

#pragma DATA_SECTION("Cla1ToCpuMsgRAM");
float   vector2_sorted[LENGTH2];// CLA Output Data

//
//Task 3 (C) Variables
// Note: vector3 is input and output (in-place sort)
//
#pragma DATA_SECTION("CLADataLS0");
int32  vector3[9] =  {-9,-8,1,2,3,0,4,8,9};// CLA Input Data
// CLA Output Data
// vector3_sorted is vector3 (in place sort);

#else
//
//Task 1 (C) Variables
//
#pragma DATA_SECTION(vector1,"CpuToCla1MsgRAM");
float  vector1[5];// CLA Input Data

#pragma DATA_SECTION(vector1_sorted,"Cla1ToCpuMsgRAM");
float   vector1_sorted[LENGTH1];// CLA Output Data

//
//Task 2 (C) Variables
//
#pragma DATA_SECTION(vector2,"CpuToCla1MsgRAM");
float  vector2[10];// CLA Input Data

#pragma DATA_SECTION(vector2_sorted,"Cla1ToCpuMsgRAM");
float   vector2_sorted[LENGTH2];// CLA Output Data

//
//Task 3 (C) Variables
// Note: vector3 is input and output (in-place sort)
//
#pragma DATA_SECTION(vector3,"CLADataLS0");
int32  vector3[9] =  {-9,-8,1,2,3,0,4,8,9};// CLA Input Data
// CLA Output Data
// vector3_sorted is vector3 (in place sort);
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
//

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
}

//
// CLA_runTest - Run task tests with specified vectors
//
void CLA_runTest(void)
{
    //
    //    vector1[5] =  {1.0,-11.3,6.2,10.8,2.5};
    //
    vector1[0] = 1.0;
    vector1[1] = -11.3;
    vector1[2] = 6.2;
    vector1[3] = 10.8;
    vector1[4] = 2.5;

    //
    //    vector2[10] = {-10.1,-9.9,-8.8,1.0,2.2,3.3,0.0,4.4,8.8,9.9}
    //
    vector2[0] = -10.1;
    vector2[1] = -9.9;
    vector2[2] = -8.8;
    vector2[3] = 1.0;
    vector2[4] = 2.2;
    vector2[5] = 3.3;
    vector2[6] = 0.0;
    vector2[7] = 4.4;
    vector2[8] = 8.8;
    vector2[9] = 9.9;

    Cla1ForceTask1andWait();

    Cla1ForceTask2andWait();

    Cla1ForceTask3andWait();

    Uint16 i;
    float vector1_gold[] = {-11.3, 1.0, 2.5, 6.2, 10.8};
    float vector2_gold[] = {9.9, 8.8, 4.4, 3.3, 2.2, 1.0, 0.0,-8.8,-9.9,-10.1};
    int32 vector3_gold[] = {9,8,4,3,2,1,0,-8,-9};

    for(i=0; i < LENGTH1; i++)
    {
        if(vector1_sorted[i] != vector1_gold[i])
        {
            fail++;
        }
        else
        {
            pass++;
        }
    }
    for(i=0; i < LENGTH2; i++)
    {
        if(vector2_sorted[i] != vector2_gold[i])
        {
            fail++;
        }
        else
        {
            pass++;
        }
    }

    //
    // Map the data memory back to the CPU so we can check the
    // results of task 3
    //
    EALLOW;
    MemCfgRegs.LSxMSEL.bit.MSEL_LS0 = 0;
    MemCfgRegs.LSxMSEL.bit.MSEL_LS1 = 0;
    EDIS;
   __asm("   NOP");
   __asm("   NOP");
   __asm("   NOP");
   __asm("   NOP");

    for(i=0; i < LENGTH3; i++)
    {
        if(vector3[i] != vector3_gold[i])
        {
            fail++;
        }
        else
        {
            pass++;
        }
    }
#if 0
    Cla1ForceTask4andWait();

    Cla1ForceTask5andWait();

    Cla1ForceTask6andWait();

    Cla1ForceTask7andWait();

    Cla1ForceTask8andWait();
#endif
}

//
// CLA_configClaMemory - Configure CLA memory
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
// CLA_initCpu1Cla1 - Initialize task vectors and end of task interrupts
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
    PieVectTable.CLA1_1_INT  = &cla1Isr1;
    PieVectTable.CLA1_2_INT  = &cla1Isr2;
    PieVectTable.CLA1_3_INT  = &cla1Isr3;
    PieVectTable.CLA1_4_INT  = &cla1Isr4;
    PieVectTable.CLA1_5_INT  = &cla1Isr5;
    PieVectTable.CLA1_6_INT  = &cla1Isr6;
    PieVectTable.CLA1_7_INT  = &cla1Isr7;
    PieVectTable.CLA1_8_INT  = &cla1Isr8;

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
// cla1Isr1 - CLA1 ISR 2
//
__interrupt void cla1Isr2 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr1 - CLA1 ISR 3
//
__interrupt void cla1Isr3 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr1 - CLA1 ISR 4
//
__interrupt void cla1Isr4 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr1 - CLA1 ISR 5
//
__interrupt void cla1Isr5 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr1 - CLA1 ISR 6
//
__interrupt void cla1Isr6 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr1 - CLA1 ISR 7
//
__interrupt void cla1Isr7 ()
{
    asm(" ESTOP0");
}

//
// cla1Isr1 - CLA1 ISR 8
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
