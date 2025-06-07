//###########################################################################
//
// FILE:   Example_2833xAdcToDMA.c
//
// TITLE:  ADC to DMA Example
//
//! \addtogroup f2833x_example_list
//! <h1> ADC to DMA (adc_dma)</h1>
//!
//! This ADC example uses ADC to convert 4 channels for each SOC received,
//! with total of 10 SOCs.
//! Each SOC initiates 4 conversions.
//! DMA is used to capture the data on each SEQ1_INT. DMA will re-sort
//! the data by channel sequentially, i.e. all channel0 data will be
//! together and all channel1 data will be together.
//!
//! \b Watch \b Variables \n
//! - DMABuf1	- DMA Buffer
//
//###########################################################################
// $TI Release: $
// $Release Date: $
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
//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//
// Defines for ADC start parameters
//
#if (CPU_FRQ_150MHZ)     // Default - 150 MHz SYSCLKOUT
    //
    // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)   = 25.0 MHz
    //
    #define ADC_MODCLK 0x3
#endif
#if (CPU_FRQ_100MHZ)
    //
    // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 100/(2*2)   = 25.0 MHz
    //
    #define ADC_MODCLK 0x2
#endif

//
// ADC module clock = HSPCLK/2*ADC_CKPS   = 25.0MHz/(1*2) = 12.5MHz
//
#define ADC_CKPS   0x1

#define ADC_SHCLK  0xf   // S/H width in ADC module periods = 16 ADC clocks
#define AVG        1000  // Average sample limit
#define ZOFFSET    0x00  // Average Zero offset
#define BUF_SIZE   40    // Sample buffer size

//
// Globals
//
Uint16 j=0;

#pragma DATA_SECTION(DMABuf1,"DMARAML4");
volatile Uint16 DMABuf1[40];

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;
__interrupt void local_DINTCH1_ISR(void);

//
// Main
//
void main(void)
{
    Uint16 i;
    
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2833x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Specific clock setting for this example
    //
    EALLOW;
    SysCtrlRegs.HISPCP.all = ADC_MODCLK;	// HSPCLK = SYSCLKOUT/ADC_MODCLK
    EDIS;

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2833x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2833x_PieCtrl.c file.
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
    // The shell ISR routines are found in DSP2833x_DefaultIsr.c.
    // This function is found in DSP2833x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;	// Allow access to EALLOW protected registers
    PieVectTable.DINTCH1= &local_DINTCH1_ISR;
    EDIS;   // Disable access to EALLOW protected registers

    IER = M_INT7 ;	                   //Enable INT7 (7.1 DMA Ch1)
    EnableInterrupts();

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in DSP2833x_InitPeripherals.c
    //
    // InitPeripherals(); // Not required for this example
    InitAdc();  // For this example, init the ADC

    //
    // Specific ADC setup for this example:
    //
    AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;
    AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 0;        // 0 Non-Cascaded Mode
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0x1;
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;
    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x0;
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x1;
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x2;
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x3;
    
    //
    // Set up ADC to perform 4 conversions for every SOC
    //
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 3;

    //
    // Step 5. User specific code, enable interrupts:
    //
    
    //
    // Initialize DMA
    //
    DMAInitialize();

    //
    // Clear Table
    //
    for (i=0; i<BUF_SIZE; i++)
    {
        DMABuf1[i] = 0;
    }

    //
    // Configure DMA Channel
    //
    
    //
    // Point DMA destination to the beginning of the array
    //
    DMADest   = &DMABuf1[0];
    
    //
    // Point DMA source to ADC result register base
    //
    DMASource = &AdcMirror.ADCRESULT0;
    
    DMACH1AddrConfig(DMADest,DMASource);
    DMACH1BurstConfig(3,1,10);
    DMACH1TransferConfig(9,1,0);
    DMACH1WrapConfig(1,0,0,1);
    DMACH1ModeConfig(DMA_SEQ1INT,PERINT_ENABLE,ONESHOT_DISABLE,CONT_DISABLE,
                     SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,
                     CHINT_END,CHINT_ENABLE);

    StartDMACH1();

    //
    // Start SEQ1
    //
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0x1;
    
    //
    // For this example will re-start manually
    //
    for(i=0;i<10;i++)
    {
        for(j=0;j<1000;j++)
        {
            
        }
        
        //
        // Normally ADC will be tied to ePWM, or timed routine
        //
        AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
    }
}

//
// local_DINTCH1_ISR - INT7.1(DMA Channel 1)
//
__interrupt void 
local_DINTCH1_ISR(void)
{
    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// End of File
//

