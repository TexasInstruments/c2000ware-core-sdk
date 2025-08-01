//#############################################################################
//
// FILE:   device.c
//
// TITLE:  Device setup for examples.
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "device.h"
#include "driverlib.h"
#ifdef __cplusplus
using std::memcpy;
#endif
#ifdef CMDTOOL
#include "device_cmd.h"
#endif

//*****************************************************************************
//
// Function to initialize the device. Primarily initializes system control to a
// known state by disabling the watchdog, setting up the SYSCLKOUT frequency,
// and enabling the clocks to the peripherals.
// To configure the pins as analog pins, use the function GPIO_setAnalogMode
//
// Note : In case XTAL is used as the PLL source, it is recommended to invoke
// the Device_verifyXTAL() before configuring PLL
//
//*****************************************************************************
void Device_init(void)
{
    //
    // Unbonded GPIO pull ups and PERCNF reg update based on package type
    //
    Device_enableUnbondedGPIOPullups(DEV_PKG_TYPE);
    Device_updatePeripheralConfig(DEV_PKG_TYPE);

    //
    // Disable the watchdog
    //
    SysCtl_disableWatchdog();
#ifdef CMDTOOL
    CMD_init();
#endif

#ifdef _FLASH
#ifndef CMDTOOL
    //
    // Copy time critical code and flash setup code to RAM. This includes the
    // following functions: InitFlash();
    //
    // The RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart symbols
    // are created by the linker. Refer to the device .cmd file.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif
    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //

    Flash_initModule(FLASH0CTRL_BASE, FLASH0ECC_BASE, DEVICE_FLASH_WAITSTATES);
#endif

    //
    // Set up PLL control and clock dividers
    //

#if defined(USE_PLL_SRC_XTAL)

    SysCtl_setClock(SYSCTL_OSCSRC_XTAL, SYSCTL_PLL_ENABLE, SYSCTL_PDIV_2,
                    SYSCTL_PLLMULT_32, SYSCTL_RDIVCLK0_2, SYSCTL_SYSDIV_1,
                    SYSCTL_DCC_BASE_0);

#elif defined(USE_PLL_SRC_SYSOSCDIV4)

    SysCtl_setClock(SYSCTL_OSCSRC_SYSOSCDIV4, SYSCTL_PLL_ENABLE, SYSCTL_PDIV_1,
                    SYSCTL_PLLMULT_40, SYSCTL_RDIVCLK0_2, SYSCTL_SYSDIV_1,
                    SYSCTL_DCC_BASE_0);

#endif

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

#ifndef _FLASH
    //
    // Call Device_cal function when run using debugger
    // This function is called as part of the Boot code. The function is called
    // in the Device_init function since during debug time resets, the boot code
    // will not be executed and the gel script will reinitialize all the
    // registers and the calibrated values will be lost.
	// Sysctl_deviceCal is a wrapper function for Device_Cal
    //
    SysCtl_deviceCal();
#endif

    //
    // Turn on PWM Time Base Clock sync
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Lock VREGCTL Register
    // The register VREGCTL is not supported in this device. It is locked to
    // prevent any writes to this register
    //
    ASysCtl_lockVREG();

    //
    // Configure GPIO 12, 13 and 28 as digital pins
    //
    GPIO_setAnalogMode(12U, GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(13U, GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(28U, GPIO_ANALOG_DISABLED);

}

//*****************************************************************************
//
// Function to enable pullups for the unbonded GPIOs
//
//*****************************************************************************
void Device_enableUnbondedGPIOPullups(uint16_t packageType)
{
    EALLOW;
    #if (packageType == DEV_PKG_32RHB)
    {
        *(unsigned long *)(GPIOCTRL_BASE + GPIO_O_GPAPUD) &= 0xBF7EC9BBUL;
        *(unsigned long *)(GPIOCTRL_BASE + GPIO_O_GPBPUD) &= 0xFFFFDC7DUL;
        *(unsigned long *)(GPIOCTRL_BASE + GPIO_O_GPHPUD) &= 0xFFF7FFFFUL;
    }
    #elif (packageType == DEV_PKG_32VFC)
    {
        *(unsigned long *)(GPIOCTRL_BASE + GPIO_O_GPAPUD) &= 0xBF7EC93BUL;
        *(unsigned long *)(GPIOCTRL_BASE + GPIO_O_GPBPUD) &= 0xFFFFD47DUL;
        *(unsigned long *)(GPIOCTRL_BASE + GPIO_O_GPHPUD) &= 0xFFF7FFFFUL;
    }
    #else
    {
        //
        // Package type is 48PT
        //
        *(unsigned long *)(GPIOCTRL_BASE + GPIO_O_GPAPUD) &= 0xBF7FF1FFUL;
        *(unsigned long *)(GPIOCTRL_BASE + GPIO_O_GPBPUD) &= 0xFFFFFC7FUL;
        *(unsigned long *)(GPIOCTRL_BASE + GPIO_O_GPHPUD) &= 0xFFF7FFFFUL;
    }
    #endif
    EDIS;

}

//*****************************************************************************
//
// Function to update peripheral configuraiton register. These bits are used to 
// provide the protection for the package when the GPIOs are double boned
//
//*****************************************************************************
void Device_updatePeripheralConfig(uint16_t packageType)
{

    #if ((packageType == DEV_PKG_32RHB) || (packageType == DEV_PKG_32VFC))
    {
        
        *(unsigned long *)(DEVCFG_BASE + SYSCTL_O_PERCNF) |= 0x00000003UL;
    }
    #else
    {

        *(unsigned long *)(DEVCFG_BASE + SYSCTL_O_PERCNF) |= 0x00000001UL;
    }
    #endif

}

//*****************************************************************************
//
// Function to disable pin locks and enable pullups on GPIOs.
//
//*****************************************************************************
void Device_initGPIO(void)
{
    //
    // Disable pin locks.
    //
    GPIO_unlockPortConfig(GPIO_PORT_A, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_B, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_H, 0xFFFFFFFF);
}

//*****************************************************************************
//
// Function to verify the XTAL frequency
// freq is the XTAL frequency in MHz
// The function return true if the the actual XTAL frequency matches with the
// input value
//
// Note that this function assumes that the PLL is not already configured and
// hence uses SysClk freq = 10MHz for DCC calculation
//
//*****************************************************************************
bool Device_verifyXTAL(float freq)
{
    //
    // Use DCC to verify the XTAL frequency using SYSOSCDIV4 as reference clock
    //

    //
    // Turn on XTAL and wait for it to power up using X1CNT
    //
    SysCtl_turnOnOsc(SYSCTL_OSCSRC_XTAL);
    SysCtl_clearExternalOscCounterValue();
    while(SysCtl_getExternalOscCounterValue() != SYSCTL_X1CNT_X1CNT_M);

    //
    // Configures XTAL as CLKSRC0 and SYSOSCDIV4 as CLKSRC1
    // Fclk0 = XTAL frequency (input parameter)
    // Fclk1 = SYSOSCDIV4 frequency = 8MHz
    //
    // Configuring DCC error tolerance of +/-1%
    // SYSOSCDIV4 can have a variance in frequency of +/-10%
    //
    // Assuming PLL is not already configured, SysClk freq = 8MHz
    //
    // Note : Update the tolerance and SYSOSCDIV4 frequency variance as necessary.
    //
    return (DCC_verifyClockFrequency(DCC0_BASE,
                                     DCC_COUNT1SRC_SYSOSCDIV4, 8.0F,
                                     DCC_COUNT0SRC_XTAL, freq,
                                     1.0F, 10.0F, 8.0F));

}

//*****************************************************************************
//
// Error handling function to be called when an ASSERT is violated
//
//*****************************************************************************
void __error__(const char *filename, uint32_t line)
{
    //
    // An ASSERT condition was evaluated as false. You can use the filename and
    // line parameters to determine what went wrong.
    //
    ESTOP0;
}
