let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let AccProt  = system.getScript("/driverlib/mecfgAccProt.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memcfg.js");
let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");
let device_driverlib_sysctl_registers =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_sysctl_registers.js");
let device_driverlib_sysctl =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_sysctl.js");

/* Intro splash on GUI */
let longDescription = ``;

longDescription += "*   [Device TRM](" + Common.getDeviceTRM() + ") \n -  For GSRAM blocks configured to be owned by CPU2: the code for Initialization, Access Protection, and Lock Configs will be generated on CPU2";

/* Array of MEMCFG configurables that are common across device families */
let staticConfig = []
let LSRAMOwnerConfig = []
let GSRAMOwnerConfig = []
let DRAMOwnerConfig = []
let FLASHOwnerConfig = []
let AccessConfig = []
let InitRAM = []
let LockConfig = []
let ViolIntConfig = []
let CorrErrIntConfig = []
let ROMConfig = []

/* Section : LSRAM Configuration */
if(device_driverlib_peripheral.MemCfg_LSRAMControllerSel)
{
    device_driverlib_peripheral.MEMCFG_SECT.
        forEach((element, index) =>
            {
                if ((element.name.includes("MEMCFG_SECT_LS")) && (element.name != "MEMCFG_SECT_LSX_ALL"))
                {
                    if (Common.isContextCPU1() || !["F28P65x"].includes(system.deviceData.deviceId)){
                        var lsOptions = []
                        lsOptions.push({name: "CPU_memory", displayName: "CPU dedicated memory"})
                        if (!["F28P65x"].includes(system.deviceData.deviceId) || !(element.name.includes("LS8") || element.name.includes("LS9"))){
                            lsOptions.push({name: "CLA_data",   displayName: "CPU/CLA shared data memory"})
                        }
                        lsOptions.push({name: "CLA_prog",   displayName: "CLA program memory"})
                        LSRAMOwnerConfig.push(
                            {
                                name: "config_" + element.name,
                                displayName : element.displayName,
                                options : lsOptions,
                                default : "CPU_memory"
                            }
                        )
                    }
                }
            }
        );
}

/* Section : GSRAM Configuration */
if (Common.isContextCPU1())
{
    if(device_driverlib_peripheral.MemCfg_GSRAMControllerSel)
    {
        device_driverlib_peripheral.MEMCFG_SECT.
            forEach((element, index) =>
                {
                    if ((element.name.includes("MEMCFG_SECT_GS")) && (element.name != "MEMCFG_SECT_GSX_ALL"))
                    {
                        GSRAMOwnerConfig.push(
                            {
                                name       : "config_" + element.name,
                                displayName: element.displayName,
                                options    : device_driverlib_peripheral.MemCfg_GSRAMControllerSel,
                                default    : device_driverlib_peripheral.MemCfg_GSRAMControllerSel[0].name
                            }
                        )
                    }
                }
            );
    }
}

if (device_driverlib_sysctl.SysCtl_CPUSel){
var SysctlOptions =  [];
device_driverlib_peripheral.MemCfg_GSRAMControllerSel.
forEach((element, index) =>
    {
        let thisName = device_driverlib_sysctl.SysCtl_CPUSel[index].name;
        let thisDisplayName = device_driverlib_peripheral.MemCfg_GSRAMControllerSel[index].displayName;
        SysctlOptions.push({ name: thisName, displayName: thisDisplayName})
    });
}

/* Section : DRAM Configuration */
if (Common.isContextCPU1() && ["F28P65x"].includes(system.deviceData.deviceId))
{
    device_driverlib_sysctl.SysCtl_SharedDxRAM.
        forEach((element, index) =>
            {
                    DRAMOwnerConfig.push(
                        {
                            name       : "config_" + element.name,
                            displayName: element.displayName,
                            options    : SysctlOptions,
                            default    : SysctlOptions[0].name
                        }
                    )
            }
        );
}

/* Section : FLASH Configuration */
if (Common.isContextCPU1() && ["F28P65x"].includes(system.deviceData.deviceId))
{
    device_driverlib_sysctl.SysCtl_FlashBank.
        forEach((element, index) =>
            {
                FLASHOwnerConfig.push(
                    {
                        name       : "config_" + element.name,
                        displayName: element.name,
                        options    : SysctlOptions,
                        default    : SysctlOptions[0].name
                    }
                )
            }
        );
}

/* Section : ROM config */
if(["F2838x", "F2837xD", "F2837xS", "F2807x","F28P65x"].includes(system.deviceData.deviceId))
{
    ROMConfig = [
        {
            name       : "rom_waitstate",
            displayName: "Enable ROM wait state",
            description: "If enabled, CPU accesses to ROM are 1-wait",
            default    : true
        }]
        if(!["F28P65x"].includes(system.deviceData.deviceId)){
            ROMConfig.push(
            {
                name       : "rom_prefetch",
                displayName: "Enable ROM prefetch",
                description: "Enable prefetch for secure ROM and boot ROM",
                default    : false
            })
        }
    var yesROM = 1;
}

/* Section : Access Protection  */
AccProt.AcessProtectionRAMs[system.deviceData.deviceId.toLowerCase()].
    forEach((element, index) =>
        {
            var ramMacro = "MEMCFG_SECT_" + element.name
            if (ramMacro[12]!="G" && ((Common.isContextCPU1() || (ramMacro[12]!="D" && ramMacro[12]!="L")) || !["F28P65x"].includes(system.deviceData.deviceId)))    // Global ram has own if statement so description is only on GSRAM
               {
                    if(device_driverlib_peripheral.MEMCFG_SECT.map(a=>a.name).includes(ramMacro) && (Common.isContextCPU1() || !ramMacro.includes("TOCM")))
                    {
                        var AvailableOptions = []
                        if(element.access.includes("FETCHPROT"))
                        AvailableOptions.push({name : "MEMCFG_PROT_ALLOWCPUFETCH", displayName: "CPU fetch allowed"})
                        if(element.access.includes("CPUWRPROT"))
                            AvailableOptions.push({name : "MEMCFG_PROT_ALLOWCPUWRITE", displayName: "CPU write allowed"})
                        if(element.access.includes("DMAWRPROT"))
                        AvailableOptions.push({name : "MEMCFG_PROT_ALLOWDMAWRITE", displayName: "DMA write allowed"})
                        if(element.access.includes("HICWRPROT"))
                            AvailableOptions.push({name : "MEMCFG_PROT_ALLOWHICWRITE", displayName: "HIC write allowed"})
                        if (ramMacro.includes("MSGCPUTOCPU")){
                            let ramNumber = ramMacro[23]; // get number from end of ram macro
                            AccessConfig.push(
                            {
                                name         : "access_" + ramMacro,
                                displayName  : "CPU-to-CPU message RAM"+ ramNumber.toString() + " Access",
                                minSelections: 0,
                                options      : AvailableOptions,
                                default      : AvailableOptions.map(a=>a.name)
                            })
                        }
                        if (ramMacro.includes("MSGCPUTOCM")){ // get number from end of ram macro
                            let ramNumber = ramMacro[22];
                            AccessConfig.push(
                            {
                                name         : "access_" + ramMacro,
                                displayName  : "CPU-to-CM message RAM"+ ramNumber.toString() + " Access",
                                minSelections: 0,
                                options      : AvailableOptions,
                                default      : AvailableOptions.map(a=>a.name)
                            })
                        }
                        if ((!ramMacro.includes("MSGCPUTOCPU")) && (!ramMacro.includes("MSGCPUTOCM"))){
                            AccessConfig.push(
                            {
                                name         : "access_" + ramMacro,
                                displayName  : element.name + " RAM Access",
                                minSelections: 0,
                                options      : AvailableOptions,
                                default      : AvailableOptions.map(a=>a.name)
                            })
                        }
                    }
                }   
            if (ramMacro[12]=="G" && (Common.isContextCPU1()))
                {
                    if(device_driverlib_peripheral.MEMCFG_SECT.map(a=>a.name).includes(ramMacro))
                    {
                        var AvailableOptions = []
                        if(element.access.includes("FETCHPROT"))
                        AvailableOptions.push({name : "MEMCFG_PROT_ALLOWCPUFETCH", displayName: "CPU fetch allowed"})
                        if(element.access.includes("CPUWRPROT"))
                            AvailableOptions.push({name : "MEMCFG_PROT_ALLOWCPUWRITE", displayName: "CPU write allowed"})
                        if(element.access.includes("DMAWRPROT"))
                        AvailableOptions.push({name : "MEMCFG_PROT_ALLOWDMAWRITE", displayName: "DMA write allowed"})
                        if(element.access.includes("HICWRPROT"))
                            AvailableOptions.push({name : "MEMCFG_PROT_ALLOWHICWRITE", displayName: "HIC write allowed"})

                        AccessConfig.push(
                        {
                            name         : "access_" + ramMacro,
                            displayName  : element.name + " RAM Access",
                            description: "For GSRAM owned by CPU2: this code will be generated on CPU2",
                            minSelections: 0,
                            options      : AvailableOptions,
                            default      : AvailableOptions.map(a=>a.name)
                        })
                    }
                } 
        }
    );


/* Section : RAM Initialization */
device_driverlib_peripheral.MEMCFG_SECT.
    forEach((element, index) =>
        {
            if (!element.name.includes("_ALL"))
            {
                if (Common.isContextCPU1())       
                    {
                        if (element.name.includes("MEMCFG_SECT_GS"))
                        InitRAM.push(
                            {
                                name       : "init_" + element.name,
                                displayName: element.displayName,
                                default    : false
                            }
                        )
                    }
                // only GS/LS/D/M/MSG RAMs. check for MEMCFG_SECT_M covers MSGRAM as well
                if ((((element.name.includes("MEMCFG_SECT_D") || element.name.includes("MEMCFG_SECT_LS")) && (Common.isContextCPU1() || !["F28P65x"].includes(system.deviceData.deviceId))) ||
                    element.name.includes("MEMCFG_SECT_M")) && (Common.isContextCPU1() || !element.name.includes("CM"))) 
                    {
                        InitRAM.push(
                            {
                                name       : "init_" + element.name,
                                displayName: element.displayName,
                                default    : false
                            }
                        )
                    }
            }
        }
    );


/* Section : Lock Registers  */
device_driverlib_peripheral.MEMCFG_SECT.
forEach((element, index) =>
    {
        if (!element.name.includes("_ALL"))
        {
            if((element.name.includes("MEMCFG_SECT_M") ||
                ((element.name.includes("MEMCFG_SECT_LS") || element.name.includes("MEMCFG_SECT_D")) &&
                (!["F28P65x"].includes(system.deviceData.deviceId) || Common.isContextCPU1()))) &&
                (Common.isContextCPU1() || !element.name.includes("CM")))
            {
                LockConfig.push(
                {
                    name         : "lock_" + element.name,
                    displayName  : "Lock " + element.displayName + " Config Registers",
                    options : [
                        {name: "NoLock", displayName: "Do not Lock"},
                        {name: "Lock",   displayName: "Lock"},
                        {name: "LockCommit",   displayName: "Lock and Commit"},
                    ],
                    default: "NoLock"
                })
            }
            if (Common.isContextCPU1()) 
           {
                if(element.name.includes("MEMCFG_SECT_GS") && (Common.isContextCPU1() || !element.name.includes("CM")))
                {
                    LockConfig.push(
                    {
                        name         : "lock_" + element.name,
                        displayName  : "Lock " + element.displayName + " Config Registers",
                        description: "For GSRAM blocks configured to be owned by CPU2: the code for Initialization, Access Protection, and Lock Configs will be generated on CPU2",
                        options : [
                            {name: "NoLock", displayName: "Do not Lock"},
                            {name: "Lock",   displayName: "Lock"},
                            {name: "LockCommit",   displayName: "Lock and Commit"},
                        ],
                        default: "NoLock"
                    })
                }  
            }
        }
    }
);


/* Section : Access Violation Interrupt */
device_driverlib_peripheral.MEMCFG_MVIOL.     // Controller access violation interrupts                 
    forEach((element, index) =>
        {
            ViolIntConfig.push(
                {
                    name       : "int_" + element.name,
                    displayName: "Enable " + element.displayName + " violation interrupt",
                    default    : false
                }
            )
        }
    );       
if(device_driverlib_peripheral.MEMCFG_NMVIOL)    // Non-controller access violation interrupts
{
    device_driverlib_peripheral.MEMCFG_NMVIOL.
    forEach((element, index) =>
        {
            ViolIntConfig.push(
                {
                    name       : "int_" + element.name,
                    displayName: "Enable " + element.displayName + " violation interrupt",
                    default    : false
                }
            )
        }
    );
}


/* Section : CorrErr Interrupt */
CorrErrIntConfig = [
    {
        name       : "errInt_enable",
        displayName: "Enable Correctable Error Interrupt",
        default    : false
    },
    {
        name       : "errInt_thres",
        displayName: "Threshold for Correctable Error Interrupt",
        default    : 0
    },
]


staticConfig.push(
    {
        name           : "InitRAM",
        displayName    : "RAM Initialization",
        longDescription: "Initialize the memory block.\n - MULTICORE NOTE: Initialization code for GSRAMs owned by CPU2 will be generated for CPU2",
        config         : InitRAM
    },
    {
        name           : "LSRAM_Config",
        displayName    : "LSRAM Configuration",
        longDescription: "",
        config         : LSRAMOwnerConfig
    }
)

if (Common.isContextCPU1())
{
    staticConfig.push(
        {
            name           : "GSRAM_Config",
            displayName    : "GSRAM Configuration",
            longDescription: "\n - For GSRAM blocks owned by CPU2: the code for Access Protection and Lock Configs will be generated on CPU2",
            config         : GSRAMOwnerConfig
        }
    )
}

if (Common.isContextCPU1() && ["F28P65x"].includes(system.deviceData.deviceId))
{
    staticConfig.push(
        {
            name           : "DRAM_Config",
            displayName    : "DRAM Configuration",
            longDescription: "\n - For DRAM blocks owned by CPU2: the code for Access Protection and Lock Configs will be generated on CPU2??????",
            config         : DRAMOwnerConfig
        },
        {
            name           : "FLASH_Config",
            displayName    : "FLASH Configuration",
            longDescription: "\n - For FLASH banks owned by CPU2: the code for Access Protection and Lock Configs will be generated on CPU2??????",
            config         : FLASHOwnerConfig
        }
    )
}

//["F2838x", "F2837xD", "F2837xS", "F2807x","F28P65x"].includes(system.deviceData.deviceId)
if(yesROM)
{
    staticConfig.push(
        {
            name           : "ROM_Config",
            displayName    : "ROM Access Configuration",
            longDescription: "",
            config         : ROMConfig
        }
    )
}


staticConfig.push(
    {
        name           : "Access_Config",
        displayName    : "Access Protection for RAMs",
        longDescription: "MULTICORE NOTE: Access Protection code for GSRAMs owned by CPU2 will be generated on CPU2",
        config         : AccessConfig
    },
    {
        name           : "Lock_Config",
        displayName    : "Lock RAM Config Registers",
        longDescription: " - Do not lock : Writes to ACCPROT, TEST, INIT and MSEL fields are allowed\n - Lock :  Writes to ACCPROT, TEST, INIT and MSEL fields are blocked. Application can unlock it using the function MemCfg_unlockConfig()\n - Lock and commit :  Writes to ACCPROT, TEST, INIT and MSEL fields are permanently blocked.\n - MULTICORE NOTE: Lock Config code for GSRAMs owned by CPU2 will be generated on CPU2",
        config         : LockConfig
    },
    {
        name           : "ViolInt_Config",
        displayName    : "Access Violation Interrupt",
        longDescription: "",
        config         : ViolIntConfig
    },
    {
        name           : "CorrError_Int",
        displayName    : "Correctable Error Interrupt",
        longDescription: "",
        config         : CorrErrIntConfig
    },
    {
        name       : "registerInterrupts",
        displayName: "Register Interrupt Handler",
        default    : false
    }
)

/* For SYS_ERR interrupt shared across modules */
var sharedModuleInstances = undefined

if(["F2838x", "F280013x", "F280015x", "F28P65x"].includes(system.deviceData.deviceId))
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

function onValidate(inst, validation)
{
    if(["F2837xS", "F2837xD", "F2807x", "F28004x"].includes(system.deviceData.deviceId))
        var maxThres = 0xFFFFFFFF
    else
        var maxThres = 0xFFFF

    if (inst.errInt_thres > maxThres)
    {
        validation.logError("The threshold value must be less than 0x" + maxThres.toString(16).toUpperCase() + "!", inst, "errInt_thres");
    }

    if (inst.rom_prefetch){
        if (!inst.rom_waitstate){
            validation.logWarning("You must enable ROM wait state to properly use the enable ROM prefetch setting", inst, "rom_waitstate");
        }
    }

    if (Common.isMultiCoreSysConfig() || (Common.isMultiCoreDevice() && Common.isContextCPU1()))
    {
        var contextNames = Common.getContextNames();
        var context1 = null;
        var context2 = null;
        for (var cntx of contextNames) 
        {
            if (cntx.slice(-1) == "1")       // Look for CPU1 Context 
            {
            context1 = cntx;
            }	

            if (cntx.slice(-1) == "2")       // Look for CPU2 Context 
            {
            context2 = cntx;
            }	
        }
        var CPU1_mod = Common.getModuleForCore("/driverlib/memcfg.js", context1);   // get module from core 1
        var CPU2_mod = Common.getModuleForCore("/driverlib/memcfg.js", context2);   // get module from core 1
        if (CPU1_mod != null)
        {
            var stat_1 = CPU1_mod.$static;
        }

        if (Common.isContextCPU1())
        {
            if (!CPU2_mod){
                validation.logWarning("Error checking and code generation are limited for single core SysConfig on a multicore device. Add memcfg module on CPU2 for full functionality.", inst, "init_MEMCFG_SECT_M0");
            }
        }
        if (Common.isContextCPU2())
        {
            if (!CPU1_mod){
                validation.logWarning("Error checking and code generation are limited for single core SysConfig on a multicore device. Add memcfg module on CPU1 for full functionality.", inst, "init_MEMCFG_SECT_M0");
            }
        }
    }
    else if (Common.isContextCPU2()){

        validation.logWarning("Error checking and code generation are limited for single core SysConfig on a multicore device.", inst, "init_MEMCFG_SECT_M0");
    }

}

var memcfgModule = {
    peripheralName     : "MEMCFG",
    displayName        : "MEMCFG",
    longDescription    : longDescription,
    maxInstances       : 1,
    defaultInstanceName: "myMEMCFG",
    description        : "Memory Configuration",
    moduleStatic : {
        config          : staticConfig,
        moduleInstances: (inst) => {
            if (inst.registerInterrupts)
            {
                if(!["F2838x", "F280013x", "F280015x", "F28P65x"].includes(system.deviceData.deviceId))
                {
                    return [
                        {
                            name: "memcfgAccInt",
                            displayName: "Access Violation Interrupt",
                            moduleName: "/driverlib/interrupt.js",
                            collapsed: true,
                            args: {
                                $name : "RAM_ACC_VIOL_INT",
                                int : "RAM_ACC_VIOL_INT",
                                pinmuxPeripheralModule : "",
                                driverlibInt: "INT_RAM_ACC_VIOL"
                            }
                        },
                        {
                            name: "memcfgCorrErrInt",
                            displayName: "Correctable Error Interrupt",
                            moduleName: "/driverlib/interrupt.js",
                            collapsed: true,
                            args: {
                                $name : "RAM_CORR_ERR_INT",
                                int : "RAM_CORR_ERR_INT",
                                pinmuxPeripheralModule : "",
                                driverlibInt: "INT_RAM_CORR_ERR"
                            }
                        }
                    ]
                }
            }
            return []
        },
        sharedModuleInstances : sharedModuleInstances,
        validate: onValidate,
    },
    templates: {
        boardc: "/driverlib/memcfg/memcfg.board.c.xdt",
        boardh: "/driverlib/memcfg/memcfg.board.h.xdt"
    },
};

exports = memcfgModule;