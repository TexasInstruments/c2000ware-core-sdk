//###########################################################################
//
//  FILE:  Example_2803xLina_EXALB.c
//
//  TITLE: LIN-A External Analog Loop Back example
//
//!  \addtogroup f2803x_example_list
//!  <h1>LIN-A External Analog Loop Back(lina_external_loopback)</h1>
//!
//!  This program is intended to validate the analog loopback
//!  functionality of the LIN module.
//!
//!  The code configures the LIN module and then transmits data onto the
//!  LIN bus.  The LIN module receives this data off the LIN bus.
//!  Correct data transmission is verified.
//!
//!  \note The LIN pins should be connected to a LIN transceiver.
//!
//!  \b Watch \b Variables \n
//!  - Rx_Data_LIN_MASTER
//!  - Tx_Data_LIN_MASTER
//!  - intCount
//!  - pstatus
//!  - error
//!  - Int_Flag
//!  - int0Count
//!  - int1Count
//!
//!  \b External \b Connections \n
//!  Connect the LIN module TXD and RXD pins to a LIN transceiver
//!  board in order to achieve analog loopback.
//!  - GPIO9 is LIN-TX
//!  - GPIO11 is LIN-RX
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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
// Globals
//
Uint32 pstatus=1;
Uint32 error=1;
Uint32 Int_Flag;

//
// Holds the final interrupt count from either of the interrupts
//
Uint32 intCount = 0;

Uint32 int0Count = 0;   // Set the interrupt count to 0
Uint32 int1Count = 0;   // Set the interrupt count to 0
Uint32 iter=0;
Uint32 Delay_val=100;
Uint32 Tx_Data_LIN_MASTER[16];
Uint32 Rx_Data_LIN_MASTER[16];
Uint32 intVector0;
Uint32 intVector1;

//
// Defines
//
#define INTEN_Config 0x2200     // IDINT | RXINT
#define RXID_MASK	0x0A
#define TXID_MASK	0x0A
#define LIN_ID		0x3A
#define LINIDNUM_Slave 0x30
#define RESP_LENGTH	0x7

//
// Function Prototypes
//
__interrupt void LINa_Lvl0_Isr(void);
__interrupt void LINa_Lvl1_Isr(void);

//
// Main
//
void main()
{
    Uint32 i;

    //
    // Initialize sent and received data pointers
    //
    Uint32 * Tx_DataPtr = &Tx_Data_LIN_MASTER[0];
    Uint32 * Rx_DataPtr = &Rx_Data_LIN_MASTER[0];

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2803x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2803x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    // InitGpio();
    // Setup only the GP I/O only for SCI-A and SCI-B functionality
    // This function is found in DSP2803x_Lin.c
    //
    InitLinaGpio();	// Initializes the appropriate pins for LIN operation

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
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.LIN0INTA = &LINa_Lvl0_Isr;
    PieVectTable.LIN1INTA = &LINa_Lvl1_Isr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    // Not required for this example
    //

    //
    // Initialize the data to send
    //
    for(i=0;i<16;i++)
    {
        Tx_Data_LIN_MASTER[i] = (((0x1111)*i + 0x1111)-0x1111);
        Rx_Data_LIN_MASTER[i] = 0;
    }

    //
    // Step 5. User specific code, enable interrupts:
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;    // Enable the PIE block
    PieCtrlRegs.PIEIER9.bit.INTx3 = 1;    // PIE Group 9, INT3
    PieCtrlRegs.PIEIER9.bit.INTx4 = 1;    // PIE Group 9, INT4
    IER = 0x100;    // Enable CPU INT
    EINT;

    //
    // Clear the interrupt flag
    //
    Int_Flag = 0;

    //
    // LIN Configuration
    //

    EALLOW;

    //
    // Perform initial configuration for LIN
    //
    InitLina();

    //
    // LIN into software reset mode
    //
    LinaRegs.SCIGCR1.bit.SWnRST = 0;

    //
    // Do LIN MODE Configurations
    //
    LinaRegs.SCIGCR1.bit.PARITYENA = 0;

    //
    // Enable Interrupt and Interrupt Levels
    //
    LinaRegs.SCISETINT.all      = INTEN_Config;     //IDINT | RXINT

    //
    // Set interrupt priority - comment as appropriate
    //

    //
    // Interrupt asserted in INT1
    //
    // LinaRegs.SCISETINTLVL.all    = 0xFFFFFFFF;
    
    //
    // Interrupt asserted in INT0
    //
    LinaRegs.SCICLEARINTLVL.all = 0xFFFFFFFF;

    //
    // LIN MASK Configuration 2
    //
    LinaRegs.LINMASK.bit.RXIDMASK = RXID_MASK;	// 0xA
    LinaRegs.LINMASK.bit.TXIDMASK = TXID_MASK;	// 0xA

    //
    // Initialize the Slave LINIDNUM register
    //
    LinaRegs.LINID.bit.IDSLAVETASKBYTE = LINIDNUM_Slave;    // 0x30

    //
    // Release	SCI from software reset state - End of Config
    //
    LinaRegs.SCIGCR1.bit.SWnRST = 1;

    //
    // LIN Response Length
    //
    LinaRegs.SCIFORMAT.bit.LENGTH = RESP_LENGTH;

    for(i=0;i<8;i++)
    {
        //
        // Transmit Data - This populates the LIN transmit
        // buffers - no data is actually sent yet.
        //
        LinaRegs.LINTD0.all = *Tx_DataPtr++;
        LinaRegs.LINTD1.all = *Tx_DataPtr++;

        //
        // Send ID by writing to LINIDNUM register
        // This causes the ID to be written to the bus.  In turn,
        // this causes both TX and RX ID matches in the slave task
        // to occur - causing the data in the transmit buffers to
        // be placed on the bus and also read into the receive buffers
        //
        LinaRegs.LINID.bit.IDBYTE = LIN_ID;	        // 0x3A

        //
        // This is waiting for an ID match to occur
        //
        while(Int_Flag != 4)
        {
            
        }
        Int_Flag = 0;
        
        //
        // This is waiting for a data reception match to occur
        //
        while(Int_Flag != 11)
        {
            
        }
        Int_Flag = 0;

        //
        // Delay to make sure all activity is finished on the bus
        //
        for(iter = 0; iter < 50; iter++)
        {
            
        }

        //
        // Transfer data from receive data buffers to data arrays
        //
        *Rx_DataPtr++ = LinaRegs.LINRD0.all;
        *Rx_DataPtr++ = LinaRegs.LINRD1.all;
    }

    //
    // Validate test
    //
    error = 0;

    //
    // Check for the Valid data reception
    //
    Tx_DataPtr = &Tx_Data_LIN_MASTER[0];
    Rx_DataPtr = &Rx_Data_LIN_MASTER[0];
    for(i=0; i<16; i++)
    {
        if( (*Rx_DataPtr++ != *Tx_DataPtr++) )
        {
            error |= 1;
        }
    }

    //
    // Validate correct interrupt occurrence
    //
    if(intCount != 16)
    {
        error |= 2;
    }

    if (error == 0)
    {
        //
        // Pass
        //
        pstatus=1;
    }
    
    else
    {
        //
        // Fail
        //
        pstatus=0;
    }
}

//
// LINa_Lvl0_Isr - High priority LIN0 ISR
//
__interrupt void 
LINa_Lvl0_Isr(void)
{
    //
	// Increment the interrupt count
    //
	int0Count++;
	EALLOW;

    //
	// Read the high priority interrupt vector. This clears the interrupt flag
    //
	intVector0 = LinaRegs.SCIINTVECT0.all;

    //
    // Code for ID interrupt
    //
	if(intVector0 == 4) 
	{
		Int_Flag = 4;
	}
    
    //
    // Code for RX interrupt
    //
	else if(intVector0 == 11)
	{
		Int_Flag = 11;
	}
    
    //
	// Acknowledge the interrupt for the PIE module
    //
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
	intCount = int0Count;
}

//
// LINa_Lvl1_Isr - Low priority LIN1 ISR.
//
__interrupt void 
LINa_Lvl1_Isr(void)
{
    //
    // Increment the interrupt count
    //
	int1Count++;
	EALLOW;

    //
	// Read the low priority interrupt vector. This clears the interrupt flag
    //
	intVector1 = LinaRegs.SCIINTVECT1.all;

    //
    // Code for ID interrupt
    //
	if(intVector1 == 4) 
	{
		Int_Flag = 4;
	}
    
    //
    // Code for RX interrupt
    //
	else if(intVector1 == 11)
	{
		Int_Flag = 11;
	}

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
	intCount = int1Count;
}

//
// End of File
//

