//#############################################################################
//
//  File:   Example_F2802xSpi_FFDLB_int.c
//
//  Title:  F2802x Device Spi Digital Loop Back with Interrupts Example.
//
//! \addtogroup example_list
//!  <h1>SPI Digital Loop Back with Interrupts</h1>
//!
//!   This program is a SPI-A example that uses the internal loopback of
//!   the peripheral.  Both interrupts and the SPI FIFOs are used.
//!
//!   A stream of data is sent and then compared to the received stream.
//!
//!   The sent data looks like this:
//!   0000 0001 \n
//!   0001 0002 \n
//!   0002 0003 \n
//!   ....      \n
//!   FFFE FFFF \n
//!   FFFF 0000 \n
//!    etc..
//!
//!   This pattern is repeated forever.
//!
//!
//!   Watch Variables:
//!   - sdata[2] - Data to send
//!   - rdata[2] - Received data
//!   - rdata_point - Used to keep track of the last position in
//!                   the receive stream for error checking.
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
// Length of the word being sent
//
#define CHAR_LENGTH     SPI_CharLength_16_Bits
#define CHAR_MAX        (0xFFFF >> (SPI_CharLength_16_Bits - CHAR_LENGTH))

//
// Function Prototypes
//
__interrupt void spiTxFifoIsr(void);
__interrupt void spiRxFifoIsr(void);
void delay_loop(void);
void spi_init(void);
void spi_fifo_init(void);
void error();

//
// Globals
//
uint16_t sdata[2];      // Send data buffer
uint16_t rdata[2];      // Receive data buffer

//
// Keep track of where we are in the data stream to check received data
//
uint16_t rdata_point;

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
    mySpi = SPI_init((void *)SPIA_BASE_ADDR, sizeof(SPI_Obj));
    myWDog = WDOG_init((void *)WDOG_BASE_ADDR, sizeof(WDOG_Obj));

    //
    // Perform basic system initialization
    //
    WDOG_disable(myWDog);
    CLK_enableAdcClock(myClk);
    (*Device_cal)();

    //
    // Enable SPI-A Clock
    //
    CLK_enableSpiaClock(myClk);

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

    //
    // Register interrupt handlers in the PIE vector table
    //
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_6, PIE_SubGroupNumber_1,
                              (intVec_t)&spiRxFifoIsr);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_6, PIE_SubGroupNumber_2,
                              (intVec_t)&spiTxFifoIsr);

    //
    // Initialize the SPI only
    //
    spi_init();

    //
    // Initialize the send data buffer
    //
    for(i=0; i<2; i++)
    {
        sdata[i] = i;
    }
    rdata_point = 0;

    //
    // Enable interrupts required for this example
    //
    PIE_enableInt(myPie, PIE_GroupNumber_6, PIE_InterruptSource_SPIARX);
    PIE_enableInt(myPie, PIE_GroupNumber_6, PIE_InterruptSource_SPIATX);
    CPU_enableInt(myCpu, CPU_IntNumber_6);
    CPU_enableGlobalInts(myCpu);

    for(;;)
    {
        __asm(" NOP");
    }
}

//
// delay_loop - Some Useful local functions
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
    __asm("     ESTOP0");     //Test failed!! Stop!
    for (;;)
    {
        __asm(" NOP");
    }
}

//
// spi_init -
//
void
spi_init()
{
    SPI_reset(mySpi);
    SPI_enable(mySpi);

    //
    // Reset on, rising edge, 16-bit char bits
    //
    SPI_setCharLength(mySpi, CHAR_LENGTH);
    SPI_enableLoopBack(mySpi);

    //
    // Enable master mode, normal phase, enable talk, and SPI int disabled.
    //
    SPI_setMode(mySpi, SPI_Mode_Master);
    SPI_enableTx(mySpi);
    SPI_enableOverRunInt(mySpi);
    SPI_enableInt(mySpi);

    SPI_setBaudRate(mySpi, (SPI_BaudRate_e)0x63);

    //
    // Initialize SPI FIFO registers
    //
    SPI_enableFifoEnh(mySpi);
    SPI_enableChannels(mySpi);
    SPI_resetTxFifo(mySpi);
    SPI_clearTxFifoInt(mySpi);
    SPI_setTxFifoIntLevel(mySpi, SPI_FifoLevel_2_Words);
    SPI_enableTxFifoInt(mySpi);

    SPI_resetRxFifo(mySpi);
    SPI_setRxFifoIntLevel(mySpi, SPI_FifoLevel_2_Words);
    SPI_enableRxFifoInt(mySpi);
    SPI_clearRxFifoInt(mySpi);

    SPI_setTxDelay(mySpi, 0);

    //
    // Set so breakpoints don't disturb xmission
    //
    SPI_setPriority(mySpi, SPI_Priority_FreeRun);

    SPI_enable(mySpi);

    SPI_enableTxFifo(mySpi);
    SPI_enableRxFifo(mySpi);
}

//
// spiTxFifoIsr -
//
__interrupt void
spiTxFifoIsr(void)
{
    uint16_t i;

    for(i=0;i<2;i++)
    {
        //
        // Send data. Note that when character length is less than 16, the
        // data must be left shifted.
        //
        SPI_write(mySpi, (sdata[i] << (SPI_CharLength_16_Bits - CHAR_LENGTH)));
    }

    for(i=0;i<2;i++)
    {
        //
        // Increment data for next cycle and make sure it is never out of range
        // for the given character length.
        //
        if(sdata[i] != CHAR_MAX)
        {
            sdata[i]++;
        }
        else
        {
            sdata[i] = 0;
        }
    }

    //
    // Clear Interrupt flag
    //
    SPI_clearTxFifoInt(mySpi);

    //
    // Issue PIE ACK
    //
    PIE_clearInt(myPie, PIE_GroupNumber_6);

    return;
}

//
// spiRxFifoIsr -
//
__interrupt void
spiRxFifoIsr(void)
{
    uint16_t i;

    if(SPI_getRxFifoStatus(mySpi) != SPI_FifoLevel_Empty)
    {
        for(i=0;i<2;i++)
        {
            //
            // Read data
            //
            rdata[i] = SPI_read(mySpi);
        }

        for(i=0;i<2;i++)
        {
            //
            // Check received data
            //
            if(rdata[i] != ((rdata_point + i) & CHAR_MAX))
            {
                error();
            }
        }

        rdata_point++;
    }

    //
    // Clear Overflow flag
    //
    SPI_clearRxFifoOvf(mySpi);

    //
    // Clear Interrupt flag
    //
    SPI_clearRxFifoInt(mySpi);

    //
    // Issue PIE ack
    //
    PIE_clearInt(myPie, PIE_GroupNumber_6);

    return;
}

//
// End of File
//

