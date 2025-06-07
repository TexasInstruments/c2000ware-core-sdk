
#ifndef TRANSFER_RINGBUFFER_H_
#define TRANSFER_RINGBUFFER_H_
#include <stdint.h>

typedef struct{
    void* buffer;
    uint16_t writeIndex;
    uint16_t readIndex;
    uint16_t bufferSize;
    uint16_t elemSize;
    uint16_t isFull;
} TransferRingBuffer;

typedef TransferRingBuffer *TransferRingBuffer_Handle;



void TransferRingBuffer_init(TransferRingBuffer_Handle trb, void* buffer, uint16_t bufferSize, uint16_t elemSize);
uint16_t TransferRingBuffer_full(TransferRingBuffer_Handle trb);
uint16_t TransferRingBuffer_empty(TransferRingBuffer_Handle trb);
uint16_t TransferRingBuffer_read(TransferRingBuffer_Handle trb, void* data);
uint16_t TransferRingBuffer_write(TransferRingBuffer_Handle trb, void* data);
uint16_t TransferRingBuffer_writeWithPad(TransferRingBuffer_Handle trb, void* partialData, uint16_t partialDataSize, char pad);
uint16_t TransferRingBuffer_spaceUsed(TransferRingBuffer_Handle trb);

//
// Partial element updates
// Advanced users only
//

uint16_t TransferRingBuffer_writePartialElement(TransferRingBuffer_Handle trb, uint16_t elemWriteStartIndex, void* partialData, uint16_t partialDataSize);
uint16_t TransferRingBuffer_writePartialElementWithConst(TransferRingBuffer_Handle trb, uint16_t elemWriteStartIndex, char constData, uint16_t constDataSize);
uint16_t TransferRingBuffer_writePartialElementComplete(TransferRingBuffer_Handle trb);

#endif /* TRANSFER_RINGBUFFER_H_ */
