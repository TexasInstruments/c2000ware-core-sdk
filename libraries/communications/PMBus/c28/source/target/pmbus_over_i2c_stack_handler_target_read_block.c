//###########################################################################
//
// FILE:   pmbus_over_i2cstack_handler_target_read_block.c
//
// TITLE:  PMBUS_OVER_I2C_STACK_STATE_READ_BLOCK handler
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

#ifdef PMBUS_OVER_I2C
//
// Includes
//
#include "pmbus_stack_handler.h"

//
// Defines
//
PMBUS_STACK_FILENUM(4)

//*****************************************************************************
//
// PMBusStack_targetReadBlockStateHandler
//
//*****************************************************************************
void PMBusStack_targetReadBlockStateHandler(PMBus_StackHandle handle)
{


    //
    // Locals
    //
    uint32_t status = PMBusStackObject_getModuleStatus(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t nBytes = PMBusStackObject_getNumOfBytes(handle);
    uint16_t *currentPointer;
    uint16_t bytesTransmitted = 0U;
    uint16_t bytesToTransmit = 0U;
#ifdef TIMEOUT
    uint32_t timerBase = PMBusStackObject_getTimerBase(handle);
#endif
    //
    // Set the current state to READ_BLOCK
    //
    PMBusStackObject_setCurrentState(handle, PMBUS_STACK_STATE_READ_BLOCK);

    //
    // Check if EOM/STOP condition is received
    //
    //if((status & I2C_STS_STOP_CONDITION)!=0U)
    if(STOP_CONDITION_DETECTED)
    {
        //
        // EOM = 1,
        // Controller has prematurely terminated the block read,
        // or in the READ/WAIT_FOR_EOM state, only 4 bytes
        // were required to be sent, and the transaction was complete
        // NOTE: ACK is required to allow the target to ack its address in
        // any subsequent transaction.
        //
        I2C_clearStatus(base, (I2C_STS_STOP_CONDITION | I2C_INT_TX_DATA_RDY));

        I2C_enableInterrupt(base, I2C_INT_TX_DATA_RDY);

        //
        // Block Read was successful, return to the
        // Idle state
        //
        PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_IDLE);
#ifdef TIMEOUT
        CPUTimer_stopTimer(timerBase);
        CPUTimer_reloadTimerCounter(timerBase);
#endif
    }
    else if(TARGET_TRANSMITTER)
    {
        //
        // DATA_REQUEST = 1, EOM = 0, NACK = 0
        //
        currentPointer = PMBusStackObject_getCurrentPositionPointer(handle);
        bytesTransmitted = (uint16_t)(currentPointer - buffer);
        bytesToTransmit = nBytes - bytesTransmitted;

        if(bytesToTransmit > 4U)
        {
            //
            // Put the data to the PMBUS Transmit buffer, without PEC
            //

            //PMBus_over_I2C_putData(base, currentPointer, bytesToTransmit);
            PMBus_over_I2C_putData(base, currentPointer, 4U);

            //
            // Update the current index into the buffer
            //
            PMBusStackObject_setCurrentPositionPointer(handle,
                                                       &currentPointer[4U]);
        }
        else //bytesToTransmit <= 4U (the last transmission)
        {
            //
            // Put the last few bytes (<=4) to the PMBUS Transmit buffer,
            // with PEC
            //
            PMBus_over_I2C_putData(base, currentPointer, bytesToTransmit);

            //
            // Return to the EOM State
            //
            PMBusStackObject_setNextState(handle,
                                          PMBUS_STACK_STATE_READ_WAIT_FOR_EOM);
        }
    }
    else
    {
        //
        // Unhandled exception
        //
        PMBUS_STACK_ASSERT(0);
    }


}
#endif
//
// End of File
//
