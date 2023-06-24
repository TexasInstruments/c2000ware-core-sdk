//#############################################################################
//
// FILE:    can_ex11_error_generation.c
//
// TITLE:   CAN Error Generation over GPIO Example 
//
//! \addtogroup driver_example_list
//! <h1> CAN Error Generation Example </h1>
//!
//! 
//! This example demonstrates the ways of handling CAN Error conditions
//! It generates the CAN Packets and sends them over GPIO
//! It is looped back externally to be received in CAN module
//! The CAN Interrupt service routine reads the Error status and 
//! demonstrates how different Error conditions can be detected
//! 
//! Change ERR_CFG define to the different Error Scenarios and run the 
//! example. The corresponding Error Flag will be set in status variable
//! of canaISR() routine.
//! Uses a CPU Timer(Timer 0) for periodic timer interrupt of CANBITRATE uSec
//! On the Timer interrupt it sends the required CAN Frame type with 
//! the specified error conditions
//! \note CAN modules on the device need to be connected to via CAN
//!       transceivers.
//!
//! Please refer to the application note titled "Configurable Error Generator
//! for Controller Area Network" at www.ti.com/lit/pdf/spracq3 for further 
//! details on this example
//!
//! \b External \b Connections \n
//!  - ControlCARD GPIOTX_PIN(GPIO4) should be connected to GPIO5(CANRXA)
//!
//! \b Watch \b Variables \b Transmit \Configuration \n
//!  - status   - variable in canaISR for checking error Status
//!
//
//#############################################################################
//! 

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

volatile uint32_t rxMsgCount = 0;
volatile uint32_t errorFlag = 0;
uint16_t txMsgData[8], rxMsgData[8]= {0,0,0,0,0,0,0,0};

//
// Function Prototypes
//
int16_t generateCANFrame(uint32_t errCfg, int16_t remote_frame, int16_t bitNErr,
                     int16_t dataByteNum, int16_t gpio);
void selectGPIO(int16_t gpio);
void initCPUTimers(void);
void configCPUTimer(uint32_t cpuTimer, float freq, float bitrate);

//
//Interrupt Service Routines
//
__interrupt void canaISR(void);
__interrupt void cpuTimer0ISR(void);

//
//Global Variables
//
int16_t         stream[200];
uint32_t    canstream[200];
uint16_t    crcRg;
int16_t         crcNext,nbits,samebits;
int16_t         nxtBit, prev_bit, canBit=0;
uint32_t    arbID;
int16_t         bitpos=0, errpos=0, stuffbits=0;

#define TX_MSG_OBJ_ID    1
#define RX_MSG_OBJ_ID    2

// Definitions - do not change values in this section
#define CAN_FRAME               0
#define REMOTE_REQUEST          1
#define CAN_GPIO_MODE           0
#define CAN_DATALBCK_MODE       1

//
// CAN error definitions
// Use any of these defines for ERR_CFG 
//
//No Error is generated for this define
//
#define NO_ERR                  0
//
//Bit 0/ CRC Error is generated for this Error define
//
#define FF_SRS_ERR              1
//
//Form Error is generated for this Error define
//
#define FF_IDE_ERR              2
//
//Form Error is generated for this Error define
//
#define FF_RTR_ERR              3
//
//Bit 0/ CRC Error is generated for this Error define
//
#define FF_R1_ERR               4
//
//Bit 0/ CRC Error is generated for this Error define
//
#define FF_R0_ERR               5
//
//Bit 0/ CRC Error is generated for this Error define
//
#define MSGID_ERR               6
//
//Bit 0/ CRC Error is generated for this Error define
//
#define DATA_ERR                8
//
//Bit 0/ CRC Error is generated for this Error define
//
#define CRC_ERR                 9
//
//Form Error is generated for this Error define
//
#define STUFF_BITS_ERR          10

//
//Default No Error
//Change this NO_ERR to required Error Type as above
//
#define ERR_CFG                 FF_IDE_ERR

// Message data length
#define MSG_DATA_LENGTH         4
// CAN bit rate
#define CANBITRATE              500000

// Define if GPIO CAN Frame Emulation (CAN_GPIO_MODE) or Internal CAN Data Loopback mode (CAN_DATALBCK_MODE)
// CAN_GPIO_MODE: GPIOTX_PIN will output the emulated CAN frame which can be observed externally
// CAN_DATALBCK_MODE: The GPIO mapped to CANRX_PAD will receive the emulated CAN frame internally.  Using this
//          mode will not allow for external monitoring of emulated CAN frames.  The CANRX_PAD defined should be
//          driven high when in this mode either externally or through the internal pull up.
#define CAN_EMULATION_MODE      CAN_GPIO_MODE


// CAN channel setup
// GPIO Pin to emulate CAN bit stream
#define GPIOTX_PIN              4

// GPIO assignment for CANRX
#define CANRX_PAD               GPIO_5_CANRXA

// GPIOPORT and PIN calculation from channel assignments
#define GPIOPORT                (GPIOTX_PIN/32)
#define GPIORX_PIN  ((((CANRX_PAD >> 8) & 0xFFU) + ((CANRX_PAD >> 16) - 0x6U))>>1)

//
// Main
//
void main(void)
{
    int16_t frame_length;

    //
    // Initialize System Control and device clock and peripherals
    //
    Device_init();

    //
    // Configure GPIO pin that will be emulated as CANTX
    //
    GPIO_setPinConfig(GPIO_4_GPIO4);
    
    //
    // Initialize CAN DATA
    //
    arbID = 0x1914A75B;

    txMsgData[0] = 0x95;
    txMsgData[1] = 0x1A;
    txMsgData[2] = 0x23;
    txMsgData[3] = 0x45;
    txMsgData[4] = 0x67;
    txMsgData[5] = 0x89;
    txMsgData[6] = 0xAB;
    txMsgData[7] = 0xCD;

    frame_length = generateCANFrame(ERR_CFG, CAN_FRAME, 0, 0, GPIOTX_PIN);

    GPIO_setPinConfig(CANRX_PAD);

    CAN_initModule(CANA_BASE);

    CAN_setBitRate(CANA_BASE, DEVICE_SYSCLK_FREQ, CANBITRATE, 20);

    CAN_enableInterrupt(CANA_BASE, CAN_INT_IE0 | CAN_INT_ERROR |
                        CAN_INT_STATUS);

    //
    // Initialize PIE, clear PIE registers, disable and clear all
    // CPU interrupts and flags
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    // This registers the interrupt handler in PIE vector table.
    //
    Interrupt_register(INT_CANA0, &canaISR);
    Interrupt_register(INT_TIMER0, &cpuTimer0ISR);

    //
    // Initializes the Device Peripheral. For this example, only initialize the
    // Cpu Timers.
    //
    initCPUTimers();

    //
    // Configure CPU-Timer 0  interrupt every second:
    // CANBITRATE Period (in uSeconds)
    //
    configCPUTimer(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ, CANBITRATE);

    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in configCPUTimer and initCPUTimers, the below settings must also
    // be updated.
    //
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);

    //
    // Enables CPU int1 which is connected to CPU-Timer 0,
    // Enable TINT0 in the PIE: Group 1 interrupt 7
    //
    Interrupt_enable(INT_TIMER0);

    //
    // Enable the CAN interrupt signal
    //
    Interrupt_enable(INT_CANA0);
    CAN_enableGlobalInterrupt(CANA_BASE, CAN_GLOBAL_INT_CANINT0);

    //
    //RX set up
    //
    CAN_setupMessageObject(CANA_BASE, RX_MSG_OBJ_ID, arbID, CAN_MSG_FRAME_EXT,
                           CAN_MSG_OBJ_TYPE_RX, 0, CAN_MSG_OBJ_RX_INT_ENABLE,
                           MSG_DATA_LENGTH);

    //
    // Start CAN module operations
    //
    CAN_startModule(CANA_BASE);

    canBit = 0;
    
    //
    // Start CPU-Timer 0
    //
    CPUTimer_startTimer(CPUTIMER0_BASE);

    for(;;)
    {
        if(canBit >= frame_length)
            canBit = 0;
    }
}



int16_t generateCANFrame(uint32_t errCfg, int16_t remote_frame,
                     int16_t bitNErr, int16_t dataByteNum, int16_t gpio)
{
    uint32_t i, j, idLSB, idMSB;
    int16_t xtd, idndx, dlcndx, datndx, nstuffbits;

    // initialize stream and canstream
    for(i = 0;i < 200;i++)
    {
        stream[i] = -1;
        canstream[i] = 0xFFFFFFFF;
    }

    // arbID
    if(arbID > 0x7FF)
    {
        idLSB = arbID & 0x3FFFF;
        idMSB = ((arbID & 0x1FFFFFFF) >> 18) & 0x7FF;

        stream[0] = 0;
        for(i = 0;i < 11;i++) 
          stream[1 + i] = ((idMSB >> (10 - i)) & 1)?1:0;
        // SRS bit position
        if(errCfg == FF_SRS_ERR)
            bitpos = i + 1;
        // SRS bit
        stream[1 + i] = 1;
        // IDE bit position
        if(errCfg == FF_IDE_ERR)
            bitpos = i + 2;
        // IDE bit
        stream[2 + i] = 1;
        for(i = 0;i < 18;i++) 
           stream[14 + i]=((idLSB >> (17 - i)) & 1 )?1:0;

        idndx = 32;
        xtd = 1;

    }
    else
    {
        idLSB = arbID & 0x7FF;
        stream[0] = 0;
        for(i = 0;i < 11;i++)
            stream[1 + i] = ((idLSB >> (10 -i )) & 1) ? 1:0;

        idndx = 12;
        xtd = 0;
    }
    // If errCfg value is MSGID_ERR, or DATA_ERR or CRC_ERR, ensure that bitNErr is valid
    if(errCfg == MSGID_ERR)
    {
        if(arbID > 0x7FF)
        {
            if(bitNErr > 28)
            // bitNErr VALUE is not valid - change to valid value
                ESTOP0;
        }
        else
        {
            if(bitNErr > 11)
            // bitNErr VALUE is not valid - change to valid value
                ESTOP0;
        }
    }
    
    //
    //If errCfg value is DATA_ERR
    //check for valid bit position bitNErr and dataByteNum value
    //
    if(errCfg == DATA_ERR)
    {
        if(dataByteNum > (MSG_DATA_LENGTH - 1))
            // dataByteNum value is not valid - change to valid value
            ESTOP0;
        if(bitNErr > 7)
            // bitNErr value is not valid - change to valid value
            ESTOP0;
    }
    // if errCfg value is CRC_ERR, check for valid bit position bitNErr
    if(errCfg == DATA_ERR)
    {
        if(bitNErr > 14)
            // bitNErr value is not valid - change to valid value
            ESTOP0;
    }

    //RTR, r1, r0 = 0 for now
    // RTR bit position
    if(errCfg == FF_RTR_ERR) bitpos = idndx;
    // RTR bit
    stream[idndx] = (!remote_frame)?0:1;
    // R1 bit position
    if(errCfg == FF_R1_ERR)
        bitpos = idndx + 1;
    // R1 bit
    stream[idndx + 1] = 0;
    // R0 bit position
    if(errCfg==FF_R0_ERR)
        bitpos = idndx + 2;
    // R0 bit
    stream[idndx + 2] = 0;

    //DLC
    dlcndx = (xtd)?35:15;
    for(i = 0;i < 4;i++)
        stream[dlcndx + i]=((MSG_DATA_LENGTH >> (3 - i)) & 1)? 1: 0;
    //DATA (up to 8 bytes
    if(!remote_frame)
    {
        datndx = (xtd)?39:19;
        for(i = 0;i < MSG_DATA_LENGTH;i++)
        {
            for(j=0;j<8;j++)
                stream[datndx + (i * 8) + j] =
                    ((txMsgData[i] >> (7 - j)) & 1)?1:0;
        }
    }

    //determine how long the bitstream is
    i = 0;
    nxtBit = stream[i];
    while(nxtBit == 0 || nxtBit == 1) 
        nxtBit=stream[i++];
    nbits=--i;

   crcRg = 0;
    for(i = 0;i < nbits;i++)
    {
            nxtBit = stream[i];
            crcNext = nxtBit ^ ((crcRg & 0x4000) >> 14);
            crcRg=(crcRg << 1) & 0x7FFE;
            if(crcNext)
            {
                crcRg = crcRg ^ 0x4599; // CAN-15 CRC polynomial
            }
    }

    // Invert bitNErr position in MSGID
    if(errCfg == MSGID_ERR)
    {
        bitpos = idndx - 1 - bitNErr;
        stream[bitpos] = (stream[bitpos] == 1)?0:1;

    }

    // SRS ERROR
    if(errCfg == FF_SRS_ERR)
        stream[bitpos] = 0;
    // IDE ERROR
    if(errCfg == FF_IDE_ERR)
        stream[bitpos] = 0;
    // RTR ERROR
    if(errCfg == FF_RTR_ERR)
        stream[bitpos] = 1;
    // R1 ERROR
    if(errCfg == FF_R1_ERR)
        stream[bitpos] = 1;
    // R0 ERROR
    if(errCfg == FF_R0_ERR)
        stream[bitpos] = 1;

    // Invert bitNErr position in the data byte pointed by dataByteNum
    if(errCfg == DATA_ERR)
    {
        bitpos = datndx + (7 - bitNErr) + (dataByteNum * 8);
        stream[bitpos] = (stream[bitpos] == 1)?0:1;
    }

    //Append CRC bits (15) + delimiter
    for(i = 0;i < 15;i++)
    {
        stream[nbits + i]=((crcRg >> (14 - i)) & 1)?1:0;
    }

    // add CRC delimiter
    stream[nbits + i] = 1;
    nbits += 1;

    // Invert bitNErr position in the 15-bit CRC
    if(errCfg==CRC_ERR)
    {
        bitpos = nbits + 13 - bitNErr;
        stream[bitpos] = stream[bitpos] == 1?0:1;
    }

    //
    //Stuff bits: check for 5 consecutive bit states 
    //then insert opposite bit state if this occurs
    //
    prev_bit = stream[0];
    canstream[0] = stream[0];
    j = 1;
    samebits = 0;
    nstuffbits = 0;
    for(i = 1;i < (nbits + 15);i++)
    {
        canstream[j++] = stream[i];
        //determine position of flipped bit
        if(i == bitpos)
            errpos = j - 1;
        if(prev_bit == stream[i])
        {
            if(!samebits)
                samebits = 2;
            else
                samebits++;
            
            if(samebits == 5)
            {
                if(errCfg != STUFF_BITS_ERR)
                    canstream[j++] = (stream[i] == 1) ? 0:1;
                samebits = 0;
                nstuffbits++;
            }
        }
        else
        {
             samebits = 0;
        }
        prev_bit = canstream[j - 1];
    }
    stuffbits = nstuffbits;
    i = 0;
    nxtBit = canstream[i];
    while(nxtBit == 0 || nxtBit == 1)
        nxtBit=canstream[i++];
    nbits=--i;

    // Append 20 recessive bits at the end of the bitstream
    for(i = 0;i < 14;i++) 
        if(i==0)
            canstream[nbits + i] = 0;
        else
            canstream[nbits + i] = 1;

    // format stream as 32-bit location
    for(i = 0;i <(nbits + 14);i++)
    {
        if(CAN_EMULATION_MODE==CAN_GPIO_MODE)
        {
            if(gpio <= 15)
            {
                canstream[i] = (canstream[i]==1)?(uint32_t)(1 << gpio):0;
            }
            if(gpio > 15 && gpio <= 31)
            {
                canstream[i] = 
                  (canstream[i]==1) ?
                    (uint32_t)(0x10000 << (gpio - 16)) : 0;

            }
            if(gpio > 31 && gpio <= 44)
            {
                canstream[i] =
                   (canstream[i] == 1) ?(uint32_t)( 1 << (gpio - 32)):0;
            }
        }
        else
            canstream[i] = (canstream[i]==0) ? 
                            GPIO_PIN_TYPE_INVERT : GPIO_PIN_TYPE_STD;

    }

    return (nbits + 14);
}

//
// initCPUTimers - This function initializes all three CPU timers
// to a known state.
//
void
initCPUTimers(void)
{
    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(CPUTIMER0_BASE, 0xFFFFFFFF);

    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);

    //
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    //
    // Reload all counter register with period value
    //
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);

}

//
// configCPUTimer - This function initializes the selected timer to the
// period specified by the "freq" and "period" parameters. The "freq" is
// entered as Hz and the period in uSeconds. The timer is held in the stopped
// state after configuration.
//
void
configCPUTimer(uint32_t cpuTimer, float freq, float bitrate)
{
    uint32_t temp;

    //
    // Initialize timer period:
    //
    temp = (uint32_t)(freq / bitrate);
    CPUTimer_setPeriod(cpuTimer, temp);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);

}

__interrupt void
canaISR(void)
{
    uint32_t status;

    //
    // Read the CAN-A interrupt status to find the cause of the interrupt
    //
    status = CAN_getInterruptCause(CANA_BASE);

    //
    // If the cause is a controller status interrupt, then get the status
    //
    if(status == CAN_INT_INT0ID_STATUS)
    {
        //
        // Read the controller status.  This will return a field of status
        // error bits that can indicate various errors.  Error processing
        // is not done in this example for simplicity.  Refer to the
        // API documentation for details about the error status bits.
        // The act of reading this status will clear the interrupt.
        //
        status = CAN_getStatus(CANA_BASE);
        // uncomment below in order to inspect LEC in CAN_ES
        //ESTOP0;


        //
        // Check to see if an error occurred.
        //
        if(((status  & ~(CAN_STATUS_RXOK)) != CAN_STATUS_LEC_MSK) &&
           ((status  & ~(CAN_STATUS_RXOK)) != CAN_STATUS_LEC_NONE))
        {
            //
            // Set a flag to indicate some errors may have occurred.
            //
            errorFlag = 1;
            // uncomment below in order to inspect LEC in CAN_ES if error occurs
            //ESTOP0;
        }
    }
    //
    // Check if the cause is the CAN-B receive message object 1
    //
    else if(status == RX_MSG_OBJ_ID)
    {
        //
        // Get the received message
        //
        CAN_readMessage(CANA_BASE, RX_MSG_OBJ_ID, rxMsgData);

        //
        // Getting to this point means that the RX interrupt occurred on
        // message object 1, and the message RX is complete.  Clear the
        // message object interrupt.
        //
        CAN_clearInterruptStatus(CANA_BASE, RX_MSG_OBJ_ID);

        //
        // Increment a counter to keep track of how many messages have been
        // received. In a real application this could be used to set flags to
        // indicate when a message is received.
        //
        rxMsgCount++;

        //
        // Since the message was received, clear any error flags.
        //
        errorFlag = 0;
    }
    //
    // If something unexpected caused the interrupt, this would handle it.
    //
    else
    {
        //
        // Spurious interrupt handling can go here.
        //
    }

    //
    // Clear the global interrupt flag for the CAN interrupt line
    //
    CAN_clearGlobalInterruptStatus(CANA_BASE, CAN_GLOBAL_INT_CANINT0);

    //
    // Acknowledge this interrupt located in group 9
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
    //ESTOP0;

}

//
// cpuTimer0ISR - Counter for CpuTimer0
//
__interrupt void
cpuTimer0ISR(void)
{

    //
    // Write canstream data to GPIO port selected
    //
    if (CAN_EMULATION_MODE == CAN_GPIO_MODE)
        GPIO_writePortData((GPIO_Port)GPIOPORT, canstream[canBit++]);
    else
        GPIO_setPadConfig(GPIORX_PIN, canstream[canBit++]);
    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}


//
// End of File
//
