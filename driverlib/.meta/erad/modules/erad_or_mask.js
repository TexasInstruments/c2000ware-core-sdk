let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let BUSCOMPS_USED = [
    {name: "BUSCOMP1"},
    {name: "BUSCOMP2"},
    {name: "BUSCOMP3"},
    {name: "BUSCOMP4"},
    {name: "BUSCOMP5"},
    {name: "BUSCOMP6"},
    {name: "BUSCOMP7"},
    {name: "BUSCOMP8"}
]

var config = [
    {
        name        : "busComptoOR",
        displayName : "Bus Comparators used:",
        description : "Choose which bus comparators to OR",
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : BUSCOMPS_USED
    },
    {
        name        : "rtosInterrupt",
        displayName : "Generate RTOS Interrupt on Count Match",
        description : "Wether or not to generate RTOS interrupt when the COUNT matches the REF value",
        default     : false
    }
]

var eradORSubmodule = {
    displayName: "ERAD OR MASK",
    maxInstances: 4,
    defaultInstanceName: "ERAD_OR_MASK",
    description: "ERAD Or Mask",
    config: config,
    templates: {
        boardc : "", //"/gpio/gpio.board.c.xdt",
        boardh : ""//"/gpio/gpio.board.h.xdt"
    },
};

exports = eradORSubmodule;
