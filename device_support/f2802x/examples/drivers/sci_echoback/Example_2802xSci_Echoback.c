//#############################################################################
//
//  File:   Example_F2802xSci_Echoback.c
//
//  Title:  F2802x Device SCI Echoback.
//
//! \addtogroup example_list
//!  <h1>SCI Echoback</h1>
//!
//!   This test receives and echo-backs data through the SCI-A port.
//!
//!   -# Configure hyperterminal:
//!      Use the included hyperterminal configuration file SCI_96.ht.
//!      To load this configuration in hyperterminal: file->open
//!      and then select the SCI_96.ht file.
//!   -# Check the COM port.
//!      The configuration file is currently setup for COM1.
//!      If this is not correct, disconnect Call->Disconnect
//!      Open the File-Properties dialog and select the correct COM port.
//!   -# Connect hyperterminal Call->Call
//!      and then start the 2802x SCI echoback program execution.
//!   -# The program will print out a greeting and then ask you to
//!      enter a character which it will echo back to hyperterminal.
//!
//!   Watch Variables:
//!   - LoopCount for the number of characters sent
//!   - ErrorCount
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
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
//#############################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

#include "common/include/adc.h"
#include "common/include/clk.h"
#include "common/include/flash.h"
#include "common/include/gpio.h"
#include "common/include/pie.h"
#include "common/include/pll.h"
#include "common/include/sci.h"
#include "common/include/wdog.h"

//
// Functions Prototypes
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
    uint16_t ReceivedChar;
    char *msg;

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
    PLL_setup(myPll, PLL_Multiplier_12, PLL_DivideSelect_ClkIn_by_2);

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

    LoopCount = 0;
    ErrorCount = 0;

    scia_echoback_init();           // Initialize SCI for echoback
    scia_fifo_init();               // Initialize the SCI FIFO

    msg = "\r\n\n\nHello World!\0";
    scia_msg(msg);

    msg = "\r\nYou will enter a character, and the DSP will echo it \
          back! \n\0";
    scia_msg(msg);

    for(;;)
    {
        msg = "\r\nEnter a character: \0";
        scia_msg(msg);

        //
        // Wait for inc character
        //
        while(SCI_getRxFifoStatus(mySci) < SCI_FifoStatus_1_Word)
        {
            
        }

        //
        // Get character
        //
        ReceivedChar = SCI_getData(mySci);

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
// scia_echoback_init - Test 1, SCIA  DLB, 8-bit word, baud rate 0x000F,
// default, 1 STOP bit, no parity
//
void
scia_echoback_init()
{
    CLK_enableSciaClock(myClk);

    //
    // 1 stop bit,  No loopback, No parity,8 char bits, async mode, 
    // idle-line protocol
    //
    SCI_disableParity(mySci);
    SCI_setNumStopBits(mySci, SCI_NumStopBits_One);
    SCI_setCharLength(mySci, SCI_CharLength_8_Bits);

    SCI_enableTx(mySci);
    SCI_enableRx(mySci);
    SCI_enableTxInt(mySci);
    SCI_enableRxInt(mySci);

    //SCI BRR = LSPCLK/(SCI BAUDx8) - 1
#if (CPU_FRQ_60MHZ)
    SCI_setBaudRate(mySci, (SCI_BaudRate_e)194);
#elif (CPU_FRQ_50MHZ)
    SCI_setBaudRate(mySci, (SCI_BaudRate_e)162);
#elif (CPU_FRQ_40MHZ)
    SCI_setBaudRate(mySci, (SCI_BaudRate_e)129);
#endif

    SCI_enable(mySci);

    return;
}

//
// scia_xmit - Transmit a character from the SCI
//
void
scia_xmit(int a)
{
    while(SCI_getTxFifoStatus(mySci) != SCI_FifoStatus_Empty)
    {
        
    }

    SCI_putDataBlocking(mySci, a);
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
    SCI_enableFifoEnh(mySci);
    SCI_resetTxFifo(mySci);
    SCI_clearTxFifoInt(mySci);
    SCI_resetChannels(mySci);
    SCI_setTxFifoIntLevel(mySci, SCI_FifoLevel_Empty);

    SCI_resetRxFifo(mySci);
    SCI_clearRxFifoInt(mySci);
    SCI_setRxFifoIntLevel(mySci, SCI_FifoLevel_4_Words);

    return;
}

//
// End of File
//

