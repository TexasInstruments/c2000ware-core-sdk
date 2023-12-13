//#############################################################################
//
//! \file   dsp_examples_setup.c
//!
//! \brief  DSP Examples Common Code
//!
//! \date   Jan 8, 2018
//
//  Group:          C2000

//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2020 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################


//*****************************************************************************
// the includes
//*****************************************************************************
#include "dsp_examples_setup.h"
#include "sysctl.h"


//=============================================================================
// DSP_Example_setupSysCtrl()
//=============================================================================
void DSP_Example_setupSysCtrl( void )
{
    //
    // Disable the watchdog
    //
    SysCtl_disableWatchdog();

    //
    // Set up PLL control and clock dividers
    //
    SysCtl_setClock(DEVICE_SETCLOCK_CFG);

    //
    // Make sure the LSPCLK divider is set to the default (divide by 4)
    //
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_4);
/*
    NOTE: This section needs to be uncommented if the examples are using the CM
    //
    // Set up AUXPLL control and clock dividers needed for CMCLK
    //
    SysCtl_setAuxClock(DEVICE_AUXSETCLOCK_CFG);

    //
    // Set up CMCLK to use AUXPLL as the clock source and set the
    // clock divider to 1.
    //
    SysCtl_setCMClk(SYSCTL_CMCLKOUT_DIV_1,SYSCTL_SOURCE_AUXPLL);
    //
*/
    // Enable Peripherals
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);


}

//=============================================================================
// DSP_Example_initGPIO()
//=============================================================================
void DSP_Example_initGPIO(void)
{
    //
    // Disable pin locks.
    //
   GPIO_unlockPortConfig(GPIO_PORT_A, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_B, 0xFFFFFFFF);
  //  GPIO_unlockPortConfig(GPIO_PORT_C, 0xFFFFFFFF); //Needs to be uncommented out for f2838x
}

//=============================================================================
// DSP_Example_setupFlash()
//=============================================================================
void DSP_Example_setupFlash( void )
{
#if defined(_FLASH)
    //
    // Copy time critical code and flash setup code to RAM. This includes the
    // following functions: InitFlash();
    //
    // The RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart symbols
    // are created by the linker. Refer to the device .cmd file.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (uint32_t)&RamfuncsLoadSize);

    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //
    Flash_initModule(FLASH0CTRL_BASE, FLASH0ECC_BASE, DEVICE_FLASH_WAITSTATES);
#endif //defined(_FLASH)
}

//=============================================================================
// done()
//=============================================================================
void done( void )
{
    for(;;);
}

//=============================================================================
// __error__()
//=============================================================================
void __error__(const char *filename, uint32_t line)
{
    __asm(" ESTOP0");
}

// End of File
