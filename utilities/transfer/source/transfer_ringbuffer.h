
#ifndef TRANSFER_RINGBUFFER_H_
#define TRANSFER_RINGBUFFER_H_
#include <stdint.h>

typedef struct{
    uint16_t** buffer;
    uint16_t writeIndex;
    uint16_t readIndex;
    uint16_t bufferSize;
    uint16_t numElemPerBuffEntry;
    uint16_t isFull;
} TransferRingBuffer;

typedef TransferRingBuffer *TransferRingBuffer_Handle;



void TransferRingBuffer_init(TransferRingBuffer_Handle trb, uint16_t** buffer, uint16_t size, uint16_t numElemPerBuffEntry);
uint16_t TransferRingBuffer_full(TransferRingBuffer_Handle trb);
uint16_t TransferRingBuffer_empty(TransferRingBuffer_Handle trb);
uint16_t TransferRingBuffer_read(TransferRingBuffer_Handle trb, uint16_t* data);
uint16_t TransferRingBuffer_write(TransferRingBuffer_Handle trb, uint16_t* data);
uint16_t TransferRingBuffer_writeWithPad(TransferRingBuffer_Handle trb, uint16_t* data, uint16_t dataSize, uint16_t pad);
uint16_t TransferRingBuffer_spaceUsed(TransferRingBuffer_Handle trb);

//
// Partial element updates
// Advanced users only
//
uint16_t TransferRingBuffer_writePartialElement(TransferRingBuffer_Handle trb, uint16_t elemWriteStartIndex, uint16_t* data, uint16_t dataSize);
uint16_t TransferRingBuffer_writePartialElementWithConst(TransferRingBuffer_Handle trb, uint16_t elemWriteStartIndex, uint16_t data, uint16_t dataSize);
uint16_t TransferRingBuffer_writePartialElementComplete(TransferRingBuffer_Handle trb);


#endif /* TRANSFER_RINGBUFFER_H_ */
