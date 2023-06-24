//###########################################################################
//
// FILE:   gpio.h
//
// TITLE:  CM GPIO driver.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef GPIO_H
#define GPIO_H

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
//! \addtogroup gpio_api GPIO
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "debug.h"

//*****************************************************************************
//
// Useful defines used within the driver functions to access gpio registers.
// Not intended for use by application code.
//
// Divide by 4 is for CM which has byte access
//
//*****************************************************************************
#define GPIO_DATA_REGS_STEP     ((GPIO_O_GPBDAT - GPIO_O_GPADAT) / 4U)
#define GPIO_DATA_READ_REGS_STEP ((GPIO_O_GPBDAT_R - GPIO_O_GPADAT_R) / 4U)

#define GPIO_GPxDAT_INDEX       (GPIO_O_GPADAT / 4U)
#define GPIO_GPxSET_INDEX       (GPIO_O_GPASET / 4U)
#define GPIO_GPxCLEAR_INDEX     (GPIO_O_GPACLEAR / 4U)
#define GPIO_GPxTOGGLE_INDEX    (GPIO_O_GPATOGGLE / 4U)

#define GPIO_GPxDAT_R_INDEX     (GPIO_O_GPADAT_R / 4U)


#ifndef DOXYGEN_PDF_IGNORE
//*****************************************************************************
//
// Values that can be passed to GPIO_setPadConfig() as the pinType parameter
// and returned by GPIO_getPadConfig().
//
//*****************************************************************************
#define GPIO_PIN_TYPE_STD       0x0000U //!< Push-pull output or floating input
#define GPIO_PIN_TYPE_PULLUP    0x0001U //!< Pull-up enable for input
#define GPIO_PIN_TYPE_INVERT    0x0002U //!< Invert polarity on input
#define GPIO_PIN_TYPE_OD        0x0004U //!< Open-drain on output
#endif

//*****************************************************************************
//
//! Values that can be passed to GPIO_readPortData(), GPIO_setPortPins(),
//! GPIO_clearPortPins(), and GPIO_togglePortPins() as the \e port parameter.
//
//*****************************************************************************
typedef enum
{
    GPIO_PORT_A = 0,                    //!< GPIO port A
    GPIO_PORT_B = 1,                    //!< GPIO port B
    GPIO_PORT_C = 2,                    //!< GPIO port C
    GPIO_PORT_D = 3,                    //!< GPIO port D
    GPIO_PORT_E = 4,                    //!< GPIO port E
    GPIO_PORT_F = 5                     //!< GPIO port F
} GPIO_Port;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks that a pin number is valid for a device.
//!
//! Note that this function reflects the highest possible GPIO number of a
//! device on its biggest package. Check the datasheet to see what the actual
//! range of valid pin numbers is for a specific package.
//!
//! \return None.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
GPIO_isPinValid(uint32_t pin)
{
    return(pin <= 168U);
}
#endif

//*****************************************************************************
//
//! Reads the value present on the specified pin.
//!
//! \param pin is the identifying GPIO number of the pin.
//!
//! The value at the specified pin are read, as specified by \e pin. The value
//! is returned for both input and output pins.
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin.
//!
//! \return Returns the value in the data register for the specified pin.
//
//*****************************************************************************
static inline uint32_t
GPIO_readPin(uint32_t pin)
{
    volatile uint32_t *gpioDataReg;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));

    gpioDataReg = (uint32_t *)((uintptr_t)GPIODATA_BASE) +
                  ((pin / 32U) * GPIO_DATA_REGS_STEP);

    return((gpioDataReg[GPIO_GPxDAT_INDEX] >> (pin % 32U)) & (uint32_t)0x1U);
}

//*****************************************************************************
//
//! Reads the data register value for specified pin.
//!
//! \param pin is the identifying GPIO number of the pin.
//!
//! The value available at the data register for the specified pin is read, as
//! specified by \e pin. The value is returned for both input and output pins.
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin.
//!
//! \sa GPIO_readPin()
//!
//! \return Returns the value in the data register for the specified pin.
//
//*****************************************************************************
static inline uint32_t
GPIO_readPinDataRegister(uint32_t pin)
{
    volatile uint32_t *gpioDataReg;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));

    gpioDataReg = (uint32_t *)((uintptr_t)GPIODATAREAD_BASE) +
                  ((pin / 32U) * GPIO_DATA_READ_REGS_STEP);

    return((gpioDataReg[GPIO_GPxDAT_R_INDEX] >> (pin % 32U)) & (uint32_t)0x1U);
}

//*****************************************************************************
//
//! Writes a value to the specified pin.
//!
//! \param pin is the identifying GPIO number of the pin.
//! \param outVal is the value to write to the pin.
//!
//! Writes the corresponding bit values to the output pin specified by
//! \e pin.  Writing to a pin configured as an input pin has no effect.
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin.
//!
//! \return None.
//
//*****************************************************************************
static inline void
GPIO_writePin(uint32_t pin, uint32_t outVal)
{
    volatile uint32_t *gpioDataReg;
    uint32_t pinMask;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));

    gpioDataReg = (uint32_t *)((uintptr_t)GPIODATA_BASE) +
                  ((pin / 32U) * GPIO_DATA_REGS_STEP);

    pinMask = (uint32_t)1U << (pin % 32U);

    if(outVal == 0U)
    {
        gpioDataReg[GPIO_GPxCLEAR_INDEX] = pinMask;
    }
    else
    {
        gpioDataReg[GPIO_GPxSET_INDEX] = pinMask;
    }
}

//*****************************************************************************
//
//! Toggles the specified pin.
//!
//! \param pin is the identifying GPIO number of the pin.
//!
//! Writes the corresponding bit values to the output pin specified by
//! \e pin.  Writing to a pin configured as an input pin has no effect.
//!
//! The pin is specified by its numerical value. For example, GPIO34 is
//! specified by passing 34 as \e pin.
//!
//! \return None.
//
//*****************************************************************************
static inline void
GPIO_togglePin(uint32_t pin)
{
    volatile uint32_t *gpioDataReg;

    //
    // Check the arguments.
    //
    ASSERT(GPIO_isPinValid(pin));

    gpioDataReg = (uint32_t *)((uintptr_t)GPIODATA_BASE) +
                  ((pin / 32U) * GPIO_DATA_REGS_STEP);

    gpioDataReg[GPIO_GPxTOGGLE_INDEX] = (uint32_t)1U << (pin % 32U);
}

//*****************************************************************************
//
//! Reads the data on the specified port.
//!
//! \param port is the GPIO port being accessed in the form of \b GPIO_PORT_X
//! where X is the port letter.
//!
//! \return Returns the value available on pin for the specified port. Each
//! bit of the the return value represents a pin on the port, where bit 0
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//
//*****************************************************************************
static inline uint32_t
GPIO_readPortData(GPIO_Port port)
{
    volatile uint32_t *gpioDataReg;

    //
    // Get the starting address of the port's registers and return DATA.
    //
    gpioDataReg = (uint32_t *)((uintptr_t)GPIODATA_BASE) +
                  ((uint32_t)port * GPIO_DATA_REGS_STEP);

    return(gpioDataReg[GPIO_GPxDAT_INDEX]);
}

//*****************************************************************************
//
//! Reads the data written in GPIO Data Register.
//!
//! \param port is the GPIO port being accessed in the form of \b GPIO_PORT_X
//! where X is the port letter.
//!
//! Reads the data written in GPIO Data Register for the specified port. In
//! previous devices, read of GPIO data registers resulted in read of
//! corespoinding pins. The function \b GPIO_readPortData() returns the value
//! on pin.
//!
//! \sa GPIO_readPortData()
//!
//! \return Returns the value in the data register for the specified port. Each
//! bit of the the return value represents a pin on the port, where bit 0
//! represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on.
//
//*****************************************************************************
static inline uint32_t
GPIO_readPortDataRegister(GPIO_Port port)
{
    volatile uint32_t *gpioDataReg;

    //
    // Get the starting address of the port's registers and return DATA.
    //
    gpioDataReg = (uint32_t *)((uintptr_t)GPIODATAREAD_BASE) +
                  ((uint32_t)port * GPIO_DATA_READ_REGS_STEP);

    return(gpioDataReg[GPIO_GPxDAT_R_INDEX]);
}

//*****************************************************************************
//
//! Writes a value to the specified port.
//!
//! \param port is the GPIO port being accessed.
//! \param outVal is the value to write to the port.
//!
//! This function writes the value \e outVal to the port specified by the
//! \e port parameter which takes a value in the form of \b GPIO_PORT_X where X
//! is the port letter. For example, use \b GPIO_PORT_A to affect port A
//! (GPIOs 0-31).
//!
//! The \e outVal is a bit-packed value, where each bit represents a bit on a
//! GPIO port. Bit 0 represents GPIO port pin 0, bit 1 represents GPIO port
//! pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
static inline void
GPIO_writePortData(GPIO_Port port, uint32_t outVal)
{
    volatile uint32_t *gpioDataReg;

    //
    // Get the starting address of the port's registers and write to DATA.
    //
    gpioDataReg = (uint32_t *)((uintptr_t)GPIODATA_BASE) +
                  ((uint32_t)port * GPIO_DATA_REGS_STEP);

    gpioDataReg[GPIO_GPxDAT_INDEX] = outVal;
}

//*****************************************************************************
//
//! Sets all of the specified pins on the specified port.
//!
//! \param port is the GPIO port being accessed.
//! \param pinMask is a mask of which of the 32 pins on the port are affected.
//!
//! This function sets all of the pins specified by the \e pinMask parameter on
//! the port specified by the \e port parameter which takes a value in the
//! form of \b GPIO_PORT_X where X is the port letter. For example, use
//! \b GPIO_PORT_A to affect port A (GPIOs 0-31).
//!
//! The \e pinMask is a bit-packed value, where each bit that is set identifies
//! the pin to be set. Bit 0 represents GPIO port pin 0, bit 1 represents GPIO
//! port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
static inline void
GPIO_setPortPins(GPIO_Port port, uint32_t pinMask)
{
    volatile uint32_t *gpioDataReg;

    //
    // Get the starting address of the port's registers and write to SET.
    //
    gpioDataReg = (uint32_t *)((uintptr_t)GPIODATA_BASE) +
                  ((uint32_t)port * GPIO_DATA_REGS_STEP);

    gpioDataReg[GPIO_GPxSET_INDEX] = pinMask;
}

//*****************************************************************************
//
//! Clears all of the specified pins on the specified port.
//!
//! \param port is the GPIO port being accessed.
//! \param pinMask is a mask of which of the 32 pins on the port are affected.
//!
//! This function clears all of the pins specified by the \e pinMask parameter
//! on the port specified by the \e port parameter which takes a value in the
//! form of \b GPIO_PORT_X where X is the port letter. For example, use
//! \b GPIO_PORT_A to affect port A (GPIOs 0-31).
//!
//! The \e pinMask is a bit-packed value, where each bit that is \b set
//! identifies the pin to be cleared. Bit 0 represents GPIO port pin 0, bit 1
//! represents GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
static inline void
GPIO_clearPortPins(GPIO_Port port, uint32_t pinMask)
{
    volatile uint32_t *gpioDataReg;

    //
    // Get the starting address of the port's registers and write to CLEAR.
    //
    gpioDataReg = (uint32_t *)((uintptr_t)GPIODATA_BASE) +
                  ((uint32_t)port * GPIO_DATA_REGS_STEP);

    gpioDataReg[GPIO_GPxCLEAR_INDEX] = pinMask;
}

//*****************************************************************************
//
//! Toggles all of the specified pins on the specified port.
//!
//! \param port is the GPIO port being accessed.
//! \param pinMask is a mask of which of the 32 pins on the port are affected.
//!
//! This function toggles all of the pins specified by the \e pinMask parameter
//! on the port specified by the \e port parameter which takes a value in the
//! form of \b GPIO_PORT_X where X is the port letter. For example, use
//! \b GPIO_PORT_A to affect port A (GPIOs 0-31).
//!
//! The \e pinMask is a bit-packed value, where each bit that is set identifies
//! the pin to be toggled. Bit 0 represents GPIO port pin 0, bit 1 represents
//! GPIO port pin 1, and so on.
//!
//! \return None.
//
//*****************************************************************************
static inline void
GPIO_togglePortPins(GPIO_Port port, uint32_t pinMask)
{
    volatile uint32_t *gpioDataReg;

    //
    // Get the starting address of the port's registers and write to TOGGLE.
    //
    gpioDataReg = (uint32_t *)((uintptr_t)GPIODATA_BASE) +
                  ((uint32_t)port * GPIO_DATA_REGS_STEP);

    gpioDataReg[GPIO_GPxTOGGLE_INDEX] = pinMask;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  GPIO_H
