//###########################################################################
//
// FILE:   pmbus_examples_defines.h
//
// TITLE:  f28p65x Examples Common Code
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2015-2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################
#ifndef F280015X_EXAMPLES_DEFINES_H
#define F280015X_EXAMPLES_DEFINES_H

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
#define PMBUS_INT_ACK            INTERRUPT_ACK_GROUP9
#define I2C_INT_ACK              INTERRUPT_ACK_GROUP8
#define TIMER_INT_ACK            INTERRUPT_ACK_GROUP1

#ifdef __cplusplus
}
#endif // extern "C"

#endif  // end of  F280015X_EXAMPLES_DEFINES_H definition

// End of File
