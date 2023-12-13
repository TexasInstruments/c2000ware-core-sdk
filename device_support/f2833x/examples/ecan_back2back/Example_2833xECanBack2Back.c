//###########################################################################
//
// FILE:   Example_2833xECanBack2Back.c
//
// TITLE:  eCAN back to back Example
//
//! \addtogroup f2833x_example_list
//! <h1>eCAN back to back (ecan_back2back)</h1>
//!
//! This example tests eCAN by transmitting data back-to-back at high speed
//! without stopping. The received data is verified. Any error is flagged.
//! MBX0 transmits to MBX16, MBX1 transmits to MBX17 and so on.... \n
//! This program illustrates the use of self-test mode
//!
//! This example uses the self-test mode of the CAN module. i.e. the
//! transmission/reception happens within the module itself (even the required
//! ACKnowldege is generated internally in the module). Therefore, there is no
//! need for a CAN transceiver to run this particular test case and no activity
//! will be seen in the CAN pins/bus. Because everything is internal, there is
//! no need for a 120-ohm termination resistor. Note that a real-world CAN
//! application needs a CAN transceiver and termination resistors on both ends
//! of the bus.
//!
//! \b Watch \b Variables \n
//! - PassCount
//! - ErrorCount
//! - MessageReceivedCount
//
//
//###########################################################################
// $TI Release: $
// $Release Date: $
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
// Function Prototypes
//
void mailbox_check(int32 T1, int32 T2, int32 T3);
void mailbox_read(int16 i);

//
// Globals
//
Uint32  ErrorCount;
Uint32  PassCount;
Uint32  MessageReceivedCount;

Uint32  TestMbox1 = 0;
Uint32  TestMbox2 = 0;
Uint32  TestMbox3 = 0;

//
// Main
//
void main(void)
{
    Uint16  j;

    //
    // eCAN control registers require read/write access using 32-bits.  Thus we
    // will create a set of shadow registers for this example.  These shadow
    // registers will be used to make sure the access is 32-bits and not 16.
    //
    struct ECAN_REGS ECanaShadow;

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2833x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2833x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // For this example, configure CAN pins using GPIO regs here
    // This function is found in DSP2833x_ECan.c
    //
    InitECanGpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2833x_PieCtrl.c file.
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
    // The shell ISR routines are found in DSP2833x_DefaultIsr.c.
    // This function is found in DSP2833x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in DSP2833x_InitPeripherals.c
    //
    // InitPeripherals(); // Not required for this example

    //
    // Step 5. User specific code, enable interrupts:
    //
    MessageReceivedCount = 0;
    ErrorCount = 0;
    PassCount = 0;

    //
    // Initialize eCAN-A module
    //
    InitECana();

    //
    // Mailboxes can be written to 16-bits or 32-bits at a time
    // Write to the MSGID field of TRANSMIT mailboxes MBOX0 - 15
    //
    ECanaMboxes.MBOX0.MSGID.all = 0x9555AAA0;
    ECanaMboxes.MBOX1.MSGID.all = 0x9555AAA1;
    ECanaMboxes.MBOX2.MSGID.all = 0x9555AAA2;
    ECanaMboxes.MBOX3.MSGID.all = 0x9555AAA3;
    ECanaMboxes.MBOX4.MSGID.all = 0x9555AAA4;
    ECanaMboxes.MBOX5.MSGID.all = 0x9555AAA5;
    ECanaMboxes.MBOX6.MSGID.all = 0x9555AAA6;
    ECanaMboxes.MBOX7.MSGID.all = 0x9555AAA7;
    ECanaMboxes.MBOX8.MSGID.all = 0x9555AAA8;
    ECanaMboxes.MBOX9.MSGID.all = 0x9555AAA9;
    ECanaMboxes.MBOX10.MSGID.all = 0x9555AAAA;
    ECanaMboxes.MBOX11.MSGID.all = 0x9555AAAB;
    ECanaMboxes.MBOX12.MSGID.all = 0x9555AAAC;
    ECanaMboxes.MBOX13.MSGID.all = 0x9555AAAD;
    ECanaMboxes.MBOX14.MSGID.all = 0x9555AAAE;
    ECanaMboxes.MBOX15.MSGID.all = 0x9555AAAF;

    //
    // Write to the MSGID field of RECEIVE mailboxes MBOX16 - 31
    //
    ECanaMboxes.MBOX16.MSGID.all = 0x9555AAA0;
    ECanaMboxes.MBOX17.MSGID.all = 0x9555AAA1;
    ECanaMboxes.MBOX18.MSGID.all = 0x9555AAA2;
    ECanaMboxes.MBOX19.MSGID.all = 0x9555AAA3;
    ECanaMboxes.MBOX20.MSGID.all = 0x9555AAA4;
    ECanaMboxes.MBOX21.MSGID.all = 0x9555AAA5;
    ECanaMboxes.MBOX22.MSGID.all = 0x9555AAA6;
    ECanaMboxes.MBOX23.MSGID.all = 0x9555AAA7;
    ECanaMboxes.MBOX24.MSGID.all = 0x9555AAA8;
    ECanaMboxes.MBOX25.MSGID.all = 0x9555AAA9;
    ECanaMboxes.MBOX26.MSGID.all = 0x9555AAAA;
    ECanaMboxes.MBOX27.MSGID.all = 0x9555AAAB;
    ECanaMboxes.MBOX28.MSGID.all = 0x9555AAAC;
    ECanaMboxes.MBOX29.MSGID.all = 0x9555AAAD;
    ECanaMboxes.MBOX30.MSGID.all = 0x9555AAAE;
    ECanaMboxes.MBOX31.MSGID.all = 0x9555AAAF;

    //
    // Configure Mailboxes 0-15 as Tx, 16-31 as Rx
    // Since this write is to the entire register (instead of a bit field)
    // a shadow register is not required.
    //
    ECanaRegs.CANMD.all = 0xFFFF0000;

    //
    // Enable all Mailboxes
    // Since this write is to the entire register (instead of a bit field)
    // a shadow register is not required.
    //
    ECanaRegs.CANME.all = 0xFFFFFFFF;

    //
    // Specify that 8 bits will be sent/received
    //
    ECanaMboxes.MBOX0.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX1.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX2.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX3.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX4.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX5.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX6.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX7.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX8.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX9.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX10.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX11.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX12.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX13.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX14.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX15.MSGCTRL.bit.DLC = 8;

    //
    // Write to the mailbox RAM field of MBOX0 - 15
    //
    ECanaMboxes.MBOX0.MDL.all = 0x9555AAA0;
    ECanaMboxes.MBOX0.MDH.all = 0x89ABCDEF;

    ECanaMboxes.MBOX1.MDL.all = 0x9555AAA1;
    ECanaMboxes.MBOX1.MDH.all = 0x89ABCDEF;

    ECanaMboxes.MBOX2.MDL.all = 0x9555AAA2;
    ECanaMboxes.MBOX2.MDH.all = 0x89ABCDEF;

    ECanaMboxes.MBOX3.MDL.all = 0x9555AAA3;
    ECanaMboxes.MBOX3.MDH.all = 0x89ABCDEF;

    ECanaMboxes.MBOX4.MDL.all = 0x9555AAA4;
    ECanaMboxes.MBOX4.MDH.all = 0x89ABCDEF;

    ECanaMboxes.MBOX5.MDL.all = 0x9555AAA5;
    ECanaMboxes.MBOX5.MDH.all = 0x89ABCDEF;

    ECanaMboxes.MBOX6.MDL.all = 0x9555AAA6;
    ECanaMboxes.MBOX6.MDH.all = 0x89ABCDEF;

    ECanaMboxes.MBOX7.MDL.all = 0x9555AAA7;
    ECanaMboxes.MBOX7.MDH.all = 0x89ABCDEF;

    ECanaMboxes.MBOX8.MDL.all = 0x9555AAA8;
    ECanaMboxes.MBOX8.MDH.all = 0x89ABCDEF;

    ECanaMboxes.MBOX9.MDL.all = 0x9555AAA9;
    ECanaMboxes.MBOX9.MDH.all = 0x89ABCDEF;

    ECanaMboxes.MBOX10.MDL.all = 0x9555AAAA;
    ECanaMboxes.MBOX10.MDH.all = 0x89ABCDEF;

    ECanaMboxes.MBOX11.MDL.all = 0x9555AAAB;
    ECanaMboxes.MBOX11.MDH.all = 0x89ABCDEF;

    ECanaMboxes.MBOX12.MDL.all = 0x9555AAAC;
    ECanaMboxes.MBOX12.MDH.all = 0x89ABCDEF;

    ECanaMboxes.MBOX13.MDL.all = 0x9555AAAD;
    ECanaMboxes.MBOX13.MDH.all = 0x89ABCDEF;

    ECanaMboxes.MBOX14.MDL.all = 0x9555AAAE;
    ECanaMboxes.MBOX14.MDH.all = 0x89ABCDEF;

    ECanaMboxes.MBOX15.MDL.all = 0x9555AAAF;
    ECanaMboxes.MBOX15.MDH.all = 0x89ABCDEF;

    //
    // Since this write is to the entire register (instead of a bit field)
    // a shadow register is not required.
    //
    EALLOW;
    ECanaRegs.CANMIM.all = 0xFFFFFFFF;

    //
    // Configure the eCAN for self test mode
    // Enable the enhanced features of the eCAN.
    //
    EALLOW;
    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
    ECanaShadow.CANMC.bit.STM = 1;      // Configure CAN for self-test mode
    ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
    EDIS;

    //
    // Begin transmitting
    //
    for(;;)
    {
        ECanaRegs.CANTRS.all = 0x0000FFFF; //Set TRS for all transmit mailboxes
        while(ECanaRegs.CANTA.all != 0x0000FFFF ) 
        {
            
        }   // Wait for all TAn bits to be set
        
        ECanaRegs.CANTA.all = 0x0000FFFF;   // Clear all TAn
        MessageReceivedCount++;
    
        //
        // Read from Receive mailboxes and begin checking for data
        //
        for(j=16; j<32; j++) // Read & check 16 mailboxes
        {
            //
            // This func reads the indicated mailbox data
            //
            mailbox_read(j);
            
            //
            // Checks the received data
            //
            mailbox_check(TestMbox1,TestMbox2,TestMbox3);
        }
    }
}

//
// mailbox_read - This function reads out the contents of the indicated
// by the Mailbox number (MBXnbr).
//
void 
mailbox_read(int16 MBXnbr)
{
    volatile struct MBOX *Mailbox;
    Mailbox = &ECanaMboxes.MBOX0 + MBXnbr;
    TestMbox1 = Mailbox->MDL.all;       // = 0x9555AAAn (n is the MBX number)
    TestMbox2 = Mailbox->MDH.all;       // = 0x89ABCDEF (a constant)
    TestMbox3 = Mailbox->MSGID.all;     // = 0x9555AAAn (n is the MBX number)
} // MSGID of a rcv MBX is transmitted as the MDL data.

//
// mailbox_check - 
//
void 
mailbox_check(int32 T1, int32 T2, int32 T3)
{
    if((T1 != T3) || ( T2 != 0x89ABCDEF))
    {
        ErrorCount++;
    }
    else
    {
        PassCount++;
    }
}

//
// End of File
//

