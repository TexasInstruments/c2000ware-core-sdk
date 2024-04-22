//###########################################################################
//
// FILE:   sdfm_filters_sync_dma_cpu01.c
//
// TITLE:  SDFM Filter sync SDM Example for F2837xD.
//
//! \addtogroup cpu01_example_list
//! <h1> SDFM Filter Sync DMA </h1>
//!
//! In this example, SDFM filter data is read by DMA. The
//! SDFM configuration is shown below:
//!  - SDFM1 used in this example
//!  - MODE0 Input control mode selected
//!  - Comparator settings
//!      - Sinc3 filter selected
//!      - OSR = 32
//!      - HLT = 0x7FFF (Higher threshold setting)
//!      - LLT  = 0x0000(Lower threshold setting)
//!  - Data filter settings
//!      - All the 4 filter modules enabled
//!      - Sinc3 filter selected
//!      - OSR = 256
//!      - All the 4 filters are synchronized by using MFE
//!       (Master Filter enable bit)
//!      - Filter output represented in 16 bit format
//!      - In order to convert 25 bit Data filter
//!        into 16 bit format user needs to right shift by 9 bits for
//!        Sinc3 filter with OSR = 256
//!  - Interrupt module settings for SDFM filter
//!      - All the 4 higher threshold comparator interrupts disabled
//!      - All the 4 lower threshold comparator interrupts disabled
//!      - All the 4 modulator failure interrupts disabled
//!      - All the 4 filter will generate interrupt when a new filter
//!        data is available
//!
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
#define MAX_SAMPLES                               1024
#define SDFM_PIN_MUX_OPTION1                      1
#define SDFM_PIN_MUX_OPTION2                      2
#define SDFM_PIN_MUX_OPTION3                      3
#define ONE_WORD_BURST                            0
#define SOURCE_NO_ADDRESS_CHANGE                  0
#define DESTINATION_INCREMENT_ONE_ADDRESS         1
#define TRANSFER_SIZE_0x800                       0x07FF
#define TRANSFER_SIZE_0x400                       0x03FF
#define TRANSFER_STEP_SOURCE_NO_CHANGE            0
#define TRANSFER_STEP_DEST_INCREMENT_ONE_ADDRESS  1

//
// Globals
//
uint16_t gPeripheralNumber;
int16  Filter1_Result[MAX_SAMPLES];
int16  Filter3_Result[MAX_SAMPLES];
int16  Filter2_Result[MAX_SAMPLES];
int16  Filter4_Result[MAX_SAMPLES];
#pragma DATA_SECTION(Filter1_Result,"Filter1_RegsFile");
#pragma DATA_SECTION(Filter2_Result,"Filter2_RegsFile");
#pragma DATA_SECTION(Filter3_Result,"Filter3_RegsFile");
#pragma DATA_SECTION(Filter4_Result,"Filter4_RegsFile");

//
// Pointers for DMA source & dest addresses
//
volatile int16 *DMA1Source, *DMA1Dest;
volatile int16 *DMA2Source, *DMA2Dest;
volatile int16 *DMA3Source, *DMA3Dest;
volatile int16 *DMA4Source, *DMA4Dest;

volatile uint16_t DMA_Done = 0;

//
// Function Prototypes
//
void Sdfm_configurePins(uint16_t);
__interrupt void SDFM1_ISR(void);
__interrupt void SDFM2_ISR(void);
__interrupt void local_DMACH1_ISR(void);
__interrupt void local_DMACH2_ISR(void);
__interrupt void local_DMACH3_ISR(void);
__interrupt void local_DMACH4_ISR(void);
void DMA_setup(void);
void DMA_configure(void);
__interrupt void SDFM1_ISR(void);
__interrupt void SDFM2_ISR(void);

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
    PieVectTable.DMA_CH1_INT = &local_DMACH1_ISR;
    PieVectTable.DMA_CH2_INT = &local_DMACH2_ISR;
    PieVectTable.DMA_CH3_INT = &local_DMACH3_ISR;
    PieVectTable.DMA_CH4_INT = &local_DMACH4_ISR;

//
// Enable DMA INTn in the PIE: Group 7 __interrupt 1-6
//
    PieCtrlRegs.PIEIER7.bit.INTx1 = 1;  //DMACH1 interrupt
    PieCtrlRegs.PIEIER7.bit.INTx2 = 1;  //DMACH2 interrupt
    PieCtrlRegs.PIEIER7.bit.INTx3 = 1;  //DMACH3 interrupt
    PieCtrlRegs.PIEIER7.bit.INTx4 = 1;  //DMACH4 interrupt

//
// Enable CPU INT7 interrupts are enabled
//
    IER |= M_INT7;
    EINT;

    DMA_configure();

#ifdef CPU1
    pinMuxoption = SDFM_PIN_MUX_OPTION1;

    //
    // Configure GPIO pins as SDFM pins
    //
    Sdfm_configurePins(pinMuxoption);
#endif

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
    HLT = 0x7FFF;  // Over value threshold settings
    LLT = 0x0000;  // Under value threshold settings

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
// Enable Master filter bit: Unless this bit is set none of the filter modules
// can be enabled. All the filter modules are synchronized when master filter
// bit is enabled after individual filter modules are enabled.
//
    Sdfm_enableMFE(gPeripheralNumber);

//
// PWM11.CMPC, PWM11.CMPD, PWM12.CMPC and PWM12.CMPD signals cannot synchronize
// the filters. This option is not being used in this example.
//
    Sdfm_configureExternalreset(gPeripheralNumber,FILTER_1_EXT_RESET_DISABLE,
                                FILTER_2_EXT_RESET_DISABLE,
                                FILTER_3_EXT_RESET_DISABLE,
                                FILTER_4_EXT_RESET_DISABLE);

//
// Enable interrupts
//
// Following SDFM interrupts can be enabled / disabled using this function.
//    Enable / disable comparator high threshold
//    Enable / disable comparator low threshold
//    Enable / disable modulator clock failure
//    Enable / disable filter acknowledge
//
    Sdfm_configureInterrupt(gPeripheralNumber, FILTER1, IEH_DISABLE,
                            IEL_DISABLE, MFIE_ENABLE, AE_ENABLE);
    Sdfm_configureInterrupt(gPeripheralNumber, FILTER2, IEH_DISABLE,
                            IEL_DISABLE, MFIE_ENABLE, AE_ENABLE);
    Sdfm_configureInterrupt(gPeripheralNumber, FILTER3, IEH_DISABLE,
                            IEL_DISABLE, MFIE_ENABLE, AE_ENABLE);
    Sdfm_configureInterrupt(gPeripheralNumber, FILTER4, IEH_DISABLE,
                            IEL_DISABLE, MFIE_ENABLE, AE_ENABLE);

//
// Enable master interrupt so that any of the filter interrupts can trigger
// by SDFM interrupt to CPU
//
    //SDFM_MASTER_INTERRUPT_ENABLE(gPeripheralNumber);
    Sdfm_enableMIE(gPeripheralNumber);

    while(1);
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
                //
                // Configure GPIOs as asynchronous input
                //
                GPIO_SetupPinOptions(pin, GPIO_INPUT, GPIO_ASYNC);

                //
                // Configure this pin to be owned by CPU1 and configure this
                // pin as SDFM pin
                //
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
// local_DMACH1_ISR - DMA Channel 1 ISR
//
__interrupt void local_DMACH1_ISR(void)
{
    DMA_Done |= 0x0001;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    ESTOP0;
}

//
// local_DMACH2_ISR - DMA Channel 2 ISR
//
__interrupt void local_DMACH2_ISR(void)
{
    DMA_Done |= 0x0002;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    ESTOP0;
}

//
// local_DMACH3_ISR - DMA Channel 3 ISR
//
__interrupt void local_DMACH3_ISR(void)
{
    DMA_Done |= 0x0004;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    ESTOP0;
}

//
// local_DMACH4_ISR - DMA Channel 4 ISR
//
__interrupt void local_DMACH4_ISR(void)
{
    DMA_Done |= 0x0008;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    ESTOP0;
}

//
// DMA_setup - Initialize DMA burst, transfer, and wrap configurations
//
void DMA_setup()
{
    //
    // Initialize the DMA
    // DMA Source is buffer 2, destination is buffer 1
    //
    DMA1Source = (int16 *)(0x5E17);
    DMA1Dest = &Filter1_Result[0];
    DMA2Source = (int16 *)(0x5E27);
    DMA2Dest = &Filter2_Result[0];
    DMA3Source = (int16 *)(0x5E37);
    DMA3Dest = &Filter3_Result[0];
    DMA4Source = (int16 *)(0x5E47);
    DMA4Dest = &Filter4_Result[0];

    DMACH1AddrConfig((Uint16 *)DMA1Dest, (Uint16 *)DMA1Source);
    DMACH2AddrConfig((Uint16 *)DMA2Dest, (Uint16 *)DMA2Source);
    DMACH3AddrConfig((Uint16 *)DMA3Dest, (Uint16 *)DMA3Source);
    DMACH4AddrConfig((Uint16 *)DMA4Dest, (Uint16 *)DMA4Source);

    //
    // Set up to use 16-bit data size
    // Pointers are based on 16-bit words
    // Increment by 1 (16 16-bit words)
    //

    //
    // BURST size = 1 | Source step size = 0 | Dest step size += 1
    //
    DMACH1BurstConfig(ONE_WORD_BURST,SOURCE_NO_ADDRESS_CHANGE,
                      DESTINATION_INCREMENT_ONE_ADDRESS);

    //
    // BURST size = 1 | Source step size = 0 | Dest step size += 1
    //
    DMACH2BurstConfig(ONE_WORD_BURST,SOURCE_NO_ADDRESS_CHANGE,
                      DESTINATION_INCREMENT_ONE_ADDRESS);

    //
    // BURST size = 1 | Source step size = 0 | Dest step size += 1
    //
    DMACH3BurstConfig(ONE_WORD_BURST,SOURCE_NO_ADDRESS_CHANGE,
                      DESTINATION_INCREMENT_ONE_ADDRESS);

    //
    // BURST size = 1 | Source step size = 0 | Dest step size += 1
    //
    DMACH4BurstConfig(ONE_WORD_BURST,SOURCE_NO_ADDRESS_CHANGE,
                      DESTINATION_INCREMENT_ONE_ADDRESS);

    //
    // Transfer size = 0x400 | Source step size = 0 | Dest step size += 1
    //
    DMACH1TransferConfig(TRANSFER_SIZE_0x400,TRANSFER_STEP_SOURCE_NO_CHANGE,
                         TRANSFER_STEP_DEST_INCREMENT_ONE_ADDRESS);

    //
    // Transfer size = 0x400 | Source step size = 0 | Dest step size += 1
    //
    DMACH2TransferConfig(TRANSFER_SIZE_0x400,TRANSFER_STEP_SOURCE_NO_CHANGE,
                         TRANSFER_STEP_DEST_INCREMENT_ONE_ADDRESS);

    //
    // Transfer size = 0x400 | Source step size = 0 | Dest step size += 1
    //
    DMACH3TransferConfig(TRANSFER_SIZE_0x400,TRANSFER_STEP_SOURCE_NO_CHANGE,
                         TRANSFER_STEP_DEST_INCREMENT_ONE_ADDRESS);

    //
    // Transfer size = 0x400 | Source step size = 0 | Dest step size += 1
    //
    DMACH4TransferConfig(TRANSFER_SIZE_0x400,TRANSFER_STEP_SOURCE_NO_CHANGE,
                         TRANSFER_STEP_DEST_INCREMENT_ONE_ADDRESS);

    DMACH1WrapConfig(0xFFFF,0,0xFFFF,0);
    DMACH2WrapConfig(0xFFFF,0,0xFFFF,0);
    DMACH3WrapConfig(0xFFFF,0,0xFFFF,0);
    DMACH4WrapConfig(0xFFFF,0,0xFFFF,0);
}

//
// DMA_configure - Configure DMA channels 1,2,3, and 4
//
void DMA_configure(void)
{
    EALLOW;
    CpuSysRegs.SECMSEL.bit.PF1SEL = 1;
    EDIS;

    DMAInitialize();
    DMA_setup();

    DMACH1ModeConfig(DMA_SD1FLT1,PERINT_ENABLE,ONESHOT_DISABLE,CONT_DISABLE,
                     SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,
                     CHINT_END,CHINT_ENABLE);
    DMACH2ModeConfig(DMA_SD1FLT2,PERINT_ENABLE,ONESHOT_DISABLE,CONT_DISABLE,
                     SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,
                     CHINT_END,CHINT_ENABLE);
    DMACH3ModeConfig(DMA_SD1FLT3,PERINT_ENABLE,ONESHOT_DISABLE,CONT_DISABLE,
                     SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,
                     CHINT_END,CHINT_ENABLE);
    DMACH4ModeConfig(DMA_SD1FLT4,PERINT_ENABLE,ONESHOT_DISABLE,CONT_DISABLE,
                     SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,
                     CHINT_END,CHINT_ENABLE);

    StartDMACH1();
    StartDMACH2();
    StartDMACH3();
    StartDMACH4();
}

//
// End of file
//
