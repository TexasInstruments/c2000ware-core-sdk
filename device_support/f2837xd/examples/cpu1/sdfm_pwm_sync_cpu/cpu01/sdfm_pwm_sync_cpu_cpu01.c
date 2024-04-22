//###########################################################################
//
// FILE:   sdfm_pwm_sync_cpu_cpu01.c
//
// TITLE:  SDFM PWM sync Example for F2837xD.
//
//! \addtogroup cpu01_example_list
//! <h1> SDFM PWM Sync </h1>
//!
//! In this example, SDFM filter data is read by CPU in SDFM ISR routine. The
//! SDFM configuration is shown below:
//!     - SDFM1 is used in this example
//!     - MODE0 Input control mode selected
//!     - Comparator settings
//!         - Sinc3 filter selected
//!         - OSR = 32
//!         - HLT = 0x7FFF (Higher threshold setting)
//!         - LLT  = 0x0000(Lower threshold setting)
//!  -  Data filter settings
//!      - All the 4 filter modules enabled
//!      - Sinc3 filter selected
//!      - OSR = 256
//!      - All the 4 filters are synchronized by using PWM
//!       (Master Filter enable bit)
//!      - Filter output represented in 16 bit format
//!      - In order to convert 25 bit Data filter
//!        into 16 bit format user needs to right shift by 9 bits for
//!        Sinc3 filter with OSR = 256
//!  - Interrupt module settings for SDFM filter
//!      - All the 4 higher threshold comparator interrupts disabled
//!      - All the 4 lower threshold comparator interrupts disabled
//!      - All the 4 modulator failure interrupts disabled
//!      - All the 4 filter will generate interrupt when a new filter data
//!        is available
//! \b External \b Connections \n
//!   - SDFM_PIN_MUX_OPTION1 Connect Sigma-Delta streams to
//!     (SDx-D1, SDx-C1 to SDx-D4,SDx-C4) on GPIO16-GPIO31
//!   - SDFM_PIN_MUX_OPTION2 Connect Sigma-Delta streams to
//!     (SDx-D1, SDx-C1 to SDx-D4,SDx-C4) on GPIO48-GPIO63
//!   - SDFM_PIN_MUX_OPTION3 Connect Sigma-Delta streams to
//!     (SDx-D1, SDx-C1 to SDx-D4,SDx-C4) on GPIO122-GPIO137
//!
//! \b Watch \b Variables \n
//! -  \b Filter1_Result - Output of filter 1
//! -  \b Filter2_Result - Output of filter 2
//! -  \b Filter3_Result - Output of filter 3
//! -  \b Filter4_Result - Output of filter 4
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
#include "F2837xD_struct.h"
#include "F2837xD_sdfm_drivers.h"

//
// Defines
//
#define MAX_SAMPLES               1024
#define SDFM_PIN_MUX_OPTION1      1
#define SDFM_PIN_MUX_OPTION2      2
#define SDFM_PIN_MUX_OPTION3      3
#define EPWM_TIMER_TBPRD          65535  // ePWM Period register

//
// Globals
//
uint16_t gPeripheralNumber;
uint16_t gPWM_number = 11; // ePWM 11 for synchronizing SDFM1 filters
int16_t  Filter1_Result[MAX_SAMPLES];
int16_t  Filter3_Result[MAX_SAMPLES];
int16_t  Filter2_Result[MAX_SAMPLES];
int16_t  Filter4_Result[MAX_SAMPLES];
#pragma DATA_SECTION(Filter1_Result,"Filter1_RegsFile");
#pragma DATA_SECTION(Filter2_Result,"Filter2_RegsFile");
#pragma DATA_SECTION(Filter3_Result,"Filter3_RegsFile");
#pragma DATA_SECTION(Filter4_Result,"Filter4_RegsFile");

//
// Function Prototypes
//
void Sdfm_configurePins(uint16_t);
void InitEPwm(void);
void done(void);
__interrupt void Sdfm1_ISR(void);
__interrupt void Sdfm2_ISR(void);

//
// Main
//
void main(void)
{
   uint16_t  pinMuxoption;
   uint16_t  HLT, LLT;

//
// Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
    InitSysCtrl();

//
// Clear all __interrupts and initialize PIE vector table:
// Disable CPU __interrupts
//
    DINT;

//
// Initialize PIE control registers to their default state.
// The default state is all PIE __interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
//
    InitPieCtrl();

//
// Disable CPU __interrupts and clear all CPU __interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the __interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_SysCtrl.c.
// This function is found in F2837xD_SysCtrl.c.
//
    InitPieVectTable();

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//
    EALLOW;
    PieVectTable.SD1_INT = &Sdfm1_ISR;
    PieVectTable.SD2_INT = &Sdfm2_ISR;
    EDIS;

    EALLOW;
//
// Enable CPU INT5 which is connected to SDFM INT
//
    IER |= M_INT5;

//
// Enable SDFM INTn in the PIE: Group 5 __interrupt 9-10
//
    PieCtrlRegs.PIEIER5.bit.INTx9 = 1;    // SDFM1 interrupt enabled
    PieCtrlRegs.PIEIER5.bit.INTx10 = 1;   // SDFM2 interrupt enabled
    EINT;

#ifdef CPU1
    pinMuxoption = SDFM_PIN_MUX_OPTION1;
//
// Configure GPIO pins as SDFM pins
//
    Sdfm_configurePins(pinMuxoption);
#endif

//
// Select SDFM1
//
    gPeripheralNumber = SDFM1;

//
// Input Control Module
//
// Configure Input Control Mode: Modulator Clock rate = Modulator data rate
//
    Sdfm_configureInputCtrl(gPeripheralNumber, FILTER1, MODE_0);
    Sdfm_configureInputCtrl(gPeripheralNumber, FILTER2, MODE_0);
    Sdfm_configureInputCtrl(gPeripheralNumber, FILTER3, MODE_0);
    Sdfm_configureInputCtrl(gPeripheralNumber, FILTER4, MODE_0);

//
// Comparator Module
//
    HLT = 0x7FFF;    //Over value threshold settings
    LLT = 0x0000;    //Under value threshold settings

//
// Configure Comparator module's comparator filter type and comparator's OSR
// value, higher threshold, lower threshold
//
    Sdfm_configureComparator(gPeripheralNumber, FILTER1, SINC3, OSR_32,
                             HLT, LLT);
    Sdfm_configureComparator(gPeripheralNumber, FILTER2, SINC3, OSR_32,
                             HLT, LLT);
    Sdfm_configureComparator(gPeripheralNumber, FILTER3, SINC3, OSR_32,
                             HLT, LLT);
    Sdfm_configureComparator(gPeripheralNumber, FILTER4, SINC3, OSR_32,
                             HLT, LLT);

//
// Enable Master filter bit: Unless this bit is set none of the filter modules
// can be enabled. All the filter modules are synchronized when master filter
// bit is enabled after individual filter modules are enabled. All the filter
// modules are asynchronized when master filter bit is enabled before
// individual filter modules are enabled.
//
    Sdfm_enableMFE(gPeripheralNumber);

//
// Data filter Module
//
// Configure Data filter modules filter type, OSR value and
// enable / disable data filter
//
    Sdfm_configureData_filter(gPeripheralNumber, FILTER1, FILTER_ENABLE, SINC3,
                              OSR_256, DATA_16_BIT, SHIFT_9_BITS);
    Sdfm_configureData_filter(gPeripheralNumber, FILTER2, FILTER_ENABLE, SINC3,
                              OSR_256, DATA_16_BIT, SHIFT_9_BITS);
    Sdfm_configureData_filter(gPeripheralNumber, FILTER3, FILTER_ENABLE, SINC3,
                              OSR_256, DATA_16_BIT, SHIFT_9_BITS);
    Sdfm_configureData_filter(gPeripheralNumber, FILTER4, FILTER_ENABLE, SINC3,
                              OSR_256, DATA_16_BIT, SHIFT_9_BITS);

//
// PWM11.CMPC, PWM11.CMPD, PWM12.CMPC and PWM12.CMPD signals cannot synchronize
// the filters. This option is not being used in this example.
//
    Sdfm_configureExternalreset(gPeripheralNumber,FILTER_1_EXT_RESET_ENABLE,
                                FILTER_2_EXT_RESET_ENABLE,
                                FILTER_3_EXT_RESET_ENABLE,
                                FILTER_4_EXT_RESET_ENABLE);
//
// Init EPWMs
//
    InitEPwm();

//
// Enable interrupts
//
// Following SDFM interrupts can be enabled / disabled using this function.
//  Enable / disable comparator high threshold
//  Enable / disable comparator low threshold
//  Enable / disable modulator clock failure
//  Enable / disable filter acknowledge
//
    Sdfm_configureInterrupt(gPeripheralNumber, FILTER1, IEH_DISABLE,
                            IEL_DISABLE, MFIE_ENABLE, AE_ENABLE);
    Sdfm_configureInterrupt(gPeripheralNumber, FILTER2, IEH_DISABLE,
                            IEL_DISABLE, MFIE_ENABLE, AE_ENABLE);
    Sdfm_configureInterrupt(gPeripheralNumber, FILTER3, IEH_DISABLE,
                            IEL_DISABLE, MFIE_ENABLE, AE_ENABLE);
    Sdfm_configureInterrupt(gPeripheralNumber, FILTER4, IEH_DISABLE,
                            IEL_DISABLE, MFIE_ENABLE, AE_ENABLE);

    while((*EPWM[gPWM_number]).TBCTR < 550);

//
// Enable master interrupt so that any of the filter interrupts can trigger
// by SDFM interrupt to CPU
//
    Sdfm_enableMIE(gPeripheralNumber);

    while(1);
}

//
// Sdfm1_ISR - SDFM 1 ISR
//
__interrupt void Sdfm1_ISR(void)
{
    uint32_t sdfmReadFlagRegister = 0;
    static uint16_t loopCounter1 = 0;

    //
    // Read SDFM flag register (SDIFLG)
    //
    sdfmReadFlagRegister = Sdfm_readFlagRegister(gPeripheralNumber);

    if(loopCounter1 < MAX_SAMPLES)
    {
        //
        // Read each SDFM filter output and store it in respective filter
        // result array
        //
        Filter1_Result[loopCounter1] = SDFM1_READ_FILTER1_DATA_16BIT;
        Filter2_Result[loopCounter1] = SDFM1_READ_FILTER2_DATA_16BIT;
        Filter3_Result[loopCounter1] = SDFM1_READ_FILTER3_DATA_16BIT;
        Filter4_Result[loopCounter1++] = SDFM1_READ_FILTER4_DATA_16BIT;

        //
        // Clear SDFM flag register
        //
        Sdfm_clearFlagRegister(gPeripheralNumber,sdfmReadFlagRegister);
        sdfmReadFlagRegister = Sdfm_readFlagRegister(gPeripheralNumber);

        if(sdfmReadFlagRegister != 0x0)
        {
            ESTOP0;
        }
    }
    else
    {
        ESTOP0;
        done();
    }

    //
    // Acknowledge this __interrupt to receive more __interrupts from group 5
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
}

//
// Sdfm2_ISR - SDFM 2 ISR
//
__interrupt void Sdfm2_ISR(void)
{
    uint32_t sdfmReadFlagRegister;
    static uint16_t loopCounter1 = 0;

    //
    // Read SDFM flag register (SDIFLG)
    //
    sdfmReadFlagRegister = Sdfm_readFlagRegister(gPeripheralNumber);

    if(loopCounter1 < MAX_SAMPLES)
    {
        //
        // Read each SDFM filter output and store it in respective filter
        // result array
        //
        Filter1_Result[loopCounter1] = SDFM2_READ_FILTER1_DATA_16BIT;
        Filter2_Result[loopCounter1] = SDFM2_READ_FILTER2_DATA_16BIT;
        Filter3_Result[loopCounter1] = SDFM2_READ_FILTER3_DATA_16BIT;
        Filter4_Result[loopCounter1++] = SDFM2_READ_FILTER4_DATA_16BIT;

        //
        // Clear SDFM flag register
        //
        Sdfm_clearFlagRegister(gPeripheralNumber,sdfmReadFlagRegister);
        sdfmReadFlagRegister = Sdfm_readFlagRegister(gPeripheralNumber);

        if(sdfmReadFlagRegister != 0x0)
        {
             ESTOP0;
        }
    }
    else
    {
        ESTOP0;
        done();
    }

    //
    // Acknowledge this __interrupt to receive more __interrupts from group 5
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
}

//
// Sdfm_configurePins - Configure SDFM GPIOs
//
void Sdfm_configurePins(uint16_t sdfmPinOption)
{
    uint16_t pin;
    switch (sdfmPinOption)
    {
        case SDFM_PIN_MUX_OPTION1:
            for(pin=16;pin<=31;pin++)
            {
                GPIO_SetupPinOptions(pin, GPIO_INPUT, GPIO_ASYNC);
                GPIO_SetupPinMux(pin,GPIO_MUX_CPU1,7);
            }
            break;

        case SDFM_PIN_MUX_OPTION2:
            for(pin=48;pin<=63;pin++)
            {
                GPIO_SetupPinOptions(pin, GPIO_INPUT, GPIO_ASYNC);
                GPIO_SetupPinMux(pin,GPIO_MUX_CPU1,7);
            }
            break;

        case SDFM_PIN_MUX_OPTION3:
            for(pin=122;pin<=137;pin++)
            {
                GPIO_SetupPinOptions(pin, GPIO_INPUT, GPIO_ASYNC);
                GPIO_SetupPinMux(pin,GPIO_MUX_CPU1,7);
            }
            break;
    }
}

//
// InitEPwm - Initialize specified EPWM settings
//
void InitEPwm(void)
{
    uint16_t CMPC,CMPD;

    CMPC = 200;
    CMPD = 200;

#ifdef CPU1
    GPIO_SetupPinOptions(4, GPIO_OUTPUT, GPIO_ASYNC);
    GPIO_SetupPinMux(4,GPIO_MUX_CPU1,1);
#endif

    EALLOW;

    //
    // Allows all users to globally synchronize all enabled ePWM modules to
    // the time-base clock (TBCLK)
    //
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;

    //
    // Setup TBCLK
    //
    (*EPWM[gPWM_number]).TBPHS.bit.TBPHS = 0x0000;    // Phase is 0
    (*EPWM[gPWM_number]).TBCTR = 0x0000;              // Clear counter
    (*EPWM[gPWM_number]).TBPRD = EPWM_TIMER_TBPRD;    // Set timer period
                                                      // 801 TBCLKs.

    (*EPWM[gPWM_number]).CMPC = CMPC;                 // Set Compare C value
    (*EPWM[gPWM_number]).CMPD = CMPD;                 // Set Compare D value

    (*EPWM[gPWM_number]).CMPA.bit.CMPA = CMPC;        // Set Compare C value
    (*EPWM[gPWM_number]).CMPB.bit.CMPB = CMPD;        // Set Compare D value

    //
    // Setup counter mode
    //
    (*EPWM[gPWM_number]).TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    (*EPWM[gPWM_number]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
    (*EPWM[gPWM_number]).TBCTL.bit.CLKDIV = TB_DIV1;

    //
    // Set actions
    //
    (*EPWM[gPWM_number]).AQCTLA.bit.CAU = 3;      // Set PWM1A on event A, up
                                                  // count

    //
    // Set actions
    //
    (*EPWM[gPWM_number]).AQCTLB.bit.CBU = 3;      // Set PWM1A on event A, up
                                                  // count

    EDIS;
}

//
// done - Function to halt debugger and stop application
//
void done(void)
{
    asm(" ESTOP0");
    for (;;);
}

//
// End of file
//
