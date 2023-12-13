//###########################################################################
//
// FILE:   pmbus_over_i2c_lib.h
//
// TITLE:  I2C Functions used in PMBUS Communications Stack
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2015-2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################
#ifdef PMBUS_OVER_I2C

#ifndef PMBUS_OVER_I2C_LIB_H
#define PMBUS_OVER_I2C_LIB_H

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

#include "device.h"

#define WAIT_TILL_TX_FIFO_IS_EMPTY     I2C_getTxFIFOStatus(base)

#define WAIT_TILL_RX_FIFO_IS_FULL    !(I2C_getRxFIFOStatus(base) == I2C_FIFO_RXFULL)

#define WAIT_TILL_RX_FIFO_HAS(x)     !(I2C_getRxFIFOStatus(base) == x)


void I2CWrite(uint32_t base, uint16_t targetAddr, uint16_t *pTXbuff, uint16_t byteCount, bool sendStopCondition);
uint16_t I2CRead(uint32_t base, uint16_t targetAddr, uint16_t *pRXbuff, uint16_t byteCount, bool sendStopCondition);
void I2C_sendRepeatedStartCondition(uint32_t base, uint16_t config);

#ifdef __cplusplus
}
#endif

#endif  // PMBUS_OVER_I2C_LIB_H
#endif // PMBUS_OVER_I2C

