//###########################################################################
//
//!  \addtogroup cpu01_example_list
//!  <h1>Software Prioritized Interrupts(sw_prioritized_interrupts)</h1>
//!
//!  For most applications, the hardware prioritizing of the
//!  the PIE module is sufficient.  For applications that need custom
//!  prioritizing, this example illustrates how this can be done
//!  through software.
//!
//!  For more information on F2837xD interrupt priorities, refer to the
//!  "Example ISR Priorities" Appendix in the Firmware Development Users guide
//!
//!  This program simulates interrupt conflicts by writing to the
//!  PIEIFR registers.  This will cause multiple interrupt requests to come into
//!  the PIE block at the same time.
//!
//!  The interrupt service routines are software prioritized as per
//!  the table found in the F2837xD_SWPrioritizedIsrLevels.h file.
//!
//!  \b Running \b the \b Application
//!  -# Before compiling you must set the Global and Group interrupt priorities
//!  in the F2837xD_SWPrioritizedIsrLevels.h file.
//!  -# Select which test case you'd like to run with the
//!     \#define CASE directive (1-9, default 1).
//!  -# Compile the code, load, and run
//!  -# At the end of each test there is a hard coded breakpoint (ESTOP0).
//!     When code stops at the breakpoint, examine the ISRTrace buffer to
//!     see the order in which the ISR's completed. All PIE interrupts will
//!     be added to the ISRTrace.
//!     The ISRTrace will consist of a list of hex values as shown: \n
//!     0x00wx    <- PIE Group w interrupt x finished first \n
//!     0x00yz    <- PIE Group y interrupt z finished next \n
//!  -# If desired, set a new set of Global and Group interrupt priorities
//!  and repeat the test to see the change.
//!
//!  \b Watch \b Variables \n
//!  - \b ISRTrace - Trace of ISR's in the order they complete. After each
//!    test, examine this buffer to determine if the ISR's completed in the
//!    order desired.
//!
//
//###########################################################################
//
// $Release Date:  $
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
#include "F2837xD_SWPrioritizedIsrLevels.h"

//
// Defines
//
#define ISRS_GROUP1  (M_INT1|M_INT2|M_INT4|M_INT5|M_INT6|M_INT7|M_INT8)
#define ISRS_GROUP2  (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6|M_INT7|M_INT8)
#define ISRS_GROUP3  (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6|M_INT7|M_INT8)
#define ISRS_GROUP4  (M_INT1|M_INT2|M_INT3|M_INT7|M_INT8)
#define ISRS_GROUP5  (M_INT1|M_INT2|M_INT4|M_INT5|M_INT8)
#define ISRS_GROUP6  (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6)
#define ISRS_GROUP7  (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6)
#define ISRS_GROUP8  (M_INT1|M_INT2)
#define ISRS_GROUP9  (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6)
#define ISRS_GROUP10 (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6|M_INT7|M_INT8)
#define ISRS_GROUP11 (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6|M_INT7|M_INT8)
#define ISRS_GROUP12 (M_INT1|M_INT7|M_INT8)

#define CASE    1 // Define which test case to run (CASE 1 is default)

//
// Globals
//
Uint16  ISRTrace[50];   // This array will be used as a trace to check the
                        // order that the interrupts were serviced
Uint16  ISRTraceIndex;  // used to update an element in the trace buffer

//
// Main
//
void main(void)
{
   Uint16 i;

//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
   InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
//
// InitGpio();  // Skipped for this example

//
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
   DINT;

//
// Initialize PIE control registers to their default state.
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
// Step 4. User specific code, enable interrupts:
//

//
// CASE 1:
//
#if (CASE==1)
       //
       // Force all group 1 interrupts at once by writing to the PIEIFR1
       // register
       //

       //
       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR
       // registers
       //
	   DINT;
	   for(i = 0; i < 50; i++)
       {
           ISRTrace[i] = 0;
       }

	   ISRTraceIndex = 0;
       InitPieCtrl();

       IER = 0;
       IFR &= 0;

       //
       // Enable the PIE block
       //
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       //
       // Enable PIE group 1 interrupt 1-8
       //
       PieCtrlRegs.PIEIER1.all = 0x00FF;

       //
       // Make sure PIEACK for group 1 is clear (default after reset)
       //
       PieCtrlRegs.PIEACK.all = M_INT1;

       //
       // Enable CPU INT1
       //
       IER |= M_INT1;

       //
       // Force all valid interrupts for Group 1
       //
       PieCtrlRegs.PIEIFR1.all = ISRS_GROUP1;

       //
       // Enable global Interrupts CPU level:
       //
	   EINT;   // Enable Global interrupt INTM

       //
	   // Wait for all Group 1 interrupts to be serviced
       //
	   while(PieCtrlRegs.PIEIFR1.all != 0x0000 ){}

       //
       // Stop here and check the ISRTrace to determine which order the
       // ISR Routines completed.  The order is dependant on the priority
       // assigned in the F2837xD_SWPrioritizedIsrLevels.h file
       //
       // The ISRTrace will contain a list of values corresponding to the
       // interrupts serviced in the order they were serviced.
	   // For example if the ISRTrace looks like this
	   //        0x0014     ISR Group 1 interrupt 4
	   //        0x0017     ISR Group 1 interrupt 7
	   //        0x0016     ISR Group 1 interrupt 6
	   //        0x0015     ISR Group 1 interrupt 5
	   //        0x0018     ISR Group 1 interrupt 8
	   //        0x0012     ISR Group 1 interrupt 2
	   //        0x0011     ISR Group 1 interrupt 1
	   //        0x0000     end of trace
       //
	  __asm("        ESTOP0");

//
// CASE 2:
//
#elif (CASE==2)
       //
       // Force all group 2 interrupts at once by writing to the PIEIFR2
       // register
       //

       //
       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR
       // registers
       //
	   DINT;
	   for(i = 0; i < 50; i++)
       {
           ISRTrace[i] = 0;
       }

	   ISRTraceIndex = 0;
       InitPieCtrl();

       IER = 0;
       IFR &= 0;

       //
       // Enable the PIE block
       //
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       //
       // Enable PIE group 2 interrupts 1-8
       //
       PieCtrlRegs.PIEIER2.all = 0x00FF;

       //
       // Enable CPU INT2
       //
       IER |= (M_INT2);

       //
	   // Make sure PIEACK for group 2 is clear (default after reset)
       //
       PieCtrlRegs.PIEACK.all = M_INT2;

       //
       // Force all valid interrupts for Group 2
       //
       PieCtrlRegs.PIEIFR2.all = ISRS_GROUP2;

       //
	   // Enable Global interrupts
       //
	   EINT;

	   //
       // Wait for all group 2 interrupts to be serviced
       //
	   while(PieCtrlRegs.PIEIFR2.all != 0x0000 ){}

       //
       // Stop here and check the order the ISR's were serviced in the
       // ISRTrace
       //
	  __asm("        ESTOP0");

//
// CASE 3:
//
#elif (CASE==3)
       //
       // Force all group 3 interrupts at once by writing to the PIEIFR3
       // register
       //

       //
       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR
       // registers
       //
	   DINT;
	   for(i = 0; i < 50; i++)
       {
           ISRTrace[i] = 0;
       }

	   ISRTraceIndex = 0;
       InitPieCtrl();

       IER = 0;
       IFR &= 0;

       //
       // Enable the PIE block
       //
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       //
       // Enable PIE group 3 interrupts 1-8
       //
       PieCtrlRegs.PIEIER3.all = 0x00FF;

       //
	   // Make sure PIEACK for group 3 is clear (default after reset)
       //
       PieCtrlRegs.PIEACK.all = M_INT3;

       //
       // Enable CPU INT3
       //
       IER |= (M_INT3);

       //
       // Force all valid interrupts for Group 3
       //
       PieCtrlRegs.PIEIFR3.all = ISRS_GROUP3;

       //
	   // Enable Global interrupts
       //
	   EINT;

       //
	   // Wait for all group 3 interrupts to be serviced
       //
	   while(PieCtrlRegs.PIEIFR3.all != 0x0000 ){}

       //
       // Stop here and check the order the ISR's were serviced in the
       // ISRTrace
       //
	  __asm("        ESTOP0");

//
// CASE 4:
//
#elif (CASE==4)
       //
       // Force all group 4 interrupts at once by writing to the PIEIFR4
       // register
       //

       //
       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR
       // registers
       //
	   DINT;
	   for(i = 0; i < 50; i++)
       {
           ISRTrace[i] = 0;
       }

	   ISRTraceIndex = 0;
       InitPieCtrl();

       IER = 0;
       IFR &= 0;

       //
       // Enable the PIE block
       //
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       //
       // Enable PIE group 4 interrupts 1-8
       //
       PieCtrlRegs.PIEIER4.all = 0x00FF;

       //
	   // Make sure PIEACK for group 4 is clear (default after reset)
       //
       PieCtrlRegs.PIEACK.all = M_INT4;

       //
       // Enable CPU INT4
       //
       IER |= (M_INT4);

       //
       // Force all valid interrupts for Group 4
       //
       PieCtrlRegs.PIEIFR4.all = ISRS_GROUP4;

       //
	   // Enable Global interrupts
       //
	   EINT;

       //
	   // Wait for all group 4 interrupts to be serviced
       //
	   while(PieCtrlRegs.PIEIFR4.all != 0x0000 ){}

       //
       // Stop here and check the order the ISR's were serviced in the
       // ISRTrace
       //
	  __asm("        ESTOP0");

//
// CASE 5:
//
#elif (CASE==5)
       //
       // Force all group 6 interrupts at once by writing to the PIEIFR6
       // register
       //

       //
       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR
       // registers
       //
	   DINT;
	   for(i = 0; i < 50; i++)
       {
           ISRTrace[i] = 0;
       }

	   ISRTraceIndex = 0;
       InitPieCtrl();

       IER = 0;
       IFR &= 0;

       //
       // Enable the PIE block
       //
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       //
       // Enable PIE group 6 interrupts 1-8
       //
       PieCtrlRegs.PIEIER6.all = 0x00FF;

       //
	   // Make sure PIEACK for group 6 is clear (default after reset)
       //
       PieCtrlRegs.PIEACK.all = M_INT6;

       //
       // Enable CPU INT6
       //
       IER |= (M_INT6);

       //
       // Force all valid interrupts for Group 6
       //
       PieCtrlRegs.PIEIFR6.all = ISRS_GROUP6;

       //
	   // Enable Global interrupts
       //
	   EINT;

       //
	   // Wait for all group 6 interrupts to be serviced
       //
	   while(PieCtrlRegs.PIEIFR6.all != 0x0000 ){}

       //
       // Stop here and check the order the ISR's were serviced in the
       // ISRTrace
       //
	  __asm("        ESTOP0");

//
// CASE 6:
//
#elif (CASE==6)
       //
       // Force all group 9 interrupts at once by writing to the PIEIFR4
       // register
       //

       //
       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR
       // registers
       //
	   DINT;
	   for(i = 0; i < 50; i++)
       {
           ISRTrace[i] = 0;
       }

	   ISRTraceIndex = 0;
       InitPieCtrl();

       IER = 0;
       IFR &= 0;

       //
       // Enable the PIE block
       //
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       //
       // Enable PIE group 9 interrupts 1-8
       //
       PieCtrlRegs.PIEIER9.all = 0x00FF;

       //
	   // Make sure PIEACK for group 9 is clear (default after reset)
       //
       PieCtrlRegs.PIEACK.all = M_INT9;

       //
       // Enable CPU INT9
       //
       IER |= (M_INT9);

       //
       // Force all valid interrupts for Group 9
       //
       PieCtrlRegs.PIEIFR9.all = ISRS_GROUP9;

       //
	   // Enable Global interrupts
       //
	   EINT;

       //
	   // Wait for all group 9 interrupts to be serviced
       //
	   while(PieCtrlRegs.PIEIFR9.all != 0x0000 ){}

       //
       // Stop here and check the order the ISR's were serviced in the
       // ISRTrace
       //
	  __asm("        ESTOP0");

//
// CASE 7:
//
#elif (CASE==7)
       //
       // Force all group 1 and group 2 interrupts at once
       //

       //
       // Setup next test - fire interrupts from Group 1 and Group 2
       //

       //
       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR
       // registers
       //
	   DINT;
	   for(i = 0; i < 50; i++)
       {
           ISRTrace[i] = 0;
       }

	   ISRTraceIndex = 0;
       InitPieCtrl();

       IER = 0;
       IFR &= 0;

       //
       // Enable the PIE block
       //
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       //
       // Enable PIE group 1 and group 2 interrupts 1-8
       //
       PieCtrlRegs.PIEIER1.all = 0x00FF;
       PieCtrlRegs.PIEIER2.all = 0x00FF;

       //
	   // Make sure PIEACK for group 1 & 2 are clear (default after reset)
       //
       PieCtrlRegs.PIEACK.all = (M_INT1 | M_INT2);

       //
       // Enable CPU INT1 and INT2
       //
       IER |= (M_INT1|M_INT2);

       //
       // Force all valid interrupts for Group 1 and from Group 2
       //
       PieCtrlRegs.PIEIFR1.all = ISRS_GROUP1;
       PieCtrlRegs.PIEIFR2.all = ISRS_GROUP2;

       //
	   // Enable Global interrupts
       //
	   EINT;

       //
	   // Wait for all group 1 and group 2 interrupts to be serviced
       //
	   while(PieCtrlRegs.PIEIFR1.all != 0x0000 ||
             PieCtrlRegs.PIEIFR2.all != 0x0000 ){}

       //
	   // Check the ISRTrace to determine which order the ISR Routines
       // completed
       //
	  __asm("        ESTOP0");

//
// CASE 8:
//
#elif (CASE==8)
       //
       // Force all group 1 and group 2 and group 3 interrupts at once
       //

       //
       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR
       // registers
       //
	   DINT;
	   for(i = 0; i < 50; i++)
       {
           ISRTrace[i] = 0;
       }

	   ISRTraceIndex = 0;
       InitPieCtrl();

       IER = 0;
       IFR &= 0;

       //
       // Enable the PIE block
       //
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       //
       // Enable PIE group 1, 2 and 3 interrupts 1-8
       //
       PieCtrlRegs.PIEIER1.all = 0x00FF;
       PieCtrlRegs.PIEIER2.all = 0x00FF;
       PieCtrlRegs.PIEIER3.all = 0x00FF;

	   //
       // Make sure PIEACK for group 1, 2 & 3 are clear (default after reset)
       //
       PieCtrlRegs.PIEACK.all = (M_INT1|M_INT2|M_INT3);

       //
       // Enable CPU INT1, INT2 & INT3
       //
       IER |= (M_INT1|M_INT2|M_INT3);

       //
       // Force all valid interrupts for Group1, 2 and 3
       //
       PieCtrlRegs.PIEIFR1.all = ISRS_GROUP1;
       PieCtrlRegs.PIEIFR2.all = ISRS_GROUP2;
       PieCtrlRegs.PIEIFR3.all = ISRS_GROUP3;

	   //
       // Enable Global interrupts
       //
	   EINT;

	   //
       // Wait for all group 1 and group 2 and group 3 interrupts to be
       // serviced
       //
	   while(PieCtrlRegs.PIEIFR1.all != 0x0000 ||
             PieCtrlRegs.PIEIFR2.all != 0x0000 ||
             PieCtrlRegs.PIEIFR3.all != 0x0000 ) {}

       //
	   // Check the ISRTrace to determine which order the ISR Routines
       // completed
       //
	  __asm("        ESTOP0");

//
// CASE 9:
//
#elif (CASE==9)
       //
       // Force all used PIE interrupts at once
       //

       //
       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR
       // registers
       //
	   DINT;
	   for(i = 0; i < 50; i++)
       {
           ISRTrace[i] = 0;
       }

	   ISRTraceIndex = 0;
       InitPieCtrl();

       IER = 0;
       IFR &= 0;

       //
       // Enable the PIE block
       //
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       //
       // Enable all PIE group interrupts 1-8
       //
       PieCtrlRegs.PIEIER1.all = 0x00FF;
       PieCtrlRegs.PIEIER2.all = 0x00FF;
       PieCtrlRegs.PIEIER3.all = 0x00FF;
       PieCtrlRegs.PIEIER4.all = 0x00FF;
       PieCtrlRegs.PIEIER6.all = 0x00FF;
       PieCtrlRegs.PIEIER8.all = 0x00FF;
       PieCtrlRegs.PIEIER9.all = 0x00FF;
       PieCtrlRegs.PIEIER10.all = 0x00FF;
       PieCtrlRegs.PIEIER12.all = 0x00FF;

	   //
       // Make sure PIEACK for group 1, 2, 3, 4, 6, 8, 9, 10, and 12 are
       // clear (default after reset)
       //
       PieCtrlRegs.PIEACK.all = (M_INT1|M_INT2|M_INT3|M_INT4|M_INT6|M_INT8|
                                 M_INT9|M_INT10|M_INT12);

       //
       // Enable CPU INT1, INT2, INT3, INT4, INT6, INT8, INT9, INT10, and INT12
       //
       IER |= (M_INT1|M_INT2|M_INT3|M_INT4|M_INT6|M_INT8|M_INT9|M_INT10|
               M_INT12);

       //
       // Force all valid interrupts for all PIE groups
       //
       PieCtrlRegs.PIEIFR1.all = ISRS_GROUP1;
       PieCtrlRegs.PIEIFR2.all = ISRS_GROUP2;
       PieCtrlRegs.PIEIFR3.all = ISRS_GROUP3;
       PieCtrlRegs.PIEIFR4.all = ISRS_GROUP4;
       PieCtrlRegs.PIEIFR6.all = ISRS_GROUP6;
       PieCtrlRegs.PIEIFR8.all = ISRS_GROUP8;
       PieCtrlRegs.PIEIFR9.all = ISRS_GROUP9;
       PieCtrlRegs.PIEIFR10.all = ISRS_GROUP10;
       PieCtrlRegs.PIEIFR12.all = ISRS_GROUP12

	   //
       // Enable Global interrupts - CPU level
       //
	   EINT;

	   //
       // Wait for all group interrupts to be serviced
       //
	   while(PieCtrlRegs.PIEIFR1.all != 0x0000 ||
             PieCtrlRegs.PIEIFR2.all != 0x0000 ||
             PieCtrlRegs.PIEIFR3.all != 0x0000 ||
             PieCtrlRegs.PIEIFR4.all != 0x0000 ||
             PieCtrlRegs.PIEIFR6.all != 0x0000 ||
             PieCtrlRegs.PIEIFR8.all != 0x0000 ||
             PieCtrlRegs.PIEIFR9.all != 0x0000 ||
             PieCtrlRegs.PIEIFR10.all!= 0x0000 ||
             PieCtrlRegs.PIEIFR12.all!= 0x0000) {}

       //
	   // Check the ISRTrace to determine which order the ISR Routines
       // completed
       //
	  __asm("        ESTOP0");

#endif
}

//
// End of file
//
