//#############################################################################
//
// FILE:   boostxl_afe031_dacmode_main.c
//
// TITLE:  FSK Transmitter using DAC mode on the AFE031
//
//! \addtogroup cpu01_example_list
//! <h1> FSK Transmitter using DAC mode on the AFE031 </h1>
//!
//! This example sets up the TMDS28379D Launchpad with the BOOSTXL-AFE031 
//! boosterpack to transmit 131.25 and 143.75 KHz FSK signals in a desired
//! sequence, configured using the AFE031's DAC 
//!
//! \b External \b Connections \n
//!  - Remove JP1, JP2, and JP3 headers on TMDS28379D Launchpad
//!  - Connect the BOOSTXL-AFE031 boosterpack to the upper TMDS28379D 
//!    Launchpad pins
//!
//! \b Watch \b Variables \n
//!  - txDataEnable
//!  - currentChar
//!  - cycleCount
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include "F28x_Project.h"
#include "boostxl_afe031_F2837xD_Sci.h"
#include "afe031_config.h"
#include "hal_spi.h"
#include "sine_table.h"

//
// Defines
//
#define EPWM1_TIMER_TBPRD   50
#define EPWM2_TIMER_TBPRD   16000
#define EPWM_CMP_UP         1
#define EPWM_CMP_DOWN       0

#define MARKFREQ            1
#define SPACEFREQ           0
#define YES                 1
#define NO                  0

//
// A N-Point sine table is decimated and fed to the AFE031 DAC via DMA at a
// 1MHz rate to produce the desired MARK and SPACE frequencies for each bit.
// Decimation calculations for SPACE and MARK frequencies w/1MHz output rate:
// Step Size = #Total/(#Points/Cycle), where #Points/Cycle = DAC_Hz/Target_Hz
// MARK Step = N/(1000KHz/131.25KHz) = N*0.13125 (537.6 for 4096pt sine wave)
// SPACE Step = N/(1000KHz/143.75KHz) = N*0.14375 (588.8 for 4096pt sine wave)
// PWM1 paces the 1us DMA DAC Output from 50MHz Base Clock (TBPRD=50, DIV=1)
// PWM2 paces the 5.12ms Bit Frame from 50MHz Base Clock (TBRD=16000, DIV=16)
// REFERENCES:
// 1. The SunSpec Rapid Shutdown Application Note can be found here:
// http://www.ti.com/lit/ug/tidue68/tidue68.pdf
// 2. A sine table calculator can be found here:
// https://daycounter.com/Calculators/Sine-Generator-Calculator.phtml
//
#define N_CODE              1024
#define N_POINT             sizeof(sineTable)
#define markSineStep        (float)N_POINT*((float)131250/(float)1000000)
#define spaceSineStep       (float)N_POINT*((float)143750/(float)1000000)

//
// Platform-dependent GPIO
//
#define GPIO_RED_LED_LP     34
#define GPIO_BLUE_LED_LP    31
#define GPIO_RED_LED2_BP    4
#define GPIO_BLUE_LED1_BP   5
#define GPIO_TEST_MODE      6
#define GPIO_TX_MODE        0

//
// Since the on-chip AFE031 Low Pass Filter (LPF) is designed for a
// 145kHz cutoff frequency for CENELEC BCD (bit 3 of Control1 register),
// significant attenuation is observed on the SPACE carrier signal.
// This inherent AFE031 attenuation effect is effectively mitigated by
// applying different firmware gain value while modulating SPACE or MARK.
// Also, carrier signal glitches and distortion observed at carrier wave
// transitions are minimized by:
// 1. Only resetting the DMA buffers at Idle-to-Transmit, SPACE-to-MARK
// and MARK-to-SPACE carrier signal transitions.
// 2. Assigning priorities to DMA (higher) and PWM (lower) interrupts and
// enabling interrupt service nesting, per TI-WIKI page found here:
// http://processors.wiki.ti.com/index.php/Interrupt_Nesting_on_C28x
//
#include "boostxl_afe031_f28379d_dacmode_isr.h"
#define ISRS_GROUP1         (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6|M_INT7|M_INT8)
#define NaN                 0xFFFF

//
// NOTE: Firmware gain values calibrated w/1500nF, 1.5kV line coupling capacitor
// and multiplied by 1024 to enable faster integer division (i.e. logical shift).
//
Uint32 GAIN_SPACE_x1024 = 676;  // SPACE Gain x 1024
Uint32 GAIN_MARK_x1024 = 558;   // MARK Gain x 1024

//
// Offset DAC code to keep output in linear region (0.1V < DAC_OUT < 3.2V).
// NOTE: The DAC offset limits the firmware gain values (1024 - 2*offset).
//
Uint32 DAC_CODE_OFFSET = 64;

//
// Global thermal shutdown and overcurrent event counters
//
Uint32 intThermal = 0;
Uint32 intCurrent = 0;

//
// Test Mode Globals
//
Uint16 tmLast = NaN;
Uint16 tmUser = NaN;
Uint16 tmJump = NaN;
Uint16 tmCont = NO;
Uint16 txDataEnable = NO;
Uint16 txChar = NaN;
Uint16 txBuf[] = { 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1 };       // Transmit Buffer
Uint16 txLogic0[] = { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0 };    // Logic "0" Word
Uint16 txLogic1[] = { 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1 };    // Logic "1" Word
Uint16 txMark[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };      // Continuous MARK
Uint16 txSpace[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };     // Continuous SPACE

//
// Other Globals
//
Uint16 currentChar = 0;
Uint16 cycleCount = 0;
Uint16 pingpongBufSel = 0;
float sinePosition = 0;
float sineStep = 0;

//
// Function Prototypes
//
void AFE_InitGpio(void);
void EPWM2_Init(void);
void EPWM1_Init(void);
void pwm_enable(Uint16 enable);
void dma_init(void);
void dma_start (void);
void fill_SineTable(Uint16 *buf,Uint16 bufSize);
void reset_DMASineTables(void);
__interrupt void epwm2_isr(void);
__interrupt void dma_isr(void);
#ifdef _FLASH
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;
extern Uint16 SineTableLoadStart;
extern Uint16 SineTableLoadSize;
extern Uint16 SineTableRunStart;
#endif

#define BURST       1       // write 7 to the register for a burst size of 8
#define TRANSFER    15      // [(MEM_BUFFER_SIZE/(BURST + 1)) - 1]

#pragma DATA_SECTION(pingBuf, "ramgs0");
#pragma DATA_SECTION(pongBuf, "ramgs0");

Uint16 pingBuf[TRANSFER+1];
Uint16 pongBuf[TRANSFER+1];

void main(void)
{
    //
    // Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    //
    InitSysCtrl();

    //
    // For Flash mode, copy the sine table to RAM
    //
#ifdef _FLASH
    memcpy(&SineTableRunStart, &SineTableLoadStart, (size_t)&SineTableLoadSize);
#endif

    //
    // Initialize LaunchPad GPIO
    //
    InitGpio();

    //
    // For this case just init GPIO pins for ePWM1
    //
    InitEPwm1Gpio();

    //
    // Initialize BoosterPack GPIO
    //
    AFE_InitGpio();

    //
    // Initialize transmit data buffer based on test mode jumpers, Notes:
    // 1. Test Mode selected with jumper across J6.60-J8.80
    // 2. Tx Mode selected with jumper across J2.20-J4.40
    // 3. Input grounded with jumper installed, otherwise pulled high
    // 4. Pin states inverted in test mode computation (NO jumper='0')
    //    Test Mode   Tx Mode   Function
    //    ---------   -------   --------
    //        0          0      Logic "1" Word (Default, w/NO jumpers)
    //        0          1      Logic "0" Word
    //        1          0      Continuous MARK
    //        1          1      Continuous SPACE
    //
    GPIO_SetupPinMux(GPIO_TX_MODE, GPIO_MUX_CPU1, 0);       // txMode
    GPIO_SetupPinOptions(GPIO_TX_MODE, GPIO_INPUT, GPIO_OPENDRAIN | GPIO_PULLUP);
    GPIO_SetupPinMux(GPIO_TEST_MODE, GPIO_MUX_CPU1, 0);     // testMode
    GPIO_SetupPinOptions(GPIO_TEST_MODE, GPIO_INPUT, GPIO_OPENDRAIN | GPIO_PULLUP);

    //
    // Disable interrupts.
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    //
    InitPieCtrl();

    // Disable and clear all CPU interrupts
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.

    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;
    PieVectTable.EPWM2_INT = &epwm2_isr;
    PieVectTable.DMA_CH1_INT= &dma_isr;
    CpuSysRegs.SECMSEL.bit.PF2SEL = 1;
    EDIS;

    //
    // initialize the ePWM
    //
    EPWM1_Init();
    EPWM2_Init();

    EALLOW;
	// Setting to a GPIO number above what exists on device, to avoid interference.
    InputXbarRegs.INPUT5SELECT = 500; 
    EPwm1Regs.TBCTL.bit.PHSEN = 1;
    EPwm2Regs.TBCTL.bit.PHSEN = 1;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = 0;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EPwm1Regs.TBCTL.bit.SWFSYNC = 1; // Sync PWM1 and PWM2 clocks
    EDIS;

    //
    // Enable CPU INT3 which is connected to EPWM2 INT:
    //
    IER |= M_INT3 + M_INT7;

    //
    // Enable TINT0 in the PIE: Group 1 interrupt 7
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
    PieCtrlRegs.PIEIER7.bit.INTx1 = 1;   // Enable PIE Group 7, INT 1 (DMA CH1)

    //
    // Configure AFE
    //
    HAL_afe031Init();

    //
    // Turn on AFE DAC transmit Enable
    //
    HAL_afe031_txDACEnable();

    //
    // NOTE: Enable INT output/flags after initializing DAC/PA.
    //
    HAL_afe031_cfgInt();

    //
    // Enable the DAC on the AFE, and set GPIO7 HIGH.
    // (When GPIO7 is high, the device enters DAC Mode)
    //
    HAL_afe031_dacEnable();

    //
    // Enable interrupts and real-time debug mode
    //
    EINT;
    ERTM;

    //
    // Initialize DMA
    //
    dma_init();
    dma_start();

    EPwm1Regs.ETSEL.bit.SOCAEN = 1;    // Enable SOC on A group

    //
    // Initialize loop variables
    //
    Uint32 toggle = 0;
    Uint16 tmShutdown = NO;
    Uint16 tmUserLast = NaN;
    Uint16 tmJumpLast = NaN;

    while(1)
    {
        Uint16 tmSet = NO;
        Uint16 tmChg = NO;
        Uint16 *tp = txBuf;

        //
        // Service serial link.
        //
        scia_service();

        //
        // Check if jumper- or user-selected test mode has changed.
        //
        tmJump = ((~GPIO_ReadPin(GPIO_TEST_MODE) & 1) << 1) | (~GPIO_ReadPin(GPIO_TX_MODE) & 1);
        if (tmJump != tmJumpLast)
        {
            tmLast = tmJump;
            tmJumpLast = tmJump;
            tmChg = YES;
        }
        else if (tmUser != tmUserLast)
        {
            tmLast = tmUser;
            tmUserLast = tmUser;
            tmChg = YES;
        }

        //
        // Check if jumper- or user-selected test mode has changed.
        //
        if (tmChg)
        {
            switch (tmLast)
            {
                case TM_TRANSMIT_KA:
                    tp = txLogic1;
                    tmSet = YES;
                    tmCont = NO;
                    break;
                case TM_TRANSMIT_AS:
                    tp = txLogic0;
                    tmSet = YES;
                    tmCont = NO;
                    break;
                case TM_TRANSMIT_MARK:
                    tp = txMark;
                    tmSet = YES;
                    tmCont = YES;
                    break;
                case TM_TRANSMIT_SPACE:
                    tp = txSpace;
                    tmSet = YES;
                    tmCont = YES;
                    break;
                case TM_TRANSMIT_W1:
                    tp = txLogic1;
                    tmSet = YES;
                    tmCont = YES;
                    break;
                case TM_TRANSMIT_W0:
                    tp = txLogic0;
                    tmSet = YES;
                    tmCont = YES;
                    break;
                case TM_PA_SHUTDOWN:
                    HAL_afe031_shutdown(1);
                    tmShutdown = YES;
                    break;
                case TM_PA_ENABLE:
                    HAL_afe031_shutdown(0);
                    tmShutdown = NO;
                    tmSet = YES;
                    break;
                default:
                    break;
            }
        }

        //
        // AFE031 Power Amp (PA) overcurrent and thermal shutdown event monitoring
        // IMPORANT: Do this after checking test mode, as enabling the AFE031's PA
        // causes transient overcurrent condition.
        //
#ifndef INT_DISABLE
        if (HAL_afe031_intAsserted())
        {
            pwm_enable(0);
            txDataEnable = NO;
            GPIO_WritePin(GPIO_BLUE_LED1_BP, 1);
            HAL_afe031_dacDisable();
            Uint16 regReset = HAL_afe031_regRead(HAL_AFE031_RESET_REG) & 0xff;
            if (regReset & 0x20)
            {
                intThermal++;
            }
            if (regReset & 0x40)
            {
                intCurrent++;
            }
            HAL_afe031_cfgInt();
            HAL_afe031_dacEnable();

            //
            // NOTE: INT flags are set while PA is in shutdown mode and
            // overcurrent and thermal SD event counters are cleared when
            // the power amplifier is enabled and transmission is reset.
            //
            if (!tmShutdown)
            {
                tmSet = YES;
            }
        }
#endif
        //
        // Reset transmission/parameters.
        //
        if (tmSet)
        {
            // Disable PWM counters
            pwm_enable(0);
            currentChar = 0;
            cycleCount = 0;
            sinePosition = 0;
            reset_DMASineTables();
            memcpy(txBuf, tp, sizeof(txBuf));
            intCurrent = 0;
            intThermal = 0;
            txDataEnable = YES;
            txChar = NaN;
            // Enable PWM counters to paces DMA/SPI
            pwm_enable(1);
            // Turn on blue LED to inform transmitting
            GPIO_WritePin(GPIO_BLUE_LED1_BP, 0);
        }

        //
        // red LED informs PA state
        //
        toggle++;

        if (intThermal > 1)
        {
            // If multiple PA thermal events, red LED on
            GPIO_WritePin(GPIO_RED_LED2_BP, 0);
        }
        else if (intCurrent > 1)
        {
            // If multiple PA current events, red LED blink
            GPIO_WritePin(GPIO_RED_LED2_BP, (toggle&1));
        }
        else
        {
            // If no PA thermal or current events, red LED off
            GPIO_WritePin(GPIO_RED_LED2_BP, 1);
        }

        DELAY_US(50000);
    }
}

//
// AFE_InitGpio - Initialize launchpad and booterpack GPIOs
//
void AFE_InitGpio()
{
    // LaunchPad LEDs
    GPIO_SetupPinMux(GPIO_RED_LED_LP, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(GPIO_RED_LED_LP, GPIO_OUTPUT, GPIO_PUSHPULL);

    GPIO_SetupPinMux(GPIO_BLUE_LED_LP, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(GPIO_BLUE_LED_LP, GPIO_OUTPUT, GPIO_PUSHPULL);

    // BoosterPack LEDs
    GPIO_SetupPinMux(GPIO_RED_LED2_BP, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(GPIO_RED_LED2_BP, GPIO_OUTPUT, GPIO_PUSHPULL);

    GPIO_SetupPinMux(GPIO_BLUE_LED1_BP, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(GPIO_BLUE_LED1_BP, GPIO_OUTPUT, GPIO_PUSHPULL);
}

//
// epwm2_isr - EPWM2 ISR
//
#pragma CODE_SECTION(epwm2_isr,".TI.ramfunc");
__interrupt void epwm2_isr(void)
{
    //
    // Enable DMA ISR Nesting
    //
    uint16_t TempPIEIER;
    TempPIEIER = PieCtrlRegs.PIEIER2.all;
    IER |= M_INT7;
    IER &= MINT7;                         // Set "global" priority
    PieCtrlRegs.PIEIER2.all &= MG7_1;     // Set "group" priority
    PieCtrlRegs.PIEACK.all = 0xFFFF;      // Enable PIE interrupts
    asm("       NOP");                    // Wait one cycle
    EINT;                                 // Clear INTM to enable interrupts

    //
    // Check if data transmission enabled
    //
    if(txDataEnable == YES)
    {
        if(txBuf[currentChar] != txChar)
        {
            txChar = txBuf[currentChar];
        }

        //
        // Update transmission data index
        //
        if (++currentChar >= sizeof(txBuf))
        {
            currentChar = 0;
        }
    }

    //
    // Increment cycle count
    //
    cycleCount++;

    //
    // If continuous transmission test mode, cap cycle count
    //
    if (tmCont)
    {
        cycleCount = (cycleCount > 2) ? 2 : cycleCount;
    }
    //
    // Otherwise, update transmission state based on cycle count
    //
    else
    {
        //
        // If cycle count = 209, reset/re-enable Tx Data
        //
        if (cycleCount == 209)
        {
            sinePosition = 0;
            cycleCount = 0;
            txDataEnable = YES;
            GPIO_WritePin(GPIO_BLUE_LED1_BP, 0);
        }
        else
        {
            //
            // If cycle count = 33, disable Tx Data
            //
            if(cycleCount == 33)
            {
                txDataEnable = NO;
            }

            //
            // If cycle count = 34, disable DMA/SPI counter
            //
            if(cycleCount == 34)
            {
                txChar = NaN;
                GPIO_WritePin(GPIO_BLUE_LED1_BP, 1);
            }
        }
    }

    //
    // Clear INT flag for this timer
    //
    EPwm2Regs.ETCLR.bit.INT = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    //
    // Restore registers saved for DMA ISR Nesting
    //
    DINT;
    PieCtrlRegs.PIEIER2.all = TempPIEIER;
}

//
// EPWM1_Init - Initialize EPWM1 configuration
//
void EPWM1_Init()
{
    //
    // Setup TBCLK
    //
    EPwm1Regs.TBPRD = EPWM1_TIMER_TBPRD;       // Set timer period 50 TBCLKs
    EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;                  // Clear counter

    //
    // Setup counter mode
    // NOTE: Counter enabled in main loop
    //
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_FREEZE;        // Freeze counter initially
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;         // Disable phase loading
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.FREE_SOFT = 11;
    
    //
    // Setup shadowing
    //
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // Load on Zero
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    //
    // SOC event config
    //
    EPwm1Regs.ETSEL.bit.SOCAEN  = 0;    // Disable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL = 4;    // Select SOC on up-count
    EPwm1Regs.ETPS.bit.SOCAPRD  = 1;    // Generate pulse on 1st event
}

//
// EPWM2_Init - Initialize EPWM2 configuration
//
void EPWM2_Init()
{
    //
    // Setup TBCLK
    //
    EPwm2Regs.TBPRD = EPWM2_TIMER_TBPRD;        // Set timer period 16000 TBCLKs
    EPwm2Regs.TBPHS.bit.TBPHS = 0x0000;         // Phase is 0
    EPwm2Regs.TBCTR = 0x0000;                   // Clear counter

    //
    // Setup counter mode
    // NOTE: Counter enabled in main loop
    //
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_FREEZE;    // Freeze counter initially
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;     // Disable phase loading
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;    // Clock ratio to SYSCLKOUT/4/4
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
    EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;    // Select INT on Zero event
    EPwm2Regs.ETSEL.bit.INTEN = 1;               // Enable INT
    EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;          // Generate INT on every event
}

//
// pwm_enable - Enable/disable PWM counters
//
void pwm_enable(Uint16 enable)
{
    if (enable)
    {
        EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
        EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    }
    else
    {
        EPwm1Regs.TBCTL.bit.CTRMODE = TB_FREEZE;
        EPwm2Regs.TBCTL.bit.CTRMODE = TB_FREEZE;
        // IMPORTANT: Delay to complete current SPI transaction
        DELAY_US(1000);
    }
}

//
// dma_init - DMA setup for both TX and RX channels.
//
void dma_init()
{
    //
    // Initialize DMA
    //
    DMAInitialize();

    //
    // configure DMACH5 for TX
    //
    DMACH1AddrConfig(&SpiaRegs.SPITXBUF,pingBuf);
    DMACH1BurstConfig(BURST,1,0);         // Burst size, src step, dest step
    DMACH1TransferConfig(TRANSFER,0,0);   // transfer size, src step, dest step
    DMACH1ModeConfig(DMA_EPWM1A,PERINT_ENABLE,ONESHOT_DISABLE,CONT_ENABLE,
                     SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,
                     CHINT_END,CHINT_ENABLE);
}

//
// dma_start - Start the DMA process
//
void dma_start(void)
{
    EALLOW;
    DmaRegs.CH1.CONTROL.bit.RUN = 1;
    EDIS;
}

//
// dma_isr - ISR DMA Channel 1
//
#pragma CODE_SECTION(dma_isr,".TI.ramfunc");
__interrupt void dma_isr(void)
{
    if(pingpongBufSel)
    {
        DMACH1AddrConfig(&SpiaRegs.SPITXBUF,(volatile Uint16 *)pongBuf);
        fill_SineTable(&pingBuf[0],sizeof(pingBuf));
        pingpongBufSel = 0;
    }
    else
    {
        DMACH1AddrConfig(&SpiaRegs.SPITXBUF,(volatile Uint16 *)pingBuf);
        fill_SineTable(&pongBuf[0],sizeof(pongBuf));
        pingpongBufSel = 1;
    }

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // ACK to receive more interrupts
                                            // from this PIE group
}

//
// fill_SineTable - Populate SINE Table
//
#pragma CODE_SECTION(fill_SineTable,".TI.ramfunc");
void fill_SineTable(Uint16 *buf, Uint16 bufSize)
{
    //
    // Initialize synthetic firmware attenuation factor and sine step.
    //
    Uint32 dacGain;
    switch (txChar)
    {
        case SPACEFREQ:
            dacGain = GAIN_SPACE_x1024;
            sineStep = spaceSineStep;
            break;
        case MARKFREQ:
            dacGain = GAIN_MARK_x1024;
            sineStep = markSineStep;
            break;
        default:
            dacGain = 0;
            sineStep = 0;
            break;
    }

    //
    // Transmit next data points in sine wave
    //
    Uint16 x, v;
    for(x=0;x<bufSize;x++)
    {
        //
        // NOTE: shift left 6 + shift right 10 (x1024 gain factor)
        // yields net shift right 4.
        //
        v = ((dacGain * sineTable[(Uint16)sinePosition]) >> 4) & 0xffc0;

        // Offset to ensure linear region (0.1V < DAC_OUT < 3.2V)
        buf[x] = v + (DAC_CODE_OFFSET << 6);

        // Calculate next step
        sinePosition += sineStep;

        // Check for overflow
        if(sinePosition > (N_POINT-1))
        {
            sinePosition -= (N_POINT-1);
        }
    }
}

//
// reset_DMASineTables - Reset DMA SINE Tables
//
void reset_DMASineTables(void)
{
    EALLOW;
    DmaRegs.CH1.TRANSFER_COUNT = TRANSFER;
    EDIS;
    DMACH1AddrConfig(&SpiaRegs.SPITXBUF,(volatile Uint16 *)pingBuf);
    fill_SineTable(&pingBuf[0],sizeof(pingBuf));
    fill_SineTable(&pongBuf[0],sizeof(pongBuf));
    pingpongBufSel = 1;
}

//
// End of file
//
