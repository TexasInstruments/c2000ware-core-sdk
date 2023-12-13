//###########################################################################
//
// FILE:   f28004x_dcl_erad.c
//
// TITLE:  ERAD driver functions for DCL suite.
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

//***********************************************************************************
//
// Included Files
//
//***********************************************************************************
#include "f28004x_dcl_erad.h"
#include "f28004x_erad.h"

//***********************************************************************************
//
//ERAD_setGlobalCTMEnable - This function is used to enable the Counters. 
//							Inputs can be CTM1_INST,CTM2_INST etc.
//							Returns false if the unit is not owned by Application.
//
//***********************************************************************************
bool ERAD_setGlobalCTMEnable(Uint16 counterInstances)
{

	//Check if Application owns the ERAD, else return false
	if(EradGlobalRegs.GLBL_OWNER.bit.OWNER == DEBUGGER)
	{
		return false;
	}else
	{
		Uint16 shiftedCounterInstance,temp;

		shiftedCounterInstance = counterInstances << 8;
		EALLOW;
		temp = (EradGlobalRegs.GLBL_ENABLE.all) | shiftedCounterInstance;
		EradGlobalRegs.GLBL_ENABLE.all = temp;
		EDIS;
		return true;
	}
}

//***********************************************************************************
//
//ERAD_setGlobalCTMDisable -This function is used to disable the Counters.
//							Inputs can be CTM1_INST,CTM2_INST etc.
//							Returns false if the unit is not owned by Application.
//
//***********************************************************************************
bool ERAD_setGlobalCTMDisable(Uint16 counterInstances)
{
	//Check if Application owns the ERAD, else return false
	if(EradGlobalRegs.GLBL_OWNER.bit.OWNER == DEBUGGER)
	{
		return false;
	}else
	{
		Uint16 shiftedCounterInstance,temp;

		shiftedCounterInstance = counterInstances << 8;
		EALLOW;
		temp = (EradGlobalRegs.GLBL_ENABLE.all) & (~shiftedCounterInstance);
		EradGlobalRegs.GLBL_ENABLE.all = temp;
		EDIS;
		return true;
	}
}

//***********************************************************************************
//
//ERAD_setGlobalCTMReset - 	This function is used to reset the Counters. 
//							Inputs can be CTM1_INST,CTM2_INST etc.
//***********************************************************************************
void ERAD_setGlobalCTMReset(Uint16 counterInstances)
{
	EALLOW;
	EradGlobalRegs.GLBL_CTM_RESET.all = counterInstances;
	EDIS;
}

//***********************************************************************************
//
//ERAD_getCTMEventStat - 	This function is used to read the Counter event stats. 
//							Outputs can be checked against CTM1_INST,CTM2_INST etc.
//
//***********************************************************************************
Uint16 ERAD_getCTMEventStat()
{
	Uint16 shiftedCounterInstance;
	shiftedCounterInstance = ((EradGlobalRegs.GLBL_EVENT_STAT.all) & 0xF00)>>8;
	return(shiftedCounterInstance);
}

//***********************************************************************************
//
//ERAD_getCTMHaltStat - 	This function is used to read the Counter halt stats. 
//							Outputs can be checked against CTM1_INST,CTM2_INST etc.
//
//***********************************************************************************
Uint16 ERAD_getCTMHaltStat()
{
	Uint16 shiftedCounterInstance;
	shiftedCounterInstance = ((EradGlobalRegs.GLBL_HALT_STAT.all) & 0xF00)>>8;
	return(shiftedCounterInstance);
}

//***********************************************************************************
//
//ERAD_globalHWBPEnable - 	This function is used to enable the Enhanced Bus Comparator 
//							units. 
//							Inputs can be HWBP1_INST,HWBP2_INST etc.
//							Returns false if the unit is not owned by Application.
//
//***********************************************************************************
bool ERAD_globalHWBPEnable(Uint16 hwbpInstances)
{
	//Check if Application owns the ERAD, else return false
	if(EradGlobalRegs.GLBL_OWNER.bit.OWNER == DEBUGGER)
	{
		return false;
	}else
	{
		Uint16 temp;
		EALLOW;
		temp = (EradGlobalRegs.GLBL_ENABLE.all)  | hwbpInstances;
		EradGlobalRegs.GLBL_ENABLE.all = temp;
		EDIS;
		return true;
	}
}

//***********************************************************************************
//
//ERAD_globalHWBPDisable - 	This function is used to disable the Enhanced Bus comparator 
//							units. 
//							Inputs can be HWBP1_INST,HWBP2_INST etc.
//							Returns false if the unit is not owned by Application.
//
//***********************************************************************************
bool ERAD_globalHWBPDisable(Uint16 hwbpInstances)
{
	//Check if Application owns the ERAD, else return false
	if(EradGlobalRegs.GLBL_OWNER.bit.OWNER == DEBUGGER)
	{
		return false;
	}else
	{
		Uint16 temp;
		EALLOW;
		temp = (EradGlobalRegs.GLBL_ENABLE.all) & (~hwbpInstances);
		EradGlobalRegs.GLBL_ENABLE.all = temp;
		EDIS;
		return true;
	}
}

//***********************************************************************************
//
//ERAD_getHWBPEventStat - 	This function is used to get the Enhanced Bus comparator 
//							event stats 
//							Outputs can be checked against HWBP1_INST,HWBP2_INST etc.
//
//***********************************************************************************
Uint16 ERAD_getHWBPEventStat()
{
	Uint16 shiftedCounterInstance;
	shiftedCounterInstance = ((EradGlobalRegs.GLBL_EVENT_STAT.all) & 0x00FF);
	return(shiftedCounterInstance);
}

//***********************************************************************************
//
//ERAD_getHWBPHaltStat - 	This function is used to get the Enhanced Bus comparator 
//							halt stats 
//							Outputs can be checked against HWBP1_INST,HWBP2_INST etc.
//
//***********************************************************************************
Uint16 ERAD_getHWBPHaltStat()
{
	Uint16 shiftedCounterInstance;
	shiftedCounterInstance = ((EradGlobalRegs.GLBL_HALT_STAT.all) & 0x00FF);
	return(shiftedCounterInstance);
}

//***********************************************************************************
//
//ERAD_counterSetRef - 	This function is used to set the reference match count for the 
//						counter. 
//						Inputs can be CTM1_INST,CTM2_INST etc and the 
//						counter reference count.
//
//***********************************************************************************
void ERAD_counterSetRef(Uint16 counterInstance,Uint32 referenceCount)
{
	EALLOW;
	if(counterInstance == CTM1_INST)
	{
		EradCounter1Regs.CTM_REF = referenceCount;
	}else if(counterInstance == CTM2_INST)
	{
		EradCounter2Regs.CTM_REF = referenceCount;
	}else if(counterInstance == CTM3_INST)
	{
		EradCounter3Regs.CTM_REF = referenceCount;
	}else if(counterInstance == CTM4_INST)
	{
		EradCounter4Regs.CTM_REF = referenceCount;
	}
	EDIS;
}

//***********************************************************************************
//
//ERAD_counterSetCurCount - This function is used to set the current count for the 
//							counter to a predetermined value. 
//							Inputs can be CTM1_INST,CTM2_INST etc and the current 
//							counter count.
//
//***********************************************************************************
void ERAD_counterSetCurCount(Uint16 counterInstance,Uint32 currentCount)
{
	EALLOW;
	if(counterInstance == CTM1_INST)
	{
		EradCounter1Regs.CTM_COUNT = currentCount;
	}else if(counterInstance == CTM2_INST)
	{
		EradCounter2Regs.CTM_COUNT = currentCount;
	}else if(counterInstance == CTM3_INST)
	{
		EradCounter3Regs.CTM_COUNT = currentCount;
	}else if(counterInstance == CTM4_INST)
	{
		EradCounter4Regs.CTM_COUNT = currentCount;
	}
	EDIS;
}

//***********************************************************************************
//
//ERAD_counterSetMaxCount - This function is used to set the max count for the 
//							counter to a predetermined value. 
//							Inputs can be CTM1_INST,CTM2_INST etc and the counter 
//							max count.
//
//***********************************************************************************
void ERAD_counterSetMaxCount(Uint16 counterInstance,Uint32 maxCount)
{
	EALLOW;
	if(counterInstance == CTM1_INST)
	{
		EradCounter1Regs.CTM_MAX_COUNT = maxCount;
	}else if(counterInstance == CTM2_INST)
	{
		EradCounter2Regs.CTM_MAX_COUNT = maxCount;
	}else if(counterInstance == CTM3_INST)
	{
		EradCounter3Regs.CTM_MAX_COUNT = maxCount;
	}else if(counterInstance == CTM4_INST)
	{
		EradCounter4Regs.CTM_MAX_COUNT = maxCount;
	}
	EDIS;
}

//***********************************************************************************
//
//ERAD_counterGetCurCount - This function is used to get the current count for 
//							the counter. 
//							Inputs can be CTM1_INST,CTM2_INST etc.
//							Returns the current count value.
//
//***********************************************************************************
Uint32 ERAD_counterGetCurCount(Uint16 counterInstance)
{
	Uint32 currentCount;
	if(counterInstance == CTM1_INST)
	{
		currentCount = EradCounter1Regs.CTM_COUNT;
	}else if(counterInstance == CTM2_INST)
	{
		currentCount = EradCounter2Regs.CTM_COUNT ;
	}else if(counterInstance == CTM3_INST)
	{
		currentCount = EradCounter3Regs.CTM_COUNT ;
	}else if(counterInstance == CTM4_INST)
	{
		currentCount = EradCounter4Regs.CTM_COUNT ;
	}
	return(currentCount);
}

//***********************************************************************************
//
//ERAD_counterGetMaxCount - This function is used to get the max count for the 
//							counter. 
//							Inputs can be CTM1_INST,CTM2_INST etc.
//							Returns the count max value.
//
//***********************************************************************************
Uint32 ERAD_counterGetMaxCount(Uint16 counterInstance)
{
	Uint32 maxCount;
	if(counterInstance == CTM1_INST)
	{
		maxCount = EradCounter1Regs.CTM_MAX_COUNT;
	}else if(counterInstance == CTM2_INST)
	{
		maxCount = EradCounter2Regs.CTM_MAX_COUNT ;
	}else if(counterInstance == CTM3_INST)
	{
		maxCount = EradCounter3Regs.CTM_MAX_COUNT ;
	}else if(counterInstance == CTM4_INST)
	{
		maxCount = EradCounter4Regs.CTM_MAX_COUNT ;
	}
	return(maxCount);
}

//***********************************************************************************
//
//ERAD_counterGetStatus -	This function is used to get the current status for the 
//							counter. 
//							Inputs can be CTM1_INST,CTM2_INST etc.
//							Returns CTM_EVENT_FIRED or CTM_EVENT_OVERFLOW or both.
//
//***********************************************************************************
Uint16 ERAD_counterGetStatus(Uint16 counterInstance)
{
	if(counterInstance == CTM1_INST)
	{
		return( ( (EradCounter1Regs.CTM_STATUS.bit.OVERFLOW << 1) | EradCounter1Regs.CTM_STATUS.bit.EVENT_FIRED) );
	}else if(counterInstance == CTM2_INST)
	{
		return( ( (EradCounter2Regs.CTM_STATUS.bit.OVERFLOW << 1) | EradCounter2Regs.CTM_STATUS.bit.EVENT_FIRED) );
	}else if(counterInstance == CTM3_INST)
	{
		return( ( (EradCounter3Regs.CTM_STATUS.bit.OVERFLOW << 1) | EradCounter3Regs.CTM_STATUS.bit.EVENT_FIRED) );
	}else if(counterInstance == CTM4_INST)
	{
		return( ( (EradCounter4Regs.CTM_STATUS.bit.OVERFLOW << 1) | EradCounter4Regs.CTM_STATUS.bit.EVENT_FIRED) );
	}else
	{
		return(0);
	}
}

//***********************************************************************************
//
//ERAD_counterClearStatus -	This function is used to clear the current status for the 
//							counter. 
//							Inputs can be CTM1_INST,CTM2_INST etc and the event 
//							to clear(CTM_EVENT_FIRED or CTM_EVENT_OVERFLOW or both).
//
//***********************************************************************************
void ERAD_counterClearStatus(Uint16 counterInstance,Uint16 clearFlags)
{
	EALLOW;
	if(counterInstance == CTM1_INST)
	{
		if(clearFlags && CTM_EVENT_FIRED == 0x1)
		{
			EradCounter1Regs.CTM_CLEAR.bit.EVENT_CLEAR = 1;
		}
		if(clearFlags && CTM_EVENT_FIRED == 0x2)
		{
			EradCounter1Regs.CTM_CLEAR.bit.OVERFLOW_CLEAR = 1;
		}
	}else if(counterInstance == CTM2_INST)
	{
		if(clearFlags && CTM_EVENT_FIRED == 0x1)
		{
			EradCounter2Regs.CTM_CLEAR.bit.EVENT_CLEAR = 1;
		}
		if(clearFlags && CTM_EVENT_FIRED == 0x2)
		{
			EradCounter2Regs.CTM_CLEAR.bit.OVERFLOW_CLEAR = 1;
		}
	}else if(counterInstance == CTM3_INST)
	{
		if(clearFlags && CTM_EVENT_FIRED == 0x1)
		{
			EradCounter3Regs.CTM_CLEAR.bit.EVENT_CLEAR = 1;
		}
		if(clearFlags && CTM_EVENT_FIRED == 0x2)
		{
			EradCounter3Regs.CTM_CLEAR.bit.OVERFLOW_CLEAR = 1;
		}
	}else if(counterInstance == CTM4_INST)
	{
		if(clearFlags && CTM_EVENT_FIRED == 0x1)
		{
			EradCounter4Regs.CTM_CLEAR.bit.EVENT_CLEAR = 1;
		}
		if(clearFlags && CTM_EVENT_FIRED == 0x2)
		{
			EradCounter4Regs.CTM_CLEAR.bit.OVERFLOW_CLEAR = 1;
		}
	}
	EDIS;
}

//***********************************************************************************
//
//ERAD_counterConfig -	This function is used to configure the counter.
//						Inputs can be CTM1_INST,CTM2_INST etc and  
//						configurations can be passed via a structure of type counterConfig.
//
//***********************************************************************************
void ERAD_counterConfig(Uint16 counterInstance,counterConfig counterCfg)
{
	EALLOW;
	if(counterInstance == CTM1_INST)
	{
		EradCounter1Regs.CTM_CNTL.bit.START_STOP_MODE	=   counterCfg.START_STOP_MODE;
	    EradCounter1Regs.CTM_CNTL.bit.EVENT_MODE		=   counterCfg.EDGE_LEVEL_CFG;
	    EradCounter1Regs.CTM_CNTL.bit.RST_ON_MATCH		=	counterCfg.RST_ON_MATCH;
	    EradCounter1Regs.CTM_CNTL.bit.STOP				=	counterCfg.DBGEVT;
	    EradCounter1Regs.CTM_CNTL.bit.RTOSINT			=	counterCfg.RTOSINT;
	    EradCounter1Regs.CTM_CNTL.bit.RST_EN			=	counterCfg.HW_CNT_RST;
	    EradCounter1Regs.CTM_CNTL.bit.RST_INP_SEL		=	counterCfg.RST_INP_SEL;
		EradCounter1Regs.CTM_INPUT_SEL.bit.CNT_INP_SEL =	counterCfg.CNT_INP_SEL;
		EradCounter1Regs.CTM_INPUT_SEL.bit.STA_INP_SEL =	counterCfg.START_INP_SEL;
		EradCounter1Regs.CTM_INPUT_SEL.bit.STO_INP_SEL =	counterCfg.STOP_INP_SEL;
		EradCounter1Regs.CTM_INPUT_SEL.bit.CTM_INP_SEL_EN = counterCfg.CNT_INP_SEL_EN;
	}else if(counterInstance == CTM2_INST)
	{
		EradCounter2Regs.CTM_CNTL.bit.START_STOP_MODE	=   counterCfg.START_STOP_MODE;
	    EradCounter2Regs.CTM_CNTL.bit.EVENT_MODE		=   counterCfg.EDGE_LEVEL_CFG;
	    EradCounter2Regs.CTM_CNTL.bit.RST_ON_MATCH		=	counterCfg.RST_ON_MATCH;
	    EradCounter2Regs.CTM_CNTL.bit.STOP				=	counterCfg.DBGEVT;
	    EradCounter2Regs.CTM_CNTL.bit.RTOSINT			=	counterCfg.RTOSINT;
	    EradCounter2Regs.CTM_CNTL.bit.RST_EN			=	counterCfg.HW_CNT_RST;
	    EradCounter2Regs.CTM_CNTL.bit.RST_INP_SEL		=	counterCfg.RST_INP_SEL;
		EradCounter2Regs.CTM_INPUT_SEL.bit.CNT_INP_SEL =	counterCfg.CNT_INP_SEL;
		EradCounter2Regs.CTM_INPUT_SEL.bit.STA_INP_SEL =	counterCfg.START_INP_SEL;
		EradCounter2Regs.CTM_INPUT_SEL.bit.STO_INP_SEL =	counterCfg.STOP_INP_SEL;
		EradCounter2Regs.CTM_INPUT_SEL.bit.CTM_INP_SEL_EN = counterCfg.CNT_INP_SEL_EN;

	}else if(counterInstance == CTM3_INST)
	{
		EradCounter3Regs.CTM_CNTL.bit.START_STOP_MODE	=   counterCfg.START_STOP_MODE;
	    EradCounter3Regs.CTM_CNTL.bit.EVENT_MODE		=   counterCfg.EDGE_LEVEL_CFG;
	    EradCounter3Regs.CTM_CNTL.bit.RST_ON_MATCH		=	counterCfg.RST_ON_MATCH;
	    EradCounter3Regs.CTM_CNTL.bit.STOP				=	counterCfg.DBGEVT;
	    EradCounter3Regs.CTM_CNTL.bit.RTOSINT			=	counterCfg.RTOSINT;
	    EradCounter3Regs.CTM_CNTL.bit.RST_EN			=	counterCfg.HW_CNT_RST;
	    EradCounter3Regs.CTM_CNTL.bit.RST_INP_SEL		=	counterCfg.RST_INP_SEL;
		EradCounter3Regs.CTM_INPUT_SEL.bit.CNT_INP_SEL =	counterCfg.CNT_INP_SEL;
		EradCounter3Regs.CTM_INPUT_SEL.bit.STA_INP_SEL =	counterCfg.START_INP_SEL;
		EradCounter3Regs.CTM_INPUT_SEL.bit.STO_INP_SEL =	counterCfg.STOP_INP_SEL;
		EradCounter3Regs.CTM_INPUT_SEL.bit.CTM_INP_SEL_EN = counterCfg.CNT_INP_SEL_EN;

	}else if(counterInstance == CTM4_INST)
	{
		EradCounter4Regs.CTM_CNTL.bit.START_STOP_MODE	=   counterCfg.START_STOP_MODE;
	    EradCounter4Regs.CTM_CNTL.bit.EVENT_MODE		=   counterCfg.EDGE_LEVEL_CFG;
	    EradCounter4Regs.CTM_CNTL.bit.RST_ON_MATCH		=	counterCfg.RST_ON_MATCH;
	    EradCounter4Regs.CTM_CNTL.bit.STOP				=	counterCfg.DBGEVT;
	    EradCounter4Regs.CTM_CNTL.bit.RTOSINT			=	counterCfg.RTOSINT;
	    EradCounter4Regs.CTM_CNTL.bit.RST_EN			=	counterCfg.HW_CNT_RST;
	    EradCounter4Regs.CTM_CNTL.bit.RST_INP_SEL		=	counterCfg.RST_INP_SEL;
		EradCounter4Regs.CTM_INPUT_SEL.bit.CNT_INP_SEL =	counterCfg.CNT_INP_SEL;
		EradCounter4Regs.CTM_INPUT_SEL.bit.STA_INP_SEL =	counterCfg.START_INP_SEL;
		EradCounter4Regs.CTM_INPUT_SEL.bit.STO_INP_SEL =	counterCfg.STOP_INP_SEL;
		EradCounter4Regs.CTM_INPUT_SEL.bit.CTM_INP_SEL_EN = counterCfg.CNT_INP_SEL_EN;
	}
	EDIS;
}

//***********************************************************************************
//
//ERAD_HWBPGetStatus -	This function is used to get the current status for the 
//						Enhanced Bus comparator unit. 
//						Inputs can be HWBP1_INST, HWBP2_INST etc.
//						Returns HWBP_EVENT_FIRED, if fired.
//
//***********************************************************************************
Uint16 ERAD_HWBPGetStatus(Uint16 hwbpInstance)
{
	if(hwbpInstance == HWBP1_INST)
	{
		return (EradHWBP1Regs.HWBP_STATUS.bit.EVENT_FIRED);
	}else if(hwbpInstance == HWBP2_INST)
	{
		return (EradHWBP2Regs.HWBP_STATUS.bit.EVENT_FIRED);
	}else if(hwbpInstance == HWBP3_INST)
	{
		return (EradHWBP3Regs.HWBP_STATUS.bit.EVENT_FIRED);
	}else if(hwbpInstance == HWBP4_INST)
	{
		return (EradHWBP4Regs.HWBP_STATUS.bit.EVENT_FIRED);
	}else if(hwbpInstance == HWBP5_INST)
	{
		return (EradHWBP5Regs.HWBP_STATUS.bit.EVENT_FIRED);
	}else if(hwbpInstance == HWBP6_INST)
	{
		return (EradHWBP6Regs.HWBP_STATUS.bit.EVENT_FIRED);
	}else if(hwbpInstance == HWBP7_INST)
	{
		return (EradHWBP7Regs.HWBP_STATUS.bit.EVENT_FIRED);
	}else if(hwbpInstance == HWBP8_INST)
	{
		return (EradHWBP8Regs.HWBP_STATUS.bit.EVENT_FIRED);
	}else
	{
		return (0);
	}
}

//***********************************************************************************
//
//ERAD_HWBPClearStatus -	This function is used to clear the current status for the 
//							Enhanced Bus comparator unit. 
//							Inputs can be HWBP1_INST, HWBP2_INST etc and the event to 
//							clear(HWBP_EVENT_FIRED).
//
//***********************************************************************************
void ERAD_HWBPClearStatus(Uint16 hwbpInstance,Uint16 clearFlags)
{
	EALLOW;
	if(clearFlags == HWBP_EVENT_FIRED)
	{
		if(hwbpInstance == HWBP1_INST)
		{
			EradHWBP1Regs.HWBP_CLEAR.bit.EVENT_CLR = 1;
		}else if(hwbpInstance == HWBP2_INST)
		{
			EradHWBP2Regs.HWBP_CLEAR.bit.EVENT_CLR = 1;
		}else if(hwbpInstance == HWBP3_INST)
		{
			EradHWBP3Regs.HWBP_CLEAR.bit.EVENT_CLR = 1;
		}else if(hwbpInstance == HWBP4_INST)
		{
			EradHWBP4Regs.HWBP_CLEAR.bit.EVENT_CLR = 1;
		}else if(hwbpInstance == HWBP5_INST)
		{
			EradHWBP5Regs.HWBP_CLEAR.bit.EVENT_CLR = 1;
		}else if(hwbpInstance == HWBP6_INST)
		{
			EradHWBP6Regs.HWBP_CLEAR.bit.EVENT_CLR = 1;
		}else if(hwbpInstance == HWBP7_INST)
		{
			EradHWBP7Regs.HWBP_CLEAR.bit.EVENT_CLR = 1;
		}else if(hwbpInstance == HWBP8_INST)
		{
			EradHWBP8Regs.HWBP_CLEAR.bit.EVENT_CLR = 1;
		}
	}
	EDIS;
}

//***********************************************************************************
//
//ERAD_HWBPConfig -	This function is used to configure the Enhanced Bus comparator unit. 
//					Inputs can be HWBP1_INST, HWBP2_INST etc and the 
//					configurations can be passed via a structure of type hwbpConfig.
//
//***********************************************************************************
void ERAD_HWBPConfig(Uint16 hwbpInstance,hwbpConfig hwbpCfg)
{
	EALLOW;
	if(hwbpInstance == HWBP1_INST)
	{
		EradHWBP1Regs.HWBP_CNTL.bit.BUS_SEL 	= hwbpCfg.BUS_SEL;
		EradHWBP1Regs.HWBP_CNTL.bit.COMP_MODE 	= hwbpCfg.COMP_MODE;
		EradHWBP1Regs.HWBP_REF 				= hwbpCfg.REF;
		EradHWBP1Regs.HWBP_MASK 				= hwbpCfg.MASK;
		EradHWBP1Regs.HWBP_CNTL.bit.STOP 		= hwbpCfg.DBGEVT;
		EradHWBP1Regs.HWBP_CNTL.bit.RTOSINT 	= hwbpCfg.RTOSINT;
	}else if(hwbpInstance == HWBP2_INST)
	{
		EradHWBP2Regs.HWBP_CNTL.bit.BUS_SEL 	= hwbpCfg.BUS_SEL;
		EradHWBP2Regs.HWBP_CNTL.bit.COMP_MODE 	= hwbpCfg.COMP_MODE;
		EradHWBP2Regs.HWBP_REF 				= hwbpCfg.REF;
		EradHWBP2Regs.HWBP_MASK 				= hwbpCfg.MASK;
		EradHWBP2Regs.HWBP_CNTL.bit.STOP 		= hwbpCfg.DBGEVT;
		EradHWBP2Regs.HWBP_CNTL.bit.RTOSINT 	= hwbpCfg.RTOSINT;
	}else if(hwbpInstance == HWBP3_INST)
	{
		EradHWBP3Regs.HWBP_CNTL.bit.BUS_SEL 	= hwbpCfg.BUS_SEL;
		EradHWBP3Regs.HWBP_CNTL.bit.COMP_MODE 	= hwbpCfg.COMP_MODE;
		EradHWBP3Regs.HWBP_REF 				= hwbpCfg.REF;
		EradHWBP3Regs.HWBP_MASK 				= hwbpCfg.MASK;
		EradHWBP3Regs.HWBP_CNTL.bit.STOP 		= hwbpCfg.DBGEVT;
		EradHWBP3Regs.HWBP_CNTL.bit.RTOSINT 	= hwbpCfg.RTOSINT;
	}else if(hwbpInstance == HWBP4_INST)
	{
		EradHWBP4Regs.HWBP_CNTL.bit.BUS_SEL 	= hwbpCfg.BUS_SEL;
		EradHWBP4Regs.HWBP_CNTL.bit.COMP_MODE 	= hwbpCfg.COMP_MODE;
		EradHWBP4Regs.HWBP_REF 				= hwbpCfg.REF;
		EradHWBP4Regs.HWBP_MASK 				= hwbpCfg.MASK;
		EradHWBP4Regs.HWBP_CNTL.bit.STOP 		= hwbpCfg.DBGEVT;
		EradHWBP4Regs.HWBP_CNTL.bit.RTOSINT 	= hwbpCfg.RTOSINT;
	}else if(hwbpInstance == HWBP5_INST)
	{
		EradHWBP5Regs.HWBP_CNTL.bit.BUS_SEL 	= hwbpCfg.BUS_SEL;
		EradHWBP5Regs.HWBP_CNTL.bit.COMP_MODE 	= hwbpCfg.COMP_MODE;
		EradHWBP5Regs.HWBP_REF 				= hwbpCfg.REF;
		EradHWBP5Regs.HWBP_MASK 				= hwbpCfg.MASK;
		EradHWBP5Regs.HWBP_CNTL.bit.STOP 		= hwbpCfg.DBGEVT;
		EradHWBP5Regs.HWBP_CNTL.bit.RTOSINT 	= hwbpCfg.RTOSINT;
	}else if(hwbpInstance == HWBP6_INST)
	{
		EradHWBP6Regs.HWBP_CNTL.bit.BUS_SEL 	= hwbpCfg.BUS_SEL;
		EradHWBP6Regs.HWBP_CNTL.bit.COMP_MODE 	= hwbpCfg.COMP_MODE;
		EradHWBP6Regs.HWBP_REF 				= hwbpCfg.REF;
		EradHWBP6Regs.HWBP_MASK 				= hwbpCfg.MASK;
		EradHWBP6Regs.HWBP_CNTL.bit.STOP 		= hwbpCfg.DBGEVT;
		EradHWBP6Regs.HWBP_CNTL.bit.RTOSINT 	= hwbpCfg.RTOSINT;
	}else if(hwbpInstance == HWBP7_INST)
	{
		EradHWBP7Regs.HWBP_CNTL.bit.BUS_SEL 	= hwbpCfg.BUS_SEL;
		EradHWBP7Regs.HWBP_CNTL.bit.COMP_MODE 	= hwbpCfg.COMP_MODE;
		EradHWBP7Regs.HWBP_REF 				= hwbpCfg.REF;
		EradHWBP7Regs.HWBP_MASK 				= hwbpCfg.MASK;
		EradHWBP7Regs.HWBP_CNTL.bit.STOP 		= hwbpCfg.DBGEVT;
		EradHWBP7Regs.HWBP_CNTL.bit.RTOSINT 	= hwbpCfg.RTOSINT;
	}else if(hwbpInstance == HWBP8_INST)
	{
		EradHWBP8Regs.HWBP_CNTL.bit.BUS_SEL 	= hwbpCfg.BUS_SEL;
		EradHWBP8Regs.HWBP_CNTL.bit.COMP_MODE 	= hwbpCfg.COMP_MODE;
		EradHWBP8Regs.HWBP_REF 				= hwbpCfg.REF;
		EradHWBP8Regs.HWBP_MASK 				= hwbpCfg.MASK;
		EradHWBP8Regs.HWBP_CNTL.bit.STOP 		= hwbpCfg.DBGEVT;
		EradHWBP8Regs.HWBP_CNTL.bit.RTOSINT 	= hwbpCfg.RTOSINT;
	}
	EDIS;
}

