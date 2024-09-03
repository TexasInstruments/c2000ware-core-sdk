// #############################################################################
//
//  FILE:   i2c_ex7_clock_stretching_controller_tx.c
//
//  TITLE:  I2C Extended Clock Stretching Controller TX
//
//! \addtogroup driver_example_list
//! <h1>I2C Extended Clock Stretching Controller TX</h1>
//!
//! This program uses the extended clock stretching mode of the I2C module. Both
//! the TX and RX I2C Non-FIFOs and their interrupts are used.
//!
//! A stream of data is sent and then compared to the received stream.
//!
// #############################################################################
//
//
//  
// C2000Ware v5.03.00.00
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
// #############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Defines
//
#define TARGET_ADDRESS (0x3C)
#define NUM_I2C_DATA (4)
#define I2CA_SDA_CURRENT (42)
#define I2CA_SCL_CURRENT (43)

//
// Globals
//
uint16_t txData = 0, rxData = 0;
uint16_t pui32DataTx[NUM_I2C_DATA], pui32DataRx[NUM_I2C_DATA];
volatile uint16_t waitForInt = 4;
uint16_t ui32Index = 0, ui32Index_1 = 0, error = 0;
volatile uint16_t I2C_Int = 1;
int status1 = 0;

//
// Function Prototypes
//
__interrupt void INT_I2CA_ISR(void);
void INTERRUPT_init(void);
void I2C_init(void);
void All_Interrupt_PIE_Enable(void);
void Pinmux_init(void);

//
// Main
//
void main(void)
{
    EALLOW;

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

    Pinmux_init();
    INTERRUPT_init();
    I2C_init();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    I2C_sendStartCondition(I2CA_BASE);
    while (I2C_Int)
    {
        if (waitForInt == 0)
        {
            I2C_Int = 0;
        }
    }
    I2C_sendStopCondition(I2CA_BASE);
    if (error == 0)
    {
        status1 = 1;
    }
    else
    {
        status1 = 0;
    }
    EDIS;
}

//
// I2C A Transmit & Receive ISR.
//

__interrupt void INT_I2CA_ISR(void)
{
    waitForInt = waitForInt - 1;
    txData = ui32Index;
    I2C_putData(I2CA_BASE, txData + 1);
    pui32DataTx[ui32Index] = txData + 1;
    ui32Index++;

    INTERRUPT_init();
}

void I2C_init()
{
    I2C_disableModule(I2CA_BASE);
    I2C_initController(I2CA_BASE, DEVICE_SYSCLK_FREQ, 400000, I2C_DUTYCYCLE_50);
    I2C_setConfig(I2CA_BASE, I2C_CONTROLLER_SEND_MODE);
    I2C_setTargetAddress(I2CA_BASE, TARGET_ADDRESS);
    I2C_disableLoopback(I2CA_BASE);
    I2C_setOwnAddress(I2CA_BASE, 0);
    I2C_setBitCount(I2CA_BASE, I2C_BITCOUNT_8);
    I2C_setAddressMode(I2CA_BASE, I2C_ADDR_MODE_7BITS);
    I2C_setDataCount(I2CA_BASE, NUM_I2C_DATA);
    I2C_disableFIFO(I2CA_BASE);
    I2C_clearInterruptStatus(I2CA_BASE, I2C_INT_TX_DATA_RDY);
    I2C_enableInterrupt(I2CA_BASE, I2C_INT_TX_DATA_RDY);
    I2C_setEmulationMode(I2CA_BASE, I2C_EMULATION_FREE_RUN);
    I2C_enableModule(I2CA_BASE);
}

void INTERRUPT_init()
{
    Interrupt_disable(INT_I2CA);
    Interrupt_register(INT_I2CA, &INT_I2CA_ISR);
    Interrupt_enable(INT_I2CA);
}

void Pinmux_init()
{
    GPIO_setPinConfig(GPIO_42_I2CA_SDA);
    GPIO_setPadConfig(I2CA_SDA_CURRENT, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(I2CA_SDA_CURRENT, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(GPIO_43_I2CA_SCL);
    GPIO_setPadConfig(I2CA_SCL_CURRENT, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(I2CA_SCL_CURRENT, GPIO_QUAL_ASYNC);
}
//
// End of File
//
