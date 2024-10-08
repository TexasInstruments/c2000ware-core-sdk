//###########################################################################
//
// FILE:   Example_2823xEPwm_DMA.c
//
// TITLE:  ePWM to DMA Example
//
//! \addtogroup f2823x_example_list
//! <h1>ePWM to DMA (epwm_dma)</h1>
//!
//! This example demonstrates several cases where the DMA is triggered from
//! SOC signals generated by ePWM modules.
//!
//! \b Watch \b Variables \n
//! - EPwm1Regs.TBPRD
//! - EPwm1Regs.CMPA.all
//! - ADCbuffer
//! - InterruptCount
//
//###########################################################################
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
//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//
// Function Prototype statements
//
void delay_loop(void);
void DMAInitialize(void);
void DMACH1Config(void);
void DMACH2Config(void);
void DMACH3Config(void);
void ConfigAdc(void);
void config_ePWM1_to_generate_ADCSOCA(void);
void config_ePWM2_to_generate_ADCSOCB(void);
__interrupt void local_DINTCH1_ISR(void);

//
// Globals
//
#pragma DATA_SECTION(ADCbuffer,"DMARAML4");
volatile Uint32 ADCbuffer[3];

Uint16 VarA;
Uint32 VarB;

volatile Uint16 *MAPCNF = (Uint16 *)0x00702E;

Uint16 InterruptCount;

//
// Main
//
void main(void)
{
    Uint16 i;

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2823x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2823x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // For this example use the following configuration:
    //

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2823x_PieCtrl.c file.
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
    // The shell ISR routines are found in DSP2823x_DefaultIsr.c.
    // This function is found in DSP2823x_PieVect.c.
    //
    InitPieVectTable();

    EALLOW;
    
    //
    // Initialize PIE vector for CPU interrupt:
    //
    PieVectTable.DINTCH1 = &local_DINTCH1_ISR;	// Point to DMA CH1 ISR
    PieCtrlRegs.PIEIER7.bit.INTx1 = 1;       // Enable DMA CH1 interrupt in PIE
    EDIS;

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in DSP2823x_InitPeripherals.c
    //
    // InitPeripherals(); // Not required for this example

    //
    // Step 5. User specific code:
    //
    InterruptCount = 0;

    EALLOW;
    GpioCtrlRegs.GPADIR.all = 0xFFFFFFFF;    // All outputs
    SysCtrlRegs.MAPCNF.bit.MAPEPWM = 1;      // Remap ePWMs for DMA access
    EDIS;

    GpioDataRegs.GPASET.all = 0xFFFFFFFF;
    delay_loop();
    GpioDataRegs.GPACLEAR.all = 0x00000002;

    for(i=0; i<3; i++)
    {
        ADCbuffer[i] = ((Uint32)i*0x00011000) + 0x00044000;
    }

    VarA = 75;
    VarB = 0x652000;

    //
    // Enable and configure clocks to peripherals:
    //
    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.DMAENCLK = 1;  // Enable SYSCLK to DMA
    EDIS;

    DMAInitialize();
    DMACH1Config();
    DMACH2Config();
    DMACH3Config();

    //
    // Enable all interrupts:
    //
    IER = M_INT7;							// Enable INT7 (7.1 DMA Ch1)
    EINT;

    InitAdc();
    ConfigAdc();

    config_ePWM1_to_generate_ADCSOCA();
    config_ePWM2_to_generate_ADCSOCB();

    EALLOW;
    DmaRegs.CH1.CONTROL.bit.RUN = 1;
    DmaRegs.CH2.CONTROL.bit.RUN = 1;
    DmaRegs.CH3.CONTROL.bit.RUN = 1;
    __asm("   NOP");
    EPwm1Regs.TBCTL.bit.CTRMODE = 0;						// Up count mode
    EPwm2Regs.TBCTL.bit.CTRMODE = 0;						// Up count mode
    EDIS;

    for(;;) 
    {
        
    }
}

//
// DMA Functions
//
void 
DMAInitialize(void)
{
	EALLOW;

    //
	// Perform a hard reset on DMA
    //
	DmaRegs.DMACTRL.bit.HARDRESET = 1;

    //
	// always perform one NOP after a HARDRESET
    //
	__asm("     NOP");

    //
	// Stop DMA on emulation suspend
    //
	DmaRegs.DEBUGCTRL.bit.FREE = 0;

	EDIS;
}

//
// DMACH1Config -
//
void 
DMACH1Config(void)
{
    EALLOW;
    
    //
    // Configure CH1:
    //
    
    //
    // Reset selected channel via CONTROL Register:
    //
    
    //
    // Perform SOFT reset on channel (clears all counters)
    //
    //DmaRegs.CH1.CONTROL.bit.SOFTRESET = 1;

    //
    // Set up MODE Register:
    //
    
    //
    // ePWM1 SOCA as peripheral interrupt source
    //
    DmaRegs.CH1.MODE.bit.PERINTSEL = 18;
    
    DmaRegs.CH1.MODE.bit.PERINTE = 1;       // Peripheral interrupt enabled
    DmaRegs.CH1.MODE.bit.ONESHOT = 0;       // 1 burst per SW interrupt
    DmaRegs.CH1.MODE.bit.CONTINUOUS = 1;    // Do not stop after each transfer
    DmaRegs.CH1.MODE.bit.SYNCE = 0;         // No sync signal
    DmaRegs.CH1.MODE.bit.SYNCSEL = 0;       // No sync signal
    DmaRegs.CH1.MODE.bit.DATASIZE = 0;		// 16-bit data size transfers
    
    //
    // Generate interrupt to CPU at the beg of transfer
    //
    DmaRegs.CH1.MODE.bit.CHINTMODE = 0;
    
    DmaRegs.CH1.MODE.bit.CHINTE = 1;        // Channel Interrupt to CPU enabled

    //
    // Set up BURST registers
    //
    
    //
    // Number (N-1) of 16-bit words transferred in a burst
    //
    DmaRegs.CH1.BURST_SIZE.all = 0;
    DmaRegs.CH1.SRC_BURST_STEP = 0;			// Not needed since BURST_SIZE = 0
    DmaRegs.CH1.DST_BURST_STEP = 0;			// Not needed since BURST_SIZE = 0

    //
    // Set up TRANSFER registers
    //
    DmaRegs.CH1.TRANSFER_SIZE = 0;		// Bursts (N-1) per transfer
    DmaRegs.CH1.SRC_TRANSFER_STEP = 0;	// Not needed since TRANSFER_SIZE = 0
    DmaRegs.CH1.DST_TRANSFER_STEP = 0;  // Not needed since TRANSFER_SIZE = 0

    //
    // Set up WRAP registers
    //
    DmaRegs.CH1.SRC_WRAP_SIZE = 0xFFFF;	// No source wrap-around
    DmaRegs.CH1.DST_WRAP_SIZE = 0xFFFF;	// No destination wrap-around
    DmaRegs.CH1.SRC_WRAP_STEP = 0;
    DmaRegs.CH1.DST_WRAP_STEP = 0;

    //
    // Set up SOURCE address
    //
    DmaRegs.CH1.SRC_ADDR_SHADOW = (Uint32) &VarA;	// Point to variable in RAM

    //
    // Set up DESTINATION address
    //
    
    //
    // Point to ePWM1 TBPRD register remapped for DMA need to make sure 
    // .cmd file has ePWMs remapped
    //
    DmaRegs.CH1.DST_ADDR_SHADOW = (Uint32) &EPwm1Regs.TBPRD;
    
    //
    // Clear any spurious flags
    //
    DmaRegs.CH1.CONTROL.bit.PERINTCLR = 1; //Clear any spurious interrupt flags
    DmaRegs.CH1.CONTROL.bit.SYNCCLR = 1;    // Clear any spurious sync flags
    DmaRegs.CH1.CONTROL.bit.ERRCLR = 1;   //Clear any spurious sync error flags

    EDIS;
}

//
// DMACH2Config -
//
void 
DMACH2Config(void)
{
    EALLOW;
    
    //
    // Configure CH2
    //
    
    //
    // Reset selected channel via CONTROL Register
    //
    
    //
    // Perform SOFT reset on channel (clears all counters)
    //
    //DmaRegs.CH2.CONTROL.bit.SOFTRESET = 1;

    //
    // Set up MODE Register
    //
    
    //
    // ePWM2 SOCB as peripheral interrupt source
    //
    DmaRegs.CH2.MODE.bit.PERINTSEL = 21;
    
    DmaRegs.CH2.MODE.bit.PERINTE = 1;    	// Peripheral interrupt enabled
    DmaRegs.CH2.MODE.bit.ONESHOT = 0;    	// 1 burst per SW interrupt
    DmaRegs.CH2.MODE.bit.CONTINUOUS = 1; 	// Do not stop after each transfer
    DmaRegs.CH2.MODE.bit.SYNCE = 0;      	// No sync signal
    DmaRegs.CH2.MODE.bit.SYNCSEL = 0;    	// No sync signal
    DmaRegs.CH2.MODE.bit.DATASIZE = 1;		// 32-bit data size transfers
    DmaRegs.CH2.MODE.bit.CHINTMODE = 0;
    DmaRegs.CH2.MODE.bit.CHINTE = 0;    // Channel Interrupt to CPU disabled

    //
    // Set up BURST registers
    //
    
    //
    // Number (N-1) of 16-bit words transferred in a burst
    //
    DmaRegs.CH2.BURST_SIZE.all = 1;
    
    //
    // Not needed since only 1 32-bit move per burst
    //
    DmaRegs.CH2.SRC_BURST_STEP = 0x0000;
    
    //
    // Not needed since only 1 32-bit move per burst
    //
    DmaRegs.CH2.DST_BURST_STEP = 0x0000;

    //
    // Set up TRANSFER registers
    //
    DmaRegs.CH2.TRANSFER_SIZE = 0;		// Bursts (N-1) per transfer
    DmaRegs.CH2.SRC_TRANSFER_STEP = 0;	// Not needed since TRANSFER_SIZE = 0
    DmaRegs.CH2.DST_TRANSFER_STEP = 0; 	// Not needed since TRANSFER_SIZE = 0

    //
    // Set up WRAP registers
    //
    DmaRegs.CH2.SRC_WRAP_SIZE = 0xFFFF;	// No source wrap-around
    DmaRegs.CH2.DST_WRAP_SIZE = 0xFFFF;	// No destination wrap-around
    DmaRegs.CH2.SRC_WRAP_STEP = 0;
    DmaRegs.CH2.DST_WRAP_STEP = 0;

    //
    // Set up SOURCE address
    //
    DmaRegs.CH2.SRC_ADDR_SHADOW = (Uint32) &VarB;	// Point to variable in RAM

    //
    // Set up DESTINATION address
    //
    
    //
    // Point to ePWM1 CMPAHR/CMPA registers
    //
    DmaRegs.CH2.DST_ADDR_SHADOW = (Uint32) &EPwm1Regs.CMPA.all;

    //
    // Clear any spurious flags
    //
    DmaRegs.CH2.CONTROL.bit.PERINTCLR = 1; //Clear any spurious interrupt flags
    DmaRegs.CH2.CONTROL.bit.SYNCCLR = 1; 	//Clear any spurious sync flags
    DmaRegs.CH2.CONTROL.bit.ERRCLR = 1;   //Clear any spurious sync error flags

    EDIS;
}

//
// DMACH3Config -
//
void
DMACH3Config(void)
{
    EALLOW;
    
    //
    // Configure CH3
    //

    //
    // Set up MODE Register
    //

    //
    // ADC SEQ1INT as peripheral interrupt source
    //
    DmaRegs.CH3.MODE.bit.PERINTSEL = 1;
    
    DmaRegs.CH3.MODE.bit.PERINTE = 1;      // Peripheral interrupt enabled
    DmaRegs.CH3.MODE.bit.ONESHOT = 0;      // 1 burst per SW interrupt
    DmaRegs.CH3.MODE.bit.CONTINUOUS = 1;   // Do not stop after each transfer
    DmaRegs.CH3.MODE.bit.SYNCE = 0;        // No sync signal
    DmaRegs.CH3.MODE.bit.SYNCSEL = 0;      // No sync signal
    DmaRegs.CH3.MODE.bit.DATASIZE = 1;	   // 32-bit data size transfers
    DmaRegs.CH3.MODE.bit.CHINTMODE = 0;
    DmaRegs.CH3.MODE.bit.CHINTE = 0;       // Channel Interrupt to CPU disabled

    //
    // Set up BURST registers
    //
    
    //
    // Number (N-1) of 16-bit words transferred in a burst
    //
    DmaRegs.CH3.BURST_SIZE.all = 5;
    
    //
    // Increment source burst address by 2 (32-bit)
    //
    DmaRegs.CH3.SRC_BURST_STEP = 2;
    
    //
    // Increment destination burst address by 2 (32-bit)
    //
    DmaRegs.CH3.DST_BURST_STEP = 2;

    //
    // Set up TRANSFER registers
    //
    DmaRegs.CH3.TRANSFER_SIZE = 0;		// Bursts (N-1) per transfer
    DmaRegs.CH3.SRC_TRANSFER_STEP = 0;	// Not needed since TRANSFER_SIZE = 0
    DmaRegs.CH3.DST_TRANSFER_STEP = 0; 	// Not needed since TRANSFER_SIZE = 0

    //
    // Set up WRAP registers
    //
    DmaRegs.CH3.SRC_WRAP_SIZE = 0xFFFF;		// No source wrap-around
    DmaRegs.CH3.DST_WRAP_SIZE = 0xFFFF;		// No destination wrap-around
    DmaRegs.CH3.SRC_WRAP_STEP = 0;
    DmaRegs.CH3.DST_WRAP_STEP = 0;

    //
    // Set up SOURCE address
    //
    
    //
    // Point to first RESULT reg
    //
    DmaRegs.CH3.SRC_ADDR_SHADOW = (Uint32) &AdcMirror.ADCRESULT0;

    //
    // Set up DESTINATION address
    //
    
    //
    // Point to beginning of ADCbuffer
    //
    DmaRegs.CH3.DST_ADDR_SHADOW = (Uint32) &ADCbuffer[0];

    //
    // Clear any spurious flags
    //
    DmaRegs.CH3.CONTROL.bit.PERINTCLR = 1; //Clear any spurious interrupt flags
    DmaRegs.CH3.CONTROL.bit.SYNCCLR = 1;   //Clear any spurious sync flags
    DmaRegs.CH3.CONTROL.bit.ERRCLR = 1;   //Clear any spurious sync error flags

    EDIS;
}

//
// local_DINTCH1_ISR - DMA (INT7.1)
//
__interrupt void 
local_DINTCH1_ISR(void)
{
    GpioDataRegs.GPATOGGLE.all = 0x00000001;		// Toggle GPIOA0

    InterruptCount++;

    if((DmaRegs.CH1.CONTROL.bit.OVRFLG == 1) || 
    (DmaRegs.CH2.CONTROL.bit.OVRFLG == 1) ||
    (DmaRegs.CH3.CONTROL.bit.OVRFLG == 1))
    {
        __asm("     ESTOP0");
    }

    PieCtrlRegs.PIEACK.bit.ACK7 = 1;				// Clear PIEIFR bit
}

//
// ConfigAdc - 
//
void 
ConfigAdc(void)
{
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 7;
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0;		// ADCINA0
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 1;		// ADCINA1
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 2;		// ADCINA2
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 3;		// ADCINA3
    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 4;		// ADCINA4
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 5;		// ADCINA5
    
    //
    // Enable ADC to accept ePWM_SOCA trigger
    //
    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
    
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;			// Clear interrupt flag
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;		// Enable SEQ1 interrupt
}

//
// config_ePWM1_to_generate_ADCSOCA -
//
void 
config_ePWM1_to_generate_ADCSOCA(void)
{
    //
    // Configure ePWM1 Timer
    // Interrupt triggers ADCSOCA
    //
    EALLOW;
    
    //
    // Setup period (one off so DMA transfer will be obvious)
    //
    EPwm1Regs.TBPRD = 74;
    
    EPwm1Regs.CMPA.all = 0x501000;
    EPwm1Regs.ETSEL.bit.SOCASEL = 2;			// ADCSOCA on TBCTR=TBPRD
    EPwm1Regs.ETPS.bit.SOCAPRD = 1;				// Generate SOCA on 1st event
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;				// Enable SOCA generation
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;			// /1 clock mode
    EDIS;
}

//
// config_ePWM2_to_generate_ADCSOCB -
//
void 
config_ePWM2_to_generate_ADCSOCB(void)
{
    //
    // Configure ePWM2 Timer
    // Interrupt triggers ADCSOCB
    //
    EALLOW;
    EPwm2Regs.TBPRD = 150;						// Setup periodSetup period
    EPwm2Regs.CMPA.all = 0x200000;
    EPwm2Regs.ETSEL.bit.SOCBSEL = 2;			// ADCSOCB on TBCTR=TBPRD
    EPwm2Regs.ETPS.bit.SOCBPRD = 1;				// Generate SOCB on 1st event
    EPwm2Regs.ETSEL.bit.SOCBEN = 1;				// Enable SOCB generation
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;			// /1 clock mode
    EDIS;
}

void delay_loop()
{
    short      i;
    for (i = 0; i < 1000; i++) 
    {
        
    }
}

//
// End of File
//

