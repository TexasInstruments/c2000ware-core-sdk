//###########################################################################
//
// FILE:   interrupt.h
//
// TITLE:  Stellaris style wrapper driver for C28x PIE Interrupt Controller.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V141 $
// $Release Date: January 19, 2015 $
// $Copyright: Copyright (C) 2011-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

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

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
    extern tBoolean IntMasterEnable(void);
    extern tBoolean IntMasterDisable(void);
    extern void IntRegister(unsigned long ulInterrupt, void (*pfnHandler)(void));
    extern void IntUnregister(unsigned long ulInterrupt);
    extern void IntEnable(unsigned long ulInterrupt);
    extern void IntDisable(unsigned long ulInterrupt);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __INTERRUPT_H__


