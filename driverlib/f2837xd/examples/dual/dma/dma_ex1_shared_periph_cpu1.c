//#############################################################################
//
// FILE:   dma_ex1_shared_periph_cpu1.c
//
// TITLE:  DMA Transfer for Shared Peripheral Example
//
//! \addtogroup driver_dual_example_list
//! <h1> DMA Transfer Shared Peripheral </h1>
//!
//! This example shows how to initiate a DMA transfer on CPU1 from a shared
//! peripheral which is owned by CPU2.  In this specific example, a timer ISR
//! is used on CPU2 to initiate a SPI transfer which will trigger the CPU1 DMA.
//! CPU1's DMA will then in turn update the ePWM1 CMPA value for the PWM which
//! it owns.  The PWM output can be observed on the GPIO pins.
//!
//! \b Watch \b Pins
//!   - GPIO0 and GPIO1 - ePWM output can be viewed with oscilloscope
//!
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
#include "driverlib.h"
#include "device.h"
#include "inc/hw_ipc.h"

//
// Defines
//
//#define USE_DMA_INTERRUPT

//
// Globals
//
uint16_t newCMPValue;
#pragma DATA_SECTION(newCMPValue, "SHARERAMGS2");

//
// Function Prototypes
//
void Example_deviceInit(void);
void initEPWM1(void);
void setupDMA(void);

#ifdef USE_DMA_INTERRUPT
__interrupt void dmaISR(void);
#endif

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Example_deviceInit();

    //
    // Initialize GPIO and configure the GPIOs 0 and 1 as ePWM outputs
    //
    Device_initGPIO();

    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_0_EPWM1A);
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_1_EPWM1B);

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Configure ePWM1 and the DMA
    //
    initEPWM1();
    setupDMA();

    //
    // Send IPC to CPU2 telling it to proceed with configuring the SPI
    //
    HWREG(IPC_BASE + IPC_O_SET) = IPC_SET_IPC1;

    //
    // Enable DMA interrupt
    //
#ifdef USE_DMA_INTERRUPT
    Interrupt_enable(INT_DMA_CH5);
    Interrupt_register(INT_DMA_CH5, &dmaISR);
#endif

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop indefinitely
    //
    for(;;)
    {
        NOP;
    }
}

//
// Example_deviceInit function
// This example uses custom Device_init function since CPU2 owns some of the
// peripherals
//
void Example_deviceInit(void)
{
    //
    // Disable the watchdog
    //
    SysCtl_disableWatchdog();

#ifdef _FLASH
    //
    // Copy time critical code and flash setup code to RAM. This includes the
    // following functions: InitFlash();
    //
    // The RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart symbols
    // are created by the linker. Refer to the device .cmd file.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //
    Flash_initModule(FLASH0CTRL_BASE, FLASH0ECC_BASE, DEVICE_FLASH_WAITSTATES);
#endif

    //
    // Set up PLL control and clock dividers
    //
    SysCtl_setClock(DEVICE_SETCLOCK_CFG);

    //
    // Make sure the LSPCLK divider is set to the default (divide by 4)
    //
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_4);

    //
    // These asserts will check that the #defines for the clock rates in
    // device.h match the actual rates that have been configured. If they do
    // not match, check that the calculations of DEVICE_SYSCLK_FREQ and
    // DEVICE_LSPCLK_FREQ are accurate. Some examples will not perform as
    // expected if these are not correct.
    //
    ASSERT(SysCtl_getClock(DEVICE_OSCSRC_FREQ) == DEVICE_SYSCLK_FREQ);
    ASSERT(SysCtl_getLowSpeedClock(DEVICE_OSCSRC_FREQ) == DEVICE_LSPCLK_FREQ);

    //
    // Give control of SPIA and GS2 to CPU2, and ePWM a secondary master to DMA
    //
    SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL6_SPI, 1, SYSCTL_CPUSEL_CPU2);
    SysCtl_selectSecMaster(SYSCTL_SEC_MASTER_DMA, SYSCTL_SEC_MASTER_DMA);
    MemCfg_setGSRAMMasterSel(MEMCFG_SECT_GS2, MEMCFG_GSRAMMASTER_CPU2);

    //
    // Send IPC flag to CPU2 signaling the completion of system initialization
    //
    HWREG(IPC_BASE + IPC_O_SET) = IPC_SET_IPC0;

    //
    // Turn on the required peripherals
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

//
// initEPWM1 - Function to Initialize ePWM1
//
void initEPWM1(void)
{
    //
    // Disable sync (freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Set-up TBCLK
    //
    EPWM_setTimeBasePeriod(EPWM1_BASE, 6000);
    EPWM_setPhaseShift(EPWM1_BASE, 0U);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0U);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_disablePhaseShiftLoad(EPWM1_BASE);

    //
    // Set ePWM clock pre-scaler
    //
    EPWM_setClockPrescaler(EPWM1_BASE,
                           EPWM_CLOCK_DIVIDER_4,
                           EPWM_HSCLOCK_DIVIDER_4);

    //
    // Set up shadowing
    //
    EPWM_setCounterCompareShadowLoadMode(EPWM1_BASE,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(EPWM1_BASE,
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    //
    // Setup compare
    //
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 3000U);

    //
    // Set actions
    //
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

//
// setupDMA - Function to Setup DMA
//
void setupDMA(void)
{
    const void *destAddr, *srcAddr;

    //
    // Initialize DMA
    //
    DMA_initController();

    destAddr = (const void *)(EPWM1_BASE + EPWM_O_CMPA + 1);
    srcAddr = (const void *)&newCMPValue;

    //
    // Setup DMA to transfer a single 16-bit word. The DMA is setup to run
    // continuously so that an interrupt is not required to restart the RUN
    // bit. The DMA trigger is SPIA-FFTX.
    //
    DMA_configAddresses(DMA_CH5_BASE, destAddr, srcAddr);
    DMA_configBurst(DMA_CH5_BASE, 1, 1, 1);
    DMA_configTransfer(DMA_CH5_BASE, 1, 1, 1);
    DMA_configWrap(DMA_CH5_BASE, 0xFFFF, 0, 0xFFFF, 0);
    DMA_configMode(DMA_CH5_BASE, DMA_TRIGGER_SPIATX, DMA_CFG_ONESHOT_ENABLE |
                                                     DMA_CFG_CONTINUOUS_ENABLE |
                                                     DMA_CFG_SIZE_16BIT);
    DMA_setInterruptMode(DMA_CH5_BASE, DMA_INT_AT_END);
    DMA_enableTrigger(DMA_CH5_BASE);
    DMA_enableInterrupt(DMA_CH5_BASE);

    DMA_startChannel(DMA_CH5_BASE);
}

//
// dmaISR - DMA Interrupt Service Routine (uncomment to enable DMA ISR)
//
#ifdef USE_DMA_INTERRUPT
__interrupt void dmaISR(void)
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}
#endif

//
// End of File
//
