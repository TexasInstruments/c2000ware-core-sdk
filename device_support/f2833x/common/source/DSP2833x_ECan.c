// TI File $Revision: /main/8 $
// Checkin $Date: June 25, 2008   15:19:07 $
//###########################################################################
//
// FILE:	DSP2833x_ECan.c
//
// TITLE:	DSP2833x Enhanced CAN Initialization & Support Functions.
//
//###########################################################################
// $TI Release: 2833x/2823x Header Files V1.32 $
// $Release Date: June 28, 2010 $
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
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

//
// InitECan - This function initializes the eCAN module to a known state.
//
void 
InitECan(void)
{
    InitECana();
#if DSP28_ECANB
    InitECanb();
#endif // if DSP28_ECANB
}

//
// InitECana - Initialize eCAN-A module
//
void 
InitECana(void)
{
    //
    // Create a shadow register structure for the CAN control registers. This 
    // is needed, since only 32-bit access is allowed to these registers. 
    // 16-bit access to these registers could potentially corrupt the register
    // contents or return false data. This is especially true while writing 
    // to/reading from a bit (or group of bits) among bits 16 - 31
    //
    struct ECAN_REGS ECanaShadow;

    EALLOW;		// EALLOW enables access to protected bits

    //
    // Configure eCAN RX and TX pins for CAN operation using eCAN regs
    //
    ECanaShadow.CANTIOC.all = ECanaRegs.CANTIOC.all;
    ECanaShadow.CANTIOC.bit.TXFUNC = 1;
    ECanaRegs.CANTIOC.all = ECanaShadow.CANTIOC.all;

    ECanaShadow.CANRIOC.all = ECanaRegs.CANRIOC.all;
    ECanaShadow.CANRIOC.bit.RXFUNC = 1;
    ECanaRegs.CANRIOC.all = ECanaShadow.CANRIOC.all;

    //
    // Configure eCAN for HECC mode - (reqd to access mailboxes 16 thru 31)
    // HECC mode also enables time-stamping feature
    //
    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
    ECanaShadow.CANMC.bit.SCB = 1;
    ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

    //
    // Initialize all bits of 'Master Control Field' to zero
    // Some bits of MSGCTRL register come up in an unknown state. For proper 
    // operation, all bits (including reserved bits) of MSGCTRL must be 
    // initialized to zero
    //
    ECanaMboxes.MBOX0.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX1.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX2.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX3.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX4.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX5.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX6.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX7.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX8.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX9.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX10.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX11.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX12.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX13.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX14.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX15.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX16.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX17.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX18.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX19.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX20.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX21.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX22.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX23.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX24.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX25.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX26.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX27.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX28.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX29.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX30.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX31.MSGCTRL.all = 0x00000000;

    //
    // TAn, RMPn, GIFn bits are all zero upon reset and are cleared again
    // as a matter of precaution.
    //
    ECanaRegs.CANTA.all	= 0xFFFFFFFF;       // Clear all TAn bits

    ECanaRegs.CANRMP.all = 0xFFFFFFFF;      // Clear all RMPn bits

    ECanaRegs.CANGIF0.all = 0xFFFFFFFF;     // Clear all interrupt flag bits
    ECanaRegs.CANGIF1.all = 0xFFFFFFFF;

    //
    // Configure bit timing parameters for eCANA
    //
    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
    ECanaShadow.CANMC.bit.CCR = 1 ;            // Set CCR = 1
    ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

    ECanaShadow.CANES.all = ECanaRegs.CANES.all;

    do
    {
        ECanaShadow.CANES.all = ECanaRegs.CANES.all;
    } while(ECanaShadow.CANES.bit.CCE != 1 );  	// Wait for CCE bit to be set

    ECanaShadow.CANBTC.all = 0;

    //
    // CPU_FRQ_150MHz is defined in DSP2833x_Examples.h
    //
    #if (CPU_FRQ_150MHZ)
    //
    // The following block for all 150 MHz SYSCLKOUT 
    // (75 MHz CAN clock) - default. Bit rate = 1 Mbps See Note at End of File
    //
    ECanaShadow.CANBTC.bit.BRPREG = 4;
    ECanaShadow.CANBTC.bit.TSEG2REG = 2;
    ECanaShadow.CANBTC.bit.TSEG1REG = 10;
    #endif
    
    //
    // CPU_FRQ_100MHz is defined in DSP2833x_Examples.h
    //
    #if (CPU_FRQ_100MHZ)
    //
    // The following block is only for 100 MHz SYSCLKOUT (50 MHz CAN clock). 
    // Bit rate = 1 Mbps See Note at End of File
    //
    ECanaShadow.CANBTC.bit.BRPREG = 4;
    ECanaShadow.CANBTC.bit.TSEG2REG = 1;
    ECanaShadow.CANBTC.bit.TSEG1REG = 6;
    #endif

    ECanaShadow.CANBTC.bit.SAM = 1;
    ECanaRegs.CANBTC.all = ECanaShadow.CANBTC.all;

    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
    ECanaShadow.CANMC.bit.CCR = 0 ;            // Set CCR = 0
    ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

    ECanaShadow.CANES.all = ECanaRegs.CANES.all;

    do
    {
        ECanaShadow.CANES.all = ECanaRegs.CANES.all;
    } while(ECanaShadow.CANES.bit.CCE != 0 );// Wait for CCE bit to be  cleared

    //
    // Disable all Mailboxes
    //
    ECanaRegs.CANME.all = 0;		// Required before writing the MSGIDs

    EDIS;
}

#if (DSP28_ECANB)
//
// Initialize eCAN-B module
//
void 
InitECanb(void)
{
    //
    // Create a shadow register structure for the CAN control registers. This 
    // is needed, since only 32-bit access is allowed to these registers. 
    // 16-bit access to these registers could potentially corrupt the register 
    // contents or return false data. This is especially true while writing 
    // to/reading from a bit (or group of bits) among bits 16 - 31
    //
    struct ECAN_REGS ECanbShadow;

    EALLOW;		// EALLOW enables access to protected bits

    //
    // Configure eCAN RX and TX pins for CAN operation using eCAN regs
    //
    ECanbShadow.CANTIOC.all = ECanbRegs.CANTIOC.all;
    ECanbShadow.CANTIOC.bit.TXFUNC = 1;
    ECanbRegs.CANTIOC.all = ECanbShadow.CANTIOC.all;

    ECanbShadow.CANRIOC.all = ECanbRegs.CANRIOC.all;
    ECanbShadow.CANRIOC.bit.RXFUNC = 1;
    ECanbRegs.CANRIOC.all = ECanbShadow.CANRIOC.all;

    //
    // Configure eCAN for HECC mode - (read to access mailboxes 16 thru 31)
    //
    ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;
    ECanbShadow.CANMC.bit.SCB = 1;
    ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;

    //
    // Initialize all bits of 'Master Control Field' to zero
    // Some bits of MSGCTRL register come up in an unknown state. For proper 
    // operation, all bits (including reserved bits) of MSGCTRL must be 
    // initialized to zero
    //
    ECanbMboxes.MBOX0.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX1.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX2.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX3.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX4.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX5.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX6.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX7.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX8.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX9.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX10.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX11.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX12.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX13.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX14.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX15.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX16.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX17.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX18.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX19.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX20.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX21.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX22.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX23.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX24.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX25.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX26.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX27.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX28.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX29.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX30.MSGCTRL.all = 0x00000000;
    ECanbMboxes.MBOX31.MSGCTRL.all = 0x00000000;

    //
    // TAn, RMPn, GIFn bits are all zero upon reset and are cleared again
    // as a matter of precaution.
    //
    ECanbRegs.CANTA.all	= 0xFFFFFFFF;	// Clear all TAn bits

    ECanbRegs.CANRMP.all = 0xFFFFFFFF;	// Clear all RMPn bits

    ECanbRegs.CANGIF0.all = 0xFFFFFFFF;	// Clear all interrupt flag bits
    ECanbRegs.CANGIF1.all = 0xFFFFFFFF;

    //
    // Configure bit timing parameters for eCANB
    //
    ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;
    ECanbShadow.CANMC.bit.CCR = 1 ;            // Set CCR = 1
    ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;

    ECanbShadow.CANES.all = ECanbRegs.CANES.all;

    do
    {
        ECanbShadow.CANES.all = ECanbRegs.CANES.all;
    } while(ECanbShadow.CANES.bit.CCE != 1); // Wait for CCE bit to be  cleared

    ECanbShadow.CANBTC.all = 0;

    //
    // CPU_FRQ_150MHz is defined in DSP2833x_Examples.h
    //
    #if (CPU_FRQ_150MHZ)
    //
    // The following block for all 150 MHz SYSCLKOUT 
    // (75 MHz CAN clock) - default. Bit rate = 1 Mbps See Note at end of file
    //
    ECanbShadow.CANBTC.bit.BRPREG = 4;
    ECanbShadow.CANBTC.bit.TSEG2REG = 2;
    ECanbShadow.CANBTC.bit.TSEG1REG = 10;
    #endif
    
    //
    // CPU_FRQ_100MHz is defined in DSP2833x_Examples.h
    //
    #if (CPU_FRQ_100MHZ)
    //
    // The following block is only for 100 MHz SYSCLKOUT (50 MHz CAN clock).
    // Bit rate = 1 Mbps  See Note at end of file
    //
    ECanbShadow.CANBTC.bit.BRPREG = 4;
    ECanbShadow.CANBTC.bit.TSEG2REG = 1;
    ECanbShadow.CANBTC.bit.TSEG1REG = 6;
    #endif

    ECanbShadow.CANBTC.bit.SAM = 1;
    ECanbRegs.CANBTC.all = ECanbShadow.CANBTC.all;

    ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;
    ECanbShadow.CANMC.bit.CCR = 0 ;            // Set CCR = 0
    ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;

    ECanbShadow.CANES.all = ECanbRegs.CANES.all;

    do
    {
        ECanbShadow.CANES.all = ECanbRegs.CANES.all;
    } while(ECanbShadow.CANES.bit.CCE != 0 );// Wait for CCE bit to be  cleared

    //
    // Disable all Mailboxes
    //
    ECanbRegs.CANME.all = 0;		// Required before writing the MSGIDs

    EDIS;
}
#endif // if DSP28_ECANB

//
// InitECanGpio - This function initializes GPIO pins to function as eCAN pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// Only one GPIO pin should be enabled for CANTXA/B operation.
// Only one GPIO pin shoudl be enabled for CANRXA/B operation.
// Comment out other unwanted lines.
//
void 
InitECanGpio(void)
{
    InitECanaGpio();
#if (DSP28_ECANB)
    InitECanbGpio();
#endif // if DSP28_ECANB
}

//
// InitECanaGpio - This function initializes GPIO pins to function as eCAN- A
//
void 
InitECanaGpio(void)
{
    EALLOW;

    //
    // Enable internal pull-up for the selected CAN pins
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO30 = 0;	  // Enable pull-up for GPIO30 (CANRXA)
    //GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0; // Enable pull-up for GPIO18 (CANRXA)

    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;	 //Enable pull-up for GPIO31 (CANTXA)
    //GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;  //Enable pull-up for GPIO19 (CANTXA)

    //
    // Set qualification for selected CAN pins to asynch only
    // Inputs are synchronized to SYSCLKOUT by default.
    // This will select asynch (no qualification) for the selected pins.
    //
    GpioCtrlRegs.GPAQSEL2.bit.GPIO30 = 3;   // Asynch qual for GPIO30 (CANRXA)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3;  // Asynch qual for GPIO18 (CANRXA)

    //
    // Configure eCAN-A pins using GPIO regs
    // This specifies which of the possible GPIO pins will be eCAN functional 
    // pins.
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;	// Configure GPIO30 for CANRXA
    //GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 3;	// Configure GPIO18 for CANRXA
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;	// Configure GPIO31 for CANTXA
    //GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 3;	// Configure GPIO19 for CANTXA

    EDIS;
}

#if (DSP28_ECANB)
//
// InitECanbGpio - This function initializes GPIO pins to function as eCAN-B
//
void 
InitECanbGpio(void)
{
    EALLOW;

    //
    // Enable internal pull-up for the selected CAN pins
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;	  //Enable pull-up for GPIO8 (CANTXB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;   //Enable pull-up for GPIO12(CANTXB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   //Enable pull-up for GPIO16(CANTXB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   //Enable pull-up for GPIO20(CANTXB)

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;	  // Enable pull-up for GPIO10(CANRXB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;  // Enable pull-up for GPIO13(CANRXB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;  // Enable pull-up for GPIO17(CANRXB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;  // Enable pull-up for GPIO21(CANRXB)

    //
    // Set qualification for selected CAN pins to asynch only
    // Inputs are synchronized to SYSCLKOUT by default.
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAQSEL1.bit.GPIO10 = 3; // Asynch qual for GPIO10 (CANRXB)
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3; // Asynch qual for GPIO13 (CANRXB)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch qual for GPIO17 (CANRXB)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 3; // Asynch qual for GPIO21 (CANRXB)

    //
    // Configure eCAN-B pins using GPIO regs
    // This specifies which of the possible GPIO pins will be eCAN functional 
    // pins.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 2;   // Configure GPIO8 for CANTXB 
    //GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 2;  // Configure GPIO12 for CANTXB 
    //GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 2;  // Configure GPIO16 for CANTXB 
    //GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 3;  // Configure GPIO20 for CANTXB 

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 2;  // Configure GPIO10 for CANRXB
    //GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 2;  // Configure GPIO13 for CANRXB
    //GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 2;  // Configure GPIO17 for CANRXB
    //GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 3;  // Configure GPIO21 for CANRXB

    EDIS;
}
#endif // if DSP28_ECANB

//
// Note: Bit timing parameters must be chosen based on the network parameters 
// such as the sampling point desired and the propagation delay of the network.
// The propagation delay is a function of length of the cable, delay introduced
// by the transceivers and opto/galvanic-isolators (if any).
//
// The parameters used in this file must be changed taking into account the 
// above mentioned factors in order to arrive at the bit-timing parameters 
// suitable for a network.
//

//
// End of File
//

