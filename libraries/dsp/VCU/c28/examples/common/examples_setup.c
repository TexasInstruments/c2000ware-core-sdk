//#############################################################################
//! \file  /examples_ccsv5/common/examples_setup.c
//!
//! \brief  Initialization routines for the VCU2 library examples
//!
//! \date   July 16, 2013
//
//  Group:             C2000
//  Target Family:     F2837x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "examples_setup.h"

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

void VCU2_initSystemClocks()
{
	InitSysCtrl();				//Enable peripheral clocks

	ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 0x00;
}

void VCU2_initEpie()
{
	DINT;						//Globally disable maskable CPU interrupts
	InitPieCtrl();				//Clear and disable all PIE interrupts
	IER = 0x0000;				//Individually disable maskable CPU interrupts
	IFR = 0x0000;				//Clear all CPU interrupt flags
	InitPieVectTable();			//Populate the PIE interrupt vector table with shell ISRs
}

#ifdef FLASH
void VCU2_initFlash()
{
	EALLOW;

	//At reset bank and pump are in sleep
	//A Flash access will power up the bank and pump automatically
	//After a Flash access, bank and pump go to low power mode (configurable in FBFALLBACK/FPAC1 registers)-
	//if there is no further access to flash
	//Power up Flash bank and pump and this also sets the fall back mode of flash and pump as active
	Flash0CtrlRegs.FPAC1.bit.PMPPWR = 0x1;
	Flash0CtrlRegs.FBFALLBACK.bit.BNKPWR0 = 0x3;

	//Disable Cache and prefetch mechanism before changing wait states
	Flash0CtrlRegs.FRD_INTF_CTRL.bit.DATA_CACHE_EN = 0;
	Flash0CtrlRegs.FRD_INTF_CTRL.bit.PREFETCH_EN = 0;

	//Set waitstates according to frequency
	//                CAUTION
	//Minimum waitstates required for the flash operating
	//at a given CPU rate must be characterized by TI.
	//Refer to the datasheet for the latest information.
#if CPU_FRQ_200MHZ
	Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x3;
#endif

#if CPU_FRQ_150MHZ
	Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x2;
#endif

#if CPU_FRQ_120MHZ
	Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x2;
#endif

	//Enable Cache and prefetch mechanism to improve performance
	//of code executed from Flash.
	Flash0CtrlRegs.FRD_INTF_CTRL.bit.DATA_CACHE_EN = 1;
	Flash0CtrlRegs.FRD_INTF_CTRL.bit.PREFETCH_EN = 1;

	//At reset, ECC is enabled
	//If it is disabled by application software and if application again wants to enable ECC
	Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0xA;

	EDIS;

	//Force a pipeline flush to ensure that the write to
	//the last register configured occurs before returning.

	__asm(" RPT #7 || NOP");
}
#endif //FLASH


void done(void)
{
    for(;;);
}
// End of file
