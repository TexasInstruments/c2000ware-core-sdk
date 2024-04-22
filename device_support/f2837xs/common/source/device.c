//#############################################################################
//
// FILE:   device.c
//
// TITLE:  Device setup for examples.
//
//#############################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2014-2024 Texas Instruments Incorporated - http://www.ti.com/
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

#define PASS 0
#define FAIL 1

uint32_t Example_Result = FAIL;
uint32_t Example_PassCount = 0;
uint32_t Example_Fail = 0;

//*****************************************************************************
//
// Function to initialize the device. Primarily initializes system control to a
// known state by disabling the watchdog, setting up the SYSCLKOUT frequency,
// and enabling the clocks to the peripherals.
//
//*****************************************************************************
void Device_init(void)
{
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
#ifdef CPU1

    //
    // Configure Analog Trim in case of untrimmed or TMX sample
    //
    if((SysCtl_getDeviceParametric(SYSCTL_DEVICE_QUAL) == 0x0U)       &&
       (HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFTRIMA) == 0x0U))
    {
        Device_configureTMXAnalogTrim();
    }

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

#endif
    //
    // Turn on all peripherals
    //
    Device_enableAllPeripherals();

    //
    // Initialize result parameter as FAIL
    //
    Example_Result = FAIL;
}

//*****************************************************************************
//
// Function to turn on all peripherals, enabling reads and writes to the
// peripherals' registers.
//
// Note that to reduce power, unused peripherals should be disabled.
//
//*****************************************************************************
void Device_enableAllPeripherals(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLA1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRPWM);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EMIF1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EMIF2);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM8);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM9);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM10);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM11);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM12);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP6);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP3);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SD1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SD2);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCID);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIC);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CB);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANB);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_MCBSPA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_MCBSPB);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_USBA);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UPPA);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCD);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS8);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACC);
}

//*****************************************************************************
//
// Function to disable pin locks on GPIOs.
//
//*****************************************************************************
void Device_initGPIO(void)
{
    //
    // Disable pin locks.
    //
    GPIO_unlockPortConfig(GPIO_PORT_A, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_B, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_C, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_D, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_E, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_F, 0xFFFFFFFF);

    //
    // Enable GPIO Pullups
    //
    Device_enableUnbondedGPIOPullups();
}

//*****************************************************************************
//
// Function to enable pullups for the unbonded GPIOs on the 176PTP package:
// GPIOs     Grp Bits
// 95-132    C   31
//           D   31:0
//           E   4:0
// 134-168   E   31:6
//           F   8:0
//
//*****************************************************************************

void Device_enableUnbondedGPIOPullupsFor176Pin(void)
{
    EALLOW;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPCPUD) = ~0x80000000U;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPDPUD) = ~0xFFFFFFF7U;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPEPUD) = ~0xFFFFFFDFU;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPFPUD) = ~0x000001FFU;
    EDIS;
}

//*****************************************************************************
//
// Function to enable pullups for the unbonded GPIOs on the 100PZ package:
// GPIOs     Grp Bits
// 0-1       A   1:0
// 5-9       A   9:5
// 22-40     A   31:22
//           B   8:0
// 44-57     B   25:12
// 67-68     C   4:3
// 74-77     C   13:10
// 79-83     C   19:15
// 93-168    C   31:29
//           D   31:0
//           E   31:0
//           F   8:0
//
//*****************************************************************************
void Device_enableUnbondedGPIOPullupsFor100Pin(void)
{
    EALLOW;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPAPUD) = ~0xFFC003E3U;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPBPUD) = ~0x03FFF1FFU;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPCPUD) = ~0xE10FBC18U;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPDPUD) = ~0xFFFFFFF7U;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPEPUD) = ~0xFFFFFFFFU;
    HWREG(GPIOCTRL_BASE + GPIO_O_GPFPUD) = ~0x000001FFU;
    EDIS;
}

//*****************************************************************************
//
// Function to enable pullups for the unbonded GPIOs on the 100PZ or
// 176PTP package.
//
//*****************************************************************************
void Device_enableUnbondedGPIOPullups(void)
{
    //
    // bits 8-10 have pin count
    //
    uint16_t pinCount = ((HWREG(DEVCFG_BASE + SYSCTL_O_PARTIDL) &
                          (uint32_t)SYSCTL_PARTIDL_PIN_COUNT_M) >>
                         SYSCTL_PARTIDL_PIN_COUNT_S);

    /*
     * 5 = 100 pin
     * 6 = 176 pin
     * 7 = 337 pin
     */
    if(pinCount == 5)
    {
        Device_enableUnbondedGPIOPullupsFor100Pin();
    }
    else if(pinCount == 6)
    {
        Device_enableUnbondedGPIOPullupsFor176Pin();
    }
    else
    {
        //
        // Do nothing - this is 337 pin package
        //
    }
}

//*****************************************************************************
//
// Function to implement Analog trim of TMX devices
//
//*****************************************************************************
void Device_configureTMXAnalogTrim(void)
{
    //
    // Enable ADC clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCD);

    //
    // Configure ADC reference trim for TMX devices
    //
    EALLOW;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFTRIMA) = 0x7BDDU;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFTRIMB) = 0x7BDDU;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFTRIMC) = 0x7BDDU;
    HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFTRIMD) = 0x7BDDU;

    //
    // Configure ADC offset trim. The user should generate the trim values
    // by following the instructions in the "ADC Zero Offset Calibration"
    // section in device TRM. The below lines needs to be uncommented and
    // updated with the correct trim values.
    //
//    HWREGH(ADCA_BASE + ADC_O_OFFTRIM) = 0x0U;
//    HWREGH(ADCB_BASE + ADC_O_OFFTRIM) = 0x0U;
//    HWREGH(ADCC_BASE + ADC_O_OFFTRIM) = 0x0U;
//    HWREGH(ADCD_BASE + ADC_O_OFFTRIM) = 0x0U;

    //
    // Configure internal oscillator trim. If the internal oscillator trim
    // contains all zeros, the user can adjust the lowest 10 bits of the
    // oscillator trim register between 1 (minimum) and 1023 (maximum)
    // while observing the system clock on the XCLOCKOUT pin. The below
    // lines needs to be uncommented and updated with the correct trim values.
    //
//    if(HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_INTOSC1TRIM) == 0x0U)
//    {
//        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_INTOSC1TRIM) = 0x0U;
//    }
//    if( HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_INTOSC2TRIM) = 0x0U)
//    {
//        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_INTOSC2TRIM) = 0x0U;
//    }

    EDIS;

    //
    // Disable ADC clock
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_ADCB);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_ADCC);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_ADCD);
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

void Example_setResultPass(void)
{
    Example_Result = PASS;
}

void Example_setResultFail(void)
{
    Example_Result = FAIL;
}

void Example_done(void)
{
    while(1);
}
