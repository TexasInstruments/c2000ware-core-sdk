//#############################################################################
//
// FILE:   udma_ex1_software_trigger.c
//
// TITLE:  uDMA RAM to RAM transfer using software trigger
//
//! \addtogroup driver_example_cm_list
//! <h1>uDMA RAM to RAM transfer</h1>
//!
//! This example showcases how to use uDMA to transfer data from one RAM
//! location to another using software trigger.
//!
//! This configures the UDMA in AUTO mode and transfers 32-bit words from
//! one location to another using Channel 30. Software trigger is being used
//! here. Once the transfer is completed, a check of the validity of the data
//! will be performed in the uDMA ISR.
//!
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b srcData - Source
//!  - \b destData - Destination
//!  - \b errCount - Error count
//!
//
//#############################################################################

#include "cm.h"

#define TRANSFER_SIZE 20


void udmaISR(void);

uint32_t srcData[TRANSFER_SIZE], destData[TRANSFER_SIZE];
uint8_t errCount = 0xFF;

#pragma DATA_ALIGN(ucControlTable, 1024)
UDMA_ControlTable ucControlTable[64];

//
// Main
//
void main(void)
{
    int i;

    //
    // Enable peripheral clocks
    //
    CM_init();

    //
    // Initialize the source and destination arrays
    //
    for(i = 0; i < TRANSFER_SIZE; i++)
    {
        srcData[i] = i;
        destData[i] = 0;
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
    // Enable interrupts from the uDMA software channel.
    //
    UDMA_registerInterrupt(UDMA_SW_INT, udmaISR);

    //
    // Put the attributes in a known state for the uDMA software channel.
    // These should already be disabled by default.
    //
    UDMA_disableChannelAttribute(UDMA_BASE, UDMA_CHANNEL_SW_CH30, UDMA_CH_ATTR_ALL);

    //
    // Configure the control parameters for the SW channel.  The SW channel
    // will be used to transfer between two memory buffers, 32 bits at a time.
    // Therefore the data size is 32 bits, and the address increment is 32 bits
    // for both source and destination.  The arbitration size will be set to 4,
    // which causes the uDMA controller to rearbitrate after 8 items are
    // transferred.  This keeps this channel from hogging the uDMA controller
    // once the transfer is started, and allows other channels cycles if they
    // are higher priority.
    //
    UDMA_setChannelControlParams(UDMA_BASE, UDMA_CHANNEL_SW_CH30,
                                 UDMA_SIZE_32 | UDMA_SRC_INC_32 | UDMA_DST_INC_32
                                 | UDMA_ARB_4);

    //
    // Set up the transfer parameters for the software channel.  This will
    // configure the transfer buffers and the transfer size.  Auto mode must be
    // used for software transfers.
    //
    UDMA_setChannelTransferParams(UDMA_BASE, UDMA_CHANNEL_SW_CH30,
                                  srcData, destData, UDMA_MODE_AUTO, TRANSFER_SIZE);

    //
    // Now the software channel is primed to start a transfer.  The channel
    // must be enabled.  For software based transfers, a request must be
    // issued.  After this, the uDMA memory transfer begins.
    //
    UDMA_enableChannel(UDMA_BASE, UDMA_CHANNEL_SW_CH30);
    UDMA_requestSoftwareTransfer(UDMA_BASE, UDMA_CHANNEL_SW_CH30);

    while(1);
}

__interrupt void udmaISR(void)
{
    int i;

	errCount = 0;

	for(i = 0; i < TRANSFER_SIZE; i++)
    {
        if(srcData[i] != destData[i])
        {
            errCount++;
        }
    }
}
