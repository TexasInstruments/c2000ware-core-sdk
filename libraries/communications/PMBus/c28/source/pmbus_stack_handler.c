//###########################################################################
//
// FILE:   pmbus_stack_handler.c
//
// TITLE:  PMBUS Communications State Machine
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


//
// Includes
//
#include "pmbus_stack_handler.h"

//
// Defines
//
PMBUS_STACK_FILENUM(2)


//*****************************************************************************
//
// PMBusStack_targetStateHandler
//
//*****************************************************************************
void PMBusStack_targetStateHandler(PMBus_StackHandle handle)
{
    //
    // Read the status bits once at the start of each state handler
    // The status bits are cleared on a read, therefore, they should be
    // read once at the start of each ISR; any subsequent flags will cause
    // another interrupt
    //
#ifndef PMBUS_OVER_I2C
    PMBusStackObject_setModuleStatus(handle,
                                     PMBus_getStatus(handle->moduleBase));
#else
    PMBusStackObject_setModuleStatus(handle,
                                     I2C_getStatus(handle->moduleBase));
#endif
    switch(PMBusStackObject_getNextState(handle))
    {
        case PMBUS_STACK_STATE_IDLE:
            PMBusStack_targetIdleStateHandler(handle);
            break;
        case PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM:
            PMBusStack_targetReceiveByteWaitForEOMStateHandler(handle);
            break;
        case PMBUS_STACK_STATE_READ_BLOCK:
            PMBusStack_targetReadBlockStateHandler(handle);
            break;
        case PMBUS_STACK_STATE_READ_WAIT_FOR_EOM:
            PMBusStack_targetReadWaitForEOMStateHandler(handle);
            break;
        case PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL:
            PMBusStack_targetBlockWriteOrProcessCallStateHandler(handle);
            break;
#ifndef PMBUS_OVER_I2C
        case PMBUS_STACK_STATE_EXTENDED_COMMAND:
            PMBusStack_targetExtendedCommandStateHandler(handle);
            break;
#endif
        default:
            PMBusStackObject_setCurrentState(handle, PMBUS_STACK_STATE_IDLE);
            PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_IDLE);
            PMBusStack_targetIdleStateHandler(handle);
            break;
    }
}

//
// End of File
//
