//#############################################################################
//
//  File:   Example_F2802xSpi_FFDLB.c
//
//  Title:  F2802x Device Spi Digital Loop Back program.
//
//! \addtogroup example_list
//!  <h1>SPI Digital Loop Back</h1>
//!
//!   This program is a SPI example that uses the internal loopback of
//!   the peripheral.  Interrupts are not used.
//!
//!   A stream of data is sent and then compared to the received stream.
//!
//!   The sent data looks like this:
//!   0000 0001 0002 0003 0004 0005 0006 0007 .... FFFE FFFF
//!
//!   This pattern is repeated forever.
//!
//!   Watch Variables:
//!   - sdata - sent data
//!   - rdata - received data
//
//#############################################################################
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
#include "common/include/spi.h"
#include "common/include/wdog.h"

//
// Defines
//
//
// Length of the word being sent
//
#define CHAR_LENGTH     SPI_CharLength_16_Bits
#define CHAR_MAX        (0xFFFF >> (SPI_CharLength_16_Bits - CHAR_LENGTH))

//
// Function Prototypes
//
void delay_loop(void);
void spi_xmit(uint16_t a);
void spi_fifo_init(void);
void spi_init(void);
void error(void);

ADC_Handle myAdc;
CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;
SPI_Handle mySpi;

//
// Main
//
void main(void)
{
    uint16_t sdata;         // send data
    uint16_t rdata;         // received data

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
    mySpi = SPI_init((void *)SPIA_BASE_ADDR, sizeof(SPI_Obj));
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
    GPIO_setPullUp(myGpio, GPIO_Number_16, GPIO_PullUp_Enable);
    GPIO_setPullUp(myGpio, GPIO_Number_17, GPIO_PullUp_Enable);
    GPIO_setPullUp(myGpio, GPIO_Number_18, GPIO_PullUp_Enable);
    GPIO_setPullUp(myGpio, GPIO_Number_19, GPIO_PullUp_Enable);
    GPIO_setQualification(myGpio, GPIO_Number_16, GPIO_Qual_ASync);
    GPIO_setQualification(myGpio, GPIO_Number_17, GPIO_Qual_ASync);
    GPIO_setQualification(myGpio, GPIO_Number_18, GPIO_Qual_ASync);
    GPIO_setQualification(myGpio, GPIO_Number_19, GPIO_Qual_ASync);
    GPIO_setMode(myGpio, GPIO_Number_16, GPIO_16_Mode_SPISIMOA);
    GPIO_setMode(myGpio, GPIO_Number_17, GPIO_17_Mode_SPISOMIA);
    GPIO_setMode(myGpio, GPIO_Number_18, GPIO_18_Mode_SPICLKA);
    GPIO_setMode(myGpio, GPIO_Number_19, GPIO_19_Mode_SPISTEA_NOT);

    //
    // Setup a debug vector table and enable the PIE
    //
    PIE_setDebugIntVectorTable(myPie);
    PIE_enable(myPie);

    spi_init();                  // Initialize SPI
    spi_fifo_init();             // Initialize the SPI FIFOs

    sdata = 0x0000;

    for(;;)
    {
        //
        // Transmit data. Note that when character length is less than 16, the
        // data must be left shifted.
        //
        SPI_write(mySpi, (sdata << (SPI_CharLength_16_Bits - CHAR_LENGTH)));

        //
        // Wait until data is received
        //
        while(SPI_getRxFifoStatus(mySpi) == SPI_FifoStatus_Empty)
        {

        }

        //
        // Check against sent data
        //
        rdata = SPI_read(mySpi);
        if(rdata != sdata)
        {
            error();
        }

        //
        // Increment sdata and make sure it is never out of range for the given
        // character length.
        //
        if(sdata != CHAR_MAX)
        {
            sdata++;
        }
        else
        {
            sdata = 0;
        }

    }
}

//
// delay_loop -
//
void
delay_loop()
{
    long      i;

    for (i = 0; i < 1000000; i++)
    {

    }

    return;
}

//
// error -
//
void
error(void)
{
    __asm(" ESTOP0");     // Test failed!! Stop!
    for (;;)
    {

    }
}

//
// spi_init -
//
void
spi_init()
{
    CLK_enableSpiaClock(myClk);

    //
    // Reset on, rising edge, 16-bit char bits
    //
    SPI_setCharLength(mySpi, CHAR_LENGTH);

    //
    // Enable master mode, normal phase, enable talk, and SPI int disabled.
    //
    SPI_setMode(mySpi, SPI_Mode_Master);
    SPI_enableTx(mySpi);

    SPI_setBaudRate(mySpi, SPI_BaudRate_1_MBaud);

    //
    // Relinquish SPI from Reset
    //
    SPI_enableLoopBack(mySpi);
    SPI_enable(mySpi);

    //
    // Set so breakpoints don't disturb xmission
    //
    SPI_setPriority(mySpi, SPI_Priority_FreeRun);

    return;
}

//
// spi_fifo_init -
//
void
spi_fifo_init()
{
    //
    // Initialize SPI FIFO registers
    //
    SPI_enableChannels(mySpi);
    SPI_enableFifoEnh(mySpi);
    SPI_resetTxFifo(mySpi);
    SPI_clearTxFifoInt(mySpi);
    SPI_resetRxFifo(mySpi);
    SPI_clearRxFifoInt(mySpi);
    SPI_setRxFifoIntLevel(mySpi, SPI_FifoLevel_4_Words);

    return;
}

//
// End of File
//

