let Common   = system.getScript("/driverlib/Common.js");
let references = system.getScript("/driverlib/PeripheralComponentsReferences.js");

let CATEGORY_ANALOG = "Analog";
let CATEGORY_COMS = "Communication";
let CATEGORY_CONTROL = "Control";
let CATEGORY_SYSTEM = "System";
let CATEGORY_BOARD = "Board Components"
let CATEGORY_SW = "Software";

let CATEGORY_LIST = [
    CATEGORY_ANALOG,
    CATEGORY_COMS,
    CATEGORY_CONTROL,
    CATEGORY_SYSTEM,
    CATEGORY_BOARD,
    CATEGORY_SW,
]

var supported_modules_analog = [];
var supported_modules_coms = [];
var supported_modules_system = [];
var supported_modules_contorl = [];
var supported_modules_board = [];
var supported_modules_sw = [];

var supported_modules = {};
supported_modules[CATEGORY_ANALOG] = supported_modules_analog
supported_modules[CATEGORY_COMS] = supported_modules_coms
supported_modules[CATEGORY_SYSTEM] = supported_modules_system
supported_modules[CATEGORY_CONTROL] = supported_modules_contorl
supported_modules[CATEGORY_BOARD] = supported_modules_board
supported_modules[CATEGORY_SW] = supported_modules_sw

var supported_peripheralName_moduleFile = [
     { moduleCategory: CATEGORY_SYSTEM ,  peripheralName : "AIO", moduleFile : "/driverlib/aio.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "CAN", moduleFile : "/driverlib/can.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "CM-I2C", moduleFile : "/driverlib/cmi2c.js"},
     { moduleCategory: CATEGORY_SYSTEM ,  peripheralName : "CLB_OUTPUTXBAR", moduleFile : "/driverlib/clb_outputxbar.js"},
     { moduleCategory: CATEGORY_ANALOG ,  peripheralName : "DC-DC", moduleFile : "/driverlib/dcdc.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "ECAT", moduleFile : "/driverlib/ecat.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "ETHERNET", moduleFile : "/driverlib/ethernet.js"},
     { moduleCategory: CATEGORY_SYSTEM ,  peripheralName : "EMIF1", moduleFile : "/driverlib/emif1.js"},
     { moduleCategory: CATEGORY_SYSTEM ,  peripheralName : "EMIF2", moduleFile : "/driverlib/emif2.js"},
     { moduleCategory: CATEGORY_CONTROL,  peripheralName : "EPWM", moduleFile : "/driverlib/epwm.js"},
     { moduleCategory: CATEGORY_CONTROL,  peripheralName : "EQEP", moduleFile : "/driverlib/eqep.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "FSITX", moduleFile : "/driverlib/fsitx.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "FSIRX", moduleFile : "/driverlib/fsirx.js"},
     { moduleCategory: CATEGORY_BOARD  ,  peripheralName : "FSIRX", moduleFile : "/driverlib/board_components/fsi"},
     { moduleCategory: CATEGORY_SYSTEM ,  peripheralName : "GPIO", moduleFile : "/driverlib/gpio.js"},
     { moduleCategory: CATEGORY_SYSTEM ,  peripheralName : "HIC", moduleFile : "/driverlib/hic.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "I2C", moduleFile : "/driverlib/i2c.js"},
     //{ moduleCategory: CATEGORY_SYSTEM ,  peripheralName : "INPUTXBAR", moduleFile : "/driverlib/inputxbar.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "LIN", moduleFile : "/driverlib/lin.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "MCAN", moduleFile : "/driverlib/mcan.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "MCBSP", moduleFile : "/driverlib/mcbsp.js"},
     { moduleCategory: CATEGORY_SYSTEM ,  peripheralName : "OUTPUTXBAR", moduleFile : "/driverlib/outputxbar.js"},
     { moduleCategory: CATEGORY_SYSTEM ,  peripheralName : "OTHER", moduleFile : "/driverlib/other.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "PMBUS", moduleFile : "/driverlib/pmbus.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "SD", moduleFile : "/driverlib/sd.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "SPI", moduleFile : "/driverlib/spi.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "SCI", moduleFile : "/driverlib/sci.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "SSI", moduleFile : "/driverlib/ssi.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "UART", moduleFile : "/driverlib/uart.js"},
     { moduleCategory: CATEGORY_SYSTEM ,  peripheralName : "UPP", moduleFile : "/driverlib/upp.js"},
     { moduleCategory: CATEGORY_COMS   ,  peripheralName : "USB", moduleFile : "/driverlib/usb.js"},
     { moduleCategory: CATEGORY_ANALOG ,  peripheralName : "ANALOG", moduleFile : "/driverlib/analog.js"},
];

var static_peripheralName_moduleFile = [
     { moduleCategory: CATEGORY_SYSTEM , peripheralName : "INTERRUPT", moduleFile : "/driverlib/interrupt.js"},
     { moduleCategory: CATEGORY_SYSTEM , peripheralName : "INPUTXBAR", moduleFile : "/driverlib/inputxbar_input.js"},
     { moduleCategory: CATEGORY_SYSTEM , peripheralName : "SYSCTL", moduleFile : "/driverlib/sysctl.js"},
     { moduleCategory: CATEGORY_ANALOG , peripheralName : "ASYSCTL", moduleFile : "/driverlib/asysctl.js"},
     { moduleCategory: CATEGORY_ANALOG , peripheralName : "ADC", moduleFile : "/driverlib/adc.js"},
     { moduleCategory: CATEGORY_SYSTEM , peripheralName : "CPUTIMER", moduleFile : "/driverlib/cputimer.js"},
     { moduleCategory: CATEGORY_SYSTEM , peripheralName : "EPWMXBAR", moduleFile : "/driverlib/epwmxbar.js"},
     { moduleCategory: CATEGORY_SYSTEM , peripheralName : "WATCHDOG", moduleFile : "/driverlib/watchdog.js"},
     { moduleCategory: CATEGORY_CONTROL, peripheralName : "ECAP", moduleFile : "/driverlib/ecap.js"},
     { moduleCategory: CATEGORY_CONTROL, peripheralName : "SYNC", moduleFile : "/driverlib/sync.js"},
     { moduleCategory: CATEGORY_SYSTEM , peripheralName : "MEMCFG", moduleFile : "/driverlib/memcfg.js"},
     { moduleCategory: CATEGORY_BOARD , peripheralName : "", moduleFile : "/driverlib/board_components/led"},
     { moduleCategory: CATEGORY_BOARD , peripheralName : "", moduleFile : "/driverlib/board_components/swtch"},
     { moduleCategory: CATEGORY_SW,  moduleFile : "/driverlib/interrupt_nesting.js"},
     { moduleCategory: CATEGORY_SW,  moduleFile : "/driverlib/device_support.js"},
]

var device_specific_modules = [
    { moduleCategory: CATEGORY_ANALOG , devices : ["F28004x", "F2838x", "F2837xS", "F2837xD", "F2807x", "F28003x","F28P55x", "F280013x", "F280015x", "F28002x", "F28P65x"], peripheralName : "CMPSS", moduleFile : "/driverlib/cmpss.js"},
    { moduleCategory: CATEGORY_ANALOG , devices : ["F280013x", "F280015x"], peripheralName : "CMPSSLITE", moduleFile : "/driverlib/cmpss_lite.js"},
    { moduleCategory: CATEGORY_ANALOG , devices : ["F28004x", "F2838x", "F2837xS", "F2837xD", "F2807x", "F28003x","F28P55x", "F28P65x"], peripheralName : "DAC", moduleFile : "/driverlib/dac.js"},
    { moduleCategory: CATEGORY_SYSTEM , devices : ["F28004x", "F2838x", "F28002x", "F28003x","F28P55x", "F28P65x"], peripheralName : "ERAD", moduleFile : "/driverlib/erad.js"},
    { moduleCategory: CATEGORY_CONTROL, devices : ["F28004x", "F2838x", "F2837xS", "F2837xD", "F2807x", "F28003x","F28P55x", "F28002x", "F28P65x"], peripheralName : "CLB", moduleFile : "/driverlib/clb.js"},
    { moduleCategory: CATEGORY_SYSTEM , devices : ["F28004x", "F2838x", "F2837xS", "F2837xD", "F2807x", "F28003x","F28P55x", "F28002x", "F28P65x"], peripheralName : "CLBXBAR", moduleFile : "/driverlib/clbxbar.js"},
    { moduleCategory: CATEGORY_SYSTEM , devices : ["F28002x", "F2838x", "F28003x","F28P55x", "F28P65x"], peripheralName : "CLB_INPUTXBAR", moduleFile : "/driverlib/clb_inputxbar_input.js"},
    { moduleCategory: CATEGORY_ANALOG , devices : ["F28004x"], peripheralName : "PGA", moduleFile : "/driverlib/pga.js"},
    { moduleCategory: CATEGORY_SYSTEM , devices : ["F28004x", "F28002x", "F2838x", "F28003x","F28P55x", "F280013x", "F280015x", "F28P65x"], peripheralName : "DCC", moduleFile : "/driverlib/dcc.js"},
    { moduleCategory: CATEGORY_SYSTEM , devices : ["F2837xD", "F2837xS", "F28004x", "F2838x", "F28003x","F28P55x", "F28P65x"], peripheralName : "CLA", moduleFile : "/driverlib/cla.js"},
    { moduleCategory: CATEGORY_COMS   , devices : ["F28002x", "F28003x","F28P55x", "F28004x","F2807x", "F2837xS", "F2837xD", "F2838x", "F28P65x"], peripheralName : "DMA", moduleFile : "/driverlib/dma.js"},
    { moduleCategory: CATEGORY_SYSTEM , devices : ["F28002x", "F2838x", "F28003x","F28P55x", "F28P65x"], peripheralName : "BGCRC", moduleFile : "/driverlib/bgcrc.js"},
    { moduleCategory: CATEGORY_SYSTEM , devices : ["F28003x","F28P65x","F28P55x", "F2838x", "F28002x", "F28004x", "F2837xD", "F2837xS","F280013x","F280015x","F2807x"], peripheralName : "FLASH", moduleFile : "/driverlib/flash.js"},
    { moduleCategory: CATEGORY_SYSTEM , devices : ["F2838x", "F2837xD", "F28P65x"], peripheralName : "IPC", moduleFile : "/driverlib/ipc.js"},
    { moduleCategory: CATEGORY_SYSTEM , devices : ["F28P65x"], peripheralName : "MINDB_XBAR", moduleFile : "/driverlib/mindbxbar.js"},
    { moduleCategory: CATEGORY_SYSTEM , devices : ["F28P65x"], peripheralName : "ICL_XBAR", moduleFile : "/driverlib/iclxbar.js"},
    { moduleCategory: CATEGORY_ANALOG , devices : ["F28P65x"], peripheralName : "ADCSafetyChecker", moduleFile : "/driverlib/adcsafetychecker.js"},
]

if (Common.onlyPinmux())
{
    static_peripheralName_moduleFile = []
    device_specific_modules = []
}

var cpu2_unavailable_peripherals = {
    "F2837xD" : [
        { peripheralName: "GPIO", moduleFile : "/driverlib/gpio.js"},
        { peripheralName: "AIO", moduleFile : "/driverlib/aio.js"},
        { peripheralName: "ANALOG", moduleFile : "/driverlib/analog.js"},
        { peripheralName: "INPUTXBAR", moduleFile : "/driverlib/inputxbar.js"},
        { peripheralName: "INPUTXBAR", moduleFile : "/driverlib/inputxbar_input.js"},
        { peripheralName: "OUTPUTXBAR", moduleFile : "/driverlib/outputxbar.js" },
        { peripheralName: "EPWMXBAR", moduleFile : "/driverlib/epwmxbar.js"},
        { peripheralName: "CLBXBAR", moduleFile : "/driverlib/clbxbar.js"},
        { peripheralName: "USB", moduleFile : "/driverlib/usb.js" },
        { peripheralName: "UPP", moduleFile : "/driverlib/upp.js" },
        { peripheralName: "EMIF2", moduleFile : "/driverlib/emif2.js" },
        { peripheralName: "SYNC", moduleFile : "/driverlib/sync.js" },
        { peripheralName: "ASYSCTL", moduleFile : "/driverlib/asysctl.js" },
        { peripheralName: "OTHER", moduleFile : "/driverlib/other.js"},
    ],
    "F2838x" : [
        { peripheralName: "GPIO", moduleFile : "/driverlib/gpio.js"},
        { peripheralName: "AIO", moduleFile : "/driverlib/aio.js"},
        { peripheralName: "ANALOG", moduleFile : "/driverlib/analog.js"},
        { peripheralName: "INPUTXBAR", moduleFile : "/driverlib/inputxbar.js"},
        { peripheralName: "OUTPUTXBAR", moduleFile : "/driverlib/outputxbar.js" },
        { peripheralName: "EPWMXBAR", moduleFile : "/driverlib/epwmxbar.js"},
        { peripheralName: "CLBXBAR", moduleFile : "/driverlib/clbxbar.js"},
        { peripheralName: "CLB_INPUTXBAR", moduleFile : "/driverlib/clb_inputxbar.js"},
        { peripheralName: "CLB_INPUTXBAR", moduleFile : "/driverlib/clb_inputxbar_input.js"},
        { peripheralName: "CLB_OUTPUTXBAR", moduleFile : "/driverlib/clb_outputxbar.js"},     
        { peripheralName: "USB", moduleFile : "/driverlib/usb.js" },
        { peripheralName: "UPP", moduleFile : "/driverlib/upp.js" },
        { peripheralName: "EMIF2", moduleFile : "/driverlib/emif2.js" },
        { peripheralName: "SYNC", moduleFile : "/driverlib/sync.js" },
        { peripheralName: "ASYSCTL", moduleFile : "/driverlib/asysctl.js" },
        { peripheralName: "ECAT", moduleFile : "/driverlib/ecat.js" },
        { peripheralName: "ETHERNET", moduleFile : "/driverlib/ethernet.js" },
        { peripheralName: "UART", moduleFile : "/driverlib/uart.js" },
        { peripheralName: "CM-I2C", moduleFile : "/driverlib/cmi2c.js" },
        { peripheralName: "OTHER", moduleFile : "/driverlib/other.js"},
    ],
    "F28P65x" : [
        { peripheralName: "GPIO", moduleFile : "/driverlib/gpio.js"},
        { peripheralName: "AIO", moduleFile : "/driverlib/aio.js"},
        { peripheralName: "ANALOG", moduleFile : "/driverlib/analog.js"},
        { peripheralName: "INPUTXBAR", moduleFile : "/driverlib/inputxbar.js"},
        { peripheralName: "OUTPUTXBAR", moduleFile : "/driverlib/outputxbar.js" },
        { peripheralName: "EPWMXBAR", moduleFile : "/driverlib/epwmxbar.js"},
        { peripheralName: "CLBXBAR", moduleFile : "/driverlib/clbxbar.js"},
        { peripheralName: "ICLXBAR", moduleFile : "/driverlib/iclxbar.js"},
        { peripheralName: "MINDBXBAR", moduleFile : "/driverlib/mindbxbar.js"},
        { peripheralName: "CLB_INPUTXBAR", moduleFile : "/driverlib/clb_inputxbar.js"},
        { peripheralName: "CLB_INPUTXBAR", moduleFile : "/driverlib/clb_inputxbar_input.js"},
        { peripheralName: "CLB_OUTPUTXBAR", moduleFile : "/driverlib/clb_outputxbar.js"},
        { peripheralName: "SYNC", moduleFile : "/driverlib/sync.js" },
        { peripheralName: "ASYSCTL", moduleFile : "/driverlib/asysctl.js" },
    ]
}

for (var periphName_moduleFile_index in supported_peripheralName_moduleFile)
{
    if (Common.peripheralCount(
        supported_peripheralName_moduleFile[periphName_moduleFile_index].peripheralName) > 0)
    {
        supported_modules[supported_peripheralName_moduleFile[periphName_moduleFile_index].moduleCategory].
            push(supported_peripheralName_moduleFile[periphName_moduleFile_index].moduleFile)
    }

}

for (var periphName_moduleFile_index in static_peripheralName_moduleFile)
{   
    supported_modules[static_peripheralName_moduleFile[periphName_moduleFile_index].moduleCategory].
        push(static_peripheralName_moduleFile[periphName_moduleFile_index].moduleFile)
}


for (var device_specific_modules_index in device_specific_modules)
{   
    if (device_specific_modules[device_specific_modules_index].
        devices.includes(Common.getDeviceName()))
    {
        supported_modules[device_specific_modules[device_specific_modules_index].moduleCategory].
            push(device_specific_modules[device_specific_modules_index].moduleFile)
    }
}

//console.log(system.deviceData.board)
var views = []
if(Common.getBoard())
{
    views.push(
        {
            "name": "/boards/templates/board_info.xdt",
            "displayName": "Board Info",
            "viewType": "markdown"
        },
    )
}


if (["F2837xD", "F2838x", "F28P65x"].includes(Common.getDeviceName()))
{
    // Multi-core Check
    var device_cpu2_unavailable_peripherals = cpu2_unavailable_peripherals[Common.getDeviceName()];
    if (device_cpu2_unavailable_peripherals)
    {
        if (Common.isContextCPU2())
        {
            for (var category of CATEGORY_LIST)
            {
                for (var unavailable_peripheral of device_cpu2_unavailable_peripherals)
                {
                    var indexToRemove = supported_modules[category].indexOf(unavailable_peripheral.moduleFile)
                    if (indexToRemove > -1)
                    {
                        supported_modules[category].splice(indexToRemove, 1)
                    }
                }
            }
        }
    }
}

// console.log(supported_modules[CATEGORY_SYSTEM])
// console.log(supported_modules[CATEGORY_COMS])
// console.log(supported_modules[CATEGORY_ANALOG])
// console.log(supported_modules[CATEGORY_CONTROL])

exports = {
    
    displayName: "C2000Ware SysConfig",
    topModules: [

        {
            displayName: CATEGORY_SYSTEM,
            description: "System configured here",
            modules: supported_modules[CATEGORY_SYSTEM]
        },
        {
            displayName: CATEGORY_ANALOG,
            description: "Analog peripherals get configured here",
            modules: supported_modules[CATEGORY_ANALOG]
            // categories: [{
            //     displayName: "Sub Cat",
            //     modules: ["/driverlib/sysctl.js"]
            // }]
        },
        {
            displayName: CATEGORY_CONTROL,
            description: "Control peripherals get configured here",
            modules: supported_modules[CATEGORY_CONTROL]
            // categories: [{
            // }]
        },
        {
            displayName: CATEGORY_COMS,
            description: "Communication peripherals get configured here",
            modules: supported_modules[CATEGORY_COMS]
        },
        {
            displayName: CATEGORY_SW,
            description: "Software modules configuration",
            modules: supported_modules[CATEGORY_SW]
        },

        {
            displayName : CATEGORY_BOARD,
            description : "Board component configurations",
            modules : supported_modules[CATEGORY_BOARD]
        }
    ],
    references: references.componentReferences,
    templates: [{
            name: "/driverlib/board.c.xdt",
            outputPath: "board.c",
            alwaysRun: true
        },
        {
            name: "/driverlib/board.h.xdt",
            outputPath: "board.h",
            alwaysRun: true
        },
        {
            name: "/driverlib/board.cmd.genlibs.xdt",
            outputPath: "board.cmd.genlibs",
            alwaysRun: true
        },
        {
            name: "/driverlib/board.opt.xdt",
            outputPath: "board.opt",
            alwaysRun: true
        },
        {
            name: "/driverlib/pinmux.csv.xdt",
            outputPath: "pinmux.csv",
            alwaysRun: true
        },
        {
            name: "/driverlib/epwm/templates/epwm.dot.xdt",
            outputPath: "epwm.dot",
        },
        {
            name: "/driverlib/device/device.c.xdt",
            outputPath: "device.c",
        },
        {
            name: "/driverlib/device/device.h.xdt",
            outputPath: "device.h",
        },
        {
            name: "/driverlib/adc/templates/adc.dot.xdt",
            outputPath: "adc.dot",
        },
        {
            name: "/driverlib/sysctl/sysctl_config.c.xdt",
            outputPath: "sysctl_config.c",
        },
        {
            name: "/driverlib/interrupt_nesting/sw_prioritized_defaultisr.c.xdt",
            outputPath: "sw_prioritized_defaultisr.c",
        },
        {
            name: "/driverlib/interrupt_nesting/sw_prioritized_isr_levels.h.xdt",
            outputPath: "sw_prioritized_isr_levels.h",
        }
    ],
    views : views
    
}