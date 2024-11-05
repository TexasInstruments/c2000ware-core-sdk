//###########################################################################
//
// FILE:   cla_ex1_asin.c
//
// TITLE:  CLA Arcsine Example
//
//! \addtogroup cpu01_example_list
//! <h1>CLA \f$arcsine(x)\f$ using a lookup table (cla_asin_cpu01)</h1>
//!
//! In this example, Task 1 of the CLA will calculate the arcsine of
//! an input argument in the range (-1.0 to 1.0) using a lookup table.
//!
//! \b Memory \b Allocation \n
//!  - CLA1 Math Tables (RAMLS0)
//!    - CLAasinTable - Lookup table
//!  - CLA1 to CPU Message RAM
//!    - fResult - Result of the lookup algorithm
//!  - CPU to CLA1 Message RAM
//!    - fVal - Sample input to the lookup algorithm
//!
//! \b Watch \b Variables \n
//!  - fVal - Argument to task 1
//!  - fResult - Result of \f$arcsin(fVal)\f$
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
#include "cla_ex1_asin_shared.h"

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
#pragma DATA_SECTION("Cla1ToCpuMsgRAM");
float fResult;
#else
#pragma DATA_SECTION(fVal,"CpuToCla1MsgRAM");
float fVal;
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
#pragma DATA_SECTION(CLAasinTable,"CLADataLS1")
#endif //__cplusplus
float CLAasinTable[]={
    0.0, 1.0, 0.0,
    0.000000636202, 0.999877862610, 0.007815361896,
    0.000005099694, 0.999510644409, 0.015647916155,
    0.000017268312, 0.998895919094, 0.023514960332,
    0.000041121765, 0.998029615282, 0.031434003631,
    0.000080794520, 0.996905974725, 0.039422875916,
    0.000140631089, 0.995517492804, 0.047499840611,
    0.000225244584, 0.993854840311, 0.055683712914,
    0.000339579512, 0.991906765146, 0.063993984848,
    0.000488979852, 0.989659972212, 0.072450958820,
    0.000679263611, 0.987098979366, 0.081075891529,
    0.000916805182, 0.984205946802, 0.089891150305,
    0.001208627040, 0.980960476685, 0.098920384204,
    0.001562502549, 0.977339379243, 0.108188712551,
    0.001987071928, 0.973316400729, 0.117722933997,
    0.002491973784, 0.968861907789, 0.127551759665,
    0.003087995053, 0.963942521723, 0.137706074532,
    0.003787242692, 0.958520694794, 0.148219231941,
    0.004603341138, 0.952554219267, 0.159127386977,
    0.005551660294, 0.945995657913, 0.170469875522,
    0.006649579796, 0.938791682505, 0.182289647088,
    0.007916796475, 0.930882303984, 0.194633761132,
    0.009375683410, 0.922199974574, 0.207553958472,
    0.011051710808, 0.912668537890, 0.221107321885,
    0.012973941175, 0.902201997769, 0.235357042896,
    0.015175614174, 0.890703070035, 0.250373315541,
    0.017694840102, 0.878061473098, 0.266234382514,
    0.020575425537, 0.864151902887, 0.283027765009,
    0.023867860513, 0.848831624374, 0.300851714968,
    0.027630504055, 0.831937595031, 0.319816937941,
    0.031931014547, 0.813283013821, 0.340048646894,
    0.036848083955, 0.792653161200, 0.361689022958,
    0.042473551274, 0.769800358920, 0.384900179460,
    0.048914992206, 0.744437830278, 0.409867752228,
    0.056298910750, 0.716232177740, 0.436805274317,
    0.064774696786, 0.684794109766, 0.465959540059,
    0.074519565699, 0.649666934178, 0.497617226179,
    0.085744766889, 0.610312179660, 0.532113122767,
    0.098703445606, 0.566091493186, 0.569840443472,
    0.113700678529, 0.516243664372, 0.611263845480,
    0.131106395009, 0.459855210927, 0.656936015611,
    0.151372169232, 0.395822366759, 0.707518998893,
    0.175053263659, 0.322801460177, 0.763811905770,
    0.202837883870, 0.239143420888, 0.826787304376,
    0.235586468765, 0.142806299514, 0.897639596948,
    0.274385149825, 0.031236880585, 0.977850174820,
    0.320619535938, -0.098791845166, 1.069276441800,
    0.376078169620, -0.251407364538, 1.174275392129,
    0.443100143614, -0.431959397725, 1.295878193174,
    0.524789871827, -0.647485610469, 1.438041695773,
    0.625336471263, -0.907400624736, 1.606018804842,
    0.750500589935, -1.224540947101, 1.806917563896,
    0.908377657341, -1.616794995066, 2.050569262035,
    1.110633894185, -2.109729648039, 2.350920816737,
    1.374584721437, -2.740985157716, 2.728353889708,
    1.726848242753, -3.567962877198, 3.213722960014,
    2.210117561056, -4.682006534082, 3.855770086891,
    2.896554011854, -6.236312386687, 4.735651038017,
    3.916505715382, -8.505488022524, 5.997790945975,
    5.526855868703, -12.026617159136, 7.922628470498,
    8.298197116322, -17.983705080358, 11.123941286820,
    13.741706072449, -29.488929624542, 17.203344479111,
    27.202707817485, -57.466598393615, 31.741016484669,
    83.158101335898, -171.803399517566, 90.149831709374
};

float asin_expected[BUFFER_SIZE]={
    1.570796, 1.393789, 1.320141, 1.263401, 1.215375,
    1.172892, 1.134327, 1.098718, 1.065436, 1.034046,
    1.004232, 0.9757544, 0.9484279, 0.9221048, 0.8966658,
    0.8720123, 0.8480621, 0.8247454, 0.8020028, 0.7797828,
    0.7580408, 0.7367374, 0.7158381, 0.6953120, 0.6751316,
    0.6552721, 0.6357113, 0.6164289, 0.5974064, 0.5786270,
    0.5600753, 0.5417370, 0.5235988, 0.5056486, 0.4878751,
    0.4702678, 0.4528166, 0.4355124, 0.4183464, 0.4013104,
    0.3843968, 0.3675981, 0.3509074, 0.3343180, 0.3178237,
    0.3014185, 0.2850964, 0.2688521, 0.2526802, 0.2365756,
    0.2205333, 0.2045484, 0.1886164, 0.1727327, 0.1568929,
    0.1410927, 0.1253278, 0.1095943, 0.09388787, 0.07820469,
    0.06254076, 0.04689218, 0.03125509, 0.01562564
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

    for(i=0; i < BUFFER_SIZE; i++)
    {
        fVal= (float)(BUFFER_SIZE - i)/(float)BUFFER_SIZE;
        Cla1ForceTask1andWait();

        y[i] = fResult;
        error = fabsf(asin_expected[i]-y[i]);

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
