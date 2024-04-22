//###########################################################################
//
// FILE:   cmpss_asynch_cpu01.c
//
// TITLE:  CMPSS Asynchronous Trip Example Configuration for F2837xD.
//
//! \addtogroup cpu01_example_list
//! <h1> CMPSS Asynchronous Trip </h1>
//!
//! This example enables the CMPSS1 COMPH comparator and feeds the asynch
//! CTRIPOUTH to GPIO14/OUTPUTXBAR3 pin and CTRIPH to GPIO15/EPWM8B
//!
//! The COMPH inputs are:
//!   -  POS signal from CMPIN1P pin
//!   -  NEG signal from internal DACH
//!
//
//###########################################################################
//
// $Release Date:  $
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
#include "F28x_Project.h"

//
// Defines
//
//definitions for selecting DACH reference
#define REFERENCE_VDDA     0
#define REFERENCE_VDAC     1
//definitions for COMPH input selection
#define NEGIN_DAC          0
#define NEGIN_PIN          1
//definitions for CTRIPH/CTRIPOUTH output selection
#define CTRIP_ASYNCH       0
#define CTRIP_SYNCH        1
#define CTRIP_FILTER       2
#define CTRIP_LATCH        3
//definitions for selecting output pin
#define GPIO_CTRIP_PIN_NUM      14 //OUTPUTXBAR3 is mux'd with GPIO14
#define GPIO_CTRIP_PER_NUM       6 //OUTPUTXBAR3 is peripheral option 6 for
                                   //GPIO14
#define GPIO_CTRIPOUT_PIN_NUM   15 //EPWM8B is mux'd with GPIO15
#define GPIO_CTRIPOUT_PER_NUM    1 //EPWM8B is peripheral option 1 for GPIO15

//
// Function Prototypes
//
void InitCMPSS(void);
void InitEPWM(void);

//
// Main
//
void main(void)
{
//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
    InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
//
    InitGpio();

//
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
    DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
//
    InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;

//
// Configure Comparator COMP1H to accept POS input from pin and NEG input
// from DAC
//
    InitCMPSS();

//
// Configure COMP1 to feed TRIP4 EPWM DC trip input
//
    InitEPWM();

//
// Configure GPIO14 to output CTRIP1H/EPWM TRIP4
//
    GPIO_SetupPinMux(GPIO_CTRIP_PIN_NUM, GPIO_MUX_CPU1, GPIO_CTRIP_PER_NUM);

//
// Configure GPIO15 to output CTRIPOUT1H
//
    GPIO_SetupPinMux(GPIO_CTRIPOUT_PIN_NUM, GPIO_MUX_CPU1,
                     GPIO_CTRIPOUT_PER_NUM);

    while(1)
    {
        //
        // Trip flags set when CTRIP signal is asserted
        //
        if( EPwm8Regs.TZFLG.bit.OST )
        {
            EALLOW;

            //
            // Wait for comparator CTRIP to de-assert
            //
            while( Cmpss1Regs.COMPSTS.bit.COMPHSTS );

            //
            // Clear trip flags
            //
            EPwm8Regs.TZCLR.bit.OST = 1;
            EPwm8Regs.TZCLR.bit.INT = 1;
            EDIS;
        }
    }
}

//
// InitCMPSS - Initialize CMPSS1 and configure settings
//
void InitCMPSS(void)
{
    EALLOW;

    //
    //Enable CMPSS
    //
    Cmpss1Regs.COMPCTL.bit.COMPDACE = 1;

    //
    //NEG signal comes from DAC
    //
    Cmpss1Regs.COMPCTL.bit.COMPHSOURCE = NEGIN_DAC;

    //
    //Use VDDA as the reference for DAC
    //
    Cmpss1Regs.COMPDACCTL.bit.SELREF = REFERENCE_VDDA;

    //
    //Set DAC to midpoint for arbitrary reference
    //
    Cmpss1Regs.DACHVALS.bit.DACVAL = 2048;

    //
    // Configure CTRIPOUT path
    // Asynch output feeds CTRIPH and CTRIPOUTH
    //
    Cmpss1Regs.COMPCTL.bit.CTRIPHSEL = CTRIP_ASYNCH;
    Cmpss1Regs.COMPCTL.bit.CTRIPOUTHSEL = CTRIP_ASYNCH;

    //
    // Configure CTRIPOUTH output pin
    // Configure OUTPUTXBAR3 to be CTRIPOUT1H
    //
    OutputXbarRegs.OUTPUT3MUX0TO15CFG.bit.MUX0 = 0;

    //
    //Enable OUTPUTXBAR3 Mux for Output
    //
    OutputXbarRegs.OUTPUT3MUXENABLE.bit.MUX0 = 1;
    EDIS;
}

//
// InitEPWM - Initialize EPWM8 module settings
//
void InitEPWM(void)
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

    //
    //Configure EPWM to run at SYSCLK
    //
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0;
    EPwm8Regs.TBCTL.bit.CLKDIV = 0;
    EPwm8Regs.TBCTL.bit.HSPCLKDIV = 0;

    //
    //Initialize dummy values for EPWM CTR/PRD
    //
    EPwm8Regs.TBCTR = 0;
    EPwm8Regs.TBPRD = 0xFFFF;

    //
    //Configure EPWM8B to output high on TZB TRIP
    //
    EPwm8Regs.TZCTL.bit.TZB = TZ_FORCE_HI;

    //
    //Configure DCB to be TRIP4
    //
    EPwm8Regs.TZDCSEL.bit.DCBEVT1 = TZ_DCBH_HI;
    EPwm8Regs.DCTRIPSEL.bit.DCBHCOMPSEL = 0xF;
    EPwm8Regs.DCBHTRIPSEL.bit.TRIPINPUT4 = 1;

    //
    //Configure DCB as OST
    //
    EPwm8Regs.TZSEL.bit.DCBEVT1 = 1;

    //
    //Configure DCB path to be unfiltered & async
    //
    EPwm8Regs.DCBCTL.bit.EVT1SRCSEL = DC_EVT1;
    EPwm8Regs.DCBCTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;

    //
    //Configure TRIP4 to be CTRIP1H
    //
    EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX0 = 0;

    //
    //Enable TRIP4 Mux for Output
    //
    EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX0 = 1;

    //
    // Clear trip flags
    //
    EPwm8Regs.TZCLR.bit.OST = 1;
    EPwm8Regs.TZCLR.bit.INT = 1;

    //
    //Enable DCB interrupt
    //
    EPwm8Regs.TZEINT.bit.OST = 1;

    //
    // Enable PWM
    //
    EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;

    EDIS;
}

//
// End of file
//
