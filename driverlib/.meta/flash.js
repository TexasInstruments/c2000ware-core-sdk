let Common  = system.getScript("/driverlib/Common.js");
let Pinmux  = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_flash.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

/* Intro splash on GUI */
let longDescription = `Flash is an electrically erasable/programmable
 nonvolatile memory that can be programmed and erased many times to 
 ease code development. Flash memory can be used primarily as a program 
 memory for the core, and secondarily as static data memory
`;

longDescription += "*   [Device TRM](" + Common.getDeviceTRM() + ")";

var FLASH_INSTANCE = [];

var ECC_INSTANCE =[];

FLASH_INSTANCE.push({ name: device_driverlib_memmap.FLASH0MemoryMap[0].name, displayName: device_driverlib_memmap.FLASH0MemoryMap[0].displayName });

ECC_INSTANCE.push({ name: device_driverlib_memmap.FLASH0MemoryMap[1].name, displayName: device_driverlib_memmap.FLASH0MemoryMap[1].displayName });

if (["F2837xS"].includes(Common.getDeviceName()))
{
    FLASH_INSTANCE.push(
        { name: device_driverlib_memmap.FLASH0MemoryMap[2].name, displayName: device_driverlib_memmap.FLASH0MemoryMap[2].displayName }, 
    )
    ECC_INSTANCE.push(
        { name: device_driverlib_memmap.FLASH0MemoryMap[3].name, displayName: device_driverlib_memmap.FLASH0MemoryMap[3].displayName }, 
    )
}
var Flash_SysClk_MHz = 200;
Flash_SysClk_MHz = Common.SYSCLK_getMaxMHz();

var Flash_FClk_MHz = 50;

if (["F28004x"].includes(Common.getDeviceName()) || ["F28002x"].includes(Common.getDeviceName()) || ["F28003x"].includes(Common.getDeviceName())){
    Flash_FClk_MHz = 20;
} 
if (["F280013x"].includes(Common.getDeviceName()) || ["F280015x"].includes(Common.getDeviceName()) || ["F28P65x"].includes(Common.getDeviceName())){
    Flash_FClk_MHz = 40;
} 



var numberOfInstance = {
    "F2807x"    : 1,
    "F28004x"   : 1,
    "F28003x"   : 1,
    "F28002x"   : 1,
    "F2838x"    : 1,
    "F2837xS"   : 2,
    "F2837xD"   : 1,
    "F280013x"  : 1,
    "F280015x"  : 1,
    "F28P65x"   : 1,
}

var deviceNumberOfInstances = numberOfInstance[Common.getDeviceName()];

//Flash_initModule(uint32_t ctrlBase, uint32_t eccBase, uint16_t waitstates)??

function calcWaitState(inst, ui)
{
    return Math.ceil((Flash_SysClk_MHz/Flash_FClk_MHz) - 1);
}

let config = [
    {
        name        : "flashBase",
        displayName : "FLASH Instance",
        description : 'Instance of the FLASH used.',
        hidden      : false,
        default     : FLASH_INSTANCE[0].name,
        options     : FLASH_INSTANCE
    },
    {
        name        : "calcWaitStates",
        displayName : "Calculate Wait State [RWAIT]",
        description : '',
        hidden      : false,
        default     : true,
        onChange    : (inst, ui) => {
            ui.waitStates.hidden = inst.calcWaitStates;
            ui.calculatedWaitStates.hidden = !inst.calcWaitStates
        }
    },    
    {
        name        : "calculatedWaitStates",
        displayName : "Wait State [RWAIT]",
        description : 'Sets the number of wait states for a flash read access. The waitstates parameter is a number between 0x0 and 0xF.',
        hidden      : true,
        default     : 0xF, 
        displayFormat: {
            radix: 'hex',
            bitSize: 4
        },
        getValue : (inst, ui) => {
            return calcWaitState(inst, ui)
        }
    },
    //Flash_setWaitstates(uint32_t ctrlBase, uint16_t waitstates), set to max 0xF by default
    {
        name        : "waitStates",
        displayName : "Wait State [RWAIT]",
        description : 'Sets the number of wait states for a flash read access. The waitstates parameter is a number between 0x0 and 0xF.',
        hidden      : true,
        default     : 0xF, 
        displayFormat: {
            radix: 'hex',
            bitSize: 4
        }
    },
    //Flash_enablePrefetch(uint32_t ctrlBase), disabled by default
    {
        name        : "enablePrefetch",
        displayName : "Enable Prefetch",
        description : '',
        hidden      : false,
        default     : true
    },
    //Flash_enableCache(uint32_t ctrlBase), disabled by default
    {
        name        : "enableCache",
        displayName : "Enable Cache",
        description : '',
        hidden      : false,
        default     : true
    },
    //enable ECC
    {
        name        : "enableECC",
        displayName : "Enable ECC",
        description : '',
        hidden      : false,
        default     : true
    },
    //ecc base init
    {
        name        : "eccBase",
        displayName : "ECC Instance",
        description : '',
        hidden      : false,
        default     : ECC_INSTANCE[0].name,
        getValue    : (inst) => {
            var ecc = ECC_INSTANCE[0].name;            
            FLASH_INSTANCE.forEach((element, index)=>{
                if(element.name == inst.flashBase){
                    ecc = ECC_INSTANCE[index].name;
                }
            })
            return ecc;
        },
    },
    {
        name        : "registerInterrupts",
        displayName : "Register Interrupt Handler",
        description : 'Whether or not to register interrupt handlers in the interrupt module. NMI is used for the uncorrectable errors in this module.',
        hidden      : false,
        default     : false
    }
];
if(!["F280015x", "F280013x", "F28P65x"].includes(Common.getDeviceName())){
    config.push(
        //ECC Error Threshold
        {
            name        : "errorThreshold",
            displayName : "Single Bit Error Threshold",
            description : 'The single bit error threshold, valid ranges are from 0x0 - 0xFFFF. Number of errors at which the correctable error interrupt flag gets set.',
            hidden      : false,
            default     : 0x0
        },
    )
}
/*
if(["F280015x"].includes(Common.getDeviceName())){
    config.push(
        {
            name: "engrWaitStates",
            displayName: "Engr Wait States",
            description: '',
            hidden: false,
            default: '0xF'
        }
    )
}
*/

var globalConfig = [
    
    {
        name: "flashSYSCLK",
        displayName: "CPUCLK [MHz] for Flash Wait State Calculation",
        description: "This is the CPUCLK/SYSCLK value assumed for flash wait state calculation",
        default: Flash_SysClk_MHz,
        onChange : (inst, ui)=>{
            Flash_SysClk_MHz = inst.flashSYSCLK
        }
    },
    
]

var sharedModuleInstances = undefined;

if(["F2838x", "F280013x", "F280015x", "F28P65x"].includes(Common.getDeviceName()))
{   
    sharedModuleInstances = function (inst) {
        if (inst.registerInterrupts)
        {
            return (
                [
                    {
                        name: "sysErrInt",      
                        displayName: "Sys Error Interrupt",
                        moduleName: "/driverlib/interrupt/interrupt_sys_err.js",
                        collapsed: true,
                    },
                ]
            );
        }
        return []
    }

}

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["FLASH"]));
}

function onValidate(inst, validation) {

    var usedFLASHInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedFLASHInsts.push(instance_obj.flashBase);
    }

    var duplicatesResult = Common.findDuplicates(usedFLASHInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The FLASH Instance used. Duplicates: " + allDuplicates, 
            inst, "flashBase");
    }


    var waitstateConfig = inst.waitStates
    var waitstateConfigName = "waitStates"
    if (inst.calcWaitStates)
    {
        waitstateConfig = inst.calculatedWaitStates
        waitstateConfigName = "calculatedWaitStates"
    }

    if (waitstateConfig < 0x0 || waitstateConfig > 0xF ){
        validation.logError(
            "Enter a value from 0x0 to 0xF", 
            inst, waitstateConfigName);
    }

    if (waitstateConfig < Math.ceil((inst.$module.$static["flashSYSCLK"]/inst.$module.$static["flashFCLK"])) - 1){
        validation.logError(
            "Please enter a wait state value greater than or equal to the minimum required for your selected SYSCLK and FCLK", 
            inst, waitstateConfigName);
    }

    if(!["F280015x", "F280013x", "F28P65x"].includes(Common.getDeviceName())){
        if (inst.errorThreshold < 0x0 || inst.errorThreshold > 0xFFFF ){
            validation.logError(
                "Enter a value from 0x0 to 0xFFFF", 
                inst, "errorThreshold");
        }
    }

    if(Common.getDeviceName().toLowerCase() == 'f2838x')
    {  
        if (inst.registerInterrupts){
            validation.logWarning(
                "Ensure that Flash Correctable Error Interrupt is enabled",
                inst, "registerInterrupts");
        }
    }

    validation.logInfo(
        `It is important to look at your device's datasheet for information about what
        the required minimum flash wait state is for your selected SYSCLK frequency.
        See Flash section of TRM for more info.`, 
        inst, waitstateConfigName);
}

function onValidateStatic(inst, validation){
    if (["F28002x"].includes(Common.getDeviceName())){
        if (inst.flashSYSCLK < 1 || inst.flashSYSCLK > 100 ){
            validation.logError(
                "Enter a value from 1 to 100 MHz", 
                inst, "flashSYSCLK");
        }
    } else if (["F28003x"].includes(Common.getDeviceName())){
        if (inst.flashSYSCLK < 1 || inst.flashSYSCLK > 120 ){
            validation.logError(
                "Enter a value from 1 to 120 MHz", 
                inst, "flashSYSCLK");
        }
    } else if (["F28004x"].includes(Common.getDeviceName())){
        if (inst.flashSYSCLK < 1 || inst.flashSYSCLK > 100 ){
            validation.logError(
                "Enter a value from 1 to 100 MHz", 
                inst, "flashSYSCLK");
        }
    } else {
        if (inst.flashSYSCLK < 1 || inst.flashSYSCLK > 200 ){
            validation.logError(
                "Enter a value from 1 to 200 MHz", 
                inst, "flashSYSCLK");
        }
    }
}

var flashModule = {

    peripheralName: "FLASH",
    displayName: "FLASH",
    maxInstances: deviceNumberOfInstances,
    defaultInstanceName: "myFMC",
    description: "FLASH",
    longDescription : longDescription,
    filterHardware: filterHardware,
    config: config,
    moduleInstances: (inst) => {
        if (inst.registerInterrupts)
        {
            var dlibname = "INT_FLASH_CORR_ERR"
            if(['F28004x', 'F28002x', 'F28003x', 'F2837xS', 'F2837xD', 'F2807x'].includes(Common.getDeviceName()))
            {   
                return [{
                    name: "flashInt",      
                    displayName: "Flash Correctable Error Interrupt",
                    moduleName: "/driverlib/interrupt.js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_INT",
                        int : "INT_" + inst.$name,
                        pinmuxPeripheralModule : "",
                        driverlibInt: dlibname
                    }
                }] 
            }         
        }
        return [];
    },
    sharedModuleInstances : sharedModuleInstances,
    templates: {
        boardc : "/driverlib/flash/flash.board.c.xdt",
        boardh : "/driverlib/flash/flash.board.h.xdt"
    },
    moduleStatic: {
        name: "flashGlobal",
        displayName: "Flash Global",
        config: globalConfig,
        collapsed: false,
        //modules: moduleStaticModules,
        validate : onValidateStatic
    },
    validate    : onValidate
};

if (flashModule.maxInstances <= 0){
    delete flashModule.pinmuxRequirements;
}

exports = flashModule;