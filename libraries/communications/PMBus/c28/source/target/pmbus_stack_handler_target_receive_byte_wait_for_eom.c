//###########################################################################
//
// FILE:   pmbus_stack_handler_target_receive_byte_wait_for_eom.c
//
// TITLE:  PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM handler
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
#include "pmbus_stack_handler.h"

//
// Defines
//
PMBUS_STACK_FILENUM(7)

//*****************************************************************************
//
// PMBusStack_targetReceiveByteWaitForEOMStateHandler
//
//*****************************************************************************
void PMBusStack_targetReceiveByteWaitForEOMStateHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint32_t status = PMBusStackObject_getModuleStatus(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    uint32_t base = PMBusStackObject_getModuleBase(handle);

    //
    // Set the current state to RECEIVE_BYTE_WAIT_FOR_EOM
    //
    PMBusStackObject_setCurrentState(handle,
                                   PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM);

    if(((status & PMBUS_PMBSTS_EOM) != 0U) &&
       ((status & PMBUS_PMBSTS_NACK) != 0U))
    {
        //
        // DATA_READY = 0, EOM = 1, DATA_REQUEST = 0, NACK = 1
        // After a DATA_REQUEST for a receive byte is seen by the target,
        // it places the requested byte (and PEC) on the line and transitions
        // from the idle to the recevie byte wait-for-eom state
        //
        // The only interrupt expected after the recevied byte is that from an
        // EOM. The quick command also has EOM=1 and DATA_READY=0 at the end.
        // In order to distinguish between the two, if an EOM is received while
        // in this state it was a receive byte, if an EOM was recevied in the
        // idle state it was a quick command
        //
        // NOTE: ACK is required to allow the target to ack its address in
        // any subsequent transaction.
        //
        PMBus_ackTransaction(base);

        //
        // Return to the idle state
        //
        PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_IDLE);

        return;
    }
    else
    {
        //
        // Unhandled Exception
        //
        PMBUS_STACK_ASSERT(0);
    }

}
#endif
//
// End of File
//
