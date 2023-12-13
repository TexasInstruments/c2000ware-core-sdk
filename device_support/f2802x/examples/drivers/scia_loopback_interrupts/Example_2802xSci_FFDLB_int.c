//#############################################################################
//
//  File:   Example_F2802xSci_FFDLB_int.c
//
//  Title:  F2802x Device SCI Digital Loop Back program.
//
//! \addtogroup example_list
//!  <h1>SCI Digital Loop Back with Interrupts</h1>
//!
//!   This program is a SCI example that uses the internal loopback of
//!   the peripheral.  Both interrupts and the SCI FIFOs are used.
//!
//!   A stream of data is sent and then compared to the received stream.
//!
//!   The SCI-A sent data looks like this: \n
//!   00 01 \n
//!   01 02 \n
//!   02 03 \n
//!   ....  \n
//!   FE FF \n
//!   FF 00 \n
//!   etc..
//!
//!   The pattern is repeated forever.
//!
//!   Watch Variables:
//!   - sdataA - Data being sent
//!   - rdataA - Data received
//!   - rdata_pointA - Keep track of where we are in the datastream.
//!                    This is used to check the incoming data
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
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
//#############################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include <stdio.h>
#include <file.h>

#include "common/include/adc.h"
#include "common/include/clk.h"
#include "common/include/flash.h"
#include "common/include/gpio.h"
#include "common/include/pie.h"
#include "common/include/pll.h"
#include "common/include/sci.h"
#include "common/include/wdog.h"

//
// Defines
//

//
// Default = 40 MHz. Change to 50E6 for 50 MHz devices
//
#define CPU_FREQ     40E6
#define LSPCLK_FREQ CPU_FREQ/4
#define SCI_FREQ     100E3
#define SCI_PRD     (LSPCLK_FREQ/(SCI_FREQ*8))-1

//
// Function Prototypes
//
__interrupt void sciaTxFifoIsr(void);
__interrupt void sciaRxFifoIsr(void);
__interrupt void scibTxFifoIsr(void);
__interrupt void scibRxFifoIsr(void);
void scia_init(void);
void scia_fifo_init(void);
void error(void);

//
// Globals
//
uint16_t sdataA[2];    // Send data for SCI-A
uint16_t rdataA[2];    // Received data for SCI-A
uint16_t rdata_pointA; // Used for checking the received data

ADC_Handle myAdc;
CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;
SCI_Handle mySci;

//
// Main
//
void main(void)
{
    uint16_t i;

    CPU_Handle myCpu;
    PLL_Handle myPll;
    WDOG_Handle myWDog;

    //
    // Initialize all the handles needed for this application
    //
    myAdc = ADC_init((void *)ADC_BASE_ADDR, sizeof(ADC_Obj));
    myClk = CLK_init((void *)CLK_BASE_ADDR, sizeof(CLK_Obj));
    myCpu = CPU_init((void *)NULL, sizeof(CPU_Obj));
    myFlash = FLASH_init((void *)FLASH_BASE_ADDR, sizeof(FLASH_Obj));
    myGpio = GPIO_init((void *)GPIO_BASE_ADDR, sizeof(GPIO_Obj));
    myPie = PIE_init((void *)PIE_BASE_ADDR, sizeof(PIE_Obj));
    myPll = PLL_init((void *)PLL_BASE_ADDR, sizeof(PLL_Obj));
    mySci = SCI_init((void *)SCIA_BASE_ADDR, sizeof(SCI_Obj));
    myWDog = WDOG_init((void *)WDOG_BASE_ADDR, sizeof(WDOG_Obj));

    //
    // Perform basic system initialization
    //
    WDOG_disable(myWDog);
    CLK_enableAdcClock(myClk);
    (*Device_cal)();

    //
    // Select the internal oscillator 1 as the clock source
    //
    CLK_setOscSrc(myClk, CLK_OscSrc_Internal);

    //
    // Setup the PLL for x10 /2 which will yield 50Mhz = 10Mhz * 10 / 2
    //
    PLL_setup(myPll, PLL_Multiplier_10, PLL_DivideSelect_ClkIn_by_2);

    //
    // Disable the PIE and all interrupts
    //
    PIE_disable(myPie);
    PIE_disableAllInts(myPie);
    CPU_disableGlobalInts(myCpu);
    CPU_clearIntFlags(myCpu);

    //
    // If running from flash copy RAM only functions to RAM
    //
#ifdef _FLASH
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif

    //
    // Initialize GPIO
    //
    GPIO_setPullUp(myGpio, GPIO_Number_28, GPIO_PullUp_Enable);
    GPIO_setPullUp(myGpio, GPIO_Number_29, GPIO_PullUp_Disable);
    GPIO_setQualification(myGpio, GPIO_Number_28, GPIO_Qual_ASync);
    GPIO_setMode(myGpio, GPIO_Number_28, GPIO_28_Mode_SCIRXDA);
    GPIO_setMode(myGpio, GPIO_Number_29, GPIO_29_Mode_SCITXDA);

    //
    // Setup a debug vector table and enable the PIE
    //
    PIE_setDebugIntVectorTable(myPie);
    PIE_enable(myPie);

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;    // This is needed to write to EALLOW protected registers
    //PieVectTable.SCIRXINTA = &sciaRxFifoIsr;
    ((PIE_Obj *)myPie)->SCIRXINTA = &sciaRxFifoIsr;
    //PieVectTable.SCITXINTA = &sciaTxFifoIsr;
    ((PIE_Obj *)myPie)->SCITXINTA = &sciaTxFifoIsr;
    EDIS;      // This is needed to disable write to EALLOW protected registers

    //
    // Register interrupt handlers in the PIE vector table
    //
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_9, PIE_SubGroupNumber_1,
                              (intVec_t)&sciaRxFifoIsr);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_9, PIE_SubGroupNumber_2,
                              (intVec_t)&sciaTxFifoIsr);

    scia_init();                // Init SCI-A
    scia_fifo_init();           // Init SCI-A Fifos

    //
    // Init send data.  After each transmission this data will be updated for 
    // the next transmission
    //
    for(i = 0; i<2; i++)
    {
        sdataA[i] = i;
    }

    rdata_pointA = sdataA[0];

    //
    // Enable interrupts required for this example
    //
    PIE_enableInt(myPie, PIE_GroupNumber_9, PIE_InterruptSource_SCIARX);
    PIE_enableInt(myPie, PIE_GroupNumber_9, PIE_InterruptSource_SCIATX);

    CPU_enableInt(myCpu, CPU_IntNumber_9);
    CPU_enableGlobalInts(myCpu);

    for(;;)
    {
        
    }
}

//
// error -
//
void error(void)
{
    __asm(" ESTOP0");           // Test failed!! Stop!
    for (;;)
    {
        
    }
}

//
// sciaTxFifoIsr - 
//
__interrupt void
sciaTxFifoIsr(void)
{
    uint16_t i;
    for(i=0; i< 2; i++)
    {
        //
        // Send data
        //
        SCI_putDataBlocking(mySci, sdataA[i]);
    }

    for(i=0; i< 2; i++)
    {
        //
        // Increment send data for next cycle
        //
        sdataA[i] = (sdataA[i]+1) & 0x00FF;
    }

    //
    // Clear SCI Interrupt flag
    //
    SCI_clearTxFifoInt(mySci);

    //
    // Issue PIE ACK
    //
    PIE_clearInt(myPie, PIE_GroupNumber_9);

    return;
}

//
// sciaRxFifoIsr - 
//
__interrupt void
sciaRxFifoIsr(void)
{
    uint16_t i;

    if(SCI_getRxFifoStatus(mySci) != SCI_FifoLevel_Empty)
    {
        for(i=0;i<2;i++)
        {
            //
            // Read data
            //
            rdataA[i] = SCI_getData(mySci);
        }
        
        for(i=0;i<2;i++)
        {
            //
            // Check received data
            //
            if(rdataA[i] != ( (rdata_pointA+i) & 0x00FF) )
            {
                error();
            }
        }

        rdata_pointA = (rdata_pointA+1) & 0x00FF;
    }

    //
    // Clear Overflow flag
    //
    SCI_clearRxFifoOvf(mySci);

    //
    // Clear Interrupt flag
    //
    SCI_clearRxFifoInt(mySci);

    //
    // Issue PIE ack
    //
    PIE_clearInt(myPie, PIE_GroupNumber_9);

    return;
}

//
// scia_init - 
//
void
scia_init()
{
    CLK_enableSciaClock(myClk);

    //
    // 1 stop bit,  No loopback, No parity, 8 char bits, async mode
    // idle-line protocol
    //
    SCI_disableParity(mySci);
    SCI_setNumStopBits(mySci, SCI_NumStopBits_One);
    SCI_setCharLength(mySci, SCI_CharLength_8_Bits);

    //
    // enable TX, RX, internal SCICLK, Disable RX ERR, SLEEP, TXWAKE
    //
    SCI_enableTx(mySci);
    SCI_enableRx(mySci);
    SCI_enableTxInt(mySci);
    SCI_enableRxInt(mySci);

    SCI_enableLoopBack(mySci);

    //SCI BRR = LSPCLK/(SCI BAUDx8) - 1
#if (CPU_FRQ_50MHZ)
    SCI_setBaudRate(mySci, SCI_BaudRate_9_6_kBaud);
#elif (CPU_FRQ_40MHZ)
    SCI_setBaudRate(mySci, (SCI_BaudRate_e)129);
#endif

    SCI_enable(mySci);

    return;
}

//
// scia_fifo_init - 
//
void
scia_fifo_init()
{
    SCI_enableFifoEnh(mySci);
    SCI_resetTxFifo(mySci);
    SCI_clearTxFifoInt(mySci);
    SCI_resetChannels(mySci);
    SCI_setTxFifoIntLevel(mySci, SCI_FifoLevel_2_Words);
    SCI_enableTxFifoInt(mySci);

    SCI_resetRxFifo(mySci);
    SCI_clearRxFifoInt(mySci);
    SCI_setRxFifoIntLevel(mySci, SCI_FifoLevel_2_Words);
    SCI_enableRxFifoInt(mySci);

    return;
}

//
// End of File
//

