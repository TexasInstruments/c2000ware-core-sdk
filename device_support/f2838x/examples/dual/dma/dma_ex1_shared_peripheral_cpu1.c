//###########################################################################
//
// FILE:   dma_ex1_shared_peripheral_cpu1.c
//
// TITLE:  DMA Transfer for Shared Peripheral Example
//
//! \addtogroup dual_example_list
//! <h1> DMA Transfer Shared Peripheral </h1>
//!
//! This example shows how to initiate a DMA transfer on CPU1 from a shared
//! peripheral which is owned by CPU2.  In this specific example, a timer ISR
//! is used on CPU2 to initiate a SPI transfer which will trigger the CPU1 DMA.
//! CPU1's DMA will then in turn update the EPWM1 CMPA value for the PWM which
//! it owns.  The PWM output can be observed on the GPIO pins configured in
//! the InitEPwm1Gpio() function.
//!
//! \b Watch \b Pins
//!   - GPIO0 and GPIO1 - ePWM output can be viewed with oscilloscope
//!
//
//###########################################################################
// 
// C2000Ware v5.05.00.00
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
//###########################################################################

//
// Included Files
//
#include "f28x_project.h"

//
// Function Prototypes
//
void ExampleInitSysCtrl(void);
void InitEPwm1(void);
void SetupDMA(void);

//
// Uncomment to enable DMA ISR
//
//interrupt void dma_isr(void);

//
// Main
//
void main(void)
{
//
// Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the f2838x_sysctrl.c file.
//
    ExampleInitSysCtrl();


//
// Initialize GPIO pins for EPWM-1
//
    InitEPwm1Gpio();

//
// Disable CPU interrupts
//
    DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
//
    InitPieCtrl();

//
// Step 7. Disable CPU interrupts and clear all CPU interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the
// default Interrupt Service Routines (ISR).
// The default ISR routines are found in f2838x_defaultisr.c.
// This function is found in f2838x_pievect.c.
//
    InitPieVectTable();

//
// Freeze TBCTR of EPWMs, setup EPWM1 and DMA
//
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    InitEPwm1();    // Setup EPWM1
    SetupDMA();     // Setup DMA to be triggered on SPI-A

    IPCLtoRFlagSet(IPC_FLAG0);


//
//  Uncomment to enable DMA ISR
//
//    EALLOW;
//    PieCtrlRegs.PIEIER7.bit.INTx5 = 1 ;
//    PieVectTable.DMA_CH5_INT= &dma_isr;
//    IER |= M_INT7;
//    EDIS;

//
// Allow EPWM TBCTRs to count
//
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

//
// Enable global Interrupts and higher priority real-time debug
// events:
//
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

//
// IDLE loop. Just sit and loop forever (optional):
//
    for(;;)
    {
        asm ("          NOP");
    }
}

//
// ExampleInitSysCtrl function
// This example uses custom InitSysCtrl function since CPU2 owns some of the
// peripherals
//
void ExampleInitSysCtrl(void)
{
    //
    // Disable the watchdog
    //
    DisableDog();

#ifdef _FLASH
    //
    // Copy time critical code and Flash setup code to RAM. This includes the
    // following functions: InitFlash()
    //
    // The  RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart
    // symbols are created by the linker. Refer to the device .cmd file.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //
    InitFlash();
#endif

    //
    //      *IMPORTANT*
    //
    // The Device_cal function, which copies the ADC & oscillator calibration
    // values from TI reserved OTP into the appropriate trim registers, occurs
    // automatically in the Boot ROM. If the boot ROM code is bypassed during
    // the debug process, the following function MUST be called for the ADC and
    // oscillators to function according to specification. The clocks to the
    // ADC MUST be enabled before calling this function.
    //
    // See the device data manual and/or the ADC Reference Manual for more
    // information.
    //
    //
    // Enable pull-ups on unbonded IOs as soon as possible to reduce power
    // consumption.
    //
    GPIO_EnableUnbondedIOPullups();

    EALLOW;


    CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
    CpuSysRegs.PCLKCR13.bit.ADC_B = 1;
    CpuSysRegs.PCLKCR13.bit.ADC_C = 1;
    CpuSysRegs.PCLKCR13.bit.ADC_D = 1;

    //
    // Check if device is trimmed
    //
    if(*((Uint16 *)0x5D736) == 0x0000){
        //
        // Device is not trimmed--apply static calibration values
        //
        AnalogSubsysRegs.ANAREFTRIMA.all = 31709;
        AnalogSubsysRegs.ANAREFTRIMB.all = 31709;
        AnalogSubsysRegs.ANAREFTRIMC.all = 31709;
        AnalogSubsysRegs.ANAREFTRIMD.all = 31709;
    }

    CpuSysRegs.PCLKCR13.bit.ADC_A = 0;
    CpuSysRegs.PCLKCR13.bit.ADC_B = 0;
    CpuSysRegs.PCLKCR13.bit.ADC_C = 0;
    CpuSysRegs.PCLKCR13.bit.ADC_D = 0;
    EDIS;

    //
    // Initialize the SYSPLL control  to generate a 200Mhz clock
    //
    // Defined options to be passed as arguments to this function are defined
    // in f2838x_examples.h.
    //
    // Note: The internal oscillator CANNOT be used as the PLL source if the
    // PLLSYSCLK is configured to frequencies above 194 MHz.
    //
    //  PLLSYSCLK = (XTAL_OSC) * (IMULT) /(REFDIV) * (ODIV) * (PLLSYSCLKDIV)
    //
    InitSysPll(XTAL_OSC, IMULT_32, REFDIV_2, ODIV_2, PLLCLK_BY_1, SYSCTL_DCC_BASE0);

    //
    // Initialize the AUXPLL control to generate a 125Mhz clock:
    //
    // Defined options to be passed as arguments to this function are defined
    // in f2838x_Examples.h.

    //
    // Note: The internal oscillator CANNOT be used as the PLL source if the
    // AUXPLLCLK is configured to frequencies above 194 MHz.
    //
    //  AUXPLLCLK = (XTAL_OSC) * (IMULT) /(REFDIV) * (ODIV) * (AUXPLLDIV)
    //
    InitAuxPll(XTAL_OSC, IMULT_40, REFDIV_2, ODIV_4, AUXPLLRAWCLK_BY_1, SYSCTL_DCC_BASE1);


    //
    //Give control of SPI-A and GS1 to CPU2
    //
    EALLOW;
    DevCfgRegs.CPUSEL6.bit.SPI_A = 1;       // Give CPU2 control to SPIA
    MemCfgRegs.GSxMSEL.bit.MSEL_GS1 = 1;    // Give CPU2 control of GS1
    EDIS;

    //
    // Send IPC flag to CPU2 signaling the completion of system initialization
    //
    IPCLtoRFlagSet(IPC_FLAG31);

    //
    // Turn on required peripherals
    //
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.DMA = 1;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;
    EDIS;
}


//
// InitEPwm1 - Function to Initialize EPWM1
//
void InitEPwm1()
{
    EPwm1Regs.TBPRD = 6000;                        // Set timer period
    EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;            // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;                      // Clear counter

    //
    // Setup TBCLK
    //
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV4;

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Setup compare
    //
    EPwm1Regs.CMPA.bit.CMPA = 3000;

    //
    // Set actions
    //
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM1A on Zero
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm1Regs.AQCTLB.bit.CAU = AQ_CLEAR;           // Set PWM1A on Zero
    EPwm1Regs.AQCTLB.bit.CAD = AQ_SET;
}

//
// SetupDMA - Function to Setup DMA
//
void SetupDMA()
{
    volatile Uint16 *destination;
    volatile Uint16 *DMADest, *DMASource;

    //
    // Initialize the DMA
    //
    DMAInitialize();

    destination = (volatile Uint16 *)&EPwm1Regs.CMPA + 1 ;
    DMADest = (volatile Uint16 *)destination;
    DMASource = (volatile Uint16 *)0xE000;  // Location of CMPA value from CPU2

    //
    // Setup DMA to transfer a single 16-bit word.  The DMA is setup to run
    // continuously so that an interrupt is not required to restart the RUN
    // bit. The DMA trigger is SPIA-FFTX.
    // These functions are found in f2838x_dma.c.
    //
    DMACH5AddrConfig(DMADest,DMASource);  // Config DMA source and dest address
    DMACH5BurstConfig(1,1,1);             // Setup burst registers
    DMACH5TransferConfig(1,1,1);          // Setup Transfer registers
    DMACH5WrapConfig(0xFFFF,0,0xFFFF,0);
    DMACH5ModeConfig(109, PERINT_ENABLE,ONESHOT_ENABLE,CONT_ENABLE,
                     SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,
                     CHINT_END,CHINT_ENABLE);
    StartDMACH5();
}

//
// dma_isr - DMA Interrupt Service Routine (Uncomment to enable DMA ISR)
//
//interrupt void dma_isr(void)     // DMA Channel 5
//{
//    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
//}

//
// End of file
//
