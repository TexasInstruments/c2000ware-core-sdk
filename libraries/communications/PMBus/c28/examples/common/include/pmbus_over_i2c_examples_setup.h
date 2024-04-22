//###########################################################################
//
// FILE:   pmbus_over_i2c_examples_setup.h
//
// TITLE:  PMBus over I2C Examples Common Code
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2015-2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################
#ifndef PMBUS_OVER_I2C_EXAMPLES_SETUP_H
#define PMBUS_OVER_I2C_EXAMPLES_SETUP_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Includes
//
#include <stdint.h>
#include "device.h"
#include "pmbus_examples_defines.h"

//*****************************************************************************
//
//!
//! \defgroup PMBUS_OVER_I2C_EXAMPLES_SETUP PMBus over I2C Examples Setup Code
//
//!
//! \ingroup PMBUS_OVER_I2C_EXAMPLES_SETUP
// @{
//
//*****************************************************************************

//
// Defines
//
#define NTESTS                   14U
#define NENABLEDTESTS            14U
#define TARGET_ADDRESS            0x6AU
#define TARGET_2_ADDRESS          0x39U
#define TARGET_ADDRESSMASK        0x7FU
#define ALERT_RESPONSE_ADDRESS   0x0CU
#define PMBUS_ENABLE_WRITE       0U
#define DATA_BYTE_COUNT          255U

//
// Send Byte Test
//
#define TEST1_DATA_BYTE          0x55U

//
// Write Byte Test
//
#define TEST2_DATA_BYTE          0xAAU

//
// Write Word Test
//
#define TEST3_DATA_BYTE_1        0xAAU
#define TEST3_DATA_BYTE_2        0x7EU

//
// Receive Byte Test
//
#define TEST5_DATA_BYTE          0x55U

//
// Process Call Test
//
#define TEST14_DATA_BYTE_1       0xAAU
#define TEST14_DATA_BYTE_2       0x7EU
#define TEST14_XOR_MASK          0x55U

//
// Group Command Test
//
#define TEST17_2BYTES            2U

//
// Extended Write Word Test
//
#define TEST19_2BYTES            2U
#define TEST19_4BYTES            4U

//
// Extended Read Byte Test
//
#define TEST20_2BYTES            2U

//
// Extended Read Word Test
//
#define TEST21_2BYTES            2U

//
// Generic Test Command XOR Masks
//
#define CMD_XOR_MASK_V1          0xFFU
#define CMD_XOR_MASK_V2          0x55U
#define CMD_XOR_MASK_V3          1U
#define CMD_XOR_MASK_V4          2U

//*****************************************************************************
//
//! Setup GPIO pins for PMBUS mode of operation
//!
//! This function configures the GPIO muxing for PMBus.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBus_over_I2C_Example_setupGPIO(void);

//*****************************************************************************
//
//! Setup System Control
//!
//! This function disables the watchdog, enables device PLL, and PMBus
//! peripheral clock.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBus_over_I2C_Example_setupSysCtrl(void);

//*****************************************************************************
//
//! Setup Interrupts
//!
//! \param pmbusISR is the handle to the PMBus ISR function
//!
//! This function enables device and PMBus interrupts. Additionally, the PMBus
//! ISR handler is registered.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBus_over_I2C_Example_setupInterrupts(void(*pmbusISR)(void),void(*pmbusRxFIFOISR)(void));

extern void
PMBus_over_I2C_Example_setupInterrupts_Controller(void(*pmbusISR)(void));

//*****************************************************************************
//
//! Setup Flash
//!
//! This function initializes the flash module.
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBus_over_I2C_Example_setupFlash(void);

//*****************************************************************************
//
//! Done Function
//!
//! This function is an infinite loop which is run at the end of testing.
//!
//! \return None.
//
//*****************************************************************************
extern void
done(void);

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif  // end of  PMBUS_EXAMPLES_SETUP_H definition

// End of File
