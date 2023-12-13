//###########################################################################
//
// FILE:   pmbus_over_i2c_stack_handler_target_rx_fifo.c
//
// TITLE:  PMBUS_OVER_I2C_STACK_RX_FIFO handler
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
PMBUS_STACK_FILENUM(8)

//*****************************************************************************
//
// PMBusStack_targetIdleStateHandler
// This function is the entry point of the target stack. PMBus will be in IDLE
// state before any transaction. Any transaction which is initiated will
// trigger an interrupt which will be handled by this function in the ISR.
//*****************************************************************************
void PMBusStack_targetRxFIFOHandler(PMBus_StackHandle handle)
{

    //PMBus_StackHandle handle = pmbusStackTargetHandle;
    uint32_t status = PMBusStackObject_getModuleStatus(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    uint16_t *CRCBuffer = PMBusStackObject_getCRCBufferPointer(handle);
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    uint16_t nBytes = 0U;
    uint16_t command = 0;
    uint16_t extcommand = 0;
    uint16_t *currentPointer;
    static bool first_time = true;
    uint16_t targetAddress;

    if(PMBusStackObject_getCurrentState(handle) == PMBUS_STACK_STATE_IDLE)
    {
        //
        // Rewind the current pointer
        //
        PMBusStackObject_setCurrentPositionPointer(handle, buffer);
        first_time = true;
    }

    if(first_time)
    {
        //read the bytes and determine the command
        //nBytes = PMBus_over_I2C_getTargetData(base, buffer) - 1; //excluding PEC
        nBytes = PMBus_over_I2C_getTargetData(base, buffer);
    }
    if(nBytes >= 0x2U)
    {
         command = buffer[0];
         extcommand = buffer[1];
    }


#ifdef PEC_ENABLED

    //
    // Remove the PEC byte
    //
    if(nBytes>1)
    {
        nBytes = nBytes - 1;
    }

    //
    // Get target address
    //
    targetAddress = PMBusStackObject_getTargetAddress(handle);

    //
    // reset CRC buffer size
    //
    PMBusStackObject_setCRCMsgSize(handle, 0U);
    if(command == PMBUS_CMD_MFR_SPECIFIC_COMMAND && extcommand == PMBUS_CMD_STORE_DEFAULT_CODE)
    {
        // Call the handler for the Extended Write Byte transaction
        PMBusStackObject_setNextState(handle,PMBUS_STACK_STATE_EXTENDED_COMMAND);

        //
        // Set the object's nBytes field
        // Set the pointer in the buffer to point to the next
        // available spot
        //
        PMBusStackObject_setCurrentPositionPointer(handle,
                                                   &buffer[nBytes]);

        //
        // Set the object's nBytes field
          PMBusStackObject_setNumOfBytes(handle, nBytes);

        //
        // Set the object transaction type
        //
        PMBusStackObject_setTransactionType(handle,
                                           PMBUS_TRANSACTION_WRITEBYTE);

       #ifdef PEC_ENABLED
       CRCBuffer[0] = targetAddress << 1;
       CRCBuffer[1] = command;
       CRCBuffer[2] = extcommand;
       CRCBuffer[3] = targetAddress << 1;        // store target address
       PMBusStackObject_setCRCMsgSize(handle, 4U);
       #endif
        //
        // Call the handler for the WRITEBYTE transaction
        //
        (void)handle->
                    transactionHandle[PMBUS_TRANSACTION_WRITEBYTE](handle);
        PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM);


    }
    else if(command == PMBUS_CMD_MFR_SPECIFIC_COMMAND && extcommand == PMBUS_CMD_VOUT_COMMAND)
    {
        // Call the handler for the Extended Write Byte transaction
        PMBusStackObject_setNextState(handle,PMBUS_STACK_STATE_EXTENDED_COMMAND);
    }
    else //STOP_CONDITION_DETECTED 
    {
        // Call the handler for the WRITEWORD transaction
       PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_WRITEWORD);
       PMBusStackObject_setNumOfBytes(handle, nBytes);
       #ifdef PEC_ENABLED
       CRCBuffer[0] = targetAddress << 1;
       PMBusStackObject_setCRCMsgSize(handle, 1U);
       #endif
       (void)handle-> transactionHandle[PMBUS_TRANSACTION_WRITEWORD](handle);
       PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM);
       //I2C_clearInterruptStatus(base,I2C_INT_STOP_CONDITION);
       I2C_clearInterruptStatus(base,I2C_INT_RXFF);
    }
#endif
    // Call the handler for the Extended Write word transaction
    if(command == PMBUS_CMD_MFR_SPECIFIC_COMMAND && extcommand == PMBUS_CMD_VOUT_COMMAND)
    {
        // Call the handler for the Extended Write Byte transaction
          PMBusStackObject_setNextState(handle,PMBUS_STACK_STATE_EXTENDED_COMMAND);

          #ifdef PEC_ENABLED
          CRCBuffer[0] = targetAddress << 1;
          CRCBuffer[1] = command;
          CRCBuffer[2] = extcommand;
          CRCBuffer[3] = targetAddress << 1;        // store target address + R/W=1
          PMBusStackObject_setCRCMsgSize(handle, 4U);
          //read PEC byte
          nBytes += PMBus_over_I2C_getTargetData(base, &buffer[nBytes+1]);
          #endif

          //
          // Set the object's nBytes field
          // Set the pointer in the buffer to point to the next
          // available spot
          //
          PMBusStackObject_setCurrentPositionPointer(handle,
                                                     &buffer[nBytes]);

          //
          // Set the object's nBytes field
          //
          PMBusStackObject_setNumOfBytes(handle, nBytes);

          //
          // Set the object transaction type
          //
          PMBusStackObject_setTransactionType(handle,
                                              PMBUS_TRANSACTION_WRITEWORD);

         //
         // Call the handler for the WRITEBYTE transaction
         //
         (void)handle->
                      transactionHandle[PMBUS_TRANSACTION_WRITEWORD](handle);

         first_time = true;

         PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM);


    }
    else
    {
         // RXFFINT gets generated only when atleast 4 bytes are received from controller
        if(STOP_CONDITION_NOT_DETECTED)
        {
            currentPointer = PMBusStackObject_getCurrentPositionPointer(handle);
            PMBusStackObject_setCurrentPositionPointer(handle, &buffer[nBytes]);
            if (first_time==false)
             {
                //
                // Set the object's nBytes field
                //
                nBytes = PMBusStackObject_getNumOfBytes(handle);
                nBytes = PMBus_over_I2C_getTargetData(base, &buffer[nBytes]);
             }


            if(first_time)
            {
                 //
                // Set the object's nBytes field
                //
                PMBusStackObject_setNumOfBytes(handle, nBytes);
            }
            else
            {
                 //
                 // Set the object's nBytes field
                 //
                 PMBusStackObject_setNumOfBytes(handle, (nBytes +
                                                 PMBusStackObject_getNumOfBytes(handle)));
            }
            first_time = false;

              if(TARGET_RECEIVER)
              {
                  // Call the handler for the BLOCK WRITE transaction
                  PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_BLOCKWRITE);
                  (void)handle-> transactionHandle[PMBUS_TRANSACTION_BLOCKWRITE](handle);
              }
              PMBusStackObject_setCurrentState(handle,PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL);
              PMBusStackObject_setNextState(handle,PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL);
        }
        else
        {
            //When STOP condition is detected
            if(PMBusStackObject_getNextState(handle)!=PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM)
            {
                PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL);
            }
            else
            {

            }
        }
    }
    I2C_clearInterruptStatus(base,I2C_INT_RXFF);


}
#endif
//
// End of File
//
