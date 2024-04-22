//###########################################################################
//
// FILE:   hw_ints.h
//
// TITLE:  Definitions of interrupt numbers for use with interrupt.c.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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
//###########################################################################

#ifndef __HW_INTS_H__
#define __HW_INTS_H__

//
// f2806x PIE Interrupt Numbers
//
// 0xF0 = PIE Table Row #
// 0x0F = PIE Table Column #
//

#define INT_ADCINT1             0x11        //ADC Interrupt 1
#define INT_ADCINT2             0x12        //ADC Interrupt 2
#define INT_XINT1               0x14        //External Interrupt 1
#define INT_XINT2               0x15        //External Interrupt 2
#define INT_ADCINT9             0x16        //ADC Interrupt 9
#define INT_TINT0               0x17        //Timer Interrupt 0
#define INT_WAKEINT             0x18        //Wakeup Interrupt

#define INT_PWM1TZ              0x21        //PWM TZ Interrupt 1
#define INT_PWM2TZ              0x22        //PWM TZ Interrupt 2
#define INT_PWM3TZ              0x23        //PWM TZ Interrupt 3
#define INT_PWM4TZ              0x24        //PWM TZ Interrupt 4
#define INT_PWM5TZ              0x25        //PWM TZ Interrupt 5
#define INT_PWM6TZ              0x26        //PWM TZ Interrupt 6
#define INT_PWM7TZ              0x27        //PWM TZ Interrupt 7
#define INT_PWM8TZ              0x28        //PWM TZ Interrupt 8

#define INT_PWM1INT             0x31        //PWM Interrupt 1
#define INT_PWM2INT             0x32        //PWM Interrupt 2
#define INT_PWM3INT             0x33        //PWM Interrupt 3
#define INT_PWM4INT             0x34        //PWM Interrupt 4
#define INT_PWM5INT             0x35        //PWM Interrupt 5
#define INT_PWM6INT             0x36        //PWM Interrupt 6
#define INT_PWM7INT             0x37        //PWM Interrupt 7
#define INT_PWM8INT             0x38        //PWM Interrupt 8

#define INT_CAP1INT             0x41        //Capture Interrupt 1
#define INT_CAP2INT             0x42        //Capture Interrupt 2
#define INT_CAP3INT             0x43        //Capture Interrupt 3

//
// High Resolution Capture Interrupt 1
//
#define INT_HRCAP1INT           0x47        

//
// High Resolution Capture Interrupt 2
//
#define INT_HRCAP2INT           0x48        

#define INT_QEP1INT             0x51        //Quadrature Interrupt 1
#define INT_QEP2INT             0x52        //Quadrature Interrupt 2

//
// High Resolution Capture Interrupt 3
//
#define INT_HRCAP3INT           0x54        

//
// High Resolution Capture Interrupt 4
//
#define INT_HRCAP4INT           0x55        
#define INT_USB0INT             0x58        //USB Interrupt 0

#define INT_SPIRXINTA           0x61        //SPI-A Receive Interrupt
#define INT_SPITXINTA           0x62        //SPI-A Transmit Interrupt
#define INT_SPIRXINTB           0x63        //SPI-B Receive Interrupt
#define INT_SPITXINTB           0x64        //SPI-B Transmit Interrupt
#define INT_MRINTA              0x65        //McBSP-A Receieve Interrupt
#define INT_MXINTA              0x66        //McBSP-A Transmit Interrupt

#define INT_DMA1INT             0x71        //DMA Channel 1 Interrupt
#define INT_DMA2INT             0x72        //DMA Channel 2 Interrupt
#define INT_DMA3INT             0x73        //DMA Channel 3 Interrupt
#define INT_DMA4INT             0x74        //DMA Channel 4 Interrupt
#define INT_DMA5INT             0x75        //DMA Channel 5 Interrupt
#define INT_DMA6INT             0x76        //DMA Channel 6 Interrupt

#define INT_I2CINT1A            0x81        //I2C-A Basic Interrupts
#define INT_I2CINT2A            0x82        //I2C-A FIFO Interrupts

#define INT_SCIRXINTA           0x91        //SCI-A RX Interrupt
#define INT_SCITXINTA           0x92        //SCI-A TX Interrupt
#define INT_SCIRXINTB           0x93        //SCI-B RX Interrupt
#define INT_SCITXINTB           0x94        //SCI-B TX Interrupt
#define INT_CANINT0             0x95        //CAN 0 Interrupt
#define INT_CANINT1             0x96        //CAN 1 Interrupt

#define INT_ADCINT1n            0xA1        //ADC Interrupt 1
#define INT_ADCINT2n            0xA2        //ADC Interrupt 2
#define INT_ADCINT3n            0xA3        //ADC Interrupt 3
#define INT_ADCINT4n            0xA4        //ADC Interrupt 4
#define INT_ADCINT5n            0xA5        //ADC Interrupt 5
#define INT_ADCINT6n            0xA6        //ADC Interrupt 6
#define INT_ADCINT7n            0xA7        //ADC Interrupt 7
#define INT_ADCINT8n            0xA8        //ADC Interrupt 8

#define INT_CLAINT1             0xB1        //CLA Interrupt 1
#define INT_CLAINT2             0xB2        //CLA Interrupt 2
#define INT_CLAINT3             0xB3        //CLA Interrupt 3
#define INT_CLAINT4             0xB4        //CLA Interrupt 4
#define INT_CLAINT5             0xB5        //CLA Interrupt 5
#define INT_CLAINT6             0xB6        //CLA Interrupt 6
#define INT_CLAINT7             0xB7        //CLA Interrupt 7
#define INT_CLAINT8             0xB8        //CLA Interrupt 8

#define INT_XINT3               0xC1        //External Interrupt 3
#define INT_LVF                 0xC2        //Latched Overflow
#define INT_LUF                 0xC3        //Latched Underflow

//
// Workaround for  Stellaris code
//
#define INT_USB0                0x58          // USB 0 Controller

#endif // __HW_INTS_H__

//
// End of File
//

