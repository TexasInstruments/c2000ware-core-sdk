let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_sdfm.js");
		


let SDFM_FilterType = 
[
	{ name: "SDFM_FILTER_SINC_FAST", displayName: "SincFast structure", regValue : 0},
	{ name: "SDFM_FILTER_SINC_1"   , displayName: "Sinc1 structure"	  , regValue : 1},
	{ name: "SDFM_FILTER_SINC_2"   , displayName: "Sinc2 structure"   , regValue : 2},
	{ name: "SDFM_FILTER_SINC_3"   , displayName: "Sinc3 structure"   , regValue : 3},
]


let SDFM_FilterNumber = 
[
	{ name: "FILTER1", displayName: "Digital filter 1" },
	{ name: "FILTER2", displayName: "Digital filter 2" },
	{ name: "FILTER3", displayName: "Digital filter 3" },
	{ name: "FILTER4", displayName: "Digital filter 4" },
]

let SDFM_CompEvent1Source = 
[
	{ name: "SDFM_COMP_EVENT_SRC_COMPH1"   , displayName: "COMPH1 event" },
	{ name: "SDFM_COMP_EVENT_SRC_COMPH1_L1", displayName: "COMPH1 or COMPL1 event" },
	{ name: "SDFM_COMP_EVENT_SRC_COMPH2"   , displayName: "COMPH2 event" },
	{ name: "SDFM_COMP_EVENT_SRC_COMPH2_L2", displayName: "COMPH2 or COMPL2 event" },
]

let SDFM_CompEvent2Source = 
[
	{ name: "SDFM_COMP_EVENT_SRC_COMPL1"   , displayName: "COMPL1 event" },
	{ name: "SDFM_COMP_EVENT_SRC_COMPH1_L1", displayName: "COMPH1 or COMPL1 event" },
	{ name: "SDFM_COMP_EVENT_SRC_COMPL2"   , displayName: "COMPL2 event" },
	{ name: "SDFM_COMP_EVENT_SRC_COMPH2_L2", displayName: "COMPH2 or COMPL2 event" },
]

let SDFM_OutputDataFormat = 
[
	{ name: "SDFM_DATA_FORMAT_16_BIT", displayName: "16 bits 2's complement format" },
	{ name: "SDFM_DATA_FORMAT_32_BIT", displayName: "32 bits 2's complement format" },
]


for (var index in SDFM_FilterNumber)
{
	SDFM_FilterNumber[index].displayName = SDFM_FilterNumber[index].displayName.replace("Digital filter ","FILTER ");
}



let SDFM_ModulatorClockMode = device_driverlib_peripheral.SDFM_ModulatorClockMode;

for (var index in SDFM_ModulatorClockMode)
{
  var temp1 = SDFM_ModulatorClockMode[index];
  SDFM_ModulatorClockMode[index].displayName =  "(Mode" + index + ") " + temp1.displayName;
}


let SDFM_PWMSyncSource = device_driverlib_peripheral.SDFM_PWMSyncSource;

for (var index in SDFM_PWMSyncSource)
{
	SDFM_PWMSyncSource[index].displayName = SDFM_PWMSyncSource[index].displayName.replace("SDFM sync source is ", "");
}


var DeviceInfo = 
[
    {device: "F2837xD", Type: "Type0", numberOfInstances : 2},
    {device: "F2837xS", Type: "Type0", numberOfInstances : 2},
    {device: "F2807x" , Type: "Type0", numberOfInstances : 2},
    {device: "F28004x", Type: "Type1", numberOfInstances : 1},
    {device: "F2838x" , Type: "Type2", numberOfInstances : 2},
    {device: "F28003x", Type: "Type2", numberOfInstances : 4},
    {device: "F28P65x", Type: "Type2", numberOfInstances : 4},
    {device: "F28P551x", Type: "Type2", numberOfInstances : 2},
	
];


var deviceID = DeviceInfo.find(element => element.device === Common.getDeviceName());
var peripheralType = deviceID.Type;
var deviceNumberOfInstances = deviceID.numberOfInstances;
 
var SDFM_INSTANCE = []
var NO_DEVICE_PIN_FOUND = "No Device Pin Found"

for (var instanceIndex = 1; instanceIndex <= deviceNumberOfInstances; instanceIndex++)
{
    SDFM_INSTANCE.push(
        { 
            name: "SDFM" + instanceIndex.toString() + "_BASE", 
            displayName: "SDFM" + instanceIndex.toString()
        }
    );
}

exports = 
{
	SDFM_FilterType   : SDFM_FilterType,
	SDFM_CompEvent1Source : SDFM_CompEvent1Source,
	SDFM_CompEvent2Source : SDFM_CompEvent2Source,
	SDFM_ModulatorClockMode : SDFM_ModulatorClockMode,
	SDFM_OutputDataFormat : SDFM_OutputDataFormat,
	SDFM_FilterNumber : SDFM_FilterNumber,
	SDFM_PWMSyncSource : SDFM_PWMSyncSource,
    deviceID : deviceID,
    SDFM_INSTANCE : SDFM_INSTANCE,
    peripheralType : peripheralType,
	deviceNumberOfInstances : deviceNumberOfInstances,
};
