let Common   = system.getScript("/driverlib/Common.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_drv.js");
let drv_spi_pins =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_drv_spi_pins.js").drvPins;

/* Intro splash on GUI */
let longDescription = "";

function onChangeCP(inst, ui)
{
    if(inst.DISCP)
    {
        ui.CPPUMPCLK.hidden = true;
        ui.CPPWRUPST.hidden = true;
        ui.CPFORCEMODE.hidden = true;
        ui.CPFORCESEL1.hidden = true;
        ui.CPFORCESEL2.hidden = true;
    }
    else
    {
        ui.CPPUMPCLK.hidden = false;
        ui.CPPWRUPST.hidden = false;
        ui.CPFORCEMODE.hidden = false;
        if(inst.CPFORCEMODE){
            ui.CPFORCESEL1.hidden = false;
            ui.CPFORCESEL2.hidden = false;
        }
        else{
            ui.CPFORCESEL1.hidden = true;
            ui.CPFORCESEL2.hidden = true;
        }
    }
}

let config = [
    {
        name        : "disDrv",
        displayName : "Disable DRV outputs",
        description : 'Disable all DRV outputs (GHx & LHx)',
        hidden      : false,
        default     : false
    },
    {
        name        : "CLRFLT",
        displayName : "Clear all faults",
        description : 'Whether or not to clear all faults on initialization.',
        hidden      : false,
        default     : false
    },
    {
        name        : "disableBSTFault",
        displayName : "Disable BST fault",
        description : 'Whether or not to disable BST fault.',
        hidden      : false,
        default     : false
    },
    {
        name        : "disableSNSFault",
        displayName : "Disable SNS fault",
        description : 'Whether or not to disable SNS fault.',
        hidden      : false,
        default     : false
    },
    {
        name        : "disableVDSFault",
        displayName : "Disable VDS fault",
        description : 'Whether or not to disable VDS fault.',
        hidden      : false,
        default     : false
    },
    {
        name        : "disTcp",
        displayName : "Disable TCP",
        description : 'Disable Trickle Charge Pump',
        hidden      : false,
        default     : false
    },
    {
        name        : "enableVdsLvlSelection",
        displayName : "Enable VDS Level Selection through SPI",
        description : 'Enable SPI writes to SEL_VDSLVL bits',
        hidden      : false,
        default     : false,
        onChange    : function(inst, ui) {
            if(inst.enableVdsLvlSelection){
                ui.selectVDSLVL.hidden = false;
            }
            else{
                ui.selectVDSLVL.hidden = true;
            }
        },
    },
    {
        name        : "selectVDSLVL",
        displayName : "Select VDS Level",
        description : 'Select the VDS level.',
        hidden      : true,
        options     : device_driverlib_peripheral.VDSLVL_val,
        default     : "DRV8329_VDSLVL_2_00V",
    },
    {
        name        : "OTSRECO",
        displayName : "OTS Recovery mode",
        description : 'Whether or not to enable OTS auto recovery.',
        hidden      : false,
        default     : device_driverlib_peripheral.OTSRECO_val[0].name,
        options     : device_driverlib_peripheral.OTSRECO_val
    },
    {
        name: "GROUP_DEBUG",
        displayName: "Debug Options",
        description: "",
        longDescription: "",
        collapsed: true,
        config: [
            {
                name        : "debug_readbackTest",
                displayName : "Enable Readback Tests",
                longDescription : "If enabled, after each API call to configure the DRV, the register is read back and the written confguration is verified.",
                hidden      : false,
                default     : false,
            },
        ]
    },
];

let moduleInstances = function () {
    return [
        {
            name: "spi",
            displayName: "SPI Interface for DRV",
            moduleName: "/driverlib/spi.js",
            args:{
                $name:'SPI_DRV',
                emulationMode: "SPI_EMULATION_STOP_MIDWAY",
                bitRate: 1000000,
                useHSMode: false,
            },
            requiredArgs: {
                transferProtocol: "SPI_PROT_POL0PHA0",
                mode: "SPI_MODE_CONTROLLER",
                ptePolarity: "SPI_PTE_ACTIVE_LOW",
                dataWidth: '16',
                useFifo: false,
                useInterrupts: false,
                loopback: false,
                useDMARX: false,
                useDMATX: false,
                useCase: 'ALL',
                clkQual:{
                    qualMode: 'GPIO_QUAL_ASYNC',
                    padConfig: 'PULLUP',
                },
                picoQual: {
                    qualMode: 'GPIO_QUAL_ASYNC',
                    padConfig: 'PULLUP',
                },
                pociQual: {
                    qualMode: 'GPIO_QUAL_ASYNC',
                    padConfig: 'PULLUP',
                },
                pteQual: {
                    qualMode: 'GPIO_QUAL_ASYNC',
                    padConfig: 'PULLUP',
                },
                spi: {
                    $assign: 'SPIA',
                    spi_picoPin: {
                        $assign : drv_spi_pins.PICO.SPIA.pins[0],
                    },
                    spi_pociPin: {
                        $assign : drv_spi_pins.POCI.SPIA.pins[0],
                    },
                    spi_clkPin: {
                        $assign : drv_spi_pins.CLK.SPIA.pins[0],
                    },
                    spi_ptePin: {
                        $assign : drv_spi_pins.PTE.SPIA.pins[0],
                    },
                },
            }
        },
    ];
};

function onValidate(inst, validation)
{
}

let drvModule = {
    peripheralName: "DRV",
    displayName: "DRV",
    maxInstances: 1,
    defaultInstanceName: "myDRV",
    description: "DRV8329 Gate Driver Configuration",
    config: config,
    templates: {
        boardc : "/driverlib/drv/drv.board.c.xdt",
        boardh : "/driverlib/drv/drv.board.h.xdt"
    },
    moduleInstances: moduleInstances,
    validate    : onValidate
};

exports = drvModule;