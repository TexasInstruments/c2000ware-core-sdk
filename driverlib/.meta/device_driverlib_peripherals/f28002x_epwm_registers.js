let EPWMRegisters = [
	{ name: "TBCTL", description: "Time Base Control Register", offset: "0x0",
		bits: [
			{ name: "CTRMODE", description: "Counter Mode", size: "2", shift: "0", mask: "0x3" },
			{ name: "PHSEN", description: "Phase Load Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "PRDLD", description: "Active Period Load", size: "1", shift: "3", mask: "0x8" },
			{ name: "SWFSYNC", description: "Software Force Sync Pulse", size: "1", shift: "6", mask: "0x40" },
			{ name: "HSPCLKDIV", description: "High Speed TBCLK Pre-scaler", size: "3", shift: "7", mask: "0x380" },
			{ name: "CLKDIV", description: "Time Base Clock Pre-scaler", size: "3", shift: "10", mask: "0x1C00" },
			{ name: "PHSDIR", description: "Phase Direction Bit", size: "1", shift: "13", mask: "0x2000" },
			{ name: "FREE_SOFT", description: "Emulation Mode Bits", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "TBCTL2", description: "Time Base Control Register 2", offset: "0x1",
		bits: [
			{ name: "OSHTSYNCMODE", description: "One shot sync mode", size: "1", shift: "6", mask: "0x40" },
			{ name: "OSHTSYNC", description: "One shot sync", size: "1", shift: "7", mask: "0x80" },
			{ name: "PRDLDSYNC", description: "PRD Shadow to Active Load on SYNC Event", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "SYNCINSEL", description: "EPWMxSYNCIN Source Select Register", offset: "0x3",
		bits: [
			{ name: "SEL", description: "EPWMxSYNCI source select", size: "5", shift: "0", mask: "0x1F" },
		]
	},
	{ name: "TBCTR", description: "Time Base Counter Register", offset: "0x4",
		bits: [
		]
	},
	{ name: "TBSTS", description: "Time Base Status Register", offset: "0x5",
		bits: [
			{ name: "CTRDIR", description: "Counter Direction Status", size: "1", shift: "0", mask: "0x1" },
			{ name: "SYNCI", description: "External Input Sync Status", size: "1", shift: "1", mask: "0x2" },
			{ name: "CTRMAX", description: "Counter Max Latched Status", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "SYNCOUTEN", description: "EPWMxSYNCOUT Source Enable Register", offset: "0x6",
		bits: [
			{ name: "SWEN", description: "EPWMxSYNCO Software Force Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "ZEROEN", description: "EPWMxSYNCO Zero Count Event Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMPBEN", description: "EPWMxSYNCO Compare B Event Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMPCEN", description: "EPWMxSYNCO Compare C Event Enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "CMPDEN", description: "EPWMxSYNCO Compare D Event Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "DCAEVT1EN", description: "EPWMxSYNCO Digital Compare A Event 1 Sync Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "DCBEVT1EN", description: "EPWMxSYNCO Digital Compare B Event 1 Sync Enable", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "TBCTL3", description: "Time Base Control Register 3", offset: "0x7",
		bits: [
			{ name: "OSSFRCEN", description: "One Shot Sync Force Enable", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CMPCTL", description: "Counter Compare Control Register", offset: "0x8",
		bits: [
			{ name: "LOADAMODE", description: "Active Compare A Load", size: "2", shift: "0", mask: "0x3" },
			{ name: "LOADBMODE", description: "Active Compare B Load", size: "2", shift: "2", mask: "0xC" },
			{ name: "SHDWAMODE", description: "Compare A Register Block Operating Mode", size: "1", shift: "4", mask: "0x10" },
			{ name: "SHDWBMODE", description: "Compare B Register Block Operating Mode", size: "1", shift: "6", mask: "0x40" },
			{ name: "SHDWAFULL", description: "Compare A Shadow Register Full Status", size: "1", shift: "8", mask: "0x100" },
			{ name: "SHDWBFULL", description: "Compare B Shadow Register Full Status", size: "1", shift: "9", mask: "0x200" },
			{ name: "LOADASYNC", description: "Active Compare A Load on SYNC", size: "2", shift: "10", mask: "0xC00" },
			{ name: "LOADBSYNC", description: "Active Compare B Load on SYNC", size: "2", shift: "12", mask: "0x3000" },
		]
	},
	{ name: "CMPCTL2", description: "Counter Compare Control Register 2", offset: "0x9",
		bits: [
			{ name: "LOADCMODE", description: "Active Compare C Load", size: "2", shift: "0", mask: "0x3" },
			{ name: "LOADDMODE", description: "Active Compare D load", size: "2", shift: "2", mask: "0xC" },
			{ name: "SHDWCMODE", description: "Compare C Block Operating Mode", size: "1", shift: "4", mask: "0x10" },
			{ name: "SHDWDMODE", description: "Compare D Block Operating Mode", size: "1", shift: "6", mask: "0x40" },
			{ name: "LOADCSYNC", description: "Active Compare C Load on SYNC", size: "2", shift: "10", mask: "0xC00" },
			{ name: "LOADDSYNC", description: "Active Compare D Load on SYNC", size: "2", shift: "12", mask: "0x3000" },
		]
	},
	{ name: "DBCTL", description: "Dead-Band Generator Control Register", offset: "0xC",
		bits: [
			{ name: "OUT_MODE", description: "Dead Band Output Mode Control", size: "2", shift: "0", mask: "0x3" },
			{ name: "POLSEL", description: "Polarity Select Control", size: "2", shift: "2", mask: "0xC" },
			{ name: "IN_MODE", description: "Dead Band Input Select Mode Control", size: "2", shift: "4", mask: "0x30" },
			{ name: "LOADREDMODE", description: "Active DBRED Load Mode", size: "2", shift: "6", mask: "0xC0" },
			{ name: "LOADFEDMODE", description: "Active DBFED Load Mode", size: "2", shift: "8", mask: "0x300" },
			{ name: "SHDWDBREDMODE", description: "DBRED Block Operating Mode", size: "1", shift: "10", mask: "0x400" },
			{ name: "SHDWDBFEDMODE", description: "DBFED Block Operating Mode", size: "1", shift: "11", mask: "0x800" },
			{ name: "OUTSWAP", description: "Dead Band Output Swap Control", size: "2", shift: "12", mask: "0x3000" },
			{ name: "DEDB_MODE", description: "Dead Band Dual-Edge B Mode Control", size: "1", shift: "14", mask: "0x4000" },
			{ name: "HALFCYCLE", description: "Half Cycle Clocking Enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "DBCTL2", description: "Dead-Band Generator Control Register 2", offset: "0xD",
		bits: [
			{ name: "LOADDBCTLMODE", description: "DBCTL Load from Shadow Mode Select", size: "2", shift: "0", mask: "0x3" },
			{ name: "SHDWDBCTLMODE", description: "DBCTL Load mode Select", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "AQCTL", description: "Action Qualifier Control Register", offset: "0x10",
		bits: [
			{ name: "LDAQAMODE", description: "Action Qualifier A Load Select", size: "2", shift: "0", mask: "0x3" },
			{ name: "LDAQBMODE", description: "Action Qualifier B Load Select", size: "2", shift: "2", mask: "0xC" },
			{ name: "SHDWAQAMODE", description: "Action Qualifer A Operating Mode", size: "1", shift: "4", mask: "0x10" },
			{ name: "SHDWAQBMODE", description: "Action Qualifier B Operating Mode", size: "1", shift: "6", mask: "0x40" },
			{ name: "LDAQASYNC", description: "AQCTLA Register Load on SYNC", size: "2", shift: "8", mask: "0x300" },
			{ name: "LDAQBSYNC", description: "AQCTLB Register Load on SYNC", size: "2", shift: "10", mask: "0xC00" },
		]
	},
	{ name: "AQTSRCSEL", description: "Action Qualifier Trigger Event Source Select Register", offset: "0x11",
		bits: [
			{ name: "T1SEL", description: "T1 Event Source Select Bits", size: "4", shift: "0", mask: "0xF" },
			{ name: "T2SEL", description: "T2 Event Source Select Bits", size: "4", shift: "4", mask: "0xF0" },
		]
	},
	{ name: "PCCTL", description: "PWM Chopper Control Register", offset: "0x14",
		bits: [
			{ name: "CHPEN", description: "PWM chopping enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "OSHTWTH", description: "One-shot pulse width", size: "4", shift: "1", mask: "0x1E" },
			{ name: "CHPFREQ", description: "Chopping clock frequency", size: "3", shift: "5", mask: "0xE0" },
			{ name: "CHPDUTY", description: "Chopping clock Duty cycle", size: "3", shift: "8", mask: "0x700" },
		]
	},
	{ name: "VCAPCTL", description: "Valley Capture Control Register", offset: "0x18",
		bits: [
			{ name: "VCAPE", description: "Valley  Capture mode", size: "1", shift: "0", mask: "0x1" },
			{ name: "VCAPSTART", description: "Valley  Capture Start", size: "1", shift: "1", mask: "0x2" },
			{ name: "TRIGSEL", description: "Capture Trigger Select", size: "3", shift: "2", mask: "0x1C" },
			{ name: "VDELAYDIV", description: "Valley Delay Mode Divide Enable", size: "3", shift: "7", mask: "0x380" },
			{ name: "EDGEFILTDLYSEL", description: "Valley Switching Mode Delay Select", size: "1", shift: "10", mask: "0x400" },
		]
	},
	{ name: "VCNTCFG", description: "Valley Counter Config Register", offset: "0x19",
		bits: [
			{ name: "STARTEDGE", description: "Counter Start Edge Selection", size: "4", shift: "0", mask: "0xF" },
			{ name: "STARTEDGESTS", description: "Start Edge Status Bit", size: "1", shift: "7", mask: "0x80" },
			{ name: "STOPEDGE", description: "Counter Start Edge Selection", size: "4", shift: "8", mask: "0xF00" },
			{ name: "STOPEDGESTS", description: "Stop Edge Status Bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "HRCNFG", description: "HRPWM Configuration Register", offset: "0x20",
		bits: [
			{ name: "EDGMODE", description: "ePWMxA Edge Mode Select Bits", size: "2", shift: "0", mask: "0x3" },
			{ name: "CTLMODE", description: "ePWMxA Control Mode Select Bits", size: "1", shift: "2", mask: "0x4" },
			{ name: "HRLOAD", description: "ePWMxA Shadow Mode Select Bits", size: "2", shift: "3", mask: "0x18" },
			{ name: "SELOUTB", description: "EPWMB Output Selection Bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "AUTOCONV", description: "Autoconversion Bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "SWAPAB", description: "Swap EPWMA and EPWMB Outputs Bit", size: "1", shift: "7", mask: "0x80" },
			{ name: "EDGMODEB", description: "ePWMxB Edge Mode Select Bits", size: "2", shift: "8", mask: "0x300" },
			{ name: "CTLMODEB", description: "ePWMxB Control Mode Select Bits", size: "1", shift: "10", mask: "0x400" },
			{ name: "HRLOADB", description: "ePWMxB Shadow Mode Select Bits", size: "2", shift: "11", mask: "0x1800" },
		]
	},
	{ name: "HRPWR", description: "HRPWM Power Register", offset: "0x21",
		bits: [
			{ name: "CALPWRON", description: "Calibration Power On", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "HRMSTEP", description: "HRPWM MEP Step Register", offset: "0x26",
		bits: [
			{ name: "HRMSTEP", description: "High Resolution Micro Step Value", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "HRCNFG2", description: "HRPWM Configuration 2 Register", offset: "0x27",
		bits: [
			{ name: "EDGMODEDB", description: "Dead-Band Edge-Mode Select Bits", size: "2", shift: "0", mask: "0x3" },
			{ name: "CTLMODEDBRED", description: "DBRED Control Mode Select Bits", size: "2", shift: "2", mask: "0xC" },
			{ name: "CTLMODEDBFED", description: "DBFED Control Mode Select Bits", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "HRPCTL", description: "High Resolution Period Control Register", offset: "0x2D",
		bits: [
			{ name: "HRPE", description: "High Resolution Period Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "PWMSYNCSEL", description: "EPWMSYNCPER Source Select", size: "1", shift: "1", mask: "0x2" },
			{ name: "TBPHSHRLOADE", description: "TBPHSHR Load Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "PWMSYNCSELX", description: "EPWMSYNCPER Extended Source Select Bit:", size: "3", shift: "4", mask: "0x70" },
		]
	},
	{ name: "TRREM", description: "HRPWM High Resolution Remainder Register", offset: "0x2E",
		bits: [
			{ name: "TRREM", description: "HRPWM Remainder Bits", size: "11", shift: "0", mask: "0x7FF" },
		]
	},
	{ name: "GLDCTL", description: "Global PWM Load Control Register", offset: "0x34",
		bits: [
			{ name: "GLD", description: "Global Shadow to Active load event control", size: "1", shift: "0", mask: "0x1" },
			{ name: "GLDMODE", description: "Shadow to Active Global Load Pulse Selection", size: "4", shift: "1", mask: "0x1E" },
			{ name: "OSHTMODE", description: "One Shot Load mode control bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "GLDPRD", description: "Global Load Strobe Period Select Register", size: "3", shift: "7", mask: "0x380" },
			{ name: "GLDCNT", description: "Global Load Strobe Counter Register", size: "3", shift: "10", mask: "0x1C00" },
		]
	},
	{ name: "GLDCFG", description: "Global PWM Load Config Register", offset: "0x35",
		bits: [
			{ name: "TBPRD_TBPRDHR", description: "Global load event configuration for TBPRD:TBPRDHR", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMPA_CMPAHR", description: "Global load event configuration for CMPA:CMPAHR", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMPB_CMPBHR", description: "Global load event configuration for CMPB:CMPBHR", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMPC", description: "Global load event configuration for CMPC", size: "1", shift: "3", mask: "0x8" },
			{ name: "CMPD", description: "Global load event configuration for CMPD", size: "1", shift: "4", mask: "0x10" },
			{ name: "DBRED_DBREDHR", description: "Global load event configuration for DBRED:DBREDHR", size: "1", shift: "5", mask: "0x20" },
			{ name: "DBFED_DBFEDHR", description: "Global load event configuration for DBFED:DBFEDHR", size: "1", shift: "6", mask: "0x40" },
			{ name: "DBCTL", description: "Global load event configuration for DBCTL", size: "1", shift: "7", mask: "0x80" },
			{ name: "AQCTLA_AQCTLA2", description: "Global load event configuration for AQCTLA/A2", size: "1", shift: "8", mask: "0x100" },
			{ name: "AQCTLB_AQCTLB2", description: "Global load event configuration for AQCTLB/B2", size: "1", shift: "9", mask: "0x200" },
			{ name: "AQCSFRC", description: "Global load event configuration for AQCSFRC", size: "1", shift: "10", mask: "0x400" },
		]
	},
	{ name: "XLINK", description: "EPWMx Link Register", offset: "0x38",
		bits: [
			{ name: "TBPRDLINK", description: "TBPRD:TBPRDHR  Link", size: "4", shift: "0", mask: "0xF" },
			{ name: "CMPALINK", description: "CMPA:CMPAHR Link", size: "4", shift: "4", mask: "0xF0" },
			{ name: "CMPBLINK", description: "CMPB:CMPBHR Link", size: "4", shift: "8", mask: "0xF00" },
			{ name: "CMPCLINK", description: "CMPC Link", size: "4", shift: "12", mask: "0xF000" },
			{ name: "CMPDLINK", description: "CMPD Link", size: "4", shift: "16", mask: "0xF0000" },
			{ name: "GLDCTL2LINK", description: "GLDCTL2 Link", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "AQCTLA", description: "Action Qualifier Control Register For Output A", offset: "0x40",
		bits: [
			{ name: "ZRO", description: "Action Counter = Zero", size: "2", shift: "0", mask: "0x3" },
			{ name: "PRD", description: "Action Counter = Period", size: "2", shift: "2", mask: "0xC" },
			{ name: "CAU", description: "Action Counter = Compare A Up", size: "2", shift: "4", mask: "0x30" },
			{ name: "CAD", description: "Action Counter = Compare A Down", size: "2", shift: "6", mask: "0xC0" },
			{ name: "CBU", description: "Action Counter = Compare B Up", size: "2", shift: "8", mask: "0x300" },
			{ name: "CBD", description: "Action Counter = Compare B Down", size: "2", shift: "10", mask: "0xC00" },
		]
	},
	{ name: "AQCTLA2", description: "Additional Action Qualifier Control Register For Output A", offset: "0x41",
		bits: [
			{ name: "T1U", description: "Action when event occurs on T1 in UP-Count", size: "2", shift: "0", mask: "0x3" },
			{ name: "T1D", description: "Action when event occurs on T1 in DOWN-Count", size: "2", shift: "2", mask: "0xC" },
			{ name: "T2U", description: "Action when event occurs on T2 in UP-Count", size: "2", shift: "4", mask: "0x30" },
			{ name: "T2D", description: "Action when event occurs on T2 in DOWN-Count", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "AQCTLB", description: "Action Qualifier Control Register For Output B", offset: "0x42",
		bits: [
			{ name: "ZRO", description: "Action Counter = Zero", size: "2", shift: "0", mask: "0x3" },
			{ name: "PRD", description: "Action Counter = Period", size: "2", shift: "2", mask: "0xC" },
			{ name: "CAU", description: "Action Counter = Compare A Up", size: "2", shift: "4", mask: "0x30" },
			{ name: "CAD", description: "Action Counter = Compare A Down", size: "2", shift: "6", mask: "0xC0" },
			{ name: "CBU", description: "Action Counter = Compare B Up", size: "2", shift: "8", mask: "0x300" },
			{ name: "CBD", description: "Action Counter = Compare B Down", size: "2", shift: "10", mask: "0xC00" },
		]
	},
	{ name: "AQCTLB2", description: "Additional Action Qualifier Control Register For Output B", offset: "0x43",
		bits: [
			{ name: "T1U", description: "Action when event occurs on T1 in UP-Count", size: "2", shift: "0", mask: "0x3" },
			{ name: "T1D", description: "Action when event occurs on T1 in DOWN-Count", size: "2", shift: "2", mask: "0xC" },
			{ name: "T2U", description: "Action when event occurs on T2 in UP-Count", size: "2", shift: "4", mask: "0x30" },
			{ name: "T2D", description: "Action when event occurs on T2 in DOWN-Count", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "AQSFRC", description: "Action Qualifier Software Force Register", offset: "0x47",
		bits: [
			{ name: "ACTSFA", description: "Action when One-time SW Force A Invoked", size: "2", shift: "0", mask: "0x3" },
			{ name: "OTSFA", description: "One-time SW Force A Output", size: "1", shift: "2", mask: "0x4" },
			{ name: "ACTSFB", description: "Action when One-time SW Force B Invoked", size: "2", shift: "3", mask: "0x18" },
			{ name: "OTSFB", description: "One-time SW Force A Output", size: "1", shift: "5", mask: "0x20" },
			{ name: "RLDCSF", description: "Reload from Shadow Options", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "AQCSFRC", description: "Action Qualifier Continuous S/W Force Register", offset: "0x49",
		bits: [
			{ name: "CSFA", description: "Continuous Software Force on output A", size: "2", shift: "0", mask: "0x3" },
			{ name: "CSFB", description: "Continuous Software Force on output B", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "DBREDHR", description: "Dead-Band Generator Rising Edge Delay High Resolution", offset: "0x50",
		bits: [
			{ name: "DBREDHR", description: "DBREDHR High Resolution Bits", size: "7", shift: "9", mask: "0xFE00" },
		]
	},
	{ name: "DBRED", description: "Dead-Band Generator Rising Edge Delay High Resolution", offset: "0x51",
		bits: [
			{ name: "DBRED", description: "Rising edge delay value", size: "14", shift: "0", mask: "0x3FFF" },
		]
	},
	{ name: "DBFEDHR", description: "Dead-Band Generator Falling Edge Delay High Resolution", offset: "0x52",
		bits: [
			{ name: "DBFEDHR", description: "DBFEDHR High Resolution Bits", size: "7", shift: "9", mask: "0xFE00" },
		]
	},
	{ name: "DBFED", description: "Dead-Band Generator Falling Edge Delay Count Register", offset: "0x53",
		bits: [
			{ name: "DBFED", description: "Falling edge delay value", size: "14", shift: "0", mask: "0x3FFF" },
		]
	},
	{ name: "TBPHS", description: "Time Base Phase High", offset: "0x60",
		bits: [
			{ name: "TBPHSHR", description: "Extension Register for HRPWM Phase (8-bits)", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "TBPHS", description: "Phase Offset Register", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "TBPRDHR", description: "Time Base Period High Resolution Register", offset: "0x62",
		bits: [
		]
	},
	{ name: "TBPRD", description: "Time Base Period Register", offset: "0x63",
		bits: [
		]
	},
	{ name: "CMPA", description: "Counter Compare A Register", offset: "0x6A",
		bits: [
			{ name: "CMPAHR", description: "Compare A HRPWM Extension Register", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "CMPA", description: "Compare A Register", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CMPB", description: "Compare B Register", offset: "0x6C",
		bits: [
			{ name: "CMPBHR", description: "Compare B High Resolution Bits", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "CMPB", description: "Compare B Register", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CMPC", description: "Counter Compare C Register", offset: "0x6F",
		bits: [
		]
	},
	{ name: "CMPD", description: "Counter Compare D Register", offset: "0x71",
		bits: [
		]
	},
	{ name: "GLDCTL2", description: "Global PWM Load Control Register 2", offset: "0x74",
		bits: [
			{ name: "OSHTLD", description: "Enable reload event in one shot mode", size: "1", shift: "0", mask: "0x1" },
			{ name: "GFRCLD", description: "Force reload event in one shot mode", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SWVDELVAL", description: "Software Valley Mode Delay Register", offset: "0x77",
		bits: [
		]
	},
	{ name: "TZSEL", description: "Trip Zone Select Register", offset: "0x80",
		bits: [
			{ name: "CBC1", description: "TZ1 CBC select", size: "1", shift: "0", mask: "0x1" },
			{ name: "CBC2", description: "TZ2 CBC select", size: "1", shift: "1", mask: "0x2" },
			{ name: "CBC3", description: "TZ3 CBC select", size: "1", shift: "2", mask: "0x4" },
			{ name: "CBC4", description: "TZ4 CBC select", size: "1", shift: "3", mask: "0x8" },
			{ name: "CBC5", description: "TZ5 CBC select", size: "1", shift: "4", mask: "0x10" },
			{ name: "CBC6", description: "TZ6 CBC select", size: "1", shift: "5", mask: "0x20" },
			{ name: "DCAEVT2", description: "DCAEVT2 CBC select", size: "1", shift: "6", mask: "0x40" },
			{ name: "DCBEVT2", description: "DCBEVT2 CBC select", size: "1", shift: "7", mask: "0x80" },
			{ name: "OSHT1", description: "One-shot TZ1 select", size: "1", shift: "8", mask: "0x100" },
			{ name: "OSHT2", description: "One-shot TZ2 select", size: "1", shift: "9", mask: "0x200" },
			{ name: "OSHT3", description: "One-shot TZ3 select", size: "1", shift: "10", mask: "0x400" },
			{ name: "OSHT4", description: "One-shot TZ4 select", size: "1", shift: "11", mask: "0x800" },
			{ name: "OSHT5", description: "One-shot TZ5 select", size: "1", shift: "12", mask: "0x1000" },
			{ name: "OSHT6", description: "One-shot TZ6 select", size: "1", shift: "13", mask: "0x2000" },
			{ name: "DCAEVT1", description: "One-shot DCAEVT1 select", size: "1", shift: "14", mask: "0x4000" },
			{ name: "DCBEVT1", description: "One-shot DCBEVT1 select", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "TZDCSEL", description: "Trip Zone Digital Comparator Select Register", offset: "0x82",
		bits: [
			{ name: "DCAEVT1", description: "Digital Compare Output A Event 1", size: "3", shift: "0", mask: "0x7" },
			{ name: "DCAEVT2", description: "Digital Compare Output A Event 2", size: "3", shift: "3", mask: "0x38" },
			{ name: "DCBEVT1", description: "Digital Compare Output B Event 1", size: "3", shift: "6", mask: "0x1C0" },
			{ name: "DCBEVT2", description: "Digital Compare Output B Event 2", size: "3", shift: "9", mask: "0xE00" },
		]
	},
	{ name: "TZCTL", description: "Trip Zone Control Register", offset: "0x84",
		bits: [
			{ name: "TZA", description: "TZ1 to TZ6 Trip Action On EPWMxA", size: "2", shift: "0", mask: "0x3" },
			{ name: "TZB", description: "TZ1 to TZ6 Trip Action On EPWMxB", size: "2", shift: "2", mask: "0xC" },
			{ name: "DCAEVT1", description: "EPWMxA action on DCAEVT1", size: "2", shift: "4", mask: "0x30" },
			{ name: "DCAEVT2", description: "EPWMxA action on DCAEVT2", size: "2", shift: "6", mask: "0xC0" },
			{ name: "DCBEVT1", description: "EPWMxB action on DCBEVT1", size: "2", shift: "8", mask: "0x300" },
			{ name: "DCBEVT2", description: "EPWMxB action on DCBEVT2", size: "2", shift: "10", mask: "0xC00" },
		]
	},
	{ name: "TZCTL2", description: "Additional Trip Zone Control Register", offset: "0x85",
		bits: [
			{ name: "TZAU", description: "Trip Action On EPWMxA while Count direction is UP", size: "3", shift: "0", mask: "0x7" },
			{ name: "TZAD", description: "Trip Action On EPWMxA while Count direction is DOWN", size: "3", shift: "3", mask: "0x38" },
			{ name: "TZBU", description: "Trip Action On EPWMxB while Count direction is UP", size: "3", shift: "6", mask: "0x1C0" },
			{ name: "TZBD", description: "Trip Action On EPWMxB while Count direction is DOWN", size: "3", shift: "9", mask: "0xE00" },
			{ name: "ETZE", description: "TZCTL2 Enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "TZCTLDCA", description: "Trip Zone Control Register Digital Compare A", offset: "0x86",
		bits: [
			{ name: "DCAEVT1U", description: "DCAEVT1 Action On EPWMxA while Count direction is UP", size: "3", shift: "0", mask: "0x7" },
			{ name: "DCAEVT1D", description: "DCAEVT1 Action On EPWMxA while Count direction is", size: "3", shift: "3", mask: "0x38" },
			{ name: "DCAEVT2U", description: "DCAEVT2 Action On EPWMxA while Count direction is UP", size: "3", shift: "6", mask: "0x1C0" },
			{ name: "DCAEVT2D", description: "DCAEVT2 Action On EPWMxA while Count direction is", size: "3", shift: "9", mask: "0xE00" },
		]
	},
	{ name: "TZCTLDCB", description: "Trip Zone Control Register Digital Compare B", offset: "0x87",
		bits: [
			{ name: "DCBEVT1U", description: "DCBEVT1 Action On EPWMxA while Count direction is UP", size: "3", shift: "0", mask: "0x7" },
			{ name: "DCBEVT1D", description: "DCBEVT1 Action On EPWMxA while Count direction is", size: "3", shift: "3", mask: "0x38" },
			{ name: "DCBEVT2U", description: "DCBEVT2 Action On EPWMxA while Count direction is UP", size: "3", shift: "6", mask: "0x1C0" },
			{ name: "DCBEVT2D", description: "DCBEVT2 Action On EPWMxA while Count direction is", size: "3", shift: "9", mask: "0xE00" },
		]
	},
	{ name: "TZEINT", description: "Trip Zone Enable Interrupt Register", offset: "0x8D",
		bits: [
			{ name: "CBC", description: "Trip Zones Cycle By Cycle Int Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "OST", description: "Trip Zones One Shot Int Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "DCAEVT1", description: "Digital Compare A Event 1 Int Enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "DCAEVT2", description: "Digital Compare A Event 2 Int Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "DCBEVT1", description: "Digital Compare B Event 1 Int Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "DCBEVT2", description: "Digital Compare B Event 2 Int Enable", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "TZFLG", description: "Trip Zone Flag Register", offset: "0x93",
		bits: [
			{ name: "INT", description: "Global Int Status Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CBC", description: "Trip Zones Cycle By Cycle Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "OST", description: "Trip Zones One Shot Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "DCAEVT1", description: "Digital Compare A Event 1 Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "DCAEVT2", description: "Digital Compare A Event 2 Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "DCBEVT1", description: "Digital Compare B Event 1 Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "DCBEVT2", description: "Digital Compare B Event 2 Flag", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "TZCBCFLG", description: "Trip Zone CBC Flag Register", offset: "0x94",
		bits: [
			{ name: "CBC1", description: "Latched Status Flag for CBC1 Trip Latch", size: "1", shift: "0", mask: "0x1" },
			{ name: "CBC2", description: "Latched Status Flag for CBC2 Trip Latch", size: "1", shift: "1", mask: "0x2" },
			{ name: "CBC3", description: "Latched Status Flag for CBC3 Trip Latch", size: "1", shift: "2", mask: "0x4" },
			{ name: "CBC4", description: "Latched Status Flag for CBC4 Trip Latch", size: "1", shift: "3", mask: "0x8" },
			{ name: "CBC5", description: "Latched Status Flag for CBC5 Trip Latch", size: "1", shift: "4", mask: "0x10" },
			{ name: "CBC6", description: "Latched Status Flag for CBC6 Trip Latch", size: "1", shift: "5", mask: "0x20" },
			{ name: "DCAEVT2", description: "Latched Status Flag for Digital Compare Output A Event 2", size: "1", shift: "6", mask: "0x40" },
			{ name: "DCBEVT2", description: "Latched Status Flag for Digital Compare Output B Event 2", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "TZOSTFLG", description: "Trip Zone OST Flag Register", offset: "0x95",
		bits: [
			{ name: "OST1", description: "Latched Status Flag for OST1 Trip Latch", size: "1", shift: "0", mask: "0x1" },
			{ name: "OST2", description: "Latched Status Flag for OST2 Trip Latch", size: "1", shift: "1", mask: "0x2" },
			{ name: "OST3", description: "Latched Status Flag for OST3 Trip Latch", size: "1", shift: "2", mask: "0x4" },
			{ name: "OST4", description: "Latched Status Flag for OST4 Trip Latch", size: "1", shift: "3", mask: "0x8" },
			{ name: "OST5", description: "Latched Status Flag for OST5 Trip Latch", size: "1", shift: "4", mask: "0x10" },
			{ name: "OST6", description: "Latched Status Flag for OST6 Trip Latch", size: "1", shift: "5", mask: "0x20" },
			{ name: "DCAEVT1", description: "Latched Status Flag for Digital Compare Output A Event 1", size: "1", shift: "6", mask: "0x40" },
			{ name: "DCBEVT1", description: "Latched Status Flag for Digital Compare Output B Event 1", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "TZCLR", description: "Trip Zone Clear Register", offset: "0x97",
		bits: [
			{ name: "INT", description: "Global Interrupt Clear Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CBC", description: "Cycle-By-Cycle Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "OST", description: "One-Shot Flag Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "DCAEVT1", description: "DCAVET1 Flag Clear", size: "1", shift: "3", mask: "0x8" },
			{ name: "DCAEVT2", description: "DCAEVT2 Flag Clear", size: "1", shift: "4", mask: "0x10" },
			{ name: "DCBEVT1", description: "DCBEVT1 Flag Clear", size: "1", shift: "5", mask: "0x20" },
			{ name: "DCBEVT2", description: "DCBEVT2 Flag Clear", size: "1", shift: "6", mask: "0x40" },
			{ name: "CBCPULSE", description: "Clear Pulse for CBC Trip Latch", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "TZCBCCLR", description: "Trip Zone CBC Clear Register", offset: "0x98",
		bits: [
			{ name: "CBC1", description: "Clear Flag for Cycle-By-Cycle (CBC1) Trip Latch", size: "1", shift: "0", mask: "0x1" },
			{ name: "CBC2", description: "Clear Flag for Cycle-By-Cycle (CBC2) Trip Latch", size: "1", shift: "1", mask: "0x2" },
			{ name: "CBC3", description: "Clear Flag for Cycle-By-Cycle (CBC3) Trip Latch", size: "1", shift: "2", mask: "0x4" },
			{ name: "CBC4", description: "Clear Flag for Cycle-By-Cycle (CBC4) Trip Latch", size: "1", shift: "3", mask: "0x8" },
			{ name: "CBC5", description: "Clear Flag for Cycle-By-Cycle (CBC5) Trip Latch", size: "1", shift: "4", mask: "0x10" },
			{ name: "CBC6", description: "Clear Flag for Cycle-By-Cycle (CBC6) Trip Latch", size: "1", shift: "5", mask: "0x20" },
			{ name: "DCAEVT2", description: "Clear Flag forDCAEVT2 selected for CBC", size: "1", shift: "6", mask: "0x40" },
			{ name: "DCBEVT2", description: "Clear Flag for DCBEVT2 selected for CBC", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "TZOSTCLR", description: "Trip Zone OST Clear Register", offset: "0x99",
		bits: [
			{ name: "OST1", description: "Clear Flag for Oneshot (OST1) Trip Latch", size: "1", shift: "0", mask: "0x1" },
			{ name: "OST2", description: "Clear Flag for Oneshot (OST2) Trip Latch", size: "1", shift: "1", mask: "0x2" },
			{ name: "OST3", description: "Clear Flag for Oneshot (OST3) Trip Latch", size: "1", shift: "2", mask: "0x4" },
			{ name: "OST4", description: "Clear Flag for Oneshot (OST4) Trip Latch", size: "1", shift: "3", mask: "0x8" },
			{ name: "OST5", description: "Clear Flag for Oneshot (OST5) Trip Latch", size: "1", shift: "4", mask: "0x10" },
			{ name: "OST6", description: "Clear Flag for Oneshot (OST6) Trip Latch", size: "1", shift: "5", mask: "0x20" },
			{ name: "DCAEVT1", description: "Clear Flag for DCAEVT1 selected for OST", size: "1", shift: "6", mask: "0x40" },
			{ name: "DCBEVT1", description: "Clear Flag for DCBEVT1 selected for OST", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "TZFRC", description: "Trip Zone Force Register", offset: "0x9B",
		bits: [
			{ name: "CBC", description: "Force Trip Zones Cycle By Cycle Event", size: "1", shift: "1", mask: "0x2" },
			{ name: "OST", description: "Force Trip Zones One Shot Event", size: "1", shift: "2", mask: "0x4" },
			{ name: "DCAEVT1", description: "Force Digital Compare A Event 1", size: "1", shift: "3", mask: "0x8" },
			{ name: "DCAEVT2", description: "Force Digital Compare A Event 2", size: "1", shift: "4", mask: "0x10" },
			{ name: "DCBEVT1", description: "Force Digital Compare B Event 1", size: "1", shift: "5", mask: "0x20" },
			{ name: "DCBEVT2", description: "Force Digital Compare B Event 2", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "ETSEL", description: "Event Trigger Selection Register", offset: "0xA4",
		bits: [
			{ name: "INTSEL", description: "EPWMxINTn Select", size: "3", shift: "0", mask: "0x7" },
			{ name: "INTEN", description: "EPWMxINTn Enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "SOCASELCMP", description: "EPWMxSOCA Compare Select", size: "1", shift: "4", mask: "0x10" },
			{ name: "SOCBSELCMP", description: "EPWMxSOCB Compare Select", size: "1", shift: "5", mask: "0x20" },
			{ name: "INTSELCMP", description: "EPWMxINT Compare Select", size: "1", shift: "6", mask: "0x40" },
			{ name: "SOCASEL", description: "Start of Conversion A Select", size: "3", shift: "8", mask: "0x700" },
			{ name: "SOCAEN", description: "Start of Conversion A Enable", size: "1", shift: "11", mask: "0x800" },
			{ name: "SOCBSEL", description: "Start of Conversion B Select", size: "3", shift: "12", mask: "0x7000" },
			{ name: "SOCBEN", description: "Start of Conversion B Enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "ETPS", description: "Event Trigger Pre-Scale Register", offset: "0xA6",
		bits: [
			{ name: "INTPRD", description: "EPWMxINTn Period Select", size: "2", shift: "0", mask: "0x3" },
			{ name: "INTCNT", description: "EPWMxINTn Counter Register", size: "2", shift: "2", mask: "0xC" },
			{ name: "INTPSSEL", description: "EPWMxINTn Pre-Scale Selection Bits", size: "1", shift: "4", mask: "0x10" },
			{ name: "SOCPSSEL", description: "EPWMxSOC A/B  Pre-Scale Selection Bits", size: "1", shift: "5", mask: "0x20" },
			{ name: "SOCAPRD", description: "EPWMxSOCA Period Select", size: "2", shift: "8", mask: "0x300" },
			{ name: "SOCACNT", description: "EPWMxSOCA Counter Register", size: "2", shift: "10", mask: "0xC00" },
			{ name: "SOCBPRD", description: "EPWMxSOCB Period Select", size: "2", shift: "12", mask: "0x3000" },
			{ name: "SOCBCNT", description: "EPWMxSOCB Counter", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "ETFLG", description: "Event Trigger Flag Register", offset: "0xA8",
		bits: [
			{ name: "INT", description: "EPWMxINTn Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "SOCA", description: "EPWMxSOCA Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "SOCB", description: "EPWMxSOCB Flag", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "ETCLR", description: "Event Trigger Clear Register", offset: "0xAA",
		bits: [
			{ name: "INT", description: "EPWMxINTn Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "SOCA", description: "EPWMxSOCA Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "SOCB", description: "EPWMxSOCB Clear", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "ETFRC", description: "Event Trigger Force Register", offset: "0xAC",
		bits: [
			{ name: "INT", description: "EPWMxINTn Force", size: "1", shift: "0", mask: "0x1" },
			{ name: "SOCA", description: "EPWMxSOCA Force", size: "1", shift: "2", mask: "0x4" },
			{ name: "SOCB", description: "EPWMxSOCB Force", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "ETINTPS", description: "Event-Trigger Interrupt Pre-Scale Register", offset: "0xAE",
		bits: [
			{ name: "INTPRD2", description: "EPWMxINTn Period Select", size: "4", shift: "0", mask: "0xF" },
			{ name: "INTCNT2", description: "EPWMxINTn Counter Register", size: "4", shift: "4", mask: "0xF0" },
		]
	},
	{ name: "ETSOCPS", description: "Event-Trigger SOC Pre-Scale Register", offset: "0xB0",
		bits: [
			{ name: "SOCAPRD2", description: "EPWMxSOCA Period Select", size: "4", shift: "0", mask: "0xF" },
			{ name: "SOCACNT2", description: "EPWMxSOCA Counter Register", size: "4", shift: "4", mask: "0xF0" },
			{ name: "SOCBPRD2", description: "EPWMxSOCB Period Select", size: "4", shift: "8", mask: "0xF00" },
			{ name: "SOCBCNT2", description: "EPWMxSOCB Counter Register", size: "4", shift: "12", mask: "0xF000" },
		]
	},
	{ name: "ETCNTINITCTL", description: "Event-Trigger Counter Initialization Control Register", offset: "0xB2",
		bits: [
			{ name: "INTINITFRC", description: "EPWMxINT Counter Initialization Force", size: "1", shift: "10", mask: "0x400" },
			{ name: "SOCAINITFRC", description: "EPWMxSOCA Counter Initialization Force", size: "1", shift: "11", mask: "0x800" },
			{ name: "SOCBINITFRC", description: "EPWMxSOCB Counter Initialization Force", size: "1", shift: "12", mask: "0x1000" },
			{ name: "INTINITEN", description: "EPWMxINT Counter Initialization Enable", size: "1", shift: "13", mask: "0x2000" },
			{ name: "SOCAINITEN", description: "EPWMxSOCA Counter Initialization Enable", size: "1", shift: "14", mask: "0x4000" },
			{ name: "SOCBINITEN", description: "EPWMxSOCB Counter Initialization Enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "ETCNTINIT", description: "Event-Trigger Counter Initialization Register", offset: "0xB4",
		bits: [
			{ name: "INTINIT", description: "EPWMxINT Counter Initialization Bits", size: "4", shift: "0", mask: "0xF" },
			{ name: "SOCAINIT", description: "EPWMxSOCA Counter Initialization Bits", size: "4", shift: "4", mask: "0xF0" },
			{ name: "SOCBINIT", description: "EPWMxSOCB Counter Initialization Bits", size: "4", shift: "8", mask: "0xF00" },
		]
	},
	{ name: "DCTRIPSEL", description: "Digital Compare Trip Select Register", offset: "0xC0",
		bits: [
			{ name: "DCAHCOMPSEL", description: "Digital Compare A High COMP Input Select", size: "4", shift: "0", mask: "0xF" },
			{ name: "DCALCOMPSEL", description: "Digital Compare A Low COMP Input Select", size: "4", shift: "4", mask: "0xF0" },
			{ name: "DCBHCOMPSEL", description: "Digital Compare B High COMP Input Select", size: "4", shift: "8", mask: "0xF00" },
			{ name: "DCBLCOMPSEL", description: "Digital Compare B Low COMP Input Select", size: "4", shift: "12", mask: "0xF000" },
		]
	},
	{ name: "DCACTL", description: "Digital Compare A Control Register", offset: "0xC3",
		bits: [
			{ name: "EVT1SRCSEL", description: "DCAEVT1 Source Signal", size: "1", shift: "0", mask: "0x1" },
			{ name: "EVT1FRCSYNCSEL", description: "DCAEVT1 Force Sync Signal", size: "1", shift: "1", mask: "0x2" },
			{ name: "EVT1SOCE", description: "DCAEVT1 SOC Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "EVT1SYNCE", description: "DCAEVT1 SYNC Enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "EVT1LATSEL", description: "DCAEVT1 Latched signal select", size: "1", shift: "4", mask: "0x10" },
			{ name: "EVT1LATCLRSEL", description: "DCAEVT1 Latched clear source select", size: "2", shift: "5", mask: "0x60" },
			{ name: "EVT1LAT", description: "Indicates the status of DCAEVT1LAT signal.", size: "1", shift: "7", mask: "0x80" },
			{ name: "EVT2SRCSEL", description: "DCAEVT2 Source Signal", size: "1", shift: "8", mask: "0x100" },
			{ name: "EVT2FRCSYNCSEL", description: "DCAEVT2 Force Sync Signal", size: "1", shift: "9", mask: "0x200" },
			{ name: "EVT2LATSEL", description: "DCAEVT2 Latched signal select", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EVT2LATCLRSEL", description: "DCAEVT2 Latched clear source select", size: "2", shift: "13", mask: "0x6000" },
			{ name: "EVT2LAT", description: "Indicates the status of DCAEVT2LAT signal.", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "DCBCTL", description: "Digital Compare B Control Register", offset: "0xC4",
		bits: [
			{ name: "EVT1SRCSEL", description: "DCBEVT1 Source Signal", size: "1", shift: "0", mask: "0x1" },
			{ name: "EVT1FRCSYNCSEL", description: "DCBEVT1 Force Sync Signal", size: "1", shift: "1", mask: "0x2" },
			{ name: "EVT1SOCE", description: "DCBEVT1 SOC Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "EVT1SYNCE", description: "DCBEVT1 SYNC Enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "EVT1LATSEL", description: "DCBEVT1 Latched signal select", size: "1", shift: "4", mask: "0x10" },
			{ name: "EVT1LATCLRSEL", description: "DCBEVT1 Latched clear source select", size: "2", shift: "5", mask: "0x60" },
			{ name: "EVT1LAT", description: "Indicates the status of DCBEVT1LAT signal.", size: "1", shift: "7", mask: "0x80" },
			{ name: "EVT2SRCSEL", description: "DCBEVT2 Source Signal", size: "1", shift: "8", mask: "0x100" },
			{ name: "EVT2FRCSYNCSEL", description: "DCBEVT2 Force Sync Signal", size: "1", shift: "9", mask: "0x200" },
			{ name: "EVT2LATSEL", description: "DCBEVT2 Latched signal select", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EVT2LATCLRSEL", description: "DCBEVT2 Latched clear source select", size: "2", shift: "13", mask: "0x6000" },
			{ name: "EVT2LAT", description: "Indicates the status of DCBEVT2LAT signal.", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "DCFCTL", description: "Digital Compare Filter Control Register", offset: "0xC7",
		bits: [
			{ name: "SRCSEL", description: "Filter Block Signal Source Select", size: "2", shift: "0", mask: "0x3" },
			{ name: "BLANKE", description: "Blanking Enable/Disable", size: "1", shift: "2", mask: "0x4" },
			{ name: "BLANKINV", description: "Blanking Window Inversion", size: "1", shift: "3", mask: "0x8" },
			{ name: "PULSESEL", description: "Pulse Select for Blanking & Capture Alignment", size: "2", shift: "4", mask: "0x30" },
			{ name: "EDGEFILTSEL", description: "Edge Filter Select", size: "1", shift: "6", mask: "0x40" },
			{ name: "EDGEMODE", description: "Edge Mode", size: "2", shift: "8", mask: "0x300" },
			{ name: "EDGECOUNT", description: "Edge Count", size: "3", shift: "10", mask: "0x1C00" },
			{ name: "EDGESTATUS", description: "Edge Status", size: "3", shift: "13", mask: "0xE000" },
		]
	},
	{ name: "DCCAPCTL", description: "Digital Compare Capture Control Register", offset: "0xC8",
		bits: [
			{ name: "CAPE", description: "Counter Capture Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "SHDWMODE", description: "Counter Capture Mode", size: "1", shift: "1", mask: "0x2" },
			{ name: "CAPSTS", description: "Latched Status Flag for Capture Event", size: "1", shift: "13", mask: "0x2000" },
			{ name: "CAPCLR", description: "DC Capture Latched Status Clear Flag", size: "1", shift: "14", mask: "0x4000" },
			{ name: "CAPMODE", description: "Counter Capture Mode", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "DCFOFFSET", description: "Digital Compare Filter Offset Register", offset: "0xC9",
		bits: [
		]
	},
	{ name: "DCFOFFSETCNT", description: "Digital Compare Filter Offset Counter Register", offset: "0xCA",
		bits: [
		]
	},
	{ name: "DCFWINDOW", description: "Digital Compare Filter Window Register", offset: "0xCB",
		bits: [
		]
	},
	{ name: "DCFWINDOWCNT", description: "Digital Compare Filter Window Counter Register", offset: "0xCC",
		bits: [
		]
	},
	{ name: "DCCAP", description: "Digital Compare Counter Capture Register", offset: "0xCF",
		bits: [
		]
	},
	{ name: "DCAHTRIPSEL", description: "Digital Compare AH Trip Select", offset: "0xD2",
		bits: [
			{ name: "TRIPINPUT1", description: "Trip Input 1 Select to DCAH Mux", size: "1", shift: "0", mask: "0x1" },
			{ name: "TRIPINPUT2", description: "Trip Input 2 Select to DCAH Mux", size: "1", shift: "1", mask: "0x2" },
			{ name: "TRIPINPUT3", description: "Trip Input 3 Select to DCAH Mux", size: "1", shift: "2", mask: "0x4" },
			{ name: "TRIPINPUT4", description: "Trip Input 4 Select to DCAH Mux", size: "1", shift: "3", mask: "0x8" },
			{ name: "TRIPINPUT5", description: "Trip Input 5 Select to DCAH Mux", size: "1", shift: "4", mask: "0x10" },
			{ name: "TRIPINPUT6", description: "Trip Input 6 Select to DCAH Mux", size: "1", shift: "5", mask: "0x20" },
			{ name: "TRIPINPUT7", description: "Trip Input 7 Select to DCAH Mux", size: "1", shift: "6", mask: "0x40" },
			{ name: "TRIPINPUT8", description: "Trip Input 8 Select to DCAH Mux", size: "1", shift: "7", mask: "0x80" },
			{ name: "TRIPINPUT9", description: "Trip Input 9 Select to DCAH Mux", size: "1", shift: "8", mask: "0x100" },
			{ name: "TRIPINPUT10", description: "Trip Input 10 Select to DCAH Mux", size: "1", shift: "9", mask: "0x200" },
			{ name: "TRIPINPUT11", description: "Trip Input 11 Select to DCAH Mux", size: "1", shift: "10", mask: "0x400" },
			{ name: "TRIPINPUT12", description: "Trip Input 12 Select to DCAH Mux", size: "1", shift: "11", mask: "0x800" },
			{ name: "TRIPINPUT14", description: "Trip Input 14 Select to DCAH Mux", size: "1", shift: "13", mask: "0x2000" },
			{ name: "TRIPINPUT15", description: "Trip Input 15 Select to DCAH Mux", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "DCALTRIPSEL", description: "Digital Compare AL Trip Select", offset: "0xD3",
		bits: [
			{ name: "TRIPINPUT1", description: "Trip Input 1 Select to DCAL Mux", size: "1", shift: "0", mask: "0x1" },
			{ name: "TRIPINPUT2", description: "Trip Input 2 Select to DCAL Mux", size: "1", shift: "1", mask: "0x2" },
			{ name: "TRIPINPUT3", description: "Trip Input 3 Select to DCAL Mux", size: "1", shift: "2", mask: "0x4" },
			{ name: "TRIPINPUT4", description: "Trip Input 4 Select to DCAL Mux", size: "1", shift: "3", mask: "0x8" },
			{ name: "TRIPINPUT5", description: "Trip Input 5 Select to DCAL Mux", size: "1", shift: "4", mask: "0x10" },
			{ name: "TRIPINPUT6", description: "Trip Input 6 Select to DCAL Mux", size: "1", shift: "5", mask: "0x20" },
			{ name: "TRIPINPUT7", description: "Trip Input 7 Select to DCAL Mux", size: "1", shift: "6", mask: "0x40" },
			{ name: "TRIPINPUT8", description: "Trip Input 8 Select to DCAL Mux", size: "1", shift: "7", mask: "0x80" },
			{ name: "TRIPINPUT9", description: "Trip Input 9 Select to DCAL Mux", size: "1", shift: "8", mask: "0x100" },
			{ name: "TRIPINPUT10", description: "Trip Input 10 Select to DCAL Mux", size: "1", shift: "9", mask: "0x200" },
			{ name: "TRIPINPUT11", description: "Trip Input 11 Select to DCAL Mux", size: "1", shift: "10", mask: "0x400" },
			{ name: "TRIPINPUT12", description: "Trip Input 12 Select to DCAL Mux", size: "1", shift: "11", mask: "0x800" },
			{ name: "TRIPINPUT14", description: "Trip Input 14 Select to DCAL Mux", size: "1", shift: "13", mask: "0x2000" },
			{ name: "TRIPINPUT15", description: "Trip Input 15 Select to DCAL Mux", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "DCBHTRIPSEL", description: "Digital Compare BH Trip Select", offset: "0xD4",
		bits: [
			{ name: "TRIPINPUT1", description: "Trip Input 1 Select to DCBH Mux", size: "1", shift: "0", mask: "0x1" },
			{ name: "TRIPINPUT2", description: "Trip Input 2 Select to DCBH Mux", size: "1", shift: "1", mask: "0x2" },
			{ name: "TRIPINPUT3", description: "Trip Input 3 Select to DCBH Mux", size: "1", shift: "2", mask: "0x4" },
			{ name: "TRIPINPUT4", description: "Trip Input 4 Select to DCBH Mux", size: "1", shift: "3", mask: "0x8" },
			{ name: "TRIPINPUT5", description: "Trip Input 5 Select to DCBH Mux", size: "1", shift: "4", mask: "0x10" },
			{ name: "TRIPINPUT6", description: "Trip Input 6 Select to DCBH Mux", size: "1", shift: "5", mask: "0x20" },
			{ name: "TRIPINPUT7", description: "Trip Input 7 Select to DCBH Mux", size: "1", shift: "6", mask: "0x40" },
			{ name: "TRIPINPUT8", description: "Trip Input 8 Select to DCBH Mux", size: "1", shift: "7", mask: "0x80" },
			{ name: "TRIPINPUT9", description: "Trip Input 9 Select to DCBH Mux", size: "1", shift: "8", mask: "0x100" },
			{ name: "TRIPINPUT10", description: "Trip Input 10 Select to DCBH Mux", size: "1", shift: "9", mask: "0x200" },
			{ name: "TRIPINPUT11", description: "Trip Input 11 Select to DCBH Mux", size: "1", shift: "10", mask: "0x400" },
			{ name: "TRIPINPUT12", description: "Trip Input 12 Select to DCBH Mux", size: "1", shift: "11", mask: "0x800" },
			{ name: "TRIPINPUT14", description: "Trip Input 14 Select to DCBH Mux", size: "1", shift: "13", mask: "0x2000" },
			{ name: "TRIPINPUT15", description: "Trip Input 15 Select to DCBH Mux", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "DCBLTRIPSEL", description: "Digital Compare BL Trip Select", offset: "0xD5",
		bits: [
			{ name: "TRIPINPUT1", description: "Trip Input 1 Select to DCBL Mux", size: "1", shift: "0", mask: "0x1" },
			{ name: "TRIPINPUT2", description: "Trip Input 2 Select to DCBL Mux", size: "1", shift: "1", mask: "0x2" },
			{ name: "TRIPINPUT3", description: "Trip Input 3 Select to DCBL Mux", size: "1", shift: "2", mask: "0x4" },
			{ name: "TRIPINPUT4", description: "Trip Input 4 Select to DCBL Mux", size: "1", shift: "3", mask: "0x8" },
			{ name: "TRIPINPUT5", description: "Trip Input 5 Select to DCBL Mux", size: "1", shift: "4", mask: "0x10" },
			{ name: "TRIPINPUT6", description: "Trip Input 6 Select to DCBL Mux", size: "1", shift: "5", mask: "0x20" },
			{ name: "TRIPINPUT7", description: "Trip Input 7 Select to DCBL Mux", size: "1", shift: "6", mask: "0x40" },
			{ name: "TRIPINPUT8", description: "Trip Input 8 Select to DCBL Mux", size: "1", shift: "7", mask: "0x80" },
			{ name: "TRIPINPUT9", description: "Trip Input 9 Select to DCBL Mux", size: "1", shift: "8", mask: "0x100" },
			{ name: "TRIPINPUT10", description: "Trip Input 10 Select to DCBL Mux", size: "1", shift: "9", mask: "0x200" },
			{ name: "TRIPINPUT11", description: "Trip Input 11 Select to DCBL Mux", size: "1", shift: "10", mask: "0x400" },
			{ name: "TRIPINPUT12", description: "Trip Input 12 Select to DCBL Mux", size: "1", shift: "11", mask: "0x800" },
			{ name: "TRIPINPUT14", description: "Trip Input 14 Select to DCBL Mux", size: "1", shift: "13", mask: "0x2000" },
			{ name: "TRIPINPUT15", description: "Trip Input 15 Select to DCBL Mux", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "LOCK", description: "EPWM Lock Register", offset: "0xFA",
		bits: [
			{ name: "HRLOCK", description: "HRPWM Register Set Lock", size: "1", shift: "0", mask: "0x1" },
			{ name: "GLLOCK", description: "Global Load Register Set Lock", size: "1", shift: "1", mask: "0x2" },
			{ name: "TZCFGLOCK", description: "TripZone Register Set Lock", size: "1", shift: "2", mask: "0x4" },
			{ name: "TZCLRLOCK", description: "TripZone Clear Register Set Lock", size: "1", shift: "3", mask: "0x8" },
			{ name: "DCLOCK", description: "Digital Compare Register Set Lock", size: "1", shift: "4", mask: "0x10" },
			{ name: "KEY", description: "Key to write to this register", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "HWVDELVAL", description: "Hardware Valley Mode Delay Register", offset: "0xFD",
		bits: [
		]
	},
	{ name: "VCNTVAL", description: "Hardware Valley Counter Register", offset: "0xFE",
		bits: [
		]
	},
];
module.exports = {
	EPWMRegisters: EPWMRegisters,
}
