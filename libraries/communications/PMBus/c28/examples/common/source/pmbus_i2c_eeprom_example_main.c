//###########################################################################
//
// FILE:   pmbus_i2c_eeprom_example_main.c
//
// TITLE:  PMBus (I2C mode) EEPROM Example
//
//! \addtogroup pmbus_nonlib_example_list
//! <h1>PMBus (I2C mode) EEPROM Example</h1>
//! This example shows how to use PMBus peripheral in I2C mode to read / write
//! to EEPROM in different read / write modes. Different modes supported:-
//!   - EEPROM_byteWrite             - Used to write a byte of data in
//!                                    specified EEPROM address
//!   - EEPROM_PageWrite             - Used to write a specified number of
//!                                    bytes from data pointer into the
//!                                    specified address
//!   - EEPROM_CurrentAddress_Read   - Used to read a byte referenced by
//!                                    current EEPROM internal address pointer
//!   - EEPROM_SequentialRead        - Used to read data from EEPROM sequentially
//!                                    of specified size
//!   - EEPROM_RandomRead            - Used to read upto 4 bytes of data  of data
//!                                    sequentially from a given EEPROM address
//!
//!  External Connections
//!   - Connect external I2C EEPROM at target address 0x50
//!   - Connect GPIO25/PMBus Data to external EEPROM SDA (serial data) pin
//!   - Connect GPIO24/PMBus CLK  to external EEPROM SCL (serial clock) pin
//!
//!  Watch Variables
//!   - eepromStatus - Used as a flag variable to check whether EEPROM drivers
//!                    executed correctly
//!   - txbuf        - Transmit buffer used to send the data to be programmed
//!                    in EEPROM
//!   - rxbuf        - Receive buffer used to store the data read from EEPROM
//!
//! Note the EEPROM used for this example is AT24C256
//! (http://www.ti.com/lit/an/slaa208a/slaa208a.pdf)
//!
//! Note this examples doesn't use the PMBus target communication stack.
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2015-2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "pmbus_eeprom.h"

//
// Defines
//
#define ENABLE  1
#define DISABLE 0
#define XCLKOUT DISABLE

#define XCLKOUT_DIVIDER(x)  EALLOW; HWREG(CLKCFG_BASE + SYSCTL_O_XCLKOUTDIVSEL) = x;EDIS;

#define PMBUS_FSM_FREQ     10000000U
#ifdef PMBUS_F28004x
#define SYSCLK_FREQ        100000000U
#endif // PMBUS_F28004x
#ifdef PMBUS_F2838x
#define SYSCLK_FREQ        200000000U
#endif // PMBUS_F2838x

#define SYSCTL_XCLKOUT_DIV_4  2
#define XCLKOUT_DIVIDE(x)    EALLOW; HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL3) |= (uint16_t)x;EDIS;

//
// Function Prototypes
//
void fail(void);
void pass(void);
void initPMBusI2C(void);
void initPMBusGPIO(void);

//
// Main
//
void main(void)
{
    uint16_t  txbuf[EEPROM_PAGE_SIZE + 2U];
    uint16_t* p_txbuf = txbuf;
    uint16_t rxbuf[512U];
    int j;
    uint16_t eepromStatus = SUCCESS;
    uint16_t eepromAddress = (uint16_t)((EEPROM_HIGH_ADDR << 8U) | EEPROM_LOW_ADDR);

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Optionally configure the external clock output
    // to read PLL system clock
    //
#ifdef XCLKOUT
#ifdef PMBUS_F28004x
    GPIO_setPinConfig(GPIO_16_XCLKOUT);
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_PLLSYS);
    XCLKOUT_DIVIDE(SYSCTL_XCLKOUT_DIV_4);
#endif // PMBUS_F28004x
#ifdef PMBUS_F2838x
    GPIO_setPinConfig(GPIO_73_XCLKOUT);
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_SYSCLK);
    SysCtl_setXClk(SYSCTL_XCLKOUT_DIV_8);
#endif // PMBUS_F2838x
#endif // XCLKOUT

    //
    // Configure the PMBus GPIOs
    //
    initPMBusGPIO();

    //
    // Initialize PIE and clear PIE registers. Disable CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Set I2C use, initializing it for FIFO mode
    //
    initPMBusI2C();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    PMBus_enableInterrupt(PMBUSA_BASE,PMBUS_INT_DATA_REQUEST |
                                      PMBUS_INT_DATA_READY   |
                                      PMBUS_INT_BUS_FREE     |
                                      PMBUS_INT_EOM);

    //
    // Set the EEPROM address in the transmit buffer
    //
    txbuf[0U] = EEPROM_HIGH_ADDR;
    txbuf[1U] = EEPROM_LOW_ADDR;
    p_txbuf = &txbuf[2U];

    //
    // Assign data for transmission
    //
    for(j = 0U; j < EEPROM_PAGE_SIZE; j++)
    {
        *p_txbuf++ = j;
    }

    //
    // Perform series of EEPROM operations
    //
    eepromStatus = PMBusEEPROM_writePage(eepromAddress, txbuf, EEPROM_PAGE_SIZE);

    eepromStatus = PMBusEEPROM_performSequentialRead(eepromAddress, rxbuf, (2U * EEPROM_PAGE_SIZE));

    eepromStatus = PMBusEEPROM_writeByte(eepromAddress + 1U, 0x5AU);

    eepromStatus = PMBusEEPROM_writeByte(eepromAddress + 2U, 0xA5U);

    eepromStatus = PMBusEEPROM_performRandomRead(eepromAddress, rxbuf, FOUR_BYTES);

    eepromStatus = PMBusEEPROM_performSequentialRead(eepromAddress + 4U, rxbuf, EEPROM_PAGE_SIZE);

    eepromStatus = PMBusEEPROM_transmitAddress(eepromAddress + 8U);

    eepromStatus = PMBusEEPROM_readCurrentAddress(rxbuf, FOUR_BYTES);

    eepromStatus = PMBusEEPROM_readCurrentAddress(rxbuf, FOUR_BYTES);

    eepromStatus = PMBusEEPROM_performRandomRead(eepromAddress + 40U, rxbuf, FOUR_BYTES);

    //
    // Check EEPROM status for pass or fail
    //
    if(eepromStatus == SUCCESS)
    {
        pass();
    }
    else
    {
        fail();
    }
}

//
// initPMBusI2C - Function to configure PMBusA in I2C mode
//
void
initPMBusI2C(void)
{
    //
    // Disable module
    //
    PMBus_disableModule(BASE);

    //
    // Setup PMBus in controller mode
    //
    PMBus_initControllerMode(BASE);

    //
    // Put PMBus into I2C mode
    //
    PMBus_enableI2CMode(BASE);

    //
    // Setup PMBus module and bus clocking
    //
    // SYSCLK        = 200 MHz
    // PMBus_FSM_CLK = 10  MHz
    //
    PMBus_configModuleClock(BASE, PMBUS_MODULE_FREQ_MAX, PMBUS_SYS_FREQ_MAX);
    PMBus_configBusClock(BASE, PMBUS_CLOCKMODE_STANDARD, PMBUS_MODULE_FREQ_MAX);

    //
    // Setup PMBus timing parameters
    //
    PMBus_setDefaultTimingParameter(BASE);

    //
    // Re-enable module
    //
    PMBus_enableModule(BASE);
}

//
// initPMBusGPIO - Function to configure the PMBusA GPIOs
//
void
initPMBusGPIO(void)
{
    //
    // Initialize GPIOs 25 and 24 for use as PMBDAT and PMBSCL respectively
    //
    GPIO_setPinConfig(GPIO_25_PMBUSA_SDA);
    GPIO_setPadConfig(25, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(25, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(GPIO_24_PMBUSA_SCL);
    GPIO_setPadConfig(24, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(24, GPIO_QUAL_ASYNC);  
}

//
// pass - Function to be called if data written matches data read
//
void
pass(void)
{
    asm("   ESTOP0");
    for(;;);
}

//
// fail - Function to be called if data written does NOT match data read
//
void fail(void)
{
    asm("   ESTOP0");
    for(;;);
}

//
// End of File
//

