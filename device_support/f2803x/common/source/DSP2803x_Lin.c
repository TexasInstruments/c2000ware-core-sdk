//###########################################################################
//
// FILE:	DSP2803x_Lin.c
//
// TITLE:	DSP2803x LIN Initialization & Support Functions.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
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
#include "DSP2803x_Device.h"
#include "DSP2803x_Examples.h"

//
// InitLin - This function initializes the LIN to a known state.
//
void 
InitLin(void)
{
    InitLina();
}

//
// InitLina -  This function initializes the LIN to LINA
//
void 
InitLina(void)
{
    EALLOW;

    //
    // Initialize LIN
    //
    
    //
    // Reset module and release reset.
    //
    LinaRegs.SCIGCR0.bit.RESET = 0;
    LinaRegs.SCIGCR0.bit.RESET = 1;

    //
    // LIN into software reset mode
    //
    LinaRegs.SCIGCR1.bit.SWnRST = 0;

    //
    // Select LIN Mode
    //
    LinaRegs.SCIGCR1.bit.LINMODE = 1;

    //
    // Configure LIN mode
    //
    LinaRegs.SCIGCR1.bit.CLK_MASTER = 1; 	// 1-->Master, 0-->Slave
    LinaRegs.SCIGCR1.bit.ADAPT = 0; 	// Fixed baud rate
    LinaRegs.SCIGCR1.bit.COMMMODE= 0;   // ID bits 4,5 not used for length control
    LinaRegs.SCIGCR1.bit.CONT = 1; 		// Continue on Emulation suspend
    LinaRegs.SCIGCR1.bit.CTYPE = 1; 	// LIN 2.0 Enhanced checksum used
    
    //
    // ID match vs LinaRegs.bit.IDSLAVETASKBYTE
    //
    LinaRegs.SCIGCR1.bit.HGENCTRL = 1; 	
    
    LinaRegs.SCIGCR1.bit.LOOPBACK = 0; 	// External communication mode
    LinaRegs.SCIGCR1.bit.MBUFMODE = 1; 	// Buffered mode
    LinaRegs.SCIGCR1.bit.PARITYENA = 1; // Check received ID for parity
    LinaRegs.SCIGCR1.bit.RXENA = 1; 	// Enable RX pin
    LinaRegs.SCIGCR1.bit.TXENA = 1; 	// Enable TX pin

    //
    // More LIN configs
    //
    LinaRegs.SCIGCR2.bit.CC = 1; 			// Validate checksum

    //
    // Set all interrupts to disabled
    //
    LinaRegs.SCICLEARINT.all 		= 0xFFFFFFFF;

    //
    // Baud Rate Settings - 60MHz device
    //
    LinaRegs.BRSR.bit.SCI_LIN_PSL = 96; 	// 19.2 kbps
    LinaRegs.BRSR.bit.M = 11;
    LinaRegs.MBRSR = 92;                    // 20kHz (max autobaud rate)

    //
    // LIN Character Size and Length
    //
    LinaRegs.SCIFORMAT.bit.LENGTH 	= 0; 	// 8 bit transmission/response

    //
    // SYNC Field Configuration
    //
    LinaRegs.LINCOMP.bit.SBREAK = 5; 	// Sync break is 13 + 5 = 18 Tbits
    LinaRegs.LINCOMP.bit.SDEL = 3; 		// Sync delimiter is 1 + 3 = 4 Tbits

    //
    // LIN MASK Configuartion
    //
    LinaRegs.LINMASK.bit.TXIDMASK = 0xFF; 	// Mask ID so TX match will happen
    LinaRegs.LINMASK.bit.RXIDMASK = 0xFF; 	// Mask ID so RX match will happen

    //
    // IODFT Configuarations
    //
    LinaRegs.IODFTCTRL.bit.IODFTENA = 0x0; 	// IODFT testing module disabled
    LinaRegs.IODFTCTRL.bit.LPBENA 	 = 0; 	// IODFT loopback disabled

    //
    // Release	SCI from software reset state - End of Config
    //
    LinaRegs.SCIGCR1.bit.SWnRST = 1;

    EDIS;
}

//
// GenIdParity - This function generates the ID parity bits and appends
// them to the ID. Call this function on a desired ID before header
// generation in master mode when LinaRegs.SCIGCR1.bit.PARITYENA is set.
//
Uint16 P0;
Uint16 P1;

Uint16 
GenIdParity(Uint16 id)
{
	P0 =  ((id << 6) ^ (id << 5) ^ (id << 4) ^ (id << 2)) & BIT6;
	P1 = (((id << 6) ^ (id << 4) ^ (id << 3) ^ (id << 2)) & BIT7) ^ BIT7;
	return id | P0 | P1;
}

//
// InitLinGpio - This function initializes GPIO pins to function as LIN pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// Only one GPIO pin should be enabled for LIN TX operation.
// Only one GPIO pin shoudl be enabled for LIN RX operation.
// Comment out other unwanted lines.
//
void 
InitLinGpio()
{
    InitLinaGpio();
}

//
// InitLinaGpio - function initializes GPIO pins to function as LINA
//
void 
InitLinaGpio()
{
    EALLOW;

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;	// Enable pull-up for GPIO9(LIN TX)
    //GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;  // Enable pull-up for GPIO14(LIN TX)
    //GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;  // Enable pull-up for GPIO18(LIN TX)
    //GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;  // Enable pull-up for GPIO22(LIN TX)

    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;	// Enable pull-up for GPIO11 (LIN RX)
    //GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0; // Enable pull-up for GPIO15 (LIN RX)
    //GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0; // Enable pull-up for GPIO19 (LIN RX)
    //GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0; // Enable pull-up for GPIO23 (LIN RX)

    //
    // Set qualification for selected pins to asynch only
    // Inputs are synchronized to SYSCLKOUT by default.
    // This will select asynch (no qualification) for the selected pins.
    //
    GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 3;  // Asynch input GPIO11 (LINRXA)
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  // Asynch input GPIO15 (LINRXA)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;  // Asynch input GPIO19 (LINRXA)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;  // Asynch input GPIO23 (LINRXA)

    //
    // Configure LIN-A pins using GPIO regs
    // This specifies which of the possible GPIO pins will be LIN pins.
    // Only one set of pins should be enabled at any time for LIN operation.
    // (2-Enable,0-Disable)
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 2;    //Setup GPIO9 for LIN TX operation 
    //GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 2; //Setup GPIO14 for LIN TX operation
    //GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2; //Setup GPIO18 for LIN TX operation
    //GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3; //Setup GPIO19 for LIN TX operation

    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 2;   //Setup GPIO11 for LIN RX operation
    //GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 2; //Setup GPIO15 for LIN RX operation
    //GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2; //Setup GPIO19 for LIN RX operation
    //GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 3; //Setup GPIO23 for LIN RX operation
    
    EDIS;
}

//
// End of file
//

