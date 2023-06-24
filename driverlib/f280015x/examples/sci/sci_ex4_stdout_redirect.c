//#############################################################################
//
// TITLE:  stdout redirect example
//!
//! \addtogroup driver_example_list
//! <h1> stdout redirect example </h1>
//!  This test transmits data through the SCI-A port to a terminal
//!
//!  A terminal such as 'putty' can be used to view the data from
//!  the SCI. Characters received by the SCI port are sent back to the host.
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
//!  The program will print out three sentences: one to the SCIA, one to CCS,
//!  and a final one to SCIA.
//!
//! \b External \b Connections \n
//!  Connect the SCI-A port to a PC via a transceiver and cable.
//!  - DEVICE_GPIO_PIN_SCIRXDA is SCI_A-RXD (Connect to Pin3, PC-TX, of serial DB9 cable)
//!  - DEVICE_GPIO_PIN_SCITXDA is SCI_A-TXD (Connect to Pin2, PC-RX, of serial DB9 cable)
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
#include <assert.h>
#include <stdio.h>
#include <file.h>
#include "uart_drv.h"

//
// Defines
//

//
// Globals
//
uint16_t loopCounter = 0;

//
// Declarations
//
void UartSetup();
void UartPutChar(uint16_t charToWrite);

//
// Main
//
void main(void)
{
    uint16_t receivedChar;
    unsigned char *msg;
    uint16_t rxStatus = 0U;

    //
    // Configure PLL, disable WD, enable peripheral clocks.
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();





    //**************************************************************************
    // NOTE: SCI Configuration for this example is done in UartSetup()
    // As an alternative, the user can configure SCI here in the main, and then
    // provide an empty UartSetup() function. UartSetup() must be defined, even
    // if it is empty.
    //**************************************************************************




    /*-----------------------------------------------------------------------*/
    /* STDOUT CONFIG START                                                   */
    /*-----------------------------------------------------------------------*/
    FILE *uart = NULL;

    /*-----------------------------------------------------------------------*/
    /* Add the UART device.  When fopen is called with a filename that       */
    /* begins "uart:", the UART device will be used to handle the file.      */
    /*-----------------------------------------------------------------------*/
    add_device("uart",
               _SSA,
               UART_open,
               UART_close,
               UART_read,
               UART_write,
               UART_lseek,
               UART_unlink,
               UART_rename);

    /*-----------------------------------------------------------------------*/
    /* Open a UART file.  Because the "uart" device is _SSA, only one UART   */
    /* file may be open at once.                                             */
    /*-----------------------------------------------------------------------*/

    uart = fopen("uart:", "w");
    assert(uart != NULL);

    /*-----------------------------------------------------------------------*/
    /* Now, write something to the UART device                               */
    /*-----------------------------------------------------------------------*/
    fputs("\r\n\r\n", uart);
    fputs("hello, world on UART\r\n", uart);

    /*-----------------------------------------------------------------------*/
    /* We must close the UART file before opening another with freopen,      */
    /* below.  Closing a file will flush the buffer automatically.           */
    /*-----------------------------------------------------------------------*/
    fclose(uart);

    /*-----------------------------------------------------------------------*/
    /* Add delay here based on the number of bytes being sent and baud rate  */
    /* This allows time for buffer to flush                                  */
    /* In this example: 22 chars for last fputs = 176 bits                   */
    /* 176 bits * (1/9600 bits/sec) = ~20 ms delay required for all bytes    */
    /*-----------------------------------------------------------------------*/
    DEVICE_DELAY_US(20000);

    /*-----------------------------------------------------------------------*/
    /* Show that stdout still works.                                         */
    /*-----------------------------------------------------------------------*/
    puts("hello, world on stdout\r\n");

    /*-----------------------------------------------------------------------*/
    /* Now reassign stdout to be a UART device!                              */
    /*-----------------------------------------------------------------------*/
    assert(freopen("uart:", "w", stdout) != NULL);

    /*-----------------------------------------------------------------------*/
    /* Now, writing to stdout actually writes to UART                        */
    /*-----------------------------------------------------------------------*/
    puts("hello, world on the new UART stdout\r\n");

    /*-----------------------------------------------------------------------*/
    /* All files are flushed when the program exits.                         */
    /*-----------------------------------------------------------------------*/
    return 0;
    /*-----------------------------------------------------------------------*/
    /* UART CONFIG END                                                       */
    /*-----------------------------------------------------------------------*/

}


void UartSetup()
{
    //
    // DEVICE_GPIO_PIN_SCIRXDA is the SCI Rx pin.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCIRXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_QUAL_ASYNC);

    //
    // DEVICE_GPIO_PIN_SCITXDA is the SCI Tx pin.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCITXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_QUAL_ASYNC);

    //
    // Initialize SCIA and its FIFO.
    //
    SCI_performSoftwareReset(SCIA_BASE);

    //
    // Configure SCIA with FIFO
    //
    SCI_setConfig(SCIA_BASE, DEVICE_LSPCLK_FREQ, 9600, (SCI_CONFIG_WLEN_8 |
                                                        SCI_CONFIG_STOP_ONE |
                                                        SCI_CONFIG_PAR_NONE));
    SCI_resetChannels(SCIA_BASE);
    SCI_resetRxFIFO(SCIA_BASE);
    SCI_resetTxFIFO(SCIA_BASE);
    SCI_enableFIFO(SCIA_BASE);
    SCI_enableModule(SCIA_BASE);
    SCI_performSoftwareReset(SCIA_BASE);
}

void UartPutChar(uint16_t charToWrite)
{
    SCI_writeCharBlockingFIFO(SCIA_BASE, charToWrite);
}

//
// End of File
//

