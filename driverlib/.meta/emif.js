let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_emif.js");

var selectControllerOption = device_driverlib_peripheral.EMIF_ControllerSelect;
if(!selectControllerOption)
{
    selectControllerOption = device_driverlib_peripheral.EMIF_MasterSelect;
}
  
let device_sysctl_nets =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_sysctl.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

function onChangeCS_EMIF1 (inst,ui) {
    var csConfigs = ["WriteSetup","WriteStrobe","WriteHold","ReadSetup","ReadStrobe","ReadHold","TurnAround","secWriteSetup","secWriteStrobe","secWriteHold","secReadSetup","secReadStrobe","secReadHold","WriteOp","ReadOp","secTurnAround","SelStrobe","WordSize","AddrMSB","enableExtWait"];
    for (var cs = 2; cs <= 4; cs++){
        for (var csConfig of csConfigs){
            ui["cs" + cs.toString() + csConfig].hidden = !inst["enableCS" + cs.toString()];
        }
    }
}

function onChangeCS_EMIF2 (inst,ui) {
    var csConfigs = ["WriteSetup","WriteStrobe","WriteHold","ReadSetup","ReadStrobe","ReadHold","TurnAround","secWriteSetup","secWriteStrobe","secWriteHold","secReadSetup","secReadStrobe","secReadHold","WriteOp","ReadOp","secTurnAround","SelStrobe","WordSize","AddrMSB","enableExtWait"];
    var cs = 2;
    for (var csConfig of csConfigs){
        ui["cs" + cs.toString() + csConfig].hidden = !inst["enableCS" + cs.toString()];
    }
}

//EM1A13 does NOT work with CS0
let EMIF1_ADDR_BUS_MSB_CS0 = [
    { name: "EM1A7", displayName: "EM1A7" },
    { name: "EM1A8", displayName: "EM1A8" },
    { name: "EM1A9", displayName: "EM1A9" },
    { name: "EM1A10", displayName: "EM1A10" },
    { name: "EM1A11", displayName: "EM1A11" },
    { name: "EM1A12", displayName: "EM1A12" }
]

let EMIF1_ADDR_BUS_MSB_CS2 = [
    { name: "EM1BA0", displayName: "EM1BA0" },
    { name: "EM1BA1", displayName: "EM1BA1" },
    { name: "EM1A0", displayName: "EM1A0" },
    { name: "EM1A1", displayName: "EM1A1" },
    { name: "EM1A2", displayName: "EM1A2" },
    { name: "EM1A3", displayName: "EM1A3" },
    { name: "EM1A4", displayName: "EM1A4" },
    { name: "EM1A5", displayName: "EM1A5" },
    { name: "EM1A6", displayName: "EM1A6" },
    { name: "EM1A7", displayName: "EM1A7" },
    { name: "EM1A8", displayName: "EM1A8" },
    { name: "EM1A9", displayName: "EM1A9" },
    { name: "EM1A10", displayName: "EM1A10" },
    { name: "EM1A11", displayName: "EM1A11" },
    { name: "EM1A12", displayName: "EM1A12" },
    { name: "EM1A13", displayName: "EM1A13" },
    { name: "EM1A14", displayName: "EM1A14" },
    { name: "EM1A15", displayName: "EM1A15" },
    { name: "EM1A16", displayName: "EM1A16" },
    { name: "EM1A17", displayName: "EM1A17" },
    { name: "EM1A18", displayName: "EM1A18" },
    { name: "EM1A19", displayName: "EM1A19" }
]

let EMIF1_ADDR_BUS_MSB_CS3 = [
    { name: "EM1BA0", displayName: "EM1BA0" },
    { name: "EM1BA1", displayName: "EM1BA1" },
    { name: "EM1A0", displayName: "EM1A0" },
    { name: "EM1A1", displayName: "EM1A1" },
    { name: "EM1A2", displayName: "EM1A2" },
    { name: "EM1A3", displayName: "EM1A3" },
    { name: "EM1A4", displayName: "EM1A4" },
    { name: "EM1A5", displayName: "EM1A5" },
    { name: "EM1A6", displayName: "EM1A6" },
    { name: "EM1A7", displayName: "EM1A7" },
    { name: "EM1A8", displayName: "EM1A8" },
    { name: "EM1A9", displayName: "EM1A9" },
    { name: "EM1A10", displayName: "EM1A10" },
    { name: "EM1A11", displayName: "EM1A11" },
    { name: "EM1A12", displayName: "EM1A12" },
    { name: "EM1A13", displayName: "EM1A13" },
    { name: "EM1A14", displayName: "EM1A14" },
    { name: "EM1A15", displayName: "EM1A15" },
    { name: "EM1A16", displayName: "EM1A16" },
    { name: "EM1A17", displayName: "EM1A17" },
    { name: "EM1A18", displayName: "EM1A18" },
    { name: "EM1A19", displayName: "EM1A19" }
]

let EMIF1_ADDR_BUS_MSB_CS4 = [
    { name: "EM1BA0", displayName: "EM1BA0" },
    { name: "EM1BA1", displayName: "EM1BA1" },
    { name: "EM1A0", displayName: "EM1A0" },
    { name: "EM1A1", displayName: "EM1A1" },
    { name: "EM1A2", displayName: "EM1A2" },
    { name: "EM1A3", displayName: "EM1A3" },
    { name: "EM1A4", displayName: "EM1A4" },
    { name: "EM1A5", displayName: "EM1A5" },
    { name: "EM1A6", displayName: "EM1A6" },
    { name: "EM1A7", displayName: "EM1A7" },
    { name: "EM1A8", displayName: "EM1A8" },
    { name: "EM1A9", displayName: "EM1A9" },
    { name: "EM1A10", displayName: "EM1A10" },
    { name: "EM1A11", displayName: "EM1A11" },
    { name: "EM1A12", displayName: "EM1A12" },
    { name: "EM1A13", displayName: "EM1A13" },
    { name: "EM1A14", displayName: "EM1A14" },
    { name: "EM1A15", displayName: "EM1A15" },
    { name: "EM1A16", displayName: "EM1A16" },
    { name: "EM1A17", displayName: "EM1A17" },
    { name: "EM1A18", displayName: "EM1A18" },
    { name: "EM1A19", displayName: "EM1A19" }
]

let EMIF2_ADDR_BUS_MSB_CS0 = [
    { name: "EM2A7", displayName: "EM2A7" },
    { name: "EM2A8", displayName: "EM2A8" },
    { name: "EM2A9", displayName: "EM2A9" },
    { name: "EM2A10", displayName: "EM2A10" },
    { name: "EM2A11", displayName: "EM2A11" }
]

let EMIF2_ADDR_BUS_MSB_CS2 = [
    { name: "EM2BA0", displayName: "EM2BA0" },
    { name: "EM2BA1", displayName: "EM2BA1" },
    { name: "EM2A0", displayName: "EM2A0" },
    { name: "EM2A1", displayName: "EM2A1" },
    { name: "EM2A2", displayName: "EM2A2" },
    { name: "EM2A3", displayName: "EM2A3" },
    { name: "EM2A4", displayName: "EM2A4" },
    { name: "EM2A5", displayName: "EM2A5" },
    { name: "EM2A6", displayName: "EM2A6" },
    { name: "EM2A7", displayName: "EM2A7" },
    { name: "EM2A8", displayName: "EM2A8" },
    { name: "EM2A9", displayName: "EM2A9" },
    { name: "EM2A10", displayName: "EM2A10" },
    { name: "EM2A11", displayName: "EM2A11" }
]

var Emif_SysClk_MHz = Common.SYSCLK_getMaxMHz();

function getEMIFConfig(emif_instance){
    if(emif_instance != "EMIF1" && emif_instance != "EMIF2"){
        throw new Error("INVALID EMIF TYPE, ONLY TYPES 1 AND 2 ALLOWED")
    }
    var offset = 0;
    let config = [
        //Clock Speed
        {
            name: "clkSpeed",
            displayName : "EMIF Clock Speed (MHz)",
            description : 'EMIF Peripheral Clock Speed',
            hidden      : false,
            default     : 100,
            getValue    : (inst) => {
                if (inst.clkDiv.includes("_DIV_2")){
                    return (inst.$module.$static["emifSYSCLK"] / 2);
                }
                else {
                    return inst.$module.$static["emifSYSCLK"];
                }
            }
        },
        //clock cycle
        {
            name: "clkCycle",
            displayName : "EMIF1 Clock Cycle (ns)",
            description : 'EMIF Peripheral Cycle Period',
            hidden      : false,
            default     : 10,
            getValue    : (inst) => {
                return (1000/inst.clkSpeed);
            }
        },
        {
            name: "selAccess",
            displayName : "Set Access Protection",
            description : 'Sets the access protection',
            hidden      : false,
            default     : device_driverlib_peripheral.EMIF_ACCPROT0[0].name,
            options     : device_driverlib_peripheral.EMIF_ACCPROT0
        },
        {
            name        : "registerInterrupts",
            displayName : "Register Interrupt Handler",
            description : 'Whether or not to register interrupt handlers in the interrupt module.',
            hidden      : false,
            default     : false
        }
    ]
    if(emif_instance == "EMIF1"){
        config.unshift(
            //Clk Divider
                {
                    name: "clkDiv",
                    displayName : "EMIF1 Clock Divider",
                    description : 'SYSCLK divider for EMIF clock',
                    hidden      : false,
                    default     : device_sysctl_nets.SysCtl_EMIF1CLKDivider[1].name,
                    options     : device_sysctl_nets.SysCtl_EMIF1CLKDivider
                }
            );
    }
    else if(emif_instance == "EMIF2"){
        config.unshift(
            //Clk Divider
                {
                    name: "clkDiv",
                    displayName : "EMIF2 Clock Divider",
                    description : 'SYSCLK divider for EMIF clock',
                    hidden      : false,
                    default     : device_sysctl_nets.SysCtl_EMIF2CLKDivider[1].name,
                    options     : device_sysctl_nets.SysCtl_EMIF2CLKDivider
                }
            );
    }
    
    config = config.concat([
    
        {
            name: "enableSyncSelfrefresh",
            displayName : "Enable Self Refresh",
            description : 'Enables Self Refresh mode for ' + emif_instance,
            hidden      : false,
            default     : false
        },
        {
            name: "enableSyncPowerDown",
            displayName : "Enable Power Down",
            description : 'Enables power down mode for synchronous memory to be interfaced.',
            hidden      : false,
            default     : false
        },
        {
            name: "enableSyncRefreshInPowerDown",
            displayName : "Enable Refresh In Power Down",
            description : 'Enables power down mode for synchronous memory to be interfaced.',
            hidden      : false,
            default     : false
        },
        {
            name        : "asyncIntFlags",
            displayName : "Enable Async Interrupt Flags",
            description : 'Select which int flags you would like to enable, if any.',
            hidden      : false,
            default     : [],
            minSelections: 0,
            options     : device_driverlib_peripheral.EMIF_ASYNC_INT
        },
        {
            name: "waitPolarity",
            displayName : "Wait Polarity",
            description : 'Assert level of Wait signal',
            hidden      : false,
            default     : device_driverlib_peripheral.EMIF_AsyncWaitPolarity[0].name,
            options     : device_driverlib_peripheral.EMIF_AsyncWaitPolarity
        },
        {
            name: "maxWait",
            displayName : "Maximum Wait (cycles/16)",
            description : 'Maximum wait cycles timeout divided by 16',
            hidden      : false,
            default     : 80
        },
        {
            name: "maxWaitCycles",
            displayName : "Maximum Wait (cycles)",
            description : 'Maximum wait cycles timeout',
            hidden      : false,
            default     : 80,
            getValue    : (inst) => {
                return (inst.maxWait * 16);
            }
        },
        {
            name: "maxWaitSec",
            displayName : "Maximum Wait (us)",
            description : 'Maximum wait timeout',
            hidden      : false,
            default     : 80,
            getValue    : (inst) => {
                return Number(((inst.maxWaitCycles * inst.clkCycle) / 1000).toFixed(3));
            }
        }
    ]);
    if (["F2837xD", "F2838x", "F28P65x"].includes(Common.getDeviceName()))
    {
        if(emif_instance == "EMIF1"){
            config.push({
                name: "selController",
                legacyNames : ["selMaster"],
                displayName : "Controller Select",
                description : 'Selects the controller for an EMIF1 instance among CPU1 or CPU2',
                hidden      : false,
                default     : selectControllerOption[0].name,
                options     : selectControllerOption
            });
            offset++;
        }
    }
    
    config.push(
        {
            name: "cs0Config",
            displayName: "CS0 SDRAM Configuration",
            description: 'Configure EMIF CS0 SDRAM Interface',
            collapsed: true,
            config: [
                //enable
                {
                    name: "enableCS0",
                    displayName : "Enable CS0 SDRAM",
                    description : 'Enable CS0 SDRAM interface',
                    hidden      : false,
                    default     : true
                },
                //CAS latency
                {
                    name: "cs0CAS",
                    displayName : "CAS Latency",
                    description : 'Column Address Strobe Latency',
                    hidden      : false,
                    default     : device_driverlib_peripheral.EMIF_SyncCASLatency[0].name,
                    options     : device_driverlib_peripheral.EMIF_SyncCASLatency
                },
                //number of banks
                {
                    name: "cs0Banks",
                    displayName : "Number of Banks",
                    description : 'Memory Banks',
                    hidden      : false,
                    default     : device_driverlib_peripheral.EMIF_SyncBank[2].name,
                    options     : device_driverlib_peripheral.EMIF_SyncBank
                },
                //CA width 
                {
                    name: "cs0CAWidth",
                    displayName : "Column Address Width",
                    description : 'Number of address signals used for column decode',
                    hidden      : false,
                    default     : device_driverlib_peripheral.EMIF_SyncPageSize[3].name,
                    options     : device_driverlib_peripheral.EMIF_SyncPageSize
                },
                //Refresh Rate 
                {
                    name: "cs0Refresh",
                    displayName : "Refresh Rate (cycles)",
                    description : 'Interval at which SDRAM will be refreshed',
                    hidden      : false,
                    default     : 781
                    //options     : 
                },
                //tRFC
                {
                    name: "cs0tRFC",
                    displayName : "tRFC (cycles)",
                    description : 'Refresh cycle time (or refresh to refresh command)',
                    hidden      : false,
                    default     : 3
                    //options     : 
                },
                //tRP
                {
                    name: "cs0tRP",
                    displayName : "tRP (cycles)",
                    description : 'Precharge command to refresh or activate command',
                    hidden      : false,
                    default     : 1
                    //options     : 
                },
                //tRCD
                {
                    name: "cs0tRCD",
                    displayName : "tRCD (cycles)",
                    description : 'Activate command to read/write command',
                    hidden      : false,
                    default     : 2
                    //options     : 
                },
                //tWR
                {
                    name: "cs0tWR",
                    displayName : "tWR (cycles)",
                    description : 'Write recovery time (or write to precharge command)',
                    hidden      : false,
                    default     : 1
                    //options     : 
                },
                //tRAS
                {
                    name: "cs0tRAS",
                    displayName : "tRAS (cycles)",
                    description : 'Active to precharge command',
                    hidden      : false,
                    default     : 4
                    //options     : 
                },
                //tRC
                {
                    name: "cs0tRC",
                    displayName : "tRC (cycles)",
                    description : 'Activate to Activate command in the same bank',
                    hidden      : false,
                    default     : 6
                    //options     : 
                },
                //tRRD
                {
                    name: "cs0tRRD",
                    displayName : "tRRD (cycles)",
                    description : 'Activate to Activate command in a different bank',
                    hidden      : false,
                    default     : 1
                    //options     : 
                },
                //tXSR
                {
                    name: "cs0tXSR",
                    displayName : "tXSR (cycles)",
                    description : 'Exit self refresh to any command',
                    hidden      : false,
                    default     : 7
                    //options     : 
                },
                {
                    name: "cs0Timings",
                    collapsed: false,
                    config: [
                        {
                            name: "secRefresh",
                            displayName : "Calculated Refresh Rate (us)",
                            description : 'Commonly 7.8125 us (tREFI)',
                            hidden      : false,
                            default     : 0.0,
                            getValue    : (inst) => {
                                return Number((inst.cs0Refresh/inst.clkSpeed).toFixed(3));
                            }
                        },
                        {
                            name: "secRefInterval",
                            displayName : "Calculated Refresh interval for 8k cycles (ms)",
                            description : 'Commonly 64ms for 8192 refresh cycles',
                            hidden      : false,
                            default     : 0,
                            getValue    : (inst) => {
                                return Number((inst.secRefresh * (8192/1000)).toFixed(3));
                            }
                        },
                        {
                            name: "sectRFC",
                            displayName : "Calculated tRFC (ns)",
                            description : 'Refresh cycle time (or refresh to refresh command)',
                            hidden      : false,
                            default     : 0,
                            getValue    : (inst) => {
                                return Number((1000 * (inst.cs0tRFC/inst.clkSpeed)).toFixed(3));
                            }
                        },
                        {
                            name: "sectRP",
                            displayName : "Calculated tRP (ns)",
                            description : 'Precharge command to refresh or activate command',
                            hidden      : false,
                            default     : 0,
                            getValue    : (inst) => {
                                return Number((1000 * (inst.cs0tRP/inst.clkSpeed)).toFixed(3));
                            }
                        },
                        {
                            name: "sectRCD",
                            displayName : "Calculated tRCD (ns)",
                            description : 'Activate command to read/write command',
                            hidden      : false,
                            default     : 0,
                            getValue    : (inst) => {
                                return Number((1000 * (inst.cs0tRCD/inst.clkSpeed)).toFixed(3));
                            }
                        },
                        {
                            name: "sectWR",
                            displayName : "Calculated tWR (ns)",
                            description : 'Write recovery time (or write to precharge command)',
                            hidden      : false,
                            default     : 0,
                            getValue    : (inst) => {
                                return Number((1000 * (inst.cs0tWR/inst.clkSpeed)).toFixed(3));
                            }
                        },
                        {
                            name: "sectRAS",
                            displayName : "Calculated tRAS (ns)",
                            description : 'Active to precharge command',
                            hidden      : false,
                            default     : 0,
                            getValue    : (inst) => {
                                return Number((1000 * (inst.cs0tRAS/inst.clkSpeed)).toFixed(3));
                            }
                        },
                        {
                            name: "sectRC",
                            displayName : "Calculated tRC (ns)",
                            description : 'Activate to Activate command in the same bank',
                            hidden      : false,
                            default     : 0,
                            getValue    : (inst) => {
                                return Number((1000 * (inst.cs0tRC/inst.clkSpeed)).toFixed(3));
                            }
                        },
                        {
                            name: "sectRRD",
                            displayName : "Calculated tRRD (ns)",
                            description : 'Activate to Activate command in a different bank',
                            hidden      : false,
                            default     : 0,
                            getValue    : (inst) => {
                                return Number((1000 * (inst.cs0tRRD/inst.clkSpeed)).toFixed(3));
                            }
                        },
                        {
                            name: "sectXSR",
                            displayName : "Calculated tXSR (ns)",
                            description : 'Exit self refresh to any command',
                            hidden      : false,
                            default     : 0,
                            getValue    : (inst) => {
                                return Number((1000 * (inst.cs0tXSR/inst.clkSpeed)).toFixed(3));
                            }
                        },
                    ]
                }
            ]
        }
    );
    //adding CS0MSB with values specific to EMIF1 and EMIF2
    if(emif_instance == "EMIF1"){
        let item = {
            name: "cs0Narrow",
            displayName : "Narrow Mode",
            description : 'Select between 16b or 32b data bus',
            hidden      : false,
            default     : device_driverlib_peripheral.EMIF_SyncNarrowMode[1].name,
            options     : device_driverlib_peripheral.EMIF_SyncNarrowMode
        };
        config[13+offset].config.splice(2,0,item);
        config[13+offset].config.push({
            name: "cs0AddrMSB",
            displayName : "Address Bus MSB",
            description : 'Most significant address bit signal',
            hidden      : false,
            default     : EMIF1_ADDR_BUS_MSB_CS0[4].name,
            options     : EMIF1_ADDR_BUS_MSB_CS0
        });
    }
    else if(emif_instance == "EMIF2"){
        let item = {
            name: "cs0Narrow",
            displayName : "Narrow Mode",
            description : 'Select between 16b or 32b data bus',
            hidden      : false,
            default     : device_driverlib_peripheral.EMIF_SyncNarrowMode[0].name,
            options     : [device_driverlib_peripheral.EMIF_SyncNarrowMode[0]]
        };
        config[13+offset].config.splice(2,0,item);
        config[13].config.push({
            name: "cs0AddrMSB",
            displayName : "Address Bus MSB",
            description : 'Most significant address bit signal',
            hidden      : false,
            default     : EMIF2_ADDR_BUS_MSB_CS0[3].name,
            options     : EMIF2_ADDR_BUS_MSB_CS0
        });
    }
    config.push(
        //CS2
        {
            name: "cs2Config",
            displayName: "EMIF CS2 Interface",
            description: 'Configure EMIF CS2 Interface',
            collapsed: true,
            config: [
                {
                    name: "enableCS2",
                    displayName : "Enable CS2 ASYNC",
                    description : 'Enable EMIF CS2 Interface',
                    hidden      : false,
                    default     : true,
                    onChange    : onChangeCS_EMIF1,
                },
                {
                    name: "cs2WriteSetup",
                    displayName : "Write Setup (cycles)",
                    description : 'Address setup before strobe signal is asserted',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs2WriteStrobe",
                    displayName : "Write Strobe (cycles)",
                    description : 'Duration that strobe signal is asserted',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs2WriteHold",
                    displayName : "Write Hold (cycles)",
                    description : 'Address and Data hold after strobe signal is deasserted',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs2ReadSetup",
                    displayName : "Read Setup (cycles)",
                    description : 'Address setup before strobe signal is asserted',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs2ReadStrobe",
                    displayName : "Read Strobe (cycles)",
                    description : 'Duration that strobe signal is asserted',
                    hidden      : false,
                    default     : 4
                },
                {
                    name: "cs2ReadHold",
                    displayName : "Read Hold (cycles)",
                    description : 'Data hold after strobe signal is deasserted',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs2TurnAround",
                    displayName : "Turn Around (cycles)",
                    description : 'Delay from Read to Write, or Write to Read',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs2Timings",
                    collapsed: false,
                    //hidden: false,
                    config: [
                        {
                            name: "cs2secWriteSetup",
                            displayName : "Calculated Write Setup (ns)",
                            description : 'Address setup before strobe signal is asserted',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs2WriteSetup * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs2secWriteStrobe",
                            displayName : "Calculated Write Strobe (ns)",
                            description : 'Duration that strobe signal is asserted',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs2WriteStrobe * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs2secWriteHold",
                            displayName : "Calculated Write Hold (ns)",
                            description : 'Address and Data hold after strobe signal is deasserted',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs2WriteHold * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs2WriteOp",
                            displayName : "Calculated Write Operation (ns)",
                            description : 'Minimum time to write one word',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs2secWriteSetup + inst.cs2secWriteStrobe + inst.cs2secWriteHold).toFixed(3));
                            }
                        },
                        {
                            name: "cs2secReadSetup",
                            displayName : "Calculated Read Setup (ns)",
                            description : 'Address setup before strobe signal is asserted',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs2ReadSetup * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs2secReadStrobe",
                            displayName : "Calculated Read Strobe (ns)",
                            description : 'Duration that strobe signal is asserted',
                            hidden      : false,
                            default     : 4,
                            getValue    : (inst) => {
                                return Number((inst.cs2ReadStrobe * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs2secReadHold",
                            displayName : "Calculated Read Hold (ns)",
                            description : 'Data hold after strobe signal is deasserted',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs2ReadHold * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs2ReadOp",
                            displayName : "Calculated Read Operation (ns)",
                            description : 'Minimum time to read one word',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs2secReadSetup + inst.cs2secReadStrobe + inst.cs2secReadHold).toFixed(3));
                            }
                        },
                        {
                            name: "cs2secTurnAround",
                            displayName : "Calculated Turn Around (ns)",
                            description : 'Delay from Read to Write, or Write to Read',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs2TurnAround * inst.clkCycle).toFixed(3));
                            }
                        },
                    ]
                },
                {
                    name: "cs2WordSize",
                    displayName : "Word Size",
                    description : 'Data bus size',
                    hidden      : false,
                    default     : device_driverlib_peripheral.EMIF_AsyncDataWidth[2].name,
                    options     : device_driverlib_peripheral.EMIF_AsyncDataWidth
                },
                /*
                {
                    name: "cs2AddrBusLSB",
                    displayName : "Address Bus LSB",
                    description : '',
                    hidden      : false,
                    default     : 0.0,
                    getValue    : (inst) => {
                        return;
                    }
                },
    
                {
                    name: "cs2AddrReach",
                    displayName : "Calculated Address Reach (Bits)",
                    description : '',
                    hidden      : false,
                    default     : 0.0,
                    getValue    : (inst) => {
                        return;
                    }
                },
    
                {
                    name: "cs2AddrWords",
                    displayName : "Calculated Address Reach (16b Words)",
                    description : '',
                    hidden      : false,
                    default     : 0.0,
                    getValue    : (inst) => {
                        return;
                    }
                },
                */
                ]
        }
    );
    if(emif_instance == "EMIF1"){
        config[14+offset].config.push({
            name: "cs2AddrMSB",
            displayName : "Address Bus MSB",
            description : 'Most significant address bit signal',
            hidden      : false,
            default     : EMIF1_ADDR_BUS_MSB_CS2[7].name,
            options     : EMIF1_ADDR_BUS_MSB_CS2
        });
        config[14+offset].config.push({
            name: "cs2SelStrobe",
            displayName : "Select Strobe",
            description : 'CS strobe in addition to WE/ & OE/ strobe',
            hidden      : false,
            default     : device_driverlib_peripheral.EMIF_AsyncMode[1].name,
            options     : device_driverlib_peripheral.EMIF_AsyncMode
        });
        config[14+offset].config.push({
            name: "cs2enableExtWait",
            displayName : "Enable Extended Wait",
            description : 'Enable Extend strobe cycles with EMnWAIT',
            hidden      : false,
            default     : true
        });
    }
    else if(emif_instance == "EMIF2"){
        config[14].config[0].onChange = onChangeCS_EMIF2;
        config[14].config.push({
            name: "cs2AddrMSB",
            displayName : "Address Bus MSB",
            description : 'Most significant address bit signal',
            hidden      : false,
            default     : EMIF2_ADDR_BUS_MSB_CS2[3].name,
            options     : EMIF2_ADDR_BUS_MSB_CS2
        });
        config[14].config.push({
            name: "cs2SelStrobe",
            displayName : "Select Strobe",
            description : 'CS strobe in addition to WE/ & OE/ strobe',
            hidden      : false,
            default     : device_driverlib_peripheral.EMIF_AsyncMode[1].name,
            options     : device_driverlib_peripheral.EMIF_AsyncMode
        });
        config[14].config.push({
            name: "cs2enableExtWait",
            displayName : "Enable Extended Wait",
            description : 'Enable Extend strobe cycles with EMnWAIT',
            hidden      : false,
            default     : true
        });
        config[14].config[9].default = device_driverlib_peripheral.EMIF_AsyncDataWidth[1].name
    }
    if(emif_instance == "EMIF1"){
        config.push(
        //CS3
        {
            name: "cs3Config",
            displayName: "EMIF CS3 Interface",
            description: 'Configure EMIF CS3 Interface',
            collapsed: true,
            config: [
                {
                    name: "enableCS3",
                    displayName : "Enable CS3 ASYNC",
                    description : 'Enable EMIF CS3 Interface',
                    hidden      : false,
                    default     : true,
                    onChange    : onChangeCS_EMIF1,
                },
                {
                    name: "cs3WriteSetup",
                    displayName : "Write Setup (cycles)",
                    description : 'Address setup before strobe signal is asserted',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs3WriteStrobe",
                    displayName : "Write Strobe (cycles)",
                    description : 'Duration that strobe signal is asserted',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs3WriteHold",
                    displayName : "Write Hold (cycles)",
                    description : 'Address and Data hold after strobe signal is deasserted',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs3ReadSetup",
                    displayName : "Read Setup (cycles)",
                    description : 'Address setup before strobe signal is asserted',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs3ReadStrobe",
                    displayName : "Read Strobe (cycles)",
                    description : 'Duration that strobe signal is asserted',
                    hidden      : false,
                    default     : 4
                },
                {
                    name: "cs3ReadHold",
                    displayName : "Read Hold (cycles)",
                    description : 'Data hold after strobe signal is deasserted',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs3TurnAround",
                    displayName : "Turn Around (cycles)",
                    description : 'Delay from Read to Write, or Write to Read',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs3Timings",
                    collapsed: false,
                    //hidden: false,
                    config: [
                        {
                            name: "cs3secWriteSetup",
                            displayName : "Calculated Write Setup (ns)",
                            description : 'Address setup before strobe signal is asserted',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs3WriteSetup * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs3secWriteStrobe",
                            displayName : "Calculated Write Strobe (ns)",
                            description : 'Duration that strobe signal is asserted',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs3WriteStrobe * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs3secWriteHold",
                            displayName : "Calculated Write Hold (ns)",
                            description : 'Address and Data hold after strobe signal is deasserted',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs3WriteHold * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs3WriteOp",
                            displayName : "Calculated Write Operation (ns)",
                            description : 'Minimum time to write one word',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs3secWriteSetup + inst.cs3secWriteStrobe + inst.cs3secWriteHold).toFixed(3));
                            }
                        },
                        {
                            name: "cs3secReadSetup",
                            displayName : "Calculated Read Setup (ns)",
                            description : 'Address setup before strobe signal is asserted',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs3ReadSetup * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs3secReadStrobe",
                            displayName : "Calculated Read Strobe (ns)",
                            description : 'Duration that strobe signal is asserted',
                            hidden      : false,
                            default     : 4,
                            getValue    : (inst) => {
                                return Number((inst.cs3ReadStrobe * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs3secReadHold",
                            displayName : "Calculated Read Hold (ns)",
                            description : 'Data hold after strobe signal is deasserted',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs3ReadHold * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs3ReadOp",
                            displayName : "Calculated Read Operation (ns)",
                            description : 'Minimum time to read one word',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs3secReadSetup + inst.cs3secReadStrobe + inst.cs3secReadHold).toFixed(3));
                            }
                        },
                        {
                            name: "cs3secTurnAround",
                            displayName : "Calculated Turn Around (ns)",
                            description : 'Delay from Read to Write, or Write to Read',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs3TurnAround * inst.clkCycle).toFixed(3));
                            }
                        },
                    ]
                },
                {
                    name: "cs3WordSize",
                    displayName : "Word Size",
                    description : 'Data bus size',
                    hidden      : false,
                    default     : device_driverlib_peripheral.EMIF_AsyncDataWidth[2].name,
                    options     : device_driverlib_peripheral.EMIF_AsyncDataWidth
                },
                {
                    name: "cs3AddrMSB",
                    displayName : "Address Bus MSB",
                    description : 'Most significant address bit signal',
                    hidden      : false,
                    default     : EMIF1_ADDR_BUS_MSB_CS2[2].name,
                    options     : EMIF1_ADDR_BUS_MSB_CS2
                },
                /*
                {
                    name: "cs3AddrBusLSB",
                    displayName : "Address Bus LSB",
                    description : '',
                    hidden      : false,
                    default     : 0.0,
                    getValue    : (inst) => {
                        return;
                    }
                },
    
                {
                    name: "cs3AddrReach",
                    displayName : "Calculated Address Reach (Bits)",
                    description : '',
                    hidden      : false,
                    default     : 0.0,
                    getValue    : (inst) => {
                        return;
                    }
                },
    
                {
                    name: "cs3AddrWords",
                    displayName : "Calculated Address Reach (16b Words)",
                    description : '',
                    hidden      : false,
                    default     : 0.0,
                    getValue    : (inst) => {
                        return;
                    }
                },
                */
                {
                    name: "cs3SelStrobe",
                    displayName : "Select Strobe",
                    description : 'CS strobe in addition to WE/ & OE/ strobe',
                    hidden      : false,
                    default     : device_driverlib_peripheral.EMIF_AsyncMode[1].name,
                    options     : device_driverlib_peripheral.EMIF_AsyncMode
                },
                {
                    name: "cs3enableExtWait",
                    displayName : "Enable Extended Wait",
                    description : 'Enable Extend strobe cycles with EMnWAIT',
                    hidden      : false,
                    default     : true
                },
            ]
        },
        //CS4
        {
            name: "cs4Config",
            displayName: "EMIF CS4 Interface",
            description: 'Configure EMIF CS4 Interface',
            collapsed: true,
            config: [
                {
                    name: "enableCS4",
                    displayName : "Enable CS4 ASYNC",
                    description : 'Enable EMIF CS4 Interface',
                    hidden      : false,
                    default     : true,
                    onChange    : onChangeCS_EMIF1,
                },
                {
                    name: "cs4WriteSetup",
                    displayName : "Write Setup (cycles)",
                    description : 'Address setup before strobe signal is asserted',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs4WriteStrobe",
                    displayName : "Write Strobe (cycles)",
                    description : 'Duration that strobe signal is asserted',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs4WriteHold",
                    displayName : "Write Hold (cycles)",
                    description : 'Address and Data hold after strobe signal is deasserted',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs4ReadSetup",
                    displayName : "Read Setup (cycles)",
                    description : 'Address setup before strobe signal is asserted',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs4ReadStrobe",
                    displayName : "Read Strobe (cycles)",
                    description : 'Duration that strobe signal is asserted',
                    hidden      : false,
                    default     : 4
                },
                {
                    name: "cs4ReadHold",
                    displayName : "Read Hold (cycles)",
                    description : 'Data hold after strobe signal is deasserted',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs4TurnAround",
                    displayName : "Turn Around (cycles)",
                    description : 'Delay from Read to Write, or Write to Read',
                    hidden      : false,
                    default     : 1
                },
                {
                    name: "cs4Timings",
                    collapsed: false,
                    //hidden: false,
                    config: [
                        {
                            name: "cs4secWriteSetup",
                            displayName : "Calculated Write Setup (ns)",
                            description : 'Address setup before strobe signal is asserted',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs4WriteSetup * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs4secWriteStrobe",
                            displayName : "Calculated Write Strobe (ns)",
                            description : 'Duration that strobe signal is asserted',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs4WriteStrobe * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs4secWriteHold",
                            displayName : "Calculated Write Hold (ns)",
                            description : 'Address and Data hold after strobe signal is deasserted',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs4WriteHold * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs4WriteOp",
                            displayName : "Calculated Write Operation (ns)",
                            description : 'Minimum time to write one word',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs4secWriteSetup + inst.cs4secWriteStrobe + inst.cs4secWriteHold).toFixed(3));
                            }
                        },
                        {
                            name: "cs4secReadSetup",
                            displayName : "Calculated Read Setup (ns)",
                            description : 'Address setup before strobe signal is asserted',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs4ReadSetup * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs4secReadStrobe",
                            displayName : "Calculated Read Strobe (ns)",
                            description : 'Duration that strobe signal is asserted',
                            hidden      : false,
                            default     : 4,
                            getValue    : (inst) => {
                                return Number((inst.cs4ReadStrobe * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs4secReadHold",
                            displayName : "Calculated Read Hold (ns)",
                            description : 'Data hold after strobe signal is deasserted',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs4ReadHold * inst.clkCycle).toFixed(3));
                            }
                        },
                        {
                            name: "cs4ReadOp",
                            displayName : "Calculated Read Operation (ns)",
                            description : 'Minimum time to read one word',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs4secReadSetup + inst.cs4secReadStrobe + inst.cs4secReadHold).toFixed(3));
                            }
                        },
                        {
                            name: "cs4secTurnAround",
                            displayName : "Calculated Turn Around (ns)",
                            description : 'Delay from Read to Write, or Write to Read',
                            hidden      : false,
                            default     : 1,
                            getValue    : (inst) => {
                                return Number((inst.cs4TurnAround * inst.clkCycle).toFixed(3));
                            }
                        },
                    ]
                },
                {
                    name: "cs4WordSize",
                    displayName : "Word Size",
                    description : 'Data bus size',
                    hidden      : false,
                    default     : device_driverlib_peripheral.EMIF_AsyncDataWidth[2].name,
                    options     : device_driverlib_peripheral.EMIF_AsyncDataWidth
                },
                {
                    name: "cs4AddrMSB",
                    displayName : "Address Bus MSB",
                    description : 'Most significant address bit signal',
                    hidden      : false,
                    default     : EMIF1_ADDR_BUS_MSB_CS2[4].name,
                    options     : EMIF1_ADDR_BUS_MSB_CS2
                },
                /*
                {
                    name: "cs4AddrBusLSB",
                    displayName : "Address Bus LSB",
                    description : '',
                    hidden      : false,
                    default     : 0.0,
                    getValue    : (inst) => {
                        return;
                    }
                },
    
                {
                    name: "cs4AddrReach",
                    displayName : "Calculated Address Reach (Bits)",
                    description : '',
                    hidden      : false,
                    default     : 0.0,
                    getValue    : (inst) => {
                        return;
                    }
                },
    
                {
                    name: "cs4AddrWords",
                    displayName : "Calculated Address Reach (16b Words)",
                    description : '',
                    hidden      : false,
                    default     : 0.0,
                    getValue    : (inst) => {
                        return;
                    }
                },
                */
                {
                    name: "cs4SelStrobe",
                    displayName : "Select Strobe",
                    description : 'CS strobe in addition to WE/ & OE/ strobe',
                    hidden      : false,
                    default     : device_driverlib_peripheral.EMIF_AsyncMode[1].name,
                    options     : device_driverlib_peripheral.EMIF_AsyncMode
                },
                {
                    name: "cs4enableExtWait",
                    displayName : "Enable Extended Wait",
                    description : 'Enable Extend strobe cycles with EMnWAIT',
                    hidden      : false,
                    default     : true
                },
            ]
        });
    }
    if(emif_instance == "EMIF1"){
        config.push({
            name: "useCase",
            displayName : "Pinmux Use Case",
            description : 'Peripheral use case',
            hidden      : false,
            default     : 'ALL',
            options     : Pinmux.getPeripheralUseCaseNames("EMIF1"),
            onChange    : Pinmux.useCaseChanged,
        });
    }
    else if(emif_instance == "EMIF2"){
        config.push({
            name: "useCase",
            displayName : "Pinmux Use Case",
            description : 'Peripheral use case',
            hidden      : false,
            default     : 'ALL',
            options     : Pinmux.getPeripheralUseCaseNames("EMIF2"),
            onChange    : Pinmux.useCaseChanged,
        });
    }
    offset = 0;
    return config;
}
/* Array of CAN configurables that are common across device families */

var globalConfig = [
    
    {
        name: "emifSYSCLK",
        displayName: "SYSCLK [MHz] for EMIF Clk Speed",
        description: "This is the SYSCLK value assumed for EMIF1 Clk Speed calculation",
        default: Emif_SysClk_MHz
    }
]

function onValidate(inst, validation) {
    var emif_instance = inst.$module.peripheralName;
    var validationIdeal = {};
    //initializing CS dictionaries as empty arrays to fix issue of 'undefined' variables populating when a CS is not turned on
    validationIdeal["CS0"] = [];
    validationIdeal["CS2"] = [];
    validationIdeal["CS3"] = [];
    validationIdeal["CS4"] = [];
    var prefix;
    //determining 'prefix' value that goes ahead of every signal for both F2837xD and F2838x and EMIF1/2
    if(["F2837xD", "F2837xS"].includes(Common.getDeviceName())){
        emif_instance == "EMIF1" ? (prefix = "EM1") : (prefix = "EM2")
    }
    else{
        emif_instance == "EMIF1" ? (prefix = "EMIF1_") : (prefix = "EMIF2_")
    }
    //creating a 'golden' view of correct pin signals during runtime based on the settings enabled by the user
    if(inst.enableCS0){
        let CS0BusSize = inst.cs0Narrow;
        validationIdeal["CS0"] = [prefix + "RAS", prefix + "SDCKE", prefix + "WEn", prefix + "CAS", prefix + "CLK", prefix + "CS0n", prefix + "A0", prefix + "A1", prefix + "A2", prefix + "A3", prefix + "A4", prefix + "A5", prefix + "A6", prefix + "A7", prefix + "A10"];
        let CS0MSB = inst.cs0AddrMSB;
        var MSB;
        if(emif_instance == "EMIF1"){
            MSB = CS0MSB.replace("EM1A", "");
        }
        else{
            MSB = CS0MSB.replace("EM2A", "");
        }
        let tempValid = [prefix + "DQM1", prefix + "DQM0", prefix + "D0", prefix + "D1", prefix + "D2", prefix + "D3", prefix + "D4", prefix + "D5", prefix + "D6", prefix + "D7", prefix + "D8", prefix + "D9", prefix + "D10", prefix + "D11", prefix + "D12", prefix + "D13", prefix + "D14", prefix + "D15"];
        MSB = parseInt(MSB);
        var additional_tempValid = [];
        if(CS0BusSize == "EMIF_SYNC_NARROW_MODE_FALSE"){
            additional_tempValid = [prefix + "D16", prefix + "D17", prefix + "D18", prefix + "D19", prefix + "D20", prefix + "D21", prefix + "D22", prefix + "D23", prefix + "D24", prefix + "D25", prefix + "D26", prefix + "D27", prefix + "D28", prefix + "D29", prefix + "D30", prefix + "D31"];
            tempValid.unshift(prefix + "DQM2");
            tempValid.unshift(prefix + "DQM3");
        }
        let cs0BankNum = inst.cs0Banks;
        cs0BankNum = cs0BankNum.replace("EMIF_SYNC_BANK_", "");
        if(cs0BankNum == "2"){validationIdeal["CS2"].unshift(prefix + "BA0");}
        else if(cs0BankNum == "4"){
            validationIdeal["CS0"].unshift(prefix + "BA0");
            validationIdeal["CS0"].unshift(prefix + "BA1");
        }
        tempValid = tempValid.concat(additional_tempValid);
        while(MSB > 7){
            let MSBSignal = prefix + "A" + MSB.toString();
            tempValid.unshift(MSBSignal);
            MSB--;
        }
        validationIdeal["CS0"] = validationIdeal["CS0"].concat(tempValid);
    }
    if(inst.enableCS2){
        validationIdeal["CS2"] = [prefix + "OEn", prefix + "WEn", prefix + "CS2n"];
        let CS2MSB = inst.cs2AddrMSB;
        let CS2BusSize = inst.cs2WordSize;
        var MSB;
        if(emif_instance == "EMIF1"){
            MSB = CS2MSB.replace("EM1", "");
        }
        else{
            MSB = CS2MSB.replace("EM2", "");
        }
        let LSB;
        let BusSize = CS2BusSize.replace("EMIF_ASYNC_DATA_WIDTH_", "");
        let tempValid = [prefix + "D0", prefix + "D1", prefix + "D2", prefix + "D3", prefix + "D4", prefix + "D5", prefix + "D6", prefix + "D7"]
        var additional_tempValid = [];
        let waitCheck = inst.cs2enableExtWait;
        if(waitCheck){tempValid.unshift(prefix + "WAIT")}
        if (BusSize == "16"){
            additional_tempValid = [prefix + "D8", prefix + "D9", prefix + "D10", prefix + "D11", prefix + "D12", prefix + "D13", prefix + "D14", prefix + "D15"];
        }
        else if(BusSize == "32"){
            additional_tempValid = [prefix + "D8", prefix + "D9", prefix + "D10", prefix + "D11", prefix + "D12", prefix + "D13", prefix + "D14", prefix + "D15", prefix + "D16", prefix + "D17", prefix + "D18", prefix + "D19", prefix + "D20", prefix + "D21", prefix + "D22", prefix + "D23", prefix + "D24", prefix + "D25", prefix + "D26", prefix + "D27", prefix + "D28", prefix + "D29", prefix + "D30", prefix + "D31"];
            tempValid.unshift(prefix + "DQM1");
            tempValid.unshift(prefix + "DQM2");
        }
        tempValid = tempValid.concat(additional_tempValid);
        if(MSB == "BA0"){MSB = -2;}
        else if(MSB == "BA1"){MSB = -1;}
        else{MSB = MSB.slice(1); MSB = parseInt(MSB);}
        BusSize = parseInt(BusSize);
        let flag = 0;
        if (BusSize == "8"){
            LSB = -2;
        }
        else if (BusSize == "16"){
            LSB = -1;
        }
        else if (BusSize == "32"){
            LSB = 0;
        }
        while(MSB >= LSB){
            var MSBSignal = '';
            if(MSB == -2){MSBSignal = prefix + "BA0";}
            else if(MSB == -1){MSBSignal = prefix + "BA1";}
            else{MSBSignal = prefix + "A" + MSB.toString();}
            tempValid.unshift(MSBSignal);
            MSB--;
        }
        validationIdeal["CS2"] = validationIdeal["CS2"].concat(tempValid);
    }
    validationIdeal["Combined"] = [];
    validationIdeal["Combined"] = validationIdeal["Combined"].concat(validationIdeal["CS0"]);
    validationIdeal["Combined"] = validationIdeal["Combined"].concat(validationIdeal["CS2"]);
    if(emif_instance == "EMIF1"){
        if(inst.enableCS3){
            validationIdeal["CS3"] = [prefix + "OEn", prefix + "WEn", prefix + "CS3n"];
            let CS3MSB = inst.cs3AddrMSB;
            let CS3BusSize = inst.cs3WordSize;
            var MSB;
            if(emif_instance == "EMIF1"){
                MSB = CS3MSB.replace("EM1", "");
            }
            else{
                MSB = CS3MSB.replace("EM2", "");
            }
            let LSB;
            let BusSize = CS3BusSize.replace("EMIF_ASYNC_DATA_WIDTH_", "");
            let tempValid = [prefix + "D0", prefix + "D1", prefix + "D2", prefix + "D3", prefix + "D4", prefix + "D5", prefix + "D6", prefix + "D7"]
            var additional_tempValid = [];
            let waitCheck = inst.cs3enableExtWait;
            if(waitCheck){tempValid.unshift(prefix + "WAIT")}
            if (BusSize == "16"){
                additional_tempValid = [prefix + "D8", prefix + "D9", prefix + "D10", prefix + "D11", prefix + "D12", prefix + "D13", prefix + "D14", prefix + "D15"];
            }
            else if(BusSize == "32"){
                additional_tempValid = [prefix + "D8", prefix + "D9", prefix + "D10", prefix + "D11", prefix + "D12", prefix + "D13", prefix + "D14", prefix + "D15", prefix + "D16", prefix + "D17", prefix + "D18", prefix + "D19", prefix + "D20", prefix + "D21", prefix + "D22", prefix + "D23", prefix + "D24", prefix + "D25", prefix + "D26", prefix + "D27", prefix + "D28", prefix + "D29", prefix + "D30", prefix + "D31"];
                tempValid.unshift(prefix + "DQM1");
                tempValid.unshift(prefix + "DQM2");
            }
            tempValid = tempValid.concat(additional_tempValid);
            if(MSB == "BA0"){MSB = -2;}
            else if(MSB == "BA1"){MSB = -1;}
            else{MSB = MSB.slice(1); MSB = parseInt(MSB);}
            BusSize = parseInt(BusSize);
            let flag = 0;
            if (BusSize == "8"){
                LSB = -2;
            }
            else if (BusSize == "16"){
                LSB = -1;
            }
            else if (BusSize == "32"){
                LSB = 0;
            }
            while(MSB >= LSB){
                var MSBSignal = '';
                if(MSB == -2){MSBSignal = prefix + "BA0";}
                else if(MSB == -1){MSBSignal = prefix + "BA1";}
                else{MSBSignal = prefix + "A" + MSB.toString();}
                tempValid.unshift(MSBSignal);
                MSB--;
            }
            validationIdeal["CS3"] = validationIdeal["CS3"].concat(tempValid);
        }
        if(inst.enableCS4){
            validationIdeal["CS4"] = [prefix + "OEn", prefix + "WEn", prefix + "CS4n"];
            let CS4MSB = inst.cs4AddrMSB;
            let CS4BusSize = inst.cs4WordSize;
            var MSB;
            if(emif_instance == "EMIF1"){
                MSB = CS4MSB.replace("EM1A", "");
            }
            else{
                MSB = CS4MSB.replace("EM2A", "");
            }
            let LSB;
            let BusSize = CS4BusSize.replace("EMIF_ASYNC_DATA_WIDTH_", "");
            let tempValid = [prefix + "D0", prefix + "D1", prefix + "D2", prefix + "D3", prefix + "D4", prefix + "D5", prefix + "D6", prefix + "D7"]
            var additional_tempValid = [];
            let waitCheck = inst.cs4enableExtWait;
            if(waitCheck){tempValid.unshift(prefix + "WAIT")}
            if (BusSize == "16"){
                additional_tempValid = [prefix + "D8", prefix + "D9", prefix + "D10", prefix + "D11", prefix + "D12", prefix + "D13", prefix + "D14", prefix + "D15"];
            }
            else if(BusSize == "32"){
                additional_tempValid = [prefix + "D8", prefix + "D9", prefix + "D10", prefix + "D11", prefix + "D12", prefix + "D13", prefix + "D14", prefix + "D15", prefix + "D16", prefix + "D17", prefix + "D18", prefix + "D19", prefix + "D20", prefix + "D21", prefix + "D22", prefix + "D23", prefix + "D24", prefix + "D25", prefix + "D26", prefix + "D27", prefix + "D28", prefix + "D29", prefix + "D30", prefix + "D31"];
                tempValid.unshift(prefix + "DQM1");
                tempValid.unshift(prefix + "DQM2");
            }
            tempValid = tempValid.concat(additional_tempValid);
            if(MSB == "BA0"){MSB = -2;}
            else if(MSB == "BA1"){MSB = -1;}
            else{MSB = MSB.slice(1); MSB = parseInt(MSB);}
            BusSize = parseInt(BusSize);
            let flag = 0;
            if (BusSize == "8"){
                LSB = -2;
            }
            else if (BusSize == "16"){
                LSB = -1;
            }
            else if (BusSize == "32"){
                LSB = 0;
            }
            while(MSB >= LSB){
                var MSBSignal = '';
                if(MSB == -2){MSBSignal = prefix + "BA0";}
                else if(MSB == -1){MSBSignal = prefix + "BA1";}
                else{MSBSignal = prefix + "A" + MSB.toString();}
                tempValid.unshift(MSBSignal);
                MSB--;
            }
            validationIdeal["CS4"] = validationIdeal["CS4"].concat(tempValid);
        }
        validationIdeal["Combined"] = validationIdeal["Combined"].concat(validationIdeal["CS3"]);
        validationIdeal["Combined"] = validationIdeal["Combined"].concat(validationIdeal["CS4"]);
    }
    //Signals required by each chip select are merged into one 'Combined' array and then sorted so as to deal with repeated values
    validationIdeal["Combined"].sort();
    let prev = "";
    var caseCheck;
    var errorLog = "useInterfacePins";
    //getting the enabled pins for each useCase
    caseCheck = Pinmux.getPeripheralUseCaseInterfaces(inst, emif_instance, inst.useCase);
    //setup for extraneous pin checks
    let extraneousCheck = _.clone(caseCheck);
    let extraneousValidity = new Array(extraneousCheck.length).fill(false);
    if(inst.useCase != "CUSTOM"){
        errorLog = "useCase";
    }
    for(let i = 0; i < validationIdeal["Combined"].length; i++){
        let signal = validationIdeal["Combined"][i];
        if(signal == prev){
            validationIdeal["Combined"].splice(i,1)
            i--;
            continue;
        }
        let index = caseCheck.indexOf(signal);
        if(index == -1){
            validation.logError("Missing required pin signal: " + signal, inst, errorLog);
        }
        else{
            extraneousValidity[index] = true;
        }
        prev = signal;
    }
    for(let i = 0; i < extraneousValidity.length; i++){
        if(extraneousValidity[i] == false){
            validation.logInfo("Non-required pin enabled: " + extraneousCheck[i], inst, errorLog);
        }
    }
    if (inst.enableCS0 && (inst.clkSpeed > 100)){
        validation.logError(
            "Configure a Clk Speed less than 100 MHz when enabling CS0",
            inst, "clkSpeed");
    }


    if (inst.maxWait < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "maxWait");
    }

    if (inst.cs0tRFC < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "cs0tRFC");
    }

    if (inst.cs0tRP < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "cs0tRP");
    }

    if (inst.cs0tRCD < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "cs0tRCD");
    }

    if (inst.cs0tWR < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "cs0tWR");
    }

    if (inst.cs0tRAS < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "cs0tRAS");
    }

    if (inst.cs0tRC < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "cs0tRC");
    }

    if (inst.cs0tRRD < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "cs0tRRD");
    }

    if (inst.cs0tXSR < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "cs0tXSR");
    }

    if (inst.cs2WriteSetup < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "cs2WriteSetup");
    }

    if (inst.cs2WriteStrobe < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "cs2WriteStrobe");
    }

    if (inst.cs2WriteHold < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "cs2WriteHold");
    }

    if (inst.cs2ReadSetup < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "cs2ReadSetup");
    }

    if (inst.cs2ReadStrobe < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "cs2ReadStrobe");
    }

    if (inst.cs2ReadHold < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "cs2ReadHold");
    }

    if (inst.cs2TurnAround < 1 ){
        validation.logError(
            "Enter a value greater than 1", 
            inst, "cs2TurnAround");
    }
    if(emif_instance == "EMIF1"){
        if (inst.cs3WriteSetup < 1 ){
            validation.logError(
                "Enter a value greater than 1", 
                inst, "cs3WriteSetup");
        }

        if (inst.cs3WriteStrobe < 1 ){
            validation.logError(
                "Enter a value greater than 1", 
                inst, "cs3WriteStrobe");
        }

        if (inst.cs3WriteHold < 1 ){
            validation.logError(
                "Enter a value greater than 1", 
                inst, "cs3WriteHold");
        }

        if (inst.cs3ReadSetup < 1 ){
            validation.logError(
                "Enter a value greater than 1", 
                inst, "cs3ReadSetup");
        }

        if (inst.cs3ReadStrobe < 1 ){
            validation.logError(
                "Enter a value greater than 1", 
                inst, "cs3ReadStrobe");
        }

        if (inst.cs3ReadHold < 1 ){
            validation.logError(
                "Enter a value greater than 1", 
                inst, "cs3ReadHold");
        }

        if (inst.cs3TurnAround < 1 ){
            validation.logError(
                "Enter a value greater than 1", 
                inst, "cs3TurnAround");
        }

        if (inst.cs4WriteSetup < 1 ){
            validation.logError(
                "Enter a value greater than 1", 
                inst, "cs4WriteSetup");
        }

        if (inst.cs4WriteStrobe < 1 ){
            validation.logError(
                "Enter a value greater than 1", 
                inst, "cs4WriteStrobe");
        }

        if (inst.cs4WriteHold < 1 ){
            validation.logError(
                "Enter a value greater than 1", 
                inst, "cs4WriteHold");
        }

        if (inst.cs4ReadSetup < 1 ){
            validation.logError(
                "Enter a value greater than 1", 
                inst, "cs4ReadSetup");
        }

        if (inst.cs4ReadStrobe < 1 ){
            validation.logError(
                "Enter a value greater than 1", 
                inst, "cs4ReadStrobe");
        }

        if (inst.cs4ReadHold < 1 ){
            validation.logError(
                "Enter a value greater than 1", 
                inst, "cs4ReadHold");
        }

        if (inst.cs4TurnAround < 1 ){
            validation.logError(
                "Enter a value greater than 1", 
                inst, "cs4TurnAround");
        }
    }
    else{
        if(inst.cs2WordSize == "EMIF_ASYNC_DATA_WIDTH_32"){
            validation.logError(
                "EMIF2 does not support a data bus size greater than 16 bits, 32 bit data bus is not allowed",
                inst, "cs2WordSize");
        }
    }
}

function onValidateStatic(inst, validation){
    if (inst.emifSYSCLK < 1 || inst.emifSYSCLK > 200 ){
        validation.logError(
            "Enter a value from 1 to 200 MHz", 
            inst, "emifSYSCLK");
    }
}

var sharedModuleInstances = undefined;

if(Common.getDeviceName().toLowerCase() == 'f2838x')
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


var emif_shared = {
    getEMIFConfig : getEMIFConfig,
    globalConfig : globalConfig,
    onValidateStatic : onValidateStatic,
    onValidate: onValidate,
};

exports = emif_shared;
