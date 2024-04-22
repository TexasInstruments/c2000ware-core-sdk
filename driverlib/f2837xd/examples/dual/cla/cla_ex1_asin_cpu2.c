//###########################################################################
//
// FILE:   cla_ex1_asin_cpu2.c
//
// TITLE:  CLA Arcsine Example for F2837xD.
//
// Dual Core arcsine example. This example demonstrates how to run CLA tasks
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
#include "cla_ex1_asin_shared.h"

//
// Defines
//
#define WAITSTEP     asm(" RPT #255 || NOP")

//
// Globals
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
#pragma DATA_SECTION("CLADataLS0")
#else
#pragma DATA_SECTION(CLAasinTable,"CLADataLS0")
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
    int16_t i, error;

    for(i = 0; i < BUFFER_SIZE; i++)
    {
        fVal= (float)(BUFFER_SIZE - i)/(float)BUFFER_SIZE;

        //
        // Force Task 1 and wait
        //
        asm("  IACK  #0x0001");
        asm("  RPT #3 || NOP");
        while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_1))
        {
        }
        WAITSTEP;

        y[i] = fResult;
        error = fabs(asin_expected[i]-y[i]);

        if(error < 0.1)
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

    //
    // Force Task 8 and wait
    //
    asm("  IACK  #0x0080");
    asm("  RPT #3 || NOP");
    while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_8))
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
__interrupt void cla1Isr1 ()
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
	Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);
//    asm(" ESTOP0");
}

//
// End of file
//
