let Common  = system.getScript("/driverlib/Common.js");
let Pinmux  = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_bgcrc.js");

let BGCRC_MODE = [
    {name: "BGCRC_CRC_MODE", displayName: "CRC Mode"},
    {name: "BGCRC_SCRUB_MODE", displayName: "Scrub Mode"},
]
/* Intro splash on GUI */
let longDescription = `Background Cyclic Redundancy Check (BGCRC)

> CRC Algorithms verify data integrity over large blocks
> The BGCRC module computes a CRC-32 on a configurable block of memory
    - Computed is compared against golden CRC-32 value to determine pass/fail
    - Memory block size to be checked can be configured
    - Identifies memory faults and corruption

The technical description of the BGCRC module and its registers are available in the device TRM:
`;

longDescription += "*   [Device TRM](" + Common.getDeviceTRM() + ")";

var BGCRC_INSTANCE = [];

let INPUT_MODE_MANUAL = "MANUAL"
let INPUT_MODE_VARIABLE = "VARIABLE"

let ADDRESS_INPUT_MODE = [
    {name: INPUT_MODE_MANUAL, displayName: "Manual Address"},
    {name: INPUT_MODE_VARIABLE, displayName: "Variable/Function Name"},
]

if (["F28002x"].includes(Common.getDeviceName()))
{
    BGCRC_INSTANCE.push(
        { name: "BGCRC_CPU_BASE", displayName: "BGCRC CPU"}, 
    )

}
else if (["F2838x", "F28003x", "F28P65x", "F28P55x","F28P551x"].includes(Common.getDeviceName()))
{
    BGCRC_INSTANCE.push(
        { name: "BGCRC_CPU_BASE", displayName: "BGCRC CPU"}, 
        { name: "BGCRC_CLA1_BASE", displayName: "BGCRC CLA1"}
    )
}
 
device_driverlib_peripheral.BGCRC_NMI[0].displayName = "Generate NMI";
device_driverlib_peripheral.BGCRC_NMI[1].displayName = "Generate non-NMI Interrupt";
device_driverlib_peripheral.BGCRC_EMUCTRL[0].displayName = "Soft - stops upon halt";
device_driverlib_peripheral.BGCRC_EMUCTRL[1].displayName = "Free - continues running";

function onChangeStartAddressInputMode(inst,ui)
{
    if (inst.startAddrInputMode == INPUT_MODE_MANUAL) {
        ui.startAddr.hidden = false
        ui.startAddrVariable.hidden = true
    }
    if (inst.startAddrInputMode == INPUT_MODE_VARIABLE) {
        ui.startAddr.hidden = true
        ui.startAddrVariable.hidden = false
    }
}

/*Array of BGCRC configurables that are common across device families */
let config = [
    {
        name        : "bgcrcBase",
        displayName : "BGCRC Instance",
        description : 'Instance of the BGCRC used.',
        hidden      : false,
        default     : BGCRC_INSTANCE[0].name,
        options     : BGCRC_INSTANCE
    },
    //Config NMI
    {
        name        : "nmiMode",
        displayName : "Error Response Severity",
        description : 'Non-Maskable Interrupts are enabled by default for memory check failures',
        hidden      : false,
        default     : device_driverlib_peripheral.BGCRC_NMI[0].name,
        options     : device_driverlib_peripheral.BGCRC_NMI
    },
    //Emulation control
    {
        name        : "emuCtl",
        displayName : "Emulation Control",
        description : 'Emulation control for the BGCRC module can be set to free or soft. CRC calculation and watchdog not affected by DEBUG HALT when set to free. Soft is set by default.',
        hidden      : false,
        default     : device_driverlib_peripheral.BGCRC_EMUCTRL[0].name,
        options     : device_driverlib_peripheral.BGCRC_EMUCTRL
    }
    
];

let wdConfig = [
    //Enable/disable Watchdog
    {
        name        : "enableWatchdog",
        displayName : "Enable Watchdog during CRC",
        description : 'Watchdog is enabled by default to ensure test completes in expected time, but can be explicitly disabled',
        hidden      : false,
        default     : true
    },
    //min
    {
        name        : "wdMin",
        displayName : "Watchdog Window Minimum",
        description : 'Lower limit for watchdog window.',
        hidden      : false,
        default     : '0x0'
    },
    //max
    {
        name        : "wdMax",
        displayName : "Watchdog Window Maximum",
        description : 'Upper limit for watchdog window.',
        hidden      : false,
        default     : '0xFFFFFFFF'
    }

];

let testConfig = [
    //startAddr
    {
        name: "startAddrInputMode",
        displayName : "Start Address Input Type",
        description : 'Type of start address input.',
        hidden      : false,
        default     : ADDRESS_INPUT_MODE[0].name,
        options     : ADDRESS_INPUT_MODE,
        onChange    : onChangeStartAddressInputMode
    },
    //Manual input
    {
        name        : "startAddr",
        displayName : "Start Address",
        description : 'Starting address of the block to be checked. Value must be 0x80 word aligned, otherwise address will be changed to match closest 0x80 aligned address.',
        hidden      : false,
        default     : "0x00"
    },
    //Variable input
    {
        name: "startAddrVariable",
        displayName : "Start Address Variable",
        description : "Void pointer to function/variable of source address.",
        hidden      : true,
        default     : "",
    },
    //Block Size
    {
        name        : "blockSize",
        displayName : "Block Size (Enter Num Bytes)",
        description : 'Block Size of Memory to be Checked. IMPORTANT: Must be a multiple of 256.',
        hidden      : false,
        default     : "256",
        /*
        options     : [{name:"256B"}
        ,{name:"512B"}
        ,{name:"768B"}
        ,{name:"1KB"}]
        */
    },
    //CRC mode
    {
        name        : "crcMode",
        displayName : "Mode Select",
        description : 'CRC mode of operation can be set to either CRC mode or Scrub mode.' +
                        'In Scrub mode, CRC of data is not compared with the golden CRC.' +
                        'Error check is done using the ECC/Parity logic. In CRC mode,' + 
                        'value is compared with golden CRC at the end in addition to' +  
                        'the data correctness check by ECC/Parity logic.',
        hidden      : false,
        default     : BGCRC_MODE[0].name,
        options     : BGCRC_MODE
    },
     //Set Seed Value
     {
        name        : "seedVal",
        displayName : "CRC Seed Value",
        description : 'Sets the seed value for the CRC calculations.',
        hidden      : false,
        default     : '0x0'
    },
    //Set Golden CRC value
    {
        name        : "goldVal",
        displayName : "Golden CRC Value",
        description : 'Sets the golden CRC Value of the memory block being tested.',
        hidden      : false,
        default     : '0x0'
    }
];

config.push({
	name: "wdWindow",
		displayName: "Watchdog Settings",
		collapsed: false,
		config: wdConfig
});

config.push({
	name: "regionSetting",
		displayName: "CRC Configuration",
		collapsed: false,
		config: testConfig
});

config.push({
	name: "interruptSetting",
	displayName: "Interrupt Settings",
    description: "",
    collapsed: false,
    config: [
        {
            name        : "intFlags",
            displayName : "Enable Interrupt Flags",
            description : 'Select which int flags you would like to enable, if any.',
            hidden      : false,
            default     : [],
            minSelections: 0,
            options     : [
                {name:"BGCRC_TEST_DONE"},
                {name:"BGCRC_CRC_FAIL"},
                {name:"BGCRC_UNCORR_ERR"},
                {name:"BGCRC_CORR_ERR"},
                {name:"BGCRC_WD_UNDERFLOW"},
                {name:"BGCRC_WD_OVERFLOW"}
            ]
        },
        //register interrupt
        {
            name        : "registerInterrupts",
            displayName : "Register Interrupt Handler",
            description : 'Whether or not to register interrupt handlers in the interrupt module.',
            hidden      : false,
            default     : false
        }
    ]
});

config.push({
    name: "regProtection",
    displayName: "Register Guards and Protection",
    description: "",
    collapsed: false,
    config: [
        {
            name        : "lockRegs",
            displayName : "Lock Registers",
            description : 'Select which register(s) you would like to lock, if any.',
            hidden      : false,
            default     : [],
            minSelections: 0,
            options     : device_driverlib_peripheral.BGCRC_REG
        },
        //commit regs
        {
            name: "commitRegs",
            displayName: "Commit locked Registers",
            description : 'Commits the current register configuration. IMPORTANT: Only a reset can change the configuration',
            hidden      : false,
            default     : false
        }
    ]
});

config.push({
    name        : "startBGCRC",
    displayName : "Initiate BGCRC",
    description : 'Whether or not to star the BGCRC computation.',
    hidden      : false,
    default     : false
})

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["BGCRC"]));
}

function onValidate(inst, validation) {

    var usedBGCRCInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedBGCRCInsts.push(instance_obj.bgcrcBase);
    }

    var duplicatesResult = Common.findDuplicates(usedBGCRCInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The BGCRC Instance used. Duplicates: " + allDuplicates, 
            inst, "bgcrcBase");
    }


    if ((inst.blockSize % 256) != 0){
        validation.logError(
            "Block Size byte input must be a mutliple of 256!", 
            inst, "blockSize");
    }

    if (inst.blockSize > 256000){
        validation.logError(
            "Block Size cannot exceed 256 KB!", 
            inst, "blockSize");
    }

    if (inst.blockSize < 0){
        validation.logError(
            "Please enter a positive multiple of 256.", 
            inst, "blockSize");
    }

    if (inst.wdMin < 0x0 || inst.wdMin > 0xFFFFFFFF ){
        validation.logError(
            "Enter a value from 0x0 to 0xFFFFFFFF", 
            inst, "wdMin");
    }

    if (inst.wdMax < 0x0 || inst.wdMax > 0xFFFFFFFF ){
        validation.logError(
            "Enter a value from 0x0 to 0xFFFFFFFF", 
            inst, "wdMax");
    }

    if (inst.wdMin > inst.wdMax){
        validation.logError(
            "Min is larger than Max value",
            inst, "wdMax")
    }

    if (inst.startAddrInputMode == INPUT_MODE_MANUAL) {

        if (inst.startAddr < 0x0 || inst.startAddr > 0xFFFFFFFF ){
            validation.logError(
                "Enter a value from 0x0 to 0xFFFFFFFF", 
                inst, "startAddr");
        }

        if ((inst.startAddr & 0xFFFFFF80) != inst.startAddr){
            validation.logWarning(
                "The entered address is not 0x80 word aligned. The start address will be set to 0x" + (inst.startAddr & 0xFFFFFF80).toString(16).toUpperCase(), 
                inst, "startAddr");
        }

    }
    
    if (inst.crcMode == BGCRC_MODE[1].name ){
        validation.logInfo(
            "Mode is set to Scrub Mode, the Golden CRC Value will not be used.", 
            inst, "goldVal");

            validation.logInfo(
                "Mode is set to Scrub Mode, the Seed Value will not be used.", 
                inst, "seedVal");
    }

    if (inst.goldVal < 0x0 || inst.goldVal > 0xFFFFFFFF ){
        validation.logError(
            "Enter a value from 0x0 to 0xFFFFFFFF", 
            inst, "goldVal");
    }

    if (inst.seedVal < 0x0 || inst.seedVal > 0xFFFFFFFF ){
        validation.logError(
            "Enter a value from 0x0 to 0xFFFFFFFF", 
            inst, "seedVal");
    }
}



var bgcrcModule = {

    peripheralName: "BGCRC",
    displayName: "BGCRC",
    maxInstances: BGCRC_INSTANCE.length,
    defaultInstanceName: "myBGCRC",
    description: "BGCRC memory check peripheral",
    longDescription : longDescription,
    filterHardware: filterHardware,
    config: config,
    moduleInstances: (inst) => {
        var dlibInt = "INT_BGCRC";

        if (inst.bgcrcBase.includes("CLA"))
        {
            dlibInt = "INT_BGCRC_CLA1";
            if (["F2838x", "F28P65x"].includes(Common.getDeviceName())){
                dlibInt = "INT_CLA1CRC";
            }
        }
        else
        {
            if (["F2838x", "F28P65x"].includes(Common.getDeviceName())){
                dlibInt = "INT_CPUCRC";
            }
        }

        if (inst.registerInterrupts){
            return[{
                name: "bgcrcInt",
                displayName: "BGCRC Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_INT",
                    int : "INT_" + inst.$name,
                    pinmuxPeripheralModule: "",
                    driverlibInt : dlibInt
                }
            }]
        }
        return []
    },
    templates: {
        boardc : "/driverlib/bgcrc/bgcrc.board.c.xdt",
        boardh : "/driverlib/bgcrc/bgcrc.board.h.xdt"
    },
    validate    : onValidate
};

if (bgcrcModule.maxInstances <= 0){
    delete bgcrcModule.pinmuxRequirements;
}

exports = bgcrcModule;