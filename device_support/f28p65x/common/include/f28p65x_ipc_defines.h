//###########################################################################
//
// FILE:    f28p65x_ipc_defines.h
//
// TITLE:   F28P65X IPC support definitions
//
//###########################################################################
//
//
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

#ifndef F28P65X_IPC_DEFINES_H
#define F28P65X_IPC_DEFINES_H

//
// Defines
//

//
// IPC Flags
//
#ifndef IPC_FLAGS_DEFINED
#define IPC_FLAGS_DEFINED
#define NO_FLAG                     0x00000000  // NO FLAG
#define IPC_NO_FLAG                 0x00000000  // NO FLAG
#define IPC_FLAG0                   0x00000001  // IPC FLAG 0
#define IPC_FLAG1                   0x00000002  // IPC FLAG 1
#define IPC_FLAG2                   0x00000004  // IPC FLAG 2
#define IPC_FLAG3                   0x00000008  // IPC FLAG 3
#define IPC_FLAG4                   0x00000010  // IPC FLAG 4
#define IPC_FLAG5                   0x00000020  // IPC FLAG 5
#define IPC_FLAG6                   0x00000040  // IPC FLAG 6
#define IPC_FLAG7                   0x00000080  // IPC FLAG 7
#define IPC_FLAG8                   0x00000100  // IPC FLAG 8
#define IPC_FLAG9                   0x00000200  // IPC FLAG 9
#define IPC_FLAG10                  0x00000400  // IPC FLAG 10
#define IPC_FLAG11                  0x00000800  // IPC FLAG 11
#define IPC_FLAG12                  0x00001000  // IPC FLAG 12
#define IPC_FLAG13                  0x00002000  // IPC FLAG 13
#define IPC_FLAG14                  0x00004000  // IPC FLAG 14
#define IPC_FLAG15                  0x00008000  // IPC FLAG 15
#define IPC_FLAG16                  0x00010000  // IPC FLAG 16
#define IPC_FLAG17                  0x00020000  // IPC FLAG 17
#define IPC_FLAG18                  0x00040000  // IPC FLAG 18
#define IPC_FLAG19                  0x00080000  // IPC FLAG 19
#define IPC_FLAG20                  0x00100000  // IPC FLAG 20
#define IPC_FLAG21                  0x00200000  // IPC FLAG 21
#define IPC_FLAG22                  0x00400000  // IPC FLAG 22
#define IPC_FLAG23                  0x00800000  // IPC FLAG 23
#define IPC_FLAG24                  0x01000000  // IPC FLAG 24
#define IPC_FLAG25                  0x02000000  // IPC FLAG 25
#define IPC_FLAG26                  0x04000000  // IPC FLAG 26
#define IPC_FLAG27                  0x08000000  // IPC FLAG 27
#define IPC_FLAG28                  0x10000000  // IPC FLAG 28
#define IPC_FLAG29                  0x20000000  // IPC FLAG 29
#define IPC_FLAG30                  0x40000000  // IPC FLAG 30
#define IPC_FLAG31                  0x80000000  // IPC FLAG 31
#define IPC_FLAG_ALL                0xFFFFFFFF  // All IPC flags
#endif
//
//Key value used for write access to the flash pump semaphore register
//
#define IPC_FLASHCTLSEM_KEY                0x5a5a0000

//
// The following defines are added for legacy reasons.
// All macros are used assuming CPUxTOCPUx_IPC instance
// Usage of driverlib APIs is recommended
//
#define C1TOC2_MSG_RAM ((void *)0x3A000)
#define C2TOC1_MSG_RAM ((void *)0x3B000)

#if defined(CPU1)
    #define SEND_MSG_RAM C1TOC2_MSG_RAM
    #define RECV_MSG_RAM C2TOC1_MSG_RAM
#elif defined(CPU2)
    #define SEND_MSG_RAM C2TOC1_MSG_RAM
    #define RECV_MSG_RAM C1TOC2_MSG_RAM
#endif
#define MSG_RAM_SIZE 0x400

#if defined(CPU1)
#define IPCRtoLFlagAcknowledge(f) \
        Cpu1toCpu2IpcRegs.CPU1TOCPU2IPCACK.all |= (f)
#define IPCRtoLFlagBusy(f) \
        (((Cpu1toCpu2IpcRegs.CPU2TOCPU1IPCSTS.all & (f)) == 0) ? 0 : 1)
#define IPCLtoRFlagBusy(f) \
        (((Cpu1toCpu2IpcRegs.CPU1TOCPU2IPCFLG.all & (f)) == 0) ? 0 : 1)
#define IPCLtoRFlagSet(f) \
        Cpu1toCpu2IpcRegs.CPU1TOCPU2IPCSET.all |= (f)
#define IPCLtoRFlagClear(f) \
        Cpu1toCpu2IpcRegs.CPU1TOCPU2IPCCLR.all |= (f)
#define SeizeFlashPump() \
        Cpu1toCpu2IpcRegs.FLASHCTLSEM.all = IPC_FLASHCTLSEM_KEY | 0x2
#define ReleaseFlashPump() \
        Cpu1toCpu2IpcRegs.FLASHCTLSEM.all = IPC_FLASHCTLSEM_KEY | 0x0


#elif defined(CPU2)
#define IPCRtoLFlagAcknowledge(f) \
        Cpu2toCpu1IpcRegs.CPU2TOCPU1IPCACK.all |= (f)
#define IPCRtoLFlagBusy(f) \
        (((Cpu2toCpu1IpcRegs.CPU1TOCPU2IPCSTS.all & (f)) == 0) ? 0 : 1)
#define IPCLtoRFlagBusy(f) \
        (((Cpu2toCpu1IpcRegs.CPU2TOCPU1IPCFLG.all & (f)) == 0) ? 0 : 1)
#define IPCLtoRFlagSet(f) \
        Cpu2toCpu1IpcRegs.CPU2TOCPU1IPCSET.all |= (f)
#define IPCLtoRFlagClear(f) \
        Cpu2toCpu1IpcRegs.CPU2TOCPU1IPCCLR.all |= (f)
#define SeizeFlashPump() \
        Cpu2toCpu1IpcRegs.FLASHCTLSEM.all = IPC_FLASHCTLSEM_KEY | 0x1
#define ReleaseFlashPump() \
        Cpu2toCpu1IpcRegs.FLASHCTLSEM.all = IPC_FLASHCTLSEM_KEY | 0x0
#endif


#endif  // end of F28P65X_IPC_DEFINES_H definition

//
// End of file
//
