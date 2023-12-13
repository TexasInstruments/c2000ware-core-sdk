//###########################################################################
//
// FILE:   pmbus_over_i2c_stack_config.h
//
// TITLE:  PMBUS over I2C Communications Stack Configuration File
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

#ifndef PMBUS_OVER_I2C_STACK_CONFIG_H
#define PMBUS_OVER_I2C_STACK_CONFIG_H

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
//!
//! \defgroup PMBUS_OVER_I2C_STACK_CONFIG PMBus over I2C Configuration
//
//!
//! \ingroup PMBUS_OVER_I2C_STACK_CONFIG
// @{
//
//*****************************************************************************

//
// Includes
//
#include "pmbus_stack_assert.h"
#include "i2c.h"
#include "pmbus_common.h"

//
// Defines
//
#define NTRANSACTIONS            11U
#define BASE_ADDRESS_MASK        0x7FU
#define COMMAND_MASK             0x3U
#define TRANSACTION_NIBBLE_MASK  0x0FU

#ifdef PEC_ENABLED
extern uint16_t PMBusTarget_CrcMsgSize;
extern uint16_t PMBusTarget_CrcMsg[5];
extern uint16_t PMBusTarget_CrcControllerGenerated;
extern uint16_t PMBusTarget_CrcTargetGenerated;
#endif
//
// Typedefs
//

//! Function pointer to the routine to handle a transaction
typedef void (*transactionHandler)(void *handle);

//*****************************************************************************
//
//! PMBus Mode of Operation
//
//*****************************************************************************
typedef enum
{
    PMBUS_STACK_MODE_TARGET  = 0,      //!< PMBus operates in target mode
    PMBUS_STACK_MODE_CONTROLLER = 1,      //!< PMBus operates in controller mode
} PMBus_StackMode;

//*****************************************************************************
//
//! Enumeration of the states in the PMBus state machine
//
//*****************************************************************************
typedef enum
{
    //! PMBus in the Idle state
    PMBUS_STACK_STATE_IDLE                        = 0U,
    //! PMBus is waiting on an end-of-message signal (NACK on last data)
    PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM   = 1U,
    //! PMBus is reading a block of data
    PMBUS_STACK_STATE_READ_BLOCK                  = 2U,
    //! PMBus is waiting on an end-of-message signal (NACK on last data)
    PMBUS_STACK_STATE_READ_WAIT_FOR_EOM           = 3U,
    //! PMBus is either writing a block or issuing a process call
    PMBUS_STACK_STATE_BLOCK_WRITE_OR_PROCESS_CALL = 5U,
    //! PMBus is doing an extended read/write byte/word
    PMBUS_STACK_STATE_EXTENDED_COMMAND            = 6U,
} PMBus_StackState;

//*****************************************************************************
//
//! PMBUS Target Mode Object
//
//*****************************************************************************
typedef struct
{
    uint32_t moduleBase;            //!< Base address of the PMBus module
    uint32_t moduleStatus;          //!< Status register of the PMBus module
    PMBus_StackMode mode;           //!< PMBus mode of operation
    uint16_t targetAddress;          //!< Target address for the PMBus module
    uint16_t targetAddressMask;      //!< Target address mask for PMBus module
    PMBus_StackState currentState;  //!< Current state of the state machine
    PMBus_StackState nextState;     //!< next state of the state machine
    uint16_t *bufferPointer;        //!< pointer to a buffer of length >= 4
    uint16_t *currentBufferPointer; //!< Current position in the buffer
    uint16_t numOfBytes;            //!< Number of bytes sent/received
    bool PECValidity;               //!< Valid PEC received or sent
    PMBus_Transaction transaction;  //!< Current Transaction type
    uint16_t *CRCBufferPointer;     //!< Pointer to CRC Buffer
    uint16_t CRCBufferSize ;        //!< CRC Buffer Size
    uint32_t timerBase;             //!< Indicates which CPU Timer base for timeout feature (PMBus over I2c)
    uint32_t timeout;               //!< Indicates the timeout value (PMBus over I2c)

    //! Handler for each transaction
    transactionHandler transactionHandle[NTRANSACTIONS];
} PMBus_StackObject;

//*****************************************************************************
//
//! Structure that packs 4 transaction fields into a word
//
//*****************************************************************************
typedef struct
{
    uint16_t transaction0 : 4;    //!< First Transaction field
    uint16_t transaction1 : 4;    //!< Second Transaction field
    uint16_t transaction2 : 4;    //!< Third Transaction field
    uint16_t transaction3 : 4;    //!< Fourth Transaction field
} PMBus_TransactionObject;

//*****************************************************************************
//
//! Union of the packed transactions struct and an unsigned word
//
//*****************************************************************************
typedef union
{
    PMBus_TransactionObject object;
    uint16_t transactionField;
} PMBus_TransactionObjectUnion;

//! Handle to the PMBus_Stack_Obj object
typedef PMBus_StackObject *PMBus_StackHandle;

//
// Globals
//

//! PMBus Target Object
extern PMBus_StackObject pmbusStackTarget;

//! Handle to the target object
extern PMBus_StackHandle pmbusStackTargetHandle;

//*****************************************************************************
//
//! PMBus Command Transaction Type Map
//!
//! Each position in the map corresponds to a particular command, its
//! entry lists the type of read transaction that is involved. It will
//! used to distinguish between read byte, read word, and block read
//! commands in the state machine
//!
//! Any command that has both a write and read command will have the
//! read transaction type as its entry. A command without a read command
//! will have its write transaction type as its entry
//
//*****************************************************************************
static const PMBus_TransactionObjectUnion PMBusStack_commandTransactionMap[64] =
{
 {
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_PAGE                       (0x00U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_OPERATION                  (0x01U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_ON_OFF_CONFIG              (0x02U)
  PMBUS_TRANSACTION_SENDBYTE   ,// PMBUS_CMD_CLEAR_FAULTS               (0x03U)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_PHASE                      (0x04U)
  PMBUS_TRANSACTION_BLOCKWRITE ,// PMBUS_CMD_PAGE_PLUS_WRITE            (0x05U)
  PMBUS_TRANSACTION_BLOCKWRPC  ,// PMBUS_CMD_PAGE_PLUS_READ             (0x06U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x07U)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x08U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x09U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x0AU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x0BU)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x0CU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x0DU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x0EU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x0FU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_WRITE_PROTECT              (0x10U)
  PMBUS_TRANSACTION_SENDBYTE   ,// PMBUS_CMD_STORE_DEFAULT_ALL          (0x11U)
  PMBUS_TRANSACTION_SENDBYTE   ,// PMBUS_CMD_RESTORE_DEFAULT_ALL        (0x12U)
  PMBUS_TRANSACTION_WRITEBYTE  ,// PMBUS_CMD_STORE_DEFAULT_CODE         (0x13U)
 },{
  PMBUS_TRANSACTION_WRITEBYTE  ,// PMBUS_CMD_RESTORE_DEFAULT_CODE       (0x14U)
  PMBUS_TRANSACTION_SENDBYTE   ,// PMBUS_CMD_STORE_USER_ALL             (0x15U)
  PMBUS_TRANSACTION_SENDBYTE   ,// PMBUS_CMD_RESTORE_USER_ALL           (0x16U)
  PMBUS_TRANSACTION_WRITEBYTE  ,// PMBUS_CMD_STORE_USER_CODE            (0x17U)
 },{
  PMBUS_TRANSACTION_WRITEBYTE  ,// PMBUS_CMD_RESTORE_USER_CODE          (0x18U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_CAPABILITY                 (0x19U)
  PMBUS_TRANSACTION_BLOCKWRPC  ,// PMBUS_CMD_QUERY                      (0x1AU)
  PMBUS_TRANSACTION_BLOCKWRPC  ,// PMBUS_CMD_SMBALERT_MASK              (0x1BU)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x1CU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x1DU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x1EU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x1FU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_VOUT_MODE                  (0x20U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_COMMAND               (0x21U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_TRIM                  (0x22U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_CAL_OFFSET            (0x23U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_MAX                   (0x24U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_MARGIN_HIGH           (0x25U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_MARGIN_LOW            (0x26U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_TRANSITION_RATE       (0x27U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_DROOP                 (0x28U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_SCALE_LOOP            (0x29U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_SCALE_MONITOR         (0x2AU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x2BU)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x2CU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x2DU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x2EU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x2FU)
 },{
  PMBUS_TRANSACTION_BLOCKWRPC  ,// PMBUS_CMD_COEFFICIENTS               (0x30U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_POUT_MAX                   (0x31U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MAX_DUTY                   (0x32U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_FREQUENCY_SWITCH           (0x33U)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x34U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VIN_ON                     (0x35U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VIN_OFF                    (0x36U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_INTERLEAVE                 (0x37U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IOUT_CAL_GAIN              (0x38U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IOUT_CAL_OFFSET            (0x39U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_FAN_CONFIG_1_2             (0x3AU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_FAN_COMMAND_1              (0x3BU)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_FAN_COMMAND_2              (0x3CU)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_FAN_CONFIG_3_4             (0x3DU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_FAN_COMMAND_3              (0x3EU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_FAN_COMMAND_4              (0x3FU)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_OV_FAULT_LIMIT        (0x40U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_VOUT_OV_FAULT_RESPONSE     (0x41U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_OV_WARN_LIMIT         (0x42U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_UV_WARN_LIMIT         (0x43U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VOUT_UV_FAULT_LIMIT        (0x44U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_VOUT_UV_FAULT_RESPONSE     (0x45U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IOUT_OC_FAULT_LIMIT        (0x46U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_IOUT_OC_FAULT_RESPONSE     (0x47U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IOUT_OC_LV_FAULT_LIMIT     (0x48U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_IOUT_OC_LV_FAULT_RESPONSE  (0x49U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IOUT_OC_WARN_LIMIT         (0x4AU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IOUT_UC_FAULT_LIMIT        (0x4BU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_IOUT_UC_FAULT_RESPONSE     (0x4CU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x4DU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x4EU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_OT_FAULT_LIMIT             (0x4FU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_OT_FAULT_RESPONSE          (0x50U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_OT_WARN_LIMIT              (0x51U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_UT_WARN_LIMIT              (0x52U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_UT_FAULT_LIMIT             (0x53U)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_UT_FAULT_RESPONSE          (0x54U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VIN_OV_FAULT_LIMIT         (0x55U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_VIN_OV_FAULT_RESPONSE      (0x56U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VIN_OV_WARN_LIMIT          (0x57U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VIN_UV_WARN_LIMIT          (0x58U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_VIN_UV_FAULT_LIMIT         (0x59U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_VIN_UV_FAULT_RESPONSE      (0x5AU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IIN_OC_FAULT_LIMIT         (0x5BU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_IIN_OC_FAULT_RESPONSE      (0x5CU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_IIN_OC_WARN_LIMIT          (0x5DU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_POWER_GOOD_ON              (0x5EU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_POWER_GOOD_OFF             (0x5FU)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_TON_DELAY                  (0x60U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_TON_RISE                   (0x61U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_TON_MAX_FAULT_LIMIT        (0x62U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_TON_MAX_FAULT_RESPONSE     (0x63U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_TOFF_DELAY                 (0x64U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_TOFF_FALL                  (0x65U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_TOFF_MAX_WARN_LIMIT        (0x66U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x67U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_POUT_OP_FAULT_LIMIT        (0x68U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_POUT_OP_FAULT_RESPONSE     (0x69U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_POUT_OP_WARN_LIMIT         (0x6AU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_PIN_OP_WARN_LIMIT          (0x6BU)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x6CU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x6DU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x6EU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x6FU)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x70U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x71U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x72U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x73U)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x74U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x75U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x76U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x77U)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_BYTE                (0x78U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_STATUS_WORD                (0x79U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_VOUT                (0x7AU)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_IOUT                (0x7BU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_INPUT               (0x7CU)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_TEMPERATURE         (0x7DU)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_CML                 (0x7EU)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_OTHER               (0x7FU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_MFR_SPECIFIC        (0x80U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_FANS_1_2            (0x81U)
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_STATUS_FANS_3_4            (0x82U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x83U)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x84U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0x85U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_READ_EIN                   (0x86U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_READ_EOUT                  (0x87U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_VIN                   (0x88U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_IIN                   (0x89U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_VCAP                  (0x8AU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_VOUT                  (0x8BU)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_IOUT                  (0x8CU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_TEMPERATURE_1         (0x8DU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_TEMPERATURE_2         (0x8EU)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_TEMPERATURE_3         (0x8FU)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_FAN_SPEED_1           (0x90U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_FAN_SPEED_2           (0x91U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_FAN_SPEED_3           (0x92U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_FAN_SPEED_4           (0x93U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_DUTY_CYCLE            (0x94U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_FREQUENCY             (0x95U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_POUT                  (0x96U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_READ_PIN                   (0x97U)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_PMBUS_REVISION             (0x98U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_ID                     (0x99U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_MODEL                  (0x9AU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_REVISION               (0x9BU)
 },{
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_LOCATION               (0x9CU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_DATE                   (0x9DU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_SERIAL                 (0x9EU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD APP_PROFILE_SUPPORT        (0x9FU)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_VIN_MIN                (0xA0U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_VIN_MAX                (0xA1U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_IIN_MAX                (0xA2U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_PIN_MAX                (0xA3U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_VOUT_MIN               (0xA4U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_VOUT_MAX               (0xA5U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_IOUT_MAX               (0xA6U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_POUT_MAX               (0xA7U)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_TAMBIENT_MAX           (0xA8U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_TAMBIENT_MIN           (0xA9U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_EFFICIENCY_LL          (0xAAU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_EFFICIENCY_HL          (0xABU)
 },{
  PMBUS_TRANSACTION_READBYTE   ,// PMBUS_CMD_MFR_PIN_ACURRACY           (0xACU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_IC_DEVICE              (0xADU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_MFR_IC_DEVICE_REV          (0xAEU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xAFU)
 },{
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_00               (0xB0U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_01               (0xB1U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_02               (0xB2U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_03               (0xB3U)
 },{
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_04               (0xB4U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_05               (0xB5U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_06               (0xB6U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_07               (0xB7U)
 },{
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_08               (0xB8U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_09               (0xB9U)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_10               (0xBAU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_11               (0xBBU)
 },{
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_12               (0xBCU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_13               (0xBDU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_14               (0xBEU)
  PMBUS_TRANSACTION_BLOCKREAD  ,// PMBUS_CMD_USER_DATA_15               (0xBFU)
 },{
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_MAX_TEMP_1             (0xC0U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_MAX_TEMP_2             (0xC1U)
  PMBUS_TRANSACTION_READWORD   ,// PMBUS_CMD_MFR_MAX_TEMP_3             (0xC2U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xC3U)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xC4U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xC5U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xC6U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xC7U)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xC8U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xC9U)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xCAU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xCBU)
 },{
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xCCU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xCDU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xCEU)
  PMBUS_TRANSACTION_NONE       ,// Reserved                             (0xCFU)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_LIGHT_LOAD_ENB         (0xD0U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_01            (0xD1U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_02            (0xD2U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_03            (0xD3U)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_04            (0xD4U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_05            (0xD5U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_06            (0xD6U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_07            (0xD7U)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_08            (0xD8U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_ROM_MODE                   (0xD9U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_USER_RAM_00                (0xDAU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_PHASE_CONTROL          (0xDBU)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_IOUT_OC_FAULT_LIMIT_LOW(0xDCU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_VIN_SCALE              (0xDDU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_VIN_OFFSET             (0xDEU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_READ_TEMPERATURE_4     (0xDFU)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_OT_LIMIT_1             (0xE0U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_OT_LIMIT_2             (0xE1U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_PARM_INFO              (0xE2U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_PARM_VALUE             (0xE3U)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_CMDS_DCDC_PAGED        (0xE4U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_CMDS_DCDC_NONPAGED     (0xE5U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_CMDS_PFC               (0xE6U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SETUP_ID               (0xE7U)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_OT_LIMIT_3             (0xE8U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_OT_LIMIT_4             (0xE9U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_DEADBAND_CONFIG        (0xEAU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_PIN_CAL_A              (0xEBU)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_PIN_CAL_B              (0xECU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_PIN_CAL_C              (0xEDU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_PIN_CAL_D              (0xEEU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_TEMP_CAL_OFFSET        (0xEFU)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_DEBUG_BUFFER           (0xF0U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_TEMP_CAL_GAIN          (0xF1U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_STATUS_BIT_MASK        (0xF2U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_35            (0xF3U)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_36            (0xF4U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_37            (0xF5U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_38            (0xF6U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_39            (0xF7U)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_VOUT_CAL_MONITOR       (0xF8U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_ROM_MODE_WITH_PASSWORD     (0xF9U)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_42            (0xFAU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_43            (0xFBU)
 },{
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_44            (0xFCU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_DEVICE_ID              (0xFDU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_MFR_SPECIFIC_COMMAND       (0xFEU)
  PMBUS_TRANSACTION_NONE       ,// PMBUS_CMD_PMBUS_COMMAND_EXT          (0xFFU)
 }
};


//*****************************************************************************
//
//! Initialize the PMBus Module
//!
//! \param handle is the handle to the PMBus stack object
//! \param moduleBase is the base address for the PMBus peripheral instance
//! \param buffer is the buffer pointer for use by the PMBus stack object
//!
//! This function initializes the PMBus peripheral (based on mode set in the
//! PMBus stack object) for target or controller mode, assigns the buffer pointer to
//! the PMBus stack object, and enables interrupts.
//!
//! \note This function enables the I2C interrupts but the user must register
//!       the necessary interrupt service routine handler and configure the ISR
//!       to call the required library handler
//! \note The buffer must point to an array of at least 4 words
//!
//! \return Returns \b true if initialization is successful and \b false when
//!         initialization isn't successful.
//
//*****************************************************************************
extern bool
PMBusStack_initModule(PMBus_StackHandle handle, const uint32_t moduleBase,
                           uint16_t *buffer, uint16_t *CRCBuffer);

//*****************************************************************************
//
//! Default Transaction Handler
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function is the default transaction handler. Default behavior is
//! to call PMBusStack_assertionFailed().
//!
//! \return If function returns, always returns value of -1.
//
//*****************************************************************************
extern int32_t
PMBusStack_defaultTransactionHandler(PMBus_StackHandle handle);

//*****************************************************************************
//
//! Set PMBus Module Base Address
//!
//! \param handle is the handle to the PMBus stack object
//! \param address is the base address for the PMBus peripheral instance
//!
//! This function sets the PMBus module instance base address in the PMBus
//! stack object.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusStackObject_setModuleBase(PMBus_StackHandle handle,
                               const uint32_t address)
{
    handle->moduleBase = address;
}

//*****************************************************************************
//
//! Get PMBus Module Base Address
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function gets the PMBus module instance base address from the
//! PMBus stack object.
//!
//! \return PMBus module instance base address
//
//*****************************************************************************
static inline uint32_t
PMBusStackObject_getModuleBase(PMBus_StackHandle handle)
{
    return(handle->moduleBase);
}

//*****************************************************************************
//
//! Set PMBus Module Status
//!
//! \param handle is the handle to the PMBus stack object
//! \param status is the PMBus module instance register status
//!
//! This function sets the PMBus module instance register status in the
//! PMBus stack object.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusStackObject_setModuleStatus(PMBus_StackHandle handle,
                                 const uint32_t status)
{
    handle->moduleStatus = status;
}

//*****************************************************************************
//
//! Get PMBus Module Status
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function gets the PMBus module instance status value from the
//! PMBus stack object.
//!
//! \return Module status
//
//*****************************************************************************
static inline uint32_t
PMBusStackObject_getModuleStatus(PMBus_StackHandle handle)
{
    return(handle->moduleStatus);
}

//*****************************************************************************
//
//! Set PMBus Module Mode
//!
//! \param handle is the handle to the PMBus stack object
//! \param mode is the PMBus module mode (either target or controller)
//!
//! This function sets the PMBus module instance operating mode
//! (controller or target) in the PMBus stack object.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusStackObject_setMode(PMBus_StackHandle handle,
                         const PMBus_StackMode mode)
{
    handle->mode = mode;
}

//*****************************************************************************
//
//! Get PMBus Module Mode
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function gets the PMBus module instance operating mode from the
//! PMBus stack object.
//!
//! \return PMBUS_STACK_MODE_TARGET or PMBUS_STACK_MODE_CONTROLLER
//
//*****************************************************************************
static inline PMBus_StackMode
PMBusStackObject_getMode(PMBus_StackHandle handle)
{
    return(handle->mode);
}

//*****************************************************************************
//
//! Set PMBus Module Target Address
//!
//! \param handle is the handle to the PMBus stack object
//! \param address is the address of the PMBus module in target mode
//!
//! This function sets the PMBus module instance target address in the
//! PMBus stack object.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusStackObject_setTargetAddress(PMBus_StackHandle handle,
                                 const uint16_t address)
{
    handle->targetAddress = address;
}

//*****************************************************************************
//
//! Get PMBus Module Target Address
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This functions gets the PMBus module instance target address from the
//! PMBus stack object
//!
//! \return Target address
//
//*****************************************************************************
static inline uint16_t
PMBusStackObject_getTargetAddress(PMBus_StackHandle handle)
{
    return(handle->targetAddress);
}

//*****************************************************************************
//
//! Set PMBus Module Target Address Mask
//!
//! \param handle is the handle to the PMBus stack object
//! \param addressMask is the address mask of the PMBus module in target mode
//!
//! This function sets the PMBus module instance target address mask in the
//! PMBus stack object.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusStackObject_setTargetAddressMask(PMBus_StackHandle handle,
                                     const uint16_t addressMask)
{
    handle->targetAddressMask = addressMask;
}

//*****************************************************************************
//
//! Get PMBus Module Target Address Mask
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function gets the PMBus module instance target address mask from the
//! PMBus stack object.
//!
//! \return Target address mask
//
//*****************************************************************************
static inline uint16_t
PMBusStackObject_getTargetAddressMask(PMBus_StackHandle handle)
{
    return(handle->targetAddressMask);
}

//*****************************************************************************
//
//! Set PMBus Module Current State
//!
//! \param handle is the handle to the PMBus stack object
//! \param state is the current state of the PMBus state machine
//!
//! This function sets the PMBus module current state of the state machine in
//! the PMBus stack object.
//! States include:
//! - PMBUS_STACK_STATE_IDLE : Idle State
//! - PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM : Waiting on end-of-message
//!                                                 signal state
//! - PMBUS_STACK_STATE_READ_WAIT_FOR_EOM : Waiting on end-of-message signal
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusStackObject_setCurrentState(PMBus_StackHandle handle,
                                 const PMBus_StackState state)
{
    handle->currentState = state;
}

//*****************************************************************************
//
//! Get PMBus Module Current State
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function gets the PMBus module current state of the state machine from
//! the PMBus stack object.
//!
//! \return Current State
//! - PMBUS_STACK_STATE_IDLE : Idle State
//! - PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM : Waiting on end-of-message
//!                                                 signal state
//! - PMBUS_STACK_STATE_READ_WAIT_FOR_EOM : Waiting on end-of-message signal
//!
//
//*****************************************************************************
static inline PMBus_StackState
PMBusStackObject_getCurrentState(PMBus_StackHandle handle)
{
    return(handle->currentState);
}

//*****************************************************************************
//
//! Set PMBus Module Next State
//!
//! \param handle is the handle to the PMBus stack object
//! \param state is the next state of the PMBus state machine
//!
//! This function sets the PMBus module next state of the state machine in the
//! PMBus stack object.
//! States include:
//! - PMBUS_STACK_STATE_IDLE : Idle State
//! - PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM : Waiting on end-of-message
//!                                                 signal state
//! - PMBUS_STACK_STATE_READ_WAIT_FOR_EOM : Waiting on end-of-message signal
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusStackObject_setNextState(PMBus_StackHandle handle,
                              const PMBus_StackState state)
{
    handle->nextState = state;
}

//*****************************************************************************
//
//! Get PMBus Module Next State
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function gets the PMBus module next state of the state machine from
//! the PMBus stack object.
//!
//! \return Next State
//! - PMBUS_STACK_STATE_IDLE : Idle State
//! - PMBUS_STACK_STATE_RECEIVE_BYTE_WAIT_FOR_EOM : Waiting on end-of-message
//!                                                 signal state
//! - PMBUS_STACK_STATE_READ_WAIT_FOR_EOM : Waiting on end-of-message signal
//!
//
//*****************************************************************************
static inline PMBus_StackState
PMBusStackObject_getNextState(PMBus_StackHandle handle)
{
    return(handle->nextState);
}

//*****************************************************************************
//
//! Set PMBus Module Buffer Pointer
//!
//! \param handle is the handle to the PMBus stack object
//! \param buffer is the pointer to the buffer (must be buffer of size >= 4)
//!
//! This function sets the PMBus module pointer to the buffer that stores
//! messages in the PMBus stack object.
//!
//! \return None.
//!
//
//*****************************************************************************
static inline void
PMBusStackObject_setBufferPointer(PMBus_StackHandle handle,
                                  uint16_t *buffer)
{
    handle->bufferPointer = buffer;
}

//*****************************************************************************
//
//! Set PMBus Module CRC Buffer Pointer
//!
//! \param handle is the handle to the PMBus stack object
//! \param buffer is the pointer to the CRC buffer
//!
//! This function sets the PMBus module CRC Buffer pointer to the CRC buffer that
//! stores data for calculation of PEC in the PMBus stack object.
//!
//! \return None.
//!
//
//*****************************************************************************
static inline void
PMBusStackObject_setCRCBufferPointer(PMBus_StackHandle handle,
                                  uint16_t *CRCbuffer)
{
    handle->CRCBufferPointer = CRCbuffer;
}

//*****************************************************************************
//
//! Set PMBus over I2C Module Timer Base Address
//!
//! \param handle is the handle to the PMBus stack object
//! \param timerBase is the base address for the CPU Timer used by PMBus over I2C
//!
//! This function sets the PMBus module instance timer base address in the PMBus
//! stack object.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusStackObject_setTimerBase(PMBus_StackHandle handle,
                                  uint32_t timerBase)
{
    handle->timerBase = timerBase;
}

//*****************************************************************************
//
//! Set PMBus over I2C Module Timeout Value
//!
//! \param handle is the handle to the PMBus stack object
//! \param timeout is the timeout value  (in uSeconds) configured in CPU Timer
//! used by PMBus over I2C
//!
//! This function sets the PMBus module instance timeout value in the PMBus
//! stack object.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusStackObject_setTimeout(PMBus_StackHandle handle,
                                  uint32_t timeout)
{
    handle->timeout = timeout;
}

//*****************************************************************************
//
//! Get PMBus Module Buffer Pointer
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function gets the PMBus module pointer to the buffer that stores
//! messages from the PMBus stack object.
//!
//! \return Buffer pointer
//
//*****************************************************************************
static inline uint16_t*
PMBusStackObject_getBufferPointer(PMBus_StackHandle handle)
{
    return(handle->bufferPointer);
}

//*****************************************************************************
//
//! Get PMBus Module CRC Buffer Pointer
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function gets the PMBus module pointer to the CRC buffer that stores
//! data for calculation of PEC.
//!
//! \return CRC Buffer pointer
//
//*****************************************************************************
static inline uint16_t*
PMBusStackObject_getCRCBufferPointer(PMBus_StackHandle handle)
{
    return(handle->CRCBufferPointer);
}

//*****************************************************************************
//
//! Get PMBus over I2C Module Timer Base
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function gets the address of the timer used by PMBus over I2C
//!
//!
//! \return Base address of the timer
//
//*****************************************************************************
static inline uint32_t
PMBusStackObject_getTimerBase(PMBus_StackHandle handle)
{
    return(handle->timerBase);
}

//*****************************************************************************
//
//! Get PMBus over I2C Module Timeout Value
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function gets the timeout value (in uSeconds) configured during
//! PMBus over I2C module operation
//!
//! \return Buffer pointer
//
//*****************************************************************************
static inline uint32_t
PMBusStackObject_getTimeout(PMBus_StackHandle handle)
{
    return(handle->timeout);
}
//*****************************************************************************
//
//! Set PMBus Module Current Buffer Position Pointer
//!
//! \param handle is the handle to the PMBus stack object
//! \param currentPointer is the pointer to the current position in the buffer
//!
//! This function sets the PMBus module pointer to the current position in the
//! buffer in the PMBus stack object.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusStackObject_setCurrentPositionPointer(PMBus_StackHandle handle,
                                           uint16_t *currentPointer)
{
    handle->currentBufferPointer = currentPointer;
}

//*****************************************************************************
//
//! Get PMBus Module Current Buffer Position Pointer
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function gets the PMBus module pointer to the current position in the
//! buffer from the PMBus stack object.
//!
//! \return Current buffer pointer.
//
//*****************************************************************************
static inline uint16_t*
PMBusStackObject_getCurrentPositionPointer(PMBus_StackHandle handle)
{
    return(handle->currentBufferPointer);
}

//*****************************************************************************
//
//! Set PMBus Module Number of Bytes
//!
//! \param handle is the handle to the PMBus stack object
//! \param numberOfBytes is the number of bytes sent/received
//!
//! This function sets the PMBus module number of bytes being sent or received
//! in the PMBus stack object.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusStackObject_setNumOfBytes(PMBus_StackHandle handle,
                               const uint16_t numberOfBytes)
{
    handle->numOfBytes = numberOfBytes;
}

//*****************************************************************************
//
//! Set PMBus Module CRC Message Size
//!
//! \param handle is the handle to the PMBus stack object
//! \param nBytes is the number of bytes in the CRC buffer
//!
//! This function sets the PMBus CRC Message size (in Bytes) that stores
//! the bytes used in the PEC calculation.
//!
//! \return None
//
//*****************************************************************************
static inline void
PMBusStackObject_setCRCMsgSize(PMBus_StackHandle handle,
                               const uint16_t nBytes)
{
    handle->CRCBufferSize = nBytes;
}
//*****************************************************************************
//
//! Get PMBus Module Number of Bytes
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function gets the PMBus module number of bytes being sent or received
//! from the PMBus stack object.
//!
//! \return Number of bytes
//
//*****************************************************************************
static inline uint16_t
PMBusStackObject_getNumOfBytes(PMBus_StackHandle handle)
{
    return(handle->numOfBytes);
}

//*****************************************************************************
//
//! Get PMBus Module CRC Buffer Size
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function gets the PMBus module CRC message size that stores
//! the bytes used in the PEC calculation.
//!
//! \return CRC Buffer size in bytes
//
//*****************************************************************************
static inline uint16_t
PMBusStackObject_getCRCBufferSize(PMBus_StackHandle handle)
{
    return(handle->CRCBufferSize);
}

//*****************************************************************************
//
//! Set PMBus Module Packet Error Checking (PEC) Validity
//!
//! \param handle is the handle to the PMBus stack object
//! \param validity is the PEC validity status (true = PEC is valid,
//!                                             false = PEC is invalid)
//!
//! This function sets the PMBus module PEC validity status (either valid or
//! invalid) in the PMBus stack object.
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusStackObject_setPECValidity(PMBus_StackHandle handle, const bool validity)
{
    handle->PECValidity = validity;
}

//*****************************************************************************
//
//! Get PMBus Module Packet Error Checking (PEC) Validity
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function gets the PMBus module PEC validity status (either valid or
//! invalid) from the PMBus stack object.
//!
//! \return Returns \b true if PEC is valid and \b false if PEC is invalid
//
//*****************************************************************************
static inline bool
PMBusStackObject_isPECValid(PMBus_StackHandle handle)
{
    return(handle->PECValidity);
}

//*****************************************************************************
//
//! Set PMBus Module Transaction Type
//!
//! \param handle is the handle to the PMBus stack object
//! \param transaction is the PMBus transaction type
//!
//! This function sets the PMBus module transaction type in the PMBus stack
//! object.
//! Transactions include:
//! - PMBUS_TRANSACTION_NONE
//! - PMBUS_TRANSACTION_WRITEBYTE
//! - PMBUS_TRANSACTION_READBYTE
//! - PMBUS_TRANSACTION_SENDBYTE
//! - PMBUS_TRANSACTION_RECEIVEBYTE
//! - PMBUS_TRANSACTION_WRITEWORD
//! - PMBUS_TRANSACTION_READWORD
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusStackObject_setTransactionType(PMBus_StackHandle handle,
                                    const PMBus_Transaction transaction)
{
    handle->transaction = transaction;
}

//*****************************************************************************
//
//! Get PMBus Module Transaction Type
//!
//! \param handle is the handle to the PMBus stack object
//!
//! This function gets the PMBus module transaction type from the PMBus
//! stack object.
//!
//! \return Transaction type
//! - PMBUS_TRANSACTION_NONE
//! - PMBUS_TRANSACTION_WRITEBYTE
//! - PMBUS_TRANSACTION_READBYTE
//! - PMBUS_TRANSACTION_SENDBYTE
//! - PMBUS_TRANSACTION_RECEIVEBYTE
//! - PMBUS_TRANSACTION_WRITEWORD
//! - PMBUS_TRANSACTION_READWORD
//
//*****************************************************************************
static inline PMBus_Transaction
PMBusStackObject_getTransactionType(PMBus_StackHandle handle)
{
    return(handle->transaction);
}

//*****************************************************************************
//
//! Set PMBus Module Transaction Handler
//!
//! \param handle is the handle to the PMBus stack object
//! \param transaction is the PMBus transaction type
//! \param handler is the pointer to the function to handle the transaction
//!
//! This function sets the PMBus module transaction handler function for a
//! specific transaction type in the PMBus stack object.
//! Transactions include:
//! - PMBUS_TRANSACTION_NONE
//! - PMBUS_TRANSACTION_WRITEBYTE
//! - PMBUS_TRANSACTION_READBYTE
//! - PMBUS_TRANSACTION_SENDBYTE
//! - PMBUS_TRANSACTION_RECEIVEBYTE
//! - PMBUS_TRANSACTION_WRITEWORD
//! - PMBUS_TRANSACTION_READWORD
//!
//! \return None.
//
//*****************************************************************************
static inline void
PMBusStackObject_setTransactionHandler(PMBus_StackHandle handle,
                                       const PMBus_Transaction transaction,
                                       transactionHandler handler)
{
    handle->transactionHandle[transaction] = handler;
}

//*****************************************************************************
//
//! Get PMBus Module Transaction Handler
//!
//! \param handle is the handle to the PMBus stack object
//! \param transaction is the PMBus transaction type
//!
//! This function gets the PMBus module transaction handler function for a
//! specific transaction type from the PMBus stack object.
//! Transactions include:
//! - PMBUS_TRANSACTION_NONE
//! - PMBUS_TRANSACTION_WRITEBYTE
//! - PMBUS_TRANSACTION_READBYTE
//! - PMBUS_TRANSACTION_SENDBYTE
//! - PMBUS_TRANSACTION_RECEIVEBYTE
//! - PMBUS_TRANSACTION_WRITEWORD
//! - PMBUS_TRANSACTION_READWORD
//!
//! \return Pointer to transaction function handler
//
//*****************************************************************************
static inline transactionHandler
PMBusStackObject_getTransactionHandler(PMBus_StackHandle handle,
                                       const PMBus_Transaction transaction)
{
    return(handle->transactionHandle[transaction]);
}

//*****************************************************************************
//
//! Check if the PMBus Command and Transaction Type are Valid
//!
//! \param handle is the handle to the PMBus stack object
//! \param transaction is the PMBus transaction type
//!
//! This function will query the PMBus command transaction mapping for the
//! given command to see if it can find a match for the given transaction type.
//!
//! \return
//! - \b true if the command and transaction match (and therefore valid)
//! - \b false if the command and transaction don't match
//
//*****************************************************************************
static bool
PMBusStackObject_isCommandAndTransactionValid(const uint16_t command,
                                              const PMBus_Transaction transaction)
{
    uint16_t base, downshift;
    PMBus_Transaction transactionNibble;
    bool status = false;

    //
    // The base address in the commandMap is command/4
    //
    base = (command >> 2U) & BASE_ADDRESS_MASK;

    //
    // The transaction is either field0, 1, 2, or 3, we are
    // going to determine how much right shift we need to have
    // our reference transaction in the lowest nibble. Since
    // each field is 4 bits, we multiply by 4
    //
    downshift = (command & COMMAND_MASK) << 2U;

    //
    // Find the transaction nibble in the commandMap
    //
    transactionNibble = (PMBus_Transaction)
                        ((PMBusStack_commandTransactionMap[base].transactionField >>
                          downshift) & TRANSACTION_NIBBLE_MASK);

    if(transactionNibble == transaction)
    {
        status = true;
    }

    return(status);
}

//*****************************************************************************
//
//! Read from the receive buffer
//!
//! \param base is the base address of the I2C instance used for PMBus over I2C.
//! \param buffer pointer to the message buffer where the received bytes
//!  will be stored
//
//! \return num_rx_bytes - Number of bytes that are received.
//!
//
//*****************************************************************************
extern uint16_t
PMBus_over_I2C_getData(uint32_t base, uint16_t *buffer);

//*****************************************************************************
//
//! write to the transmit buffer
//!
//! \param base is the base address of the I2C instance used for PMBus over I2C.
//! \param buffer pointer to the message buffer where the transmit bytes
//!   are stored
//! \param nBytes number of transmit bytes, up to 255
//!
//! This function can write up to 255 bytes in the transmit buffer.
//!
//!
//! \return None.
//
//*****************************************************************************
extern void
PMBus_over_I2C_putData(uint32_t base, uint16_t *buffer, uint16_t nBytes);

#ifdef PEC_ENABLED
//*****************************************************************************
//
//! Calcuate PEC (PMBus over I2C)
//!
//! \param CRCMsgBuffer is the pointer to the  CRC Message Buffer.
//! \param CRCMsgSize  is the size of the CRCMsgBuffer in bytes
//! \param pMsgBuffer is the pointer to the Message Buffer that stores the
//!        messages transmitted or received
//! \param nBytes number of transmit/received bytes, up to 255
//!
//!
//! \return PEC.
//
//*****************************************************************************
extern uint16_t calc_PEC(uint16_t *CRCMsgBuffer, uint16_t CRCMsgSize, uint16_t *pMsgBuffer, uint16_t nBytes);
//*****************************************************************************
//
//! Verify PEC (PMBus over I2C)
//!
//! \param CRCMsgBuffer is the pointer to the  CRC Message Buffer.
//! \param CRCMsgSize  is the size of the CRCMsgBuffer in bytes
//! \param pMsgBuffer is the pointer to the Message Buffer that stores the
//!        messages transmitted or received
//! \param nBytes number of transmit/received bytes, up to 255
//! \param receivedPEC - Received PEC byte
//!
//!
//! \return True if calculated PEC matches the received PEC byte
//! \return False if calculated PEC does not match with the received PEC byte
//
//*****************************************************************************
extern bool verifyPEC(uint16_t *CRCMsgBuffer, uint16_t CRCMsgSize, uint16_t *pMsgBuffer, uint16_t nBytes, uint16_t receivedPEC);
#endif

#ifdef TIMEOUT
//*****************************************************************************
//
//! Configure CPU Timer (PMBus over I2C)
//! This function initializes the selected timer to the
//! period specified by the "freq" and "period" parameters. The "freq" is
//! entered as Hz and the period in uSeconds. The timer is held in the stopped
//! state after configuration.to interrupt after each period (in uSeconds)
//!
//! \param cpuTimer is the selected timer
//! \param freq  is the device sys clk freq
//! \param period is the time in uSeconds
//!
//! \return None
//
//*****************************************************************************
void configCPUTimer(uint32_t cpuTimer, float freq, float period);
//*****************************************************************************
//
//! Initialize CPU Timer (PMBus over I2C)
//! This function initializes the selected CPU timers to a known state.
//!
//! \param cpuTimer is the selected CPU timer.
//!
//! \return None
//
//*****************************************************************************
void initCPUTimers(uint32_t cpuTimer);
#endif

#define PMBus_over_I2C_getControllerData PMBus_over_I2C_getData
#define PMBus_over_I2C_getTargetData  PMBus_over_I2C_getData

#define PMBus_over_I2C_putControllerData PMBus_over_I2C_putData
#define PMBus_over_I2C_putTargetData  PMBus_over_I2C_putData


//*****************************************************************************
//
// Close the Doxygen group.
// @}
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

#endif  // PMBUS_OVER_I2C_STACK_CONFIG_H
#endif // PMBUS_OVER_I2C
