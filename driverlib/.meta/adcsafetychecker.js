let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_adc.js");
let device_driverlib_memmap =
system.getScript("/driverlib/device_driverlib_peripherals/" +
    Common.getDeviceName().toLowerCase() + "_memmap.js");

//var numberOfBusCompInstance = {
//    "F29H85x"   : 8
//}

let config = [
    {
        name: "GROUP_SAFECHECKCFG",
        displayName: "ADC Safety Checker Configuration",
        collapsed: false,
        config: []
    },
];

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["ADC"]));
}

function moduleInstances(inst)
{
    let components = new Array();

    components.push(
        {
            name: "adc_safetycheckertile",
            group: "GROUP_SAFECHECKCFG",
            displayName: "Safety Checker Tile",
            moduleName: "/driverlib/adc/modules/adcsafetycheckertile.js",
            useArray: true,
            collapsed: true,
            //maxInstances: maxInstances,
        }
    )

    components.push(
        {
            name: "adc_safetycheckeraggr",
            group: "GROUP_SAFECHECKCFG",
            displayName: "Safety Checker Interrupt/Event Configuration",
            moduleName: "/driverlib/adc/modules/adcsafetycheckeraggr.js",
            useArray: true,
            collapsed: true,
            //maxInstances: maxInstances,
        }
    )

    return components;
}

var adcSCModule = {
    peripheralName: "ADCSafetyChecker",
    displayName: "ADC SAFETY CHECKER",
    defaultInstanceName: "myADCSAFETYCHECK",
    description: "ADC Safety Checker Module",
    // longDescription: (Common.getCollateralFindabilityList("ERAD")),
    filterHardware : filterHardware,
    moduleStatic          : {
        config          : config,
        moduleInstances : moduleInstances,
    },
    templates: {
        boardc : "/driverlib/adc/adcsc.board.c.xdt",
        boardh : "/driverlib/adc/adcsc.board.h.xdt"
    },
};


exports = adcSCModule;