//#############################################################################
//
// FILE:   sci_ex1_sysconfig_cpu2.c
//
// TITLE: SysConfig SCI exhoback example
//
//! \addtogroup driver_dual_example_list
//! <h1>SCI Echoback SysConfig CPU2</h1>
//!
//!  This test receives and echo-backs data through the SCI port.
//!
//!  A terminal such as 'putty' can be used to view the data from
//!  the SCI and to send information to the SCI. Characters received
//!  by the SCI port are sent back to the host.
//!
//!  \b Running \b the \b Application
//!  Open a COM port with the following settings using a terminal:
//!  -  Find correct COM port
//!  -  Bits per second = 9600 (or Sysconfig-configured value)
//!  -  Data Bits = 8 (or Sysconfig-configured value)
//!  -  Parity = None (or Sysconfig-configured value)
//!  -  Stop Bits = 1 (or Sysconfig-configured value)
//!  -  Hardware Control = None
//!
//!  The program will print out a greeting and then ask you to
//!  enter a character which it will echo back to the terminal.
//!
//!  \b Watch \b Variables \n
//!  - loopCounter - the number of characters sent
//!
//! \b External \b Connections \n
//!  Connect the SCI port to a PC via a transceiver and cable.
//!  - GPIO chosen in Sysconfig for SCI-RX (Connect to PC-TX of DB9)
//!  - GPIO chosen in Sysconfig for SCI-TX (Connect to PC-RX of DB9)
//!
//
//#############################################################################
//
//
// 
// C2000Ware v6.00.01.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "inc/hw_ipc.h"
#include "board.h"

//
// Defines
//
// Define AUTOBAUD to use the autobaud lock feature
//#define AUTOBAUD

//
// Globals
//
uint16_t loopCounter = 0;

//
// Main
//
void main(void)
{
    uint16_t receivedChar;
    unsigned char *msg;
    uint16_t rxStatus = 0U;
    //uint16_t ipcFlag17 = 17U;

    //
    // Configure PLL, disable WD, enable peripheral clocks.
    //
    Device_init();

    //
    // Initialize interrupt controller and vector table.
    //
    Interrupt_initModule();
    Interrupt_initVectorTable();

    //
    // Wait until CPU01 is ready and IPC flag 17 is set
    //
    IPC_sync(IPC_CPU2_L_CPU1_R, SYNC_FLAG);

    //
    // Initialize settings from SysConfig
    //
    Board_init();

#ifdef AUTOBAUD
    //
    // Perform an autobaud lock.
    // SCI expects an 'a' or 'A' to lock the baud rate.
    //
    SCI_lockAutobaud(SCIA_BASE);
#endif

    //
    // Send starting message.
    //
    msg = "\r\n\n\nHello World!\0";
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 17);
    msg = "\r\nYou will enter a character, and the DSP will echo it back!\n\0";
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 62);

    for(;;)
    {
        msg = "\r\nEnter a character: \0";
        SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 22);

        //
        // Read a character from the FIFO.
        //
        receivedChar = SCI_readCharBlockingFIFO(SCIA_BASE);

        rxStatus = SCI_getRxStatus(SCIA_BASE);
        if((rxStatus & SCI_RXSTATUS_ERROR) != 0)
        {
            //
            //If Execution stops here there is some error
            //Analyze SCI_getRxStatus() API return value
            //
            ESTOP0;
        }

        //
        // Echo back the character.
        //
        msg = "  You sent: \0";
        SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 13);
        SCI_writeCharBlockingFIFO(SCIA_BASE, receivedChar);

        //
        // Increment the loop count variable.
        //
        loopCounter++;
    }
}

//
// End of File
//

