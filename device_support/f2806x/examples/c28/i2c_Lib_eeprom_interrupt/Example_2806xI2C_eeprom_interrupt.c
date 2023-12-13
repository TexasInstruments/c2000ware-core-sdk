//###########################################################################
//
// FILE:   Example_2806xI2C_eeprom_interrupt.c
//
// TITLE:  I2C EEPROM FIFO Interrupt Example
//
//!  \addtogroup f2806x_example_list
//!  <h1>I2C EEPROM FIFO Interrupt Example (i2c_eeprom_polling)</h1>
//!
//!  This program requires an external I2C EEPROM connected to the I2C bus
//!  with address 0x50 (EEPROM_SLAVE_ADDRESS).
//!
//!  This program will write 1-64 bytes, configured with EEPROM_DATA_BYTES,
//!  to the I2C EEPROM and read them back using an interrupt based method.
//!  Writes to and reads from the I2C EEPROM are configured using the EEPROM
//!  I2CHandle. The I2CHandle and functions the struct can be passed to are
//!  defined in the i2cLib_FIFO_interrupt files.
//!
//!  The data written to the EEPROM is contained in the TX message buffer,
//!  \b TxMsgBuffer. The data read back will be contained in the RX message
//!  buffer, \b RxMsgBuffer.
//!
//!  \note This program will only work if an external I2C EEPROM is
//!  properly connected to the device's I2C SDA/SCL signals.
//!
//!  \b Watch \b Variables \n
//!  - TxMsgBuffer
//!  - RxMsgBuffer
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

// I2C defines and functions defined in 'i2cLib_FIFO_interrupt' files
#include "i2cLib_FIFO_interrupt.h"

//
// Function Prototypes
//
void I2CA_Init(void);

Uint16 compareData(Uint16 nBytes);
void pass(void);
void fail(void);

interrupt void i2cFIFO_isr(void);
interrupt void i2c_isr(void);

//
// Defines
//
#define EEPROM_SLAVE_ADDRESS        0x50
#define EEPROM_HIGH_ADDR            0x00
#define EEPROM_LOW_ADDR             0x00
#define EEPROM_READ_ATTEMPTS        10
#define EEPROM_DATA_BYTES           32

//
// Globals
//
struct I2CHandle EEPROM;

Uint16 TxMsgBuffer[MAX_BUFFER_SIZE];
Uint16 RxMsgBuffer[MAX_BUFFER_SIZE];
Uint16 ControlAddr[2];
Uint16 status;

//
// Variables used in i2cLib_FIFO_interrupt
//
struct I2CHandle *currentResponderPtr;

//
// Main
//
void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2806x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initalize GPIO:
    // This example function is found in the F2806x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    //InitGpio();
    
    //
    // Setup only the GP I/O only for I2C functionality
    //
    InitI2CGpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the F2806x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in F2806x_DefaultIsr.c.
    // This function is found in F2806x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.I2CINT1A = &i2c_isr;
    PieVectTable.I2CINT2A = &i2cFIFO_isr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in F2806x_InitPeripherals.c
    //
    //InitPeripherals(); // Not required for this example
    I2CA_Init();

    //
    // Enable I2C interrupt 1 and 2 in the PIE: Group 8
    //
    PieCtrlRegs.PIEIER8.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER8.bit.INTx2 = 1;

    //
    // Enable CPU INT8 which is connected to PIE group 8
    //
    IER |= M_INT8;
    EINT;

    //
    // Step 5. User specific code
    //
    Uint16 i;

    // Fill TX and RX buffer arrays
    for(i=0;i<MAX_BUFFER_SIZE;i++)
    {
        TxMsgBuffer[i] = i;
        RxMsgBuffer[i] = 0;
    }

    //
    // Set EEPROM byte addresses to write to and read from
    //
    ControlAddr[0] = EEPROM_HIGH_ADDR;
    ControlAddr[1] = EEPROM_LOW_ADDR;

    // Set I2CHandle EEPROM as current responder to be used in i2cFIFO_isr
    currentResponderPtr = &EEPROM;

    //
    // Configure EEPROM I2CHandle for Writing
    //
    EEPROM.SlaveAddr         = EEPROM_SLAVE_ADDRESS;
    EEPROM.pControlBuffer    = ControlAddr;
    EEPROM.NumOfControlBytes = 2;
    EEPROM.pMsgBuffer        = TxMsgBuffer;
    EEPROM.NumOfDataBytes    = EEPROM_DATA_BYTES;
    EEPROM.Timeout           = 100;

    //
    // Write data to EEPROM
    //
    status = I2C_MasterWrite(&EEPROM);

    if(status)
    {
        fail();
    }

    Uint16 I2C_timeout = 100;

    //
    // Wait for bytes to be transmitted.
    // Times out if takes too long.
    //
    while(I2caRegs.I2CSTR.bit.BB)
    {
        DELAY_US(1000);

        if(!I2C_timeout)
        {
            fail();
        }
        --I2C_timeout;
    }

    //
    // Configure EEPROM I2CHandle for Reading
    //
    EEPROM.pMsgBuffer     = RxMsgBuffer;
    EEPROM.NumOfDataBytes = EEPROM_DATA_BYTES;

    //
    // Read data back from EEPROM after write cycle time
    //
    for (i = 0; i < EEPROM_READ_ATTEMPTS; i++)
    {
        // Delay between read attempts during EEPROM write cycle time
        DELAY_US(1000);

        status = I2C_MasterRead(&EEPROM);

        if(status == SUCCESS)
        {
            break;
        }
    }

    I2C_timeout = 100;

    //
    // Wait for bytes to be received.
    // Times out if takes too long.
    //
    while(I2caRegs.I2CSTR.bit.BB)
    {
        DELAY_US(1000);

        if(!I2C_timeout)
        {
            fail();
        }
        --I2C_timeout;
    }

    //
    // Compare transmitted and received data
    //
    status = compareData(EEPROM.NumOfDataBytes);

    //
    // Pass if the written data matches the data read back.
    //
    if(status)
    {
        fail();
    }
    else
    {
        pass();
    }
}

//
// I2CA_Init - 
//
void
I2CA_Init(void)
{
    //
    // Initialize I2C
    //

    //
    // I2CCLK = SYSCLK/(I2CPSC+1)
    //
    I2caRegs.I2CPSC.all = 8;        // Prescaler - need 7-12 Mhz on module clk

    //
    // Configure I2CCLKL/I2CCLKH for 100KHz SCL clock
    // SCL Frequency = I2CCLK / ((I2CCLKL + d) + (I2CCLKH + d))
    //
    //    I2CPSC          |  d
    // -------------------|-----
    //    0               |  7
    //    1               |  6
    //    Greater than 1  |  5
    //
    I2caRegs.I2CCLKL = 45;          // NOTE: must be non zero
    I2caRegs.I2CCLKH = 45;          // NOTE: must be non zero

    I2caRegs.I2CIER.all = 0x0;      // Disable interrupts

    //
    // Take I2C out of reset. Stop I2C when suspended
    //
    I2caRegs.I2CMDR.all = 0x0020;	

    return;
}

//
// compareData - Compares if received data is same as transmitted data
//
Uint16 compareData(Uint16 nBytes)
{
    Uint16 i;

    for(i = 0; i < nBytes; i++)
    {
        if(TxMsgBuffer[i] != RxMsgBuffer[i])
        {
            return 0xFFFF;
        }
    }

    return SUCCESS;
}

//
// pass -
//
void
pass()
{
    __asm("   ESTOP0");
    for(;;);
}

//
// fail - 
//
void
fail(void)
{
    __asm("   ESTOP0");
    for(;;);
}

//
// End of File
//

