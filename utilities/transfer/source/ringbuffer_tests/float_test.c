#include "transfer_ring_buffer_test.h"

#include "stdint.h"
#include "transfer_ringbuffer.h"
#include "stddef.h"
#include "string.h"

//
// Float
//
#define TESTFLOAT_BUFFER_SIZE 20
#define TESTFLOAT_ELEMENT_SIZE 10


uint16_t readFloatValidate(float * d, float * rd)
{
    uint16_t i = 0;
    for (i = 0; i < TESTFLOAT_ELEMENT_SIZE; i++)
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

void floatTest(){
    uint16_t result = 0;
    uint16_t index = 0;

    float TestFloat_buffer[TESTFLOAT_BUFFER_SIZE][TESTFLOAT_ELEMENT_SIZE] = {0};

    TransferRingBuffer TestFloat_trb;
    TransferRingBuffer_Handle TestFloat_trb_Handle = &TestFloat_trb;
    float readFloatData[TESTFLOAT_ELEMENT_SIZE] = {0};

    TransferRingBuffer_init(
            TestFloat_trb_Handle,
            (uint16_t**)TestFloat_buffer,
            TESTFLOAT_BUFFER_SIZE,
            sizeof(TestFloat_buffer[0]));


    result = TransferRingBuffer_full(TestFloat_trb_Handle);
    if (result)
    {
        // Error
        ESTOP0;
    }
    result = TransferRingBuffer_empty(TestFloat_trb_Handle);
    if (!result)
    {
        // Error
        ESTOP0;
    }

    float data1Float[TESTFLOAT_ELEMENT_SIZE] = {0.34, 1.3, 2.3, 3.5, 4.6, 5.7, 6.8, 7, 8, 9};
    float data2Float[TESTFLOAT_ELEMENT_SIZE] = {15.13, 1.45, 2, 3, 4, 5, 6, 7, 8, 9};
    float data3Float[TESTFLOAT_ELEMENT_SIZE] = {16.42, 1.33, 2.021, 3, 4, 5, 6, 7, 8, 9};

    //
    // Write data1 then read validate
    //
    result = TransferRingBuffer_write(TestFloat_trb_Handle, data1Float);
    CHECK_RESULT(result);

    result = TransferRingBuffer_read(TestFloat_trb_Handle, readFloatData);
    CHECK_RESULT(result);

    result = readFloatValidate(data1Float, readFloatData);
    CHECK_RESULT(result);

    //
    // Write data2Float and data3Float (write two in a row) then validate
    //
    result = TransferRingBuffer_write(TestFloat_trb_Handle, data2Float);
    CHECK_RESULT(result);
    result = TransferRingBuffer_write(TestFloat_trb_Handle, data3Float);
    CHECK_RESULT(result);

    result = TransferRingBuffer_read(TestFloat_trb_Handle, readFloatData);
    CHECK_RESULT(result);
    result = readFloatValidate(data2Float, readFloatData);
    CHECK_RESULT(result);
    result = TransferRingBuffer_read(TestFloat_trb_Handle, readFloatData);
    CHECK_RESULT(result);
    result = readFloatValidate(data3Float, readFloatData);
    CHECK_RESULT(result);


    //
    // Write till full
    //
    result = TransferRingBuffer_empty(TestFloat_trb_Handle);
    if (!result)
    {
        // Error
        ESTOP0;
    }

    for (index = 0; index < (TESTFLOAT_BUFFER_SIZE - 1); index++)
    {
        result = TransferRingBuffer_write(TestFloat_trb_Handle, data1Float);
        CHECK_RESULT(result);

        // Should not be full yet
        result = TransferRingBuffer_full(TestFloat_trb_Handle);
        if (result)
        {
            // Error
            ESTOP0;
        }

        // Should not be empty
        result = TransferRingBuffer_empty(TestFloat_trb_Handle);
        if (result)
        {
            // Error
            ESTOP0;
        }

    }
    result = TransferRingBuffer_write(TestFloat_trb_Handle, data1Float);
    CHECK_RESULT(result);
    // Now it should be full
    result = TransferRingBuffer_full(TestFloat_trb_Handle);
    CHECK_RESULT(result);
    // Next write should fail
    result = TransferRingBuffer_write(TestFloat_trb_Handle, data1Float);
    if (result)
    {
        // Error
        ESTOP0;
    }

    // Now read to all except last
    for (index = 0; index < (TESTFLOAT_BUFFER_SIZE - 1); index++)
    {
        result = TransferRingBuffer_read(TestFloat_trb_Handle, readFloatData);
        CHECK_RESULT(result);
        result = readFloatValidate(data1Float, readFloatData);
        CHECK_RESULT(result);

        // Should not be full yet
        result = TransferRingBuffer_full(TestFloat_trb_Handle);
        if (result)
        {
            // Error
            ESTOP0;
        }

        // Should not be empty
        result = TransferRingBuffer_empty(TestFloat_trb_Handle);
        if (result)
        {
            // Error
            ESTOP0;
        }

    }
    result = TransferRingBuffer_read(TestFloat_trb_Handle, readFloatData);
    CHECK_RESULT(result);
    result = readFloatValidate(data1Float, readFloatData);
    CHECK_RESULT(result);
    // Now it should be empty
    result = TransferRingBuffer_empty(TestFloat_trb_Handle);
    CHECK_RESULT(result);
    // Next read should fail
    result = TransferRingBuffer_read(TestFloat_trb_Handle, readFloatData);
    if (result)
    {
        // Error
        ESTOP0;
    }



    //
    // Partial element tests
    //
    // Clear the TestBuffer
    memset(TestFloat_buffer, 0, sizeof(TestFloat_buffer));
    TestFloat_trb.writeIndex = 0;
    TestFloat_trb.readIndex = 0;
    TestFloat_trb.isFull = 0;

    float partialData1[] = {33.43, 42.32, 22.66, 23.44, 46.78, 7895.96, 4900.97, 44.55, 55.44, 88.02};
    result = TransferRingBuffer_writePartialElement(
            TestFloat_trb_Handle,
            3*sizeof(float),
            partialData1 + 3,
            7*sizeof(float));
    CHECK_RESULT(result);

    result = TransferRingBuffer_writePartialElement(
            TestFloat_trb_Handle,
            0,
            partialData1,
            3*sizeof(float));
    CHECK_RESULT(result);

    result = TransferRingBuffer_writePartialElementComplete(TestFloat_trb_Handle);
    CHECK_RESULT(result);

    float partialData2[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10};
    result = TransferRingBuffer_writePartialElement(
            TestFloat_trb_Handle,
            4*sizeof(float),
            partialData2 + 4,
            6*sizeof(float));
    CHECK_RESULT(result);

    result = TransferRingBuffer_writePartialElement(
            TestFloat_trb_Handle,
            0,
            partialData2,
            4*sizeof(float));
    CHECK_RESULT(result);


    result = TransferRingBuffer_writePartialElementComplete(TestFloat_trb_Handle);
    CHECK_RESULT(result);

    result = TransferRingBuffer_read(TestFloat_trb_Handle, readFloatData);
    CHECK_RESULT(result);
    result = readFloatValidate(partialData1, readFloatData);
    CHECK_RESULT(result);

    result = TransferRingBuffer_read(TestFloat_trb_Handle, readFloatData);
    CHECK_RESULT(result);
    result = readFloatValidate(partialData2, readFloatData);
    CHECK_RESULT(result);

    //
    // Basic write and read validated
    //
    // Now let validate write with PAD.
    //
    result = TransferRingBuffer_writeWithPad(
            TestFloat_trb_Handle,
            partialData1,
            4*sizeof(float),
            0x20);

    float padVal = 0;
    memset(&padVal, 0x20, sizeof(float));

    CHECK_RESULT(result);

    result = TransferRingBuffer_read(TestFloat_trb_Handle, readFloatData);
    CHECK_RESULT(result);

    for (index = 0; index < TESTFLOAT_ELEMENT_SIZE; index++)
    {
        if (index < 4)
        {
            if (partialData1[index] != readFloatData[index]){
                //
                // Error
                //
                ESTOP0;
            }
        }
        else
        {
#ifdef _TMS320C28X
            if (readFloatData[index] != padVal) {
#else
            if (readFloatData[index] != padVal) {
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
            TestFloat_trb_Handle,
            4*sizeof(float),
            0x20,
            4*sizeof(float));

    CHECK_RESULT(result);

    result = TransferRingBuffer_writePartialElementComplete(TestFloat_trb_Handle);
    CHECK_RESULT(result);


    result = TransferRingBuffer_read(TestFloat_trb_Handle, readFloatData);
    CHECK_RESULT(result);

    for (index = 0; index < TESTFLOAT_ELEMENT_SIZE; index++)
    {
        if (index >= 4 && index < 8)
        {
#ifdef _TMS320C28X
            if (readFloatData[index] != padVal){
#else
            if (readFloatData[index] != padVal){
#endif
                //
                // Error
                //
                ESTOP0;
            }
        }
        else
        {
            if (readFloatData[index] != 0) {
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
