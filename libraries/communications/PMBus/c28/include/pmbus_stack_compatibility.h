//###########################################################################
//
// FILE:   pmbus_stack_compatibility.h
//
// TITLE:  PMBus Stack Library Compatibility Header
//
// IMPORTANT: This re-maps the legacy F28004x PMBus stack library API, ENUM, 
//            Struct, etc names to the new names of the PMBus library
//            (Legacy PMBus library refers to the version released in
//             C2000Ware v2.00.00.03 and older)
//
// Legacy Users: If you've previously developed using the legacy PMBus library,
//               include this header in your project to map the legacy names
//               to the new library names           
//
// New Users: If this is your first time developing with this library,
//            DON'T include this file.
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

#ifndef PMBUS_STACK_COMPATIBILITY_H
#define PMBUS_STACK_COMPATIBILITY_H

//
// Library API re-defining
//
#define PMBus_Stack_assertionFailed                       PMBusStack_assertionFailed
#define PMBus_Stack_errorHandler                          PMBusStack_errorHandler
#define PMBus_Stack_initModule                            PMBusStack_initModule
#define PMBus_Stack_defaultTransactionHandler             PMBusStack_defaultTransactionHandler
#define PMBus_Stack_Obj_setModuleBase                     PMBusStackObject_setModuleBase
#define PMBus_Stack_Obj_getModuleBase                     PMBusStackObject_getModuleBase
#define PMBus_Stack_Obj_setModuleStatus                   PMBusStackObject_setModuleStatus
#define PMBus_Stack_Obj_getModuleStatus                   PMBusStackObject_getModuleStatus
#define PMBus_Stack_Obj_setMode                           PMBusStackObject_setMode
#define PMBus_Stack_Obj_getMode                           PMBusStackObject_getMode
#define PMBus_Stack_Obj_setAddress                        PMBusStackObject_setTargetAddress
#define PMBus_Stack_Obj_getAddress                        PMBusStackObject_getTargetAddress
#define PMBus_Stack_Obj_setAddressMask                    PMBusStackObject_setTargetAddressMask
#define PMBus_Stack_Obj_getAddressMask                    PMBusStackObject_getTargetAddressMask
#define PMBus_Stack_Obj_setCurrentState                   PMBusStackObject_setCurrentState
#define PMBus_Stack_Obj_getCurrentState                   PMBusStackObject_getCurrentState
#define PMBus_Stack_Obj_setNextState                      PMBusStackObject_setNextState
#define PMBus_Stack_Obj_getNextState                      PMBusStackObject_getNextState
#define PMBus_Stack_Obj_setPtrBuffer                      PMBusStackObject_setBufferPointer
#define PMBus_Stack_Obj_getPtrBuffer                      PMBusStackObject_getBufferPointer
#define PMBus_Stack_Obj_setCurrPtr                        PMBusStackObject_setCurrentPositionPointer
#define PMBus_Stack_Obj_getCurrPtr                        PMBusStackObject_getCurrentPositionPointer
#define PMBus_Stack_Obj_setNBytes                         PMBusStackObject_setNumOfBytes
#define PMBus_Stack_Obj_getNBytes                         PMBusStackObject_getNumOfBytes
#define PMBus_Stack_Obj_setPECValid                       PMBusStackObject_setPECValidity
#define PMBus_Stack_Obj_getPECValid                       PMBusStackObject_isPECValid
#define PMBus_Stack_Obj_setTransaction                    PMBusStackObject_setTransactionType
#define PMBus_Stack_Obj_getTransaction                    PMBusStackObject_getTransactionType
#define PMBus_Stack_Obj_setTransactionHandler             PMBusStackObject_setTransactionHandler
#define PMBus_Stack_Obj_getTransactionHandler             PMBusStackObject_getTransactionHandler
#define PMBus_Stack_doesCommandMatchTransaction           PMBusStackObject_isCommandAndTransactionValid

#define PMBus_Stack_targetHandler                          PMBusStack_targetStateHandler
#define PMBus_Stack_targetIdleHandler                      PMBusStack_targetIdleStateHandler
#define PMBus_Stack_targetReceiveByteWaitForEomHandler     PMBusStack_targetReceiveByteWaitForEOMStateHandler
#define PMBus_Stack_targetReadBlockHandler                 PMBusStack_targetReadBlockStateHandler
#define PMBus_Stack_targetReadWaitForEOMHandler            PMBusStack_targetReadWaitForEOMStateHandler
#define PMBus_Stack_targetBlockWriteOrProcessCallHandler   PMBusStack_targetBlockWriteOrProcessCallStateHandler
#define PMBUS_STACK_extendedCommandHandler                PMBusStack_targetExtendedCommandStateHandler

//
// ENUM, Structs, etc re-defining
//
#define PMBus_Stack_mode                                  PMBus_StackMode
#define PMBus_Stack_State                                 PMBus_StackState
#define PMBus_Stack_Obj                                   PMBus_StackObject
#define PMBus_Transaction_Obj                             PMBus_TransactionObject
#define PMBus_Stack_Handle                                PMBus_StackHandle
#define PMBus_Transaction_Obj_u                           PMBus_TransactionObjectUnion
#define PMBus_Stack_commandTransactionMap                 PMBusStack_commandTransactionMap
#define PMBUS_STACK_Target                                 PMBusStackTarget

#endif // PMBUS_STACK_COMPATIBILITY_H
