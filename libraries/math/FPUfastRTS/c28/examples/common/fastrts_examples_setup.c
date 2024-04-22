//#############################################################################
//
//! \file   fastrts_examples_setup.c
//!
//! \brief  Fast RTS Examples (f28002x) Common Code
//! \author Ritvik Sadana
//! \date   Feb 2, 2018
//
//  Group:          C2000
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################


//*****************************************************************************
// the includes
//*****************************************************************************
#include "fastrts_examples_setup.h"
#include "fpu.h"

//*****************************************************************************
// the globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("FpuRegsFile")
#else
#pragma DATA_SECTION(FpuRegs,"FpuRegsFile");
#endif
//! \brief FPU Register object
//
volatile struct FPU_REG FpuRegs;

//*****************************************************************************
// the function definitions
//*****************************************************************************

//=============================================================================
// FastRTS_Example_setupSysCtrl()
//=============================================================================
void FastRTS_Example_setupSysCtrl( void )
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
 
    
}

//=============================================================================
// FastRTS_Example_setupFlash()
//=============================================================================
void FastRTS_Example_setupFlash( void )
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
    // Copy FPU Math Tables from Flash to RAM
    //
    // The FPUmathTablesRunStart, FPUmathTablesLoadSize, and
    // FPUmathTablesLoadStart symbols are created by the linker. Refer to the
    // device .cmd file.
    //
#if defined(__TMS320C28XX_FPU64__)
    memcpy(&FPU64mathTablesRunStart, &FPU64mathTablesLoadStart,
            (uint32_t)&FPU64mathTablesLoadSize);
#else
    memcpy(&FPUmathTablesRunStart, &FPUmathTablesLoadStart,
                (uint32_t)&FPUmathTablesLoadSize);
#endif

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
