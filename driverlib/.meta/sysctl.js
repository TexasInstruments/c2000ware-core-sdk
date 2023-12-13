let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_sysctl.js");

let device_driverlib_peripheral_registers = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_sysctl_registers.js");



var selectAccessOption = device_driverlib_peripheral.SysCtl_AccessController
if(!selectAccessOption)
{
    selectAccessOption = device_driverlib_peripheral.SysCtl_AccessMaster
}         

var selectControllerOption = device_driverlib_peripheral.SYSCTL_SEC_CONTROLLER;
if(!selectControllerOption)
{
    selectControllerOption = device_driverlib_peripheral.SYSCTL_SEC_MASTER;
}
  
var canSelectCPU = [];
for (var prd = 0; prd <= 30; prd++){
    var fullSelString = "CPUSEL" + prd.toString();
    device_driverlib_peripheral_registers.SYSCTLRegisters.forEach((element, index) => 
    {
        if (element.name == fullSelString){
            element.bits.forEach((bitElement, number) =>
            {
                canSelectCPU.push(bitElement.name)
            });
        }
    });
}

var enablePeipheralConfigs = []
device_driverlib_peripheral.SysCtl_PeripheralPCLOCKCR.
    forEach((element, index) => 
        {
            var skipCpu2Enable = false;
            var defaultValue = true;
            if ([
                "SYSCTL_PERIPH_CLK_TBCLKSYNC",
                "SYSCTL_PERIPH_CLK_GTBCLKSYNC"
                ].includes(element.name)){
                    defaultValue = false;
            }

            if (["F2837xD"].includes(Common.getDeviceName()) && Common.isContextCPU2()){
                if([
                    "SYSCTL_PERIPH_CLK_HRPWM",
                    "SYSCTL_PERIPH_CLK_EMIF1", "SYSCTL_PERIPH_CLK_EMIF2",
                    "SYSCTL_PERIPH_CLK_USBA",  "SYSCTL_PERIPH_CLK_UPPA",
                    "SYSCTL_PERIPH_CLK_GTBCLKSYNC"
                    ].includes(element.name)){
                        skipCpu2Enable = true;
                }
            }
            if (["F2838x"].includes(Common.getDeviceName()) && Common.isContextCPU2()){
                if([
                    "SYSCTL_PERIPH_CLK_HRCAL",
                    "SYSCTL_PERIPH_CLK_EMIF1", "SYSCTL_PERIPH_CLK_EMIF2",
                    "SYSCTL_PERIPH_CLK_USBA",
                    "SYSCTL_PERIPH_CLK_DCC0", "SYSCTL_PERIPH_CLK_DCC1", "SYSCTL_PERIPH_CLK_DCC2",
                    "SYSCTL_PERIPH_CLK_ECAT", "SYSCTL_PERIPH_CLK_MCANA",
                    "SYSCTL_PERIPH_CLK_GTBCLKSYNC"
                    ].includes(element.name)){
                        skipCpu2Enable = true;
                }
            }
            if (["F28P65x"].includes(Common.getDeviceName()) && Common.isContextCPU2()){
                if([
                    "SYSCTL_PERIPH_CLK_CLA", "SYSCTL_PERIPH_CLK_GTBCLKSYNC"
                    ].includes(element.name)){
                        skipCpu2Enable = true;
                }
            }

            if (!skipCpu2Enable){
                enablePeipheralConfigs.push(
                    {
                        name: "enable_" + element.name,
                        displayName: element.displayName,
                        default : defaultValue
                    }
                )
            }
        }
    );

var gpios = Common.getGPIOs();
var lpmGpios = []
for (var gpioNumber = 0; gpioNumber <= 63; gpioNumber++)
{
    if (gpios.includes("GPIO" + gpioNumber.toString()))
    {
        lpmGpios.push({ name : gpioNumber, displayName: "GPIO" + gpioNumber.toString()});
    }
}


var lpmConfigs = [
    {
        name: "lpmWakeUpPin",
        displayName: "LPM Wake Up Pin",
        default : [],
        minSelections : 0,
        options : lpmGpios,
    }
]

if (!["F28004x"].includes(Common.getDeviceName()))
{
    var standbyOptions = []
    for (var prd = 0; prd <= 63; prd++)
    {
        standbyOptions.push({
            name: prd + 2,
            displayName: (prd + 2).toString() + " OSCCLKs"
        })
    }

    lpmConfigs.push({
        name: "standbyQualificationPeriod",
        displayName: "Standby Qualification Period",
        options : standbyOptions,
        default: standbyOptions[0].name
    })
}

/* Array of CAN configurables that are common across device families */
let staticConfig = [
    {
        name: "splitCode",
        displayName: "Split Code into Separate File",
        default: false,
    },
    {
        name: "GROUP_LPM",
        displayName: "Low Power Mode",
        longDescription : "",
        config : lpmConfigs
    },
    {
        name: "GROUP_ENABLE_PERIPHERAL",
        displayName: "Enable Peripherals",
        longDescription : "",
        config : enablePeipheralConfigs
    }
];

var enableCpuSel = true;
if (["F2837xD", "F2838x", "F28P65x"].includes(Common.getDeviceName()) && Common.isContextCPU2()){
    enableCpuSel = false;
}

if (device_driverlib_peripheral.SysCtl_CPUSelPeripheral && enableCpuSel)
{
    var inInstanceEnumsEnd = []; 
    if (device_driverlib_peripheral.SysCtl_CPUSelPeriphInstance && ["F28P65x"].includes(Common.getDeviceName())){       
            device_driverlib_peripheral.SysCtl_CPUSelPeriphInstance.
            forEach((element, index) => 
            {
               inInstanceEnumsEnd.push(element.name.split("_").slice(-1)[0]);
               }
            );
        }
    var cpuSelPeipheralConfigs = []
    device_driverlib_peripheral.SysCtl_CPUSelPeripheral.
    forEach((element, index) => 
        {
            var peripheralInsts = Common.peripheralListFromSysCtl(element.name.split("_").slice(-1)[0], device_driverlib_peripheral)
            var cpuSelPerupheralInstsConfigs = []
            peripheralInsts.forEach((element_periphInst, index) => {
                var matchesInstances = 1;
                if(device_driverlib_peripheral.SysCtl_CPUSelPeriphInstance && ["F28P65x"].includes(Common.getDeviceName())){
                    matchesInstances = 0;
                    if(inInstanceEnumsEnd.includes(element_periphInst)){
                        matchesInstances = 1;
                    }
                }
                if (matchesInstances == 1){
                    cpuSelPerupheralInstsConfigs.push(
                        {
                            name: "cpuSel_" + element_periphInst,
                            displayName : element_periphInst,
                            default : device_driverlib_peripheral.SysCtl_CPUSel[0].name,
                            options: device_driverlib_peripheral.SysCtl_CPUSel
                        }
                    )
                }
            });
            cpuSelPeipheralConfigs.push(
                {
                    name: "GROUP_CPUSEL_" + element.name,
                    displayName : element.displayName,
                    config: cpuSelPerupheralInstsConfigs
                }
            )
        }
    );
    var cpuSelControlConfig = {
        name: "GROUP_CPUSEL_PERIPHERAL",
        displayName: "CPU Select For Peripherals",
        longDescription : "",
        config : cpuSelPeipheralConfigs,
    }
    staticConfig.push(cpuSelControlConfig)
}

if (device_driverlib_peripheral.SysCtl_AccessPeripheral)
{
    var accessPeipheralConfigs = [
        {
            name: "lockAccessControlRegs",
            displayName: "Lock Access Control Regsiters",
            default: false
        }
    ]
    device_driverlib_peripheral.SysCtl_AccessPeripheral.
    forEach((element, index) => 
        {
            var accessPermissionConfigs = []
            selectAccessOption.forEach((accMast, accMastIndex) => {
                var skipAccess = false;
                if (["F28003x"].includes(Common.getDeviceName()))
                {
                    if (
                        (element.name == "SYSCTL_ACCESS_HICA" && accMast.name == "SYSCTL_ACCESS_HIC") ||
                        (element.name == "SYSCTL_ACCESS_AESA" && accMast.name == "SYSCTL_ACCESS_HIC") ||
                        (element.name == "SYSCTL_ACCESS_MCANA" && accMast.name == "SYSCTL_ACCESS_DMA1") ||
                        (element.name.includes("SYSCTL_ACCESS_I2C") && accMast.name == "SYSCTL_ACCESS_DMA1") ||
                        (element.name.includes("SYSCTL_ACCESS_SCI") && accMast.name == "SYSCTL_ACCESS_DMA1")||
                        (element.name == "SYSCTL_ACCESS_CANA" && accMast.name == "SYSCTL_ACCESS_CLA1") ||
                        (element.name.includes("SYSCTL_ACCESS_CLB") && accMast.name == "SYSCTL_ACCESS_DMA1") ||
                        (element.name.includes("SYSCTL_ACCESS_ADC") && accMast.name == "SYSCTL_ACCESS_DMA1") ||
                        (element.name.includes("SYSCTL_ACCESS_ADC") && accMast.name == "SYSCTL_ACCESS_HIC")
                        )
                    {
                        skipAccess = true;
                    }
                }
                if (["F28004x"].includes(Common.getDeviceName()))
                {
                    if (
                        (element.name.includes("SYSCTL_ACCESS_CLB") && accMast.name == "SYSCTL_ACCESS_DMA1") ||
                        (element.name == "SYSCTL_ACCESS_CLA1PROMCRC" && accMast.name == "SYSCTL_ACCESS_DMA1")||
                        (element.name.includes("SYSCTL_ACCESS_CAN") && accMast.name == "SYSCTL_ACCESS_CLA1")
                        )
                    {
                        skipAccess = true;
                    }
                }
                if ((!skipAccess) && (accMast.name == "SYSCTL_ACCESS_HIC"))
                {
                    accessPermissionConfigs.push({
                        name: "accessPermission_" + element.name + "_" + accMast.name,
                        legacyNames: ["accessPermission_" + element.name + "_" + "SYSCTL_ACCESS_HICMASTER"],
                        displayName : accMast.displayName,
                        default : device_driverlib_peripheral.SysCtl_AccessPermission[0].name,
                        options: device_driverlib_peripheral.SysCtl_AccessPermission
                    })
                }
                else if (!skipAccess)
                {
                    accessPermissionConfigs.push({
                        name: "accessPermission_" + element.name + "_" + accMast.name,
                        displayName : accMast.displayName,
                        default : device_driverlib_peripheral.SysCtl_AccessPermission[0].name,
                        options: device_driverlib_peripheral.SysCtl_AccessPermission
                    })
                }
                
            })
            accessPeipheralConfigs.push(
                {
                    name: "GROUP_" + element.name,
                    displayName: element.displayName.replace("access", "Access"),
                    config : accessPermissionConfigs
                }
            )
        }
    );
    var accessControlConfig = {
        name: "GROUP_ACCESS_CONTROL_PERIPHERAL",
        displayName: "Access Control For Peripherals",
        longDescription : "",
        config : accessPeipheralConfigs,
    }
    staticConfig.push(accessControlConfig)
}

if (selectControllerOption)
{
    var secControllerFrameConfig = []
    secControllerFrameConfig.push({
        name: "secControllerFrame1",
        legacyNames : ["secMasterFrame1"],
        displayName : "Frame 1 Secondary Controller",
        default : selectControllerOption[0].name,
        options: selectControllerOption
    })
    secControllerFrameConfig.push({
        name: "secControllerFrame2",
        legacyNames : ["secMasterFrame2"],
        displayName : "Frame 2 Secondary Controller",
        default : selectControllerOption[0].name,
        options: selectControllerOption
    })

    staticConfig.push({
        name: "GROUP_SECONDARY_CONTROLLER",
        displayName: "Peripheral Frame Secondary Controller",
        config: secControllerFrameConfig
    })
}


if (device_driverlib_peripheral.SysCtl_SharedPeripheral && enableCpuSel)
{
    var sharedPeripheralAllocateConfig = []
    device_driverlib_peripheral.SysCtl_SharedPeripheral.forEach((element, index) => 
    {
        sharedPeripheralAllocateConfig.push({
            name: "sharedPeripheralAllocate_" + element.name,
            displayName : element.displayName,
            default : false
        })
    })
    
    staticConfig.push({
        name: "GROUP_SHARED_PERIPH_ALLOCATE",
        displayName: "Shared Peripheral Allocation",
        config: sharedPeripheralAllocateConfig
    })
}

if (device_driverlib_peripheral.SysCtl_ClkRegSel)
{
    var clockLockConfig = []
    device_driverlib_peripheral.SysCtl_ClkRegSel.forEach((element, index) => 
    {
        clockLockConfig.push({
            name: "lockClk_" + element.name,
            displayName : element.displayName,
            default : false
        })
    })
    
    staticConfig.push({
        name: "GROUP_CLOCK_LOCK",
        displayName: "Lock Clock Configs",
        config: clockLockConfig
    })
}

if (device_driverlib_peripheral.SysCtl_CpuRegSel)
{
    var sysLockConfig = []
    device_driverlib_peripheral.SysCtl_CpuRegSel.forEach((element, index) => 
    {
        sysLockConfig.push({
            name: "sysClk_" + element.name,
            displayName : element.displayName,
            default : false
        })
    })
    
    staticConfig.push({
        name: "GROUP_SYS_LOCK",
        displayName: "Lock System Configs",
        config: sysLockConfig
    })
}

staticConfig.push({
    name: "GROUP_NMI",
    displayName : "NMI",
    config: [
        {
            name: "enableNMIGlobalInterrupt",
            displayName: "Enable NMI Global Interrupt",
            default: false
        },
        // {
        //     name: "registerNMIInterrupt",
        //     displayName: "Register NMI Interrupt Handler",
        //     default: false
        // },
        
    ]
})

if (device_driverlib_peripheral.SysCtl_SelType  && enableCpuSel){
    var selTypeConfig = []
    device_driverlib_peripheral.SysCtl_SelType.forEach((element, index) => 
    {
        selTypeConfig.push({
            name: "selType_" + element.name,
            displayName : element.displayName.substring(0,element.displayName.indexOf(":")),
            description : element.displayName,
            longDescription : element.displayName,
            default : false
        })

        selTypeConfig.push({
            name: "selTypeLock_" + element.name,
            displayName : "Lock" + element.displayName.substring(0,element.displayName.indexOf(":")).replace("Configure", ""),
            description : "Lock the configuration for Type. " + element.displayName,
            default : false
        })
    })
    
    staticConfig.push({
        name: "GROUP_TYPE",
        displayName: "Peripheral Type Configuration",
        config: selTypeConfig
    })
}

if (["F2838x"].includes(Common.getDeviceName()) && Common.isContextCPU1())
{
    staticConfig.push({
        name: "semOwner",
        displayName: "Semaphore Owner",
        default: device_driverlib_peripheral.SysCtl_CPUSel[0].name,
        options: device_driverlib_peripheral.SysCtl_CPUSel
    })

    staticConfig.push({
        name: "GROUP_CM",
        displayName: "Connectivity Manager (CM) Configuration",
        config: [
            {
                name: "enableCMtoCPU1NMI",
                displayName: "Enable CM to CPU1 NMI",
                options: device_driverlib_peripheral.SYSCTL_FLAG_CMNMIWDRST,
                default: [],
                minSelections : 0
            },
            {
                name: "enableCMtoCPUInterrupt",
                displayName: "Enable CM to CPU1 Interrupt",
                options: device_driverlib_peripheral.SYSCTL_STATUS,
                default: [],
                minSelections : 0
            },
            {
                name: "lockCMConfig",
                displayName: "Lock CM Config",
                default: false,
            },
            {
                name: "setCMInterruptStatusMask",
                displayName: "CM Interrupt Status Mask",
                options: device_driverlib_peripheral.SYSCTL_STATUS,
                default: [],
                minSelections : 0
            }
        ]
    });
}

if (!["F2837xS", "F2837xD", "F2807x", "F28004x"].includes(Common.getDeviceName()))
{
    var enableErrorstatus = true;
    if (["F2838x","F28P65x"].includes(Common.getDeviceName()) && Common.isContextCPU2()){
        enableErrorstatus = false;
    }
    if(enableErrorstatus == true){
        staticConfig.push({
            name: "GROUP_ERROR",
            displayName: "ERRORSTS",
            config: [
                {
                    name: "errorPinPolarity",
                    displayName: "Error Pin Polarity",
                    options: [
                        { name: 1, displayName: "Error when pin transitions from 0 to 1"},
                        { name: 0, displayName: "Error when pin transitions from 1 to 0"},
                    ],
                    default: 0,
                },
                {
                    name: "lockErrorControl",
                    displayName: "Lock Error Control",
                    default: false,
                },
            ]
        });
    }
}

if(Common.isContextCPU1()){
    staticConfig.push({
        name: "enableMCD",
        displayName: "Enable Missing Clock Detect (MCD)",
        default: false,
    })
}

/*
 *  ======== filterHardware ========
 *  Control RX, TX Pin usage by the user specified dataDirection.
 *
 *  param component - hardware object describing signals and
 *                     resources they're attached to
 *
 *  returns Boolean indicating whether or not to allow the component to
 *           be assigned to an instance's $hardware config
 */
function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["SYSCTL"]));
}

function modules(inst)
{
    if (inst.splitCode) {
        return [
            {
                name: "sysctlPullInTemplateConfigC",
                moduleName: "/driverlib/sysctl/sysctl_config.c.dynamic.js",
            }
        ];  
    }
    return [];
}

function onValidate(inst, validation) 
{    
    if (["F28003x"].includes(Common.getDeviceName()))
    {
        if (inst.lpmWakeUpPin.includes(61))
        {
            validation.logError(
                "GPIO61 is not a wake up pin", 
                inst, "lpmWakeUpPin");
        }
    }

}

var sysctlModule = {
    peripheralName: "SYSCTL",
    displayName: "SYSCTL",
    maxInstances: 1,
    defaultInstanceName: "mySYSCTL",
    description: "System Control",
    longDescription: (Common.getCollateralFindabilityList("SYSCTL")),
    filterHardware : filterHardware,
    moduleStatic : {
        config          : staticConfig,
        modules : modules,
        validate: onValidate,
    },
    //config: config,
    templates: {
        boardc : "/driverlib/sysctl/sysctl.board.c.xdt",
        boardh : "/driverlib/sysctl/sysctl.board.h.xdt"
    },
};




exports = sysctlModule;
