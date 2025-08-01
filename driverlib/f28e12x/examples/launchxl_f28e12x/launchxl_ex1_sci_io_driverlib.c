//#############################################################################
//
// FILE:   launchxl_ex1_sci_io_driverlib.c
//
// TITLE:  Contains the various functions related to the serial 
//         communications interface (SCI) object
//
//! <h1> Contains the various functions related to the serial
//!      communications interface (SCI) object </h1>
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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
//#############################################################################

//
// Included Files
//
#include <stdio.h>
#include <file.h>
#include <launchxl_ex1_sci_io_driverlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "driverlib.h"
#include "device.h"

//
// Defines
//

//
// Globals
//
uint16_t deviceOpen = 0;

//
// Functions
//

//
// SCI_open -
//
int SCI_open(const char * path, unsigned flags, int llv_fd)
{
    if(deviceOpen)
    {
        return (-1);
    }
    else
    {
        deviceOpen = 1;
        return (1);    
    }      
}

//
// SCI_close - 
//
int SCI_close(int dev_fd)
{
    if((dev_fd != 1) || (!deviceOpen))
    {
        return (-1);
    }
    else
    {
        deviceOpen = 0;
        return (0);
    }    
}

//
// SCI_read - 
//
int SCI_read(int dev_fd, char * buf, unsigned count)
{
    uint16_t readCount = 0;
    uint16_t * bufPtr = (uint16_t *) buf;
    
    if(count == 0)
    {
        return (0);
    }
    
    while((readCount < count) && SCI_isDataAvailableNonFIFO(SCIA_BASE))
    {
        *bufPtr = SCI_readCharNonBlocking(SCIA_BASE);
        readCount++;
        bufPtr++;
    }

//    while((readCount < count) && SciaRegs.SCIRXST.bit.RXRDY)
//    {
//        *bufPtr = SciaRegs.SCIRXBUF.all;
//        readCount++;
//        bufPtr++;
//    }
    
    return (readCount);
}

//
// SCI_write - 
//
int SCI_write(int dev_fd, const char * buf, unsigned count)
{
    uint16_t writeCount = 0;
    uint16_t * bufPtr = (uint16_t *) buf;
    
    if(count == 0)
    {
        return (0);
    }
    
    while(writeCount < count)
    {
        SCI_writeCharBlockingNonFIFO(SCIA_BASE, *bufPtr);
        writeCount++;
        bufPtr++;
    }
    
//    while(writeCount < count)
//    {
//        while(!SciaRegs.SCICTL2.bit.TXRDY);
//        SciaRegs.SCITXBUF.all = *bufPtr;
//        writeCount++;
//        bufPtr++;
//    }

    return (writeCount);
}

//
// SCI_lseek - 
//
off_t SCI_lseek(int dev_fd, off_t offset, int origin)
{
    return (0);   
}

//
// SCI_unlink -
//
int SCI_unlink(const char * path)
{
    return (0);
}

//
// SCI_rename - 
//
int SCI_rename(const char * old_name, const char * new_name)
{
    return (0);    
}

//
// End of File
//

