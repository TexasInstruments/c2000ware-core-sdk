let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let ADDRESS_INPUT_MODE = [
    {name: "MANUAL", displayName: "Manual"},
    {name: "CODE", displayName: "Variable/Function Name"}
]

let BUS_SEL_MODE = [
    {name: "ERAD_BUSCOMP_BUS_PAB", displayName: "Program Address Bus (PAB) for instruction fetches"},
    {name: "ERAD_BUSCOMP_BUS_VPC", displayName: "Program Counter (VPC) for program counter matches"},
    {name: "ERAD_BUSCOMP_BUS_DWAB", displayName: "Data Write Accesses (DWAB) for writes to memory"},
    {name: "ERAD_BUSCOMP_BUS_DRAB", displayName: "Data Read Accesses (DRAB) for read from memory"},
    {name: "ERAD_BUSCOMP_BUS_DWDB", displayName: "Data Write Data Match (DWDB)"}
]

let COMP_MODE = [
    {name: "ERAD_BUSCOMP_COMPMODE_EQ", displayName: "Use a MASK value for the address matching"},
    {name: "ERAD_BUSCOMP_COMPMODE_GT", displayName: "Address is greater than reference address"},
    {name: "ERAD_BUSCOMP_COMPMODE_GE", displayName: "Address is greater than or equal to reference address"},
    {name: "ERAD_BUSCOMP_COMPMODE_LT", displayName: "Address is less than reference address"},
    {name: "ERAD_BUSCOMP_COMPMODE_LE", displayName: "Address is less than or equal reference address"}
]

function onChangeAddressInputMode(inst, ui)
{
    ui.hwbpRefCodeName.hidden = (inst.hwbpAddressInputMode == ADDRESS_INPUT_MODE[0].name)
    ui.hwbpRef.hidden = !(inst.hwbpAddressInputMode == ADDRESS_INPUT_MODE[0].name)
    ui.hwbpMask.hidden = !((inst.hwbpCompMode == COMP_MODE[0].name) &&
                            (!ui.hwbpCompMode.hidden))
}

var config = [
    {
        name: "hwbpBusSel",
        displayName : "Address Monitoring Type",
        description : 'Type of address monitoring for the HWBP.',
        hidden      : false,
        default     : BUS_SEL_MODE[1].name,
        options     : BUS_SEL_MODE,
        onChange    : onChangeAddressInputMode
    },
    {
        name: "hwbpAddressInputMode",
        displayName : "Address Input Type",
        description : 'Type of address input.',
        hidden      : false,
        default     : ADDRESS_INPUT_MODE[0].name,
        options     : ADDRESS_INPUT_MODE,
        onChange    : onChangeAddressInputMode
    },
    {
        name: "hwbpRefCodeName",
        displayName : "Void pointer to Function/Variable",
        description : 'Address for the HWBP to monitor.',
        hidden      : true,
        default     : "",
    },
    {
        name: "hwbpCompMode",
        displayName : "Reference Address Compare Type",
        description : "Use a mask or a select a comparison type for the reference address",
        hidden      : false,
        default     : COMP_MODE[0].name,
        options     : COMP_MODE,
        onChange    : onChangeAddressInputMode

    },
    {
        name: "hwbpMask",
        displayName : "Address Mask",
        description : 'Address mask applied to the HWBP_REF address.',
        hidden      : false,
        default     : 0,
    },
    {
        name: "hwbpRef",
        displayName : "Reference Address",
        description : 'Address for the HWBP to monitor.',
        hidden      : false,
        default     : 0,
    },
    {
        name        : "haltCPU",
        displayName : "Halt CPU on Match",
        description : "Wether or not to halt the CPU when the HWBP matches the REF value",
        default     : false
    },
    {
        name        : "rtosInterrupt",
        displayName : "Generate RTOS Interrupt on Match",
        description : "Wether or not to generate RTOS interrupt when the HWBP matches the REF value",
        default     : false
    }
];
if(["F2838x", "F28002x", "F28003x", "F28P65x", "F28P55x"].includes(system.deviceData.deviceId))
{
    config.push({
        name        : "NMIInterrupt",
        displayName : "Generate NMI Interrupt on Match",
        description : "Wether or not to generate NMI interrupt when the HWBP matches the REF value",
        default     : false})
}



var eradHWBPSubmodule = {
    displayName: "ERAD HWBP",
    maxInstances: 8,
    defaultInstanceName: "ERAD_HWBP",
    description: "ERAD HWBP",
    config: config,
    templates: {
        boardc : "", //"/gpio/gpio.board.c.xdt",
        boardh : ""//"/gpio/gpio.board.h.xdt"
    },
};


exports = eradHWBPSubmodule;