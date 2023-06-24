let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_dma.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

var DMA_INSTANCE = [];
for (var dma of device_driverlib_memmap.DMAMemoryMap) {
    DMA_INSTANCE.push({
        name : dma.name,
        displayName : dma.displayName
    })
}

device_driverlib_peripheral.DMA_Trigger.push({name: "DMA_TRIGGER_LINKED", displayName: "Trigger is linked to peripheral"})

let INPUT_MODE_MANUAL = "MANUAL"
let INPUT_MODE_VARIABLE = "VARIABLE"
let INPUT_MODE_LINKED = "LINKED"

let ADDRESS_INPUT_MODE = [
    {name: "MANUAL", displayName: "Manual"},
    {name: "VARIABLE", displayName: "Variable/Function Name"},
    {name: "LINKED", displayName: "Linked to Peripheral"},
]

/* Intro splash on GUI */
let longDescription = "";

function onChangePeripheralTXLinked(inst,ui)
{
    if (inst.peripheralTXLinked) {
        inst.destBurstStep = 0;
        //ui.destBurstStep.readOnly = true;
        inst.destTransferStep = 0;
        //ui.destTransferStep.readOnly = true;
        inst.destWrapStep = 0;
        //ui.destWrapStep.readOnly = true;
        

        ui.destAddressManual.hidden = true;
        inst.destAddressInputMode = INPUT_MODE_LINKED
        ui.destAddressInputMode.readOnly = true
        ui.destAddressLinked.hidden = false
        ui.destAddressLinked.readOnly = true
        inst.destWrapSize = 65535;
        //ui.destWrapSize.readOnly = true
    }
}

function onChangePeripheralRXLinked(inst,ui)
{
    if (inst.peripheralRXLinked) {
        inst.srcBurstStep = 0;
        //ui.srcBurstStep.readOnly = true;
        inst.srcTransferStep = 0;
        //ui.srcTransferStep.readOnly = true;
        inst.srcWrapStep = 0;
        //ui.srcWrapStep.readOnly = true;

        ui.srcAddressManual.hidden = true;
        inst.srcAddressInputMode = INPUT_MODE_LINKED
        ui.srcAddressInputMode.readOnly = true
        ui.srcAddressLinked.hidden = false
        ui.srcAddressLinked.readOnly = true
        inst.srcWrapSize = 65535;
        //ui.srcWrapSize.readOnly = true
    }
}

function onChangeDMAInstance(inst,ui)
{
    if (inst.dmaBase == DMA_INSTANCE[1].name) {
        ui.enablePriority.hidden = false
    }
    else {
        ui.enablePriority.hidden = true
    }
}

function onChangeUseInterrupts(inst,ui)
{
    if (inst.useInterrupts) {
        ui.enableInterrupts.hidden = false
        ui.registerInterrupts.hidden = false
        ui.enableOverrunInterrupt.hidden = false
        ui.interruptMode.hidden = false
    }
    else {
        ui.enableInterrupts.hidden = true
        ui.registerInterrupts.hidden = true
        ui.enableOverrunInterrupt.hidden = true
        ui.interruptMode.hidden = true
    }
}

function onChangeSrcAddressInputMode(inst,ui)
{
    if (inst.srcAddressInputMode == INPUT_MODE_MANUAL) {
        ui.srcAddressManual.hidden = false
        ui.srcAddressVariable.hidden = true
        ui.srcAddressLinked.hidden = true
    }
    if (inst.srcAddressInputMode == INPUT_MODE_VARIABLE) {
        ui.srcAddressManual.hidden = true
        ui.srcAddressVariable.hidden = false
        ui.srcAddressLinked.hidden = true
    }
    if (inst.srcAddressInputMode == INPUT_MODE_LINKED) {
        ui.srcAddressManual.hidden = true
        ui.srcAddressVariable.hidden = true
        ui.srcAddressLinked.hidden = false
        ui.srcAddressLinked.readOnly = true
        ui.srcWrapSize.readOnly = true
    }
}

function onChangeDestAddressInputMode(inst,ui)
{
    if (inst.destAddressInputMode == INPUT_MODE_MANUAL) {
        ui.destAddressManual.hidden = false
        ui.destAddressVariable.hidden = true
        ui.destAddressLinked.hidden = true
    }
    if (inst.destAddressInputMode == INPUT_MODE_VARIABLE) {
        ui.destAddressManual.hidden = true
        ui.destAddressVariable.hidden = false
        ui.destAddressLinked.hidden = true
    }
    if (inst.destAddressInputMode == INPUT_MODE_LINKED) {
        ui.destAddressManual.hidden = true
        ui.destAddressVariable.hidden = true
        ui.destAddressLinked.hidden = false
        ui.destAddressLinked.readOnly = true
        ui.destWrapSize.readOnly = true
    }
}

/*
function onChangeUseWordSizeCalculator(inst, ui)
{
    if (inst.useWordSizeCalculator == true){
        ui.numberWordsToTransfer.readOnly = false
        ui.burstSize.getValue = calculateBurstSize
        ui.transferSize.getValue = calculateTransferSize
    }
    else {
        ui.numberWordsToTransfer.readonly = true
        ui.transferSize.getValue = calculateWordsToTransfer
    }
}

function calculateBurstSize(inst, ui)
{
    return 0
}

function calculateTransferSize(inst, ui)
{
    return 0
}
*/

function calculateWordsToTransfer(inst, ui)
{
    var tempWords = 0
    if (inst.databusWidthConfig == "DMA_CFG_SIZE_16BIT") {
        tempWords = (inst.transferSize - 1) * (inst.burstSize - 1)
    }
    if (inst.databusWidthConfig == "DMA_CFG_SIZE_32BIT") {
        tempWords = ((inst.transferSize - 1) * (inst.burstSize - 1)) / 2
    }
    return tempWords
}
 
/* Array of DMA configurables that are common across device families */
let config = [
    {
        name        : "peripheralRXLinked",
        displayName : "Channel is linked to a peripheral for recieve from DMA.",
        description : '',
        hidden      : true,
        default     : false,
        onChange    : onChangePeripheralRXLinked
    },

    {
        name        : "peripheralTXLinked",
        displayName : "Channel is linked to a peripheral for transmit to DMA.",
        description : '',
        hidden      : true,
        default     : false,
        onChange    : onChangePeripheralTXLinked
    },

    {
        name        : "dmaBase",
        displayName : "DMA Channel",
        description : 'DMA Channel used.',
        hidden      : false,
        default     : DMA_INSTANCE[1].name,
        options     : DMA_INSTANCE.slice(1),
        onChange    : onChangeDMAInstance
    },

    {
        name        : "enableTriggers",
        displayName : "Enable Triggers",
        description : "Enable triggers for the selected channel.",
        hidden      : false,
        default     : false,
    },

    {
        name        : "triggerSource",
        displayName : "Trigger Source",
        description : "Set trigger source for the selected channel.",
        hidden      : false,
        default     : device_driverlib_peripheral.DMA_Trigger[0].name,
        options     : device_driverlib_peripheral.DMA_Trigger
    },

    {
        name        : "useInterrupts",
        displayName : "Use Interrupt",
        onChange    : onChangeUseInterrupts,
        description : 'Whether or not to use Interrupt mode.',
        hidden      : false,
        default     : false,
    },

    {
        name        : "registerInterrupts",
        displayName : "Register Interrupt Handler",
        description : 'Whether or not to register interrupt handlers in the interrupt module.',
        hidden      : true,
        default     : false,
    },

    {
        name        : "enableInterrupts",
        displayName : "Enable Interrupts",
        description : "Enable the DMA channel's CPU interrupt.",
        hidden      : true,
        default     : false,
    },

    {
        name        : "enableOverrunInterrupt",
        displayName : "Enable Overrun Interrupt",
        description : "Determines whether the DMA module generates a CPU interrupt when it detects an overflow event.",
        hidden      : true,
        default     : false,
    },

    {
        name        : "interruptMode",
        displayName : "Interrupt Mode",
        description : "Set interrupt mode for the selected channel.",
        hidden      : true,
        default     : device_driverlib_peripheral.DMA_InterruptMode[0].name,
        options     : device_driverlib_peripheral.DMA_InterruptMode
    },

    {
        name        : "emulationMode",
        displayName : "Emulation Mode",
        description : "Set emulation mode for the selected channel.",
        hidden      : false,
        default     : device_driverlib_peripheral.DMA_EmulationMode[0].name,
        options     : device_driverlib_peripheral.DMA_EmulationMode
    },

    {
        name        : "oneShotConfig",
        displayName : "One-Shot Configuration",
        description : "Configuration options for the selected channel.",
        hidden      : false,
        default     : device_driverlib_peripheral.DMA_CFG[0].name,
        options     : device_driverlib_peripheral.DMA_CFG.slice(0,2)
    },

    {
        name        : "continuousModeConfig",
        displayName : "Continuous Mode Configuration",
        description : "Configuration options for the selected channel.",
        hidden      : false,
        default     : device_driverlib_peripheral.DMA_CFG[2].name,
        options     : device_driverlib_peripheral.DMA_CFG.slice(2,4)
    },

    {
        name        : "databusWidthConfig",
        displayName : "Databus Width",
        description : "Configuration options for the selected channel.",
        hidden      : false,
        default     : device_driverlib_peripheral.DMA_CFG[4].name,
        options     : device_driverlib_peripheral.DMA_CFG.slice(4)
    },

    {
        name        : "burstSize",
        displayName : "Burst Size",
        description : "Set number of words to transfer with each burst.",
        hidden      : false,
        default     : 1,
    },

    {
        name        : "transferSize",
        displayName : "Transfer Size",
        description : "Set number of bursts per transfer.",
        hidden      : false,
        default     : 1,
    },

/*
    {
        name        : "useWordSizeCalculator",
        displayName : "Use Word Size Calculator",
        description : "Auto-calculate Burst size and transfer size based on databus width and words to transfer",
        hidden      : false,
        default     : false,
        onChange    : onChangeUseWordSizeCalculator,
    },
*/
    {
        name        : "numberWordsToTransfer",
        displayName : "Number of words to be transferred",
        hidden      : false,
        readOnly    : true,
        default     : 0,
        getValue    : calculateWordsToTransfer,
    },

    {
        name        : "enablePriority",
        displayName : "Enable Channel 1 Priority",
        description : "Give priority to Channel 1 over all other channels.",
        hidden      : false,
        default     : false,
    },

    {
        name        : "startChannel",
        displayName : "Start Channel",
        description : "Start channel immediately at runtime.",
        hidden      : false,
        default     : false,
    }, 
]

config = config.concat([{
    name: "GROUP_SRC_ADDRESS",
    displayName: "Source Address Setup",
    description: "Source address setup options",
    longDescription: "",
    config: [
        {
            name: "srcAddressInputMode",
            displayName : "Source Address Input Type",
            description : 'Type of source address input.',
            hidden      : false,
            default     : ADDRESS_INPUT_MODE[0].name,
            options     : ADDRESS_INPUT_MODE,
            onChange    : onChangeSrcAddressInputMode
        },

        {
            name        : "srcAddressManual",
            displayName : "Source Address",
            description : 'The source address (hexadecimal if using "0x" prefix)',
            hidden      : false,
            displayFormat: "hex",
            default     : 0x00
        },
    
        {
            name: "srcAddressVariable",
            displayName : "Source Address Variable",
            description : "Void pointer to function/variable of source address.",
            hidden      : true,
            default     : "",
        },
    
        {
            name: "srcAddressLinked",
            displayName : "Source Address Of Linked Peripheral",
            description : "Static source address of linked peripheral",
            hidden      : true,
            default     : "",
        },
    
        {
            name        : "srcBurstStep",
            displayName : "Source Address Burst Step",
            description : "Amount to increment (positive) or decrement (negative) source address after each word of burst. Note: step size will occur in 16-bit increments regardless of databus width.",
            hidden      : false,
            default     : 0,
        },
    
        {
            name        : "srcTransferStep",
            displayName : "Source Address Transfer Step",
            description : "Amount to increment (positive) or decrement (negative) source address after completing the current burst transfer. Note: step size will occur in 16-bit increments regardless of databus width.",
            hidden      : false,
            default     : 0,
        },
    
        {
            name        : "srcWrapSize",
            displayName : "Source Wrap Size",
            description : "Set number of bursts before wrap on source address occurs.",
            hidden      : false,
            default     : 65535,
        },
    
        {
            name        : "srcWrapStep",
            displayName : "Source Address Wrap Step",
            description : "Amount to increment (positive) or decrement (negative) source address after wrap counter reaches 0. Note: step size will occur in 16-bit increments regardless of databus width.",
            hidden      : false,
            default     : 0,
        },
    ]
}]);

config = config.concat([{
    name: "GROUP_DEST_ADDRESS",
    displayName: "Destination Address Setup",
    description: "Destination address setup options",
    longDescription: "",
    config: [
        {
            name: "destAddressInputMode",
            displayName : "Destination Address Input Type",
            description : 'Type of destination address input.',
            hidden      : false,
            default     : ADDRESS_INPUT_MODE[0].name,
            options     : ADDRESS_INPUT_MODE,
            onChange    : onChangeDestAddressInputMode
        },
    
        {
            name        : "destAddressManual",
            displayName : "Destination Address",
            description : 'The source address (hexadecimal if using "0x" prefix)',
            hidden      : false,
            displayFormat: "hex",
            default     : 0x00
        },
    
        {
            name: "destAddressVariable",
            displayName : "Destination Address Variable",
            description : "Void pointer to function/variable of destination address.",
            hidden      : true,
            default     : "",
        },
    
        {
            name: "destAddressLinked",
            displayName : "Destination Address Of Linked Peripheral",
            description : "Static destination address of linked peripheral",
            hidden      : true,
            default     : "",
        },
    
        {
            name        : "destBurstStep",
            displayName : "Destination Address Burst Step",
            description : "Amount to increment (positive) or decrement (negative) destination address after each word of burst. Note: step size will occur in 16-bit increments regardless of databus width.",
            hidden      : false,
            default     : 0,
        },
    
        {
            name        : "destTransferStep",
            displayName : "Destination Address Transfer Step",
            description : "Amount to increment (positive) or decrement (negative) destination address after completing the current burst transfer. Note: step size will occur in 16-bit increments regardless of databus width.",
            hidden      : false,
            default     : 0,
        },
    
        {
            name        : "destWrapSize",
            displayName : "Destination Wrap Size",
            description : "Set number of bursts before wrap on destination address occurs.",
            hidden      : false,
            default     : 65535,
        },
    
        {
            name        : "destWrapStep",
            displayName : "Destination Address Wrap Step",
            description : "Amount to increment (positive) or decrement (negative) destination address after wrap counter reaches 0. Note: step size will occur in 16-bit increments regardless of databus width.",
            hidden      : false,
            default     : 0,
        },
    ]
}]);

function onValidate(inst, validation)
{
    var usedDMAInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedDMAInsts.push(instance_obj.dmaBase);
    }
    
    var duplicatesResult = Common.findDuplicates(usedDMAInsts)
    
    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ")
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "This DMA Instance is already in use! Duplicates: " + allDuplicates,
            inst, "dmaBase");
    }

    if (inst.burstSize > 32 || inst.burstSize < 1 || !Number.isInteger(inst.burstSize)) {
        validation.logError("Burst size must be an integer between 1 and 32!", inst, "burstSize");
    }

    if (inst.srcBurstStep > 4095 || inst.srcBurstStep < -4096 || !Number.isInteger(inst.srcBurstStep)) {
        validation.logError("Source address step size must be an integer between -4096 and 4095!", inst, "srcBurstStep");
    }

    if (inst.destBurstStep > 4095 || inst.destBurstStep < -4096 || !Number.isInteger(inst.destBurstStep)) {
        validation.logError("Destination address step size must be an integer between -4096 and 4095!", inst, "destBurstStep");
    }

    if (inst.srcTransferStep > 4095 || inst.srcTransferStep < -4096 || !Number.isInteger(inst.srcTransferStep)) {
        validation.logError("Source address step size must be an integer between -4096 and 4095!", inst, "srcTransferStep");
    }

    if (inst.destTransferStep > 4095 || inst.destTransferStep < -4096 || !Number.isInteger(inst.destTransferStep)) {
        validation.logError("Destination address step size must be an integer between -4096 and 4095!", inst, "destTransferStep");
    }

    if (inst.srcWrapStep > 4095 || inst.srcWrapStep < -4096 || !Number.isInteger(inst.srcWrapStep)) {
        validation.logError("Source address step size must be an integer between -4096 and 4095!", inst, "srcWrapStep");
    }

    if (inst.destWrapStep > 4095 || inst.destWrapStep < -4096 || !Number.isInteger(inst.destWrapStep)) {
        validation.logError("Destination address step size must be an integer between -4096 and 4095!", inst, "destWrapStep");
    }

    if (inst.transferSize > 65536 || inst.transferSize < 1 || !Number.isInteger(inst.transferSize)) {
        validation.logError("Transfer size must be an integer between 0 and 65,536!", inst, "transferSize");
    }

    if (inst.srcWrapSize > 65536 || inst.srcWrapSize < 1 || !Number.isInteger(inst.srcWrapSize)) {
        validation.logError("Source address wrap size must be an integer between 0 and 65,536!", inst, "srcWrapSize");
    }

    if (inst.destWrapSize > 65536 || inst.destWrapSize < 1 || !Number.isInteger(inst.destWrapSize)) {
        validation.logError("Destination address wrap size must be an integer between 0 and 65,536!", inst, "destWrapSize");
    }

    if (inst.oneShotConfig == device_driverlib_peripheral.DMA_CFG[1].name && inst.enablePriority) {
        validation.logError("One-Shot mode and High-priority mode must not be used at the same time on channel 1!", inst, "enablePriority");   
    }

    if (inst.peripheralTXLinked == 0 && inst.destAddressInputMode == INPUT_MODE_LINKED) {
        validation.logError("Linking to a peripheral must be configured as a submodule of that peripheral!", inst, "destAddressInputMode");   
    }

    if (inst.peripheralRXLinked == 0 && inst.srcAddressInputMode == INPUT_MODE_LINKED) {
        validation.logError("Linking to a peripheral must be configured as a submodule of that peripheral!", inst, "srcAddressInputMode");   
    }

    if (inst.peripheralTXLinked == 0 && inst.peripheralRXLinked == 0 && inst.triggerSource == "DMA_TRIGGER_LINKED") {
        validation.logError("Linking to a peripheral must be configured as a submodule of that peripheral!", inst, "triggerSource");   
    }
}

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["DMA"]));
}
 
var dmaModule = {
    peripheralName: "DMA",
    displayName: "DMA",
    maxInstances: 6,
    defaultInstanceName: "myDMA",
    description: "DMA Peripheral",
    filterHardware : filterHardware,
    config: config,
    moduleInstances: (inst) => {
        if (inst.useInterrupts && inst.registerInterrupts)
        {
            return [{
                name: "dmaInt",      
                displayName: "DMA Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
            		$name : inst.$name + "_INT",
                    int : "INT_" + inst.$name,
                    pinmuxPeripheralModule :"",
                    driverlibInt: "INT_" + inst.dmaBase.replace("_BASE", "")
                }
            },
            ]
        }
        return [];
    },
    templates: {
        boardc : "/driverlib/dma/dma.board.c.xdt",
        boardh : "/driverlib/dma/dma.board.h.xdt"
    },
    validate : onValidate
};
 
 
if (dmaModule.maxInstances <= 0)
{
    delete dmaModule.pinmuxRequirements;
}
 
exports = dmaModule;