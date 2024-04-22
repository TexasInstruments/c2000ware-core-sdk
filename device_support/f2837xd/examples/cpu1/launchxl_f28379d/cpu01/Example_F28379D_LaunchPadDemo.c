//###########################################################################
//
// FILE:	Example_F28379D_LaunchPadDemo.c
//
// TITLE:	F28379D LaunchPad Out of Box Demo
//
// DESCRIPTION:
//! \addtogroup cpu01_example_list
//! <h1>Out of Box Demo (LaunchPadDemo)</h1>
//!
//!  This program is the demo program that comes pre-loaded on the F28379D
//!  LaunchPad development kit.  The program starts by flashing the two user
//!  LEDs. After a few seconds the LEDs stop flashing and the device starts 
//!  sampling ADCIN14 once a second.  If the sample is greater than midscale
//!  the red LED on the board is lit, while if it is lower a blue LED is lit.  
//!  Sample data is also display in a serial terminal via the boards back 
//!  channel UART.  You may view this data by configuring a serial terminal 
//!  to the correct COM port at 115200 Baud 8-N-1.
//!
//
//###########################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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

#include "F28x_Project.h"     // DSP28x Headerfile
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
const unsigned char pucTempString[] = "ADCIN14 Sample:     ";

int16_t currentSample;

//
// sampleADC - 
//
int16_t sampleADC(void)
{
    int16_t sample;

    //
    // Force start of conversion on SOC0
    //
    AdcaRegs.ADCSOCFRC1.all = 0x03;

    //
    // Wait for end of conversion.
    //
    while(AdcaRegs.ADCINTFLG.bit.ADCINT1 == 0)
    {
        //
        // Wait for ADCINT1
        //
    }
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;        // Clear ADCINT1

    //
    // Get ADC sample result from SOC0
    //
    sample = AdcaResultRegs.ADCRESULT1;

    return(sample);
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
// updateDisplay -
//
void updateDisplay(void)
{
    //
    // Restore cursor position
    //
    putchar(0x1B);
    putchar('[');
    putchar('u');
    
    printf("%d               ", currentSample);
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
    // 115200 baud @LSPCLK = 50MHz (200MHz SYSCLK)
    //
    SciaRegs.SCIHBAUD.all    =0x0000;  
    
    SciaRegs.SCILBAUD.all    =53;

	SciaRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
  
    return;
}

//
// Main
//
void main()
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
    // Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2806x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // For this example, only init the pins for the SCI-A port.
    //
    EALLOW;
    GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 3;
    GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 3;
    GpioCtrlRegs.GPBGMUX1.bit.GPIO42 = 3;
    GpioCtrlRegs.GPBGMUX1.bit.GPIO43 = 3;
    EDIS;

    //
    // Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the F2837xD_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in F2837xD_DefaultIsr.c.
    // This function is found in F2837xD_PieVect.c.
    //
    InitPieVectTable();

    //
    // Initialize SCIA
    //
    scia_init();

    //
    // Initialize GPIOs for the LEDs and turn them off
    //
    EALLOW;
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
    GpioDataRegs.GPADAT.bit.GPIO31 = 1;
    GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
    EDIS;

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    //
    // Configure the ADC: Initialize the ADC
    //
	EALLOW;

    //
	// write configurations
    //
	AdcaRegs.ADCCTL2.bit.PRESCALE = 6;      // set ADCCLK divider to /4
	AdcbRegs.ADCCTL2.bit.PRESCALE = 6;      // set ADCCLK divider to /4
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    //
	// Set pulse positions to late
    //
	AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
	AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //
	// power up the ADCs
    //
	AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
	AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    //
	// delay for 1ms to allow ADC time to power up
    //
	DELAY_US(1000);

    //
    // ADCA
    //
    EALLOW;
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0x0E;   //SOC0 will convert pin ADCIN14
    
    //
    // sample window is acqps + 1 SYSCLK cycles
    //
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 25;     
    
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 0x0E;   //SOC1 will convert pin ADCIN14
    
    //
    // sample window is acqps + 1 SYSCLK cycles
    //
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = 25;     
    
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 1;  //end of SOC1 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;    //enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;  //make sure INT1 flag is cleared

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
    GpioDataRegs.GPADAT.bit.GPIO31 = 0;
    GpioDataRegs.GPBDAT.bit.GPIO34 = 1;

    for(i = 0; i < 50; i++)
    {
        GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
        DELAY_US(50000);
    }

    //
    // LEDs off
    //
    GpioDataRegs.GPADAT.bit.GPIO31 = 1;
    GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
    
    // 
    // Clear out one of the text boxes so we can write more info to it
    //
    clearTextBox();
    
    currentSample = sampleADC();
    
    //
    // Main program loop - continually sample temperature
    //
    for(;;)
    {
        //
        // Sample ADCIN14
        //
        currentSample = sampleADC();

        //
        // Update the serial terminal output
        //
        updateDisplay();

        //
        // If the sample is above midscale light one LED
        //
        if(currentSample > 2048)
        {
            GpioDataRegs.GPBSET.bit.GPIO34 = 1;
            GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;
        }
        else
        {
            //
            // Otherwise light the other
            //
            GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
            GpioDataRegs.GPASET.bit.GPIO31 = 1;
        }

        DELAY_US(1000000);
    }
}

//
// End of File
//

