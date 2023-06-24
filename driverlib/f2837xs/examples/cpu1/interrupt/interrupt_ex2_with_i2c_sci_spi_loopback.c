//#############################################################################
//
// FILE:   interrupt_ex2_with_i2c_sci_spi_loopback.c
//
// TITLE:  Multiple interrupt handling of I2C, SCI & SPI Digital Loopback
//
//! \addtogroup driver_example_list
//! <h1>Multiple interrupt handling of I2C, SCI & SPI Digital Loopback</h1>
//!
//! This program is used to demonstrate how to handle multiple interrupts
//! when using multiple communication peripherals like I2C, SCI & SPI
//! Digital Loopback all in a single example. The data transfers would
//! be done with FIFO Interrupts.
//!
//! It uses the internal loopback test mode of these modules. Both
//! the TX and RX FIFOs and their interrupts are used.
//! Other than boot mode pin configuration, no other hardware configuration
//! is required.
//!
//! A stream of data is sent and then compared to the received stream.
//! The sent data looks like this for I2C and SCI: \n
//!  0000 0001 \n
//!  0001 0002 \n
//!  0002 0003 \n
//!  .... \n
//!  00FE 00FF \n
//!  00FF 0000 \n
//!  etc.. \n
//!
//! The sent data looks like this for SPI: \n
//!  0000 0001 \n
//!  0001 0002 \n
//!  0002 0003 \n
//!  .... \n
//!  FFFE FFFF \n
//!  FFFF 0000 \n
//!  etc.. \n
//!
//! This pattern is repeated forever.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b sDatai2cA - Data to send through I2C
//!  - \b rDatai2cA - Received I2C data
//!  - \b rDataPoint - Used to keep track of the last position in the receive
//!    I2C stream for error checking
//!
//!  - \b sDataspiA - Data to send through SPI
//!  - \b rDataspiA - Received SPI data
//!  - \b rDataPointspiA - Used to keep track of the last position in the receive
//!    SPI stream for error checking
//!
//!  - \b sDatasciA - SCI Data being sent
//!  - \b rDatasciA - SCI Data received
//!  - \b rDataPointA - Keep track of where we are in the SCI data stream.
//!    This is used to check the incoming data
//!
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define SLAVE_ADDRESS   0x3C

//
// Globals
//

//
// I2C data Globals
//
uint16_t sDatai2cA[2];                  // Send I2CA data buffer
uint16_t rDatai2cA[2];                  // Receive I2CA data buffer
uint16_t rDataPoint = 0;            // To keep track of where we are in the
                                    // data stream to check received I2C data
//
// SCI data Globals
//
uint16_t sDatasciA[2];              // Send SCI-A data buffer
uint16_t rDatasciA[2];              // Receive SCI-A data buffer
uint16_t rDataPointA = 0;           // Used for checking the received SCI data

//
// SPI data Globals
//
uint16_t sDataspiA[2];                  // Send SPI data buffer
uint16_t rDataspiA[2];                  // Receive SPI data buffer
uint16_t rDataPointspiA = 0;            // To keep track of where we are in the
                                    // data stream to check received SPI data
//
// Function Prototypes
//
void initI2CFIFO(void);
__interrupt void i2cFIFOISR(void);
__interrupt void sciaTXFIFOISR(void);
__interrupt void sciaRXFIFOISR(void);
void initSCIAFIFO(void);
void initSPIFIFO(void);
__interrupt void spiTxFIFOISR(void);
__interrupt void spiRxFIFOISR(void);

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
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

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
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_I2CA_FIFO, &i2cFIFOISR);
    Interrupt_register(INT_SCIA_RX, &sciaRXFIFOISR);
    Interrupt_register(INT_SCIA_TX, &sciaTXFIFOISR);
    Interrupt_register(INT_SPIA_TX, &spiTxFIFOISR);
    Interrupt_register(INT_SPIA_RX, &spiRxFIFOISR);

    //
    // Set I2C use, initializing it for FIFO mode
    //
    initI2CFIFO();

    //
    // Set SCI use, initializing it for FIFO mode
    //
    initSCIAFIFO();

    //
    // Set up SPI, initializing it for FIFO mode
    //
    initSPIFIFO();

    //
    // Initialize the I2C data buffers
    //
    for(i = 0; i < 2; i++)
    {
        sDatai2cA[i] = i;
        rDatai2cA[i]= 0;
    }

    //
    // Init the SCI send data.  After each transmission this data
    // will be updated for the next transmission
    //
    for(i = 0; i < 2; i++)
    {
        sDatasciA[i] = i;
    }

    //
    // Initialize the SPI data buffers
    //
    for(i = 0; i < 2; i++)
    {
        sDataspiA[i] = i;
        rDataspiA[i]= 0;
    }

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_I2CA_FIFO);
    Interrupt_enable(INT_SCIA_RX);
    Interrupt_enable(INT_SCIA_TX);
    Interrupt_enable(INT_SPIA_TX);
    Interrupt_enable(INT_SPIA_RX);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    while(1)
    {
     // A FIFO interrupt will be generated for each Tx and Rx based
     // on the Interrupt levels configured for each of the modules.
    }
}

//
// Function to configure I2C A in FIFO mode.
//
void initI2CFIFO()
{
    //
    // Must put I2C into reset before configuring it
    //
    I2C_disableModule(I2CA_BASE);

    //
    // I2C configuration. Use a 400kHz I2CCLK with a 50% duty cycle.
    //
    I2C_initMaster(I2CA_BASE, DEVICE_SYSCLK_FREQ, 400000, I2C_DUTYCYCLE_50);
    I2C_setConfig(I2CA_BASE, I2C_MASTER_SEND_MODE);
    I2C_setDataCount(I2CA_BASE, 2);
    I2C_setBitCount(I2CA_BASE, I2C_BITCOUNT_8);

    //
    // Configure for internal loopback mode
    //
    I2C_setSlaveAddress(I2CA_BASE, SLAVE_ADDRESS);
    I2C_setOwnSlaveAddress(I2CA_BASE, SLAVE_ADDRESS);
    I2C_enableLoopback(I2CA_BASE);
    I2C_setEmulationMode(I2CA_BASE, I2C_EMULATION_STOP_SCL_LOW);

    //
    // FIFO and interrupt configuration
    //
    I2C_enableFIFO(I2CA_BASE);
    I2C_clearInterruptStatus(I2CA_BASE, I2C_INT_RXFF | I2C_INT_TXFF);

    //
    // Transmit FIFO interrupt levels are set to generate an interrupt
    // when the 16 byte TX fifo contains 2 or lesser bytes of data.
    // Receive FIFO interrupt levels are set to generate an interrupt
    // when the 16 byte RX fifo contains 2 or greater bytes of data.
    //
    I2C_setFIFOInterruptLevel(I2CA_BASE, I2C_FIFO_TX2, I2C_FIFO_RX2);
    I2C_enableInterrupt(I2CA_BASE, I2C_INT_RXFF | I2C_INT_TXFF);

    //
    // Configuration complete. Enable the module.
    //
    I2C_enableModule(I2CA_BASE);
}

//
// I2C A Transmit & Receive FIFO ISR.
// The ISR will handle pushing/pulling data to/from the TX and
// RX FIFOs resp.
//
 __interrupt void i2cFIFOISR(void)
{
    uint16_t i;

    //
    // If receive FIFO interrupt flag is set, read data
    //
    if((I2C_getInterruptStatus(I2CA_BASE) & I2C_INT_RXFF) != 0)
    {
        for(i = 0; i < 2; i++)
        {
            rDatai2cA[i] = I2C_getData(I2CA_BASE);
        }

        //
        // Check received data
        //
        for(i = 0; i < 2; i++)
        {
            if(rDatai2cA[i] != ((rDataPoint + i) & 0xFF))
            {
                //
                // Something went wrong. rDatai2cA doesn't contain expected data.
                //
                ESTOP0;
            }
        }

        rDataPoint = (rDataPoint + 1) & 0xFF;

        //
        // Clear interrupt flag
        //
        I2C_clearInterruptStatus(I2CA_BASE, I2C_INT_RXFF);
    }
    //
    // If transmit FIFO interrupt flag is set, put data in the buffer
    //
    else if((I2C_getInterruptStatus(I2CA_BASE) & I2C_INT_TXFF) != 0)
    {
        for(i = 0; i < 2; i++)
        {
            I2C_putData(I2CA_BASE, sDatai2cA[i]);
        }

        //
        // Send the start condition
        //
        I2C_sendStartCondition(I2CA_BASE);

        //
        // Increment data for next cycle
        //
        for(i = 0; i < 2; i++)
        {
           sDatai2cA[i] = (sDatai2cA[i] + 1) & 0xFF;
        }

        //
        // Clear interrupt flag
        //
        I2C_clearInterruptStatus(I2CA_BASE, I2C_INT_TXFF);
    }

    //
    // Issue ACK
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

 //
 // sciaTXFIFOISR - SCIA Transmit FIFO ISR
 //
 __interrupt void sciaTXFIFOISR(void)
 {
     uint16_t i;

     SCI_writeCharArray(SCIA_BASE, sDatasciA, 2);

     //
     // Increment send data for next cycle
     //
     for(i = 0; i < 2; i++)
     {
         sDatasciA[i] = (sDatasciA[i] + 1) & 0x00FF;
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

     SCI_readCharArray(SCIA_BASE, rDatasciA, 2);

     //
     // Check received data
     //
     for(i = 0; i < 2; i++)
     {
         if(rDatasciA[i] != ((rDataPointA + i) & 0x00FF))
         {
             //
             // Something went wrong. rDatasciA doesn't contain expected data.
             //
             ESTOP0;
         }
     }

     rDataPointA = (rDataPointA + 1) & 0x00FF;

     SCI_clearOverflowStatus(SCIA_BASE);

     SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_RXFF);

     //
     // Issue PIE ack
     //
     Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
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

     //
     // The transmit FIFO generates an interrupt when FIFO status
     // bits are less than or equal to 2 out of 16 words
     // The receive FIFO generates an interrupt when FIFO status
     // bits are greater than equal to 2 out of 16 words
     //
     SCI_setFIFOInterruptLevel(SCIA_BASE, SCI_FIFO_TX2, SCI_FIFO_RX2);
     SCI_performSoftwareReset(SCIA_BASE);

     SCI_resetTxFIFO(SCIA_BASE);
     SCI_resetRxFIFO(SCIA_BASE);
 }

 //
 // Function to configure SPI A in FIFO mode.
 //
 void initSPIFIFO()
 {
     //
     // Must put SPI into reset before configuring it
     //
     SPI_disableModule(SPIA_BASE);

     //
     // SPI configuration. Use a 500kHz SPICLK and 16-bit word size.
     //
     SPI_setConfig(SPIA_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0,
                   SPI_MODE_MASTER, 500000, 16);
     SPI_enableLoopback(SPIA_BASE);
     SPI_setEmulationMode(SPIA_BASE, SPI_EMULATION_STOP_AFTER_TRANSMIT);

     //
     // FIFO and interrupt configuration
     //
     SPI_enableFIFO(SPIA_BASE);
     SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF | SPI_INT_TXFF);
     SPI_setFIFOInterruptLevel(SPIA_BASE, SPI_FIFO_TX2, SPI_FIFO_RX2);
     SPI_enableInterrupt(SPIA_BASE, SPI_INT_RXFF | SPI_INT_TXFF);

     //
     // Configuration complete. Enable the module.
     //
     SPI_enableModule(SPIA_BASE);
 }

 //
 // SPI A Transmit FIFO ISR
 //
 __interrupt void spiTxFIFOISR(void)
 {
     uint16_t i;

     //
     // Send data
     //
     for(i = 0; i < 2; i++)
     {
        SPI_writeDataNonBlocking(SPIA_BASE, sDataspiA[i]);
     }

     //
     // Increment data for next cycle
     //
     for(i = 0; i < 2; i++)
     {
        sDataspiA[i] = sDataspiA[i] + 1;
     }

     //
     // Clear interrupt flag and issue ACK
     //
     SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_TXFF);
     Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP6);
 }

 //
 // SPI A Receive FIFO ISR
 //
  __interrupt void spiRxFIFOISR(void)
 {
     uint16_t i;

     //
     // Read data
     //
     for(i = 0; i < 2; i++)
     {
         rDataspiA[i] = SPI_readDataNonBlocking(SPIA_BASE);
     }

     //
     // Check received data
     //
     for(i = 0; i < 2; i++)
     {
         if(rDataspiA[i] != (rDataPointspiA + i))
         {
             // Something went wrong. rDataspiA doesn't contain expected data.
             ESTOP0;
         }
     }

     rDataPointspiA++;

     //
     // Clear interrupt flag and issue ACK
     //
     SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF);
     Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP6);
 }

//
// End of File
//

