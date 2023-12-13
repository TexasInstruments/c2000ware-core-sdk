//###########################################################################
//
// FILE:   pmbus_over_i2c_stack_handler_target_idle.c
//
// TITLE:  PMBUS_OVER_I2C_STACK_STATE_IDLE handler
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
PMBUS_STACK_FILENUM(3)

//*****************************************************************************
//
// PMBusStack_targetIdleStateHandler
// This function is the entry point of the target stack. PMBus will be in IDLE
// state before any transaction. Any transaction which is initiated will
// trigger an interrupt which will be handled by this function in the ISR.
//*****************************************************************************
void PMBusStack_targetIdleStateHandler(PMBus_StackHandle handle)
{
    //
    // Locals
    //
    uint32_t status = PMBusStackObject_getModuleStatus(handle);
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);
    uint16_t *CRCBuffer = PMBusStackObject_getCRCBufferPointer(handle);
    uint32_t base = PMBusStackObject_getModuleBase(handle);
    //bool PEC_validity = handle->PECValidity;
    uint16_t targetAddress;
    uint16_t nBytes = 0U;
    uint16_t command = 0;
    uint16_t extcommand = 0;
    uint16_t *currentPointer;
#ifdef TIMEOUT
    uint32_t timerBase;
#endif
    //
    // Set the current state to idle
    //
    PMBusStackObject_setCurrentState(handle, PMBUS_STACK_STATE_IDLE);

    //
    // Rewind the current pointer
    //
    PMBusStackObject_setCurrentPositionPointer(handle, buffer);

    //
    // Set the object transaction type
    //
    PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_NONE);

#ifdef TIMEOUT
    timerBase = PMBusStackObject_getTimerBase(handle);
    CPUTimer_startTimer(timerBase);
#endif

#ifdef PEC_ENABLED
    //
    // Get target address
    //
    targetAddress = PMBusStackObject_getTargetAddress(handle);

    //
    // reset CRC buffer size
    //
    PMBusStackObject_setCRCMsgSize(handle, 0U);
#endif
    //
    // Check if the unit is busy
    //
    if((status & I2C_STS_BUS_BUSY) == 0U)  //I2C - Busy flag
    {
        //
        // Neither I2C hardware nor firmware are stuck,
        //
        // The user must use the clock low timeout feature to
        // fire an interrupt off to the CPU, query the comms
        // stack object, take remedial measures and reset
        // the state machine prior to returning from the interrupt
        //
    }


#ifdef PEC_ENABLED
    //nBytes = PMBus_over_I2C_getTargetData(base, buffer) - PEC_validity;
    nBytes = PMBus_over_I2C_getTargetData(base, buffer);

#else
    nBytes = PMBus_over_I2C_getTargetData(base, buffer);
#endif

    if(nBytes >= 0x2U)
    {
        command = buffer[0];
        extcommand = buffer[1];
    }
    else
    {
        command= buffer[0];
    }
    if(TARGET_RECEIVER)
    {

#if PEC_ENABLED
        if(nBytes>1)
        {
            nBytes = nBytes - 1;
        }
#endif
        I2C_setConfig(base, I2C_TARGET_RECEIVE_MODE);

        //nBytes = PMBus_over_I2C_getTargetData(base, buffer) - PEC_validity;
        PMBusStackObject_setNumOfBytes(handle, nBytes);

        switch(nBytes)
        {
            case I2C_FIFO_RX0:
                PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_QUICKCOMMAND);
                (void)handle-> transactionHandle[PMBUS_TRANSACTION_QUICKCOMMAND](handle);
                break;


            case I2C_FIFO_RX1: // Call the handler for the SENDBYTE transaction

                 PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_SENDBYTE);
                 #ifdef PEC_ENABLED
                 CRCBuffer[0] = targetAddress << 1;
                 PMBusStackObject_setCRCMsgSize(handle, 1U);
                 #endif
                 (void)handle-> transactionHandle[PMBUS_TRANSACTION_SENDBYTE](handle);
                 break;

             case I2C_FIFO_RX2: // Call the handler for the WRITEBYTE transaction
                 PMBusStackObject_isCommandAndTransactionValid(command, PMBUS_TRANSACTION_WRITEBYTE);
                 PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_WRITEBYTE);
                 #ifdef PEC_ENABLED
                 CRCBuffer[0] = targetAddress << 1;
                 PMBusStackObject_setCRCMsgSize(handle, 1U);
                 #endif
                 (void)handle-> transactionHandle[PMBUS_TRANSACTION_WRITEBYTE](handle);
                 break;

             case I2C_FIFO_RX3:
                 // Call the handler for the Extended command Write byte transaction
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
                    CRCBuffer[3] = targetAddress << 1;        // store target address + R/W=1
                     PMBusStackObject_setCRCMsgSize(handle, 4U);
                    #endif
                     //
                     // Call the handler for the WRITEBYTE transaction
                     //
                     (void)handle->
                                 transactionHandle[PMBUS_TRANSACTION_WRITEBYTE](handle);

                 }
                 else
                 {
                     // Call the handler for the WRITEWORD transaction
                    PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_WRITEWORD);
                    #ifdef PEC_ENABLED
                    CRCBuffer[0] = targetAddress << 1;
                    PMBusStackObject_setCRCMsgSize(handle, 1U);
                    #endif
                    (void)handle-> transactionHandle[PMBUS_TRANSACTION_WRITEWORD](handle);
                 }
                 break;

             case I2C_FIFO_RX4:
                 // Call the handler for the Extended Write word transaction
                 if(command == PMBUS_CMD_MFR_SPECIFIC_COMMAND && extcommand == PMBUS_CMD_VOUT_COMMAND)
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


                 }
                 else
                 {
                     currentPointer = PMBusStackObject_getCurrentPositionPointer(handle);
                     PMBusStackObject_setCurrentPositionPointer(handle,
                                                                      &currentPointer[nBytes]);

                     //
                     // Set the object's nBytes field
                     //
                     PMBusStackObject_setNumOfBytes(handle, nBytes);


                     //
                     // Set the object transaction type
                     //
                     PMBusStackObject_setTransactionType(handle,
                                                            PMBUS_TRANSACTION_BLOCKWRPC);


                 }
                 break;

             default: // Unhandled exception
                 PMBUS_STACK_ASSERT(0);
                 break;
             }

             //
             // Set next state to IDLE
            //
            if(PMBusStackObject_getTransactionType(handle) == PMBUS_TRANSACTION_BLOCKWRPC)
            {
                PMBusStackObject_setNextState(handle,PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL);
                I2C_clearInterruptStatus(base,I2C_INT_RXFF);
            }
            else
            {
                PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_IDLE);
                I2C_clearInterruptStatus(base,I2C_INT_STOP_CONDITION);
                I2C_clearInterruptStatus(base,I2C_INT_RXFF);
#ifdef TIMEOUT
                CPUTimer_stopTimer(timerBase);
                CPUTimer_reloadTimerCounter(timerBase);
#endif
            }
        }

    if(TARGET_TRANSMITTER)
    {

        I2C_setConfig(base, I2C_TARGET_SEND_MODE);

        if(STOP_CONDITION_NOT_DETECTED)
        {
            switch(nBytes)
            {
              case I2C_FIFO_RXEMPTY:
                  //When you don't receive any command, it is Receive Byte transaction
                  PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_RECEIVEBYTE);
                  (void)handle-> transactionHandle[PMBUS_TRANSACTION_RECEIVEBYTE](handle);
                  #ifdef PEC_ENABLED
                  CRCBuffer[0] = targetAddress << 1;
                  PMBusStackObject_setCRCMsgSize(handle, 1U);
                  #endif
                  break;

              case I2C_FIFO_RX1:
                  if(PMBusStackObject_isCommandAndTransactionValid(command, PMBUS_TRANSACTION_READBYTE))
                  {
                     PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_READBYTE);
                     (void)handle-> transactionHandle[PMBUS_TRANSACTION_READBYTE](handle);
                     #ifdef PEC_ENABLED
                     CRCBuffer[0] = targetAddress << 1;
                     CRCBuffer[1] = command    ;
                     CRCBuffer[2] = (targetAddress << 1) + 1;        // store target address + R/W=1
                     PMBusStackObject_setCRCMsgSize(handle, 3U);
                     #endif
                  }
                  else if(PMBusStackObject_isCommandAndTransactionValid(command, PMBUS_TRANSACTION_READWORD))
                  {
                      PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_READWORD);
                      (void)handle-> transactionHandle[PMBUS_TRANSACTION_READWORD](handle);
                      #ifdef PEC_ENABLED
                      CRCBuffer[0] = targetAddress << 1;
                      CRCBuffer[1] = command;
                      CRCBuffer[2] = (targetAddress << 1) + 1;        // store target address + R/W=1
                      PMBusStackObject_setCRCMsgSize(handle, 3U);
                      #endif
                  }
                  else if(PMBusStackObject_isCommandAndTransactionValid(command, PMBUS_TRANSACTION_BLOCKREAD))
                  {
                      //
                      // Set the object transaction type
                      //
                      PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_BLOCKREAD);

                      //
                      // Call the handler for the READBLOCK transaction
                      //
                      (void)handle->transactionHandle[PMBUS_TRANSACTION_BLOCKREAD](handle);

                      I2C_disableInterrupt(base, I2C_INT_TX_DATA_RDY);
                      //
                      // Get the number of bytes to transfer, buffer pointer
                      //
                      nBytes = PMBusStackObject_getNumOfBytes(handle);

                     /*
                      if(nBytes <= 4U)
                      {
                          //
                          // Put the data to the PMBUS Transmit buffer, with PEC
                          //
                          PMBus_over_I2C_putData(base, buffer, nBytes);
                      }
                      else // nBytes > 4
                      {
                          //
                          // Put the data to the PMBUS Transmit buffer, without PEC
                          //
                          PMBus_over_I2C_putData(base, buffer, 4U);

                          //
                          // Update the current index into the buffer
                          //
                          PMBusStackObject_setCurrentPositionPointer(handle, &buffer[4U]);
                      }
                      */
                      //
                      // Proceed to the READ_BLOCK state
                      //
                     // PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_READ_BLOCK);
                      PMBus_over_I2C_putData(base, buffer, nBytes);
                      PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM);

                  }

                  break;

              case I2C_FIFO_RX2:
                  // Call the handler for the Extended Read byte transaction
                  if(command == PMBUS_CMD_MFR_SPECIFIC_COMMAND && extcommand == PMBUS_CMD_OPERATION)
                  {
                      //
                      // Set the current state to PMBUS_STACK_STATE_EXTENDED_COMMAND
                      //
                      PMBusStackObject_setCurrentState(handle, PMBUS_STACK_STATE_EXTENDED_COMMAND);
                      //if(PMBusStackObject_isCommandAndTransactionValid(command,
                      //           PMBUS_TRANSACTION_READBYTE))
                      //{
                          //
                          // Set the object transaction type
                          //
                          PMBusStackObject_setTransactionType(handle,
                                                              PMBUS_TRANSACTION_READBYTE);

                          //
                          // Call the handler for the READBYTE transaction
                          //
                          (void)handle->transactionHandle[PMBUS_TRANSACTION_READBYTE](handle);
                          #ifdef PEC_ENABLED
                          CRCBuffer[0] = targetAddress << 1;
                          CRCBuffer[1] = command;
                          CRCBuffer[2] = extcommand;
                          CRCBuffer[3] = (targetAddress << 1) + 1;        // store target address + R/W=1
                          PMBusStackObject_setCRCMsgSize(handle, 4U);
                          #endif
                  }
                  // Call the handler for the Extended Read word transaction
                  else if(command == PMBUS_CMD_MFR_SPECIFIC_COMMAND && extcommand == PMBUS_CMD_VOUT_COMMAND)
                  {
                      //
                      // Set the current state to PMBUS_STACK_STATE_EXTENDED_COMMAND
                      //
                      PMBusStackObject_setCurrentState(handle, PMBUS_STACK_STATE_EXTENDED_COMMAND);


                      //
                      // Set the object transaction type
                      //
                      PMBusStackObject_setTransactionType(handle,
                                                          PMBUS_TRANSACTION_READWORD);

                      //
                      // Call the handler for the READWORD transaction
                      //
                      (void)handle->transactionHandle[PMBUS_TRANSACTION_READWORD](handle);
                      #ifdef PEC_ENABLED
                      CRCBuffer[0] = targetAddress << 1;
                      CRCBuffer[1] = command;
                      CRCBuffer[2] = extcommand;
                      CRCBuffer[3] = (targetAddress << 1) + 1;        // store target address + R/W=1
                      PMBusStackObject_setCRCMsgSize(handle, 4U);
                      #endif
                  }
                  break;
              case I2C_FIFO_RX3:
                  //
                  // RD_BYTE_COUNT = 3, EOM = 0, DATA_READY = 1
                  //
                  // Set the pointer in the buffer to point to the next
                  // available spot
                  //
                  currentPointer = PMBusStackObject_getCurrentPositionPointer(handle);
                  PMBusStackObject_setCurrentPositionPointer(handle,
                                                             &currentPointer[nBytes]);

                  //
                  // Set the object's nBytes field
                  //
                  PMBusStackObject_setNumOfBytes(handle, nBytes);


                  //
                  // Set the object transaction type
                  //
                  PMBusStackObject_setTransactionType(handle,
                                                      PMBUS_TRANSACTION_BLOCKWRPC);


                  //
                  // Set the current state to
                  // PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL //Process call
                  //
                  PMBusStackObject_setCurrentState(handle, PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL);


                  #ifdef PEC_ENABLED
                  CRCBuffer[0] = targetAddress << 1;
                  CRCBuffer[1] = command;
                  CRCBuffer[2] = buffer[1];
                  CRCBuffer[3] = buffer[2];
                  CRCBuffer[3] = (targetAddress << 1) + 1;        // store target address + R/W=1
                  PMBusStackObject_setCRCMsgSize(handle, 4U);
                  #endif

                  //
                  // Call the handler for the READWORD transaction
                  //
                  (void)handle->transactionHandle[PMBUS_TRANSACTION_BLOCKWRPC](handle);
                  break;
              default:
                  // Unhandled exception
                  PMBUS_STACK_ASSERT(0);
                  break;
            }

        }
        else
        {
            switch(nBytes)
            {
                case I2C_FIFO_RX0:
                    PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_QUICKCOMMAND);
                    (void)handle-> transactionHandle[PMBUS_TRANSACTION_QUICKCOMMAND](handle);
                    break;

                default:
                    // Unhandled exception
                    PMBUS_STACK_ASSERT(0);
                    break;
            }
        }

        if(PMBusStackObject_getTransactionType(handle) != PMBUS_TRANSACTION_BLOCKREAD)
        {
            PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM);

            I2C_disableInterrupt(base, I2C_INT_TX_DATA_RDY);

            //
            // Get the number of bytes to transfer, buffer pointer
            //
            nBytes = PMBusStackObject_getNumOfBytes(handle);

#ifdef PEC_ENABLED
            buffer[nBytes]  = calc_PEC(CRCBuffer, PMBusStackObject_getCRCBufferSize(handle), buffer[1], nBytes);
            //
            // Put the data to the PMBUS Transmit buffer + PEC.
            //
            PMBus_over_I2C_putData(base, buffer, nBytes+1);
#else
            PMBus_over_I2C_putData(base, buffer, nBytes);
#endif
        }
    }
}

#endif
//
// End of File
//
