//#############################################################################
//
// FILE:        examples_setup.c
//
// Description: Initialization routines for the CLA FFT library examples
//
//#############################################################################
// $TI Release: CLA Math Library 4.05.00.00 $
// $Release Date: Apr 7, 2024 $
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "f2837x_fft_examples_setup.h"
#include "F28x_Project.h"
#include "driverlib.h"
#include "device.h"

//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

void CLA_DSP_initSystemClocks()
{
    Device_init();
}

void CLA_DSP_initEpie()
{
    Interrupt_initModule();
    Interrupt_initVectorTable();
}


void CLA_DSP_configClaMemory(void)
{
	extern uint32_t Cla1ProgRunStart, Cla1ProgLoadStart, Cla1ProgLoadSize;
	extern uint32_t CLA1fftTablesRunStart, CLA1fftTablesLoadStart, CLA1fftTablesLoadSize;

	EALLOW;

#ifdef _FLASH
	// Copy over code and tables from FLASH to RAM
	memcpy((uint32_t *)&Cla1ProgRunStart, (uint32_t *)&Cla1ProgLoadStart,
			(uint32_t)&Cla1ProgLoadSize);

	memcpy((uint32_t *)&CLA1fftTablesRunStart, (uint32_t *)&CLA1fftTablesLoadStart,
			(uint32_t)&CLA1fftTablesLoadSize);
#endif //_FLASH

	// Initialize and wait for CLA1ToCPUMsgRAM
    MemCfg_initSections(MEMCFG_SECT_MSGCLA1TOCPU);
    while (!MemCfg_getInitStatus(MEMCFG_SECT_MSGCLA1TOCPU)){};

	// Initialize and wait for CPUToCLA1MsgRAM
    MemCfg_initSections(MEMCFG_SECT_MSGCPUTOCLA1);
    while (!MemCfg_getInitStatus(MEMCFG_SECT_MSGCPUTOCLA1)){};

	// Select LS0-LS1RAM to be the programming space for the CLA
	// First configure the CLA to be the master for LS0 and then
	// set the space to be a program block
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS0,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS0,MEMCFG_CLA_MEM_PROGRAM);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS1,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS1,MEMCFG_CLA_MEM_PROGRAM);

	//Next configure LS2-LS5RAM as data spaces for the CLA
	// First configure the CLA to be the master for LSx and then
    // set the spaces to be code blocks

    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS2,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS2, MEMCFG_CLA_MEM_DATA);

    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS3,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS3, MEMCFG_CLA_MEM_DATA);

    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS4,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS4, MEMCFG_CLA_MEM_DATA);

    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS5,MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS5, MEMCFG_CLA_MEM_DATA);

}

void CLA_DSP_initCpu1Cla1(void)
{
	// Compute all CLA task vectors
	// On Type-1 CLAs the MVECT registers accept full 16-bit task addresses as
	// opposed to offsets used on older Type-0 CLAs

//
// Suppressing #770-D conversion from pointer to smaller integer
// The CLA address range is 16 bits so the addresses passed to the MVECT
// registers will be in the lower 64KW address space. Turn the warning
// back on after the MVECTs are assigned addresses
//
#pragma diag_suppress=770
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_1,(uint16_t)&Cla1Task1);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_2,(uint16_t)&Cla1Task2);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_3,(uint16_t)&Cla1Task3);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_4,(uint16_t)&Cla1Task4);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_5,(uint16_t)&Cla1Task5);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_6,(uint16_t)&Cla1Task6);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_7,(uint16_t)&Cla1Task7);
    CLA_mapTaskVector(CLA1_BASE,CLA_MVECT_8,(uint16_t)&Cla1Task8);

#pragma diag_warning=770

	// Enable IACK instruction to start a task on CLA in software
	// for all  8 CLA tasks

    CLA_enableIACK(CLA1_BASE);
    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_ALL);

    // Configure the vectors for the end-of-task interrupt for all
    // 8 tasks

    Interrupt_register(INT_CLA1_1, &cla1Isr1);
    Interrupt_register(INT_CLA1_2, &cla1Isr2);
    Interrupt_register(INT_CLA1_3, &cla1Isr3);
    Interrupt_register(INT_CLA1_4, &cla1Isr4);
    Interrupt_register(INT_CLA1_5, &cla1Isr5);
    Interrupt_register(INT_CLA1_6, &cla1Isr6);
    Interrupt_register(INT_CLA1_7, &cla1Isr7);
    Interrupt_register(INT_CLA1_8, &cla1Isr8);
}
// End of file
