//#############################################################################
//! \file  /$FOLDER_EXAMPLES$/common/examples_setup.c
//!
//! \brief  Initialization routines for the Fixed Point  library examples
//! \date   Sep 9, 2014
//
//  Group:             C2000
//  Target Family:     C28x
//
//#############################################################################
// $Copyright: Copyright (C) 2014-2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//            
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "examples_setup.h"
#include "DSP28x_Project.h"
#include <cpy_tbl.h>
//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************
extern COPY_TABLE ramfuncsCopyTable;
//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

void FIXPT_DSP_initSystemClocks()
{
	InitSysCtrl();				//Enable peripheral clocks

}

void FIXPT_DSP_initEpie()
{
	DINT;						//Globally disable maskable CPU interrupts
	InitPieCtrl();				//Clear and disable all PIE interrupts
	IER = 0x0000;				//Individually disable maskable CPU interrupts
	IFR = 0x0000;				//Clear all CPU interrupt flags
	InitPieVectTable();			//Populate the PIE interrupt vector table with shell ISRs
}

#ifdef _FLASH
void FIXPT_DSP_initFlash()
{
// Copy time critical code and Flash setup code to RAM
// The  ramfuncs copy table is created by the linker. Please see the linker command
// file for its definition
   copy_in(&ramfuncsCopyTable);

// Call Flash Initialization to setup flash waitstates
// This function must reside in RAM
   InitFlash();
}
#endif //FLASH

// End of file
