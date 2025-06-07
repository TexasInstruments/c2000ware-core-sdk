//#############################################################################
//
// FILE:   f2807x_examples_setup.c
//
// TITLE:  Initialization routines for CLA Math library examples
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Includes
//
#include "F28x_Project.h"
#include "F2807x_Cla_defines.h"
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
void initPIE(void);
void configCLAMemory(void);
void initCPU1CLA1(void);
void done(void);

//*****************************************************************************
// main
//*****************************************************************************
int main( void )
{
    //
    // Initialize device clock and peripherals
    //
    InitSysCtrl();

    initPIE();
    
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
// void initPIE()
//
// Initialize the PIE.
//
void initPIE()
{
    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    InitPieVectTable();
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

    EALLOW;
    //
    // Perform RAM initialization on the message RAMs
    //
    MemCfgRegs.MSGxINIT.bit.INIT_CLA1TOCPU = 1;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CLA1TOCPU != 1)
    {
    }

    MemCfgRegs.MSGxINIT.bit.INIT_CPUTOCLA1 = 1;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CPUTOCLA1 != 1)
    {
    }

    //
    // Select LS0RAM to be program space for the CLA
    // First, configure the CLA to be the master for LS0
    // Second, set the space to be a program block
    //
    MemCfgRegs.LSxMSEL.bit.MSEL_LS0 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS0 = 1;

    //
    // Configure RAM blocks LS1-LS5 as data spaces for the CLA
    // First, configure the CLA to be the master for LSx
    // Second, set the spaces to be code blocks
    //
    MemCfgRegs.LSxMSEL.bit.MSEL_LS1 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS1 = 0;

    MemCfgRegs.LSxMSEL.bit.MSEL_LS2 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS2 = 0;

    MemCfgRegs.LSxMSEL.bit.MSEL_LS3 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS3 = 0;

    MemCfgRegs.LSxMSEL.bit.MSEL_LS4 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS4 = 0;

    MemCfgRegs.LSxMSEL.bit.MSEL_LS5 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS5 = 0;

    EDIS;
}

//
// void initCPU1CLA1(void)
//
// This function initializes the CLA for task execution.
//
void initCPU1CLA1(void)
{
    //
    // Compute all CLA task vectors
    // On Type-1 CLAs the MVECT registers accept full 16-bit task addresses as
    // opposed to offsets used on older Type-0 CLAs
    //
    // Assign the task vectors
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
    // Enable IACK instruction to start a task on CLA in software
    // and enable all  8 CLA tasks
    //
    __asm("   RPT #3 || NOP");
    Cla1Regs.MCTL.bit.IACKE = 1;
    Cla1Regs.MIER.all   = 0x00FF;
    EDIS;
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
