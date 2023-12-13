//###########################################################################
//
// FILE:   f28004x_dcl_erad.h
//
// TITLE:  ERAD driver header file for DCL suite.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:  
// Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F28004x_DCL_ERAD_DEFINES_H
#define F28004x_DCL_ERAD_DEFINES_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
//! \addtogroup f28004x_dcl_erad_api F28004x_DCL_ERAD
//! @{
//
//*****************************************************************************

#include "f28004x_device.h"

//*****************************************************************************
//
// The following defines are used by the Counter, Enhanced bus comparator APIs 
// to configure the corresponding instances.
//
//*****************************************************************************
#define CTM1_INST	0x00000001
#define CTM2_INST	0x00000002
#define CTM3_INST	0x00000004
#define CTM4_INST	0x00000008
#define HWBP1_INST	0x00000001
#define HWBP2_INST	0x00000002
#define HWBP3_INST	0x00000004
#define HWBP4_INST	0x00000008
#define HWBP5_INST	0x00000010
#define HWBP6_INST	0x00000020
#define HWBP7_INST	0x00000040
#define HWBP8_INST	0x00000080

//*****************************************************************************
//
// The following defines are used by the Counter APIs  
// ERAD_counterClearStatus and ERAD_counterGetStatus.
//
//*****************************************************************************
#define CTM_EVENT_FIRED 0x1
#define CTM_EVENT_OVERFLOW 0x2

//*****************************************************************************
//
// The following defines are used by the Enhanced bus comparator APIs  
// ERAD_HWBPClearStatus and ERAD_HWBPGetStatus.
//
//*****************************************************************************
#define HWBP_EVENT_FIRED 0x1

//*****************************************************************************
//
//! Values passed onto counterConfig and and hwbpConfig structs 
//! to enable/disable the selected features.
//
//*****************************************************************************
typedef enum {
	ENABLED=1,
	DISABLED=0
}modeConfig;

//*****************************************************************************
//
//! Values passed onto ERAD_setGlobalOwner() or returned from ERAD_getGlobalOwner API
//! These values are used to select the owner or return the owner 
//
//*****************************************************************************
typedef enum{
	NO_OWNER=0,
	APPLICATION=1,
	DEBUGGER=2
}globalOwner;

//*****************************************************************************
//
//! Values passed onto counterConfig struct 
//! These values are used to select the event on which the counter will 
//! start,stop,reset,count. 
//
//*****************************************************************************
typedef enum {
	BUS_COMP1_EVENT=0,
	BUS_COMP2_EVENT=1,
	BUS_COMP3_EVENT=2,
	BUS_COMP4_EVENT=3,
	BUS_COMP5_EVENT=4,
	BUS_COMP6_EVENT=5,
	BUS_COMP7_EVENT=6,
	BUS_COMP8_EVENT=7,
	COUNTER1_EVENT=8,
	COUNTER2_EVENT=9,
	COUNTER3_EVENT=10,
	COUNTER4_EVENT=11,
	PIE_INT1=12,
	PIE_INT2=13,
	PIE_INT3=14,
	PIE_INT4=15,
	PIE_INT5=16,
	PIE_INT6=17,
	PIE_INT7=18,
	PIE_INT8=19,
	PIE_INT9=20,
	PIE_INT10=21,
	PIE_INT11=22,
	PIE_INT12=23,
	TIMER1_TINT1=24,
	TIMER2_TINT2=25,
	CLA_INTERRUPT1=26,
	CLA_INTERRUPT2=27,
	CLA_INTERRUPT3=28,
	CLA_INTERRUPT4=29,
	CLA_INTERRUPT5=30,
	CLA_INTERRUPT8=31
}eventInputs;

//*****************************************************************************
//
//! Values passed onto hwbpConfig struct.
//! These values are used to  select which CPU buses will be used for
//! comparison to generate the match events.
//
//*****************************************************************************
typedef enum{
	PAB=0,
	DRAB=3,
	DWAB=2,
	VPC=1,
	DWDB=4
}busSel;

//*****************************************************************************
//
//! Values passed onto hwbpConfig struct.
//! These values are used to select the comparison Mode of the bus that is 
//! selected. 
//
//*****************************************************************************
typedef enum{
	GT=4,
	GE=5,
	LT=6,
	LE=7,
	EQ=0
}compMode;

//*****************************************************************************
//
//! Values that can be passed onto counterConfig struct.
//! These values are used to configure the counter to count on the edge 
//! or level event.
//
//*****************************************************************************
typedef enum
{
	LEVEL=0,
	EDGE=1
}edgeLevel;

//*****************************************************************************
//
//! Data structure that can be passed onto ERAD_counterConfig API.
//! The structure is used to configure the counter to count on 
//! the required event.
//
//*****************************************************************************
typedef struct
{
	modeConfig HW_CNT_RST;  	
	eventInputs RST_INP_SEL;
	modeConfig RTOSINT;
	modeConfig DBGEVT;			
	modeConfig RST_ON_MATCH;
	edgeLevel  EDGE_LEVEL_CFG;	
	modeConfig START_STOP_MODE;
	eventInputs START_INP_SEL;
	eventInputs STOP_INP_SEL;
	modeConfig CNT_INP_SEL_EN;
	eventInputs CNT_INP_SEL;
}counterConfig;

//*****************************************************************************
//
//! Data structure that can be passed onto ERAD_HWBPConfig API.
//! The structure is used to configure the Enhanced Bus Comparator unit. 
//
//*****************************************************************************
typedef struct
{
	busSel BUS_SEL;
	compMode COMP_MODE;
	Uint32 REF;
	Uint32 MASK;
	modeConfig RTOSINT;
	modeConfig DBGEVT;		
}hwbpConfig;


//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! This function is used to enable the Counter unit(s).
//!
//! \param counterInstances is the counter instance to be enabled.
//! 
//! The \e counterInstances parameter is the logical OR of any of the following:
//! - \b CTM1_INST - Counter unit1
//! - \b CTM2_INST - Counter unit2
//! - \b CTM3_INST - Counter unit3
//! - \b CTM4_INST - Counter unit4
//!
//! \return Returns \b true if the ERAD is owned by Application.Returns 
//! \b false if the ERAD is owned by Debugger.
//
//*****************************************************************************
extern bool ERAD_setGlobalCTMEnable(Uint16 counterInstances);

//*****************************************************************************
//
//! This function is used to disable the Counter unit(s).
//!
//! \param counterInstances is the counter instance to be disabled.
//! 
//! The \e counterInstances parameter is the logical OR of any of the following:
//! - \b CTM1_INST - Counter unit1
//! - \b CTM2_INST - Counter unit2
//! - \b CTM3_INST - Counter unit3
//! - \b CTM4_INST - Counter unit4
//!
//! \return Returns \b true if the ERAD is owned by Application.Returns 
//! \b false if the ERAD is owned by Debugger.
//
//*****************************************************************************
extern bool ERAD_setGlobalCTMDisable(Uint16 counterInstances);

//*****************************************************************************
//
//! This function is used to reset the Counter unit(s).
//!
//! \param counterInstances is the counter instance to be reset.
//! 
//! The \e counterInstances parameter is the logical OR of any of the following:
//! - \b CTM1_INST - Counter unit1
//! - \b CTM2_INST - Counter unit2
//! - \b CTM3_INST - Counter unit3
//! - \b CTM4_INST - Counter unit4
//!
//! \return None.
//
//*****************************************************************************
extern void ERAD_setGlobalCTMReset(Uint16 counterInstances);

//*****************************************************************************
//
//! This function is used to read the Global Counter event stats. 
//!
//! \param None.
//!
//! \return Returns 
//! -\b CTM1_INST if the event is fired from Counter1.  
//! -\b CTM2_INST if the event is fired from Counter2.
//! -\b CTM3_INST if the event is fired from Counter3.
//! -\b CTM4_INST if the event is fired from Counter4.  
//
//*****************************************************************************
extern Uint16 ERAD_getCTMEventStat();

//*****************************************************************************
//
//! This function is used to read the Global Counter halt stats. 
//!
//! \param None.
//!
//! \return Returns 
//! -\b CTM1_INST if the count event of Counter1 is generated.  
//! -\b CTM2_INST if the count event of Counter2 is generated.  
//! -\b CTM3_INST if the count event of Counter3 is generated.  
//! -\b CTM4_INST if the count event of Counter4 is generated.  
//
//*****************************************************************************
extern Uint16 ERAD_getCTMHaltStat();

//*****************************************************************************
//
//! This function is used to enable the Enhanced Bus Comparator unit(s).
//!
//! \param hwbpInstances is the Enhanced Bus Comparator instance to be enabled.
//! 
//! The \e hwbpInstances parameter is the logical OR of any of the following:
//! - \b HWBP1_INST - Enhanced Bus Comparator unit1
//! - \b HWBP2_INST - Enhanced Bus Comparator unit2
//! - \b HWBP3_INST - Enhanced Bus Comparator unit3
//! - \b HWBP4_INST - Enhanced Bus Comparator unit4
//! - \b HWBP5_INST - Enhanced Bus Comparator unit5
//! - \b HWBP6_INST - Enhanced Bus Comparator unit6
//! - \b HWBP7_INST - Enhanced Bus Comparator unit7
//! - \b HWBP8_INST - Enhanced Bus Comparator unit8
//!
//! \return Returns \b true if the ERAD is owned by Application.Returns 
//! \b false if the ERAD is owned by Debugger.
//
//*****************************************************************************
extern bool ERAD_globalHWBPEnable(Uint16 hwbpInstances);

//*****************************************************************************
//
//! This function is used to disable the Enhanced Bus Comparator unit(s).
//!
//! \param hwbpInstances is the Enhanced Bus Comparator instance to be disabled.
//! 
//! The \e hwbpInstances parameter is the logical OR of any of the following:
//! - \b HWBP1_INST - Enhanced Bus Comparator unit1
//! - \b HWBP2_INST - Enhanced Bus Comparator unit2
//! - \b HWBP3_INST - Enhanced Bus Comparator unit3
//! - \b HWBP4_INST - Enhanced Bus Comparator unit4
//! - \b HWBP5_INST - Enhanced Bus Comparator unit5
//! - \b HWBP6_INST - Enhanced Bus Comparator unit6
//! - \b HWBP7_INST - Enhanced Bus Comparator unit7
//! - \b HWBP8_INST - Enhanced Bus Comparator unit8
//!
//! \return Returns \b true if the ERAD is owned by Application.Returns 
//! \b false if the ERAD is owned by Debugger.
//
//*****************************************************************************
extern bool ERAD_globalHWBPDisable(Uint16 hwbpInstances);

//*****************************************************************************
//
//! This function is used to read the Global Enhanced Bus Comparator event stats. 
//!
//! \param None.
//!
//! \return Returns 
//! -\b HWBP1_INST if the event is fired from Enhanced Bus Comparator unit1.  
//! -\b HWBP2_INST if the event is fired from Enhanced Bus Comparator unit2.
//! -\b HWBP3_INST if the event is fired from Enhanced Bus Comparator unit3.  
//! -\b HWBP4_INST if the event is fired from Enhanced Bus Comparator unit4.
//! -\b HWBP5_INST if the event is fired from Enhanced Bus Comparator unit5.  
//! -\b HWBP6_INST if the event is fired from Enhanced Bus Comparator unit6.
//! -\b HWBP7_INST if the event is fired from Enhanced Bus Comparator unit7.  
//! -\b HWBP8_INST if the event is fired from Enhanced Bus Comparator unit8.
//
//*****************************************************************************
extern Uint16 ERAD_getHWBPEventStat();

//*****************************************************************************
//
//! This function is used to read the Global Enhanced Bus Comparator halt stats. 
//!
//! \param None.
//!
//! \return Returns 
//! -\b HWBP1_INST if the Enhanced Bus Comparator unit1 is completed.  
//! -\b HWBP2_INST if the Enhanced Bus Comparator unit2 is completed.
//! -\b HWBP3_INST if the Enhanced Bus Comparator unit3 is completed.  
//! -\b HWBP4_INST if the Enhanced Bus Comparator unit4 is completed.
//! -\b HWBP5_INST if the Enhanced Bus Comparator unit5 is completed.  
//! -\b HWBP6_INST if the Enhanced Bus Comparator unit6 is completed.
//! -\b HWBP7_INST if the Enhanced Bus Comparator unit7 is completed.  
//! -\b HWBP8_INST if the Enhanced Bus Comparator unit8 is completed.
//
//*****************************************************************************
extern Uint16 ERAD_getHWBPHaltStat();

//*****************************************************************************
//
//! This function is used to set the reference match count for the counter to
//! a predetermined value.
//!
//! \param counterInstances is the counter instance.
//! \param referenceCount is the counter reference for comparison
//! 
//! The \e counterInstances parameter is one of the following:
//! - \b CTM1_INST - Counter unit1
//! - \b CTM2_INST - Counter unit2
//! - \b CTM3_INST - Counter unit3
//! - \b CTM4_INST - Counter unit4
//!
//! \return None.
//
//*****************************************************************************
extern void ERAD_counterSetRef(Uint16 counterInstance,Uint32 referenceCount);

//*****************************************************************************
//
//! This function is used to set the current count for the counter to 
//! a predetermined value.
//!
//! \param counterInstances is the counter instance.
//! \param currentCount is the current counter value to be set. 
//! 
//! The \e counterInstances parameter is one of the following:
//! - \b CTM1_INST - Counter unit1
//! - \b CTM2_INST - Counter unit2
//! - \b CTM3_INST - Counter unit3
//! - \b CTM4_INST - Counter unit4
//!
//! \return None.
//
//*****************************************************************************
extern void ERAD_counterSetCurCount(Uint16 counterInstance,Uint32 currentCount);

//*****************************************************************************
//
//! This function is used to set the maximum count for the counter to 
//! a predetermined value.
//!
//! \param counterInstances is the counter instance.
//! \param maxCount is the maximum counter value to be set. 
//! 
//! The \e counterInstances parameter is one of the following:
//! - \b CTM1_INST - Counter unit1
//! - \b CTM2_INST - Counter unit2
//! - \b CTM3_INST - Counter unit3
//! - \b CTM4_INST - Counter unit4
//!
//! \return None.
//
//*****************************************************************************
extern void ERAD_counterSetMaxCount(Uint16 counterInstance,Uint32 maxCount);

//*****************************************************************************
//
//! This function is used to get the current count of the counter.
//!
//! \param counterInstances is the counter instance.
//! 
//! The \e counterInstances parameter is one of the following:
//! - \b CTM1_INST - Counter unit1
//! - \b CTM2_INST - Counter unit2
//! - \b CTM3_INST - Counter unit3
//! - \b CTM4_INST - Counter unit4
//!
//! \return Returns the current counter value.
//
//*****************************************************************************
extern Uint32 ERAD_counterGetCurCount(Uint16 counterInstance);

//*****************************************************************************
//
//! This function is used to get the maximum count of the counter.
//!
//! \param counterInstances is the counter instance.
//! 
//! The \e counterInstances parameter is one of the following:
//! - \b CTM1_INST - Counter unit1
//! - \b CTM2_INST - Counter unit2
//! - \b CTM3_INST - Counter unit3
//! - \b CTM4_INST - Counter unit4
//!
//! \return Returns the Max count value.
//
//*****************************************************************************
extern Uint32 ERAD_counterGetMaxCount(Uint16 counterInstance);

//*****************************************************************************
//
//! This function is used to get the current status for the counter.
//!
//! \param counterInstances is the counter instance.
//! 
//! The \e counterInstances parameter is one of the following:
//! - \b CTM1_INST - Counter unit1
//! - \b CTM2_INST - Counter unit2
//! - \b CTM3_INST - Counter unit3
//! - \b CTM4_INST - Counter unit4
//!
//! \return Returns 
//! -\b CTM_EVENT_FIRED if the event is fired. 
//! -\b CTM_EVENT_OVERFLOW if the counter has overflown.
//
//*****************************************************************************
extern Uint16 ERAD_counterGetStatus(Uint16 counterInstance);

//*****************************************************************************
//
//! This function is used to clear the current status for the counter.
//!
//! \param counterInstances is the counter instance.
//! \param clearFlags is the flag to be cleared
//!
//! The \e counterInstances parameter is one of the following:
//! - \b CTM1_INST - Counter unit1
//! - \b CTM2_INST - Counter unit2
//! - \b CTM3_INST - Counter unit3
//! - \b CTM4_INST - Counter unit4
//!
//! The \e clearFlags parameter is the one of the following:
//! - \b CTM_EVENT_FIRED - To clear the event fired status
//! - \b CTM_EVENT_OVERFLOW - To clear the event overflow status
//!
//! \return None.
//
//*****************************************************************************
extern void ERAD_counterClearStatus(Uint16 counterInstance,Uint16 clearFlags);

//*****************************************************************************
//
//! This function is used to configure the counter to count on certain event.
//!
//! \param counterInstances is the counter instance.
//! \param counterCfg is the data struture that is used to configure 
//!  the counter to count on
//! 
//! The \e counterInstances parameter is one of the following:
//! - \b CTM1_INST - Counter unit1
//! - \b CTM2_INST - Counter unit2
//! - \b CTM3_INST - Counter unit3
//! - \b CTM4_INST - Counter unit4
//!
//! \return None.
//
//*****************************************************************************
extern void ERAD_counterConfig(Uint16 counterInstance,counterConfig counterCfg);

//*****************************************************************************
//
//! This function is used to get the current status for the Enhanced Bus Comparator unit.
//!
//! \param hwbpInstance is the Enhanced Bus Comparator instance.
//! 
//! The \e hwbpInstance parameter is one of the following:
//! - \b HWBP1_INST - Enhanced Bus Comparator unit1
//! - \b HWBP2_INST - Enhanced Bus Comparator unit2
//! - \b HWBP3_INST - Enhanced Bus Comparator unit3
//! - \b HWBP4_INST - Enhanced Bus Comparator unit4
//! - \b HWBP5_INST - Enhanced Bus Comparator unit5
//! - \b HWBP6_INST - Enhanced Bus Comparator unit6
//! - \b HWBP7_INST - Enhanced Bus Comparator unit7
//! - \b HWBP8_INST - Enhanced Bus Comparator unit8
//!
//! \return Returns 
//! -\b HWBP_EVENT_FIRED if the event is fired. 
//
//*****************************************************************************
extern Uint16 ERAD_HWBPGetStatus(Uint16 hwbpInstance);

//*****************************************************************************
//
//! This function is used to clear the status for the Enhanced Bus Comparator unit.
//!
//! \param hwbpInstance is the Enhanced Bus Comparator instance.
//! \param clearFlags is the flag to be cleared
//! 
//! The \e hwbpInstance parameter is one of the following:
//! - \b HWBP1_INST - Enhanced Bus Comparator unit1
//! - \b HWBP2_INST - Enhanced Bus Comparator unit2
//! - \b HWBP3_INST - Enhanced Bus Comparator unit3
//! - \b HWBP4_INST - Enhanced Bus Comparator unit4
//! - \b HWBP5_INST - Enhanced Bus Comparator unit5
//! - \b HWBP6_INST - Enhanced Bus Comparator unit6
//! - \b HWBP7_INST - Enhanced Bus Comparator unit7
//! - \b HWBP8_INST - Enhanced Bus Comparator unit8
//!
//! The \e clearFlags parameter is the one of the following:
//! -\b HWBP_EVENT_FIRED - To clear the event fired status. 
//!
//! \return None. 
//
//*****************************************************************************
extern void ERAD_HWBPClearStatus(Uint16 hwbpInstance,Uint16 clearFlags);

//*****************************************************************************
//
//! This function is used to configure the Enhanced Bus Comparator unit.
//!
//! \param hwbpInstance is the Enhanced Bus Comparator unit instance.
//! \param hwbpCfg is the data struture that is used to configure 
//!  the Enhanced Bus Comparator unit.
//! 
//! The \e hwbpInstance parameter is one of the following:
//! - \b HWBP1_INST - Enhanced Bus Comparator unit1
//! - \b HWBP2_INST - Enhanced Bus Comparator unit2
//! - \b HWBP3_INST - Enhanced Bus Comparator unit3
//! - \b HWBP4_INST - Enhanced Bus Comparator unit4
//! - \b HWBP5_INST - Enhanced Bus Comparator unit5
//! - \b HWBP6_INST - Enhanced Bus Comparator unit6
//! - \b HWBP7_INST - Enhanced Bus Comparator unit7
//! - \b HWBP8_INST - Enhanced Bus Comparator unit8
//!
//! \return None.
//
//*****************************************************************************
extern void ERAD_HWBPConfig(Uint16 hwbpInstance,hwbpConfig hwbpCfg);

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

#endif   // - end of F28004x_DCL_ERAD_DEFINES_H
