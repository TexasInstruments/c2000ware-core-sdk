//###########################################################################
//
// FILE:    DSP2803x_ECan.c
//
// TITLE:   DSP2803x Enhanced CAN Initialization & Support Functions.
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
#include "DSP2803x_Device.h"     // DSP28 Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP28 Examples Include File

//
// InitECan - This function initializes the eCAN module to a known state.
//
void 
InitECan(void)
{
    InitECana();
}

//
// InitECana - Initialize eCAN-A module
//
void
InitECana(void)   
{
    //
    // Create a shadow register structure for the CAN control registers.
    // This is needed, since only 32-bit access is allowed to these registers.
    // 16-bit access to these registers could potentially corrupt the register
    // contents or return false data.
    struct ECAN_REGS ECanaShadow;

    //
    // EALLOW enables access to protected bits
    //
    EALLOW;

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
    // Initialize all bits of 'Message Control Register' to zero
    // Some bits of MSGCTRL register come up in an unknown state.
    // For proper operation, all bits (including reserved bits) of MSGCTRL must
    // be initialized to zero
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
    ECanaRegs.CANTA.all = 0xFFFFFFFF;       // Clear all TAn bits
    ECanaRegs.CANRMP.all = 0xFFFFFFFF;      // Clear all RMPn bits
    ECanaRegs.CANGIF0.all = 0xFFFFFFFF;     // Clear all interrupt flag bits
    ECanaRegs.CANGIF1.all = 0xFFFFFFFF;

    //
    // Configure bit timing parameters for eCANA
    //
    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
    ECanaShadow.CANMC.bit.CCR = 1 ;            // Set CCR = 1
    ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

    //
    // Wait until the CPU has been granted permission to change 
    // the configuration registers
    //
    do
    {
        ECanaShadow.CANES.all = ECanaRegs.CANES.all;
    } while(ECanaShadow.CANES.bit.CCE != 1 );   // Wait for CCE bit to be set

    ECanaShadow.CANBTC.all = 0;
    
    //
    // The following block is only for 60 MHz SYSCLKOUT.
    // (30 MHz CAN module clock Bit rate = 1 Mbps)
    // See Note at end of file.
    //
    ECanaShadow.CANBTC.bit.BRPREG = 2;
    ECanaShadow.CANBTC.bit.TSEG2REG = 1;
    ECanaShadow.CANBTC.bit.TSEG1REG = 6;

    ECanaShadow.CANBTC.bit.SAM = 0;
    ECanaRegs.CANBTC.all = ECanaShadow.CANBTC.all;

    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
    ECanaShadow.CANMC.bit.CCR = 0 ;            // Set CCR = 0
    ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

    //
    // Wait until the CPU no longer has permission to change
    // the configuration registers
    //
    do
    {
        ECanaShadow.CANES.all = ECanaRegs.CANES.all;
    } while(ECanaShadow.CANES.bit.CCE != 0 );   // Wait for CCE bit to clear

    //
    // Disable all Mailboxes
    //
    ECanaRegs.CANME.all = 0;        // Required before writing the MSGIDs

    EDIS;
}

//
// InitECanGpio - This function initializes GPIO pins to function as eCAN pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// Only one GPIO pin should be enabled for CANTXA operation.
// Only one GPIO pin shoudl be enabled for CANRXA operation.
// Comment out other unwanted lines.
//
void 
InitECanGpio(void)
{
   InitECanaGpio();
}

//
// InitECanaGpio - Configure eCAN-A module GPIO pins to function as eCAN pins
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
    GpioCtrlRegs.GPAPUD.bit.GPIO30 = 0;   // Enable pull-up for GPIO30 (CANRXA)
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;   // Enable pull-up for GPIO31 (CANTXA)

    //
    // Set qualification for selected CAN pins to asynch only
    // Inputs are synchronized to SYSCLKOUT by default.
    // This will select asynch (no qualification) for the selected pins.
    //
    GpioCtrlRegs.GPAQSEL2.bit.GPIO30 = 3;   // Asynch qual for GPIO30 (CANRXA)

    //
    // Configure eCAN-A pins using GPIO regs
    // This specifies which of the possible GPIO pins will be 
    // eCAN functional pins.
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;    // Configure GPIO30 to CANRXA 
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;    // Configure GPIO31 to CANTXA 

    EDIS;
}

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
// End of file
//

