//###########################################################################
//
// FILE:    Example_2802x0Sci_Echoback.c
//
// TITLE:   f2802x0 Device SCI Echoback.
//
// ASSUMPTIONS:
//
//    This program requires the f2802x0 header files.
//    As supplied, this project is configured for "boot to SARAM" operation.
//
//    Connect the SCI-A port to a PC via a transciever and cable.
//    The PC application 'hypterterminal' can be used to view the data
//    from the SCI and to send information to the SCI.  Characters received
//    by the SCI port are sent back to the host.
//
//    As supplied, this project is configured for "boot to SARAM"
//    operation.  The 2802x0 Boot Mode table is shown below.
//    For information on configuring the boot mode of an eZdsp,
//    please refer to the documentation included with the eZdsp,
//
//    $Boot_Table
//    While an emulator is connected to your device, the TRSTn pin = 1,
//    which sets the device into EMU_BOOT boot mode. In this mode, the
//    peripheral boot modes are as follows:
//
//      Boot Mode:   EMU_KEY        EMU_BMODE
//                   (0xD00)         (0xD01)
//      ---------------------------------------
//      Wait         !=0x55AA        X
//      I/O          0x55AA          0x0000
//      SCI          0x55AA          0x0001
//      Wait         0x55AA          0x0002
//      Get_Mode     0x55AA          0x0003
//      SPI          0x55AA          0x0004
//      I2C          0x55AA          0x0005
//      OTP          0x55AA          0x0006
//      Wait         0x55AA          0x0007
//      Wait         0x55AA          0x0008
//      SARAM        0x55AA          0x000A   <-- "Boot to SARAM"
//      Flash        0x55AA          0x000B
//      Wait         0x55AA          Other
//
//   Write EMU_KEY to 0xD00 and EMU_BMODE to 0xD01 via the debugger
//   according to the Boot Mode Table above. Build/Load project,
//   Reset the device, and Run example
//
//   $End_Boot_Table
//
// DESCRIPTION:
//
//
//    This test receives and echo-backs data through the SCI-A port.
//
//    1) Configure hyperterminal:
//       Use the included hyperterminal configuration file SCI_96.ht.
//       To load this configuration in hyperterminal: file->open
//       and then select the SCI_96.ht file.
//    2) Check the COM port.
//       The configuration file is currently setup for COM1.
//       If this is not correct, disconnect Call->Disconnect
//       Open the File-Properties dialog and select the correct COM port.
//    3) Connect hyperterminal Call->Call
//       and then start the 2802x0 SCI echoback program execution.
//    4) The program will print out a greeting and then ask you to
//       enter a character which it will echo back to hyperterminal.
//
//
//    Watch Variables:
//       LoopCount for the number of characters sent
//       ErrorCount
//
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
void scia_echoback_init(void);
void scia_fifo_init(void);
void scia_xmit(int a);
void scia_msg(char *msg);

//
// Globals
//
uint16_t LoopCount;
uint16_t ErrorCount;

//
// Main
//
void main(void)
{
    Uint16 ReceivedChar;
    char *msg;

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
    // This example function is found in the f2802x0_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the f2802x0_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    //InitGpio(); Skipped for this example

    //
    // For this example, only init the pins for the SCI-A port.
    // This function is found in the f2802x0_Sci.c file.
    //
    InitSciaGpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the f2802x0_PieCtrl.c file.
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
    // The shell ISR routines are found in f2802x0_DefaultIsr.c.
    // This function is found in f2802x0_PieVect.c.
    //
    InitPieVectTable();

    //
    // Step 4. Initialize all the Device Peripherals
    // Not required for this example
    //

    //
    // Step 5. User specific code
    //

    LoopCount = 0;
    ErrorCount = 0;

    scia_fifo_init();           // Initialize the SCI FIFO
    scia_echoback_init();       // Initialize SCI for echoback

    msg = "\r\n\n\nHello World!\0";
    scia_msg(msg);

    msg = "\r\nYou will enter a character, and the DSP will echo it back!\n\0";
    scia_msg(msg);

    for(;;)
    {
        msg = "\r\nEnter a character: \0";
        scia_msg(msg);

        //
        // Wait for inc character
        //
        while(SciaRegs.SCIFFRX.bit.RXFFST !=1)
        {
            //
            // wait for XRDY =1 for empty state
            //
        }

        //
        // Get character
        //
        ReceivedChar = SciaRegs.SCIRXBUF.all;

        //
        // Echo character back
        //
        msg = "  You sent: \0";
        scia_msg(msg);
        scia_xmit(ReceivedChar);

        LoopCount++;
    }
}

//
// scia_echoback_init - Test 1,SCIA  DLB, 8-bit word, baud rate 0x000F, default
// 1 STOP bit, no parity
//
void
scia_echoback_init()
{
    //
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
    //
    
    //
    // 1 stop bit,  No loopback, No parity, 8 char bits, async mode, 
    // idle-line protocol
    //
    SciaRegs.SCICCR.all =0x0007;   
    
    //
    // enable TX, RX, internal SCICLK, Disable RX ERR, SLEEP, TXWAKE
    //
    SciaRegs.SCICTL1.all =0x0003;
    SciaRegs.SCICTL2.all =0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA =1;
    SciaRegs.SCICTL2.bit.RXBKINTENA =1;

    //
    // SCI BRR = LSPCLK/(SCI BAUDx8) - 1
    //
#if (CPU_FRQ_60MHZ)
    SciaRegs.SCIHBAUD = 0x0000;  // 9600 baud @LSPCLK = 15MHz(60 MHz SYSCLK)
    SciaRegs.SCILBAUD = 0x00C2;
#elif (CPU_FRQ_50MHZ)
    SciaRegs.SCIHBAUD = 0x0000;  // 9600 baud @LSPCLK = 12.5 MHz(50 MHz SYSCLK)
    SciaRegs.SCILBAUD = 0x00A1;
#elif (CPU_FRQ_40MHZ)
    SciaRegs.SCIHBAUD = 0x0000;  // 9600 baud @LSPCLK = 10MHz(40 MHz SYSCLK)
    SciaRegs.SCILBAUD = 0x0081;
#endif

    SciaRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
}

//
// scia_xmit - Transmit a character from the SCI
//
void
scia_xmit(int a)
{
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0)
    {
        
    }
    SciaRegs.SCITXBUF=a;
}

//
// scia_msg - 
//
void
scia_msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scia_xmit(msg[i]);
        i++;
    }
}

//
// scia_fifo_init - Initialize the SCI FIFO
//
void
scia_fifo_init()
{
    SciaRegs.SCIFFTX.all=0xE040;
    SciaRegs.SCIFFRX.all=0x2044;
    SciaRegs.SCIFFCT.all=0x0;
}

//
// End of File
//

