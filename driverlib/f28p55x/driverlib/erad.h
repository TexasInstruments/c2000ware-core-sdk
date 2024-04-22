//###########################################################################
//
// FILE:   erad.h
//
// TITLE:  C28x ERAD driver.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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

#ifndef ERAD_H
#define ERAD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup erad_api ERAD
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_erad.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// Useful defines used within the driver functions. Not intended for use by
// application code.
//
//*****************************************************************************

//
// Macros for but positions of some register bit fields
//
#define ERAD_HWBP_CNTL_STOP_S         0x05U
#define ERAD_HWBP_CNTL_RTOSINT_S      0x06U

#define ERAD_CTM_CNTL_EVENT_MODE_S    0x03U
#define ERAD_CTM_CNTL_RST_ON_MATCH_S  0x04U
#define ERAD_CTM_CNTL_STOP_S          0x06U
#define ERAD_CTM_CNTL_RTOSINT_S       0x07U

//
// Macro function for getting the instance number from the base address
//
#define ERAD_getBusCompInstance(base) (1UL << ((base >> 3U) & 0x7U))
#define ERAD_getCounterInstance(base) ((1UL << ((base >> 4U) & 0x3U)) << 8U)
#define ERAD_getCRCInstance(base) (1U << (((base >> 4U) & 0xFU) - 1U))

//
// Macro function to get the HWBP event number from the base address
//
#define ERAD_BUSCOMP_BASE_TO_EVENT(base) ((base >> 3U) & 0x07U)

//*****************************************************************************
//
//! Values that can be passed to ERAD_enableModules() or
//! ERAD_disableModules() as \e instances parameter.
//
//*****************************************************************************

#define ERAD_INST_BUSCOMP1  0x00000001UL   //!< Instance for bus comparator 1
#define ERAD_INST_BUSCOMP2  0x00000002UL   //!< Instance for bus comparator 2
#define ERAD_INST_BUSCOMP3  0x00000004UL   //!< Instance for bus comparator 3
#define ERAD_INST_BUSCOMP4  0x00000008UL   //!< Instance for bus comparator 4
#define ERAD_INST_BUSCOMP5  0x00000010UL   //!< Instance for bus comparator 5
#define ERAD_INST_BUSCOMP6  0x00000020UL   //!< Instance for bus comparator 6
#define ERAD_INST_BUSCOMP7  0x00000040UL   //!< Instance for bus comparator 7
#define ERAD_INST_BUSCOMP8  0x00000080UL   //!< Instance for bus comparator 8
#define ERAD_INST_COUNTER1  0x00000100UL   //!< Instance for counter 1
#define ERAD_INST_COUNTER2  0x00000200UL   //!< Instance for counter 2
#define ERAD_INST_COUNTER3  0x00000400UL   //!< Instance for counter 3
#define ERAD_INST_COUNTER4  0x00000800UL   //!< Instance for counter 4
#define ERAD_INST_CRC1      0x00000001UL   //!< Instance for CRC unit 1
#define ERAD_INST_CRC2      0x00000002UL   //!< Instance for CRC unit 2
#define ERAD_INST_CRC3      0x00000004UL   //!< Instance for CRC unit 3
#define ERAD_INST_CRC4      0x00000008UL   //!< Instance for CRC unit 4
#define ERAD_INST_CRC5      0x00000010UL   //!< Instance for CRC unit 5
#define ERAD_INST_CRC6      0x00000020UL   //!< Instance for CRC unit 6
#define ERAD_INST_CRC7      0x00000040UL   //!< Instance for CRC unit 7
#define ERAD_INST_CRC8      0x00000080UL   //!< Instance for CRC unit 8

//*****************************************************************************
//
//! Values that can be passed to ERAD_setCounterInputConditioning() as options
//! parameter.
//
//*****************************************************************************
#define ERAD_INPUT_INVERT_DISABLE 0x00U   //!< Do not invert the input
#define ERAD_INPUT_INVERT_ENABLE  0x01U   //!< Invert the input
#define ERAD_INPUT_SYNC_DISABLE   0x00U   //!< Disable 2-stage synchronizer
#define ERAD_INPUT_SYNC_ENABLE    0x02U   //!< Enable 2-stage synchronizer

//*****************************************************************************
//
//! Values that can be passed to ERAD_initModule() as \e owner parameter to
//! set owner of ERAD.
//
//*****************************************************************************
typedef enum
{
    ERAD_OWNER_NOOWNER     = 0,     //!< No owner
    ERAD_OWNER_APPLICATION = 1,     //!< Application owned
    ERAD_OWNER_DEBUGGER    = 2      //!< Debugger owned
} ERAD_Owner;

//*****************************************************************************
//
//! Values that can are returned by ERAD_getBusCompStatus() and
//! ERAD_getCounterStatus() to indicate the state of the respective module.
//
//*****************************************************************************
typedef enum
{
    ERAD_STATE_IDLE      = 0,     //!< Module is idle
    ERAD_STATE_ENABLED   = 2,     //!< Module is enabled
    ERAD_STATE_COMPLETED = 3      //!< Module was enabled and an event occurred
} ERAD_Status;

//*****************************************************************************
//
//! Values that can be passed to ERAD_configBusComp() and ERAD_profile()
//! as \e config_params.bus_sel parameter to choose which CPU bus to monitor.
//
//*****************************************************************************
typedef enum
{
    ERAD_BUSCOMP_BUS_PAB            = 0,  //!< Use the Program Address Bus
    ERAD_BUSCOMP_BUS_VPC            = 1,  //!< Use the Virtual Program Counter
    ERAD_BUSCOMP_BUS_DWAB           = 2,  //!< Use the Data Write Address Bus
    ERAD_BUSCOMP_BUS_DRAB           = 3,  //!< Use the Data Read Address Bus
    ERAD_BUSCOMP_BUS_DWDB           = 4,  //!< Use the Data Write Data Bus
    ERAD_BUSCOMP_BUS_DRDB           = 5,  //!< Use the Data Read Data Bus
    ERAD_BUSCOMP_BUS_VPC_I_ALIGNED  = 6,  //!< Use VPC Instruction aligned match
    ERAD_BUSCOMP_BUS_VPC_R1_ALIGNED = 7,  //!< Use VPC R1 aligned match
    ERAD_BUSCOMP_BUS_VPC_R2_ALIGNED = 8,  //!< Use VPC R2 aligned match
    ERAD_BUSCOMP_BUS_VPC_W_ALIGNED  = 9,  //!< Use VPC Word aligned match
} ERAD_BusComp_Bus_Select;

//*****************************************************************************
//
//! Values that can be passed to ERAD_configBusComp() and ERAD_profile()
//! as \e config_params.comp_mode to indicate what kind of comparison to use
//! for the bus comparators.
//
//*****************************************************************************
typedef enum
{
    ERAD_BUSCOMP_COMPMODE_GT = 4,         //!< Check for greater than
    ERAD_BUSCOMP_COMPMODE_GE = 5,         //!< Check for greater than equal to
    ERAD_BUSCOMP_COMPMODE_LT = 6,         //!< Check for lesser than
    ERAD_BUSCOMP_COMPMODE_LE = 7,         //!< Check for lesser than equal to
    ERAD_BUSCOMP_COMPMODE_EQ = 0          //!< Check for only equality
} ERAD_BusComp_Comp_Mode;

//*****************************************************************************
//
//! Values that can be passed to ERAD_configCounterInStartStopMode()
//! and ERAD_configCounterInCountingMode() as \e config_params.event_mode to
//! indicate whether to count rising edges or the number of CPU clock cycles an
//! is active.
//
//*****************************************************************************
typedef enum
{
    ERAD_COUNTER_MODE_ACTIVE      = 0,     //!< Count number of CPU
                                           //!  Cycles event is active for
    ERAD_COUNTER_MODE_RISING_EDGE = 1      //!< Count number of Rising
                                           //!  Edges of event
} ERAD_Counter_Event_Mode;

//*****************************************************************************
//
//! Values that can be passed to ERAD_configCounterInStartStopMode()
//! and ERAD_configCounterInCountingMode() as \e config_params.event to
//! indicate what event to consider as input. Also may be passed to
//! ERAD_configCounterInStartStopMode() as \e start_event and \e stop_event
//! to indicate start and stop events for the counter.
//
//*****************************************************************************
typedef enum
{
	ERAD_EVENT_HWBP1		 = 0,	//!EVENT HWBP1
	ERAD_EVENT_HWBP2		 = 1,	//!EVENT HWBP2
	ERAD_EVENT_HWBP3		 = 2,	//!EVENT HWBP3
	ERAD_EVENT_HWBP4		 = 3,	//!EVENT HWBP4
	ERAD_EVENT_HWBP5		 = 4,	//!EVENT HWBP5
	ERAD_EVENT_HWBP6		 = 5,	//!EVENT HWBP6
	ERAD_EVENT_HWBP7		 = 6,	//!EVENT HWBP7
	ERAD_EVENT_HWBP8		 = 7,	//!EVENT HWBP8
	ERAD_EVENT_COUNTER1_EVENT		 = 8,	//!EVENT COUNTER1 EVENT
	ERAD_EVENT_COUNTER2_EVENT		 = 9,	//!EVENT COUNTER2 EVENT
	ERAD_EVENT_COUNTER3_EVENT		 = 10,	//!EVENT COUNTER3 EVENT
	ERAD_EVENT_COUNTER4_EVENT		 = 11,	//!EVENT COUNTER4 EVENT
	ERAD_EVENT_ERAD_OR_MASK0		 = 12,	//!EVENT ERAD OR MASK0
	ERAD_EVENT_ERAD_OR_MASK1		 = 13,	//!EVENT ERAD OR MASK1
	ERAD_EVENT_ERAD_OR_MASK2		 = 14,	//!EVENT ERAD OR MASK2
	ERAD_EVENT_ERAD_OR_MASK3		 = 15,	//!EVENT ERAD OR MASK3
	ERAD_EVENT_ERAD_AND_MASK0		 = 16,	//!EVENT ERAD AND MASK0
	ERAD_EVENT_ERAD_AND_MASK1		 = 17,	//!EVENT ERAD AND MASK1
	ERAD_EVENT_ERAD_AND_MASK2		 = 18,	//!EVENT ERAD AND MASK2
	ERAD_EVENT_ERAD_AND_MASK3		 = 19,	//!EVENT ERAD AND MASK3
	ERAD_EVENT_PIE_INT1		 = 20,	//!EVENT PIE INT1
	ERAD_EVENT_PIE_INT2		 = 21,	//!EVENT PIE INT2
	ERAD_EVENT_PIE_INT3		 = 22,	//!EVENT PIE INT3
	ERAD_EVENT_PIE_INT4		 = 23,	//!EVENT PIE INT4
	ERAD_EVENT_PIE_INT5		 = 24,	//!EVENT PIE INT5
	ERAD_EVENT_PIE_INT6		 = 25,	//!EVENT PIE INT6
	ERAD_EVENT_PIE_INT7		 = 26,	//!EVENT PIE INT7
	ERAD_EVENT_PIE_INT8		 = 27,	//!EVENT PIE INT8
	ERAD_EVENT_PIE_INT9		 = 28,	//!EVENT PIE INT9
	ERAD_EVENT_PIE_INT10		 = 29,	//!EVENT PIE INT10
	ERAD_EVENT_PIE_INT11		 = 30,	//!EVENT PIE INT11
	ERAD_EVENT_PIE_INT12		 = 31,	//!EVENT PIE INT12
	ERAD_EVENT_TIMER1_TINT0		 = 32,	//!EVENT TIMER1 TINT0
	ERAD_EVENT_TIMER1_TINT1		 = 33,	//!EVENT TIMER1 TINT1
	ERAD_EVENT_TIMER2_TINT2		 = 34,	//!EVENT TIMER2 TINT2
	ERAD_EVENT_DMACH1INT		 = 35,	//!EVENT DMACH1INT
	ERAD_EVENT_DMACH2INT		 = 36,	//!EVENT DMACH2INT
	ERAD_EVENT_DMACH3INT		 = 37,	//!EVENT DMACH3INT
	ERAD_EVENT_DMACH4INT		 = 38,	//!EVENT DMACH4INT
	ERAD_EVENT_DMACH5INT		 = 39,	//!EVENT DMACH5INT
	ERAD_EVENT_DMACH6INT		 = 40,	//!EVENT DMACH6INT
	ERAD_EVENT_FSIA_DATA_PKT_RCVD		 = 41,	//!EVENT FSIA DATA PKT RCVD
	ERAD_EVENT_FSIA_ERROR_PKT_RCVD		 = 42,	//!EVENT FSIA ERROR PKT RCVD
	ERAD_EVENT_FSIA_PING_PKT_RCVD		 = 43,	//!EVENT FSIA PING PKT RCVD
	ERAD_EVENT_FSIA_PING_FRAME_TAG_MATCH		 = 44,	//!EVENT FSIA PING FRAME TAG MATCH
	ERAD_EVENT_FSIA_DATA_FRAME_TAG_MATCH		 = 45,	//!EVENT FSIA DATA FRAME TAG MATCH
	ERAD_EVENT_FSIA_ERROR_FRAME_TAG_MATCH		 = 46,	//!EVENT FSIA ERROR FRAME TAG MATCH
	ERAD_EVENT_FSIA_FRAME_DONE		 = 47,	//!EVENT FSIA FRAME DONE
	ERAD_EVENT_ADCAEVTINT		 = 48,	//!EVENT ADCAEVTINT
	ERAD_EVENT_ADCBEVTINT		 = 49,	//!EVENT ADCBEVTINT
	ERAD_EVENT_MCANA_EVT0		 = 50,	//!EVENT MCANA EVT0
	ERAD_EVENT_MCANA_EVT1		 = 51,	//!EVENT MCANA EVT1
	ERAD_EVENT_MCANA_EVT2		 = 52,	//!EVENT MCANA EVT2
	ERAD_EVENT_ADCSOCA		 = 53,	//!EVENT ADCSOCA
	ERAD_EVENT_ADCSOCB		 = 54,	//!EVENT ADCSOCB
	ERAD_EVENT_CLATASKRUN1		 = 55,	//!EVENT CLATASKRUN1
	ERAD_EVENT_CLATASKRUN2		 = 56,	//!EVENT CLATASKRUN2
	ERAD_EVENT_CLATASKRUN3		 = 57,	//!EVENT CLATASKRUN3
	ERAD_EVENT_CLATASKRUN4		 = 58,	//!EVENT CLATASKRUN4
	ERAD_EVENT_CLATASKRUN5		 = 59,	//!EVENT CLATASKRUN5
	ERAD_EVENT_CLATASKRUN6		 = 60,	//!EVENT CLATASKRUN6
	ERAD_EVENT_CLATASKRUN7		 = 61,	//!EVENT CLATASKRUN7
	ERAD_EVENT_CLATASKRUN8		 = 62,	//!EVENT CLATASKRUN8
	ERAD_EVENT_EPWMXBAR_OUT1		 = 63,	//!EVENT EPWMXBAR OUT1
	ERAD_EVENT_EPWMXBAR_OUT2		 = 64,	//!EVENT EPWMXBAR OUT2
	ERAD_EVENT_EPWMXBAR_OUT3		 = 65,	//!EVENT EPWMXBAR OUT3
	ERAD_EVENT_EPWMXBAR_OUT4		 = 66,	//!EVENT EPWMXBAR OUT4
	ERAD_EVENT_EPWMXBAR_OUT5		 = 67,	//!EVENT EPWMXBAR OUT5
	ERAD_EVENT_EPWMXBAR_OUT6		 = 68,	//!EVENT EPWMXBAR OUT6
	ERAD_EVENT_EPWMXBAR_OUT7		 = 69,	//!EVENT EPWMXBAR OUT7
	ERAD_EVENT_EPWMXBAR_OUT8		 = 70,	//!EVENT EPWMXBAR OUT8
	ERAD_EVENT_INPUTXBAR0		 = 71,	//!EVENT INPUTXBAR0
	ERAD_EVENT_INPUTXBAR1		 = 72,	//!EVENT INPUTXBAR1
	ERAD_EVENT_INPUTXBAR2		 = 73,	//!EVENT INPUTXBAR2
	ERAD_EVENT_INPUTXBAR3		 = 74,	//!EVENT INPUTXBAR3
	ERAD_EVENT_INPUTXBAR4		 = 75,	//!EVENT INPUTXBAR4
	ERAD_EVENT_INPUTXBAR5		 = 76,	//!EVENT INPUTXBAR5
	ERAD_EVENT_INPUTXBAR6		 = 77,	//!EVENT INPUTXBAR6
	ERAD_EVENT_INPUTXBAR7		 = 78,	//!EVENT INPUTXBAR7
	ERAD_EVENT_INPUTXBAR8		 = 79,	//!EVENT INPUTXBAR8
	ERAD_EVENT_INPUTXBAR9		 = 80,	//!EVENT INPUTXBAR9
	ERAD_EVENT_INPUTXBAR10		 = 81,	//!EVENT INPUTXBAR10
	ERAD_EVENT_INPUTXBAR11		 = 82,	//!EVENT INPUTXBAR11
	ERAD_EVENT_INPUTXBAR12		 = 83,	//!EVENT INPUTXBAR12
	ERAD_EVENT_INPUTXBAR13		 = 84,	//!EVENT INPUTXBAR13
	ERAD_EVENT_INPUTXBAR14		 = 85,	//!EVENT INPUTXBAR14
	ERAD_EVENT_INPUTXBAR15		 = 86,	//!EVENT INPUTXBAR15
	ERAD_EVENT_CPUx_CPUSTAT		 = 87,	//!EVENT CPUX CPUSTAT
	ERAD_EVENT_CPUx_DBGACK		 = 88,	//!EVENT CPUX DBGACK
	ERAD_EVENT_CPUx_NMI		 = 89,	//!EVENT CPUX NMI
	ERAD_EVENT_CMPSS1_CTRIPH_OR_CTRIPL		 = 90,	//!EVENT CMPSS1 CTRIPH OR CTRIPL
	ERAD_EVENT_CMPSS2_CTRIPH_OR_CTRIPL		 = 91,	//!EVENT CMPSS2 CTRIPH OR CTRIPL
	ERAD_EVENT_CMPSS3_CTRIPH_OR_CTRIPL		 = 92,	//!EVENT CMPSS3 CTRIPH OR CTRIPL
	ERAD_EVENT_CMPSS4_CTRIPH_OR_CTRIPL		 = 93,	//!EVENT CMPSS4 CTRIPH OR CTRIPL
	ERAD_EVENT_ADCAINT1		 = 106,	//!EVENT ADCAINT1
	ERAD_EVENT_ADCAINT2		 = 107,	//!EVENT ADCAINT2
	ERAD_EVENT_ADCAINT3		 = 108,	//!EVENT ADCAINT3
	ERAD_EVENT_ADCAINT4		 = 109,	//!EVENT ADCAINT4
	ERAD_EVENT_ADCBINT1		 = 110,	//!EVENT ADCBINT1
	ERAD_EVENT_ADCBINT2		 = 111,	//!EVENT ADCBINT2
	ERAD_EVENT_ADCBINT3		 = 112,	//!EVENT ADCBINT3
	ERAD_EVENT_ADCBINT4		 = 113,	//!EVENT ADCBINT4
	ERAD_EVENT_ADCCINT1		 = 114,	//!EVENT ADCCINT1
	ERAD_EVENT_ADCCINT2		 = 115,	//!EVENT ADCCINT2
	ERAD_EVENT_ADCCINT3		 = 116,	//!EVENT ADCCINT3
	ERAD_EVENT_ADCCINT4		 = 117,	//!EVENT ADCCINT4
	ERAD_EVENT_ADCDINT1		 = 118,	//!EVENT ADCDINT1
	ERAD_EVENT_ADCDINT2		 = 119,	//!EVENT ADCDINT2
	ERAD_EVENT_ADCDINT3		 = 120,	//!EVENT ADCDINT3
	ERAD_EVENT_ADCDINT4		 = 121,	//!EVENT ADCDINT4
	ERAD_EVENT_ADCEINT1		 = 122,	//!EVENT ADCEINT1
	ERAD_EVENT_ADCEINT2		 = 123,	//!EVENT ADCEINT2
	ERAD_EVENT_ADCEINT3		 = 124,	//!EVENT ADCEINT3
	ERAD_EVENT_ADCEINT4		 = 125,	//!EVENT ADCEINT4
	ERAD_EVENT_MCANB_EVT0		 = 126,	//!EVENT MCANB EVT0
	ERAD_EVENT_MCANB_EVT1		 = 127,	//!EVENT MCANB EVT1
	ERAD_EVENT_MCANB_EVT2		 = 128,	//!EVENT MCANB EVT2
	ERAD_EVENT_CLA_INTERRUPT1		 = 129,	//!EVENT CLA INTERRUPT1
	ERAD_EVENT_CLA_INTERRUPT2		 = 130,	//!EVENT CLA INTERRUPT2
	ERAD_EVENT_CLA_INTERRUPT3		 = 131,	//!EVENT CLA INTERRUPT3
	ERAD_EVENT_CLA_INTERRUPT4		 = 132,	//!EVENT CLA INTERRUPT4
	ERAD_EVENT_CLA_INTERRUPT5		 = 133,	//!EVENT CLA INTERRUPT5
	ERAD_EVENT_CLA_INTERRUPT6		 = 134,	//!EVENT CLA INTERRUPT6
	ERAD_EVENT_CLA_INTERRUPT7		 = 135,	//!EVENT CLA INTERRUPT7
	ERAD_EVENT_CLA_INTERRUPT8		 = 136,	//!EVENT CLA INTERRUPT8
	ERAD_EVENT_ADCCEVTINT		 = 137,	//!EVENT ADCCEVTINT
	ERAD_EVENT_ADCDEVTINT		 = 138,	//!EVENT ADCDEVTINT
	ERAD_EVENT_ADCEEVTINT		 = 139,	//!EVENT ADCEEVTINT
	ERAD_EVENT_TRACE_HIT_EVENT		 = 140,	//!EVENT TRACE HIT EVENT
	ERAD_EVENT_CLBINPUTXBAR0		 = 143,	//!EVENT CLBINPUTXBAR0
	ERAD_EVENT_CLBINPUTXBAR1		 = 144,	//!EVENT CLBINPUTXBAR1
	ERAD_EVENT_CLBINPUTXBAR2		 = 145,	//!EVENT CLBINPUTXBAR2
	ERAD_EVENT_CLBINPUTXBAR3		 = 146,	//!EVENT CLBINPUTXBAR3
	ERAD_EVENT_CLBINPUTXBAR4		 = 147,	//!EVENT CLBINPUTXBAR4
	ERAD_EVENT_CLBINPUTXBAR5		 = 148,	//!EVENT CLBINPUTXBAR5
	ERAD_EVENT_CLBINPUTXBAR6		 = 149,	//!EVENT CLBINPUTXBAR6
	ERAD_EVENT_CLBINPUTXBAR7		 = 150,	//!EVENT CLBINPUTXBAR7
	ERAD_EVENT_CLBINPUTXBAR8		 = 151,	//!EVENT CLBINPUTXBAR8
	ERAD_EVENT_CLBINPUTXBAR9		 = 152,	//!EVENT CLBINPUTXBAR9
	ERAD_EVENT_CLBINPUTXBAR10		 = 153,	//!EVENT CLBINPUTXBAR10
	ERAD_EVENT_CLBINPUTXBAR11		 = 154,	//!EVENT CLBINPUTXBAR11
	ERAD_EVENT_CLBINPUTXBAR12		 = 155,	//!EVENT CLBINPUTXBAR12
	ERAD_EVENT_CLBINPUTXBAR13		 = 156,	//!EVENT CLBINPUTXBAR13
	ERAD_EVENT_CLBINPUTXBAR14		 = 157,	//!EVENT CLBINPUTXBAR14
	ERAD_EVENT_CLBINPUTXBAR15		 = 158,	//!EVENT CLBINPUTXBAR15
	ERAD_EVENT_NO_EVENT		 = 256
} ERAD_Counter_Input_Event;


typedef enum
{
    ERAD_AND_MASK1 = 0,
    ERAD_AND_MASK2 = 1,
    ERAD_AND_MASK3 = 2,
    ERAD_AND_MASK4 = 3,
    ERAD_OR_MASK1  = 4,
    ERAD_OR_MASK2  = 5,
    ERAD_OR_MASK3  = 6,
    ERAD_OR_MASK4  = 7
} ERAD_Mask;

//*****************************************************************************
//
//! Values that can be passed to ERAD_setCRCQualifier() as the \e qualifier
//! paramter to specify which events to set as the qualifier for the CRC unit.
//
//*****************************************************************************
typedef enum
{
    ERAD_CRC_QUAL_NONE      = 0,  //!< Use every valid event as qualifier
                                  //!< for CRC computation
    ERAD_CRC_QUAL_HWBP1     = 1,  //!< CRC Compute Qualified by HWBP_EVENT1
    ERAD_CRC_QUAL_HWBP2     = 2,  //!< CRC Compute Qualified by HWBP_EVENT2
    ERAD_CRC_QUAL_HWBP3     = 3,  //!< CRC Compute Qualified by HWBP_EVENT3
    ERAD_CRC_QUAL_HWBP4     = 4,  //!< CRC Compute Qualified by HWBP_EVENT4
    ERAD_CRC_QUAL_HWBP5     = 5,  //!< CRC Compute Qualified by HWBP_EVENT5
    ERAD_CRC_QUAL_HWBP6     = 6,  //!< CRC Compute Qualified by HWBP_EVENT6
    ERAD_CRC_QUAL_HWBP7     = 7,  //!< CRC Compute Qualified by HWBP_EVENT7
    ERAD_CRC_QUAL_HWBP8     = 8,  //!< CRC Compute Qualified by HWBP_EVENT8
    ERAD_CRC_QUAL_HWBP_OR1  = 9,  //!< CRC Compute Qualified by HWBP_EVENT_OR1
    ERAD_CRC_QUAL_HWBP_OR2  = 10, //!< CRC Compute Qualified by HWBP_EVENT_OR1
    ERAD_CRC_QUAL_HWBP_OR3  = 11, //!< CRC Compute Qualified by HWBP_EVENT_OR1
    ERAD_CRC_QUAL_HWBP_OR4  = 12, //!< CRC Compute Qualified by HWBP_EVENT_OR1
    ERAD_CRC_QUAL_HWBP_AND1 = 13, //!< CRC Compute Qualified by HWBP_EVENT_AND2
    ERAD_CRC_QUAL_HWBP_AND2 = 14, //!< CRC Compute Qualified by HWBP_EVENT_AND2
    ERAD_CRC_QUAL_HWBP_AND3 = 15, //!< CRC Compute Qualified by HWBP_EVENT_AND2
    ERAD_CRC_QUAL_HWBP_AND4 = 16  //!< CRC Compute Qualified by HWBP_EVENT_AND2
} ERAD_CRC_Qualifiers;

//*****************************************************************************
//
//! Values that can be passed to ERAD_setCounterInputConditioning() as
//! \e input_type parameter. To specify which input to condition.
//
//*****************************************************************************
typedef enum
{
    ERAD_COUNTER_COUNT_INPUT = 0,
    ERAD_COUNTER_START_INPUT = 1,
    ERAD_COUNTER_STOP_INPUT  = 2,
    ERAD_COUNTER_RESET_INPUT = 3
} ERAD_Counter_Input_Type;

//*****************************************************************************
//
//! Values that can be passed to ERAD_setPCTraceMode_Windowed() as
//! \e qualifier parameter
//
//*****************************************************************************
typedef enum
{
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP1     = 1,
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP2     = 2,
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP3     = 3,
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP4     = 4,
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP5     = 5,
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP6     = 6,
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP7     = 7,
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP8     = 8,
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP_OR1  = 9,
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP_OR2  = 10,
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP_OR3  = 11,
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP_OR4  = 12,
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP_AND1 = 13,
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP_AND2 = 14,
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP_AND3 = 15,
    ERAD_PCTRACE_WINDOWED_QUAL_HWBP_AND4 = 16
} ERAD_PCTrace_Windowed_Qualifier;

//*****************************************************************************
//
//! Structure that is passed to ERAD_configBusComp() as \e config_params
//! to configure a bus comparator.
//
//*****************************************************************************
typedef struct
{
    uint32_t               mask;        //!< Mask to be used for comparing
    uint32_t               reference;   //!< Reference value to be compared
    ERAD_BusComp_Comp_Mode comp_mode;   //!< Comparison mode
    bool                   enable_int;  //!< Enable Interrupt on event match
    bool                   enable_stop; //!< Enable CPU halt on event match
    ERAD_BusComp_Bus_Select bus_sel;    //!< Bus to be monitored
} ERAD_BusComp_Config;

//*****************************************************************************
//
//! Structure that is passed to ERAD_profile() as \e config_params to setup
//! the required modules appropriately for each use case.
//
//*****************************************************************************
typedef struct
{
    uint32_t                start_address;  //!< Start address
    uint32_t                end_address;    //!< End address
    ERAD_BusComp_Bus_Select bus_sel;        //!< Bus to be monitored
    uint32_t                busComp_base1;  //!< Bus comparators to be used
    uint32_t                busComp_base2;  //!< Bus comparators to be used
    uint32_t                counter_base;   //!< Counter to be used
} ERAD_Profile_Params;

//*****************************************************************************
//
//! Structure that is passed to ERAD_configCounterInStartStopMode() and
//! ERA_configCounterInCountingMode() as \e config_params to setup a
//! counter appropriately.
//
//*****************************************************************************
typedef struct
{
    ERAD_Counter_Input_Event event;        //!< Input Event to be counted
    ERAD_Counter_Event_Mode  event_mode;   //!< Active / rising edge
    uint32_t                 reference;    //!< Reference to be compared
    bool                     rst_on_match; //!< Enable counter reset on match
    bool                     enable_int;   //!< Enable Interrupt on match
    bool                     enable_stop;  //!< Enable CPU halt on match
} ERAD_Counter_Config;

//*****************************************************************************
//
//! Structure that is passed to ERAD_enableInterruptOnAddressHit() and
//! ERAD_countAddressHits() as \e config_params to select the bus and the
//! address to compare. \e bus_Sel can be one of the following:
//! \b ERAD_BUSCOMP_BUS_PAB   : for instruction fetch at the address
//! \b ERAD_BUSCOMP_BUS_DWAB  : for data write access to the address
//! \b ERAD_BUSCOMP_BUS_DRAB  : for data read access to the address
//
//*****************************************************************************
typedef struct
{
    uint32_t                address;    //!< Address to compare
    uint32_t                mask;       //!< Mask for the address compare
    ERAD_BusComp_Bus_Select bus_sel;    //!< Bus to be monitored
} ERAD_AddressHit_Params;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

#ifdef DEBUG
//*****************************************************************************
//
//! \internal
//! Checks a bus comparator base address.
//!
//! \param base specifies the bus comparator base address.
//!
//! This function determines if a bus comparator base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
static inline bool
ERAD_isValidBusCompBase(uint32_t base)
{
    return((base == ERAD_HWBP1_BASE) ||
           (base == ERAD_HWBP2_BASE) ||
           (base == ERAD_HWBP3_BASE) ||
           (base == ERAD_HWBP4_BASE) ||
           (base == ERAD_HWBP5_BASE) ||
           (base == ERAD_HWBP6_BASE) ||
           (base == ERAD_HWBP7_BASE) ||
           (base == ERAD_HWBP8_BASE));
}

//*****************************************************************************
//
//! \internal
//! Checks a counter base address.
//!
//! \param base specifies the counter base address.
//!
//! This function determines if a counter base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
static inline bool
ERAD_isValidCounterBase(uint32_t base)
{
    return((base == ERAD_COUNTER1_BASE) ||
           (base == ERAD_COUNTER2_BASE) ||
           (base == ERAD_COUNTER3_BASE) ||
           (base == ERAD_COUNTER4_BASE));
}

//*****************************************************************************
//
//! \internal
//! Checks a CRC base address.
//!
//! \param base specifies the CRC base address.
//!
//! This function determines if a CRC base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
static inline bool
ERAD_isValidCRCBase(uint32_t base)
{
    return((base == ERAD_CRC1_BASE) ||
           (base == ERAD_CRC2_BASE) ||
           (base == ERAD_CRC3_BASE) ||
           (base == ERAD_CRC4_BASE) ||
           (base == ERAD_CRC5_BASE) ||
           (base == ERAD_CRC6_BASE) ||
           (base == ERAD_CRC7_BASE) ||
           (base == ERAD_CRC8_BASE));
}

#endif

//*****************************************************************************
//
//! Gets the current owner of ERAD.
//!
//! \param None.
//!
//! This function returns the current owner of ERAD.
//!
//! \return Owner of ERAD.
//
//*****************************************************************************
static inline ERAD_Owner
ERAD_getOwnership(void)
{
    //
    // Read Global Owner register and return value
    //
    return((ERAD_Owner)((uint16_t)((HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_OWNER) &
                         ERAD_GLBL_OWNER_OWNER_M) >> ERAD_GLBL_OWNER_OWNER_S)));
}

//*****************************************************************************
//
//! Sets the current owner of ERAD.
//!
//! \param owner is the Owner of ERAD that is to be set
//!
//! This function sets the current owner of ERAD.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setOwnership(ERAD_Owner owner)
{
    //
    // Set the Global Owner as owner
    //
    EALLOW;
    HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_OWNER) =
        ((uint16_t)owner & ERAD_GLBL_OWNER_OWNER_M) << ERAD_GLBL_OWNER_OWNER_S;
    EDIS;
}

//*****************************************************************************
//
//! Resets the counter using the global registers.
//!
//! \param instances is the OR'd value of counter instances to be reset.
//! Following macros can be used:
//! - \b ERAD_INST_COUNTER1
//! - \b ERAD_INST_COUNTER2
//! - \b ERAD_INST_COUNTER3
//! - \b ERAD_INST_COUNTER4
//!
//! This function resets the selected counters using the global registers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_resetCounter(uint16_t instances)
{
    //
    // Resets the counter by writing into the global registers
    //
    EALLOW;
    HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_CTM_RESET) |= instances >> 8U;
    EDIS;
}

//*****************************************************************************
//
//! Enables counters and bus comparators.
//!
//! \param instances is the OR'd value of instances of the counters and bus
//! comparators. Following macros can be used:
//! - \b ERAD_INST_BUSCOMP1
//! - \b ERAD_INST_BUSCOMP2
//! - \b ERAD_INST_BUSCOMP3
//! - \b ERAD_INST_BUSCOMP4
//! - \b ERAD_INST_BUSCOMP5
//! - \b ERAD_INST_BUSCOMP6
//! - \b ERAD_INST_BUSCOMP7
//! - \b ERAD_INST_BUSCOMP8
//! - \b ERAD_INST_COUNTER1
//! - \b ERAD_INST_COUNTER2
//! - \b ERAD_INST_COUNTER3
//! - \b ERAD_INST_COUNTER4
//!
//! This function enables bus comparators and counters whose instances are
//! passed.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_enableModules(uint16_t instances)
{
    //
    // Write into Global register for enabling the required modules
    //
    EALLOW;
    HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_ENABLE) |= instances;
    EDIS;
}

//*****************************************************************************
//
//! Disables counters and bus comparators.
//!
//! \param instances is the OR'd value of instances of the counters and bus
//! comparators. Following macros can be used:
//! - \b ERAD_INST_BUSCOMP1
//! - \b ERAD_INST_BUSCOMP2
//! - \b ERAD_INST_BUSCOMP3
//! - \b ERAD_INST_BUSCOMP4
//! - \b ERAD_INST_BUSCOMP5
//! - \b ERAD_INST_BUSCOMP6
//! - \b ERAD_INST_BUSCOMP7
//! - \b ERAD_INST_BUSCOMP8
//! - \b ERAD_INST_COUNTER1
//! - \b ERAD_INST_COUNTER2
//! - \b ERAD_INST_COUNTER3
//! - \b ERAD_INST_COUNTER4
//!
//! This function disables bus comparators and counters whose instances are
//! passed.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_disableModules(uint16_t instances)
{
    //
    // Write into Global register for disabling the required modules
    //
    EALLOW;
    HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_ENABLE) &= (~instances);
    EDIS;
}

//*****************************************************************************
//
//! Initialises ERAD.
//!
//! \param owner is the owner of ERAD that is to be set.
//!
//! This function resets all the counters and disables all bus comparators and
//! counters.
//! Also sets the owner of the ERAD to the required owner.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_initModule(ERAD_Owner owner)
{
    //
    // Set the owner of ERAD as required
    //
    ERAD_setOwnership(owner);

    //
    // Disable all counters and bus comparators
    //
    ERAD_disableModules(ERAD_INST_BUSCOMP1 | ERAD_INST_BUSCOMP2 |
                        ERAD_INST_BUSCOMP3 | ERAD_INST_BUSCOMP4 |
                        ERAD_INST_BUSCOMP5 | ERAD_INST_BUSCOMP6 |
                        ERAD_INST_BUSCOMP7 | ERAD_INST_BUSCOMP8 |
                        ERAD_INST_COUNTER1 | ERAD_INST_COUNTER2 |
                        ERAD_INST_COUNTER3 | ERAD_INST_COUNTER4);

    //
    // Reset all counters
    //
    ERAD_resetCounter(ERAD_INST_COUNTER1 | ERAD_INST_COUNTER2 |
                      ERAD_INST_COUNTER3 | ERAD_INST_COUNTER4);
}

//*****************************************************************************
//
//! Returns the completed status of any of the modules.
//!
//! \param None.
//!
//! This function returns the completed status of the counters and bus
//! comparators as stored in the global registers. This allows us to read just
//! one register and see if any of the modules are in a completed state.
//!
//! \return Completed status of all the modules as stored in the global
//! register.
//
//*****************************************************************************
static inline uint16_t
ERAD_getHaltStatus(void)
{
    //
    // Read and return from the global register
    //
    return(HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_HALT_STAT));
}

//*****************************************************************************
//
//! Returns the event fired status of any of the modules.
//!
//! \param None.
//!
//! This function returns the event fired status of the counters and bus
//! comparators as stored in the global registers. This allows us to read just
//! one register and see if any of the modules have fired.
//!
//! \return Event fired status of all the modules as stored in the global
//! register.
//
//*****************************************************************************
static inline uint16_t
ERAD_getEventStatus(void)
{
    //
    // Read and return from the global register
    //
    return(HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_EVENT_STAT));
}

//*****************************************************************************
//
//! Enables an NMI for the specified modules.
//!
//! \param instances is the OR'd value of the instances of the counters and
//! bus comparator units that need to have an NMI enabled. Following macros can
//! be used:
//! - \b ERAD_INST_BUSCOMP1
//! - \b ERAD_INST_BUSCOMP2
//! - \b ERAD_INST_BUSCOMP3
//! - \b ERAD_INST_BUSCOMP4
//! - \b ERAD_INST_BUSCOMP5
//! - \b ERAD_INST_BUSCOMP6
//! - \b ERAD_INST_BUSCOMP7
//! - \b ERAD_INST_BUSCOMP8
//! - \b ERAD_INST_COUNTER1
//! - \b ERAD_INST_COUNTER2
//! - \b ERAD_INST_COUNTER3
//! - \b ERAD_INST_COUNTER4
//!
//! This function enables an NMI to be generated whenever any of the specified
//! counters or bus comparator units generate and event.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_enableNMI(uint16_t instances)
{
    EALLOW;
    HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_NMI_CTL) |= instances;
    EDIS;
}

//*****************************************************************************
//
//! Disables an NMI for the specified modules.
//!
//! \param instances is the OR'd value of the instances of the counters and
//! bus comparator units that need to have an NMI disabled. Following macros can
//! be used:
//! - \b ERAD_INST_BUSCOMP1
//! - \b ERAD_INST_BUSCOMP2
//! - \b ERAD_INST_BUSCOMP3
//! - \b ERAD_INST_BUSCOMP4
//! - \b ERAD_INST_BUSCOMP5
//! - \b ERAD_INST_BUSCOMP6
//! - \b ERAD_INST_BUSCOMP7
//! - \b ERAD_INST_BUSCOMP8
//! - \b ERAD_INST_COUNTER1
//! - \b ERAD_INST_COUNTER2
//! - \b ERAD_INST_COUNTER3
//! - \b ERAD_INST_COUNTER4
//!
//! This function disables the NMI for the specified counters and bus
//! comparator units.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_disableNMI(uint16_t instances)
{
    EALLOW;
    HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_NMI_CTL) &= (~instances);
    EDIS;
}

//*****************************************************************************
//
//! Returns the status of a bus comparator.
//!
//! \param base is the base of the bus comparator.
//!
//! This function returns the status of the bus comparator whose base was
//! passed. It may be either \b ERAD_STATE_IDLE, \b ERAD_STATE_ENABLED or
//! \b ERAD_STATE_COMPLETED.
//!
//! \return Status of bus comparator.
//
//*****************************************************************************
static inline ERAD_Status
ERAD_getBusCompStatus(uint32_t base)
{
    //
    // Check if the base is valid
    //
    ASSERT(ERAD_isValidBusCompBase(base));

    //
    // Read and return status of bus comparator
    //
    return((ERAD_Status)((uint16_t)((HWREGH(base + ERAD_O_HWBP_STATUS) &
                    ERAD_HWBP_STATUS_STATUS_M) >> ERAD_HWBP_STATUS_STATUS_S)));
}

//*****************************************************************************
//
//! Clears the event fired status of any of the modules.
//!
//! \param base is the base of the bus comparator.
//!
//! This function clears the event fired status of the bus comparator and
//! brings the module  and brings the module back to \b ERAD_STATE_IDLE .
//!
//! \return None
//
//*****************************************************************************
static inline void
ERAD_clearBusCompEvent(uint32_t base)
{
    //
    // Check if the base is valid
    //
    ASSERT(ERAD_isValidBusCompBase(base));

    //
    // Clear the event fired bit by writing into EVENT_CLR register
    //
    EALLOW;
    HWREGH(base + ERAD_O_HWBP_CLEAR) = ERAD_HWBP_CLEAR_EVENT_CLR;
    EDIS;
}

//*****************************************************************************
//
//! Returns the status of a counter.
//!
//! \param base is the base of the counter.
//!
//! This function returns the status of the counter whose base was
//! passed. It may be either \b ERAD_STATE_IDLE, \b ERAD_STATE_ENABLED or
//! \b ERAD_STATE_COMPLETED.
//!
//! \return Status of counter.
//
//*****************************************************************************
static inline ERAD_Status
ERAD_getCounterStatus(uint32_t base)
{
    //
    // Check if the base is valid
    //
    ASSERT(ERAD_isValidCounterBase(base));

    //
    // Read and return status of the counter
    //
    return((ERAD_Status)((uint16_t)((HWREGH(base + ERAD_O_CTM_STATUS) &
                      ERAD_CTM_STATUS_STATUS_M) >> ERAD_CTM_STATUS_STATUS_S)));
}
//*****************************************************************************
//
//! Configures the bus comparators.
//!
//! \param base is the base of the bus comparator to be configured.
//! \param config_params are the configuration parameters to be used to
//! configure the bus comparator.
//!
//! This function configures the bus comparator with the given parameters.
//!
//! \return None.
//
//*****************************************************************************
extern void
ERAD_configBusComp(uint32_t base, ERAD_BusComp_Config config_params);

//*****************************************************************************
//
//! Configures the counter in Counting mode.
//!
//! \param base is the base of the counter to be configured.
//! \param config_params are the configuration parameters to be used to
//! configure the counter.
//!
//! This function configures the counter with the given parameters. The counter
//! is setup in Counting mode, which means counting begins as soon as the
//! counter is enabled.
//! NOTE: This function does not enable the counter. The counter must be
//! enabled using the \b ERAD_enableModules method to begin counting.
//!
//! \return None.
//
//*****************************************************************************
extern void
ERAD_configCounterInCountingMode(uint32_t base,
                                 ERAD_Counter_Config config_params);

//*****************************************************************************
//
//! Configures the counter in Start-Stop mode.
//!
//! \param base is the base of the counter to be configured.
//! \param config_params are the configuration parameters to be used to
//! configure the counter.
//! \param start_event is the event that starts the counter
//! \param stop_event is the event which stops that counter
//!
//! This function configures the counter with the given parameters. The counter
//! is setup in Start-Stop mode, which means counting will happen only between
//! two specified events. The event that will be counted can be any of the
//! \b ERAD_Counter_Input_Event and not only CPU cycles.
//! NOTE: \b ERAD_EVENT_NO_EVENT causes the counter to use the CPU cycles.
//! NOTE: This function does not enable the counter. The counter must be
//! enabled using the \b ERAD_enableModules method to begin counting.
//!
//! \return None.
//
//*****************************************************************************
extern void
ERAD_configCounterInStartStopMode(uint32_t base,
                                    ERAD_Counter_Config config_params,
                                    ERAD_Counter_Input_Event start_event,
                                    ERAD_Counter_Input_Event stop_event);

//*****************************************************************************
//
//! Configures the counter in Start-Stop Cumulative mode.
//!
//! \param base is the base of the counter to be configured.
//! \param config_params are the configuration parameters to be used to
//! configure the counter.
//! \param start_event is the event that starts the counter
//! \param stop_event is the event which stops that counter
//!
//! This function configures the counter with the given parameters. The counter
//! is setup in Cumulative mode, which means counting will happen only between
//! two specified events and the counter will not reset on \b stop_event. The
//! event that will be counted can be any of the \b ERAD_Counter_Input_Event
//! and not only CPU cycles.
//! NOTE: \b ERAD_EVENT_NO_EVENT causes the counter to use the CPU cycles.
//! NOTE: This function does not enable the counter. The counter must be
//! enabled using the \b ERAD_enableModules method to begin counting.
//!
//! \return None.
//
//*****************************************************************************
extern void
ERAD_configCounterInCumulativeMode(uint32_t base,
                                   ERAD_Counter_Config config_params,
                                   ERAD_Counter_Input_Event start_event,
                                   ERAD_Counter_Input_Event stop_event);

//*****************************************************************************
//
//! Configures the AND and OR masks
//!
//! \param mask is the Mask to be used.
//!
//! \param instances is the OR'd value of the instances of the  bus comparator
//!  units whose events need to be used for the mask. Following macros can be
//!  used:
//! - \b ERAD_INST_BUSCOMP1
//! - \b ERAD_INST_BUSCOMP2
//! - \b ERAD_INST_BUSCOMP3
//! - \b ERAD_INST_BUSCOMP4
//! - \b ERAD_INST_BUSCOMP5
//! - \b ERAD_INST_BUSCOMP6
//! - \b ERAD_INST_BUSCOMP7
//! - \b ERAD_INST_BUSCOMP8
//! - \b ERAD_INST_COUNTER1
//! - \b ERAD_INST_COUNTER2
//! - \b ERAD_INST_COUNTER3
//! - \b ERAD_INST_COUNTER4
//!
//! \param enable_int True if interrupt needs to be enabled, False if not
//!
//! This function enables the event generated from the specified bus comparator
//! units to be used for the specified Mask. It also configures the interrupt
//! generation when the mask event occurs.
//!
//! \return None.
//
//*****************************************************************************
extern void
ERAD_configMask(ERAD_Mask mask, uint32_t instances, bool enable_int);

//*****************************************************************************
//
//! Configures the reset event of the counter.
//!
//! \param base is the base of the counter to be configured.
//! \param reset_event is the event upon which the counter must be reset.
//!
//! This function sets the event upon which the counter must reset and enables
//! reset upon such an event.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_enableCounterResetInput(uint32_t base,
                            ERAD_Counter_Input_Event reset_event)
{
    //
    // Check if the base is valid
    //
    ASSERT(ERAD_isValidCounterBase(base));

    //
    // Setup up the counter such that the reset event is set and enabled
    //
    EALLOW;
    EDIS;
}

//*****************************************************************************
//
//! Disables the reset event of the counter.
//!
//! \param base is the base of the counter.
//!
//! This function disables the reset event that may have been set earlier
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_disableCounterResetInput(uint32_t base)
{
    //
    // Check if the base is valid
    //
    ASSERT(ERAD_isValidCounterBase(base));

    //
    // Disable the reset bit
    //
    EALLOW;
    HWREGH(base + ERAD_O_CTM_CNTL) &= (~ERAD_CTM_CNTL_RST_EN);
    EDIS;
}

//*****************************************************************************
//
//! Clears an event that may have fired in the counter upon match.
//!
//! \param base is the base of the counter.
//!
//! This function clears a counter event that may have fired when the counter
//! hit a match.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_clearCounterEvent(uint32_t base)
{
    //
    // Check if the base is valid
    //
    ASSERT(ERAD_isValidCounterBase(base));

    //
    // Clear the event by writing into CTM_CLEAR register
    //
    EALLOW;
    HWREGH(base + ERAD_O_CTM_CLEAR) = ERAD_CTM_CLEAR_EVENT_CLEAR;
    EDIS;
}

//*****************************************************************************
//
//! Clears an overflow that may have occured in the counter.
//!
//! \param base is the base of the counter.
//!
//! This function clears the overflow bit that may have got set when the
//! counter may have crossed 0xFFFFFFFF.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_clearCounterOverflow(uint32_t base)
{
    //
    // Check if the base is valid
    //
    ASSERT(ERAD_isValidCounterBase(base));

    //
    // Clear the overflow bit by writing into the CTM_CLEAR register
    //
    EALLOW;
    HWREGH(base + ERAD_O_CTM_CLEAR) = ERAD_CTM_CLEAR_OVERFLOW_CLEAR;
    EDIS;
}

//*****************************************************************************
//
//! Gets the current count of a counter.
//!
//! \param base is the base of the counter.
//!
//! This function returns the current count of the counter which was
//! configured earlier.
//!
//! \return Returns the value of the current count of the counter.
//
//*****************************************************************************
static inline uint32_t
ERAD_getCurrentCount(uint32_t base)
{
    //
    // Check if the base is valid
    //
    ASSERT(ERAD_isValidCounterBase(base));

    //
    // Return the current count
    //
    return(HWREG(base + ERAD_O_CTM_COUNT));
}

//*****************************************************************************
//
//! Sets the current count of a counter.
//!
//! \param base is the base of the counter.
//! \param value is the value to be written as the current count.
//!
//! This function sets the current count of the counter which was
//! configured earlier. This can be used to reset the counter or start at
//! a value other than 0.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setCurrentCount(uint32_t base, uint32_t value)
{
    //
    // Check if owner is APPLICATION or NO_OWNER
    //
    ASSERT((ERAD_getOwnership() == ERAD_OWNER_APPLICATION) ||
           (ERAD_getOwnership() == ERAD_OWNER_NOOWNER));

    //
    // Check if the base is valid
    //
    ASSERT(ERAD_isValidCounterBase(base));

    //
    // Write the value into CTM_COUNT register
    //
    EALLOW;
    HWREG(base + ERAD_O_CTM_COUNT) = value;
    EDIS;
}

//*****************************************************************************
//
//! Gets the maximum count of a counter.
//!
//! \param base is the base of the counter.
//!
//! This function returns the current maximum count of the counter which was
//! configured earlier.
//!
//! \return Returns the value of the current maximum count of the counter.
//
//*****************************************************************************
static inline uint32_t
ERAD_getMaxCount(uint32_t base)
{
    //
    // Check if the base is valid
    //
    ASSERT(ERAD_isValidCounterBase(base));

    //
    // Return the maximum value
    //
    return(HWREG(base + ERAD_O_CTM_MAX_COUNT));
}

//*****************************************************************************
//
//! Sets the maximum count of a counter.
//!
//! \param base is the base of the counter.
//! \param value is the value to be written as the maximum count.
//!
//! This function sets the current maximum count of the counter which was
//! configured earlier.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setMaxCount(uint32_t base, uint32_t value)
{
    //
    // Check if owner is APPLICATION or NO_OWNER
    //
    ASSERT((ERAD_getOwnership() == ERAD_OWNER_APPLICATION) ||
           (ERAD_getOwnership() == ERAD_OWNER_NOOWNER));

    //
    // Check if the base is valid
    //
    ASSERT(ERAD_isValidCounterBase(base));

    //
    // Write the value into the CTM_MAX_COUNT register
    //
    EALLOW;
    HWREG(base + ERAD_O_CTM_MAX_COUNT) = value;
    EDIS;
}

//*****************************************************************************
//
//! Sets conditioning on the inputs to the counter.
//!
//! \param base is the base value of the counter to be configured
//! \param input_type defines which input needs to be conditioned
//! \param options is the kind of conditioning that needs to applied. This will
//! be an OR'd value of \b ERAD_INVERT_ENABLE, \b ERAD_INVERT_DISABLE,
//! \b ERAD_SYNC_ENABLE or \b ERAD_SYNC_DISABLE.
//!
//! This function conditions the inputs to the counter specified. This includes
//! inverting the input and enabling a 2-stage synchronizer for any 4 of the
//! inputs: \e reset, \e stop, \e start, \e count_input.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setCounterInputConditioning(uint32_t base,
                                 ERAD_Counter_Input_Type input_type,
                                 uint16_t options)
{
    //
    // Write into the Input Conditioning register
    //
    EALLOW;
    HWREGH(base + ERAD_O_CTM_INPUT_COND) =
                    (HWREGH(base + ERAD_O_CTM_INPUT_COND) &
                     ~(0x03U << (uint16_t)input_type)) |
                    (options << (uint16_t)input_type);
    EDIS;
}

//*****************************************************************************
//
//! Initialises the CRC unit.
//!
//! \param instances is the OR'd value of CRC instances. Following macros can
//!  be used:
//!  - \b ERAD_INST_CRC1
//!  - \b ERAD_INST_CRC2
//!  - \b ERAD_INST_CRC3
//!  - \b ERAD_INST_CRC4
//!  - \b ERAD_INST_CRC5
//!  - \b ERAD_INST_CRC6
//!  - \b ERAD_INST_CRC7
//!  - \b ERAD_INST_CRC8
//!
//! This function initialises the specified CRC units.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_initCRC(uint16_t instances)
{
    //
    // Write into the CRC GLOBAL CTRL register
    //
    EALLOW;
    HWREGH(ERAD_CRC_GLOBAL_BASE + ERAD_O_CRC_GLOBAL_CTRL) |= instances;
    EDIS;
}

//*****************************************************************************
//
//! Enables the CRC unit.
//!
//! \param instances is the OR'd value of CRC instances. Following macros can
//!  be used:
//!  - \b ERAD_INST_CRC1
//!  - \b ERAD_INST_CRC2
//!  - \b ERAD_INST_CRC3
//!  - \b ERAD_INST_CRC4
//!  - \b ERAD_INST_CRC5
//!  - \b ERAD_INST_CRC6
//!  - \b ERAD_INST_CRC7
//!  - \b ERAD_INST_CRC8
//!
//! This function enables the specified CRC units.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_enableCRC(uint16_t instances)
{
    //
    // Write into the CRC GLOBAL CTRL register
    //
    EALLOW;
    HWREGH(ERAD_CRC_GLOBAL_BASE + ERAD_O_CRC_GLOBAL_CTRL) |= instances << 8;
    EDIS;
}

//*****************************************************************************
//
//! Disables the CRC unit.
//!
//! \param instances is the OR'd value of CRC instances. Following macros can
//!  be used:
//!  - \b ERAD_INST_CRC1
//!  - \b ERAD_INST_CRC2
//!  - \b ERAD_INST_CRC3
//!  - \b ERAD_INST_CRC4
//!  - \b ERAD_INST_CRC5
//!  - \b ERAD_INST_CRC6
//!  - \b ERAD_INST_CRC7
//!  - \b ERAD_INST_CRC8
//!
//! This function disables the specified CRC units.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_disableCRC(uint16_t instances)
{
    //
    // Write into the CRC GLOBAL CTRL register
    //
    EALLOW;
    HWREGH(ERAD_CRC_GLOBAL_BASE + ERAD_O_CRC_GLOBAL_CTRL) &= ~(instances << 8);
    EDIS;
}

//*****************************************************************************
//
//! Gets the current value of the CRC unit.
//!
//! \param base is the base value of CRC unit
//!
//! This function returns the current value of te specified CRC unit.
//!
//! \return Current CRC value.
//
//*****************************************************************************
static inline uint32_t
ERAD_getCurrentCRC(uint32_t base)
{
    //
    // Check if base is valid
    //
    ASSERT(ERAD_isValidCRCBase(base));

    //
    // Read from the current value register of the specified CRC unit
    //
    return(HWREG(base + ERAD_O_CRC_CURRENT));
}

//*****************************************************************************
//
//! Sets the seed value of the CRC unit
//!
//! \param base is the base value of the CRC unit
//! \param seed is the value of seed to be set
//!
//! This function sets a seed value of the CRC unit.
//! Note: The corresponding CRC unit must be disabled before setting the seed
//! value.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setSeed(uint32_t base, uint32_t seed)
{
    //
    // Check if base is valid
    //
    ASSERT(ERAD_isValidCRCBase(base));

    //
    // Check if the unit is disabled
    //
    ASSERT((HWREGH(ERAD_CRC_GLOBAL_BASE + ERAD_O_CRC_GLOBAL_CTRL) &
            ERAD_getCRCInstance(base)) == 0U);

    //
    // Write into the CRC SEED register
    //
    EALLOW;
    HWREGH(base + ERAD_O_CRC_SEED) = seed;
    EDIS;
}

//*****************************************************************************
//
//! Sets the qualifier event of the CRC unit
//!
//! \param base is the base value of the CRC unit
//! \param qualifier is the type of qualifier to be set
//!
//! This function sets a qualifier to decide which events require a CRC
//! computation.
//! Note: The corresponding CRC unit must be disabled before setting the
//! qualifier.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setCRCQualifier(uint32_t base, ERAD_CRC_Qualifiers qualifier)
{
    //
    // Check if base is valid
    //
    ASSERT(ERAD_isValidCRCBase(base));

    //
    // Check if the unit is disabled
    //
    ASSERT((HWREGH(ERAD_CRC_GLOBAL_BASE + ERAD_O_CRC_GLOBAL_CTRL) &
            ERAD_getCRCInstance(base)) == 0U);

    //
    // Write into the CRC Qualifier register
    //
    EALLOW;
    HWREGH(base + ERAD_O_CRC_QUALIFIER) = qualifier;
    EDIS;
}

//*****************************************************************************
//
//! Enable PC Trace
//!
//! This function enables PC Trace
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_enablePCTrace(void)
{
    EALLOW;
    HWREGH(ERAD_PCTRACE_BASE + ERAD_O_PCTRACE_GLOBAL) |= ERAD_PCTRACE_GLOBAL_EN;
    EDIS;
}

//*****************************************************************************
//
//! Disable PC Trace
//!
//! This function disables PC Trace
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_disablePCTrace(void)
{
    EALLOW;
    HWREGH(ERAD_PCTRACE_BASE + ERAD_O_PCTRACE_GLOBAL) &= ~ERAD_PCTRACE_GLOBAL_EN;
    EDIS;
}

//*****************************************************************************
//
//! Initialize PC Trace Buffer
//!
//! This function initilizes the Trace module for a fresh trace start with
//! buffer pointer reset and overflow flags cleared along with SOFT_START_PC
//! and SOFT_STOP_PC
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_initPCTraceBuffer(void)
{
    EALLOW;
    HWREGH(ERAD_PCTRACE_BASE + ERAD_O_PCTRACE_GLOBAL) |=
                                ERAD_PCTRACE_GLOBAL_INIT;
    EDIS;
}

//*****************************************************************************
//
//! Configures the PC Trace submodule to trace without hardware qaulifiers
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setPCTraceMode_NoQualifiers(void)
{
    //
    // Clear the QUAL1 and QUAL2 Registers and set Trace Mode to Trace without
    // any hardware qualifiers
    //
    EALLOW;
    HWREG(ERAD_PCTRACE_BASE + ERAD_O_PCTRACE_QUAL1) = 0U;
    HWREG(ERAD_PCTRACE_BASE + ERAD_O_PCTRACE_QUAL2) = 0U;
    EDIS;
}

//*****************************************************************************
//
//! Configures the PC Trace submodule to trace using windowed mode
//!
//! \param qualifier Qualifier input to enable tracing
//! \param inputConditioning is the kind of conditioning that needs to applied
//! for the trace input. This will be an OR'd value of
//! \b ERAD_INPUT_INVERT_ENABLE or  \b ERAD_INPUT_INVERT_DISABLE and
//! \b ERAD_INPUT_SYNC_ENABLE or \b ERAD_INPUT_SYNC_DISABLE.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setPCTraceMode_Windowed(ERAD_PCTrace_Windowed_Qualifier qualifier,
                             uint32_t inputConditioning)
{
    EALLOW;
    HWREG(ERAD_PCTRACE_BASE + ERAD_O_PCTRACE_QUAL1) =
        ((uint32_t)qualifier << ERAD_PCTRACE_QUAL1_WINDOWED_INP_SEL_S) |
        (0x2UL << ERAD_PCTRACE_QUAL1_TRACE_MODE_S) | (inputConditioning << 18U);
    HWREG(ERAD_PCTRACE_BASE + ERAD_O_PCTRACE_QUAL2) = 0U;

    EDIS;
}

//*****************************************************************************
//
//! Configures the PC Trace submodule to trace using start stop mode
//!
//! \param startInput Start Event for the Trace
//! \param stopInput  Stop Event for the Trace
//! \param startInputConditioning is the kind of conditioning that needs to
//!  applied for the start input. This will be an OR'd value of
//! \b ERAD_INPUT_INVERT_ENABLE or  \b ERAD_INPUT_INVERT_DISABLE and
//! \b ERAD_INPUT_SYNC_ENABLE or \b ERAD_INPUT_SYNC_DISABLE.
//! \param stopInputConditioning is the kind of conditioning that needs to
//!  applied for the start input. This will be an OR'd value of
//! \b ERAD_INPUT_INVERT_ENABLE or  \b ERAD_INPUT_INVERT_DISABLE and
//! \b ERAD_INPUT_SYNC_ENABLE or \b ERAD_INPUT_SYNC_DISABLE.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ERAD_setPCTraceMode_StartSop(ERAD_Counter_Input_Event startInput,
                             uint32_t startInputConditioning,
                             ERAD_Counter_Input_Event stopInput,
                             uint32_t stopInputConditioning)
{
    EALLOW;
    HWREG(ERAD_PCTRACE_BASE + ERAD_O_PCTRACE_QUAL1) =
        (0x3UL << ERAD_PCTRACE_QUAL1_TRACE_MODE_S)  |
        (startInputConditioning << 20U) | (stopInputConditioning << 22U);
    HWREG(ERAD_PCTRACE_BASE + ERAD_O_PCTRACE_QUAL2) =
        ((uint32_t)startInput << ERAD_PCTRACE_QUAL2_START_INP_SEL_S) |
        ((uint32_t)stopInput << ERAD_PCTRACE_QUAL2_STOP_INP_SEL_S);

    EDIS;
}
//*****************************************************************************
//
//! Configures the ERAD to profile a certain piece of code
//!
//! \param config_params are the parameters that will be used to configure ERAD
//!
//! This function configures 2 bus comparators and 1 counter to profile a
//! certain piece of code. The base address of the bus comparators and the
//! counter to be used are specified in \e config_params.
//! Note: Use \b ERAD_getMaxCount to get the latest profiled value. The
//! maximum count of the counter being used must be reset to 0x0 to get the
//! correct value everytime.
//!
//! \return None.
//
//*****************************************************************************
extern void
ERAD_profile(ERAD_Profile_Params config_params);

//*****************************************************************************
//
//! Enables an RTOS interrupt at a specified address.
//!
//! \param config_params contrains the bus to be monitored and the address
//! \param busComp_base is the base of the bus compoarator to be used
//!
//! This function enables an RTOS interrupt to be generated when an address
//! in memory or instruction is hit.
//!
//! If the selected bus is \b ERAD_BUSCOMP_BUS_PAB, then the ERAD will be
//! configured to trigger an interrupt when there is instruction fetch happening
//! at the specified address. Similary, if \b ERAD_BUSCOMP_BUS_DWAB is selected,
//! the ERAD will be configured to trigger an interrupt when there write
//! access to the specified address, and so on.
//!
//! Use \e
//!
//! \return None.
//
//*****************************************************************************
extern void
ERAD_enableInterruptOnAddressHit(ERAD_AddressHit_Params config_params,
                                 uint32_t busComp_base);

//*****************************************************************************
//
//! Configures the ERAD to count the number of times a the specified address
//! is hit
//!
//! \param config_params are the parameters that will be used to configure ERAD
//! \param busComp_base is the base of the bus compoarator to be used
//! \param counter_base is the base of the counter to be used
//!
//! This function configures 1 bus comparator and 1 counter to count how many
//! times a the specified address is hit.
//!
//! If the selected bus is \b ERAD_BUSCOMP_BUS_PAB, then the ERAD will be
//! configured to count the number of times an instruction fetch happens
//! at the specified address. Similary, if \b ERAD_BUSCOMP_BUS_DWAB is selected,
//! the ERAD will be configured to count the number of times there is a write
//! access to the specified address, and so on.
//!
//! \return None.
//
//*****************************************************************************
extern void
ERAD_countAddressHits(ERAD_AddressHit_Params config_params,
                      uint32_t busComp_base, uint32_t counter_base);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // ERAD_H
