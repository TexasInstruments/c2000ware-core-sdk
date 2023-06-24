//#############################################################################
//
// FILE:   sci_ex3_interrupts_fifo.c
//
// TITLE:  SCI interrupt echoback example with FIFO.
//
//! \addtogroup driver_example_list
//! <h1>SCI Interrupt Echoback with FIFO</h1>
//!
//!  This test receives and echo-backs data through the SCI-A port
//!  via interrupts two characters at a time. A Rx interrupt is triggered
//!  after the FIFO status level is two or greater. Once two characters
//!  are in the RXFIFO, the SCI Rx ISR will be triggered and will read two
//!  characters from the FIFO and write them to the transmit buffer. The SCI
//!  Tx ISR will then be triggered again to request more data from the terminal.
//!
//!  A terminal such as 'putty' can be used to view the data from
//!  the SCI and to send information to the SCI. Characters received
//!  by the SCI port are sent back to the host.
//!
//!  \b Running \b the \b Application
//!  Open a COM port with the following settings using a terminal:
//!  -  Find correct COM port
//!  -  Bits per second = 9600
//!  -  Data Bits = 8
//!  -  Parity = None
//!  -  Stop Bits = 1
//!  -  Hardware Control = None
//!
//!  The program will print out a greeting and then ask you to
//!  enter two characters which it will echo back to the terminal.
//!
//!  \b Watch \b Variables \n
//!  - counter - the number of character pairs sent
//!
//! \b External \b Connections \n
//!  Connect the SCI-A port to a PC via a transceiver and cable.
//!  - GPIO28 is SCI_A-RXD (Connect to Pin3, PC-TX, of serial DB9 cable)
//!  - GPIO29 is SCI_A-TXD (Connect to Pin2, PC-RX, of serial DB9 cable)
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

#ifdef _FLASH
// These are defined by the linker (see device linker command file)
extern uint16_t RamfuncsLoadStart;
extern uint16_t RamfuncsLoadSize;
extern uint16_t RamfuncsRunStart;
#endif

//
// Defines
//
// Define AUTOBAUD to use the autobaud lock feature
//#define AUTOBAUD

//
// Globals
//
uint16_t counter = 0;
unsigned char *msg;

//
// Function Prototypes
//
__interrupt void sciaTxISR(void);
__interrupt void sciaRxISR(void);

//
// Main
//
void main(void)
{
    //
    // Configure PLL, disable WD, enable peripheral clocks.
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // GPIO28 is the SCI Rx pin.
    //
    GPIO_setControllerCore(DEVICE_GPIO_PIN_SCIRXDA, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCIRXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_QUAL_ASYNC);

    //
    // GPIO29 is the SCI Tx pin.
    //
    GPIO_setControllerCore(DEVICE_GPIO_PIN_SCITXDA, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCITXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_QUAL_ASYNC);

    //
    // Disable global interrupts.
    //
    DINT;

    //
    // Initialize interrupt controller and vector table.
    //
    Interrupt_initModule();
    Interrupt_initVectorTable();
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Map the ISR to the wake interrupt.
    //
    Interrupt_register(INT_SCIA_TX, sciaTxISR);
    Interrupt_register(INT_SCIA_RX, sciaRxISR);

    //
    // Initialize SCIA and its FIFO.
    //
    SCI_performSoftwareReset(SCIA_BASE);

    //
    // Configure SCIA for echoback.
    //
    SCI_setConfig(SCIA_BASE, 25000000, 9600, (SCI_CONFIG_WLEN_8 |
                                             SCI_CONFIG_STOP_ONE |
                                             SCI_CONFIG_PAR_NONE));
    SCI_resetChannels(SCIA_BASE);
    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_TXFF | SCI_INT_RXFF);
    SCI_enableFIFO(SCIA_BASE);
    SCI_enableModule(SCIA_BASE);
    SCI_performSoftwareReset(SCIA_BASE);

    //
    // Set the transmit FIFO level to 0 and the receive FIFO level to 2.
    // Enable the TXFF and RXFF interrupts.
    //
    SCI_setFIFOInterruptLevel(SCIA_BASE, SCI_FIFO_TX0, SCI_FIFO_RX2);
    SCI_enableInterrupt(SCIA_BASE, SCI_INT_TXFF | SCI_INT_RXFF);

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

    //
    // Clear the SCI interrupts before enabling them.
    //
    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_TXFF | SCI_INT_RXFF);

    //
    // Enable the interrupts in the PIE: Group 9 interrupts 1 & 2.
    //
    Interrupt_enable(INT_SCIA_RX);
    Interrupt_enable(INT_SCIA_TX);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);

    //
    // Enable global interrupts.
    //
    EINT;

    for(;;)
    {
    }
}

//
// sciaTxISR - Disable the TXFF interrupt and print message asking
//             for two characters.
//
__interrupt void
sciaTxISR(void)
{
    //
    // Disable the TXRDY interrupt.
    //
    SCI_disableInterrupt(SCIA_BASE, SCI_INT_TXFF);

    msg = "\r\nEnter two characters: \0";
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 26);

    //
    // Acknowledge the PIE interrupt.
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

//
// sciaRxISR - Read two characters from the RXBUF and echo them back.
//
__interrupt void
sciaRxISR(void)
{
    uint16_t receivedChar1, receivedChar2;

    //
    // Enable the TXFF interrupt again.
    //
    SCI_enableInterrupt(SCIA_BASE, SCI_INT_TXFF);

    //
    // Read two characters from the FIFO.
    //
    receivedChar1 = SCI_readCharBlockingFIFO(SCIA_BASE);
    receivedChar2 = SCI_readCharBlockingFIFO(SCIA_BASE);

    //
    // Echo back the two characters.
    //
    msg = "  You sent: \0";
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 13);
    SCI_writeCharBlockingFIFO(SCIA_BASE, receivedChar1);
    SCI_writeCharBlockingFIFO(SCIA_BASE, receivedChar2);

    //
    // Clear the SCI RXFF interrupt and acknowledge the PIE interrupt.
    //
    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_RXFF);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);

    counter++;
}

//
// End of File
//

