//###########################################################################
//
// FILE:   cla_fir32_cpu01.c
//
// TITLE:  CLA 5 Tap FIR Filter Example for F2837xD.
//
//! \addtogroup cpu01_example_list
//! <h1>CLA 5 Tap Finite Impulse Response Filter (cla_fir32_cpu01)</h1>
//!
//! This example implements a 5 Tap FIR filter. The input vector, stored
//! in a lookup table, is filtered and then stored
//! in an output buffer for storage.
//!
//! \b Memory \b Allocation \n
//!  - CLA1 Data RAM 0 (RAMLS0)
//!    - fCoeffs - Filter Coefficients
//!    - fDelayLine - Delay line memory elements
//!  - CLA1 to CPU Message RAM
//!    - xResult - Result of the FIR operation
//!  - CPU to CLA1 Message RAM
//!    - xAdcInput - Simulated ADC input
//!
//! \b Watch \b Variables \n
//! - xResult - Result of the FIR operation
//! - xAdcInput - Simulated ADC input
//! - pass
//! - fail
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
#include "cla_fir32_shared.h"

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
    #pragma DATA_SECTION("CpuToCla1MsgRAM");
    long xAdcInput;
    #pragma DATA_SECTION("Cla1ToCpuMsgRAM");
    long xResult;
    #pragma DATA_SECTION("CLADataLS0");
    float fCoeffs[FILTER_LEN] = {0.0625, 0.25, 0.375, 0.25, 0.0625};
    #pragma DATA_SECTION("CLADataLS0");
    float fDelayLine[FILTER_LEN] = {0,0,0,0,0};
#else
    #pragma DATA_SECTION(xAdcInput,"CpuToCla1MsgRAM");
    long xAdcInput;
    #pragma DATA_SECTION(xResult,"Cla1ToCpuMsgRAM");
    long xResult;
    #pragma DATA_SECTION(fCoeffs,"CLADataLS0");
    float fCoeffs[FILTER_LEN] = {0.0625, 0.25, 0.375, 0.25, 0.0625};
    #pragma DATA_SECTION(fDelayLine,"CLADataLS0");
    float fDelayLine[FILTER_LEN] = {0,0,0,0,0};
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
unsigned long adc_input[INPUT_LEN] = {
3036, 452, 2449, 973, 3824, 2852, 804, 2550,
430, 482, 3233, 2174, 768, 514, 1301, 4046,
524, 2624, 1506, 375, 1091, 533, 1296, 698,
2251, 1347, 844, 1660, 3268, 379, 891, 1056,
1988, 2678, 355, 430, 1997, 33, 1029, 1625,
3647, 3068, 3162, 460, 3149, 1733, 3657, 304,
3272, 2389, 843, 3213, 1622, 2685, 2880, 2802,
3008, 3031, 1590, 1194, 1118, 2961, 2276, 1648,
211, 962, 2260, 2472, 153, 2176, 756, 4025,
299, 3010, 938, 3950, 2758, 446, 869, 1647,
363, 3975, 2629, 1772, 1760, 2588, 317, 2542,
3270, 3551, 1984, 2846, 1850, 519, 3743, 633,
3862, 354, 622, 3105, 2498, 550, 2894, 1562,
2800, 1501, 3203, 1772, 244, 404, 2285, 660,
541, 1512, 412, 2685, 1294, 582, 1284, 3105,
2960, 2806, 1205, 0, 0, 0, 0 ,0
};
unsigned long fir_output[OUTPUT_LEN];

unsigned long fir_expected[OUTPUT_LEN]={
189, 787, 1404, 1601, 1703, 2139, 2593, 2446,
1917, 1473, 1171, 1391, 1951, 1877, 1243, 1098,
1708, 2169, 2039, 1767, 1415, 987, 811, 863,
1002, 1266, 1489, 1426, 1413, 1758, 1843, 1351,
1021, 1306, 1756, 1682, 1159, 918, 951, 897,
1153, 1972, 2802, 2983, 2492, 2050, 2155, 2399,
2281, 2103, 2181, 2144, 2022, 2138, 2315, 2508,
2741, 2880, 2865, 2535, 1910, 1499, 1699, 2136,
2088, 1484, 1015, 1236, 1728, 1726, 1407, 1449,
1862, 2097, 1976, 1936, 2282, 2621, 2246, 1423,
1044, 1201, 1760, 2452, 2555, 2171, 1934, 1759,
1715, 2233, 2893, 2981, 2663, 2280, 1892, 1810,
2048, 2193, 1967, 1487, 1495, 2000, 2070, 1845,
1944, 2137, 2196, 2272, 2209, 1645, 978, 935,
1171, 1073, 914, 1014, 1318, 1564, 1408, 1224,
1669, 2437, 2743, 2287, 1338, 476, 75, 0,
0, 0, 0, 0, 0
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
    int i;

    for(i=0; i < OUTPUT_LEN; i++)
    {
        if(i < INPUT_LEN)
        {
            xAdcInput = adc_input[i];
            Cla1ForceTask1andWait();
            fir_output[i] = xResult;
        }
        else
        {
            fir_output[i] = 0;
        }

        if(fir_output[i] == fir_expected[i])
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
