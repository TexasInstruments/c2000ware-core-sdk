//###########################################################################
//
// FILE:   pmbus_stack_config.c
//
// TITLE:  PMBUS Communications Stack Configuration
//
//#############################################################################
//!
//! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//!	All rights reserved not granted herein.
//!	Limited License.
//!
//! Texas Instruments Incorporated grants a world-wide, royalty-free,
//! non-exclusive license under copyrights and patents it now or hereafter
//! owns or controls to make, have made, use, import, offer to sell and sell
//! ("Utilize") this software subject to the terms herein. With respect to the
//! foregoing patent license, such license is granted solely to the extent that
//! any such patent is necessary to Utilize the software alone. The patent
//! license shall not apply to any combinations which include this software,
//! other than combinations with devices manufactured by or for TI 
//! ("TI Devices").
//! No hardware patent is licensed hereunder.
//!
//! Redistributions must preserve existing copyright notices and reproduce this
//! license (including the above copyright notice and the disclaimer and
//! (if applicable) source code license limitations below) in the documentation
//!  and/or other materials provided with the distribution.
//!
//! Redistribution and use in binary form, without modification, are permitted
//! provided that the following conditions are met:
//!
//! * No reverse engineering, decompilation, or disassembly of this software is 
//! permitted with respect to any software provided in binary form.
//! * Any redistribution and use are licensed by TI for use only 
//!   with TI Devices.
//! * Nothing shall obligate TI to provide you with source code for the 
//!   software licensed and provided to you in object code.
//!
//! If software source code is provided to you, modification and redistribution
//! of the source code are permitted provided that the following conditions 
//! are met:
//!
//! * any redistribution and use of the source code, including any resulting
//!   derivative works, are licensed by TI for use only with TI Devices.
//! * any redistribution and use of any object code compiled from the source
//!   code and any resulting derivative works, are licensed by TI for use 
//!   only with TI Devices.
//!
//! Neither the name of Texas Instruments Incorporated nor the names of its
//! suppliers may be used to endorse or promote products derived from this 
//! software without specific prior written permission.
//#############################################################################

#ifndef PMBUS_OVER_I2C
//
// Includes
//
#include <stdint.h>
#include <stdbool.h>
#include "pmbus_stack_config.h"

//
// Defines
//
PMBUS_STACK_FILENUM(1)

#define PMBUS_STACK_TARGET_ADDRESS  0U
#define PMBUS_STACK_TARGET_MASK     0x7FU

//
// Globals
//
PMBus_StackObject PMBusStackTarget;
PMBus_StackHandle PMBusStackTargetHandle = &PMBusStackTarget;

//*****************************************************************************
//
// PMBusStack_initModule
//
//*****************************************************************************
bool PMBusStack_initModule(PMBus_StackHandle handle, const uint32_t moduleBase,
                           uint16_t *buffer)
{
    //
    // Locals
    //
    bool status = false;

    //
    // Set the module base address
    //
    PMBusStackObject_setModuleBase(handle, moduleBase);

    //
    // Assign the buffer pointer to the object, set the current pointer to
    // the head of the buffer
    //
    PMBusStackObject_setBufferPointer(handle, buffer);
    PMBusStackObject_setCurrentPositionPointer(handle, buffer);

    //
    // Reset the PMBUS Module
    //
    PMBus_disableModule(PMBusStackObject_getModuleBase(handle));

    //
    // Take the PMBUS out of reset
    //
    PMBus_enableModule(PMBusStackObject_getModuleBase(handle));

    //
    // Initialize depending upon whether in target or controller mode
    //
    if(PMBusStackObject_getMode(handle) == PMBUS_STACK_MODE_TARGET)
    {
        //
        // Initialize the target module
        //
        PMBus_initTargetMode(PMBusStackObject_getModuleBase(handle),
                            PMBusStackObject_getTargetAddress(handle),
                            PMBusStackObject_getTargetAddressMask(handle));

        //
        // Configure the target module (writes to the PMBSC register)
        //
        PMBus_configTarget(PMBUSA_BASE, (PMBUS_TARGET_ENABLE_PEC_PROCESSING |
                                        PMBUS_TARGET_AUTO_ACK_4_BYTES));

        //
        // Enable interrupts
        //
        //I2C - AAS, FIFO Interrupts RX & TX , STOP
        PMBus_enableInterrupt(PMBusStackObject_getModuleBase(handle),
                              (PMBUS_INT_DATA_READY | PMBUS_INT_DATA_REQUEST |
                               PMBUS_INT_EOM));

        //
        // Reset the state machine
        //
        PMBusStackObject_setCurrentState(handle, PMBUS_STACK_STATE_IDLE);
        PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_IDLE);

        status = true;
    }
    else // (PMBusStackObject_getMode(handle) == PMBUS_STACK_MODE_CONTROLLER)
    {
        //
        // Zero out the target address and set the mask to 0x7F
        // (the mask is N/A in controller mode)
        //
        PMBusStackObject_setTargetAddress(handle, PMBUS_STACK_TARGET_ADDRESS);
        PMBusStackObject_setTargetAddressMask(handle, PMBUS_STACK_TARGET_MASK);

        //
        // Initialize the controller module
        //
        PMBus_initControllerMode(PMBusStackObject_getModuleBase(handle));

        //
        // Enable interrupts
        //
        PMBus_enableInterrupt(PMBusStackObject_getModuleBase(handle),
                              (PMBUS_INT_DATA_READY | PMBUS_INT_DATA_REQUEST |
                               PMBUS_INT_EOM | PMBUS_INT_ALERT));

        //
        // Reset the state machine
        //
        PMBusStackObject_setCurrentState(handle, PMBUS_STACK_STATE_IDLE);
        PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_IDLE);

        status = true;
    }

    return(status);
}

//*****************************************************************************
//
// PMBusStack_defaultTransactionHandler
//
//*****************************************************************************
int32_t PMBusStack_defaultTransactionHandler(PMBus_StackHandle handle)
{
    //
    // Replace with an actual handler. This will stop emulation
    //
    PMBUS_STACK_ASSERT(0);

    return(-1);
}

#endif
//
// End of File
//
