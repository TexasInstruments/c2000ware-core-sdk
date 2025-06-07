//#############################################################################
//
// FILE:   transfer_ringbuffer.c
//
// Version 2.0
//
// Changes:
// Implementation changed to use void * instead of uint16_t **
// So now the buffer can be used with any element type. The element can be an
// array of uint16_t's, similar to rev 1.0. Or it can be an float, array of
// floats etc.
//
// TransferRingBuffer_init
// elemSize is now the number of chars (sizeof) each buffer element
//
// TransferRingBuffer_writeWithPad
// pad
// The pad value is now of type char instead of uint16.
// This change means that if the user was passing in a value larger than 0xFF
// then this will be a compatibility break.
// Also on architectures where char is 8-bits, uint16_t can fit two chars.
// Hence if a value of non-zero was used, it will be a compatibility break.
// partialDataSize
// This is now the size of partialData in chars. must be changed to
// sizeof(partialData) or oldValue*sizeof(the type of data)
//
// TransferRingBuffer_writePartialElement
// elemWriteStartIndex
// The argument elemWriteStartIndex has changed. In rev 1.0 it was the index of
// the specific entry in each element (uint16_t array) that the write was to
// begin from.
// In rev 2.0 elemWriteStartIndex is the char index of the location in the
// elem that the write should start from.
// To operate the same, the value passed into the elemWriteStartIndex should be
// changed with (oldValue * sizeof(the type of data))
// partialDataSize
// same as above
//
// TransferRingBuffer_writePartialElementWithConst
// elemWriteStartIndex
// same as the info above.
// data -> constData
// the type switched from uint16_t to char. if value
// larger than 0xFF was used, then this will be a compatibility break.
// Also on architectures where char is 8-bits, uint16_t can fit two chars.
// Hence if a value of non-zero was used, it will be a compatibility break.
// dataSize -> constDataSize
// same as partialDataSize, changes should be similar.
//
//
//
//#############################################################################
//
// C2000Ware v5.03.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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

#include <stdint.h>
#include <string.h>
#include "transfer_ringbuffer.h"

void TransferRingBuffer_init(TransferRingBuffer_Handle trb, void* buffer, uint16_t bufferSize, uint16_t elemSize)
{
    trb->buffer = buffer;
    trb->bufferSize = bufferSize;
    trb->writeIndex = 0;
    trb->readIndex = 0;
    trb->elemSize = elemSize;
    trb->isFull = 0;

    return;
}

//
// Return 1 if full
//
uint16_t TransferRingBuffer_full(TransferRingBuffer_Handle trb)
{
    return trb->isFull;
}

//
// Empty is writeIndex == readIndex and not FULL
// Return 1 if empty
//
uint16_t TransferRingBuffer_empty(TransferRingBuffer_Handle trb)
{
    return ((!trb->isFull) && (trb->writeIndex == trb->readIndex));
}

uint16_t TransferRingBuffer_spaceUsed(TransferRingBuffer_Handle trb)
{
    uint16_t size = trb->bufferSize;

    if(!trb->isFull)
    {
        if(trb->writeIndex >= trb->readIndex)
        {
            size = (trb->writeIndex - trb->readIndex);
        }
        else
        {
            size = (trb->bufferSize + trb->writeIndex - trb->readIndex);
        }
    }

    return size;
}

//
// Returns 1 if successful
// Returns 0 if fail (empty)
//
uint16_t TransferRingBuffer_read(TransferRingBuffer_Handle trb, void* data)
{
    uint16_t r = 0;
    char* bufferEntry = &(((char*)trb->buffer)[trb->elemSize*trb->readIndex]);

    if(trb && data && !TransferRingBuffer_empty(trb))
    {
        memcpy(data, bufferEntry, trb->elemSize);
        trb->readIndex = trb->readIndex + 1;
        if (trb->readIndex >= trb->bufferSize)
        {
            trb->readIndex = 0;
        }
        trb->isFull = 0;
        r = 1;
    }

    return r;
}

//
// Returns 1 if successful
// Returns 0 if fail (full)
//
uint16_t TransferRingBuffer_write(TransferRingBuffer_Handle trb, void* data)
{
    uint16_t r = 0;
    char* bufferEntry = &(((char*)trb->buffer)[trb->elemSize*trb->writeIndex]);

    if(trb && !TransferRingBuffer_full(trb))
    {
        memcpy(bufferEntry, data, trb->elemSize);
        trb->writeIndex = (trb->writeIndex + 1);
        if (trb->writeIndex >= trb->bufferSize)
        {
            trb->writeIndex = 0;
        }
        trb->isFull = (trb->writeIndex == trb->readIndex);

        r = 1;
    }

    return r;
}


//
// Returns 1 if successful
// Returns 0 if fail (full)
//
uint16_t TransferRingBuffer_writeWithPad(TransferRingBuffer_Handle trb, void* partialData, uint16_t partialDataSize, char pad)
{
    uint16_t r = 0;
    char* bufferEntry = &(((char*)trb->buffer)[trb->elemSize*trb->writeIndex]);


    if(trb && !TransferRingBuffer_full(trb))
    {
        memcpy(bufferEntry, partialData, partialDataSize);
        memset(bufferEntry + partialDataSize, pad, trb->elemSize - partialDataSize);
        trb->writeIndex = (trb->writeIndex + 1);
        if (trb->writeIndex >= trb->bufferSize)
        {
            trb->writeIndex = 0;
        }
        trb->isFull = (trb->writeIndex == trb->readIndex);

        r = 1;
    }

    return r;
}

//
// Returns 1 if successful
// Returns 0 if fail (full)
//
uint16_t TransferRingBuffer_writePartialElement(TransferRingBuffer_Handle trb, uint16_t elemWriteStartIndex, void* partialData, uint16_t partialDataSize)
{
    uint16_t r = 0;
    char* bufferEntry = &(((char*)trb->buffer)[trb->elemSize*trb->writeIndex]);
    char* elemEntry = bufferEntry + elemWriteStartIndex;


    if (elemWriteStartIndex + partialDataSize > trb->elemSize)
    {
        return 0;
    }

    if(trb && !TransferRingBuffer_full(trb))
    {
        memcpy(elemEntry, partialData, partialDataSize);

        r = 1;
    }

    return r;
}

//
// Returns 1 if successful
// Returns 0 if fail (full)
//
uint16_t TransferRingBuffer_writePartialElementWithConst(TransferRingBuffer_Handle trb, uint16_t elemWriteStartIndex, char constData, uint16_t constDataSize)
{
    uint16_t r = 0;
    char* bufferEntry = &(((char*)trb->buffer)[trb->elemSize*trb->writeIndex]);
    char* elemEntry = bufferEntry + elemWriteStartIndex;

    if (elemWriteStartIndex + constDataSize > trb->elemSize)
    {
        return 0;
    }

    if(trb && !TransferRingBuffer_full(trb))
    {
        memset(elemEntry, constData, constDataSize);

        r = 1;
    }

    return r;
}

uint16_t TransferRingBuffer_writePartialElementComplete(TransferRingBuffer_Handle trb)
{
   uint16_t r = 0;
   if (trb && !TransferRingBuffer_full(trb))
   {
       trb->writeIndex = (trb->writeIndex + 1);
       if (trb->writeIndex >= trb->bufferSize)
       {
           trb->writeIndex = 0;
       }
       trb->isFull = (trb->writeIndex == trb->readIndex);
       r = 1;
   }

   return r;
}
