//#############################################################################
//! \file  /$FOLDER_TEST$/common/examples_setup.c
//!
//! \brief  Test framework for the Fixed Point library examples
//! \date   Sep 22, 2014
//
//  Group:             C2000
//  Target Family:     C28x
//
//#############################################################################
//
//
//$Copyright: Copyright (C) 2014-2025 Texas Instruments Incorporated -
//            http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################
#define XSTRINGIZE(s)	STRINGIZE(s)  // calls stringize(s), if s is a macro it
                                      // will expand s first
#define STRINGIZE(s)	#s			  // TREAT s as a literal, if s is a macro
                                      // it wont be expanded
#define XCONCAT(x,y,z) CONCAT(x,y,z)  // expand x and y then call concat on the
                                      // expanded macros x and y
#define CONCAT(x,y,z)	x ## y ## z   // concats x and y but doesnt expand
                                      // x and y if they are macros
//*****************************************************************************
// includes
//*****************************************************************************
#include "test_setup.h"
#include "f28x_project.h"
#include <cpy_tbl.h>
// #include XSTRINGIZE(XCONCAT(test_,TEST_NAME,.h))
//#include "test_fir16d_alt.h" // arav modified
//#include "test_fir16d.h" // arav modified
//#include "test_cfft.h" // arav modified
//#include "test_fir32d.h"
//#include "test_fir32d_alt.h" // arav modified
//#include "test_iir16d.h" // arav modified
//#include "test_iir32d.h" // arav modified
#include "test_rfft.h" // arav modified

//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************
extern COPY_TABLE ramfuncsCopyTable;

uint16_t pass = 0;
uint16_t fail = 0;

//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************
// Start of main
int main(void) {
	//Locals

#ifdef _FLASH
    FIXPT_DSP_initFlash();
#endif //_FLASH
    FIXPT_DSP_initSystemClocks();

    FIXPT_DSP_initEpie();

   	FIXPT_DSP_runTest();

   	FIXPT_DSP_genReport();

    FIXPT_DSP_testEnd();

	return 1;

} // End of main

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
#endif //_FLASH


void FIXPT_DSP_testEnd()
{
    //
    // Everything went right
    //
    done();
    //
    // Should never stop at this point
    //
    asm("   ESTOP0");
    for(;;);
}

void FIXPT_DSP_testError()
{
	//
	// Something went wrong.
	//
	asm("   ESTOP0");
	for(;;);
}

void done(void)
{
    for(;;);
}
// End of file
