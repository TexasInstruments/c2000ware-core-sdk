//=============================================================================
// export_mod_gpio.js - GPIO Export Module for CDT
//=============================================================================
// Purpose: Expose GPIO diagnostic information for Clinic Diagnostic Tool
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: GPIO chapter
//   - driverlib/<device>/driverlib/gpio.h
//   - driverlib/<device>/driverlib/gpio.c
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const {
    DEVICES_WITH_CDT_SUPPORT,
    DEVICES_WITH_GPIO_PORTA,
    DEVICES_WITH_GPIO_PORTB,
    DEVICES_WITH_GPIO_PORTC,
    DEVICES_WITH_GPIO_PORTD,
    DEVICES_WITH_GPIO_PORTE,
    DEVICES_WITH_GPIO_PORTF,
    getDeviceName,
    getGpioPinCount
} = exportCommon;
const deviceName = getDeviceName();

// GPIO port availability varies by device
// Port A: GPIO0-31 (all devices)
// Port B: GPIO32-63 (larger devices)
// Port C: GPIO64-95 (larger devices)
// Port D: GPIO96-127 (largest devices)
// Port E: GPIO128-159 (largest devices)
// Port F: GPIO160-168 (F2838x, F28P65x)

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // GPIO Port A Data (GPIO0-31)
    //-------------------------------------------------------------------------
    {
        name: "gpioPortAData",
        displayName: "GPIO Port A Data",
        type: 'value',
        register: "GPADAT",
        updateFunc: (instBase) => `HWREG(GPIODATA_BASE + GPIO_O_GPADAT)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "gpioPortADir",
        displayName: "GPIO Port A Direction",
        type: 'value',
        register: "GPADIR",
        bitfieldInstance: "ctrl",
        // 0 = Input, 1 = Output
        updateFunc: (instBase) => `HWREG(GPIOCTRL_BASE + GPIO_O_GPADIR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "gpioPortAPud",
        displayName: "GPIO Port A Pull-Up Disable",
        type: 'value',
        register: "GPAPUD",
        bitfieldInstance: "ctrl",
        // 0 = Pull-up enabled, 1 = Pull-up disabled
        updateFunc: (instBase) => `HWREG(GPIOCTRL_BASE + GPIO_O_GPAPUD)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "gpioPortAOdr",
        displayName: "GPIO Port A Open Drain",
        type: 'value',
        register: "GPAODR",
        bitfieldInstance: "ctrl",
        // 0 = Normal output, 1 = Open drain
        updateFunc: (instBase) => `HWREG(GPIOCTRL_BASE + GPIO_O_GPAODR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "gpioPortAAmsel",
        displayName: "GPIO Port A Analog Mode",
        type: 'value',
        register: "GPAAMSEL",
        bitfieldInstance: "ctrl",
        // 1 = Analog mode enabled (for ADC inputs)
        updateFunc: (instBase) => `HWREG(GPIOCTRL_BASE + GPIO_O_GPAAMSEL)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "gpioPortALock",
        displayName: "GPIO Port A Lock",
        type: 'value',
        register: "GPALOCK",
        bitfieldInstance: "ctrl",
        // 1 = Configuration locked
        updateFunc: (instBase) => `HWREG(GPIOCTRL_BASE + GPIO_O_GPALOCK)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // GPIO Port B Data (GPIO32-63)
    //-------------------------------------------------------------------------
    {
        name: "gpioPortBData",
        displayName: "GPIO Port B Data",
        type: 'value',
        register: "GPBDAT",
        updateFunc: (instBase) => `HWREG(GPIODATA_BASE + GPIO_O_GPBDAT)`,
        applicable: (inst) => DEVICES_WITH_GPIO_PORTB.includes(deviceName)
    },
    {
        name: "gpioPortBDir",
        displayName: "GPIO Port B Direction",
        type: 'value',
        register: "GPBDIR",
        bitfieldInstance: "ctrl",
        updateFunc: (instBase) => `HWREG(GPIOCTRL_BASE + GPIO_O_GPBDIR)`,
        applicable: (inst) => DEVICES_WITH_GPIO_PORTB.includes(deviceName)
    },
    {
        name: "gpioPortBPud",
        displayName: "GPIO Port B Pull-Up Disable",
        type: 'value',
        register: "GPBPUD",
        bitfieldInstance: "ctrl",
        updateFunc: (instBase) => `HWREG(GPIOCTRL_BASE + GPIO_O_GPBPUD)`,
        applicable: (inst) => DEVICES_WITH_GPIO_PORTB.includes(deviceName)
    },
    {
        name: "gpioPortBOdr",
        displayName: "GPIO Port B Open Drain",
        type: 'value',
        register: "GPBODR",
        bitfieldInstance: "ctrl",
        updateFunc: (instBase) => `HWREG(GPIOCTRL_BASE + GPIO_O_GPBODR)`,
        applicable: (inst) => DEVICES_WITH_GPIO_PORTB.includes(deviceName)
    },
    {
        name: "gpioPortBLock",
        displayName: "GPIO Port B Lock",
        type: 'value',
        register: "GPBLOCK",
        bitfieldInstance: "ctrl",
        updateFunc: (instBase) => `HWREG(GPIOCTRL_BASE + GPIO_O_GPBLOCK)`,
        applicable: (inst) => DEVICES_WITH_GPIO_PORTB.includes(deviceName)
    },

    //-------------------------------------------------------------------------
    // GPIO Port C Data (GPIO64-95)
    //-------------------------------------------------------------------------
    {
        name: "gpioPortCData",
        displayName: "GPIO Port C Data",
        type: 'value',
        register: "GPCDAT",
        updateFunc: (instBase) => `HWREG(GPIODATA_BASE + GPIO_O_GPCDAT)`,
        applicable: (inst) => DEVICES_WITH_GPIO_PORTC.includes(deviceName)
    },
    {
        name: "gpioPortCDir",
        displayName: "GPIO Port C Direction",
        type: 'value',
        register: "GPCDIR",
        bitfieldInstance: "ctrl",
        updateFunc: (instBase) => `HWREG(GPIOCTRL_BASE + GPIO_O_GPCDIR)`,
        applicable: (inst) => DEVICES_WITH_GPIO_PORTC.includes(deviceName)
    },
    {
        name: "gpioPortCPud",
        displayName: "GPIO Port C Pull-Up Disable",
        type: 'value',
        register: "GPCPUD",
        bitfieldInstance: "ctrl",
        updateFunc: (instBase) => `HWREG(GPIOCTRL_BASE + GPIO_O_GPCPUD)`,
        applicable: (inst) => DEVICES_WITH_GPIO_PORTC.includes(deviceName)
    },

    //-------------------------------------------------------------------------
    // GPIO Port D Data (GPIO96-127)
    //-------------------------------------------------------------------------
    {
        name: "gpioPortDData",
        displayName: "GPIO Port D Data",
        type: 'value',
        register: "GPDDAT",
        updateFunc: (instBase) => `HWREG(GPIODATA_BASE + GPIO_O_GPDDAT)`,
        applicable: (inst) => DEVICES_WITH_GPIO_PORTD.includes(deviceName)
    },
    {
        name: "gpioPortDDir",
        displayName: "GPIO Port D Direction",
        type: 'value',
        register: "GPDDIR",
        bitfieldInstance: "ctrl",
        updateFunc: (instBase) => `HWREG(GPIOCTRL_BASE + GPIO_O_GPDDIR)`,
        applicable: (inst) => DEVICES_WITH_GPIO_PORTD.includes(deviceName)
    },

    //-------------------------------------------------------------------------
    // GPIO Port E Data (GPIO128-159)
    //-------------------------------------------------------------------------
    {
        name: "gpioPortEData",
        displayName: "GPIO Port E Data",
        type: 'value',
        register: "GPEDAT",
        updateFunc: (instBase) => `HWREG(GPIODATA_BASE + GPIO_O_GPEDAT)`,
        applicable: (inst) => DEVICES_WITH_GPIO_PORTE.includes(deviceName)
    },
    {
        name: "gpioPortEDir",
        displayName: "GPIO Port E Direction",
        type: 'value',
        register: "GPEDIR",
        bitfieldInstance: "ctrl",
        updateFunc: (instBase) => `HWREG(GPIOCTRL_BASE + GPIO_O_GPEDIR)`,
        applicable: (inst) => DEVICES_WITH_GPIO_PORTE.includes(deviceName)
    },

    //-------------------------------------------------------------------------
    // GPIO Port F Data (GPIO160-168)
    //-------------------------------------------------------------------------
    {
        name: "gpioPortFData",
        displayName: "GPIO Port F Data",
        type: 'value',
        register: "GPFDAT",
        updateFunc: (instBase) => `HWREG(GPIODATA_BASE + GPIO_O_GPFDAT)`,
        applicable: (inst) => DEVICES_WITH_GPIO_PORTF.includes(deviceName)
    },
    {
        name: "gpioPortFDir",
        displayName: "GPIO Port F Direction",
        type: 'value',
        register: "GPFDIR",
        bitfieldInstance: "ctrl",
        updateFunc: (instBase) => `HWREG(GPIOCTRL_BASE + GPIO_O_GPFDIR)`,
        applicable: (inst) => DEVICES_WITH_GPIO_PORTF.includes(deviceName)
    },

    //-------------------------------------------------------------------------
    // GPIO Qualification Status
    //-------------------------------------------------------------------------
    {
        name: "gpioQualPrd0",
        displayName: "GPIO Qual Period (GPIO0-7)",
        type: 'value',
        register: "GPACTRL.QUALPRD0",
        bitfieldInstance: "ctrl",
        updateFunc: (instBase) => `((HWREG(GPIOCTRL_BASE + GPIO_O_GPACTRL) & 0xFF))`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // External Interrupt Status
    //-------------------------------------------------------------------------
    {
        name: "xint1Sts",
        displayName: "XINT1 Status",
        description: "External Interrupt 1 enable status. GREEN = Enabled, RED = Disabled.",
        type: 'led',
        register: "XINT1CR.ENABLE",
        bitfieldInstance: "xint",
        // XINT flags are in PIE, not XINT module; show enable status instead
        updateFunc: (instBase) => `((HWREGH(XINT_BASE + XINT_O_1CR) & XINT_1CR_ENABLE) == XINT_1CR_ENABLE)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "xint2Sts",
        displayName: "XINT2 Status",
        description: "External Interrupt 2 enable status. GREEN = Enabled, RED = Disabled.",
        type: 'led',
        register: "XINT2CR.ENABLE",
        bitfieldInstance: "xint",
        updateFunc: (instBase) => `((HWREGH(XINT_BASE + XINT_O_2CR) & XINT_2CR_ENABLE) == XINT_2CR_ENABLE)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Diagnostic Indicators - DISABLED for now (calculated values require
    // special handling that's not yet implemented in the XDS export system)
    // TODO: Re-enable when calculated/diagnostic export support is added
    //-------------------------------------------------------------------------
    // gpioFloatingInputWarning, gpioLockedPinsWarning, gpioInputCount,
    // gpioOutputCount are calculated from GPADIR/GPAPUD/GPALOCK registers
    // but don't have actual register paths - they need to be computed in JS

    //-------------------------------------------------------------------------
    // Individual GPIO Pin Status - DISABLED
    // The register notation with bit indices (GPADAT.0) causes parsing errors
    // in the XDS export system ("unexpected token: .0").
    // GPIO pin status is still available through the Pinmux panel which reads
    // GPADAT/GPBDAT registers directly and displays per-pin state.
    //-------------------------------------------------------------------------
    // TODO: Re-enable when XDS export supports bit-indexed register notation
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "GpioDataRegs" },
    "data": (instName) => { return "GpioDataRegs" },
    "ctrl": (instName) => { return "GpioCtrlRegs" },
    "xint": (instName) => { return "XintRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Data registers are read-only for inputs, may skip if causing issues
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
