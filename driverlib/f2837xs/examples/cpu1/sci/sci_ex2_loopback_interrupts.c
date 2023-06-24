//###########################################################################
//
// FILE:   sci_ex2_loopback_interrupts.c
//
// TITLE:  SCI Digital Loop Back with Interrupts.
//
//! \addtogroup driver_example_list
//! <h1> SCI Digital Loop Back with Interrupts </h1>
//!
//!  This test uses the internal loop back test mode of the peripheral.
//!  Other then boot mode pin configuration, no other hardware configuration
//!  is required. Both interrupts and the SCI FIFOs are used.
//!
//!  A stream of data is sent and then compared to the received stream.
//!  The SCI-A sent data looks like this: \n
//!  00 01 \n
//!  01 02 \n
//!  02 03 \n
//!  .... \n
//!  FE FF \n
//!  FF 00 \n
//!  etc.. \n
//!  The pattern is repeated forever.
//!
//!  \b Watch \b Variables \n
//!  - \b sDataA - Data being sent
//!  - \b rDataA - Data received
//!  - \b rDataPointA - Keep track of where we are in the data stream.
//!    This is used to check the incoming data
//!
//
//###########################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2014-2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "driverlib.h"
#include "device.h"

//
// Globals
//

//
// Send data for SCI-A
//
uint16_t sDataA[2];

//
// Received data for SCI-A
//
uint16_t rDataA[2];

//
// Used for checking the received data
//
uint16_t rDataPointA;

//
// Function Prototypes
//
__interrupt void sciaTXFIFOISR(void);
__interrupt void sciaRXFIFOISR(void);
void initSCIAFIFO(void);
void error(void);

//
// Main
//
void main(void)
{
    uint16_t i;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Setup GPIO by disabling pin locks and enabling pullups
    //
    Device_initGPIO();

    //
    // GPIO28 is the SCI Rx pin.
    //
    GPIO_setMasterCore(28, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_28_SCIRXDA);
    GPIO_setDirectionMode(28, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(28, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(28, GPIO_QUAL_ASYNC);

    //
    // GPIO29 is the SCI Tx pin.
    //
    GPIO_setMasterCore(29, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_29_SCITXDA);
    GPIO_setDirectionMode(29, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(29, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(29, GPIO_QUAL_ASYNC);

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_SCIA_RX, sciaRXFIFOISR);
    Interrupt_register(INT_SCIA_TX, sciaTXFIFOISR);

    //
    // Initialize the Device Peripherals:
    //
    initSCIAFIFO();

    //
    // Init the send data.  After each transmission this data
    // will be updated for the next transmission
    //
    for(i = 0; i < 2; i++)
    {
        sDataA[i] = i;
    }

    rDataPointA = sDataA[0];

    Interrupt_enable(INT_SCIA_RX);
    Interrupt_enable(INT_SCIA_TX);

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;);
}

//
// error - Function to halt debugger on error
//
void error(void)
{
    Example_Fail = 1;
    asm("     ESTOP0"); // Test failed!! Stop!
    for (;;);
}

//
// sciaTXFIFOISR - SCIA Transmit FIFO ISR
//
__interrupt void sciaTXFIFOISR(void)
{
    uint16_t i;

    SCI_writeCharArray(SCIA_BASE, sDataA, 2);

    //
    // Increment send data for next cycle
    //
    for(i = 0; i < 2; i++)
    {
        sDataA[i] = (sDataA[i] + 1) & 0x00FF;
    }

    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_TXFF);

    //
    // Issue PIE ACK
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

//
// sciaRXFIFOISR - SCIA Receive FIFO ISR
//
__interrupt void sciaRXFIFOISR(void)
{
    uint16_t i;

    SCI_readCharArray(SCIA_BASE, rDataA, 2);

    //
    // Check received data
    //
    for(i = 0; i < 2; i++)
    {
        if(rDataA[i] != ((rDataPointA + i) & 0x00FF))
        {
            error();
        }
    }

    rDataPointA = (rDataPointA + 1) & 0x00FF;

    SCI_clearOverflowStatus(SCIA_BASE);

    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_RXFF);

    //
    // Issue PIE ack
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);

    Example_PassCount++;
}

//
// initSCIAFIFO - Configure SCIA FIFO
//
void initSCIAFIFO()
{
    //
    // 8 char bits, 1 stop bit, no parity. Baud rate is 9600.
    //
    SCI_setConfig(SCIA_BASE, DEVICE_LSPCLK_FREQ, 9600, (SCI_CONFIG_WLEN_8 |
                                                        SCI_CONFIG_STOP_ONE |
                                                        SCI_CONFIG_PAR_NONE));
    SCI_enableModule(SCIA_BASE);
    SCI_enableLoopback(SCIA_BASE);
    SCI_resetChannels(SCIA_BASE);
    SCI_enableFIFO(SCIA_BASE);

    //
    // RX and TX FIFO Interrupts Enabled
    //
    SCI_enableInterrupt(SCIA_BASE, (SCI_INT_RXFF | SCI_INT_TXFF));
    SCI_disableInterrupt(SCIA_BASE, SCI_INT_RXERR);

    SCI_setFIFOInterruptLevel(SCIA_BASE, SCI_FIFO_TX2, SCI_FIFO_RX2);
    SCI_performSoftwareReset(SCIA_BASE);

    SCI_resetTxFIFO(SCIA_BASE);
    SCI_resetRxFIFO(SCIA_BASE);

#ifdef AUTOBAUD
    //
    // Perform an autobaud lock.
    // SCI expects an 'a' or 'A' to lock the baud rate.
    //
    SCI_lockAutobaud(SCIA_BASE);
#endif
}

//
// End of file
//
