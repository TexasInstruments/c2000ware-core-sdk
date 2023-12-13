//###########################################################################
//
// FILE:   pmbus_examples_defines.h
//
// TITLE:  f28002x Examples Common Code
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2015-2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################
#ifndef F28002X_EXAMPLES_DEFINES_H
#define F28002X_EXAMPLES_DEFINES_H

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
// Interrupt Acknowledgement
//
#define PMBUS_INT_ACK          INTERRUPT_ACK_GROUP8
#define I2C_INT_ACK            INTERRUPT_ACK_GROUP8
#define TIMER_INT_ACK          INTERRUPT_ACK_GROUP1

#ifdef __cplusplus
}
#endif // extern "C"

#endif  // end of  F28002X_EXAMPLES_DEFINES_H definition

// End of File
