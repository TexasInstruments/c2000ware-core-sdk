#include "transfer_ring_buffer_test.h"

#include "stdint.h"
#include "transfer_ringbuffer.h"
#include "stddef.h"


//
// 16bit vs 8bit arch tests
//
extern uint16_t readValidate(uint16_t * d, uint16_t * rd);


#define TESTARCH_BUFFER_SIZE 20
#define TESTARCH_ELEMENT_SIZE 10

void arch16bitTest(){
    uint16_t result = 0;

    uint16_t TestArch_buffer[TESTARCH_BUFFER_SIZE][TESTARCH_ELEMENT_SIZE] = {0};

    TransferRingBuffer TestArch_trb;
    TransferRingBuffer_Handle TestArch_trb_Handle = &TestArch_trb;
    uint16_t readData[TESTARCH_ELEMENT_SIZE] = {0};


    TransferRingBuffer_init(
            TestArch_trb_Handle,
            (uint16_t**)TestArch_buffer,
            TESTARCH_BUFFER_SIZE,
            sizeof(TestArch_buffer[0]));



    char data1[TESTARCH_ELEMENT_SIZE] = "ABCDEFGHIJ";

    //
    // Write data1 then read validate
    //
    result = TransferRingBuffer_write(TestArch_trb_Handle, data1);
    CHECK_RESULT(result);

    result = TransferRingBuffer_read(TestArch_trb_Handle, readData);
    CHECK_RESULT(result);

    result = readValidate((uint16_t *)data1, readData);

#ifdef _TMS320C28X
    // C2000 must pass
    CHECK_RESULT(result);
#else
    // 8-bits must fail
    CHECK_RESULT(!result);
#endif

    ESTOP0;

}
