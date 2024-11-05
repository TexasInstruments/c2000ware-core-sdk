//###########################################################################
//
// FILE:   cla_ex2_atan.c
//
// TITLE:  CLA ArcTan Example
//
//! \addtogroup cpu01_example_list
//! <h1>CLA \f$arctangent(x)\f$ using a lookup table (cla_atan_cpu01)</h1>
//!
//! In this example, Task 1 of the CLA will calculate the arctangent of
//! an input argument using a lookup table.
//!
//! \b Memory \b Allocation \n
//!  - CLA1 Math Tables (RAMLS0)
//!    - CLAatan2Table - Lookup table
//!  - CLA1 to CPU Message RAM
//!    - fResult - Result of the lookup algorithm
//!  - CPU to CLA1 Message RAM
//!    - fNum - Numerator of sample input
//!    - fDen - Denominator of sample input
//!
//! \b Watch \b Variables \n
//! - fVal - Argument to task 1
//! - fResult - Result of \f$arctan(fVal)\f$
//!
//
//###########################################################################
//
//
// 
// C2000Ware v5.04.00.00
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

//
// Included Files
//
#include "f28x_project.h"
#include "cla_ex2_atan_shared.h"

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
float fVal;
#pragma DATA_SECTION("CpuToCla1MsgRAM")
float PIBYTWO;
#pragma DATA_SECTION("Cla1ToCpuMsgRAM");
float fResult;

#else

#pragma DATA_SECTION(fVal,"CpuToCla1MsgRAM");
float fVal;
#pragma DATA_SECTION(PIBYTWO,"CpuToCla1MsgRAM")
float PIBYTWO = 1.570796327;
#pragma DATA_SECTION(fResult,"Cla1ToCpuMsgRAM");
float fResult;
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
#pragma DATA_SECTION("CLADataLS1")
#else
#pragma DATA_SECTION(CLAatan2Table,"CLADataLS1")
#endif //__cplusplus
float CLAatan2Table[]={
    0.000000000000, 1.000040679675, -0.007811069750,
    -0.000003807022, 1.000528067772, -0.023410345493,
    -0.000018968310, 1.001498568106, -0.038941197075,
    -0.000052831927, 1.002943680965, -0.054358563160,
    -0.000112417996, 1.004850785788, -0.069618206649,
    -0.000204295885, 1.007203293243, -0.084677028723,
    -0.000334469493, 1.009980843501, -0.099493367628,
    -0.000508272606, 1.013159547023, -0.114027278430,
    -0.000730276035, 1.016712263449, -0.128240790343,
    -0.001004207980, 1.020608913557, -0.142098138715,
    -0.001332888717, 1.024816818801, -0.155565969259,
    -0.001718180431, 1.029301062569, -0.168613512667,
    -0.002160952612, 1.034024867135, -0.181212728329,
    -0.002661063159, 1.038949980222, -0.193338416410,
    -0.003217354977, 1.044037065160, -0.204968298146,
    -0.003827667546, 1.049246088868, -0.216083064706,
    -0.004488862702, 1.054536702192, -0.226666395507,
    -0.005196863579, 1.059868607573, -0.236704947279,
    -0.005946705500, 1.065201909527, -0.246188315613,
    -0.006732597422, 1.070497443994, -0.255108971022,
    -0.007547992413, 1.075717083222, -0.263462171840,
    -0.008385665599, 1.080824013499, -0.271245856476,
    -0.009237797924, 1.085782983693, -0.278460517693,
    -0.010096064139, 1.090560523211, -0.285109061650,
    -0.010951723407, 1.095125128557, -0.291196654447,
    -0.011795711029, 1.099447418304, -0.296730558920,
    -0.012618729873, 1.103500256784, -0.301719964310,
    -0.013411340199, 1.107258847274, -0.306175811325,
    -0.014164046711, 1.110700795887, -0.310110614947,
    -0.014867381831, 1.113806147717, -0.313538287176,
    -0.015511984298, 1.116557397059, -0.316473961655,
    -0.016088672395, 1.118939473766, -0.318933821948,
    -0.016588511229, 1.120939707956, -0.320934934991,
    -0.017002873645, 1.122547775367, -0.322495091022,
    -0.017323494499, 1.123755625749, -0.323632651068,
    -0.017542518140, 1.124557396633, -0.324366402860,
    -0.017652539065, 1.124949314810, -0.324715425833,
    -0.017646635823, 1.124929587773, -0.324698965683,
    -0.017518398344, 1.124498287266, -0.324336318787,
    -0.017261948920, 1.123657226955, -0.323646726613,
    -0.016871957164, 1.122409836098, -0.322649280139,
    -0.016343649294, 1.120761030918, -0.321362834119,
    -0.015672812166, 1.118717085258, -0.319805931024,
    -0.014855792451, 1.116285501852, -0.317996734279,
    -0.013889491441, 1.113474885484, -0.315952970460,
    -0.012771355912, 1.110294819035, -0.313691879968,
    -0.011499365513, 1.106755743329, -0.311230175714,
    -0.010072017131, 1.102868841531, -0.308584009287,
    -0.008488306656, 1.098645928648, -0.305768944066,
    -0.006747708579, 1.094099346648, -0.302799934724,
    -0.004850153815, 1.089241865523, -0.299691312610,
    -0.002796006119, 1.084086590517, -0.296456776409,
    -0.000586037441, 1.078646875666, -0.293109387609,
    0.001778597452, 1.072936243727, -0.289661570229,
    0.004296386804, 1.066968312440, -0.286125114351,
    0.006965487894, 1.060756727064, -0.282511182960,
    0.009783753017, 1.054315099009, -0.278830321668,
    0.012748755207, 1.047656950440, -0.275092470943,
    0.015857813546, 1.040795664582, -0.271306980411,
    0.019108017893, 1.033744441476, -0.267482624928,
    0.022496252887, 1.026516258989, -0.263627622089,
    0.026019221162, 1.019123838651, -0.259749650860,
    0.029673465636, 1.011579616186, -0.255855871106,
    0.033455390838, 1.003895716322, -0.251952943763,
    0.037361283212, 0.996083931611, -0.248047051426
};

float atan_expected[BUFFER_SIZE]={
    1.5395565,  1.5385494,  1.5374753,  1.5363272,
    1.5350972,  1.5337762,  1.5323538,  1.5308176,
    1.5291537,  1.5273454,  1.5253731,  1.5232133,
    1.5208379,  1.5182133,  1.5152978,  1.5120405,
    1.5083776,  1.5042281,  1.4994888,  1.4940244,
    1.4876550,  1.4801364,  1.4711276,  1.4601392,
    1.4464413,  1.4288993,  1.4056476,  1.3734008,
    1.3258177,  1.2490457,  1.1071488,  0.7853982,
    0.0000000, -0.7853982, -1.1071488, -1.2490457,
    -1.3258177, -1.3734008, -1.4056476, -1.4288993,
    -1.4464413, -1.4601392, -1.4711276, -1.4801364,
    -1.4876550, -1.4940244, -1.4994888, -1.5042281,
    -1.5083776, -1.5120405, -1.5152978, -1.5182133,
    -1.5208379, -1.5232133, -1.5253731, -1.5273454,
    -1.5291537, -1.5308176, -1.5323538, -1.5337762,
    -1.5350972, -1.5363272, -1.5374753, -1.5385494
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
// This example function is found in the <device>_sysctrl.c file.
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
// This function is found in the <device>_piectrl.c file.
//
    InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the default Interrupt
// Service Routines (ISR).
// The default ISR routines are found in <device>_defaultisr.c.
// This function is found in <device>_pievect.c.
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

    for(;;)
    {
    }
}

//
// CLA_runTest - Execute CLA task tests for specified vectors
//
void CLA_runTest(void)
{
    int16_t i;
    float error;

    //
    // Initialize the CPUToCLA1MsgRam variables here
    //
    PIBYTWO = 1.570796327;

    for(i=0; i < BUFFER_SIZE; i++)
    {
        fVal = (float)((BUFFER_SIZE/2) - i);

        Cla1ForceTask1andWait();

        y[i] = fResult;
        error = fabsf(atan_expected[i]-y[i]);

        if(error < 0.1f)
        {
            pass++;
        }
        else
        {
            fail++;
        }
    }

    //
    // CLA tasks 2-8 are not used in this example
    //
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
    extern uint32_t Cla1ProgRunStart, Cla1ProgLoadStart, Cla1ProgLoadSize;
    EALLOW;

#ifdef _FLASH
    //
    // Copy over code from FLASH to RAM
    //
    memcpy((uint32_t *)&Cla1ProgRunStart, (uint32_t *)&Cla1ProgLoadStart,
           (uint32_t)&Cla1ProgLoadSize);
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
    // CLA Program will reside in RAMLS0 and data in RAMLS1, RAMLS2
    //
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS0 = 1U;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS1 = 0U;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS2 = 0U;

    //
    // Select CLA as the master of RAMLS0, RAMSL1, RAMLS2
    //
    MemCfgRegs.LSxMSEL.bit.MSEL_LS0 = 1U;
    MemCfgRegs.LSxMSEL.bit.MSEL_LS1 = 1U;
    MemCfgRegs.LSxMSEL.bit.MSEL_LS2 = 1U;

    EDIS;
}

//
// CLA_initCpu1Cla1 - Initialize CLA1 task vectors and end of task interrupts
//
void CLA_initCpu1Cla1(void)
{
    //
    // Suppressing #770-D conversion from pointer to smaller integer
    // The CLA address range is 16 bits so the addresses passed to the MVECT
    // registers will be in the lower 64KW address space. Turn the warning
    // back on after the MVECTs are assigned addresses
    //
#pragma diag_suppress=770
    EALLOW;
    Cla1Regs.MVECT1 = (uint16_t)(&Cla1Task1);
    Cla1Regs.MVECT2 = (uint16_t)(&Cla1Task2);
    Cla1Regs.MVECT3 = (uint16_t)(&Cla1Task3);
    Cla1Regs.MVECT4 = (uint16_t)(&Cla1Task4);
    Cla1Regs.MVECT5 = (uint16_t)(&Cla1Task5);
    Cla1Regs.MVECT6 = (uint16_t)(&Cla1Task6);
    Cla1Regs.MVECT7 = (uint16_t)(&Cla1Task7);
    Cla1Regs.MVECT8 = (uint16_t)(&Cla1Task8);
#pragma diag_warning=770

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
