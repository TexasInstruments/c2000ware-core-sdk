let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let useComparator = system.getScript("/driverlib/sdfm/modules/sd_comparatorFilter.js");
let useDatafilter = system.getScript("/driverlib/sdfm/modules/sd_DataFilter.js");
let sd_device_info = system.getScript("/driverlib/sdfm/sd_device_info.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_sdfm.js");
		
		
let CompEvent = 
[
	{ name: "CEVT1"   , displayName: "Comparator event 1 interrupt" },
	{ name: "CEVT2"   , displayName: "Comparator event 2 interrupt" },
]

let IEL_IEHEvent = 
[
	{ name: "IEL"   , displayName: "Low Threshold interrupt" },
	{ name: "IEH"   , displayName: "High Threshold interrupt" },
]

var temp1 = [];
var temp2 = [];

if (sd_device_info.peripheralType == "Type0" || sd_device_info.peripheralType == "Type1")
{
	var temp1 	 = IEL_IEHEvent[0];
	var temp2    = IEL_IEHEvent[1];
}
if (sd_device_info.peripheralType == "Type2")
{
	var temp1 	 = CompEvent[0];
	var temp2    = CompEvent[1];
}


var FilterNumber = [];

//var length = sd_device_info.SDFM_FilterNumber.length;

function onChangeUseInterrupts(inst, ui)
{
	var status_use_int = inst.useInterrupts

	var status_FIFO_EN = (inst.Ch1_FIFO_Enable || inst.Ch2_FIFO_Enable || inst.Ch3_FIFO_Enable || inst.Ch4_FIFO_Enable);
	
	
	var status_compEN;
	
	if(sd_device_info.peripheralType == "Type1" || sd_device_info.peripheralType == "Type2")
	{
		status_compEN = (inst.Ch1_ComparatorEnable || inst.Ch2_ComparatorEnable || inst.Ch3_ComparatorEnable || inst.Ch4_ComparatorEnable);
	}
	else
	{
		status_compEN = true;
	}
		
	
	ui.MFIE.hidden = !status_use_int;
	ui.AE.hidden = !status_use_int;
	
	if(sd_device_info.peripheralType == "Type0" || sd_device_info.peripheralType == "Type1")
	{
		ui.IEH.hidden = ((!status_use_int) || (!status_compEN));
		ui.IEL.hidden = ((!status_use_int) || (!status_compEN));
	}
	
	if(sd_device_info.peripheralType == "Type2")
	{
		ui.CEVT1.hidden = ((!status_use_int) || (!status_compEN));
		ui.CEVT2.hidden = ((!status_use_int) || (!status_compEN));
	}	
	
	if(sd_device_info.peripheralType == "Type0")
	{
//	   ui.SDFM_INT_RegisterInterrupts.hidden = (!status_use_int);
	}
		
	if(sd_device_info.peripheralType == "Type1" || sd_device_info.peripheralType == "Type2")
	{
		ui.SDFFINT.hidden = ((!status_FIFO_EN) || (!status_use_int));
		ui.SDFFOVF.hidden = ((!status_FIFO_EN) || (!status_use_int));
//		ui.SDFM_ERR_RegisterInterrupts.hidden = (!status_use_int);
//		ui.SDFM_DR_RegisterInterrupts.hidden = (!status_use_int);
	}
}

var interruptSettings_Type0 = [];

var intSettings = [];

if(sd_device_info.peripheralType == "Type0")
{
	interruptSettings_Type0 = interruptSettings_Type0.concat
	([ 
		{
        name        : "MFIE",
        displayName : "Modulator Clock failure",
        description : 'Which interrupts to enabled.',
        hidden      : true,
        default     : [],
        minSelections: 0,
        options     : sd_device_info.SDFM_FilterNumber,
		},
		{
        name        : temp1.name,
        displayName : temp1.displayName,
        description : 'Which interrupts to enabled.',
        hidden      : true,
        default     : [],
        minSelections: 0,
        options     : sd_device_info.SDFM_FilterNumber,
		},
		{
        name        : temp2.name,
        displayName : temp2.displayName,
        description : 'Which interrupts to enabled.',
        hidden      : true,
        default     : [],
        minSelections: 0,
        options     : sd_device_info.SDFM_FilterNumber,
		},
		{
        name        : "AE",
        displayName : "Data Acknowledge",
        description : 'Which interrupts to enabled.',
        hidden      : true,
        default     : [],
        minSelections: 0,
        options     : sd_device_info.SDFM_FilterNumber,
		},
	])
		
	intSettings = interruptSettings_Type0;
}

var interruptSettings_SDFM_INT = [];
var interruptSettings_SDFM_DR_INT = [];

if(sd_device_info.peripheralType == "Type1" || sd_device_info.peripheralType == "Type2")
{
	interruptSettings_SDFM_INT = interruptSettings_SDFM_INT.concat([
		{
        name        : "MFIE",
        displayName : "Modulator Clock failure",
        description : 'Which interrupts to enabled.',
        hidden      : true,
        default     : [],
        minSelections: 0,
        options     : sd_device_info.SDFM_FilterNumber,
		},
		{
        name        : temp1.name,
        displayName : temp1.displayName,
        description : 'Which interrupts to enabled.',
        hidden      : true,
        default     : [],
        minSelections: 0,
        options     : sd_device_info.SDFM_FilterNumber,
		},
		{
        name        : temp2.name,
        displayName : temp2.displayName,
        description : 'Which interrupts to enabled.',
        hidden      : true,
        default     : [],
        minSelections: 0,
        options     : sd_device_info.SDFM_FilterNumber,
		},
		{
		name        : "SDFFOVF",
		displayName : "FIFO Overflow error",
		description : 'Which interrupts to enabled.',
		hidden      : true,
		default     : [],
		minSelections: 0,
		options     : sd_device_info.SDFM_FilterNumber,
		},
	])
		intSettings = interruptSettings_SDFM_INT;
			
		interruptSettings_SDFM_DR_INT = interruptSettings_SDFM_DR_INT.concat([ 
		{
        name        : "AE",
        displayName : "Data Acknowledge",
        description : 'Which interrupts to enabled.',
        hidden      : true,
        default     : [],
        minSelections: 0,
        options     : sd_device_info.SDFM_FilterNumber,
		},
		{
        name        : "SDFFINT",
        displayName : "SDFM FIFO Interrupt",
        description : 'Which interrupts to enabled.',
        hidden      : true,
        default     : [],
        minSelections: 0,
        options     : sd_device_info.SDFM_FilterNumber,
		},		
		])		
}
  

var interruptSettings = [];

	interruptSettings = 
	[
		{
		name		: "useInterrupts",
		displayName : "Use SDFM interrupts",
		description : 'Whether or not to use Interrupt mode.',
        hidden      : false,
		default     : false,
		onChange    : onChangeUseInterrupts,
		},
		{
        name: "GROUP_SDFM_INT",
        displayName: "SDFM interrupt",
        description: "Configure SDFM interrupt",
		collapsed	: false,
        longDescription: "",
        config: intSettings,
		},
		{
        name: "GROUP_SDFM_DR_INT",
        displayName: "SDFM data ready interrupt",
        description: "Configure SDFM data ready interrupt",
		collapsed	: false,
        longDescription: "",
        config: interruptSettings_SDFM_DR_INT,
		},
	]	
	

var sdInterruptConfigSubmodule = 
{
    displayName: "Interrupt Configurations",
	maxInstances: Common.peripheralCount("SD"),
    defaultInstanceName: "_INTERRUPT_CONFIG",
	description: "Select Interrupt source",
    config: interruptSettings,
    templates: 
	{
        boardc : "", 
        boardh : "",
    },
};

exports = sdInterruptConfigSubmodule







