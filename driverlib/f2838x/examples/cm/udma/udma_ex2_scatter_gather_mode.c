//#############################################################################
//
// FILE:   udma_ex2_scatter_gather_mode.c
//
// TITLE:  uDMA RAM to RAM transfer using scatter gather mode
//
//! \addtogroup driver_example_cm_list
//! <h1>uDMA RAM to RAM transfer</h1>
//!
//! This example showcases how to configure uDMA in memory scatter-gather mode
//! and transfer data from varied locations in memory rather than a set of
//! contiguous locations in a memory buffer.
//!
//! This example creates an array of structs of length 20. The struct includes
//! a header element and a data element, each of length 10. The UDMA is 
//! configured to tranfer only the data element from all the 20 data packets.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b packets - 'data' element contains the actual data to be transferred
//!  - \b consolidatedData - Destination buffer where the data is transferred to
//!  - \b errCount - Error count
//!
//
//#############################################################################

#include "cm.h"
#include "stdlib.h"

#pragma DATA_ALIGN(ucControlTable, 1024)
UDMA_ControlTable ucControlTable[64];

#define DATA_LENGTH			 	10
#define HEADER_LENGTH 			10
#define TOTAL_NO_OF_PACKETS		20

//
// Define a data packet struct that includes a header and data.
//
typedef struct
{
    uint32_t header[HEADER_LENGTH];
    uint32_t data[DATA_LENGTH];
}DataPacket_t;

//
// Create an array of data packet struct of length 5
//
DataPacket_t packets[TOTAL_NO_OF_PACKETS];

//
// Memory buffer where the uDMA copies the data
//
uint32_t consolidatedData[TOTAL_NO_OF_PACKETS * DATA_LENGTH];

//
// uDMA task list used for scatter gather mode
//
UDMA_ControlTable tasklist[TOTAL_NO_OF_PACKETS];

uint32_t errCount;

//
// Main
//
void main(void)
{
    uint32_t i,j;

    //
    // Enable peripheral clocks
    //
    CM_init();

    //
    // Initialize the data package with dummy data
    //
    for(i = 0; i < TOTAL_NO_OF_PACKETS; i++)
    {
        //
        // Header is filled with random integers and the data is filled
        // with integers in sequence to check at the end.
        //
		for(j = 0; j < HEADER_LENGTH; j++)
        {
            packets[i].header[j] =  rand();
        }
		for(j = 0; j < DATA_LENGTH; j++)
        {
            packets[i].data[j]   =  (i * DATA_LENGTH) + j;
        }
    }

    //
    // Enable the uDMA controller.
    //
    UDMA_enable(UDMA_BASE);

    //
    // Point at the control table to use for channel control structures.
    //
    UDMA_setControlBase(UDMA_BASE, ucControlTable);

    //
    // Configure the task list
    // Each task is configured for transferring the data element of a single
    // data packet.
    // Item size, source address increment, destination address increment is
    // set as 32 and the data is collected in the memory buffer consolidatedData
    // in a continuous manner
    //
    for(i = 0; i < TOTAL_NO_OF_PACKETS; i++)
    {
        UDMA_ControlTable task =                                   
        UDMA_TASK_STRUCT_ENTRY(DATA_LENGTH,                        // Transfer count
                               UDMA_SIZE_32,                       // Item size
                               UDMA_SRC_INC_32,                    // Src Increment
                               packets[i].data,                    // Src Address
                               UDMA_DST_INC_32,                    // Dst Increment
                               &consolidatedData[i * DATA_LENGTH], // Dst Address
                               UDMA_ARB_8,                         // Arbitration
                               UDMA_MODE_MEM_SCATTER_GATHER);      // Transfer Mode

        memcpy(&tasklist[i], &task, sizeof(task));
    }

    //
    // Configure channel 0 for memory scatter gather mode. 
    //
    UDMA_setChannelScatterGatherMode(UDMA_BASE, UDMA_CHANNEL_30,
									 TOTAL_NO_OF_PACKETS, tasklist, false);

    //
    // Now the software channel is primed to start a transfer.  The channel
    // must be enabled.  For software based transfers, a request must be
    // issued.  After this, the uDMA memory transfer begins.
    //
    UDMA_enableChannel(UDMA_BASE, UDMA_CHANNEL_30);
    UDMA_requestSoftwareTransfer(UDMA_BASE, UDMA_CHANNEL_30);

    //
    // Wait until the transfer is complete
    //
    while(UDMA_isChannelEnabled(UDMA_BASE, UDMA_CHANNEL_30));

    //
    // Check the transferred data
    //
    for(i = 0; i < TOTAL_NO_OF_PACKETS * DATA_LENGTH; i++)
    {
        if(consolidatedData[i] != i)
        {
            errCount++;
        }
    }
    while(1);
}
