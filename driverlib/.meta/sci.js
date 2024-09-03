let Common = system.getScript("/driverlib/Common.js");
let Pinmux = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_sci.js");

function onChangeUseFIFO(inst, ui) {
    onChangeUseInterrupts(inst, ui);
}

function onChangeUseInterrupts(inst, ui) {
    if (inst.useInterrupts) {
        ui.enabledErrorInterrupts.hidden = false;
        ui.selectRegisteredInterrupts.hidden = false;

        if (inst.useFifo) {
            ui.enabledFIFOInterrupts.hidden = false;
            ui.enabledInterrupts.hidden = true;

            ui.txFifo.hidden = false;
            ui.rxFifo.hidden = false;
        }
        else {
            ui.enabledFIFOInterrupts.hidden = true;
            ui.enabledInterrupts.hidden = false;

            ui.txFifo.hidden = true;
            ui.rxFifo.hidden = true;
        }
    }
    else {
        ui.enabledInterrupts.hidden = true;
        ui.enabledFIFOInterrupts.hidden = true;
        ui.enabledErrorInterrupts.hidden = true;
        ui.selectRegisteredInterrupts.hidden = true;
        ui.txFifo.hidden = true;
        ui.rxFifo.hidden = true;
    }


}

let clocktree = Common.getClockTree();

/* Intro splash on GUI */
let longDescription = "An SCI peripheral is used to translate data between " +
    "the chip and a serial port. The SCI driver simplifies reading " +
    "and writing to any of the SCI(UART) peripherals on the board, with " +
    "multiple modes of operation and performance. These include " +
    "blocking, non-blocking, and polling, as well as text/binary " +
    "mode, echo and return characters.";

/* Array of SCI configurables that are common across device families */
let config = [
    {
        name: "baudRates",
        displayName: "Baud Rate",
        description: 'The set of baud rates that are used by this instance. '
            + 'On some devices, these rates are used to pre-compute '
            + 'a table of clock dividers necessary for each rate.',
        hidden: false,
        default: 115200,
    },
    {
        name: "brrReg",
        displayName: "BRR Register Field (LSB)",
        description: '',
        hidden: true,
        getValue: (inst) => {
            let baudrt = inst.baudRates;
            let usedLspclk;
            if (clocktree)
                usedLspclk = (clocktree["LSPCLK_domain"].in) * 1000000;
            else
                usedLspclk = (Common.getSYSCLK() * 1000000) / 4;
            let brrRegister = Math.round(((usedLspclk / 8) / baudrt) - 1);
            return brrRegister;
        },
        default: 115200
    },
    {
        name: "baudVal",
        displayName: "Actual Baud Rate Value",
        description: 'Actual baud rate value calculated based on LSPCLK and programmable values for this module. Not all baud rates are possible, depending on LSPCLK and BRR register values available. See the LSPCLK and LSPCLK Divider settings in "Global Parameters" being used to calculate this. Note: The actual baud rate is calculated based on the chosen settings and could still vary based on real-world factors like operating temperature, age etc. However this real-world error is typically negligible.',
        hidden: false,
        getValue: (inst) => {
            let usedLspclk;
            if (clocktree)
                usedLspclk = (clocktree["LSPCLK_domain"].in) * 1000000;
            else
                usedLspclk = (Common.getSYSCLK() * 1000000) / 4;
            let actualBaud = Math.round((usedLspclk / (inst.brrReg + 1)) / 8);
            return actualBaud;
        },
        default: 115200
    },
    {
        name: "baudErr",
        displayName: "Baud Rate Error Percent [%]",
        description: 'Percent error of the actual vs. set baud rate of the C2000 SCI. It is recommended to choose an LSPCLK divider and baud rate that will reduce this error as much as possible to avoid incorrectly transmitting/receiving bits or corrupting data.',
        hidden: false,
        getValue: (inst) => {
            let baudrtExpected = inst.baudRates;
            let errVal = ((inst.baudVal - baudrtExpected) / baudrtExpected) * 100;
            return Number(errVal.toFixed(3));
        },
        default: 0,
    },
    {
        name: "loopback",
        displayName: "Use Loopback Mode",
        description: 'Whether or not to use loopback mode.',
        hidden: false,
        default: false

    },

    {
        name: "wordLenght",
        displayName: "Word Length",
        description: 'Length of word.',
        hidden: false,
        default: '8',
        options: [
            { name: "1" },
            { name: "2" },
            { name: "3" },
            { name: "4" },
            { name: "5" },
            { name: "6" },
            { name: "7" },
            { name: "8" }
        ]
    },

    {
        name: "stop",
        displayName: "Stop Mode",
        description: 'Number of stop bits.',
        hidden: false,
        default: 'ONE',
        options: [
            { name: "ONE", displayName: "1" },
            { name: "TWO", displayName: "2" }
        ]
    },

    {
        name: "parity",
        displayName: "Parity Mode",
        description: 'Parity mode.',
        hidden: false,
        default: device_driverlib_peripheral.SCI_ParityType[0].name,
        options: device_driverlib_peripheral.SCI_ParityType
    },

    {
        name: "useInterrupts",
        displayName: "Use Interrupt",
        description: 'Whether or not to use Interrupt mode.',
        hidden: false,
        onChange: onChangeUseInterrupts,
        default: true

    },

    {
        name: "useFifo",
        displayName: "Use FIFO",
        description: 'Whether or not to use FIFO mode.',
        hidden: false,
        onChange: onChangeUseFIFO,
        default: true

    },

    {
        name: "registerInterrupts",
        description: 'INTERNAL: Hidden config maintained to avoid compatibility issues.',
        hidden: true,
        default: false,
    },
    

    {
        name: "selectRegisteredInterrupts",
        displayName: "Select Interrupt Handlers to register",
        description: 'List of interrupt handlers to be registered in the interrupt module.',
        hidden: false,
        minSelections: 0,
        default: [],
        options: [
            { name: "registerRxInt", displayName: "Receive Interrupt" },
            { name: "registerTxInt", displayName: "Transmit Interrupt" },
        ],

    },
    {
        name: "enabledInterrupts",
        displayName: "Enabled Interrupts",
        description: 'Which interrupts to enabled.',
        hidden: true,
        default: [],
        minSelections: 0,
        options: [
            { name: "SCI_INT_RXRDY_BRKDT", displayName: "Receive Interrupt" },
            { name: "SCI_INT_TXRDY", displayName: "Transmit Interrupt" },
        ],

    },

    {
        name: "enabledFIFOInterrupts",
        displayName: "Enabled FIFO Interrupts",
        description: 'Which FIFO interrupts to enabled.',
        hidden: false,
        default: [],
        minSelections: 0,
        options: [
            { name: "SCI_INT_RXFF", displayName: "Receive Interrupt" },
            { name: "SCI_INT_TXFF", displayName: "Transmit Interrupt" },
        ],

    },

    {
        name: "enabledErrorInterrupts",
        displayName: "Enabled Error Interrupts",
        description: 'Which error interrupts to enabled.',
        hidden: false,
        default: [],
        minSelections: 0,
        options: [
            { name: "SCI_INT_RXERR", displayName: "Receive Error Interrupt" },
            { name: "SCI_INT_PE", displayName: "Parity Error Interrupt" },
            { name: "SCI_INT_FE", displayName: "Frame Error Interrupt" },
            { name: "SCI_INT_OE", displayName: "Overrun Error Interrupt" }
        ],

    },

    {
        name: "txFifo",
        displayName: "Transmit FIFO Interrupt Level",
        description: 'Transmit FIFO interrupt level used.',
        hidden: false,
        default: device_driverlib_peripheral.SCI_TxFIFOLevel[0].name,
        options: device_driverlib_peripheral.SCI_TxFIFOLevel
    },

    {
        name: "rxFifo",
        displayName: "Receive FIFO Interrupt Level",
        description: 'Receive FIFO interrupt level used.',
        hidden: false,
        default: device_driverlib_peripheral.SCI_RxFIFOLevel[0].name,
        options: device_driverlib_peripheral.SCI_RxFIFOLevel
    },

    {
        name: "useCase",
        displayName: "Use Case",
        description: 'Peripheral use case',
        hidden: false,
        default: 'ALL',
        options: Pinmux.getPeripheralUseCaseNames("SCI"),
        onChange: Pinmux.useCaseChanged,
    },
];


function onValidate(inst, validation) {
    var bitRateInt = parseInt(inst.baudRates);
    let clockTree = Common.getClockTree();
    let lspClk = (Common.SYSCLK_getMaxMHz() * 1000000) / 4;
    if (clockTree) {
        lspClk = parseInt(parseFloat(clockTree["LSPCLK"].in) * 1000000);
    }
    var bitRateError = false;
    if (bitRateInt < lspClk / 65536 || bitRateInt > lspClk / 16) {
        bitRateError = true;
    }
    if (bitRateError) {
        validation.logError(
            "Enter an integer for baud rates between LSPCLK/65536 and LSPCLK/16!",
            inst, "baudRates");
    }
    if (inst.baudErr > 5 || inst.baudErr < -5) {
        validation.logWarning(
            "The C2000 SCI could introduce a large baud rate error with the chosen settings. It is recommended to modify the LSPCLK or selected baud rate in order to reduce the percent error. See the LSPCLK settings in 'Global Parameters' or in the clock tree tool. ",
            inst, "baudErr");
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
function filterHardware(component) {
    return (Common.typeMatches(component.type, ["SCI"]));
}

if (Common.onlyPinmux()) {
    config = [config[config.length - 1]];
}

var sciModule = {
    peripheralName: "SCI",
    displayName: "SCI",
    maxInstances: Common.peripheralCount("SCI"),
    defaultInstanceName: "mySCI",
    description: "Serial Communication Interface Peripheral",
    longDescription: (Common.getCollateralFindabilityList("SCI")),
    filterHardware: filterHardware,
    moduleInstances: (inst) => {
        var ownedInstances = []
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("SCI", inst)
        for (var pinmuxQualMod of pinmuxQualMods) {
            pinmuxQualMod.args = {
                qualMode: "GPIO_QUAL_ASYNC",
            }
            pinmuxQualMod.args.padConfig = "PULLUP";
        }
        ownedInstances = ownedInstances.concat(pinmuxQualMods)

        if (inst.useInterrupts) {
            if (inst.selectRegisteredInterrupts.includes("registerRxInt")) {
                ownedInstances = ownedInstances.concat([{
                    name: "sciRXInt",
                    displayName: "RX Interrupt",
                    moduleName: "/driverlib/interrupt.js",
                    collapsed: true,
                    args: {
                        $name: inst.$name + "_RX_INT",
                        int: "INT_" + inst.$name + "_RX",
                        pinmuxPeripheralModule: "sci",
                        driverlibInt: "INT_#_RX"
                    }
                }])
            }
            if (inst.selectRegisteredInterrupts.includes("registerTxInt")) {
                ownedInstances = ownedInstances.concat([{
                    name: "sciTXInt",
                    displayName: "TX Interrupt",
                    moduleName: "/driverlib/interrupt.js",
                    collapsed: true,
                    args: {
                        $name: inst.$name + "_TX_INT",
                        int: "INT_" + inst.$name + "_TX",
                        pinmuxPeripheralModule: "sci",
                        driverlibInt: "INT_#_TX"
                    }
                }])
            }
        }
        return ownedInstances;
    },
    config: config,
    templates: {
        boardc: "/driverlib/sci/sci.board.c.xdt",
        boardh: "/driverlib/sci/sci.board.h.xdt"
    },
    pinmuxRequirements: Pinmux.sciPinmuxRequirements,
    validate: onValidate,
    moduleStatic: {
        name: "SciGlobal",
        displayName: "SCI Global",
        config: [
            {
                name: "lspclk",
                displayName: "LSPCLK [MHz]",
                description: "LSPCLK set in clock tree tool. The LSPCLK is used as the clock source for the SCI module.",
                default: 1,
                hidden: false,
                getValue: (inst) => {
                    let clockTree = Common.getClockTree();
                    if (clockTree) {
                        return clockTree["LSPCLK_domain"].in
                    }
                    else {
                        return 0;
                    }
                }
            },
            {
                name: "lspclkDiv",
                displayName: "LSPCLK Divider (LOSPCP)",
                description: "LOSPCP divider set in clock tree tool. The LOSPCP divider sets the frequency of LSPCLK, which is used as the clock source for the SCI module.",
                default: 1,
                hidden: false,
                getValue: (inst) => {
                    let clockTree = Common.getClockTree();
                    if (clockTree) {
                        return clockTree.LOSPCP.divideValue
                    }
                    else {
                        return 1;
                    }
                }
            }
        ]
    }
};

if (sciModule.maxInstances <= 0) {
    delete sciModule.pinmuxRequirements;
}
else {
    Pinmux.addCustomPinmuxEnumToConfig(sciModule)
    Pinmux.addPinMuxQualGroupToConfig(sciModule)
}


exports = sciModule;