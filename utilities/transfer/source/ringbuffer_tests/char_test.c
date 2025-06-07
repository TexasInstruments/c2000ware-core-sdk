#include "transfer_ring_buffer_test.h"

#include "stdint.h"
#include "transfer_ringbuffer.h"
#include "stddef.h"
#include "string.h"


//
// Char
//

#define TESTCHAR_BUFFER_SIZE 20
#define TESTCHAR_ELEMENT_SIZE 10

uint16_t readCharValidate(char * d, char * rd)
{
    uint16_t i = 0;
    for (i = 0; i < TESTCHAR_ELEMENT_SIZE; i++)
    {
        if (d[i] != rd[i])
        {
            // Error
            ESTOP0;
            return 0;
        }
    }


    return 1;
}

void charTest(){
    uint16_t result = 0;
    uint16_t index = 0;

    char TestChar_buffer[TESTCHAR_BUFFER_SIZE][TESTCHAR_ELEMENT_SIZE] = {0};

    TransferRingBuffer TestChar_trb;
    TransferRingBuffer_Handle TestChar_trb_Handle = &TestChar_trb;
    char readCharData[TESTCHAR_ELEMENT_SIZE] = {0};


    TransferRingBuffer_init(
            TestChar_trb_Handle,
            (uint16_t**)TestChar_buffer,
            TESTCHAR_BUFFER_SIZE,
            sizeof(TestChar_buffer[0]));


    result = TransferRingBuffer_full(TestChar_trb_Handle);
    if (result)
    {
        // Error
        ESTOP0;
    }
    result = TransferRingBuffer_empty(TestChar_trb_Handle);
    if (!result)
    {
        // Error
        ESTOP0;
    }

    char data1Char[TESTCHAR_ELEMENT_SIZE] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    //char data2Char[TESTCHAR_ELEMENT_SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    char data2Char[TESTCHAR_ELEMENT_SIZE] = "ABCDEFGHIJ";
    char data3Char[TESTCHAR_ELEMENT_SIZE] = {16, 1, 240, 3, 4, 5, 6, 7, 8, 9};

    //
    // Write data1 then read validate
    //
    result = TransferRingBuffer_write(TestChar_trb_Handle, data1Char);
    CHECK_RESULT(result);

    result = TransferRingBuffer_read(TestChar_trb_Handle, readCharData);
    CHECK_RESULT(result);

    result = readCharValidate(data1Char, readCharData);
    CHECK_RESULT(result);

    //
    // Write data2Char and data3Char (write two in a row) then validate
    //
    result = TransferRingBuffer_write(TestChar_trb_Handle, data2Char);
    CHECK_RESULT(result);
    result = TransferRingBuffer_write(TestChar_trb_Handle, data3Char);
    CHECK_RESULT(result);

    result = TransferRingBuffer_read(TestChar_trb_Handle, readCharData);
    CHECK_RESULT(result);
    result = readCharValidate(data2Char, readCharData);
    CHECK_RESULT(result);
    result = TransferRingBuffer_read(TestChar_trb_Handle, readCharData);
    CHECK_RESULT(result);
    result = readCharValidate(data3Char, readCharData);
    CHECK_RESULT(result);


    //
    // Write till full
    //
    result = TransferRingBuffer_empty(TestChar_trb_Handle);
    if (!result)
    {
        // Error
        ESTOP0;
    }

    for (index = 0; index < (TESTCHAR_BUFFER_SIZE - 1); index++)
    {
        result = TransferRingBuffer_write(TestChar_trb_Handle, data1Char);
        CHECK_RESULT(result);

        // Should not be full yet
        result = TransferRingBuffer_full(TestChar_trb_Handle);
        if (result)
        {
            // Error
            ESTOP0;
        }

        // Should not be empty
        result = TransferRingBuffer_empty(TestChar_trb_Handle);
        if (result)
        {
            // Error
            ESTOP0;
        }

    }
    result = TransferRingBuffer_write(TestChar_trb_Handle, data1Char);
    CHECK_RESULT(result);
    // Now it should be full
    result = TransferRingBuffer_full(TestChar_trb_Handle);
    CHECK_RESULT(result);
    // Next write should fail
    result = TransferRingBuffer_write(TestChar_trb_Handle, data1Char);
    if (result)
    {
        // Error
        ESTOP0;
    }

    // Now read to all except last
    for (index = 0; index < (TESTCHAR_BUFFER_SIZE - 1); index++)
    {
        result = TransferRingBuffer_read(TestChar_trb_Handle, readCharData);
        CHECK_RESULT(result);
        result = readCharValidate(data1Char, readCharData);
        CHECK_RESULT(result);

        // Should not be full yet
        result = TransferRingBuffer_full(TestChar_trb_Handle);
        if (result)
        {
            // Error
            ESTOP0;
        }

        // Should not be empty
        result = TransferRingBuffer_empty(TestChar_trb_Handle);
        if (result)
        {
            // Error
            ESTOP0;
        }

    }
    result = TransferRingBuffer_read(TestChar_trb_Handle, readCharData);
    CHECK_RESULT(result);
    result = readCharValidate(data1Char, readCharData);
    CHECK_RESULT(result);
    // Now it should be empty
    result = TransferRingBuffer_empty(TestChar_trb_Handle);
    CHECK_RESULT(result);
    // Next read should fail
    result = TransferRingBuffer_read(TestChar_trb_Handle, readCharData);
    if (result)
    {
        // Error
        ESTOP0;
    }


    //
    // Partial element tests
    //
    // Clear the TestBuffer
    memset(TestChar_buffer, 0, sizeof(TestChar_buffer));
    TestChar_trb.writeIndex = 0;
    TestChar_trb.readIndex = 0;
    TestChar_trb.isFull = 0;

    char partialData1[] = {33.43, 42.32, 22.66, 23.44, 46.78, 7895.96, 4900.97, 44.55, 55.44, 88.02};
    result = TransferRingBuffer_writePartialElement(
            TestChar_trb_Handle,
            3*sizeof(char),
            partialData1 + 3,
            7*sizeof(char));
    CHECK_RESULT(result);

    result = TransferRingBuffer_writePartialElement(
            TestChar_trb_Handle,
            0,
            partialData1,
            3*sizeof(char));
    CHECK_RESULT(result);

    result = TransferRingBuffer_writePartialElementComplete(TestChar_trb_Handle);
    CHECK_RESULT(result);

    char partialData2[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10};
    result = TransferRingBuffer_writePartialElement(
            TestChar_trb_Handle,
            4*sizeof(char),
            partialData2 + 4,
            6*sizeof(char));
    CHECK_RESULT(result);

    result = TransferRingBuffer_writePartialElement(
            TestChar_trb_Handle,
            0,
            partialData2,
            4*sizeof(char));
    CHECK_RESULT(result);


    result = TransferRingBuffer_writePartialElementComplete(TestChar_trb_Handle);
    CHECK_RESULT(result);

    result = TransferRingBuffer_read(TestChar_trb_Handle, readCharData);
    CHECK_RESULT(result);
    result = readCharValidate(partialData1, readCharData);
    CHECK_RESULT(result);

    result = TransferRingBuffer_read(TestChar_trb_Handle, readCharData);
    CHECK_RESULT(result);
    result = readCharValidate(partialData2, readCharData);
    CHECK_RESULT(result);

    //
    // Basic write and read validated
    //
    // Now let validate write with PAD.
    //
    result = TransferRingBuffer_writeWithPad(
            TestChar_trb_Handle,
            partialData1,
            4*sizeof(char),
            0x20);

    char padVal = 0;
    memset(&padVal, 0x20, sizeof(char));

    CHECK_RESULT(result);

    result = TransferRingBuffer_read(TestChar_trb_Handle, readCharData);
    CHECK_RESULT(result);

    for (index = 0; index < TESTCHAR_ELEMENT_SIZE; index++)
    {
        if (index < 4)
        {
            if (partialData1[index] != readCharData[index]){
                //
                // Error
                //
                ESTOP0;
            }
        }
        else
        {
#ifdef _TMS320C28X
            if (readCharData[index] != padVal) {
#else
            if (readCharData[index] != padVal) {
#endif
                //
                // Error
                //
                ESTOP0;
            }
        }
    }

    //
    // Now let validate write with CONST.
    //
    result = TransferRingBuffer_writePartialElementWithConst(
            TestChar_trb_Handle,
            4*sizeof(char),
            0x20,
            4*sizeof(char));

    CHECK_RESULT(result);

    result = TransferRingBuffer_writePartialElementComplete(TestChar_trb_Handle);
    CHECK_RESULT(result);


    result = TransferRingBuffer_read(TestChar_trb_Handle, readCharData);
    CHECK_RESULT(result);

    for (index = 0; index < TESTCHAR_ELEMENT_SIZE; index++)
    {
        if (index >= 4 && index < 8)
        {
#ifdef _TMS320C28X
            if (readCharData[index] != padVal){
#else
            if (readCharData[index] != padVal){
#endif
                //
                // Error
                //
                ESTOP0;
            }
        }
        else
        {
            if (readCharData[index] != 0) {
                //
                // Error
                //
                ESTOP0;
            }
        }
    }


    // All pass should only stop here
    ESTOP0;

}
