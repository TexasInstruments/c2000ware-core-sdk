//###########################################################################
//
// FILE:    Example_F2802xLaunchPadDemo.c
//
// TITLE:   F2802x LaunchPad Demo (This example comes pre-loaded on the controlPad)
//
// ASSUMPTIONS:
//
//    This program requires the F2802x header files.
//
//    This program makes use of variables stored in OTP during factory
//    test on 2802x TMS devices only.
//    These OTP locations on pre-TMS devices may not be populated.
//    Ensure that the following memory locations in TI OTP are populated
//    (not 0xFFFF) before use:
//
//    0x3D7E90 to 0x3D7EA4
//
//    As supplied, this project is configured for "boot to SARAM"
//    operation.  The 2802x Boot Mode table is shown below.
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
//! \addtogroup example_list
//!  <h1>LaunchPad Demo</h1>
//!
//!  This program is the demo program that comes pre-loaded on the LaunchPad
//!  development kit.  The program starts by flashing the 4 bit binary display.
//!  When the user pushes S3 (GPIO12) the demo then stops flashing the display
//!  and samples the device's internal temperature sensor to establish a 
//!  reference.  After this, the board displays a value of 0x08 and displays 
//!  any increase or decrease in temperature as a delta on the display.  So for
//!  instance if the temperature was initially 20C and now it is 22C, the value
//!  on the display would be 22C - 20C + 8 = 10 = 0x0A = 0b1010.  Additionally,
//!  the reference temperature may be reset to the current value by pressing 
//!  and holding S3.
//!
//!    Watch Variables:
//!    - referenceTemp
//!    - currentTemp
//!
//
//###########################################################################
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
//###########################################################################

//
// Included Files
//
#include <stdio.h>
#include <file.h>

#include "DSP28x_Project.h"     // DSP28x Headerfile
#include "ti_ascii.h"

#include "adc.h"
#include "clk.h"
#include "flash.h"
#include "gpio.h"
#include "pie.h"
#include "pll.h"
#include "sci.h"
#include "sci_io.h"
#include "wdog.h"

//
// Defines
//

//
// Micro-seconds to wait for ADC conversion. Longer than necessary.
//
#define CONV_WAIT 1L

//
// Globals
//
extern void DSP28x_usDelay(Uint32 Count);

static unsigned short indexX=0;
static unsigned short indexY=0;

const unsigned char escRed[] = {0x1B, 0x5B, '3','1', 'm'};
const unsigned char escWhite[] = {0x1B, 0x5B, '3','7', 'm'};
const unsigned char escLeft[] = {0x1B, 0x5B, '3','7', 'm'};
const unsigned char pucTempString[] = "Current Temperature:";

int16_t referenceTemp;
int16_t currentTemp;

ADC_Handle myAdc;
CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;
SCI_Handle mySci;

//
// sampleTemperature - 
//
int16_t sampleTemperature(void)
{
    //
    // Force start of conversion on SOC0 and SOC1
    //
    ADC_forceConversion(myAdc, ADC_SocNumber_0);
    ADC_forceConversion(myAdc, ADC_SocNumber_1);

    //
    // Wait for end of conversion.
    //
    while(ADC_getIntStatus(myAdc, ADC_IntNumber_1) == 0)
    {
        
    }

    //
    // Clear ADCINT1
    //
    ADC_clearIntFlag(myAdc, ADC_IntNumber_1);

    //
    // Get temp sensor sample result from SOC1
    //
    return (ADC_readResult(myAdc, ADC_ResultNumber_1));
}

//
// drawTILogo - 
//
void drawTILogo(void)
{
    unsigned char ucChar, lastChar;
    
    putchar('\n');
    while(indexY<45)
    {
        if(indexY<45)
        {
            if(indexX<77)
            {
                ucChar = ti_ascii[indexY][indexX++] ;
                //
                // We are in the TI logo make it red
                //
                if(ucChar != '7' && lastChar=='7')
                {
                    putchar(escRed[0]);
                    putchar(escRed[1]);
                    putchar(escRed[2]);
                    putchar(escRed[3]);
                    putchar(escRed[4]);
                }
                
                //                
                // We are in the TI logo make it red
                //
                if(ucChar == '7' && lastChar!='7')
                {
                    putchar(escWhite[0]);
                    putchar(escWhite[1]);
                    putchar(escWhite[2]);
                    putchar(escWhite[3]);
                    putchar(escWhite[4]);
                }
                    
                putchar(ucChar);
                lastChar = ucChar;
            }
            
            else
            {
                ucChar = 10;
                putchar(ucChar);
                ucChar = 13;
                putchar(ucChar);
                indexX=0;
                indexY++;
            }
        }
    }
}

//
// clearTextBox - 
//
void clearTextBox(void)
{
    putchar(0x08);
    
    //
    // Move back 24 columns
    //
    putchar(0x1B);
    putchar('[');
    putchar('2');
    putchar('6');
    putchar('D');
    
    //
    // Move up 3 lines
    //
    putchar(0x1B);
    putchar('[');
    putchar('3');
    putchar('A');
    
    //
    // Change to Red text
    //
    putchar(escRed[0]);
    putchar(escRed[1]);
    putchar(escRed[2]);
    putchar(escRed[3]);
    putchar(escRed[4]);
    
    printf((char*)pucTempString);
    
    //
    // Move down 1 lines
    //
    putchar(0x1B);
    putchar('[');
    putchar('1');
    putchar('B');
    
    //
    // Move back 20 columns
    //
    putchar(0x1B);
    putchar('[');
    putchar('2');
    putchar('0');
    putchar('D');
    
    //
    // Save cursor position
    //
    putchar(0x1B);
    putchar('[');
    putchar('s');
}

//
// updateTemperature - 
//
void updateTemperature(void)
{
    //
    // Restore cursor position
    //
    putchar(0x1B);
    putchar('[');
    putchar('u');
    
    printf("%d Celcius = Ref + %d ", currentTemp, (currentTemp - referenceTemp));
}

//
// scia_init - SCIA  8-bit word, baud rate 0x000F, default, 1 STOP bit, 
// no parity
//
void scia_init()
{
    CLK_enableSciaClock(myClk);

    //
    // 1 stop bit,  No loopback, No parity, 8 char bits, async mode, 
    // idle-line protocol
    //
    SCI_disableParity(mySci);
    SCI_setNumStopBits(mySci, SCI_NumStopBits_One);
    SCI_setCharLength(mySci, SCI_CharLength_8_Bits);
    
    SCI_enableTx(mySci);
    SCI_enableRx(mySci);
    SCI_enableTxInt(mySci);
    SCI_enableRxInt(mySci);

    //
    // SCI BRR = LSPCLK/(SCI BAUDx8) - 1
    // Configured for 115.2kbps
    //
#if (CPU_FRQ_60MHZ)
    SCI_setBaudRate(mySci, SCI_BaudRate_115_2_kBaud);    
#elif (CPU_FRQ_50MHZ)
    SCI_setBaudRate(mySci, (SCI_BaudRate_e)13);
#elif (CPU_FRQ_40MHZ)
    SCI_setBaudRate(mySci, (SCI_BaudRate_e)10);
#endif

    SCI_enableFifoEnh(mySci);
    SCI_resetTxFifo(mySci);
    SCI_clearTxFifoInt(mySci);
    SCI_resetChannels(mySci);
    SCI_setTxFifoIntLevel(mySci, SCI_FifoLevel_Empty);

    SCI_resetRxFifo(mySci);
    SCI_clearRxFifoInt(mySci);
    SCI_setRxFifoIntLevel(mySci, SCI_FifoLevel_4_Words);

    SCI_setPriority(mySci, SCI_Priority_FreeRun);
    
    SCI_enable(mySci);
  
    return;
}

//
// Main
//
void main(void)
{
    volatile int status = 0;
    volatile FILE *fid;
    
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
    // Initalize GPIO
    // Enable XCLOCKOUT to allow monitoring of oscillator 1
    //
    GPIO_setMode(myGpio, GPIO_Number_18, GPIO_18_Mode_XCLKOUT);
    CLK_setClkOutPreScaler(myClk, CLK_ClkOutPreScaler_SysClkOut_by_1);

    //
    // Setup a debug vector table and enable the PIE
    //
    PIE_setDebugIntVectorTable(myPie);
    PIE_enable(myPie);   

    //
    // Initialize SCIA
    //
    scia_init();
    
    //
    // Initialize the ADC
    //
    ADC_enableBandGap(myAdc);
    ADC_enableRefBuffers(myAdc);
    ADC_powerUp(myAdc);
    ADC_enable(myAdc);
    ADC_setVoltRefSrc(myAdc, ADC_VoltageRefSrc_Int);

    //
    // Connect channel A5 internally to the temperature sensor
    //
    ADC_enableTempSensor(myAdc);
    
    //
    // Set SOC0 channel select to ADCINA5
    //
    ADC_setSocChanNumber (myAdc, ADC_SocNumber_0, ADC_SocChanNumber_A5);    
    
    //
    // Set SOC1 channel select to ADCINA5
    //
    ADC_setSocChanNumber (myAdc, ADC_SocNumber_1, ADC_SocChanNumber_A5);    
    
    //
    // Set SOC0 acquisition period to 7 ADCCLK
    //
    ADC_setSocSampleWindow(myAdc, ADC_SocNumber_0, ADC_SocSampleWindow_7_cycles);   
    
    //
    // Set SOC1 acquisition period to 7 ADCCLK
    //
    ADC_setSocSampleWindow(myAdc, ADC_SocNumber_1, ADC_SocSampleWindow_7_cycles);   
    
    //
    // Connect ADCINT1 to EOC1
    //
    ADC_setIntSrc(myAdc, ADC_IntNumber_1, ADC_IntSrc_EOC1);
    
    //
    // Enable ADCINT1
    //
    ADC_enableInt(myAdc, ADC_IntNumber_1);

    //
    // Set the flash OTP wait-states to minimum. This is important
    // for the performance of the temperature conversion function.
    //
    FLASH_setup(myFlash);

    //
    // Initalize GPIO
    //
    GPIO_setPullUp(myGpio, GPIO_Number_28, GPIO_PullUp_Enable);
    GPIO_setPullUp(myGpio, GPIO_Number_29, GPIO_PullUp_Disable);
    GPIO_setQualification(myGpio, GPIO_Number_28, GPIO_Qual_ASync);
    GPIO_setMode(myGpio, GPIO_Number_28, GPIO_28_Mode_SCIRXDA);
    GPIO_setMode(myGpio, GPIO_Number_29, GPIO_29_Mode_SCITXDA);
    
    //
    // Configure GPIO 0-3 as outputs
    //
    GPIO_setMode(myGpio, GPIO_Number_0, GPIO_0_Mode_GeneralPurpose);
    GPIO_setMode(myGpio, GPIO_Number_1, GPIO_0_Mode_GeneralPurpose);
    GPIO_setMode(myGpio, GPIO_Number_2, GPIO_0_Mode_GeneralPurpose);
    GPIO_setMode(myGpio, GPIO_Number_3, GPIO_0_Mode_GeneralPurpose);
    
    GPIO_setDirection(myGpio, GPIO_Number_0, GPIO_Direction_Output);
    GPIO_setDirection(myGpio, GPIO_Number_1, GPIO_Direction_Output);
    GPIO_setDirection(myGpio, GPIO_Number_2, GPIO_Direction_Output);
    GPIO_setDirection(myGpio, GPIO_Number_3, GPIO_Direction_Output);
    
    GPIO_setMode(myGpio, GPIO_Number_12, GPIO_12_Mode_GeneralPurpose);
    GPIO_setDirection(myGpio, GPIO_Number_12, GPIO_Direction_Input);
    GPIO_setPullUp(myGpio, GPIO_Number_12, GPIO_PullUp_Disable);
    
    //
    // Redirect STDOUT to SCI
    //
    status = add_device("scia", _SSA, SCI_open, SCI_close, SCI_read, SCI_write,
                        SCI_lseek, SCI_unlink, SCI_rename);
    fid = fopen("scia","w");
    freopen("scia:", "w", stdout);
    setvbuf(stdout, NULL, _IONBF, 0);
    
    //
    // Print a TI Logo to STDOUT
    //
    drawTILogo();
    
    //    
    // Scan the LEDs until the pushbutton is pressed
    //
    while(GPIO_getData(myGpio, GPIO_Number_12) != 1)
    {       
        GPIO_setHigh(myGpio, GPIO_Number_0);
        GPIO_setHigh(myGpio, GPIO_Number_1);
        GPIO_setHigh(myGpio, GPIO_Number_2);
        GPIO_setLow(myGpio, GPIO_Number_3);
        DELAY_US(50000);

        GPIO_setHigh(myGpio, GPIO_Number_0);
        GPIO_setHigh(myGpio, GPIO_Number_1);
        GPIO_setLow(myGpio, GPIO_Number_2);
        GPIO_setHigh(myGpio, GPIO_Number_3);
        DELAY_US(50000);

        GPIO_setHigh(myGpio, GPIO_Number_0);
        GPIO_setLow(myGpio, GPIO_Number_1);
        GPIO_setHigh(myGpio, GPIO_Number_2);
        GPIO_setHigh(myGpio, GPIO_Number_3);
        DELAY_US(50000);

        GPIO_setLow(myGpio, GPIO_Number_0);
        GPIO_setHigh(myGpio, GPIO_Number_1);
        GPIO_setHigh(myGpio, GPIO_Number_2);
        GPIO_setHigh(myGpio, GPIO_Number_3);
        DELAY_US(500000);
    }
    
    //
    // Clear out one of the text boxes so we can write more info to it
    //
    clearTextBox();
    
    //
    // Sample the temperature and save it as our reference
    //
    referenceTemp = ADC_getTemperatureC(myAdc, sampleTemperature());
    
    //
    // Light up the binary display with a median value (0x08)
    //
    GPIO_setPortData(myGpio, GPIO_Port_A, (~0x08) & 0x0F);
    
    //
    // Main program loop - continually sample temperature
    //
    for(;;)
    {
        //
        // Convert the raw temperature sensor measurement into temperature
        //
        currentTemp = ADC_getTemperatureC(myAdc, sampleTemperature());
        
        updateTemperature();
        
        GPIO_setPortData(myGpio, GPIO_Port_A, 
                         (~(0x08 + (currentTemp - referenceTemp))) & 0x0F);
        
        DELAY_US(1000000);
        
        if(GPIO_getData(myGpio, GPIO_Number_12) == 1)
        {
            referenceTemp = ADC_getTemperatureC(myAdc, sampleTemperature());
        }
        
    }
}

//
// End of File
//

