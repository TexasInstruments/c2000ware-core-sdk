//###########################################################################
//
//  FILE:  Example_2803xLinSci_DLB_int.c
//
//  TITLE: LIN-SCI Digital Loop Back Interrupts example
//
//!  \addtogroup f2803x_example_list
//!  <h1>LIN-SCI Digital Loop Back Interrupts (lina_sci_loopback_interrupts)
//!  </h1>
//!
//!  This program uses the internal loop back test mode of the peripheral.
//!  Other then boot mode pin configuration, no other hardware configuration
//!  is required. Interrupts are enabled
//!
//!  A stream of data is sent and then compared to the received stream.
//!  The SCI-A sent data looks like this: \n
//!  00 01 02 03 \n
//!  04 05 06 07 \n
//!  08 09 0A 0B \n
//!  etc.. \n
//!
//!  The pattern is repeated forever.
//!
//!  \b Watch \b Variables \n
//!  - \b sdataA, Data being sent
//!  - \b rdataA, Data received
//!  - \b LinL0IntCount, Number of transmissions received
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Function Prototypes
//
__interrupt void Lina_Level0_ISR(void);
__interrupt void Lina_Level1_ISR(void);
void scia_fifo_init(void);
void PackTxBuffers(void);
void UnpackRxBuffers(void);
void CheckData(void);
void SetupSCI(void);
void error(void);

//
// Globals
//
Uint16 sdataA[4];           // Send data for SCI-A
Uint16 rdataA[4];           // Received data for SCI-A

Uint32 LinL0IntCount;       // Counter for L0 interrupts
Uint32 LinL1IntCount;       // Counter for L0 interrupts

Uint32 LinL0IntVect;        // Vector for L0 interrupts
Uint32 LinL1IntVect;        // Vector for L1interrupts

Uint16 i;			        // Generic iterator

//
// Main
//
void main(void)
{
    //
    // Initialize Variables
    //
    LinL0IntCount = 0;
    LinL0IntVect  = 0;
    LinL1IntCount = 0;
    LinL1IntVect  = 0;

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2803x_SysCtrl.c file.
    //
    InitSysCtrl();

    EALLOW;

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2803x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    // InitGpio();
    // Setup only the GP I/O only for SCI-A and SCI-B functionality
    // This function is found in DSP2803x_Sci.c
	//
    // For this example, this step is not necessary as the example
    // performs a digital loopback. This step is for illustration
    // to initialize the GPIO for SCI.
    //
    InitSciGpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2803x_PieCtrl.c file.
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
    // The shell ISR routines are found in DSP2803x_DefaultIsr.c.
    // This function is found in DSP2803x_PieVect.c.
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;	// This is needed to write to EALLOW protected registers
    PieVectTable.LIN0INTA  = &Lina_Level0_ISR;
    PieVectTable.LIN1INTA  = &Lina_Level1_ISR;
    EDIS;   // This is needed to disable write to EALLOW protected registers

    //
    // Initialize and Enable BLIN SCI module
    //
    SetupSCI();

    // Step 4. Initialize all the Device Peripherals:
    // Not required for this example

    //
    // Step 5. User specific code, enable interrupts:
    //

    // 
    // Init send data.  After each transmission this data
    // will be updated for the next transmission
    //
    for(i = 0; i<4; i++)
    {
        sdataA[i] = i;
    }

    EALLOW;

    //
    // Enable interrupts required for this example
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
    PieCtrlRegs.PIEIER9.bit.INTx3=1;     // PIE Group 9, INT3
    PieCtrlRegs.PIEIER9.bit.INTx4=1;     // PIE Group 9, INT4
    IER = 0x100;	// Enable CPU INT
    EINT;

    //
    // Wait for SCI to be idle and ready for transmission
    //
    while(LinaRegs.SCIFLR.bit.IDLE == 1);

    //
    // Initiate communication by filling LINTD buffers
    //
    PackTxBuffers();

    //
    // Step 6. IDLE loop. Just sit and loop forever (optional):
    //
    for(;;);
}

//
// High priority LIN ISR.
//
__interrupt void Lina_Level0_ISR(void)
{
    //
	// Increment the interrupt counter
    //
	LinL0IntCount++;

    //
	// Read-clear the interrupt vector
    //
	LinL0IntVect = LinaRegs.SCIINTVECT0.all;

    //
	// RXINT
    //
	if(LinL0IntVect == 11)
	{
        //
		// Move data from receive buffers to data arrays
        //
		UnpackRxBuffers();
        
        //
		// Verify data and increment for next transmission
        //
		CheckData();
        
        //
		// Move new data from data array to transmit buffers
        //
		PackTxBuffers();
	}
    
    //
	// Other Interrupt
    //
	else
	{
        //
		// There should not be other interrupts
        //
		error();
	}

    //
	// Acknowledge the PIE to be able to receive more interrupts
    //
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

//
// Lina_Level1_ISR - Lin A ISR
//
__interrupt void 
Lina_Level1_ISR(void)
{
    //
	// Increment the interrupt counter
    //
	LinL1IntCount++;

    //
	// Read-clear the interrupt vector
    //
	LinL1IntVect = LinaRegs.SCIINTVECT1.all;

    //
	// Acknowledge the PIE to be able to receive more interrupts
    //
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

//
// PackTxBuffers - Pack array words into LINTD buffer bytes sending high byte 
// first.
//
void 
PackTxBuffers(void)
{
    LinaRegs.LINTD0.bit.TD0 = sdataA[0] >> 8;
    LinaRegs.LINTD0.bit.TD1 = sdataA[0] &  0x00FF;
    LinaRegs.LINTD0.bit.TD2 = sdataA[1] >> 8;
    LinaRegs.LINTD0.bit.TD3 = sdataA[1] &  0x00FF;
    LinaRegs.LINTD1.bit.TD4 = sdataA[2] >> 8;
    LinaRegs.LINTD1.bit.TD5 = sdataA[2] &  0x00FF;
    LinaRegs.LINTD1.bit.TD6 = sdataA[3] >> 8;
    LinaRegs.LINTD1.bit.TD7 = sdataA[3] &  0x00FF;
}

//
// UnpackRxBuffers - Move data from LINRD buffers to data array.
//
void 
UnpackRxBuffers(void)
{
    Uint32 ReadData;
    ReadData = LinaRegs.LINRD0.all;
    rdataA[0] = (ReadData & 0xFFFF0000) >> 16;
    rdataA[1] = ReadData & 0x0000FFFF;
    ReadData = LinaRegs.LINRD1.all;
    rdataA[2] = (ReadData & 0xFFFF0000) >> 16;
    rdataA[3] = ReadData & 0x0000FFFF;
}

//
// CheckData - Verify correct data transmission and increment test data.
//
void 
CheckData(void)
{
	for(i = 0; i < 4; i++)
	{
		if(sdataA[i] != rdataA[i])
		{
			error();
		}
		sdataA[i] += 4;
	}
}

//
// SetupSCI - 
// 
void 
SetupSCI(void)
{
    // 
    // Allow write to protected registers
    //
    EALLOW;

    LinaRegs.SCIGCR0.bit.RESET = 0;     //Into reset
    LinaRegs.SCIGCR0.bit.RESET = 1;     //Out of reset

    LinaRegs.SCIGCR1.bit.SWnRST = 0;    //Into software reset

    //
    // SCI Configurations
    //
    LinaRegs.SCIGCR1.bit.COMMMODE = 0;   //Idle-Line Mode
    LinaRegs.SCIGCR1.bit.TIMINGMODE = 1; //Asynchronous Timing
    LinaRegs.SCIGCR1.bit.PARITYENA = 0;  //No Parity Check
    LinaRegs.SCIGCR1.bit.PARITY = 0;	 //Odd Parity
    LinaRegs.SCIGCR1.bit.STOP = 0;		 //One Stop Bit
    LinaRegs.SCIGCR1.bit.CLK_MASTER = 1; //Enable SCI Clock
    LinaRegs.SCIGCR1.bit.LINMODE = 0;	 //SCI Mode
    LinaRegs.SCIGCR1.bit.SLEEP = 0;      //Ensure Out of Sleep
    LinaRegs.SCIGCR1.bit.MBUFMODE = 1;	 //Buffered Mode
    LinaRegs.SCIGCR1.bit.LOOPBACK = 1;   //Internal Loopback
    LinaRegs.SCIGCR1.bit.CONT = 1;		 //Continue on Suspend
    LinaRegs.SCIGCR1.bit.RXENA = 1;		 //Enable RX
    LinaRegs.SCIGCR1.bit.TXENA = 1;		 //Enable TX

    //
    // Ensure IODFT is disabled
    // 
    LinaRegs.IODFTCTRL.bit.IODFTENA = 0x0;

    //
    // Set transmission length
    //
    LinaRegs.SCIFORMAT.bit.CHAR = 7;	 //Eight bits
    LinaRegs.SCIFORMAT.bit.LENGTH = 7;   //Eight bytes

    //
    // Set baudrate
    //
    LinaRegs.BRSR.bit.SCI_LIN_PSL = 96;	 //19.2 kbps for SYSCLKOUT = 60 MHz
    LinaRegs.BRSR.bit.M = 10;

    //
    // Enable interrupts
    //
    LinaRegs.SCISETINT.bit.SETRXINT = 1; //Enable RX interrupt
    
    //
    // Set interrupt priority
    // Set interrupt level of all interrupts to LVL 0
    //
    LinaRegs.SCICLEARINTLVL.all = 0xFFFFFFFF; 

    LinaRegs.SCIGCR1.bit.SWnRST = 1;  //bring out of software reset

    //
    // Disable write to protected registers
    //
    EDIS;
}

//
// error- Error checking function
//
void 
error(void)
{
    __asm("     ESTOP0");       // Test failed!! Stop!
    for (;;);
}

//
// End of File
//

