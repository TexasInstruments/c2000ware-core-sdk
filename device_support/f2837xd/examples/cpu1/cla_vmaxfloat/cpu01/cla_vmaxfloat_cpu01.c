//###########################################################################
//
// FILE:   cla_vmaxfloat_cpu01.c
//
// TITLE:  Vector Maximum Example for F2837xD.
//
//! \addtogroup cpu01_example_list
//! <h1>CLA Vector Maximum (cla_vmaxfloat_cpu01)</h1>
//!
//! Task 1 calculates the vector max moving backward through the array. \n
//! Task 2 calculates the vector max moving forward through the array. \n
//! Task 3 calculates the vector max using the ternary operator. \n
//! Task 4 calculates the vector max using min/max intrinsics. \n
//!
//! \b Memory \b Allocation \n
//!  - CLA1 to CPU Message RAM
//!    - max1 - Maximum value in vector 1
//!    - index1 - Index of the maximum value in vector 1
//!    - max2 - Maximum value in vector 2
//!    - index2 - Index of the maximum value in vector 2
//!    - max3 - Maximum value in vector 3
//!    - index3 - Index of the maximum value in vector 3
//!    - max4 - Maximum value in vector 4
//!    - min4 - Minimum value in vector 4
//!  - CPU to CLA1 Message RAM
//!    - vector1 - Input vector to task 1
//!    - vector2 - Input vector to task 2
//!    - vector3 - Input vector to task 3
//!    - vector4 - Input vector to task 4
//!    - length1 - Length of vector 1
//!    - length2 - Length of vector 2
//!
//! \b Watch \b Variables \n
//! - vector1 - Input vector to task 1
//! - vector2 - Input vector to task 2
//! - vector3 - Input vector to task 3
//! - vector4 - Input vector to task 4
//! - max1 - Maximum value in vector 1
//! - index1 - Index of the maximum value in vector 1
//! - max2 - Maximum value in vector 2
//! - index2 - Index of the maximum value in vector 2
//! - max3 - Maximum value in vector 3
//! - index3 - Index of the maximum value in vector 3
//! - max4 - Maximum value in vector 4
//! - min4 - Minimum value in vector 4
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
#include "cla_vmaxfloat_shared.h"

//
// Defines
//
#define WAITSTEP     asm(" RPT #255 || NOP")

//
// Globals
//

//
//Task 1 (C) Variables
//
#ifdef __cplusplus
    //
    // CLA Input Data
    //
    #pragma DATA_SECTION("CpuToCla1MsgRAM");
    #pragma DATA_SECTION("CpuToCla1MsgRAM");
    float  vector1[] = {1.0,-11.3,6.2,10.8,2.5,7.3,13.2,3.1};
    int32  length1 = 8; // Length 3 and 4 are #defined in vmaxfloat_shared.h

    //
    // CLA Output Data
    //
    #pragma DATA_SECTION("Cla1ToCpuMsgRAM");
    #pragma DATA_SECTION("Cla1ToCpuMsgRAM");
    float32 max1;
    int32   index1;
#else
    //
    // CLA Input Data
    //
    #pragma DATA_SECTION(vector1,"CpuToCla1MsgRAM");
    #pragma DATA_SECTION(length1,"CpuToCla1MsgRAM");
    float  vector1[] = {1.0,-11.3,6.2,10.8,2.5,7.3,13.2,3.1};
    int32  length1 = 8; // Length 3 and 4 are #defined in vmaxfloat_shared.h

    //
    // CLA Output Data
    //
    #pragma DATA_SECTION(max1,"Cla1ToCpuMsgRAM");
    #pragma DATA_SECTION(index1,"Cla1ToCpuMsgRAM");
    float32 max1;
    int32   index1;
#endif

//
//Task 2 (C) Variables
//
#ifdef __cplusplus
    //
    // CLA Input Data
    //
    #pragma DATA_SECTION("CpuToCla1MsgRAM");
    #pragma DATA_SECTION("CpuToCla1MsgRAM");
    float  vector2[] = {-3.6,-11.3,-16.2,-10.8,-2.5,-12.5,-33.3};
    int32  length2 = 7;

    //
    // CLA Output Data
    //
    #pragma DATA_SECTION("Cla1ToCpuMsgRAM");
    #pragma DATA_SECTION("Cla1ToCpuMsgRAM");
    float32 max2;
    int32   index2;
#else
    //
    // CLA Input Data
    //
    #pragma DATA_SECTION(vector2,"CpuToCla1MsgRAM");
    #pragma DATA_SECTION(length2,"CpuToCla1MsgRAM");
    float  vector2[] = {-3.6,-11.3,-16.2,-10.8,-2.5,-12.5,-33.3};
    int32  length2 = 7;

    //
    // CLA Output Data
    //
    #pragma DATA_SECTION(max2,"Cla1ToCpuMsgRAM");
    #pragma DATA_SECTION(index2,"Cla1ToCpuMsgRAM");
    float32 max2;
    int32   index2;
#endif

//
//Task 3 (C) Variables
//
#ifdef __cplusplus
    //
    // CLA Input Data
    //
    #pragma DATA_SECTION("CpuToCla1MsgRAM");
    float  vector3[] = {12.2,2.3,9.6,9.2,6.2,10.8,2.5,-13.3};

    //
    // CLA Output Data
    //
    #pragma DATA_SECTION("Cla1ToCpuMsgRAM");
    #pragma DATA_SECTION("Cla1ToCpuMsgRAM");
    int32   index3;
    float32 max3;
#else
    //
    // CLA Input Data
    //
    #pragma DATA_SECTION(vector3,"CpuToCla1MsgRAM");
    float  vector3[] = {12.2,2.3,9.6,9.2,6.2,10.8,2.5,-13.3};

    //
    // CLA Output Data
    //
    #pragma DATA_SECTION(max3,"Cla1ToCpuMsgRAM");
    #pragma DATA_SECTION(index3,"Cla1ToCpuMsgRAM");
    int32   index3;
    float32 max3;
#endif

//
//Task 4 (C) Variables
//
#ifdef __cplusplus
    //
    // CLA Input Data
    //
    #pragma DATA_SECTION("CpuToCla1MsgRAM");
    float  vector4[] = {1.1,9.9,7.7,-5.5,-2.2,4.4,-8.8,0.0,6.6,-4.4};

    //
    // CLA Output Data
    //
    #pragma DATA_SECTION("Cla1ToCpuMsgRAM");
    #pragma DATA_SECTION("Cla1ToCpuMsgRAM");
    float32 max4, min4;
#else
    //
    // CLA Input Data
    //
    #pragma DATA_SECTION(vector4,"CpuToCla1MsgRAM");
    float  vector4[] = {1.1,9.9,7.7,-5.5,-2.2,4.4,-8.8,0.0,6.6,-4.4};

    //
    // CLA Output Data
    //
    #pragma DATA_SECTION(max4,"Cla1ToCpuMsgRAM");
    #pragma DATA_SECTION(min4,"Cla1ToCpuMsgRAM");
    float32 max4, min4;
#endif

//
//Task 5 (C) Variables
//

//
//Task 6 (C) Variables
//

//
//Task 7 (C) Variables
//

//Task 8 (C) Variables

//
//Common (C) Variables
//
#ifdef __cplusplus
    #pragma DATA_SECTION("Cla1ToCpuMsgRAM");
    int32   i;
#else
    #pragma DATA_SECTION(i,"Cla1ToCpuMsgRAM");
    int32   i;
#endif
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
// CLA_runTest - Execute task tests with specified vectors
//
void CLA_runTest(void)
{
    //
    //    float  vector1[] = {1.0,-11.3,6.2,10.8,2.5,7.3,13.2,3.1};
    //
    length1 = 8;
    vector1[0] = 1.0;
    vector1[1] = -11.3;
    vector1[2] = 6.2;
    vector1[3] = 10.8;
    vector1[4] = 2.5;
    vector1[5] = 7.3;
    vector1[6] = 13.2;
    vector1[7] = 3.1;

    //
    //    float  vector2[] = {-3.6,-11.3,-16.2,-10.8,-2.5,-12.5,-33.3};
    //
    length2 = 7;
    vector2[0] = -3.6;
    vector2[1] = -11.3;
    vector2[2] = -16.2;
    vector2[3] = -10.8;
    vector2[4] = -2.5;
    vector2[5] = -12.5;
    vector2[6] = -33.3;

    //
    //    float  vector3[] = {12.2,2.3,9.6,9.2,6.2,10.8,2.5,-13.3};
    //
    vector3[0] = 12.2;
    vector3[1] = 2.3;
    vector3[2] = 9.6;
    vector3[3] = 9.2;
    vector3[4] = 6.2;
    vector3[5] = 10.8;
    vector3[6] = 2.5;
    vector3[7] = -13.3;

    //
    //    float  vector4[] = {1.1,9.9,7.7,-5.5,-2.2,4.4,-8.8,0.0,6.6,-4.4};
    //
    vector4[0] = 1.1;
    vector4[1] = 9.9;
    vector4[2] = 7.7;
    vector4[3] = -5.5;
    vector4[4] = -2.2;
    vector4[5] = 4.4;
    vector4[6] = -8.8;
    vector4[7] = 0.0;
    vector4[8] = 6.6;
    vector4[9] = -4.4;

    Cla1ForceTask1andWait();

    Cla1ForceTask2andWait();

    Cla1ForceTask3andWait();

    Cla1ForceTask4andWait();

    if(index1 != 6 || max1 != 13.2)
    {
        fail++;
    }
    else
    {
        pass++;
    }
    if(index2 != 4 || max2 != -2.5)
    {
        fail++;
    }
    else
    {
        pass++;
    }
    if(index3 != 0 || max3 != 12.2)
    {
        fail++;
    }
    else
    {
        pass++;
    }
    if(max4 != 9.9 || min4 != -8.8)
    {
        fail++;
    }
    else
    {
        pass++;
    }

#if 0
    Cla1ForceTask5andWait();

    Cla1ForceTask6andWait();

    Cla1ForceTask7andWait();

    Cla1ForceTask8andWait();
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
// CLA_initCpu1Cla1 -  Initialize CLA task vectors and end of task interrupts
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
