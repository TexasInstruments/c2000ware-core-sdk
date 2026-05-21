//=============================================================================
// export_mod_adc.js - ADC Export Module for CDT
//=============================================================================
// Purpose: Expose ADC diagnostic information for Clinic Diagnostic Tool
// Reference: driverlib/<device>/driverlib/inc/hw_adc.h
//
// ADC Instance Availability by Device (from device_constants.js):
//   ADCA: All Gen3 devices
//   ADCB: F28003x, F28004x, F2807x, F2837xD/S, F2838x, F28P55x, F28P65x
//   ADCC: F280013x, F280015x, F28002x, F28003x, F28004x, F2837xD/S, F2838x, F28P55x, F28P65x (NOT F2807x)
//   ADCD: F2807x, F2837xD, F2837xS, F2838x, F28P55x (Note: F2807x has ADCD but NOT ADCC)
//   ADCE: F28P55x only
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const {
    DEVICES_WITH_CDT_SUPPORT,
    DEVICES_WITH_ADCA,
    DEVICES_WITH_ADCB,
    DEVICES_WITH_ADCC,
    DEVICES_WITH_ADCD,
    DEVICES_WITH_ADCE,
    DEVICES_WITH_ADC_CONFIGURABLE_RESOLUTION,
    getDeviceName
} = exportCommon;
const deviceName = getDeviceName();

//-----------------------------------------------------------------------------
// Helper function to check if ADC instance is available on current device
//-----------------------------------------------------------------------------
function isAdcInstanceAvailable(inst) {
    if (!inst || !inst.adc) return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);

    let adcName = inst.adc.$solution ? inst.adc.$solution.peripheralName : "";
    if (adcName.includes("ADCA")) return DEVICES_WITH_ADCA.includes(deviceName);
    if (adcName.includes("ADCB")) return DEVICES_WITH_ADCB.includes(deviceName);
    if (adcName.includes("ADCC")) return DEVICES_WITH_ADCC.includes(deviceName);
    if (adcName.includes("ADCD")) return DEVICES_WITH_ADCD.includes(deviceName);
    if (adcName.includes("ADCE")) return DEVICES_WITH_ADCE.includes(deviceName);

    return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
}

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // ADC Power Status
    //-------------------------------------------------------------------------
    {
        name: "adcPowerDown",
        displayName: "ADC Powered Down",
        description: "ADC power-down state. Indicates ADC is powered off (ADCPWDNZ=0) and cannot perform conversions. Power on ADC before use.",
        type: 'led',
        ledType: 'error',  // Error - ADC should be powered on
        register: "ADCCTL1.ADCPWDNZ",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_CTL1) & ADC_CTL1_ADCPWDNZ) == 0)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },

    //-------------------------------------------------------------------------
    // ADC Busy Status
    //-------------------------------------------------------------------------
    {
        name: "adcBusy",
        displayName: "ADC Conversion In Progress",
        description: "ADC conversion active. Indicates ADC is currently performing a conversion. Normal during active sampling - not an error.",
        type: 'led',
        ledType: 'status',  // Informational - not an error
        register: "ADCCTL1.ADCBSY",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_CTL1) & ADC_CTL1_ADCBSY) == ADC_CTL1_ADCBSY)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },

    //-------------------------------------------------------------------------
    // ADC Interrupt Overflow
    // Indicates SOC trigger occurred while previous conversion still pending
    //-------------------------------------------------------------------------
    {
        name: "adcIntOvf1",
        displayName: "ADCINT1 Overflow",
        description: "Interrupt overflow - new trigger occurred before INT1 was cleared. May indicate ISR too slow.",
        type: 'led',
        ledType: 'error',  // Error - overflow is a problem
        register: "ADCINTOVF.ADCINT1",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_INTOVF) & ADC_INTOVF_ADCINT1) == ADC_INTOVF_ADCINT1)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },
    {
        name: "adcIntOvf2",
        displayName: "ADCINT2 Overflow",
        description: "Interrupt overflow - new trigger occurred before INT2 was cleared. May indicate ISR too slow.",
        type: 'led',
        ledType: 'error',  // Error - overflow is a problem
        register: "ADCINTOVF.ADCINT2",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_INTOVF) & ADC_INTOVF_ADCINT2) == ADC_INTOVF_ADCINT2)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },
    {
        name: "adcIntOvf3",
        displayName: "ADCINT3 Overflow",
        description: "Interrupt overflow - new trigger occurred before INT3 was cleared. May indicate ISR too slow.",
        type: 'led',
        ledType: 'error',  // Error - overflow is a problem
        register: "ADCINTOVF.ADCINT3",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_INTOVF) & ADC_INTOVF_ADCINT3) == ADC_INTOVF_ADCINT3)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },
    {
        name: "adcIntOvf4",
        displayName: "ADCINT4 Overflow",
        description: "Interrupt overflow - new trigger occurred before INT4 was cleared. May indicate ISR too slow.",
        type: 'led',
        ledType: 'error',  // Error - overflow is a problem
        register: "ADCINTOVF.ADCINT4",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_INTOVF) & ADC_INTOVF_ADCINT4) == ADC_INTOVF_ADCINT4)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },

    //-------------------------------------------------------------------------
    // ADC PPB (Post-Processing Block) Event Status
    // ADCEVTSTAT register contains trip flags for all PPBs
    //-------------------------------------------------------------------------
    {
        name: "ppb1TripHi",
        displayName: "PPB1 High Limit Trip",
        description: "PPB1 result exceeded high limit threshold. Check PPB1TRIPHI configuration.",
        type: 'led',
        register: "ADCEVTSTAT.PPB1TRIPHI",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_EVTSTAT) & ADC_EVTSTAT_PPB1TRIPHI) == ADC_EVTSTAT_PPB1TRIPHI)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },
    {
        name: "ppb1TripLo",
        displayName: "PPB1 Low Limit Trip",
        description: "PPB1 result below low limit threshold. Check PPB1TRIPLO configuration.",
        type: 'led',
        register: "ADCEVTSTAT.PPB1TRIPLO",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_EVTSTAT) & ADC_EVTSTAT_PPB1TRIPLO) == ADC_EVTSTAT_PPB1TRIPLO)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },
    {
        name: "ppb1Zero",
        displayName: "PPB1 Zero Crossing",
        description: "PPB1 detected zero crossing event. Used for signal analysis.",
        type: 'led',
        register: "ADCEVTSTAT.PPB1ZERO",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_EVTSTAT) & ADC_EVTSTAT_PPB1ZERO) == ADC_EVTSTAT_PPB1ZERO)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },
    {
        name: "ppb2TripHi",
        displayName: "PPB2 High Limit Trip",
        description: "PPB2 result exceeded high limit threshold. Check PPB2TRIPHI configuration.",
        type: 'led',
        register: "ADCEVTSTAT.PPB2TRIPHI",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_EVTSTAT) & ADC_EVTSTAT_PPB2TRIPHI) == ADC_EVTSTAT_PPB2TRIPHI)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },
    {
        name: "ppb2TripLo",
        displayName: "PPB2 Low Limit Trip",
        description: "PPB2 result below low limit threshold. Check PPB2TRIPLO configuration.",
        type: 'led',
        register: "ADCEVTSTAT.PPB2TRIPLO",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_EVTSTAT) & ADC_EVTSTAT_PPB2TRIPLO) == ADC_EVTSTAT_PPB2TRIPLO)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },
    {
        name: "ppb2Zero",
        displayName: "PPB2 Zero Crossing",
        description: "PPB2 detected zero crossing event. Used for signal analysis.",
        type: 'led',
        register: "ADCEVTSTAT.PPB2ZERO",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_EVTSTAT) & ADC_EVTSTAT_PPB2ZERO) == ADC_EVTSTAT_PPB2ZERO)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },
    {
        name: "ppb3TripHi",
        displayName: "PPB3 High Limit Trip",
        description: "PPB3 result exceeded high limit threshold. Check PPB3TRIPHI configuration.",
        type: 'led',
        register: "ADCEVTSTAT.PPB3TRIPHI",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_EVTSTAT) & ADC_EVTSTAT_PPB3TRIPHI) == ADC_EVTSTAT_PPB3TRIPHI)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },
    {
        name: "ppb3TripLo",
        displayName: "PPB3 Low Limit Trip",
        description: "PPB3 result below low limit threshold. Check PPB3TRIPLO configuration.",
        type: 'led',
        register: "ADCEVTSTAT.PPB3TRIPLO",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_EVTSTAT) & ADC_EVTSTAT_PPB3TRIPLO) == ADC_EVTSTAT_PPB3TRIPLO)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },
    {
        name: "ppb3Zero",
        displayName: "PPB3 Zero Crossing",
        description: "PPB3 detected zero crossing event. Used for signal analysis.",
        type: 'led',
        register: "ADCEVTSTAT.PPB3ZERO",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_EVTSTAT) & ADC_EVTSTAT_PPB3ZERO) == ADC_EVTSTAT_PPB3ZERO)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },
    {
        name: "ppb4TripHi",
        displayName: "PPB4 High Limit Trip",
        description: "PPB4 result exceeded high limit threshold. Check PPB4TRIPHI configuration.",
        type: 'led',
        register: "ADCEVTSTAT.PPB4TRIPHI",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_EVTSTAT) & ADC_EVTSTAT_PPB4TRIPHI) == ADC_EVTSTAT_PPB4TRIPHI)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },
    {
        name: "ppb4TripLo",
        displayName: "PPB4 Low Limit Trip",
        description: "PPB4 result below low limit threshold. Check PPB4TRIPLO configuration.",
        type: 'led',
        register: "ADCEVTSTAT.PPB4TRIPLO",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_EVTSTAT) & ADC_EVTSTAT_PPB4TRIPLO) == ADC_EVTSTAT_PPB4TRIPLO)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },
    {
        name: "ppb4Zero",
        displayName: "PPB4 Zero Crossing",
        description: "PPB4 detected zero crossing event. Used for signal analysis.",
        type: 'led',
        register: "ADCEVTSTAT.PPB4ZERO",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_EVTSTAT) & ADC_EVTSTAT_PPB4ZERO) == ADC_EVTSTAT_PPB4ZERO)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },

    //-------------------------------------------------------------------------
    // Value Exports - Current ADC Configuration
    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------
    // Value Exports - Current ADC Configuration
    // Note: PRESCALE exists on all devices, but RESOLUTION and SIGNALMODE
    // only exist on devices with configurable ADC (F2837xD/S, F2838x)
    //-------------------------------------------------------------------------
    {
        name: "adcPrescale",
        displayName: "ADC Clock Prescale",
        description: "ADCCLK divider value (0-15). ADCCLK = SYSCLK / prescale.",
        type: 'value',
        register: "ADCCTL2.PRESCALE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_CTL2) & ADC_CTL2_PRESCALE_M) >> ADC_CTL2_PRESCALE_S)`,
        applicable: (inst) => {
            return isAdcInstanceAvailable(inst);
        }
    },
    {
        name: "adcResolution",
        displayName: "ADC Resolution Mode",
        description: "ADC resolution: 0=12-bit, 1=16-bit.",
        type: 'led',
        register: "ADCCTL2.RESOLUTION",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_CTL2) & ADC_CTL2_RESOLUTION) >> 6)`,
        applicable: (inst) => {
            // Only devices with configurable ADC resolution (from device_constants.js)
            return DEVICES_WITH_ADC_CONFIGURABLE_RESOLUTION.includes(deviceName);
        }
    },
    {
        name: "adcSignalMode",
        displayName: "ADC Signal Mode",
        description: "Input signal mode: 0=Single-ended, 1=Differential.",
        type: 'led',
        register: "ADCCTL2.SIGNALMODE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ADC_O_CTL2) & ADC_CTL2_SIGNALMODE) >> 7)`,
        applicable: (inst) => {
            // Only devices with configurable ADC resolution (from device_constants.js)
            return DEVICES_WITH_ADC_CONFIGURABLE_RESOLUTION.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
// Maps both letter instances (A/B/C/D) and numeric instances (0/1/2/3)
// SysConfig may name instances as myADCA or myADC0 depending on configuration
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "Adc" + instName + "Regs" },
    // Letter-based instance names (preferred)
    "a": (instName) => { return "AdcaRegs" },
    "b": (instName) => { return "AdcbRegs" },
    "c": (instName) => { return "AdccRegs" },
    "d": (instName) => { return "AdcdRegs" },
    // Numeric instance names (map to letter equivalents)
    "0": (instName) => { return "AdcaRegs" },  // ADC0 -> ADCA
    "1": (instName) => { return "AdcbRegs" },  // ADC1 -> ADCB
    "2": (instName) => { return "AdccRegs" },  // ADC2 -> ADCC
    "3": (instName) => { return "AdcdRegs" },  // ADC3 -> ADCD
};

//-----------------------------------------------------------------------------
// Registers to Skip (volatile data registers that shouldn't be exported)
// ADC result registers change with each conversion - skip them
// Read-to-Clear and Force registers - reading affects state
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Result registers (volatile - change with each conversion)
    { name: "RESULT0", register: "ADCRESULT0" },
    { name: "RESULT1", register: "ADCRESULT1" },
    { name: "RESULT2", register: "ADCRESULT2" },
    { name: "RESULT3", register: "ADCRESULT3" },
    { name: "RESULT4", register: "ADCRESULT4" },
    { name: "RESULT5", register: "ADCRESULT5" },
    { name: "RESULT6", register: "ADCRESULT6" },
    { name: "RESULT7", register: "ADCRESULT7" },
    { name: "RESULT8", register: "ADCRESULT8" },
    { name: "RESULT9", register: "ADCRESULT9" },
    { name: "RESULT10", register: "ADCRESULT10" },
    { name: "RESULT11", register: "ADCRESULT11" },
    { name: "RESULT12", register: "ADCRESULT12" },
    { name: "RESULT13", register: "ADCRESULT13" },
    { name: "RESULT14", register: "ADCRESULT14" },
    { name: "RESULT15", register: "ADCRESULT15" },
    // Read-to-Clear registers (R/W1C - Write 1 to Clear)
    { name: "INTFLGCLR", register: "ADCINTFLGCLR" },
    { name: "INTOVFCLR", register: "ADCINTOVFCLR" },
    { name: "SOCOVFCLR1", register: "ADCSOCOVFCLR1" },
    { name: "EVTCLR", register: "ADCEVTCLR" },
    // Force registers (Write-Only - Force trigger)
    { name: "SOCFRC1", register: "ADCSOCFRC1" },
    // PPB Result registers (volatile - contain post-processed conversion results)
    { name: "PPB1RESULT", register: "ADCPPB1RESULT" },
    { name: "PPB2RESULT", register: "ADCPPB2RESULT" },
    { name: "PPB3RESULT", register: "ADCPPB3RESULT" },
    { name: "PPB4RESULT", register: "ADCPPB4RESULT" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
