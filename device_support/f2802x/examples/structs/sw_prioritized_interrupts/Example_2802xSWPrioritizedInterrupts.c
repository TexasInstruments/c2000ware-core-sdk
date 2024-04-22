//###########################################################################
//
// FILE:   Example_2802xSWPrioritizedInterrupts.c
//
// TITLE:  f2802x Software Prioritized Interrupt Example.
//
// ASSUMPTIONS:
//
//    This program requires the f2802x header files.
//
//    As supplied, this project is configured for "boot to SARAM"
//    operation.  The 2802x Boot Mode table is shown below.
//    For information on configuring the boot mode of an eZdsp,
//    please refer to the documentation included with the eZdsp,
//
//    $Boot_Table
//    While an emulator is connected to your device, the TRSTn pin = 1,
//    which sets the device into EMU_BOOT boot mode. In this mode, the
//    peripheral boot modes are as follows:
//
//      Boot Mode:   EMU_KEY        EMU_BMODE
//                   (0xD00)	     (0xD01)
//      ---------------------------------------
//      Wait		 !=0x55AA        X
//      I/O		     0x55AA	         0x0000
//      SCI		     0x55AA	         0x0001
//      Wait 	     0x55AA	         0x0002
//      Get_Mode	 0x55AA	         0x0003
//      SPI		     0x55AA	         0x0004
//      I2C		     0x55AA	         0x0005
//      OTP		     0x55AA	         0x0006
//      Wait		 0x55AA	         0x0007
//      Wait		 0x55AA	         0x0008
//      SARAM		 0x55AA	         0x000A	  <-- "Boot to SARAM"
//      Flash		 0x55AA	         0x000B
//	    Wait		 0x55AA          Other
//
//   Write EMU_KEY to 0xD00 and EMU_BMODE to 0xD01 via the debugger
//   according to the Boot Mode Table above. Build/Load project,
//   Reset the device, and Run example
//
//   $End_Boot_Table
//
// DESCRIPTION:
//
//    For most applications, the hardware prioritization of the
//    the PIE module is sufficient.  For applications that need custom
//    prioritization, this example illustrates an example of
//    how this can be done through software.
//
//    For more information on F2802x interrupt priorities, refer to the
//    f2802x-FRM-EX-UG.pdf file included with the f2802x/doc directory.
//
//    This program simulates interrupt conflicts by writing to the
//    PIEIFR registers.  This will simulate multiple interrupts coming into
//    the PIE block at the same time.
//
//    The interrupt service routine routines are software prioritized
//    by the table found in the f2802x_SWPrioritizedIsrLevels.h file.
//
//       1) Before compiling you must set the Global and Group interrupt
//          priorities in the f2802x_SWPrioritizedIsrLevels.h file.
//
//       2) Set the #define CASE directive at the top of the code in this file
//          to determine which test case to run
//
//       3) Compile the code, load, and run
//
//       4) At the end of each test there is a hard coded breakpoint (ESTOP0).
//          When code stops at the breakpoint, examine the ISRTrace buffer to
//          see the order in which the ISR's completed. All PIE interrupts will
//          add to the ISRTrace.
//
//          The ISRTrace will consist of a list of hex values as shown:
//
//              0x00wx    <- PIE Group w interrupt x finished first
//              0x00yz    <- PIE Group y interrupt z finished next
//
//       5) If desired, set a new set of Global and Group interrupt priorities
//          and repeat the test to see the change.
//
//
//       Watch Variables:
//                ISRTrace[50]           Trace of ISR's in the order they
//                                       complete.
//                                       After each test, examine this buffer
//                                       to determine if the ISR's completed in
//                                       the order desired.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "f2802x_swprioritizedisrlevels.h"

//
// Defines
//
#define CASE 1

//
// Define whichs interrupts are used in the PIE for each group.
//
#define ISRS_GROUP1  (M_INT1|M_INT2|M_INT4|M_INT5|M_INT6|M_INT7|M_INT8)
#define ISRS_GROUP2  (M_INT1|M_INT2|M_INT3|M_INT4)
#define ISRS_GROUP3  (M_INT1|M_INT2|M_INT3|M_INT4)
#define ISRS_GROUP4  (M_INT1)
#define ISRS_GROUP6  (M_INT1|M_INT2)
#define ISRS_GROUP8  (M_INT1|M_INT2)
#define ISRS_GROUP9  (M_INT1|M_INT2)

//
// If M_INT1,M_INT2 are available in Group 10, delete them in Group 1
//
#define ISRS_GROUP10 (M_INT3|M_INT4|M_INT5|M_INT6|M_INT7|M_INT8)
#define ISRS_GROUP12 (M_INT1)

//
// This array will be used as a trace to check the order that the
// interrupts were serviced
//
uint16_t  ISRTrace[50];
uint16_t  ISRTraceIndex;  // used to update an element in the trace buffer

//
// Main
//
void main(void)
{
    uint16_t i;

    //
    // WARNING: Always ensure you call memcpy before running any functions from
    // RAM InitSysCtrl includes a call to a RAM based function and without a
    // call to memcpy first, the processor will go "into the weeds"
    //
#ifdef _FLASH
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the f2802x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the f2802x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    //InitGpio();  // Skipped for this example

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the f2802x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in f2802x_DefaultIsr.c.
    // This function is found in f2802x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Step 4. Initialize all the Device Peripherals:
    // Not required for this example
    //

    //
    // Step 5. User specific code, enable interrupts
    //

    //
    // CASE 1
    //
#if (CASE==1)
    //
    // Force all group 1 interrupts at once by writing to the PIEIFR1 register
    //

    //
    // Prepare for the test. Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
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
    EINT;                   // Enable Global interrupt INTM

    //
    // Wait for all Group 1 interrupts to be serviced
    //
    while(PieCtrlRegs.PIEIFR1.all != 0x0000 )
    {
        
    }

    //
    // Stop here and check the ISRTrace to determine which order the
    // ISR Routines completed.  The order is dependant on the priority
    // assigned in the f2802x_SWPrioritizedIsrLevels.h file
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
    // CASE 2
    //
#elif (CASE==2)
    //
    // Force all group 2 interrupts at once by writing to the PIEIFR2 register
    //

    //
    // Prepare for the test. Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
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
    while(PieCtrlRegs.PIEIFR2.all != 0x0000 )
    {
        
    }

    //
    // Stop here and check the order the ISR's were serviced in the
    // ISRTrace
    //
    __asm("        ESTOP0");

    //
    // CASE 3
    //
#elif (CASE==3)
    //
    // Force all group 3 interrupts at once by writing to the PIEIFR3 register
    //

    //
    // Prepare for the test. Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
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
    while(PieCtrlRegs.PIEIFR3.all != 0x0000 )
    {
        
    }

    //
    // Stop here and check the order the ISR's were serviced in the
    // ISRTrace
    //
    __asm("        ESTOP0");

    //
    // CASE 4
    //
#elif (CASE==4)
    //
    // Force all group 4 interrupts at once by writing to the PIEIFR4 register
    //

    //
    // Prepare for the test. Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
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
    // Make sure PIEACK for group 3 is clear (default after reset)
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
    while(PieCtrlRegs.PIEIFR4.all != 0x0000 )
    {
        
    }

    //
    // Stop here and check the order the ISR's were serviced in the
    // ISRTrace
    //
    __asm("        ESTOP0");

    //
    // CASE 5
    //
#elif (CASE==5)
    //
    // Force all group 6 interrupts at once by writing to the PIEIFR6 register
    //

    //
    // Prepare for the test. Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
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
    while(PieCtrlRegs.PIEIFR6.all != 0x0000 )
    {
        
    }

    //
    // Stop here and check the order the ISR's were serviced in the
    // ISRTrace
    //
    __asm("        ESTOP0");

    //
    // CASE 6
    //
#elif (CASE==6)
    //
    // Force all group 9 interrupts at once by writing to the PIEIFR4 register
    //

    //
    // Prepare for the test. Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
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
    while(PieCtrlRegs.PIEIFR9.all != 0x0000 )
    {
        
    }

    //
    // Stop here and check the order the ISR's were serviced in the
    // ISRTrace
    //
    __asm("        ESTOP0");

    //
    // CASE 7
    //
#elif (CASE==7)
    //
    // Force all group 1 and group 2 interrupts at once
    //

    //
    // Setup next test - fire interrupts from Group 1 and Group 2
    //

    //
    // Prepare for the test. Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
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
    PieCtrlRegs.PIEACK.all = (M_INT3 | M_INT2);

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
          PieCtrlRegs.PIEIFR2.all != 0x0000 )
    {
        
    }

    //
    // Check the ISRTrace to determine which order the ISR Routines completed
    //
    __asm("        ESTOP0");

    //
    // CASE 8
    //
#elif (CASE==8)
    //
    // Force all group 1 and group 2 and group 3 interrupts at once
    //

    //
    // Prepare for the test. Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
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
    PieCtrlRegs.PIEACK.all = (M_INT3|M_INT2|M_INT3);

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
    // Wait for all group 1 and group 2 and group 3 interrupts to be serviced
    //
    while(PieCtrlRegs.PIEIFR1.all != 0x0000 || 
          PieCtrlRegs.PIEIFR2.all != 0x0000 || 
          PieCtrlRegs.PIEIFR3.all != 0x0000 )
    {
        
    }

    //
    // Check the ISRTrace to determine which order the ISR Routines completed
    //
    __asm("        ESTOP0");

    //
    // CASE 9
    //
#elif (CASE==9)
    //
    // Force all used PIE interrupts at once
    //

    //
    // Prepare for the test. Disable interrupts
    // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
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
    // Make sure PIEACK for group 1, 2, 3, 4, 6, 8, 9, 10, and 12 are clear 
    // (default after reset)
    //
    PieCtrlRegs.PIEACK.all = (M_INT1|M_INT2|M_INT3|M_INT4|M_INT6|M_INT8|M_INT9|
                              M_INT10|M_INT12);

    //
    // Enable CPU INT1, INT2, INT3, INT4, INT6, INT8, INT9, INT10, and INT12
    //
    IER |= (M_INT1|M_INT2|M_INT3|M_INT4|M_INT6|M_INT8|M_INT9|M_INT10|M_INT12);

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
          PieCtrlRegs.PIEIFR12.all!= 0x0000)
    {
        
    }
    
    //
    // Check the ISRTrace to determine which order the ISR Routines completed
    //
    __asm("        ESTOP0");
#endif
}

//
// End of File
//

