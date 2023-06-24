let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_emif.js");

let device_sysctl_nets =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_sysctl.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

let emif_shared =
    system.getScript("/driverlib/emif.js");

var config = emif_shared.getEMIFConfig("EMIF2");
var globalConfig = _.clone(emif_shared.globalConfig);

function onChangeCS (inst,ui) {
    var csConfigs = ["WriteSetup","WriteStrobe","WriteHold","ReadSetup","ReadStrobe","ReadHold","TurnAround","secWriteSetup","secWriteStrobe","secWriteHold","secReadSetup","secReadStrobe","secReadHold","WriteOp","ReadOp","secTurnAround","SelStrobe","WordSize","AddrMSB","enableExtWait"];
    var cs = 2;
    for (var csConfig of csConfigs){
        ui["cs" + cs.toString() + csConfig].hidden = !inst["enableCS" + cs.toString()];
    }
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
    return (Common.typeMatches(component.type, ["EMIF2"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
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


var emif2Module = {
    peripheralName: "EMIF2",
    displayName: "EMIF2",
    maxInstances: Common.peripheralCount("EMIF2"),
    defaultInstanceName: "myEMIF2",
    description: "External Memory Interface Peripheral 2 Peripheral",
    longDescription: (Common.getCollateralFindabilityList("EMIF")),
    filterHardware : filterHardware,
    config: config,
    moduleInstances: (inst) => {
        var ownedInstances = []
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("EMIF2", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            pinmuxQualMod.requiredArgs = {
               qualMode : "GPIO_QUAL_ASYNC",
            }
        }
        ownedInstances = ownedInstances.concat(pinmuxQualMods)

        if (inst.registerInterrupts)
        {
            if(["F2837xS"].includes(Common.getDeviceName()) || ["F2837xD"].includes(Common.getDeviceName()))
            {   
                ownedInstances = ownedInstances.concat([{
                    name: "emifInt",      
                    displayName: "EMIF Error Interrupt",
                    moduleName: "/driverlib/interrupt.js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_INT",
                        int : "INT_" + inst.$name,
                        pinmuxPeripheralModule : "",
                        driverlibInt: "INT_EMIF_ERROR"
                    }
                }])
            }              
        }
    	return ownedInstances;
    },
    sharedModuleInstances: sharedModuleInstances,
    templates: {
        boardc : "/driverlib/emif2/emif2.board.c.xdt",
        boardh : "/driverlib/emif2/emif2.board.h.xdt"
    },    
    moduleStatic: {
        name: "emif2Global",
        displayName: "EMIF2 Global",
        config: globalConfig,
        //modules: moduleStaticModules,
        validate : emif_shared.onValidateStatic
    },
    validate: emif_shared.onValidate,
    pinmuxRequirements    : Pinmux.emif2PinmuxRequirements
};


if (emif2Module.maxInstances <= 0)
{
    delete emif2Module.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(emif2Module)
    Pinmux.addPinMuxQualGroupToConfig(emif2Module)
}


exports = emif2Module;