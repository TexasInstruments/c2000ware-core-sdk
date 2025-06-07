#include "transfer_ring_buffer_test.h"

#include "stdint.h"
#include "transfer_ringbuffer.h"
#include "stddef.h"
#include "string.h"


//
// Uint16_t
//
#define TEST_BUFFER_SIZE 20
#define TEST_ELEMENT_SIZE 10


uint16_t readValidate(uint16_t * d, uint16_t * rd)
{
    uint16_t i = 0;
    for (i = 0; i < TEST_ELEMENT_SIZE; i++)
    {
        if (d[i] != rd[i])
        {
            // Error
            // ESTOP0;
            return 0;
        }
    }


    return 1;
}

void uint16Test()
{
    uint16_t result = 0;
    size_t sz = 0;
    uint16_t index = 0;

    uint16_t readData[TEST_ELEMENT_SIZE] = {0};
    uint16_t Test_buffer[TEST_BUFFER_SIZE][TEST_ELEMENT_SIZE] = {0};
    TransferRingBuffer Test_trb;
    TransferRingBuffer_Handle Test_trb_Handle = &Test_trb;

    TransferRingBuffer_init(
            Test_trb_Handle,
            (uint16_t**)Test_buffer,
            TEST_BUFFER_SIZE,
            sizeof(Test_buffer[0]));


    sz = sizeof(uint16_t);
    sz = sizeof(char);
    sz = sizeof(Test_buffer);
    sz = sizeof(Test_trb);
    sz = sizeof(Test_trb_Handle);

    sz++;


    result = TransferRingBuffer_full(Test_trb_Handle);
    if (result)
    {
        // Error
        ESTOP0;
    }
    result = TransferRingBuffer_empty(Test_trb_Handle);
    if (!result)
    {
        // Error
        ESTOP0;
    }

    uint16_t data1[TEST_ELEMENT_SIZE] = {0, 1, 2, 3, 4, 5, 65533, 7, 8, 9};
    uint16_t data2[TEST_ELEMENT_SIZE] = {15, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    uint16_t data3[TEST_ELEMENT_SIZE] = {16, 1, 2, 3, 4, 50000, 6, 7, 8, 9};

    //
    // Write data1 then read validate
    //
    result = TransferRingBuffer_write(Test_trb_Handle, data1);
    CHECK_RESULT(result);

    result = TransferRingBuffer_read(Test_trb_Handle, readData);
    CHECK_RESULT(result);

    result = readValidate(data1, readData);
    CHECK_RESULT(result);

    //
    // Write data2 and data3 (write two in a row) then validate
    //
    result = TransferRingBuffer_write(Test_trb_Handle, data2);
    CHECK_RESULT(result);
    result = TransferRingBuffer_write(Test_trb_Handle, data3);
    CHECK_RESULT(result);

    result = TransferRingBuffer_read(Test_trb_Handle, readData);
    CHECK_RESULT(result);
    result = readValidate(data2, readData);
    CHECK_RESULT(result);
    result = TransferRingBuffer_read(Test_trb_Handle, readData);
    CHECK_RESULT(result);
    result = readValidate(data3, readData);
    CHECK_RESULT(result);


    //
    // Write till full
    //
    result = TransferRingBuffer_empty(Test_trb_Handle);
    if (!result)
    {
        // Error
        ESTOP0;
    }

    for (index = 0; index < (TEST_BUFFER_SIZE - 1); index++)
    {
        result = TransferRingBuffer_write(Test_trb_Handle, data1);
        CHECK_RESULT(result);

        // Should not be full yet
        result = TransferRingBuffer_full(Test_trb_Handle);
        if (result)
        {
            // Error
            ESTOP0;
        }

        // Should not be empty
        result = TransferRingBuffer_empty(Test_trb_Handle);
        if (result)
        {
            // Error
            ESTOP0;
        }

    }
    result = TransferRingBuffer_write(Test_trb_Handle, data1);
    CHECK_RESULT(result);
    // Now it should be full
    result = TransferRingBuffer_full(Test_trb_Handle);
    CHECK_RESULT(result);
    // Next write should fail
    result = TransferRingBuffer_write(Test_trb_Handle, data1);
    if (result)
    {
        // Error
        ESTOP0;
    }

    // Now read to all except last
    for (index = 0; index < (TEST_BUFFER_SIZE - 1); index++)
    {
        result = TransferRingBuffer_read(Test_trb_Handle, readData);
        CHECK_RESULT(result);
        result = readValidate(data1, readData);
        CHECK_RESULT(result);

        // Should not be full yet
        result = TransferRingBuffer_full(Test_trb_Handle);
        if (result)
        {
            // Error
            ESTOP0;
        }

        // Should not be empty
        result = TransferRingBuffer_empty(Test_trb_Handle);
        if (result)
        {
            // Error
            ESTOP0;
        }

    }
    result = TransferRingBuffer_read(Test_trb_Handle, readData);
    CHECK_RESULT(result);
    result = readValidate(data1, readData);
    CHECK_RESULT(result);
    // Now it should be empty
    result = TransferRingBuffer_empty(Test_trb_Handle);
    CHECK_RESULT(result);
    // Next read should fail
    result = TransferRingBuffer_read(Test_trb_Handle, readData);
    if (result)
    {
        // Error
        ESTOP0;
    }



    //
    // Partial element tests
    //
    // Clear the TestBuffer
    memset(Test_buffer, 0, sizeof(Test_buffer));
    Test_trb.writeIndex = 0;
    Test_trb.readIndex = 0;
    Test_trb.isFull = 0;

    uint16_t partialData1[] = {33, 42, 22, 23, 46, 7895, 4900, 44, 55, 88};
    result = TransferRingBuffer_writePartialElement(
            Test_trb_Handle,
            3*sizeof(uint16_t),
            partialData1 + 3,
            7*sizeof(uint16_t));
    CHECK_RESULT(result);

    result = TransferRingBuffer_writePartialElement(
            Test_trb_Handle,
            0,
            partialData1,
            3*sizeof(uint16_t));
    CHECK_RESULT(result);

    result = TransferRingBuffer_writePartialElementComplete(Test_trb_Handle);
    CHECK_RESULT(result);

    uint16_t partialData2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    result = TransferRingBuffer_writePartialElement(
            Test_trb_Handle,
            4*sizeof(uint16_t),
            partialData2 + 4,
            6*sizeof(uint16_t));
    CHECK_RESULT(result);

    result = TransferRingBuffer_writePartialElement(
            Test_trb_Handle,
            0,
            partialData2,
            4*sizeof(uint16_t));
    CHECK_RESULT(result);


    result = TransferRingBuffer_writePartialElementComplete(Test_trb_Handle);
    CHECK_RESULT(result);

    result = TransferRingBuffer_read(Test_trb_Handle, readData);
    CHECK_RESULT(result);
    result = readValidate(partialData1, readData);
    CHECK_RESULT(result);

    result = TransferRingBuffer_read(Test_trb_Handle, readData);
    CHECK_RESULT(result);
    result = readValidate(partialData2, readData);
    CHECK_RESULT(result);

    //
    // Basic write and read validated
    //
    // Now let validate write with PAD.
    //
    result = TransferRingBuffer_writeWithPad(
            Test_trb_Handle,
            partialData1,
            4*sizeof(uint16_t),
            0x20);

    CHECK_RESULT(result);

    result = TransferRingBuffer_read(Test_trb_Handle, readData);
    CHECK_RESULT(result);

    for (index = 0; index < TEST_ELEMENT_SIZE; index++)
    {
        if (index < 4)
        {
            if (partialData1[index] != readData[index]){
                //
                // Error
                //
                ESTOP0;
            }
        }
        else
        {
#ifdef _TMS320C28X
            if (readData[index] != 0x20) {
#else
            if (readData[index] != 0x2020) {
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
            Test_trb_Handle,
            4*sizeof(uint16_t),
            0x20,
            4*sizeof(uint16_t));

    CHECK_RESULT(result);

    result = TransferRingBuffer_writePartialElementComplete(Test_trb_Handle);
    CHECK_RESULT(result);


    result = TransferRingBuffer_read(Test_trb_Handle, readData);
    CHECK_RESULT(result);

    for (index = 0; index < TEST_ELEMENT_SIZE; index++)
    {
        if (index >= 4 && index < 8)
        {
#ifdef _TMS320C28X
            if (readData[index] != 0x20){
#else
            if (readData[index] != 0x2020){
#endif
                //
                // Error
                //
                ESTOP0;
            }
        }
        else
        {
            if (readData[index] != 0) {
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

