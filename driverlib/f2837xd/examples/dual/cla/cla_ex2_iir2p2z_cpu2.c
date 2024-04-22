//###########################################################################
//
// FILE:   cla_ex2_iir2p2z_cpu2.c
//
// TITLE:  CLA 2-pole 2-zero IIR Filter Example for F2837xD.
//
// Dual Core iir2p2z example. This example demonstrates how to run CLA tasks
// on cpu2.cla1
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "inc/hw_ipc.h"
#include "cla_ex2_iir2p2z_shared.h"

//
// Defines
//
#define NUM_SAMPLES    128
#define WAITSTEP       asm(" RPT #255 || NOP")

//
// Globals
//
//Task 1 (C) Variables
//
#ifdef __cplusplus
    #pragma DATA_SECTION("CLADataLS0")
    float S1_B[]={0.02008, 0.04017, 0.02008};
    #pragma DATA_SECTION("CLADataLS0")
    float S1_A[]={-1.0, 1.56102, -0.64135};
    #pragma DATA_SECTION("CLADataLS0")
    float S2_B[]={0, 0, 0};
    #pragma DATA_SECTION("CLADataLS0")
    float S2_A[]={0, 0, 0};
    #pragma DATA_SECTION("CLADataLS0")
    float S3_B[]={0, 0, 0};
    #pragma DATA_SECTION("CLADataLS0")
    float S3_A[]={0, 0, 0};
    #pragma DATA_SECTION("CpuToCla1MsgRAM")
    float xn;
    #pragma DATA_SECTION("Cla1ToCpuMsgRAM")
    float yn;
#else
    #pragma DATA_SECTION(S1_B,"CLADataLS0")
    float S1_B[]={0.02008, 0.04017, 0.02008};
    #pragma DATA_SECTION(S1_A,"CLADataLS0")
    float S1_A[]={-1.0, 1.56102, -0.64135};
    #pragma DATA_SECTION(S2_B,"CLADataLS0")
    float S2_B[]={0, 0, 0};
    #pragma DATA_SECTION(S2_A,"CLADataLS0")
    float S2_A[]={0, 0, 0};
    #pragma DATA_SECTION(S3_B,"CLADataLS0")
    float S3_B[]={0, 0, 0};
    #pragma DATA_SECTION(S3_A,"CLADataLS0")
    float S3_A[]={0, 0, 0};
    #pragma DATA_SECTION(xn,"CpuToCla1MsgRAM")
    float xn;
    #pragma DATA_SECTION(yn,"Cla1ToCpuMsgRAM")
    float yn;
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
float fBiquadOutput[NUM_SAMPLES];
float fAdcInput[NUM_SAMPLES] = {
    0, 0.4359, -0.4129, 0.2482,
    0.4182, -0.3455, 0.4780, 0.3674,
    -0.2347, 0.6724, 0.2939, -0.0858,
    0.8178, 0.2100, 0.0914, 0.9045,
    0.1283, 0.2836, 0.9279, 0.0604,
    0.4755, 0.8888, 0.0156, 0.6506,
    0.7929, 0, 0.7929, 0.6506,
    0.0156, 0.8888, 0.4755, 0.0604,
    0.9279, 0.2836, 0.1283, 0.9045,
    0.0914, 0.2100, 0.8178, -0.0858,
    0.2939, 0.6724, -0.2347, 0.3674,
    0.4780, -0.3455, 0.4182, 0.2482,
    -0.4129, 0.4359, 0.0000, -0.4359,
    0.4129, -0.2482, -0.4182, 0.3455,
    -0.4780, -0.3674, 0.2347, -0.6724,
    -0.2939, 0.0858, -0.8178, -0.2100,
    -0.0914, -0.9045, -0.1283, -0.2836,
    -0.9279, -0.0604, -0.4755, -0.8888,
    -0.0156, -0.6506, -0.7929, 0,
    -0.7929, -0.6506, -0.0156, -0.8888,
    -0.4755, -0.0604, -0.9279, -0.2836,
    -0.1283, -0.9045, -0.0914, -0.2100,
    -0.8178, 0.0858, -0.2939, -0.6724,
    0.2347, -0.3674, -0.4780, 0.3455,
    -0.4182, -0.2482, 0.4129, -0.4359,
    -0.0000, 0.4359, -0.4129, 0.2482,
    0.4182, -0.3455, 0.4780, 0.3674,
    -0.2347, 0.6724, 0.2939, -0.0858,
    0.8178, 0.2100, 0.0914, 0.9045,
    0.1283, 0.2836, 0.9279, 0.0604,
    0.4755, 0.8888, 0.0156, 0.6506,
    0.7929, 0, 0.7929, 0.6506
    };

float iir_expected[NUM_SAMPLES]={
    0, 0.008754415, 0.02288298, 0.02726187,
    0.03795755, 0.05661327, 0.06815149, 0.08971455,
    0.1159805, 0.1349670, 0.1645004, 0.1938129,
    0.2159233, 0.2481003, 0.2754995, 0.2969926,
    0.3276609, 0.3500223, 0.3688507, 0.3954768,
    0.4113952, 0.4267188, 0.4478308, 0.4569381,
    0.4684406, 0.4831003, 0.4855416, 0.4930161,
    0.5005732, 0.4967500, 0.4999563, 0.5000126,
    0.4904927, 0.4891656, 0.4816235, 0.4671103,
    0.4610198, 0.4461307, 0.4274355, 0.4164503,
    0.3948304, 0.3728325, 0.3569719, 0.3295808,
    0.3051807, 0.2846532, 0.2527421, 0.2268174,
    0.2020469, 0.1670849, 0.1404567, 0.1120952,
    0.07568341, 0.04909494, 0.01802110, -0.01820113,
    -0.04409146, -0.07679208, -0.1112392, -0.1358536,
    -0.1689253, -0.2001516, -0.2229802, -0.2550509,
    -0.2818236, -0.3024068, -0.3320566, -0.3534117,
    -0.3713224, -0.3971615, -0.4124396, -0.4272688,
    -0.4480195, -0.4568799, -0.4682287, -0.4828069,
    -0.4852195, -0.4927015, -0.5002885, -0.4965075,
    -0.4997604, -0.4998623, -0.4903836, -0.4890918,
    -0.4815782, -0.4670869, -0.4610124, -0.4461341,
    -0.4274456, -0.4164638, -0.3948451, -0.3728467,
    -0.3569847, -0.3295917, -0.3051894, -0.2846599,
    -0.2527469, -0.2268206, -0.2020488, -0.1670859,
    -0.1404569, -0.1120951, -0.07568294, -0.04909432,
    -0.01802043, 0.01820178, 0.04409203, 0.07679256,
    0.1112396, 0.1358539, 0.1689255, 0.2001518,
    0.2229803, 0.2550510, 0.2818236, 0.3024068,
    0.3320566, 0.3534117, 0.3713224, 0.3971614,
    0.4124396, 0.4272687, 0.4480195, 0.4568799,
    0.4682287, 0.4828069, 0.4852195, 0.4927014
};

uint16_t pass=0;
uint16_t fail=0;

//
// Function Prototypes
//
void runTest(void);
void configClaMemory(void);
void initCpu2Cla1(void);

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
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure the GPIO pin as a push-pull output
    //
    // This is configured by CPU1

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Configure the CLA memory spaces first followed by
    // the CLA task vectors.
    //
    configClaMemory();
    initCpu2Cla1();

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // Run the test
    //
    runTest();

    while(1);
}

//
// runTest - Run CLA test
//
void runTest(void)
{
    int16_t i;
    float fError[NUM_SAMPLES];

    //
    // Force Task 8 and wait
    //
    asm("  IACK  #0x0080");
    asm("  RPT #3 || NOP");
    while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_8))
    {
    }
    WAITSTEP;

    for(i = 0; i < NUM_SAMPLES; i++)
    {
        xn = fAdcInput[i];

        //
        // Force Task 1 and wait
        //
        asm("  IACK  #0x0001");
        asm("  RPT #3 || NOP");
        while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_1))
        {
        }
        WAITSTEP;

        fBiquadOutput[i] = yn;
        fError[i] = fabs(iir_expected[i]-fBiquadOutput[i]);

        if(fError[i] < 0.01)
        {
          pass++;
        }
        else
        {
          fail++;
        }
    }

#if 0
    //
        // Force Task 2 and wait
        //
        asm("  IACK  #0x0002");
        asm("  RPT #3 || NOP");
        while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_2))
        {
        }
        WAITSTEP;

        //
        // Force Task 3 and wait
        //
        asm("  IACK  #0x0004");
        asm("  RPT #3 || NOP");
        while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_3))
        {
        }
        WAITSTEP;

        //
        // Force Task 4 and wait
        //
        asm("  IACK  #0x0008");
        asm("  RPT #3 || NOP");
        while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_4))
        {
        }
        WAITSTEP;

        //
        // Force Task 5 and wait
        //
        asm("  IACK  #0x0010");
        asm("  RPT #3 || NOP");
        while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_5))
        {
        }
        WAITSTEP;

        //
        // Force Task 6 and wait
        //
        asm("  IACK  #0x0020");
        asm("  RPT #3 || NOP");
        while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_6))
        {
        }
        WAITSTEP;

        //
        // Force Task 7 and wait
        //
        asm("  IACK  #0x0040");
        asm("  RPT #3 || NOP");
        while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_7))
        {
        }
        WAITSTEP;
#endif
}

//
// configClaMemory - Configure CLA memory
//
void configClaMemory(void)
{
	uint16_t ipcFlag = 5U;

    //
    // Wait for signal from CPU1 before configuring
    //
    //
    // Send IPC flag 5 to CPU1
    //
    HWREG(IPC_BASE + IPC_O_SET) = 1UL << ipcFlag;

    //
    // Wait for IPC flag 5 from CPU1
    //
    while((HWREG(IPC_BASE + IPC_O_STS) & (1UL << ipcFlag)) == 0x00000000UL)
    {
    }

    //
    // ACK IPC flag 5 for CPU1
    //
    HWREG(IPC_BASE + IPC_O_ACK) = 1UL << ipcFlag;

    //
    // Wait for ACK of IPC flag 5 from CPU1
    //
    while((HWREG(IPC_BASE + IPC_O_FLG) & (1UL << ipcFlag)) != 0x00000000UL)
    {
    }

#ifdef _FLASH
    extern uint32_t Cla1funcsRunStart, Cla1funcsLoadStart, Cla1funcsLoadSize;
    //
    // Copy over code from FLASH to RAM
    //
    memcpy((uint32_t *)&Cla1funcsRunStart, (uint32_t *)&Cla1funcsLoadStart,
           (uint32_t)&Cla1funcsLoadSize);
#endif //_FLASH

#ifdef CPU2
    //
    // Enable CPU2 clocking at the sys clock level
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLA1);
#endif //CPU2

    //
    // Initialize and wait for CLA1ToCPUMsgRAM
    //
    MemCfg_initSections(MEMCFG_SECT_MSGCLA1TOCPU);
    while(!MemCfg_getInitStatus(MEMCFG_SECT_MSGCLA1TOCPU))
    {
    }

    //
    // Initialize and wait for CPUToCLA1MsgRAM
    //
    MemCfg_initSections(MEMCFG_SECT_MSGCPUTOCLA1);
    while(!MemCfg_getInitStatus(MEMCFG_SECT_MSGCPUTOCLA1))
    {
    }

    //
    // Select LS4RAM and LS5RAM to be the programming space for the CLA
    // First configure the CLA to be the master for LS4 and LS5 and then
    // set the space to be a program block
    //
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS4, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS4, MEMCFG_CLA_MEM_PROGRAM);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS5, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS5, MEMCFG_CLA_MEM_PROGRAM);

    //
    // Next configure LS0RAM and LS1RAM as data spaces for the CLA
    // First configure the CLA to be the master for LS0(1) and then
    // set the spaces to be code blocks
    //
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS0, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS0, MEMCFG_CLA_MEM_DATA);

    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS1, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS1, MEMCFG_CLA_MEM_DATA);
}

//
// initCpu2Cla1 - Initialize CLA1 task vectors and end of task ISRs
//
void initCpu2Cla1(void)
{
    //
    // Compute all CLA task vectors
    // On Type-1 CLAs the MVECT registers accept full 16-bit task addresses as
    // opposed to offsets used on older Type-0 CLAs
    //
	// Adding a pragma to suppress the warnings when casting the CLA tasks'
	// function pointers to uint16_t. Compiler believes this to be improper
	// although the CLA only has 16-bit addressing.
	//
#pragma diag_suppress=770
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_1, (uint16_t)&Cla1Task1);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_2, (uint16_t)&Cla1Task2);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_3, (uint16_t)&Cla1Task3);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_4, (uint16_t)&Cla1Task4);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_5, (uint16_t)&Cla1Task5);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_6, (uint16_t)&Cla1Task6);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_7, (uint16_t)&Cla1Task7);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_8, (uint16_t)&Cla1Task8);
#pragma diag_warning=770

    //
    // Enable the IACK instruction to start a task on CLA in software
    // for all  8 CLA tasks. Also, globally enable all 8 tasks (or a
    // subset of tasks) by writing to their respective bits in the
    // MIER register
    //
    CLA_enableIACK(CLA1_BASE);
    CLA_enableTasks(CLA1_BASE, 0x00FF);

    //
    // Configure the vectors for the end-of-task interrupt for all
    // 8 tasks
    //
    Interrupt_register(INT_CLA1_1, cla1Isr1);
    Interrupt_register(INT_CLA1_2, cla1Isr2);
    Interrupt_register(INT_CLA1_3, cla1Isr3);
    Interrupt_register(INT_CLA1_4, cla1Isr4);
    Interrupt_register(INT_CLA1_5, cla1Isr5);
    Interrupt_register(INT_CLA1_6, cla1Isr6);
    Interrupt_register(INT_CLA1_7, cla1Isr7);
    Interrupt_register(INT_CLA1_8, cla1Isr8);

    //
    // Enable CLA interrupts at the group and subgroup levels
    //
    Interrupt_enable(INT_CLA1_1);
    Interrupt_enable(INT_CLA1_2);
    Interrupt_enable(INT_CLA1_3);
    Interrupt_enable(INT_CLA1_4);
    Interrupt_enable(INT_CLA1_5);
    Interrupt_enable(INT_CLA1_6);
    Interrupt_enable(INT_CLA1_7);
    Interrupt_enable(INT_CLA1_8);
    IER |= INTERRUPT_CPU_INT11;
}

//
// cla1Isr1 - CLA1 ISR 1
//
__interrupt void cla1Isr1()
{
    //
    // Acknowledge the end-of-task interrupt for task 1
    //
	Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);
//    asm(" ESTOP0");
}

//
// cla1Isr2 - CLA1 ISR 2
//
__interrupt void cla1Isr2()
{
    asm(" ESTOP0");
}

//
// cla1Isr3 - CLA1 ISR 3
//
__interrupt void cla1Isr3()
{
    asm(" ESTOP0");
}

//
// cla1Isr4 - CLA1 ISR 4
//
__interrupt void cla1Isr4()
{
    asm(" ESTOP0");
}

//
// cla1Isr5 - CLA1 ISR 5
//
__interrupt void cla1Isr5()
{
    asm(" ESTOP0");
}

//
// cla1Isr6 - CLA1 ISR 6
//
__interrupt void cla1Isr6()
{
    asm(" ESTOP0");
}

//
// cla1Isr7 - CLA1 ISR 7
//
__interrupt void cla1Isr7()
{
    asm(" ESTOP0");
}

//
// cla1Isr8 - CLA1 ISR 8
//
__interrupt void cla1Isr8()
{
    //
    // Acknowledge the end-of-task interrupt for task 8
    //
	Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);
//    asm(" ESTOP0");
}

//
// End of file
//
