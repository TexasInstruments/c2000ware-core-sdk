#include <stdint.h>
#include "transfer_ringbuffer.h"

void TransferRingBuffer_init(TransferRingBuffer_Handle trb, uint16_t** buffer, uint16_t size, uint16_t numElemPerBuffEntry)
{
    trb->buffer = buffer;
    trb->bufferSize = size;
    trb->writeIndex = 0;
    trb->readIndex = 0;
    trb->numElemPerBuffEntry = numElemPerBuffEntry;
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
uint16_t TransferRingBuffer_read(TransferRingBuffer_Handle trb, uint16_t* data)
{
    uint16_t r = 0;
    uint16_t elemIndex = 0;
    uint16_t* bufferEntry = &(
            ((uint16_t *)trb->buffer)[trb->numElemPerBuffEntry*trb->readIndex]
                              );

    if(trb && data && !TransferRingBuffer_empty(trb))
    {
        for (elemIndex = 0; elemIndex < trb->numElemPerBuffEntry; elemIndex++) {
            data[elemIndex] = bufferEntry[elemIndex];
        }
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
uint16_t TransferRingBuffer_write(TransferRingBuffer_Handle trb, uint16_t* data)
{
    uint16_t r = 0;
    uint16_t elemIndex = 0;
    uint16_t* bufferEntry = &(
            ((uint16_t *)trb->buffer)[trb->numElemPerBuffEntry*trb->writeIndex]
                              );

    if(trb && !TransferRingBuffer_full(trb))
    {
        for (elemIndex = 0; elemIndex < trb->numElemPerBuffEntry; elemIndex++) {
            bufferEntry[elemIndex] = data[elemIndex];
        }
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
uint16_t TransferRingBuffer_writeWithPad(TransferRingBuffer_Handle trb, uint16_t* data, uint16_t dataSize, uint16_t pad)
{
    uint16_t r = 0;
    uint16_t elemIndex = 0;
    uint16_t* bufferEntry = &(
            ((uint16_t *)trb->buffer)[trb->numElemPerBuffEntry*trb->writeIndex]
                              );

    if(trb && !TransferRingBuffer_full(trb))
    {
        for (elemIndex = 0; elemIndex < trb->numElemPerBuffEntry; elemIndex++) {
            if (elemIndex < dataSize)
            {
                bufferEntry[elemIndex] = data[elemIndex];
            }
            else
            {
                bufferEntry[elemIndex] = pad;
            }
        }
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
uint16_t TransferRingBuffer_writePartialElement(TransferRingBuffer_Handle trb, uint16_t elemWriteStartIndex, uint16_t* data, uint16_t dataSize)
{
    uint16_t r = 0;
    uint16_t elemIndex = 0;
    uint16_t dataIndex = 0;
    uint16_t* bufferEntry = &(
            ((uint16_t *)trb->buffer)[trb->numElemPerBuffEntry*trb->writeIndex]
                              );

    if (elemWriteStartIndex + dataSize > trb->numElemPerBuffEntry)
    {
        return 0;
    }

    if(trb && !TransferRingBuffer_full(trb))
    {
        for (elemIndex = elemWriteStartIndex;
                elemIndex < elemWriteStartIndex + dataSize;
                elemIndex++) {

                bufferEntry[elemIndex] = data[dataIndex];
                dataIndex++;
        }

        r = 1;
    }

    return r;
}

//
// Returns 1 if successful
// Returns 0 if fail (full)
//
uint16_t TransferRingBuffer_writePartialElementWithConst(TransferRingBuffer_Handle trb, uint16_t elemWriteStartIndex, uint16_t data, uint16_t dataSize)
{
    uint16_t r = 0;
    uint16_t elemIndex = 0;
    uint16_t* bufferEntry = &(
            ((uint16_t *)trb->buffer)[trb->numElemPerBuffEntry*trb->writeIndex]
                              );

    if (elemWriteStartIndex + dataSize > trb->numElemPerBuffEntry)
    {
        return 0;
    }

    if(trb && !TransferRingBuffer_full(trb))
    {
        for (elemIndex = elemWriteStartIndex;
                elemIndex < elemWriteStartIndex + dataSize;
                elemIndex++) {

                bufferEntry[elemIndex] = data;
        }

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
