let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

/* Intro splash on GUI */
let longDescription = "An FSI peripheral is used to translate data between " +
    "the chip and a serial port. The SCI driver simplifies reading " +
    "and writing to any of the UART peripherals on the board, with " +
    "multiple modes of operation and performance. These include " +
    "blocking, non-blocking, and polling, as well as text/binary " +
    "mode, echo and return characters.";
    
let device_sysctl_nets =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_sysctl.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_emif.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

let emif_shared =
    system.getScript("/driverlib/emif.js");

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
    return (Common.typeMatches(component.type, ["EMIF1"]));
}
var globalConfig = _.clone(emif_shared.globalConfig)

function onChangeCS (inst,ui) {
    var csConfigs = ["WriteSetup","WriteStrobe","WriteHold","ReadSetup","ReadStrobe","ReadHold","TurnAround","secWriteSetup","secWriteStrobe","secWriteHold","secReadSetup","secReadStrobe","secReadHold","WriteOp","ReadOp","secTurnAround","SelStrobe","WordSize","AddrMSB","enableExtWait"];
    for (var cs = 2; cs <= 4; cs++){
        for (var csConfig of csConfigs){
            ui["cs" + cs.toString() + csConfig].hidden = !inst["enableCS" + cs.toString()];
        }
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

var emif1Module = {
    peripheralName: "EMIF1",
    displayName: "EMIF1",
    maxInstances: Common.peripheralCount("EMIF1"),
    defaultInstanceName: "myEMIF1",
    description: "External Memory Interface Peripheral 1 Peripheral",
    longDescription: (Common.getCollateralFindabilityList("EMIF")),
    filterHardware : filterHardware,
    config: emif_shared.getEMIFConfig("EMIF1"),
    moduleInstances: (inst) => {
        var ownedInstances = []
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("EMIF1", inst)
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
        boardc : "/driverlib/emif1/emif1.board.c.xdt",
        boardh : "/driverlib/emif1/emif1.board.h.xdt"
    },
    moduleStatic: {
        name: "emif1Global",
        displayName: "EMIF1 Global",
        config: globalConfig,
        //modules: moduleStaticModules,
        validate : emif_shared.onValidateStatic
    },
    validate: emif_shared.onValidate,
    pinmuxRequirements    : Pinmux.emif1PinmuxRequirements
};

if (emif1Module.maxInstances <= 0)
{
    delete emif1Module.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(emif1Module)
    Pinmux.addPinMuxQualGroupToConfig(emif1Module)
}

exports = emif1Module;