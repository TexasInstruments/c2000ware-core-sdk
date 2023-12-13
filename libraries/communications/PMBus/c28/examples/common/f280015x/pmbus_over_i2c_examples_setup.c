//###########################################################################
//
// FILE:   pmbus_examples_setup.c
//
// TITLE:  f280015x Examples Common Code
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
#include "pmbus_over_i2c_examples_setup.h"

//*****************************************************************************
//
// PMBusExample_setupGPIO
//
//*****************************************************************************
void PMBus_over_I2C_Example_setupGPIO(void)
{
    //
    // I2C module is accessible over other GPIO pin mux configurations
    // as well. Refer to the device TRM for the different pin configurations
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SDAA);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SDAA, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SDAA, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCLA);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCLA, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCLA, GPIO_QUAL_ASYNC);
}

//*****************************************************************************
//
// PMBus_over_I2C_Example_setupSysCtrl
//
//*****************************************************************************
void PMBus_over_I2C_Example_setupSysCtrl(void)
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
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CA);
}

//*****************************************************************************
//
// PMBusExample_setupInterrupts
//
//*****************************************************************************
void PMBus_over_I2C_Example_setupInterrupts(void(*pmbusISR)(void), void(*pmbusRxFIFOISR)(void))
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
    Interrupt_register(INT_I2CA, pmbusISR);

    //
    // Enable the PMBUS interrupt
    //
    Interrupt_enable(INT_I2CA);

    // Enable FIFO interrupt
    Interrupt_register(INT_I2CA_FIFO, pmbusRxFIFOISR);
    Interrupt_enable(INT_I2CA_FIFO);

    //
    // ACK any pending group interrupts (if any got set)
    //
    Interrupt_clearACKGroup(I2C_INT_ACK);

    //
    // Globally enable all interrupts
    //
    Interrupt_enableGlobal();
}

void PMBus_over_I2C_Example_setupInterrupts_Controller(void(*pmbusISR)(void))
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
    Interrupt_register(INT_I2CA, pmbusISR);

    //
    // Enable the PMBUS interrupt
    //
    Interrupt_enable(INT_I2CA);



    //
    // ACK any pending group Interrupts (if any got set)
    //
    Interrupt_clearACKGroup(I2C_INT_ACK);

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
void PMBus_over_I2C_Example_setupFlash(void)
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
