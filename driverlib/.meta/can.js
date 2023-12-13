let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

/* Intro splash on GUI */
let longDescription = "CAN is a communication peripheral which is used " +
    "when there is high noise in the signal bus. It uses a differential " +
    "wire topology to reduce the common noise. This applicatoin provides " +
    "a simplified interface to configure the different parameters of the " +
    "peripheral such as bit rate, time quanta and test mode etc. ";

function onChangeUseLoopback(inst, ui)
{
    if (inst.enableLoopback) {
        ui.loopbackMode.hidden = false;
    }
    else {
        ui.loopbackMode.hidden = true;
    }
}
function onChangeUseAutoBusOn(inst, ui)
{
    if (inst.enableAutoBusOn) {
        ui.AutoBusOnTimer.hidden = false;
    }
    else {
        ui.AutoBusOnTimer.hidden = true;
    }
}
function onChangeEnableInterrupt(inst, ui)
{
    if (inst.enableInterrupt) {
        ui.registerInterrupts.hidden = false;
        ui.interruptFlags.hidden = false;
        ui.interruptLine.hidden = false;
    }
    else {
        ui.registerInterrupts.hidden = true;
        ui.interruptFlags.hidden = true;
        ui.interruptLine.hidden = true;
    }
}

var msgCountConfig = []
for (var msgCount = 1; msgCount <= 32; msgCount++)
{
    msgCountConfig.push(
        {
            name: msgCount ,
            displayName: msgCount.toString()
        }
    );
}
var SysClk_MHz = Common.SYSCLK_getMaxMHz();
var SysClk_Hz = SysClk_MHz * 1000000;
var bitTimeOptions = [];
for (var bitTime = 8; bitTime <= 25; bitTime++)
{
    bitTimeOptions.push(
        {
            name: bitTime ,
            displayName: bitTime.toString()
        }
    );
}
var tSeg1 = 0;
var tSeg2 = 0;
var sjw = 0;
var prescalerExtension = 0, prescaler = 0;
var bitTime = 8;

function calcBitTimeParam(bitRate)
{
    for (var i = 17; i >= 0; i--)
    {
        bitTime = i + 8;
        var brp = (SysClk_Hz/(bitRate*bitTime)), tProp = 2, tSync = 1, tPhase = bitTime - (tSync + tProp), phaseSeg1 = 0, phaseSeg2 = 0;
        if((tPhase / 2) <= 8)
        {
            phaseSeg2 = tPhase / 2;
        }
        else
        {
            phaseSeg2 = 8;
        }
        tSeg1 = ((tPhase - phaseSeg2) + tProp) - 1;
        tSeg2 = phaseSeg2 - 1;
        sjw = 0;
        prescalerExtension = 0; prescaler = 0;
        if(phaseSeg2 > 4)
        {
            sjw = 3;
        }
        else
        {
            sjw = tSeg2;
        }
        prescalerExtension = parseInt((brp - 1) / 64);
        prescaler = ((brp - 1) % 64);
        if(Number.isInteger(brp))
        {
            return;
        }
    }
}
function onChangeBitRate(inst, ui)
{
    SysClk_Hz = inst.sysClock*1000000;
    calcBitTimeParam(inst.bitRate);
    inst.bitTime = bitTime;
    inst.bitRatePrescalerExtension = prescalerExtension;
    inst.bitRatePrescaler = prescaler;
    inst.bitTimeSeg1 = tSeg1;
    inst.bitTimeSeg2 = tSeg2;
    return;
}

calcBitTimeParam(500000);

function onChangeAutoCalc(inst, ui)
{
    if(inst.bitTimeAutoCalc)
    {
        ui.bitTime.readOnly = true;
        ui.bitTimeSeg1.readOnly = true;
        ui.bitTimeSeg2.readOnly = true;
        ui.bitRatePrescaler.readOnly = true;
        ui.bitRatePrescalerExtension.readOnly = true;
        ui.sjw.readOnly = true;
        onChangeBitRate(inst, ui);
    }
    else
    {
        ui.bitTime.readOnly = false;
        ui.bitTimeSeg1.readOnly = false;
        ui.bitTimeSeg2.readOnly = false;
        ui.bitRatePrescaler.readOnly = false;
        ui.bitRatePrescalerExtension.readOnly = false;
        ui.sjw.readOnly = false;
    }
}

let config = [
    {
        name: "GROUP_BR",
        displayName: "Bit Rate Parameters",
        config: [
        {
            name        : "sysClock",
            displayName : "Device SYSCLK MHz",
            description : 'Device System Clock Frequency',
            hidden      : false,
            default     : SysClk_MHz,
            onChange    : onChangeBitRate,
        },
        {
            name        : "bitRate",
            displayName : "Bit Rate Bps",
            description : 'CAN bus bit rate',
            hidden      : false,
            default     : "500000",
            onChange    : onChangeBitRate,
            options     :[
                {name: "1000000", displayName : "1000000"},
                {name: "800000", displayName : "800000"},
                {name: "500000", displayName : "500000"},
                {name: "250000", displayName : "250000"},
                {name: "125000", displayName : "125000"},
                {name: "100000", displayName : "100000"},
                {name: "50000", displayName : "50000"},
            ],
        },
        {
            name        : "bitTimeAutoCalc",
            displayName : "Use Calculated Values for Bit Timing Parameters",
            description : 'Use Calculated Values for Bit Timing Parameters',
            hidden      : false,
            onChange    : onChangeAutoCalc,
            default     : true,

        },
        {
            name        : "bitTime",
            displayName : "Bit Time Quanta (Tq)",
            description : 'Number of time quanta per bit',
            hidden      : false,
            default     : bitTimeOptions[bitTime-8].name,
            options     : bitTimeOptions,
            readOnly    : true,

        },
        {
            name        : "bitRatePrescalerExtension",
            displayName : "Bit Rate Prescelar Extension",
            description : 'Bit Rate Prescelar Extension',
            hidden      : false,
            default     : prescalerExtension,
            readOnly    : true,

        },
        {
            name        : "bitRatePrescaler",
            displayName : "Bit Rate Prescaler",
            description : 'Bit Rate Prescaler',
            hidden      : false,
            default     : prescaler,
            readOnly    : true,

        },
        {
            name        : "bitTimeSeg1",
            displayName : "Bit Time segment before sample point (Tq)",
            description : 'Bit Time segment before sample point (Tq)',
            hidden      : false,
            default     : tSeg1,
            readOnly    : true,

        },
        {
            name        : "bitTimeSeg2",
            displayName : "Bit Time segment after sample point (Tq)",
            description : 'Bit Time segment after sample point (Tq)',
            hidden      : false,
            default     : tSeg2,
            readOnly    : true,

        },
        {
            name        : "sjw",
            displayName : "(Re)Synchronization Jump Width (Tq)",
            description : '(Re)Synchronization Jump Width (Tq)',
            hidden      : false,
            default     : sjw,
            readOnly    : true,

        },
        ]
    },
    {
        name        : "enableLoopback",
        displayName : "Enable Loopback",
        description : 'Whether loopback mode to be enabled.',
        hidden      : false,
        onChange    : onChangeUseLoopback,
        default     : false,
    },
    {
        name        : "loopbackMode",
        displayName : "Loopback Mode",
        description : 'Which loopback mode to use if enabled.',
        hidden      : true,
        default     : "CAN_TEST_SILENT",
        options     : [
            {name: "CAN_TEST_SILENT", displayName : "Silent Mode"},
            {name: "CAN_TEST_LBACK", displayName : "Internal Loopback Mode"},
            {name: "CAN_TEST_EXL", displayName : "External Loopback Mode"},
        ],

    },
    {
        name        : "enableAutoBusOn",
        displayName : "Enable Auto-Bus-On",
        description : 'Whether auto bus on feature is to be enabled.',
        hidden      : false,
        onChange    : onChangeUseAutoBusOn,
        default     : false,
    },
    {
        name        : "AutoBusOnTimer",
        displayName : "Auto-Bus-On Timer",
        description : 'Auto-Bus-On Timer value if enabled.',
        hidden      : true,
        default     : 0,

    },
    {
        name: "GROUP_INT",
        displayName: "Interrupts",
        config: [
            {
                name        : "enableInterrupt",
                displayName : "Enable Interrupt",
                description : 'To Enable CAN Interrupts.',
                hidden      : false,
                onChange    : onChangeEnableInterrupt,
                default     : false,
            },
            {
                name        : "registerInterrupts",
                displayName : "Register Interrupt Handler",
                description : 'Whether or not to register interrupt handlers in the interrupt module.',
                hidden      : true,
                default     : false

            },
            {
                name        : "interruptFlags",
                displayName : "Enable Interrupts",
                description : 'Which Interrupts to enable.',
                hidden      : true,
                minSelections : 0,
                default     : [],
                options     : [
                    {name: "CAN_INT_ERROR", displayName : "Controller error condition "},
                    {name: "CAN_INT_STATUS", displayName : "Message transfer complete or bus error"},
                    {name: "CAN_INT_IE0", displayName : "Enable CAN line 0 Interrupts"},
                    {name: "CAN_INT_IE1", displayName : "Enable CAN line 1 Interrupts"},
                ],

            },
            {
                name        : "interruptLine",
                displayName : "Enable Global Interrupt Lines",
                description : 'Which Interrupt lines to enable.',
                hidden      : true,
                minSelections : 0,
                default     : [],
                options     : [
                    {name: "CAN_GLOBAL_INT_CANINT0", displayName : "Enable CAN Global Interrupt line 0"},
                    {name: "CAN_GLOBAL_INT_CANINT1", displayName : "Enable CAN Global Interrupt line 1"},
                ],

            },
        ]
    },
    {
        deprecated  : true,
        name        : "msgObjs",
        displayName : "Message Objects",
        description : 'Message objects need to be configured',
        hidden      : false,
        default     : 0,
        onChange    : (inst, ui) => {
            var convertedArray = []
            for (var mO = 1; mO <= inst["msgObjs"]; mO++)
            {
                convertedArray.push(mO);
            }
            inst["msgObjsUsed"] = convertedArray;
        }
    },
    {
        name        : "msgObjsUsed",
        displayName : "Message Objects used (1-32)",
        description : 'Message objects need to be configured',
        hidden      : false,
        minSelections : 0,
        default     : [],
        options     : msgCountConfig
    },
    {
        name: "useCase",
        displayName : "PinMux Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("CAN"),
        onChange    : Pinmux.useCaseChanged,
    },
    {
        name : "startModule",
        displayName : "Start CAN module in CAN_init() function",
        description : "Starts the CAN Module",
        hidden      : false,
        default     : true,
    },
];

function moduleInstances(inst,ui)
{
    let components = [];

    var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("CAN", inst)
    for (var pinmuxQualMod of pinmuxQualMods)
    {
        pinmuxQualMod.args.padConfig = "PULLUP";

        if(pinmuxQualMod.name.includes("rx"))
        {
            pinmuxQualMod.requiredArgs = {
                qualMode : "GPIO_QUAL_ASYNC",
            }
        }
        else
        {
            pinmuxQualMod.args.qualMode = "GPIO_QUAL_ASYNC";
        }
    }
    components = components.concat(pinmuxQualMods)

    for(var i in inst.msgObjsUsed)
    {
        components = components.concat([
        {
            moduleName : "/driverlib/canMsgObj.js",
            name : "msgObj"+inst.msgObjsUsed[i],
            displayName: "Message Object "+inst.msgObjsUsed[i],
            collapsed : true,
        },
        ]);
    }
    if (inst.enableInterrupt && inst.registerInterrupts)
    {
        components = components.concat([{
            name: "can0Int",
            displayName: "CAN Interrupt 0",
            moduleName: "/driverlib/interrupt.js",
            collapsed: true,
            args: {
                $name : inst.$name + "_0_INT",
                int : "INT_" + inst.$name + "_0",
                pinmuxPeripheralModule : "can",
                driverlibInt: "INT_#0"
            }
        },
        {
            name: "can1Int",
            displayName: "CAN Interrupt 1",
            moduleName: "/driverlib/interrupt.js",
            collapsed: true,
            args: {
                $name : inst.$name + "_1_INT",
                int : "INT_" + inst.$name + "_1",
                pinmuxPeripheralModule : "can",
                driverlibInt: "INT_#1"
            }
        }]);
    }
    return components;
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
    return (Common.typeMatches(component.type, ["CAN"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}


function onValidate(inst, validation) {

    if ( inst.bitRatePrescaler >= 64 || inst.bitRatePrescaler < 0)
    {
        validation.logError(
            "The Bit Rate Prescaler must be a number between 0 and 64",
            inst, "bitRatePrescaler");
    }
    if ((inst.bitRatePrescalerExtension < 0) || (inst.bitRatePrescalerExtension >= 16))
    {
        validation.logError(
            "The Bit Rate Prescaler Extension value must be a number between 0 and 16",
            inst, "bitRatePrescalerExtension");
    }
    if ( inst.bitTimeSeg1 >= 16 || inst.bitTimeSeg1 <= 0)
    {
        validation.logError(
            "The Bit Time segment before sampling must be a number between 1 and 16",
            inst, "bitTimeSeg1");
    }
    if ( inst.bitTimeSeg2 >= 8 || inst.bitTimeSeg1 < 0)
    {
        validation.logError(
            "The Bit Time segment after sampling must be a number between 0 and 8",
            inst, "bitTimeSeg2");
    }
    if ( inst.sjw >= 4 || inst.sjw < 0)
    {
        validation.logError(
            "(Re)Synchronization Jump Width must be a number between 0 and 4",
            inst, "sjw");
    }
    if ( inst.sysClock != SysClk_MHz)
    {
        validation.logWarning(
            "Sysclk Frequency is not the default value of " + String(SysClk_MHz),
            inst, "sysClock");
    }
    if((String(inst.interruptFlags).includes("CAN_INT_IE0") || String(inst.interruptFlags).includes("CAN_INT_STATUS") || String(inst.interruptFlags).includes("CAN_INT_ERROR")) && !String(inst.interruptLine).includes("CAN_GLOBAL_INT_CANINT0"))
    {
        validation.logWarning("Line 0 Interrupts Enabled but Global Line 0 Not Enabled",
            inst, "interruptLine");
    }
    if(String(inst.interruptFlags).includes("CAN_INT_IE1") && !String(inst.interruptLine).includes("CAN_GLOBAL_INT_CANINT1"))
    {
        validation.logWarning("Line 1 Interrupt Enabled but Global Line 1 Not Enabled",
            inst, "interruptLine");
    }
    
    var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("CAN", inst)
    for (var pinmuxQualMod of pinmuxQualMods)
    {
        if ((inst[pinmuxQualMod.name].padConfig.includes("OD")) || (inst[pinmuxQualMod.name].padConfig.includes("INVERT")))
        {
            validation.logError("The open-drain and inverted pad configurations should not be used for the CAN module.", inst);
        }
    }
}

var canModule = {
    peripheralName: "CAN",
    displayName: "CAN",
    maxInstances: Common.peripheralCount("CAN"),
    defaultInstanceName: "myCAN",
    description: "Controller Area Network Peripheral",
    longDescription: (Common.getCollateralFindabilityList("DCAN")),
    filterHardware : filterHardware,
    moduleInstances : moduleInstances,
    config: config,
    templates: {
        boardc : "/driverlib/can/can.board.c.xdt",
        boardh : "/driverlib/can/can.board.h.xdt"
    },
    validate: onValidate,
    pinmuxRequirements    : Pinmux.canPinmuxRequirements
};


if (canModule.maxInstances <= 0)
{
    delete canModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(canModule)
    Pinmux.addPinMuxQualGroupToConfig(canModule)
}

exports = canModule;
