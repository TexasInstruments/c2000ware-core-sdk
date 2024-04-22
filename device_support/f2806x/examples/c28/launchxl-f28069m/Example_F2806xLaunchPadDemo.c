//###########################################################################
//
// FILE:	Example_F2806xLaunchPadDemo.c
//
// TITLE:	F2806x LaunchPad Out of Box Demo
//
//! \addtogroup f2806x_example_list
//! <h1>LaunchPad Demo (launchxl_f28069m)</h1>
//!
//!  This program is the demo program that comes pre-loaded on the F28069M
//!  LaunchPad development kit.  The program starts by flashing the two user
//!  LEDs. After a few seconds the LEDs stop flashing and samples the
//!  device's internal temperature sensor to establish a reference.  After
//!  this, any difference between the current temperature and the reference
//!  is shown as a change in the intensity of the two user LEDs.
//!
//
//###########################################################################
// $TI Release: $
// $Release Date: $
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
//###########################################################################

//
// Included Files
//
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <file.h>

#include "DSP28x_Project.h"     // DSP28x Headerfile
#include "ti_ascii.h"
#include "sci_io.h"

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
int16_t tempDelta;

//
// sampleTemperature - 
//
int16_t sampleTemperature(void)
{
    int16_t temp;

    //
    // Force start of conversion on SOC0
    //
    AdcRegs.ADCSOCFRC1.all = 0x01;

    //
    // Wait for end of conversion.
    //
    while(AdcRegs.ADCINTFLG.bit.ADCINT1 == 0)
    {
        //
        // Wait for ADCINT1
        //
    }
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;        // Clear ADCINT1

    //
    // Get temp sensor sample result from SOC0
    //
    temp = AdcResult.ADCRESULT0;

    //
    // Convert the raw temperature sensor measurement into temperature
    //
    return(GetTemperatureC(temp));
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
    
    tempDelta = (currentTemp - referenceTemp);

    printf("%d Celcius = Ref + %d ", currentTemp, tempDelta);   
}

//
// scia_init - SCIA  8-bit word, baud rate 0x000F, default, 1 STOP bit, 
// no parity
//
void scia_init()
{
    //
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
    //
 	
    //
    // 1 stop bit,  No loopback, No parity,8 char bits, async mode, 
    // idle-line protocol
    //
    SciaRegs.SCICCR.all =0x0007;   
	
    //
    // enable TX, RX, internal SCICLK, Disable RX ERR, SLEEP, TXWAKE
    //
    SciaRegs.SCICTL1.all =0x0003;  

	SciaRegs.SCICTL2.bit.TXINTENA =1;
	SciaRegs.SCICTL2.bit.RXBKINTENA =1;

	//
    // 115200 baud @LSPCLK = 22.5MHz (90 MHz SYSCLK).
    //
    SciaRegs.SCIHBAUD    =0x0000;  
    
    SciaRegs.SCILBAUD    =0x0017;

	SciaRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
  
    return;
}

//
// cpu_timer0_isr - 
//
__interrupt void cpu_timer0_isr(void)
{
	static uint16_t cycleCount = 0;

	if(tempDelta > 10)
    {
        //
		// Red LED on, blue off
        //
	    GpioDataRegs.GPBDAT.bit.GPIO34 = 0;
	    GpioDataRegs.GPBDAT.bit.GPIO39 = 1;
	}
    else if(tempDelta < -10)
    {
	    GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
	    GpioDataRegs.GPBDAT.bit.GPIO39 = 0;
	}
    else
    {
		if(tempDelta > 0)
        {
		    GpioDataRegs.GPBDAT.bit.GPIO39 = 1;
		    if(tempDelta > cycleCount)
            {
                GpioDataRegs.GPBDAT.bit.GPIO34 = 0;
		    }
            else
            {
			    GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
		    }
		}
        else
        {
		    GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
		    if(abs(tempDelta) > cycleCount)
            {
                GpioDataRegs.GPBDAT.bit.GPIO39 = 0;
		    }
            else
            {
			    GpioDataRegs.GPBDAT.bit.GPIO39 = 1;
		    }
		}
	}

	cycleCount++;

	if(cycleCount == 10)
    {
        cycleCount = 0;
    }

    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// Main
//
void main(void)
{
    volatile int status = 0;
    uint16_t i;
    volatile FILE *fid;
    
    //
    // If running from flash copy RAM only functions to RAM
    //
#ifdef _FLASH
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif      

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2806x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initalize GPIO:
    // This example function is found in the F2806x_Gpio.c file and
    // illustrates how to set the GPIO to its default state.
    //
    // InitGpio(); Skipped for this example

    //
    // For this example, only init the pins for the SCI-A port.
    // This function is found in the F2806x_Sci.c file.
    //
    InitSciaGpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the F2806x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags:
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in F2806x_DefaultIsr.c.
    // This function is found in F2806x_PieVect.c.
    //
    InitPieVectTable();

    EALLOW;
    PieVectTable.TINT0 = &cpu_timer0_isr;
    EDIS;

    //
    // Initialize SCIA
    //
    scia_init();

    //
    // Initialize GPIOs for the LEDs and turn them off
    //
    EALLOW;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;
    GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
    GpioDataRegs.GPBDAT.bit.GPIO39 = 1;
    EDIS;

    InitCpuTimers();        // For this example, only initialize the Cpu Timers
    ConfigCpuTimer(&CpuTimer0, 90, 1000);
    
    //
    // Use write-only instruction to set TSS bit = 1
    //
    CpuTimer0Regs.TCR.all = 0x4010;
    
    IER |= M_INT1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    //
    // Configure the ADC: Initialize the ADC
    //
    InitAdc();

    EALLOW;
    AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1;	//Enable non-overlap mode
    
    //
    // Connect channel A5 internally to the temperature sensor
    //
    AdcRegs.ADCCTL1.bit.TEMPCONV  = 1; 		
    
    AdcRegs.ADCSOC0CTL.bit.CHSEL  = 5;    //Set SOC0 channel select to ADCINA5
    
    //
    // Set SOC0 acquisition period to 26 ADCCLK
    //
    AdcRegs.ADCSOC0CTL.bit.ACQPS  = 25;   
    
    AdcRegs.INTSEL1N2.bit.INT1SEL = 0; 	  //Connect ADCINT1 to EOC0
    AdcRegs.INTSEL1N2.bit.INT1E  =  1; 	  //Enable ADCINT1

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
    // Twiddle LEDs
    //
    GpioDataRegs.GPBDAT.bit.GPIO34 = 0;
    GpioDataRegs.GPBDAT.bit.GPIO39 = 1;

    for(i = 0; i < 50; i++)
    {
        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
        GpioDataRegs.GPBTOGGLE.bit.GPIO39 = 1;
        DELAY_US(50000);
    }

    //
    // LEDs off
    //
    GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
    GpioDataRegs.GPBDAT.bit.GPIO39 = 1;  
    
    //
    // Clear out one of the text boxes so we can write more info to it
    //
    clearTextBox();
    
    referenceTemp = sampleTemperature();
    
    //
    // Enable timer
    //
    
    //
    // Use write-only instruction to set TSS bit = 1
    //
    CpuTimer0Regs.TCR.all = 0x4000; 

    //
    // Main program loop - continually sample temperature
    //
    for(;;)
    {
        //
        // Convert the raw temperature sensor measurement into temperature
        //
        currentTemp = sampleTemperature();
        
        updateTemperature();
        
        DELAY_US(1000000);
    }
}

//
// End of File
//

