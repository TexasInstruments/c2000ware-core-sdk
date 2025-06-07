//#############################################################################
//
// FILE:   launchxl_ex1_f280039c_demo.c
//
// TITLE:  F280039C LaunchPad Out of Box Demo Example
//
//! \addtogroup driver_example_list
//! <h1> F280039C LaunchPad Out of Box Demo Example </h1>
//!
//! This program is the demo program that comes pre-loaded on the F280039C
//! LaunchPad development kit. The program starts by flashing the two user
//! LEDs. After a few seconds the LEDs stop flashing and the device starts
//! sampling ADCINA6 once a second. If the sample is greater than midscale
//! the red LED on the board is lit, while if it is lower the green LED is lit.
//! Sample data is also displayed in a serial terminal via the board's back
//! channel UART. You may view this data by configuring a serial terminal
//! to the correct COM port at 115200 Baud 8-N-1.
//!
//! \b External \b Connections \n
//!  - Connect to COM port at 115200 Baud 8-N-1 for serial data
//!  - Connect signal to ADCINA6 to change LED based on value
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// Included Files
//
#include <stdint.h>
#include <stdio.h>
#include <file.h>
#include <launchxl_ex1_sci_io_driverlib.h>

#include "launchxl_ex1_ti_ascii.h"
#include "driverlib.h"
#include "device.h"

//
// Defines
//

//
// Select which SCI/UART pinout is desired -
// Must configure switch S2 on LaunchPad board accordingly
//
#define SCIPinout  0    // GPIO28/29
//#define SCIPinout  1    // GPIO15/56


//
// Globals
//
static unsigned short indexX=0;
static unsigned short indexY=0;

const unsigned char escRed[] = {0x1B, 0x5B, '3','1', 'm'};
const unsigned char escWhite[] = {0x1B, 0x5B, '3','7', 'm'};
const unsigned char escLeft[] = {0x1B, 0x5B, '3','7', 'm'};
const unsigned char pucTempString[] = "ADCINA6 Sample:     ";
int16_t currentSample;

//
// sampleADC - ADCINA6
//
int16_t sampleADC(void)
{
    int16_t sample;

    //
    // Force start of conversion on SOC0
    //
    ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER0);

    //
    // Wait for ADCA to complete, then acknowledge flag
    //
    while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1) == false)
    {
    }
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    //
    // Get ADC sample result from SOC0
    //
    sample = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);

    return(sample);
}

//
// drawTILogo - Draw the TI logo in the display
//
void drawTILogo(void)
{
    unsigned char ucChar, lastChar;

    putchar('\n');
    while(indexY<45)
    {
        if(indexY<45)
        {
            if(indexX<77)
            {
                ucChar = ti_ascii[indexY][indexX++] ;

                //
                // We are in the TI logo make it red
                //
				if((ucChar != '7') && (lastChar=='7'))
                {
                    putchar(escRed[0]);
                    putchar(escRed[1]);
                    putchar(escRed[2]);
                    putchar(escRed[3]);
                    putchar(escRed[4]);
                }

                //
                // We are in the TI logo make it red
                //
                if(ucChar == '7' && lastChar!='7')
                {
                    putchar(escWhite[0]);
                    putchar(escWhite[1]);
                    putchar(escWhite[2]);
                    putchar(escWhite[3]);
                    putchar(escWhite[4]);
                }

                putchar(ucChar);
                lastChar = ucChar;
            }

            else
            {
                ucChar = 10;
                putchar(ucChar);
                ucChar = 13;
                putchar(ucChar);
                indexX=0;
                indexY++;
            }
        }
    }
}

//
// clearTextBox - Clear the text box
//
void clearTextBox(void)
{
    putchar(0x08);

    //
    // Move back 24 columns
    //
    putchar(0x1B);
    putchar('[');
    putchar('2');
    putchar('6');
    putchar('D');

    //
    // Move up 3 lines
    //
    putchar(0x1B);
    putchar('[');
    putchar('3');
    putchar('A');

    //
    // Change to Red text
    //
    putchar(escRed[0]);
    putchar(escRed[1]);
    putchar(escRed[2]);
    putchar(escRed[3]);
    putchar(escRed[4]);

    printf((char*)pucTempString);

    //
    // Move down 1 lines
    //
    putchar(0x1B);
    putchar('[');
    putchar('1');
    putchar('B');

    //
    // Move back 20 columns
    //
    putchar(0x1B);
    putchar('[');
    putchar('2');
    putchar('0');
    putchar('D');

    //
    // Save cursor position
    //
    putchar(0x1B);
    putchar('[');
    putchar('s');
}

//
// updateDisplay - Update the serial display
//
void updateDisplay(void)
{
    //
    // Restore cursor position
    //
    putchar(0x1B);
    putchar('[');
    putchar('u');

    printf("%d                ", currentSample);
}

//
// scia_init - SCIA  8-bit word, baud rate 0x001A, default, 1 STOP bit,
// no parity
//
void scia_init()
{
    //
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
    //

    //
    // 1 stop bit,  No loopback, No parity,8 char bits, async mode,
    // idle-line protocol
    //
    SCI_performSoftwareReset(SCIA_BASE);

    SCI_setConfig(SCIA_BASE, DEVICE_LSPCLK_FREQ, 115200, (SCI_CONFIG_WLEN_8 |
                                                        SCI_CONFIG_STOP_ONE |
                                                        SCI_CONFIG_PAR_NONE));

    SCI_resetChannels(SCIA_BASE);
//    SCI_resetRxFIFO(SCIA_BASE);
//    SCI_resetTxFIFO(SCIA_BASE);
//    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_TXFF | SCI_INT_RXFF);
//    SCI_enableFIFO(SCIA_BASE);
    SCI_enableInterrupt(SCIA_BASE, SCI_INT_RXRDY_BRKDT | SCI_INT_TXRDY);
    SCI_enableModule(SCIA_BASE);
    SCI_performSoftwareReset(SCIA_BASE);

    return;
}

//
// initADCs - Function to configure and power up ADCs A and B.
//
void initADCs(void)
{
    //
    // Setup VREF as internal
    //
    ADC_setVREF(ADCA_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);

    //
    // Set ADCCLK divider to /4
    //
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);

    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);

    //
    // Power up the ADCs and then delay for 1 ms
    //
    ADC_enableConverter(ADCA_BASE);

    DEVICE_DELAY_US(1000);
}

//
// initADCSOCs - Function to configure SOC 0 of ADC A.
//
void initADCSOCs(void)
{
    //
    // Configure SOCs of ADCA
    // - SOC0 will convert pin A6 with a sample window of 10 SYSCLK cycles.
    //
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN6, 10);

    //
    // Set SOC0 to set the interrupt 1 flag. Enable the interrupt and make
    // sure its flag is cleared.
    //
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
}

//
// Main
//
void main()
{
    volatile int status = 0;
    uint16_t i;
    volatile FILE *fid;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // For this example, only init the pins for the SCI-A port.
    //
    EALLOW;
#if !SCIPinout
    //
    // GPIO28 is the SCI Rx pin.
    //

    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCIRXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_QUAL_ASYNC);

    //
    // GPIO29 is the SCI Tx pin.
    //

    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCITXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_QUAL_ASYNC);

#else
    //
    // GPIO15 is the SCI Rx pin.
    //

    GPIO_setPinConfig(DEVICE_GPIO_PIN_SCIRXDB);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCIRXDB, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCIRXDB, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCIRXDB, GPIO_QUAL_ASYNC);

    //
    // GPIO56 is the SCI Tx pin.
    //

    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDB);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCITXDB, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCITXDB, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCITXDB, GPIO_QUAL_ASYNC);
#endif

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Initialize SCIA
    //
    scia_init();

    //
    // Initialize GPIOs for the USER LEDs and turn them off
    // GPIO20 is LED4
    // GPIO22 is LED5
    //
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);

    // GPIO20 LED4 comes up in Analog mode by default, switch to Digital
    GPIO_setAnalogMode(DEVICE_GPIO_PIN_LED1, GPIO_ANALOG_DISABLED);

    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);

    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1);
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, 1);

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    //
    // Set up ADCs, initializing the SOCs to be triggered by software
    //
    initADCs();
    initADCSOCs();

    //
    // Redirect STDOUT to SCI
    //
    status = add_device("scia", _SSA, SCI_open, SCI_close, SCI_read, SCI_write,
                        SCI_lseek, SCI_unlink, SCI_rename);
    fid = fopen("scia","w");
    freopen("scia:", "w", stdout);
    setvbuf(stdout, NULL, _IONBF, 0);

    //
    // Print a TI Logo to STDOUT
    //
    drawTILogo();

    //
    // Twiddle LEDs
    //
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 0);
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, 1);

    for(i = 0; i < 50; i++)
    {
        GPIO_togglePin(DEVICE_GPIO_PIN_LED1);
        GPIO_togglePin(DEVICE_GPIO_PIN_LED2);
        DEVICE_DELAY_US(50000);
    }

    //
    // LEDs off
    //
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1);
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, 1);

    //
    // Clear out one of the text boxes so we can write more info to it
    //
    clearTextBox();

    currentSample = sampleADC();

    //
    // Main program loop - continually sample temperature
    //
    for(;;)
    {
        //
        // Sample ADCINA6
        //
        currentSample = sampleADC();

        //
        // Update the serial terminal output
        //
        updateDisplay();

        //
        // If the sample is above midscale light one LED
        //
        if(currentSample > 2048)
        {
            GPIO_writePin(DEVICE_GPIO_PIN_LED1, 0);
            GPIO_writePin(DEVICE_GPIO_PIN_LED2, 1);
        }
        else
        {
            //
            // Otherwise light the other
            //
            GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1);
            GPIO_writePin(DEVICE_GPIO_PIN_LED2, 0);
        }

        DEVICE_DELAY_US(1000000);
    }
}

//
// End of File
//
