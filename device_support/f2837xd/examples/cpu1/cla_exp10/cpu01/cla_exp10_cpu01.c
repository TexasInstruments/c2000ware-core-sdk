//###########################################################################
//
// FILE:   cla_exp10_cpu01.c
//
// TITLE:  CLA 10^X Example for F2837xD.
//
//! \addtogroup cpu01_example_list
//! <h1>CLA \f$10^{X}\f$ using a lookup table (cla_exp2_cpu01)</h1>
//!
//! In this example, Task 1 of the CLA will calculate
//! the Xth power of 10 using a table lookup method.
//!
//! \b Memory \b Allocation \n
//!  - CLA1 Math Tables (RAMLS0)
//!    - CLAexpTable - Lookup table
//!  - CLA1 to CPU Message RAM
//!    - ExpRes - Result of the exponentiation operation
//!  - CPU to CLA1 Message RAM
//!    - Val - The exponent
//!
//! \b Watch \b Variables \n
//! - Val            - Input
//! - ExpRes         - Result of \f$10^{Val}\f$
//! - y              - Array that golds the results
//! - exp10_expected - Array that holds the expected results
//! - pass           - pass counter
//! - fail           - fail counter
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
#include "cla_exp10_shared.h"

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
#pragma DATA_SECTION("CpuToCla1MsgRAM");
float Val;
#pragma DATA_SECTION("Cla1ToCpuMsgRAM");
float ExpRes;
#else
#pragma DATA_SECTION(Val,"CpuToCla1MsgRAM");
float Val;
#pragma DATA_SECTION(ExpRes,"Cla1ToCpuMsgRAM");
float ExpRes;
#endif //__cplusplus
float y[BUFFER_SIZE];

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
#pragma DATA_SECTION(CLAexpTable,"CLADataLS0")
#endif //__cplusplus
float CLAexpTable[] = {
    1.0, 2.7182818285e+0, 7.3890560989e+0, 2.0085536923e+1,
    5.4598150033e+1, 1.484131591e+2, 4.0342879349e+2, 1.0966331584e+3,
    2.980957987e+3, 8.1030839276e+3, 2.2026465795e+4, 5.9874141715e+4,
    1.6275479142e+5, 4.4241339201e+5, 1.2026042842e+6, 3.2690173725e+6,
    8.8861105205e+6, 2.4154952754e+7, 6.5659969137e+7, 1.7848230096e+8,
    4.8516519541e+8, 1.3188157345e+9, 3.5849128461e+9, 9.7448034462e+9,
    2.648912213e+10, 7.2004899337e+10, 1.9572960943e+11, 5.320482406e+11,
    1.4462570643e+12, 3.9313342971e+12, 1.0686474582e+13, 2.9048849665e+13,
    7.8962960183e+13, 2.1464357979e+14, 5.8346174253e+14, 1.5860134523e+15,
    4.3112315471e+15, 1.1719142373e+16, 3.1855931757e+16, 8.6593400424e+16,
    2.3538526684e+17, 6.3984349353e+17, 1.7392749415e+18, 4.7278394682e+18,
    1.2851600114e+19, 3.4934271057e+19, 9.4961194206e+19, 2.5813128862e+20,
    7.0167359121e+20, 1.9073465725e+21, 5.1847055286e+21, 1.4093490824e+22,
    3.8310080007e+22, 1.0413759433e+23, 2.8307533033e+23, 7.6947852651e+23,
    2.091659496e+24, 5.6857199993e+24, 1.5455389356e+25, 4.2012104038e+25,
    1.1420073898e+26, 3.1042979357e+26, 8.4383566687e+26, 2.2937831595e+27,
    6.2351490808e+27, 1.6948892444e+28, 4.6071866343e+28, 1.2523631708e+29,
    3.4042760499e+29, 9.2537817256e+29, 2.5154386709e+30, 6.8376712298e+30,
    1.8586717453e+31, 5.0523936303e+31, 1.3733829795e+32, 3.7332419968e+32,
    1.0148003881e+33, 2.7585134545e+33, 7.498416997e+33, 2.0382810665e+34,
    5.5406223844e+34, 1.5060973146e+35, 4.0939969621e+35, 1.1128637548e+36,
    3.0250773222e+36, 8.2230127146e+36, 2.2352466037e+37, 6.0760302251e+37,
    1.651636255e+38
};
#ifdef __cplusplus
#pragma DATA_SECTION("CLADataLS0");
float CLALOG10_E = 2.30258509;
//
//Coefficients in the Taylor series expansion of exp(A/B)
//
#pragma DATA_SECTION("CLADataLS0")
float CLAINV1 =   1.0 ;
#pragma DATA_SECTION("CLADataLS0")
float CLAINV2 =   0.5 ; //1/2
#pragma DATA_SECTION("CLADataLS0")
float CLAINV3 =   0.333333333333333333; //1/3
#pragma DATA_SECTION("CLADataLS0")
float CLAINV4 =   0.25; //1/4
#pragma DATA_SECTION("CLADataLS0")
float CLAINV5 =   0.20; //1/5
#pragma DATA_SECTION("CLADataLS0")
float CLAINV6 =   0.166666666666666666; //1/6
#pragma DATA_SECTION("CLADataLS0")
float CLAINV7 =   0.142857142857142857; //1/7
#else
#pragma DATA_SECTION(CLALOG10_E,"CLADataLS0");
float CLALOG10_E = 2.30258509;
//
//Coefficients in the Taylor series expansion of exp(A/B)
//
#pragma DATA_SECTION(CLAINV1,"CLADataLS0")
float CLAINV1 =   1.0 ;
#pragma DATA_SECTION(CLAINV2,"CLADataLS0")
float CLAINV2 =   0.5 ; //1/2
#pragma DATA_SECTION(CLAINV3,"CLADataLS0")
float CLAINV3 =   0.333333333333333333; //1/3
#pragma DATA_SECTION(CLAINV4,"CLADataLS0")
float CLAINV4 =   0.25; //1/4
#pragma DATA_SECTION(CLAINV5,"CLADataLS0")
float CLAINV5 =   0.20; //1/5
#pragma DATA_SECTION(CLAINV6,"CLADataLS0")
float CLAINV6 =   0.166666666666666666; //1/6
#pragma DATA_SECTION(CLAINV7,"CLADataLS0")
float CLAINV7 =   0.142857142857142857; //1/7
#endif // __cplusplus

//
//Golden Test Values
//
float exp10_expected[BUFFER_SIZE]={
10, 9.646616, 9.305720, 8.976871, 8.659643,
8.353625, 8.058422, 7.773650, 7.498942, 7.233942,
6.978306, 6.731704, 6.493816, 6.264335, 6.042964,
5.829415, 5.623413, 5.424691, 5.232991, 5.048066,
4.869675, 4.697589, 4.531584, 4.371445, 4.216965,
4.067945, 3.924190, 3.785515, 3.651741, 3.522695,
3.398208, 3.278121, 3.162278, 3.050528, 2.942727,
2.838736, 2.738420, 2.641648, 2.548297, 2.458244,
2.371374, 2.287573, 2.206734, 2.128752, 2.053525,
1.980957, 1.910953, 1.843423, 1.778279, 1.715438,
1.654817, 1.596339, 1.539927, 1.485508, 1.433013,
1.382372, 1.333521, 1.286397, 1.240938, 1.197085,
1.154782, 1.113974, 1.074608, 1.036633 };

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
    int i, error;

    for(i=0; i < BUFFER_SIZE; i++)
    {
        Val = (float)(BUFFER_SIZE - i)/(float)BUFFER_SIZE;

        Cla1ForceTask1andWait();

        y[i] = ExpRes;
        error = fabs(exp10_expected[i]-y[i]);

        if(error < 0.01)
        {
            pass++;
        }
        else
        {
            fail++;
        }
    }

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
