//#############################################################################
//
// FILE:   f2838x_examples_setup.c
//
// TITLE:  Initialization routines for CLA Math library examples
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Includes
//
#include "driverlib.h"
#include "device.h"
#include "cla_shared.h"

//
// Globals
//
int16_t pass = 0, fail = 0;
extern uint16_t Cla1ProgRunStart, Cla1ProgLoadStart, Cla1ProgLoadSize;
extern uint16_t CLA1mathTablesRunStart, CLA1mathTablesLoadStart;
extern uint16_t CLA1mathTablesLoadSize;

//
// Prototypes
//
void configCLAMemory(void);
void initCPU1CLA1(void);
void done(void);

//
// int main(void)
//
int main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();
    
    configCLAMemory();

    initCPU1CLA1();

    //
    // Run the test with the input test vectors
    //
    test_run();

    //
    // Verify the results
    //
    test_report();

    //
    // End of Test
    //
    done();

    //
    // Code must never reach this point
    //
    return(1);
}

//
// void configCLAMemory(void)
//
// This function copies ramfuncs, CLA program and CLA Math tables
// into RAM and configures the RAM blocks for CLA execution.
//
void configCLAMemory(void)
{

#ifdef _FLASH
    //
    // Copy over code and tables from FLASH to RAM
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (uint32_t)&RamfuncsLoadSize);
    memcpy((uint32_t *)&Cla1ProgRunStart, (uint32_t *)&Cla1ProgLoadStart,
            (uint32_t)&Cla1ProgLoadSize);

#if !(CLA_MATH_TABLES_IN_ROM)
    //
    // Copy over CLA Math tables from FLASH to RAM
    //
    memcpy((uint32_t *)&CLA1mathTablesRunStart, (uint32_t *)&CLA1mathTablesLoadStart,
            (uint32_t)&CLA1mathTablesLoadSize);
#endif
#endif

    //
    // Perform RAM initialization on the message RAMs
    //
    MemCfg_initSections(MEMCFG_SECT_MSGX_ALL);
    while(MemCfg_getInitStatus(MEMCFG_SECT_MSGX_ALL) == false)
    {
    }

    //
    // Select LS0RAM to be program space for the CLA
    // First, configure the CLA to be the master for LS0
    // Second, set the space to be a program block
    //
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS0, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS0, MEMCFG_CLA_MEM_PROGRAM);

    //
    // Configure RAM blocks LS1-LS5 as data spaces for the CLA
    // First, configure the CLA to be the master for LSx
    // Second, set the spaces to be code blocks
    //
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS1, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS1, MEMCFG_CLA_MEM_DATA);

    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS2, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS2, MEMCFG_CLA_MEM_DATA);

    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS3, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS3, MEMCFG_CLA_MEM_DATA);

    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS4, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS4, MEMCFG_CLA_MEM_DATA);

    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS5, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS5, MEMCFG_CLA_MEM_DATA);
}

//
// void initCPU1CLA1(void)
//
// This function initializes the CLA for task execution.
//
void initCPU1CLA1(void)
{
    //
    // Suppressing #770-D conversion from pointer to smaller integer
    // The CLA address range is 16 bits so the addresses passed to the MVECT
    // registers will be in the lower 64KW address space. Turn the warning
    // back on after the MVECTs are assigned addresses
    //
#pragma diag_suppress=770

    //
    // Compute all CLA task vectors
    // On Type-2 CLAs the MVECT registers accept full 16-bit task addresses as
    // opposed to offsets used on older Type-0 CLAs
    //
    // Assign the task vectors
    //
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
    // Enable IACK instruction to start a task on CLA in software
    // and enable all  8 CLA tasks
    //
    __asm("   RPT #3 || NOP");
    CLA_enableIACK(CLA1_BASE);
    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_ALL);
}

//
// void done(void)
//
// This is an infinite loop.
//
void done(void)
{
    for(;;)
    {
    }
}

//
// End of file
//
