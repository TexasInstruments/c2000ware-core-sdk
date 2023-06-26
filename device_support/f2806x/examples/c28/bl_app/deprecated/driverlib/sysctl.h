//###########################################################################
//
// FILE:   sysctl.h
//
// TITLE:  Stellaris style wrapper driver for C28x system control.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V141 $
// $Release Date: January 19, 2015 $
// $Copyright: Copyright (C) 2011-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __SYSCTL_H__
#define __SYSCTL_H__

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
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! Defined System Clock Speed (CPU speed).  Adjust this to reflect your
//! actual clock speed.
//
//*****************************************************************************
#define SYSTEM_CLOCK_SPEED      80000000

//*****************************************************************************
//
// The following are values that can be passed to the
// SysCtlPeripheralPresent(), SysCtlPeripheralEnable(),
// SysCtlPeripheralDisable(), and SysCtlPeripheralReset() APIs as the
// ulPeripheral parameter.  The peripherals in the fourth group (upper nibble
// is 3) can only be used with the SysCtlPeripheralPresent() API.
//
//*****************************************************************************

#define SYSCTL_PERIPH_UART0     0x1  // SCI 0
#define SYSCTL_PERIPH_UART1     0x2  // SCI 1
#define SYSCTL_PERIPH_SPI0      0x3  // SPI 0
#define SYSCTL_PERIPH_SPI1      0x4  // SPI 1
#define SYSCTL_PERIPH_DMA       0x5  // uDMA
#define SYSCTL_PERIPH_USB0      0x6  // USB0

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

    extern void SysCtlPeripheralReset(unsigned long ulPeripheral);
    extern void SysCtlPeripheralEnable(unsigned long ulPeripheral);
    extern void SysCtlPeripheralDisable(unsigned long ulPeripheral);
    extern tBoolean SysCtlPeripheralPresent(unsigned long ulPeripheral);
    extern void SysCtlDelay(unsigned long ulCount);
    extern unsigned long SysCtlClockGet(void);
    extern void SysCtlUSBPLLEnable(void);
    extern void SysCtlUSBPLLDisable(void);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//****************************************************************************    

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __SYSCTL_H__


