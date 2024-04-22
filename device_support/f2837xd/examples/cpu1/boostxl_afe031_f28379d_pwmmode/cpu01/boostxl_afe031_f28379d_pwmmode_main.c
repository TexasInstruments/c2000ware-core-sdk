//#############################################################################
//
// FILE:   boostxl_afe031_f28379d_pwmmode_main.c
//
// TITLE:  FSK Transmitter using PWM mode on the AFE031
//

//! \addtogroup cpu01_example_list
//! <h1> FSK Transmitter using PWM mode on the AFE031 </h1>
//!
//! This example sets up the TMDS28379D Launchpad with the BOOSTXL-AFE031 
//! boosterpack to transmit 131.25 and 143.75 KHz FSK signals in a desired
//! sequence, configured using EPWMs
//!
//! \b External \b Connections \n
//!  - Remove JP1, JP2, and JP3 headers on TMDS28379D Launchpad
//!  - Connect the BOOSTXL-AFE031 boosterpack to the upper TMDS28379D 
//!    Launchpad pins
//!  - Supply 15V power via upper right most jumpers
//!
//! \b Watch \b Variables \n
//!  - txDataEnable
//!  - currentChar
//!  - cycleCount
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
#include "F28x_Project.h"     // Device Header file and Examples Include File
#include "SFO_V8.h"
#include "afe031_config.h"

//
// Defines
//
#define EPWM1_TIMER_TBPRD  380  // Period register
#define EPWM1_CMPA         128
#define EPWM1_CMPB         252

#define EPWM2_TIMER_TBPRD  32000  // Period register

#define EPWM_CMP_UP        1
#define EPWM_CMP_DOWN      0

//
//Defines for PWM FSK Application
//
#define EPWM1B_SPACE_COMPARE 229
#define EPWM1A_SPACE_COMPARE 118
#define EPWM1B_MARK_COMPARE  252
#define EPWM1A_MARK_COMPARE  128

#define MARKFREQ  1
#define SPACEFREQ 0
#define YES       1
#define NO        0
#define STOP      2

//
// Globals
//
int MEP_ScaleFactor; // Global variable used by the SFO library
// Used by SFO library (ePWM[0] is a dummy value that isn't used)
volatile struct EPWM_REGS *ePWM[PWM_CH_MAX] = { &EPwm1Regs, &EPwm1Regs };

//
// Globals used for FSK Application
//
Uint16 txDataEnable = 0;
Uint16 txMessage_1[12] = { 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, STOP };     // Logic 1 word
Uint16 txMessage_0[12] = { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, STOP };     // Logic 0 word
//Uint16 txMessage_1[12] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, STOP };
//Uint16 txMessage_1[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, STOP };
Uint16 currentChar = 0;
Uint16 cycleCount = 0;
Uint16 status;
Uint16 packet_to_send = 1;

//
// Function Prototypes
//
void AFE_InitGpio(void);
void EPWM1_Init(void);
void EPWM2_Init(void);
void error (void);
__interrupt void epwm2_isr(void);

#ifdef _FLASH
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;
#endif

void main(void)
{
    //
    // Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    //
    InitSysCtrl();

    //
    // Initialize GPIO:
    // These GPIOs control LEDs, AFE GPIOS.
    //
    InitGpio();
    AFE_InitGpio();

    //
    // Init GPIO pins for ePWM1
    //
    InitEPwm1Gpio();


    //
    // Initialize PIE vector table:
    //
    DINT;

    //
    // Initialize PIE control registers to their default state:
    //
    InitPieCtrl();

    // Disable and clear all CPU interrupts
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;
    PieVectTable.EPWM2_INT = &epwm2_isr;
    EDIS;

    //
    //initialize the ePWM
    //
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    EPWM1_Init();
    EPWM2_Init();

    EALLOW;
    InputXbarRegs.INPUT5SELECT = 500; // Setting to a GPIO number above what exists on device, to avoid interference.
    EPwm1Regs.TBCTL.bit.PHSEN = 1;
    EPwm2Regs.TBCTL.bit.PHSEN = 1;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = 0;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EPwm1Regs.TBCTL.bit.SWFSYNC = 1; // Sync PWM1 and PWM2 clocks
    EDIS;

    //
    // Enable CPU INT3 which is connected to EPWM2 INT:
    //
    IER |= M_INT3;

    //
    // Enable EPWM2 INTn in the PIE: Group 3 interrupt 2
    //
    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;

    status = SFO_INCOMPLETE;

    //
    // Calling SFO() updates the HRMSTEP register with calibrated MEP_ScaleFactor.
    // HRMSTEP must be populated with a scale factor value prior to enabling
    // high resolution period control.
    //
    while(status == SFO_INCOMPLETE)
    {
        status = SFO();
        if(status == SFO_ERROR)
        {
            error();   // SFO function returns 2 if an error occurs & # of MEP
        }              // steps/coarse step exceeds maximum of 255.
    }

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;
    ERTM;

    //
    //Configure AFE
    //
    HAL_afe031Init();

    //
    // Turn on AFE PWM transmit Enable
    //
    HAL_afe031_txPWMEnable();

    //
    // Disable the DAC on the AFE, and set GPIO7 LOW.
    //(When GPIO7 is high, the device enters DAC Mode)
    //
    HAL_afe031_dacDisable();

    //
    //Enable Transmission Mode
    //
    txDataEnable = YES;

    //
    //Create a toggle variable for LEDs
    //
    Uint16 toggle = 0;
    while(1)
    {
        //Toggle LEDs as packets are sent.
        GPIO_WritePin(4, toggle);
        toggle = !toggle;
        GPIO_WritePin(5, toggle);
        DELAY_US(100000);
    }
}

//
// AFE_InitGpio - Initialize the GPIOs on launchpad and boosterpack
//
void AFE_InitGpio()
{
    EALLOW;

    //GPIO-34 - LaunchPad RED LED
    GPIO_SetupPinMux(34, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(34, GPIO_OUTPUT, GPIO_PUSHPULL);

    // GPIO-31 - LaunchPad BLUE LED
    GPIO_SetupPinMux(31, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(31, GPIO_OUTPUT, GPIO_PUSHPULL);

    // GPIO AFE BoosterPack LED
    GPIO_SetupPinMux(4, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(4, GPIO_OUTPUT, GPIO_PUSHPULL);

    GPIO_SetupPinMux(5, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(5, GPIO_OUTPUT, GPIO_PUSHPULL);

    GPIO_WritePin(4, 0);
    GPIO_WritePin(5, 0);
    EDIS;
}

//
// epwm2_isr - EPWM2 ISR
//
__interrupt void epwm2_isr(void)
{
    EALLOW;

    //
    //Checking for cycle count. If cycle count is 209, we can reset the cycle
    //count and enable Tx Data
    //
    if (cycleCount == 209)
    {
        txDataEnable = YES;
        cycleCount = 0;
        EALLOW;
        EPwm1Regs.TZCLR.bit.OST = 1;
        EDIS;
    }

    //
    //Checking for cycle count. If cycle count is 33, then we can disable Tx Data
    //
    if(cycleCount == 33)
    {
        txDataEnable = NO;
        EPwm1Regs.TZFRC.bit.OST = 1;

        //software breakpoint after sending full 33 bit message, for debug
        //asm("   ESTOP0");
    }

    //
    //Check Cycle Count
    //Check for Data to send
    //
    if(txDataEnable == YES)
    {
        //
        // Transmit packet of txMessage_1's
        //
        if(packet_to_send == 1){
            if(txMessage_1[currentChar] == MARKFREQ)
            {
                EPwm1Regs.TBPRD = 380;
                EPwm1Regs.TBPRDHR = (243U << 8);
                EPwm1Regs.CMPA.bit.CMPA = EPWM1A_MARK_COMPARE; // Set compare A value
                EPwm1Regs.CMPB.bit.CMPB = EPWM1B_MARK_COMPARE; // Set Compare B value
            }

            if(txMessage_1[currentChar] == SPACEFREQ)
            {
                EPwm1Regs.TBPRD = 347;
                EPwm1Regs.TBPRDHR = (211U << 8);
                EPwm1Regs.CMPA.bit.CMPA = EPWM1A_SPACE_COMPARE; // Set compare A value
                EPwm1Regs.CMPB.bit.CMPB = EPWM1B_SPACE_COMPARE; // Set Compare B value
            }

            currentChar++;

            if(txMessage_1[currentChar] == STOP)
            {
                currentChar = 0;
            }
        }
        //
        // Transmit packet of txMessage_0's
        //
        else
        {
            if(txMessage_0[currentChar] == MARKFREQ)
            {
                EPwm1Regs.TBPRD = 380;
                EPwm1Regs.TBPRDHR = (243U << 8);
                EPwm1Regs.CMPA.bit.CMPA = EPWM1A_MARK_COMPARE; // Set compare A value
                EPwm1Regs.CMPB.bit.CMPB = EPWM1B_MARK_COMPARE; // Set Compare B value
            }

            if(txMessage_0[currentChar] == SPACEFREQ)
            {
                EPwm1Regs.TBPRD = 347;
                EPwm1Regs.TBPRDHR = (211U << 8);
                EPwm1Regs.CMPA.bit.CMPA = EPWM1A_SPACE_COMPARE; // Set compare A value
                EPwm1Regs.CMPB.bit.CMPB = EPWM1B_SPACE_COMPARE; // Set Compare B value
            }

            currentChar++;

            if(txMessage_0[currentChar] == STOP)
            {
                currentChar = 0;
            }
        }
    }

    cycleCount++; // comment out for continuous run

    EDIS;

    //
    // Clear INT flag for this timer
    //
    EPwm2Regs.ETCLR.bit.INT = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

//
// EPWM1_Init - Initialize EPWM1 configuration
//
void EPWM1_Init()
{
    //
    //Setup for HRPWM
    //
    EALLOW;
    EPwm1Regs.HRMSTEP.bit.HRMSTEP = 55;
    CpuSysRegs.PCLKCR0.bit.HRPWM = 1;
    EDIS;

    //
    // Setup TBCLK
    //
    EPwm1Regs.TBPRD = EPWM1_TIMER_TBPRD;       // Set timer period 380 TBCLKs
    EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;                  // Clear counter

    //
    // Set Compare values
    //
    EPwm1Regs.CMPA.bit.CMPA = EPWM1_CMPA;    // Set compare A value
    EPwm1Regs.CMPB.bit.CMPB = EPWM1_CMPB;    // Set Compare B value

    //
    // Setup counter mode
    //
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up and down
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.FREE_SOFT = 0x03;

    //
    // Setup shadowing
    //
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // Load on Zero
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    //
    //Setup Tripping
    //

    //TZCTL[TZA] = 2: EPWM1A will be forced low on a trip event.
    EPwm1Regs.TZCTL.bit.TZA = 2;
    EPwm1Regs.TZCTL.bit.DCAEVT1 = 3;
    EPwm1Regs.TZCTL.bit.DCAEVT2 = 3;
    // – TZCTL[TZB] = 2: EPWM1B will be forced low on a trip event.
    EPwm1Regs.TZCTL.bit.TZB = 2;
    EPwm1Regs.TZCTL.bit.DCBEVT1 = 3;
    EPwm1Regs.TZCTL.bit.DCBEVT2 = 3;

    //
    // Set actions
    //
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on event A, up
                                                  // count
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;          // Clear PWM1A on event A,
                                                  // down count
    EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;            // Set PWM1B on event B, up
                                                  // count
    EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;          // Clear PWM1B on event B,
                                                  // down count

    //
    //Disable Interrupt
    //
    EPwm1Regs.ETSEL.bit.INTEN = 0;                // disable INT

    //
    //HRPWM SETUP
    //
    EALLOW;
    EPwm1Regs.HRCNFG.bit.HRLOAD = 2;
    EPwm1Regs.HRCNFG.bit.AUTOCONV = 1;
    EPwm1Regs.HRCNFG.bit.EDGMODE = 3;
    EPwm1Regs.HRPCTL.bit.HRPE = 1;
    EDIS;
}

//
// EPWM2_Init - Initialize EPWM2 configuration
//
void EPWM2_Init()
{
    //
    // Setup TBCLK
    //
    EPwm2Regs.TBPRD = EPWM2_TIMER_TBPRD;         // Set timer period 16000 TBCLKs
    EPwm2Regs.TBPHS.bit.TBPHS = 0x0000;          // Phase is 0
    EPwm2Regs.TBCTR = 0x0000;                    // Clear counter

    //
    // Setup counter mode
    //
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up/down
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;      // Clock ratio to SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV4;

    //
    // Setup shadowing
    //
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // Load on Zero
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;


    //
    // Interrupt where we will change the Compare Values
    //
    EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;    // Select INT on period event
    EPwm2Regs.ETSEL.bit.INTEN = 1;              // Enable INT
    EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;         // Generate INT on every event
}

//
// error - Halt debugger when called
//
void error(void)
{
    ESTOP0;         // Stop here and handle error
}

//
// End of file
//

