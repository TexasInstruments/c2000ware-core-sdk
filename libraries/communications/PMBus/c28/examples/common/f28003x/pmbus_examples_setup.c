//###########################################################################
//
// FILE:   pmbus_examples_setup.c
//
// TITLE:  f28003x Examples Common Code
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2015-2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Includes
//
#include "pmbus_examples_setup.h"

//*****************************************************************************
//
// PMBusExample_setupGPIO
//
//*****************************************************************************
void PMBusExample_setupGPIO(void)
{
    //
    // PMBus module is accessible over other GPIO pin mux configurations
    // as well. Refer to the device TRM for the different pin configurations
    //
    GPIO_setPinConfig(GPIO_12_PMBUSA_CTL);
    GPIO_setPinConfig(GPIO_13_PMBUSA_ALERT);
    GPIO_setPinConfig(GPIO_14_PMBUSA_SDA);
    GPIO_setPinConfig(GPIO_15_PMBUSA_SCL);
}

//*****************************************************************************
//
// PMBusExample_setupSysCtrl
//
//*****************************************************************************
void PMBusExample_setupSysCtrl(void)
{
    //
    // Disable the watchdog
    //
    SysCtl_disableWatchdog();

    //
    // Setup PLL and clock dividers for 100MHz
    //
    SysCtl_setClock(DEVICE_SETCLOCK_CFG);

    //
    // Enable the PMBUS-A peripheral at the system level
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PMBUSA);
}

//*****************************************************************************
//
// PMBusExample_setupInterrupts
//
//*****************************************************************************
void PMBusExample_setupInterrupts(void(*pmbusISR)(void))
{
    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts
    //
    Interrupt_initModule();

    //
    // Initialize the interrupt vector table
    //
    Interrupt_initVectorTable();

    //
    // Register user defined PMBUS ISR
    //
    Interrupt_register(INT_PMBUSA, pmbusISR);

    //
    // Enable the PMBUS interrupt
    //
    Interrupt_enable(INT_PMBUSA);

    //
    // ACK any pending group interrupts (if any got set)
    //
    Interrupt_clearACKGroup(PMBUS_INT_ACK);

    //
    // Globally enable all interrupts
    //
    Interrupt_enableGlobal();
}

//*****************************************************************************
//
// PMBusExample_setupFlash
//
//*****************************************************************************
void PMBusExample_setupFlash(void)
{
#if defined(_FLASH)
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
#endif //defined(_FLASH)
}

//*****************************************************************************
//
// done
//
//*****************************************************************************
void done(void)
{
    for(;;);
}

//*****************************************************************************
//
// __error__
//
//*****************************************************************************
void __error__(const char *filename, uint32_t line)
{
    __asm(" ESTOP0");
}

//
// End of File
//
