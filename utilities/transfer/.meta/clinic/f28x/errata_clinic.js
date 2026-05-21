/**
 * @fileoverview Errata Clinic Module for CDT (Clinic Diagnostic Tool)
 *
 * This module provides runtime checks for known silicon errata advisories
 * on TI C2000 Gen3 devices. Each check reads device registers and/or memory
 * locations to detect conditions that may trigger errata behavior.
 *
 * @module errata_clinic
 * @author Texas Instruments
 *
 * @description
 * The module exports four data structures:
 * - errataPrereqRegisters: Device registers needed for errata checks
 * - errataPrereqMemoryLocs: Memory locations needed for errata checks
 * - memoryValueCalculators: Functions to process raw memory values
 * - errataChecks: The actual errata advisory checks
 *
 * Each check includes:
 * - Device-specific applicability
 * - Reference links to official TI errata documentation
 * - Workaround descriptions with affected silicon revisions
 *
 * @see https://www.ti.com/tool/c2000ware - C2000Ware SDK
 * @see device_constants.js - Centralized device support definitions
 */

// =============================================================================
// Device Constants - Import from centralized module
// =============================================================================
const {
    // Device Families
    DEVICES_GEN2,
    DEVICES_GEN3,
    DEVICES_WITH_CDT_SUPPORT,
    // Gen2 PLL Architecture
    DEVICES_WITH_PLLCR_DIV,
    // ADC Instances
    DEVICES_WITH_ADCA,
    DEVICES_WITH_ADCB,
    DEVICES_WITH_ADCC,
    DEVICES_WITH_ADCD,
    // eQEP Instances
    DEVICES_WITH_EQEP1,
    DEVICES_WITH_EQEP2,
    DEVICES_WITH_EQEP3,
    // System Features
    DEVICES_WITH_CMPSS,
    DEVICES_WITH_SDFM,
    DEVICES_WITH_DCC,
    DEVICES_WITH_FSI,
    // Errata Applicability
    DEVICES_WITH_ADC_FRACTIONAL_DIVIDER_ERRATA,
    DEVICES_WITH_CMPSS_LATCH_ERRATA,
    DEVICES_WITH_CMPSS_RAMP_ERRATA,
    DEVICES_WITH_EPWM_DEADBAND_ERRATA,
    DEVICES_WITH_MCD_ERRATA,
    DEVICES_WITH_FLASH_ECC_ERRATA,
    DEVICES_WITH_DCC_SINGLESHOT_ERRATA,
    DEVICES_WITH_SDFM_MANCHESTER_ERRATA,
    DEVICES_WITH_I2C_OPENDRAIN_ERRATA,
    DEVICES_WITH_PLL_LOCK_ERRATA,
    // DEVICES_WITH_FSI_OVERRUN_ERRATA — imported but check not yet implemented (planned future release)
    DEVICES_WITH_EQEP_POSITION_ERRATA,
    // Register availability (for device-specific prereqs)
    DEVICES_WITH_CERRTHRES_REG,
    DEVICES_WITH_PLL_REFLOST_REG,
    DEVICES_WITH_PREFETCH_BOUNDARY_ERRATA
} = system.getScript("./device_constants.js");

// ADC Interrupt Continue errata affects all Gen3 devices
const DEVICES_WITH_ADC_INTCONT_ERRATA = DEVICES_GEN3;

// =============================================================================
// Gen2 Errata Applicability Groups
// Source: SPRZ283 (F2802x/F2803x), SPRZ281 (F2806x), SPRZ324 (F2805x)
// =============================================================================

// Gen2 PLL Lock/DIVSEL Sequence Errata
// Advisory: PLL may not lock properly if DIVSEL changed before PLLLOCKS=1
const DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA = ["F2802x", "F2803x", "F2805x", "F2806x"];

// Gen2 Flash Pump Wakeup Errata
// Advisory: Flash pump may not wake up correctly from low power mode
const DEVICES_GEN2_WITH_FLASH_PUMP_ERRATA = ["F2802x", "F2803x"];

// Gen2 ADC Reference Errata
// Advisory: ADC reference may be unstable after power-up
const DEVICES_GEN2_WITH_ADC_REF_ERRATA = ["F2802x", "F2803x", "F2805x"];

// Gen2 I2C Clock Stretching Errata
// Advisory: I2C may not properly handle clock stretching
const DEVICES_GEN2_WITH_I2C_STRETCH_ERRATA = ["F2802x", "F2803x", "F2806x"];

// =============================================================================
// Prerequisite Registers
// =============================================================================

/**
 * @typedef {Object} PrereqRegister
 * @property {string} description - Human-readable description of the register
 * @property {string} register - Register path (e.g., "AdcaRegs.ADCINTSEL1N2.INT1CONT")
 * @property {string} name - Unique identifier used in calculator/check functions
 * @property {function(string): boolean} applicable - Returns true if register applies to device
 */

/**
 * Prerequisite registers required for errata checks.
 * Each register is read from the device via XDS debugger interface.
 * @type {PrereqRegister[]}
 */
const errataPrereqRegisters = [
    // =========================================================================
    // Gen2 PLL Errata Registers
    // =========================================================================
    {
        description: "Gen2 PLLSTS DIVSEL",
        register: "SysCtrlRegs.PLLSTS.DIVSEL",
        name: "gen2pllstsdivsel",
        applicable: (device) => DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA.includes(device)
    },
    {
        description: "Gen2 PLLSTS PLLLOCKS",
        register: "SysCtrlRegs.PLLSTS.PLLLOCKS",
        name: "gen2pllstslocks",
        applicable: (device) => DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA.includes(device)
    },
    {
        description: "Gen2 PLLSTS MCLKSTS",
        register: "SysCtrlRegs.PLLSTS.MCLKSTS",
        name: "gen2pllstsmclksts",
        applicable: (device) => DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA.includes(device)
    },
    // =========================================================================
    // ADCA Interrupt Continue Registers (ALL Gen3 devices)
    // =========================================================================
    {
        description: "ADCAINT1 CONTINUE TO INTERRUPT",
        register: "AdcaRegs.ADCINTSEL1N2.INT1CONT",
        name: "adcaintsel1",
        applicable: (device) => DEVICES_WITH_ADCA.includes(device)
    },
    {
        description: "ADCAINT2 CONTINUE TO INTERRUPT",
        register: "AdcaRegs.ADCINTSEL1N2.INT2CONT",
        name: "adcaintsel2",
        applicable: (device) => DEVICES_WITH_ADCA.includes(device)
    },
    {
        description: "ADCAINT3 CONTINUE TO INTERRUPT",
        register: "AdcaRegs.ADCINTSEL3N4.INT3CONT",
        name: "adcaintsel3",
        applicable: (device) => DEVICES_WITH_ADCA.includes(device)
    },
    {
        description: "ADCAINT4 CONTINUE TO INTERRUPT",
        register: "AdcaRegs.ADCINTSEL3N4.INT4CONT",
        name: "adcaintsel4",
        applicable: (device) => DEVICES_WITH_ADCA.includes(device)
    },
    // =========================================================================
    // ADCB Interrupt Continue Registers (devices with ADCB)
    // =========================================================================
    {
        description: "ADCBINT1 CONTINUE TO INTERRUPT",
        register: "AdcbRegs.ADCINTSEL1N2.INT1CONT",
        name: "adcbintsel1",
        applicable: (device) => DEVICES_WITH_ADCB.includes(device)
    },
    {
        description: "ADCBINT2 CONTINUE TO INTERRUPT",
        register: "AdcbRegs.ADCINTSEL1N2.INT2CONT",
        name: "adcbintsel2",
        applicable: (device) => DEVICES_WITH_ADCB.includes(device)
    },
    {
        description: "ADCBINT3 CONTINUE TO INTERRUPT",
        register: "AdcbRegs.ADCINTSEL3N4.INT3CONT",
        name: "adcbintsel3",
        applicable: (device) => DEVICES_WITH_ADCB.includes(device)
    },
    {
        description: "ADCBINT4 CONTINUE TO INTERRUPT",
        register: "AdcbRegs.ADCINTSEL3N4.INT4CONT",
        name: "adcbintsel4",
        applicable: (device) => DEVICES_WITH_ADCB.includes(device)
    },
    // =========================================================================
    // ADCC Interrupt Continue Registers (devices with ADCC)
    // =========================================================================
    {
        description: "ADCCINT1 CONTINUE TO INTERRUPT",
        register: "AdccRegs.ADCINTSEL1N2.INT1CONT",
        name: "adccintsel1",
        applicable: (device) => DEVICES_WITH_ADCC.includes(device)
    },
    {
        description: "ADCCINT2 CONTINUE TO INTERRUPT",
        register: "AdccRegs.ADCINTSEL1N2.INT2CONT",
        name: "adccintsel2",
        applicable: (device) => DEVICES_WITH_ADCC.includes(device)
    },
    {
        description: "ADCCINT3 CONTINUE TO INTERRUPT",
        register: "AdccRegs.ADCINTSEL3N4.INT3CONT",
        name: "adccintsel3",
        applicable: (device) => DEVICES_WITH_ADCC.includes(device)
    },
    {
        description: "ADCCINT4 CONTINUE TO INTERRUPT",
        register: "AdccRegs.ADCINTSEL3N4.INT4CONT",
        name: "adccintsel4",
        applicable: (device) => DEVICES_WITH_ADCC.includes(device)
    },
    // =========================================================================
    // eQEP Position Counter Registers (CONSOLIDATED)
    // =========================================================================
    {
        description: "eQEP1 POS COUNTER RESET",
        register: "EQep1Regs.QEPCTL.PCRM",
        name: "eqep1posctrreset",
        applicable: (device) => DEVICES_WITH_EQEP_POSITION_ERRATA.includes(device) && DEVICES_WITH_EQEP1.includes(device)
    },
    {
        description: "eQEP2 POS COUNTER RESET",
        register: "EQep2Regs.QEPCTL.PCRM",
        name: "eqep2posctrreset",
        applicable: (device) => DEVICES_WITH_EQEP_POSITION_ERRATA.includes(device) && DEVICES_WITH_EQEP2.includes(device)
    },
    // =========================================================================
    // ADC Power Down Registers (CONSOLIDATED)
    // =========================================================================
    {
        description: "ADCA POWERDOWN",
        register: "AdcaRegs.ADCCTL1.ADCPWDNZ",
        name: "adcapowerdownerrata",
        applicable: (device) => DEVICES_WITH_ADCA.includes(device)
    },
    {
        description: "ADCB POWERDOWN",
        register: "AdcbRegs.ADCCTL1.ADCPWDNZ",
        name: "adcbpowerdownerrata",
        applicable: (device) => DEVICES_WITH_ADCB.includes(device)
    },
    {
        description: "ADCC POWERDOWN",
        register: "AdccRegs.ADCCTL1.ADCPWDNZ",
        name: "adccpowerdownerrata",
        applicable: (device) => DEVICES_WITH_ADCC.includes(device)
    },
    // =========================================================================
    // ADC Prescale Registers for Fractional Divider Errata
    // =========================================================================
    {
        description: "ADCACLK PRESCALE",
        register: "AdcaRegs.ADCCTL2.PRESCALE",
        name: "adcaclkprescaleerrata",
        applicable: (device) => DEVICES_WITH_ADC_FRACTIONAL_DIVIDER_ERRATA.includes(device) && DEVICES_WITH_ADCA.includes(device)
    },
    {
        description: "ADCBCLK PRESCALE",
        register: "AdcbRegs.ADCCTL2.PRESCALE",
        name: "adcbclkprescaleerrata",
        applicable: (device) => DEVICES_WITH_ADC_FRACTIONAL_DIVIDER_ERRATA.includes(device) && DEVICES_WITH_ADCB.includes(device)
    },
    {
        description: "ADCCCLK PRESCALE",
        register: "AdccRegs.ADCCTL2.PRESCALE",
        name: "adccclkprescaleerrata",
        applicable: (device) => DEVICES_WITH_ADC_FRACTIONAL_DIVIDER_ERRATA.includes(device) && DEVICES_WITH_ADCC.includes(device)
    },
    {
        description: "ERROR THRESHOLD RAM/FLASH",
        register: "MemoryErrorRegs.CERRTHRES.CERRTHRES",
        name: "memoryerrorthreshold",
        applicable: (device) => DEVICES_WITH_CERRTHRES_REG.includes(device)
    },
    {
        description: "PLL REFERENCE CLOCK MISSING FLAG",
        register: "ClkCfgRegs.SYSPLLSTS.REF_LOSTS",
        name: "pllrefclklostflag",
        applicable: (device) => DEVICES_WITH_PLL_REFLOST_REG.includes(device)
    },
    {
        description: "SYSCLK DIVSEL",
        register: "ClkCfgRegs.SYSCLKDIVSEL.PLLSYSCLKDIV",
        name: "sysclkdivsel",
        // Only F280015x is affected by the LCM compare error / SYSCLKDIVSEL=0 errata
        applicable: (device) => device === "F280015x"
    },
    // =========================================================================
    // ADCD Interrupt Continue Registers (devices with ADCD)
    // =========================================================================
    {
        description: "ADCDINT1 CONTINUE TO INTERRUPT",
        register: "AdcdRegs.ADCINTSEL1N2.INT1CONT",
        name: "adcdintsel1",
        applicable: (device) => DEVICES_WITH_ADCD.includes(device)
    },
    {
        description: "ADCDINT2 CONTINUE TO INTERRUPT",
        register: "AdcdRegs.ADCINTSEL1N2.INT2CONT",
        name: "adcdintsel2",
        applicable: (device) => DEVICES_WITH_ADCD.includes(device)
    },
    {
        description: "ADCDINT3 CONTINUE TO INTERRUPT",
        register: "AdcdRegs.ADCINTSEL3N4.INT3CONT",
        name: "adcdintsel3",
        applicable: (device) => DEVICES_WITH_ADCD.includes(device)
    },
    {
        description: "ADCDINT4 CONTINUE TO INTERRUPT",
        register: "AdcdRegs.ADCINTSEL3N4.INT4CONT",
        name: "adcdintsel4",
        applicable: (device) => DEVICES_WITH_ADCD.includes(device)
    },
    {
        description: "ADCD POWERDOWN",
        register: "AdcdRegs.ADCCTL1.ADCPWDNZ",
        name: "adcdpowerdownerrata",
        applicable: (device) => DEVICES_WITH_ADCD.includes(device)
    },
    // =========================================================================
    // eQEP3 Position Counter Register (for devices with eQEP3 and the errata)
    // =========================================================================
    {
        description: "eQEP3 POS COUNTER RESET",
        register: "EQep3Regs.QEPCTL.PCRM",
        name: "eqep3posctrreset",
        applicable: (device) => DEVICES_WITH_EQEP_POSITION_ERRATA.includes(device) && DEVICES_WITH_EQEP3.includes(device)
    },
    // =========================================================================
    // CMPSS Registers
    // =========================================================================
    {
        description: "CMPSS1 HIGH COMPARATOR LATCH",
        register: "Cmpss1Regs.COMPSTS.COMPHSTS",
        name: "cmpss1highlatch",
        applicable: (device) => DEVICES_WITH_CMPSS.includes(device)
    },
    {
        description: "CMPSS1 LOW COMPARATOR LATCH",
        register: "Cmpss1Regs.COMPSTS.COMPLSTS",
        name: "cmpss1lowlatch",
        applicable: (device) => DEVICES_WITH_CMPSS.includes(device)
    },
    {
        // NOTE: There is no direct "ramp running" status register in CMPSS.
        // COMPHLATCH (high comparator latched output) is used as a proxy:
        // if the latch is set on a device affected by the ramp-start errata,
        // it may indicate a spurious trip caused by the ramp failing to start.
        // A true ramp-status register does not exist in hardware for these devices.
        description: "CMPSS1 HIGH COMPARATOR LATCH (proxy for ramp status)",
        register: "Cmpss1Regs.COMPSTS.COMPHLATCH",
        name: "cmpss1rampstatus",
        applicable: (device) => DEVICES_WITH_CMPSS_RAMP_ERRATA.includes(device)
    },
    // =========================================================================
    // ePWM Dead-Band Registers
    // =========================================================================
    {
        description: "EPWM1 DBCTL HALFCYCLE",
        register: "EPwm1Regs.DBCTL.HALFCYCLE",
        name: "epwm1dbctlhalfcycle",
        applicable: (device) => DEVICES_WITH_EPWM_DEADBAND_ERRATA.includes(device)
    },
    {
        description: "EPWM1 DBCTL LOADREDMODE",
        register: "EPwm1Regs.DBCTL2.LOADREDMODE",
        name: "epwm1dbctlloadredmode",
        applicable: (device) => DEVICES_WITH_EPWM_DEADBAND_ERRATA.includes(device)
    },
    {
        description: "EPWM1 DBCTL LOADFEDMODE",
        register: "EPwm1Regs.DBCTL2.LOADFEDMODE",
        name: "epwm1dbctlloadfedmode",
        applicable: (device) => DEVICES_WITH_EPWM_DEADBAND_ERRATA.includes(device)
    },
    {
        description: "EPWM1 DBRED",
        register: "EPwm1Regs.DBRED.DBRED",
        name: "epwm1dbred",
        applicable: (device) => DEVICES_WITH_EPWM_DEADBAND_ERRATA.includes(device)
    },
    {
        description: "EPWM1 DBFED",
        register: "EPwm1Regs.DBFED.DBFED",
        name: "epwm1dbfed",
        applicable: (device) => DEVICES_WITH_EPWM_DEADBAND_ERRATA.includes(device)
    },
    // =========================================================================
    // MCD (Missing Clock Detect) Registers
    // =========================================================================
    {
        description: "MCD STATUS",
        register: "ClkCfgRegs.MCDCR.MCLKSTS",
        name: "mcdstatus",
        applicable: (device) => DEVICES_WITH_MCD_ERRATA.includes(device)
    },
    {
        // MCLKOFF bit: 0 = MCD is ENABLED (bit name is inverted — "MCLK OFF" means OFF=0 → running)
        // Variable named "mcdenabled" to reflect semantic: mcdenabled===0 means MCD is active
        description: "MCD ENABLED (MCLKOFF=0 means MCD is active)",
        register: "ClkCfgRegs.MCDCR.MCLKOFF",
        name: "mcdenabled",
        applicable: (device) => DEVICES_WITH_MCD_ERRATA.includes(device)
    },
    {
        description: "PLL CLKEN",
        register: "ClkCfgRegs.SYSPLLCTL1.PLLCLKEN",
        name: "pllclkenabled",
        applicable: (device) => DEVICES_WITH_MCD_ERRATA.includes(device)
    },
    // =========================================================================
    // DCC (Dual Clock Comparator) Registers
    // =========================================================================
    {
        description: "DCC0 SINGLE SHOT MODE",
        register: "Dcc0Regs.DCCGCTRL.SINGLESHOT",
        name: "dcc0singleshot",
        applicable: (device) => DEVICES_WITH_DCC_SINGLESHOT_ERRATA.includes(device)
    },
    {
        description: "DCC0 ENABLED",
        register: "Dcc0Regs.DCCGCTRL.DCCENA",
        name: "dcc0enabled",
        applicable: (device) => DEVICES_WITH_DCC_SINGLESHOT_ERRATA.includes(device)
    },
    // =========================================================================
    // SDFM Registers
    // =========================================================================
    {
        description: "SDFM1 FILTER1 MODE",
        register: "Sdfm1Regs.SDCTLPARM1.MOD",
        name: "sdfm1filter1mode",
        applicable: (device) => DEVICES_WITH_SDFM_MANCHESTER_ERRATA.includes(device)
    },
    {
        description: "SDFM1 MODULE ENABLED",
        register: "Sdfm1Regs.SDMFILEN.MFE",
        name: "sdfm1enabled",
        applicable: (device) => DEVICES_WITH_SDFM_MANCHESTER_ERRATA.includes(device)
    },
    // =========================================================================
    // I2C Registers
    // =========================================================================
    {
        description: "I2CA MODE REGISTER",
        register: "I2caRegs.I2CMDR.MST",
        name: "i2camodemaster",
        applicable: (device) => DEVICES_WITH_I2C_OPENDRAIN_ERRATA.includes(device)
    },
    {
        description: "I2CA ENABLED",
        register: "I2caRegs.I2CMDR.IRS",
        name: "i2caenabled",
        applicable: (device) => DEVICES_WITH_I2C_OPENDRAIN_ERRATA.includes(device)
    },
    // =========================================================================
    // Flash ECC Registers
    // =========================================================================
    {
        description: "FLASH ECC ENABLED",
        register: "Flash0EccRegs.ECC_ENABLE.ENABLE",
        name: "flasheccenabled",
        applicable: (device) => DEVICES_WITH_FLASH_ECC_ERRATA.includes(device)
    },
    // =========================================================================
    // PLL Registers for Lock Errata
    // =========================================================================
    {
        description: "PLL LOCK STATUS",
        register: "ClkCfgRegs.SYSPLLSTS.LOCKS",
        name: "plllockstatus",
        applicable: (device) => DEVICES_WITH_PLL_LOCK_ERRATA.includes(device)
    }
]

/**
 * @typedef {Object} PrereqMemoryLoc
 * @property {string} description - Human-readable description of the memory location
 * @property {string} address - Hexadecimal memory address (e.g., "0x000711DE")
 * @property {string} name - Unique identifier used in calculator/check functions
 * @property {function(string): boolean} applicable - Returns true if location applies to device
 */

/**
 * Prerequisite memory locations required for errata checks.
 * These are raw memory addresses read directly via XDS debugger.
 * Used for OTP revision numbers and prefetch boundary checks.
 * @type {PrereqMemoryLoc[]}
 */
const errataPrereqMemoryLocs = [
    {
        // OTP revision byte at address 0x000711DE (Ref: SPRZ506D/SPRZ507D errata MPOST check)
        // Bit [7:0] of this 16-bit word = OTP revision number
        description: "OTP REVISION NUMBER",
        address: "0x000711DE",
        name: "otprevisionnumberMemoryLoc",
        applicable: (device) => DEVICES_WITH_PLL_REFLOST_REG.includes(device)
    },
    {
        // M1 SARAM boundary register (Ref: SPRZ496D/SPRZ506D/SPRZ507D prefetch errata)
        // Valid when = 0 (prefetch window does not extend beyond M1 end boundary)
        description: "PREFETCH BOUNDARY M1",
        address: "0x000007F8",
        name: "prefetchboundaryMemoryLocM1",
        applicable: (device) => DEVICES_WITH_PREFETCH_BOUNDARY_ERRATA.includes(device)
    },
    {
        // GS3 SARAM boundary register (Ref: SPRZ496D prefetch errata)
        // Valid when = 0 (prefetch window does not extend beyond GS3 end boundary)
        description: "PREFETCH BOUNDARY GS3",
        address: "0x0000FFF8",
        name: "prefetchboundaryMemoryLocGS3",
        applicable: (device) => device === "F28003x"
    },
    {
        // Flash boundary register (Ref: SPRZ496D prefetch errata)
        // Valid when = 0xFFFF (= 65535): prefetch boundary is at top of Flash address space
        description: "PREFETCH BOUNDARY FLASH",
        address: "0x000AFFF0",
        name: "prefetchboundaryMemoryLocFlash",
        applicable: (device) => device === "F28003x"
    },
]

/**
 * @typedef {Object} MemoryValueCalculator
 * @property {string} name - Unique identifier for the calculated value
 * @property {function(*): number} get - Function to process raw memory value
 * @property {function(string): boolean} applicable - Returns true if calculator applies to device
 */

/**
 * Calculators for processing raw memory location values.
 * These extract specific fields from memory reads (e.g., masking revision numbers).
 * @type {MemoryValueCalculator[]}
 */
const memoryValueCalculators = [
    {
        name: "otprevisionnumber",
        get: (otprevisionnumberMemoryLoc) => {
            // Extract low byte: OTP revision is stored in bits [7:0] of the 16-bit word
            return otprevisionnumberMemoryLoc & 0x000000FF;
        },
        applicable: (device) => DEVICES_WITH_PLL_REFLOST_REG.includes(device)
    },
    {
        name: "prefetchboundarym1",
        get: (prefetchboundaryMemoryLocM1) => {
            // C2000 SARAM boundary registers are 16-bit values; mask to 0xFFFF
            return prefetchboundaryMemoryLocM1 & 0xFFFF;
        },
        applicable: (device) => DEVICES_WITH_PREFETCH_BOUNDARY_ERRATA.includes(device)
    },
    {
        name: "prefetchboundarygs3",
        get: (prefetchboundaryMemoryLocGS3) => {
            // C2000 SARAM boundary registers are 16-bit values; mask to 0xFFFF
            return prefetchboundaryMemoryLocGS3 & 0xFFFF;
        },
        applicable: (device) => device === "F28003x"
    },
    {
        name: "prefetchboundaryflash",
        get: (prefetchboundaryMemoryLocFlash) => {
            // Flash boundary register is a 16-bit value; mask to 0xFFFF
            return prefetchboundaryMemoryLocFlash & 0xFFFF;
        },
        applicable: (device) => device === "F28003x"
    }
]

/**
 * @typedef {Object} ErrataCheck
 * @property {string} name - Unique identifier for the check
 * @property {string} displayName - User-facing name shown in GUI
 * @property {string} peripheral - Associated peripheral module (adc, system, epwm, etc.)
 * @property {Object.<string, string>} referenceLink - Device-specific TI errata document URLs
 * @property {string|Object.<string, string>} description - Errata description with affected revisions and workaround
 * @property {function(...*): boolean} check - Returns true if check passes (no errata condition), false if errata detected
 * @property {function(string): boolean} applicable - Returns true if check applies to device
 */

/**
 * Errata advisory checks for C2000 Gen3 devices.
 *
 * Each check evaluates device state to detect conditions that may trigger
 * documented silicon errata behavior. Checks return:
 * - true: Check passes (errata condition NOT present, or workaround applied)
 * - false: Check fails (errata condition detected, user should review advisory)
 *
 * Reference links point to official TI errata documentation with:
 * - Affected silicon revisions
 * - Problem description
 * - Recommended workarounds
 *
 * @type {ErrataCheck[]}
 */
const errataChecks = [
    // =========================================================================
    // Gen2 Errata Checks
    // =========================================================================
    {
        name: "gen2PllDivselSequence",
        displayName: "Gen2 PLL DIVSEL Sequence",
        peripheral: "sysctl",
        referenceLink: {
            "F2802x": "https://www.ti.com/lit/er/sprz283s/sprz283s.pdf",
            "F2803x": "https://www.ti.com/lit/er/sprz283s/sprz283s.pdf",
            "F2805x": "https://www.ti.com/lit/er/sprz324f/sprz324f.pdf",
            "F2806x": "https://www.ti.com/lit/er/sprz281p/sprz281p.pdf"
        },
        description: {
            "default": "Gen2 PLL Errata Advisory 5\n\nProblem: DIVSEL should not be changed to /1 while PLLLOCKS=0. The PLL may not lock properly if the DIVSEL is set to /1 before the PLL has locked.\n\nWorkaround: Wait for PLLLOCKS=1 before setting DIVSEL to /1 (value 3). The sequence should be:\n1. Set PLLCR.DIV to desired multiplier\n2. Wait for PLLLOCKS=1\n3. Then change DIVSEL to desired value"
        },
        check: (gen2pllstsdivsel, gen2pllstslocks) => {
            // DIVSEL=3 means /1 divider
            // PLLLOCKS=0 means PLL is not locked
            // Problem condition: DIVSEL=/1 AND PLL not locked
            if (gen2pllstsdivsel === 3 && gen2pllstslocks === 0) {
                return false;  // Errata condition detected
            }
            return true;  // OK - either PLL locked or DIVSEL not /1
        },
        applicable: (device) => DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA.includes(device)
    },
    {
        name: "gen2MclkDetected",
        displayName: "Gen2 Missing Clock Detected",
        peripheral: "sysctl",
        referenceLink: {
            "F2802x": "https://www.ti.com/lit/er/sprz283s/sprz283s.pdf",
            "F2803x": "https://www.ti.com/lit/er/sprz283s/sprz283s.pdf",
            "F2805x": "https://www.ti.com/lit/er/sprz324f/sprz324f.pdf",
            "F2806x": "https://www.ti.com/lit/er/sprz281p/sprz281p.pdf"
        },
        description: {
            "default": "Gen2 Missing Clock Status\n\nStatus: MCLKSTS=1 indicates the Missing Clock Detect (MCD) circuit has detected a loss of the main oscillator clock.\n\nAction: Check external oscillator/crystal connections. If MCLKSTS=1, the device has switched to the internal oscillator (INTOSC1)."
        },
        check: (gen2pllstsmclksts) => {
            // MCLKSTS=1 means missing clock was detected
            return gen2pllstsmclksts === 0;  // Pass if no missing clock
        },
        applicable: (device) => DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA.includes(device)
    },
    // =========================================================================
    // Gen3 Errata Checks
    // =========================================================================
    {
        name: "adccContInterruptNotSet",
        displayName: "ADCC INTxCONT Not Set",
        peripheral: "adc",  // Associated peripheral module
        referenceLink : {
            "F280013x": "https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-1F598B78-29D2-4CCE-8624-52CA6D1EB1C6/TITLE-SPRZ466X3264",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-D0DDFBED-54C9-4F94-BF76-89EBA7ECA72C/TITLE-SPRZ466X3264",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-70BFECFD-5EFD-4B23-AB49-2F026FBEEB99/TITLE-SPRZ466X3264",
            "F28002x": "https://www.ti.com/document-viewer/lit/html/sprz466c#GUID-2E34FD25-77F1-4A25-A978-3513361D7D1E/TITLE-SPRZ466C",
            "F28004x": "https://www.ti.com/document-viewer/lit/html/sprz439h#GUID-2E34FD25-77F1-4A25-A978-3513361D7D1E/TITLE-SPRZ439H",
            "F2837xD": "https://www.ti.com/document-viewer/lit/html/sprz412n#GUID-DFB82063-C08D-4C29-A681-491988C2F131/TITLE-SPRZ412N",
            "F2837xS": "https://www.ti.com/document-viewer/lit/html/sprz422k#GUID-5BE20B83-8402-487D-A5D6-1EAAACB9E862/TITLE-SPRZ422K",
            "F2838x": "https://www.ti.com/document-viewer/lit/html/sprz458f#GUID-8B500FB3-20CC-4F53-BEA9-E2C87DA3D6CC/TITLE-SPRZ458F",
            "F28P55x": "https://www.ti.com/document-viewer/lit/html/sprz572b#GUID-C78B20A8-5D35-4EC1-9214-E5D69C95A18C/TITLE-SPRZ572B",
            "F28P65x": "https://www.ti.com/document-viewer/lit/html/sprz545d#GUID-C78B20A8-5D35-4EC1-9214-E5D69C95A18C/TITLE-SPRZ545D"
        },
        description: {
            "default": "Revisions Affected: 0, A\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F28004x": "Revisions Affected: 0, A, B, C\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F2837xD": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F2837xS": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode."
        },
        check: (adccintsel1, adccintsel2, adccintsel3, adccintsel4, adccpowerdownerrata) => {
            if (adccpowerdownerrata === 0) return true;
            return adccintsel1 !== 0 && adccintsel2 !== 0 && adccintsel3 !== 0 && adccintsel4 !== 0;
        },
        applicable: (device) => DEVICES_WITH_ADCC.includes(device)
    },
    {
        name: "adcbContInterruptNotSet",
        displayName: "ADCB INTxCONT Not Set",
        peripheral: "adc",  // Associated peripheral module
        referenceLink : {
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-70BFECFD-5EFD-4B23-AB49-2F026FBEEB99/TITLE-SPRZ466X3264",
            "F28004x": "https://www.ti.com/document-viewer/lit/html/sprz439h#GUID-2E34FD25-77F1-4A25-A978-3513361D7D1E/TITLE-SPRZ439H",
            "F2807x": "https://www.ti.com/document-viewer/lit/html/sprz423k#GUID-A1B5F986-F097-4AB6-A611-1F9FB27F0FA2/TITLE-SPRZ423K",
            "F2837xD": "https://www.ti.com/document-viewer/lit/html/sprz412n#GUID-DFB82063-C08D-4C29-A681-491988C2F131/TITLE-SPRZ412N",
            "F2837xS": "https://www.ti.com/document-viewer/lit/html/sprz422k#GUID-5BE20B83-8402-487D-A5D6-1EAAACB9E862/TITLE-SPRZ422K",
            "F2838x": "https://www.ti.com/document-viewer/lit/html/sprz458f#GUID-8B500FB3-20CC-4F53-BEA9-E2C87DA3D6CC/TITLE-SPRZ458F",
            "F28P55x": "https://www.ti.com/document-viewer/lit/html/sprz572b#GUID-C78B20A8-5D35-4EC1-9214-E5D69C95A18C/TITLE-SPRZ572B",
            "F28P65x": "https://www.ti.com/document-viewer/lit/html/sprz545d#GUID-C78B20A8-5D35-4EC1-9214-E5D69C95A18C/TITLE-SPRZ545D"
        },
        description: {
            "default": "Revisions Affected: 0, A\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F28004x": "Revisions Affected: 0, A, B, C\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F2807x": "Revisions Affected: 0, A, B, C\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F2837xD": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F2837xS": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode."
        },
        check: (adcbintsel1, adcbintsel2, adcbintsel3, adcbintsel4, adcbpowerdownerrata) => {
            if (adcbpowerdownerrata === 0) return true;
            return adcbintsel1 !== 0 && adcbintsel2 !== 0 && adcbintsel3 !== 0 && adcbintsel4 !== 0;
        },
        applicable: (device) => DEVICES_WITH_ADCB.includes(device)
    },
    {
        name: "adcaContInterruptNotSet",
        displayName: "ADCA INTxCONT Not Set",
        peripheral: "adc",  // Associated peripheral module
        referenceLink : {
            "F280013x": "https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-1F598B78-29D2-4CCE-8624-52CA6D1EB1C6/TITLE-SPRZ466X3264",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-D0DDFBED-54C9-4F94-BF76-89EBA7ECA72C/TITLE-SPRZ466X3264",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-70BFECFD-5EFD-4B23-AB49-2F026FBEEB99/TITLE-SPRZ466X3264",
            "F28002x": "https://www.ti.com/document-viewer/lit/html/sprz466c#GUID-2E34FD25-77F1-4A25-A978-3513361D7D1E/TITLE-SPRZ466C",
            "F28004x": "https://www.ti.com/document-viewer/lit/html/sprz439h#GUID-2E34FD25-77F1-4A25-A978-3513361D7D1E/TITLE-SPRZ439H",
            "F2807x": "https://www.ti.com/document-viewer/lit/html/sprz423k#GUID-A1B5F986-F097-4AB6-A611-1F9FB27F0FA2/TITLE-SPRZ423K",
            "F2837xD": "https://www.ti.com/document-viewer/lit/html/sprz412n#GUID-DFB82063-C08D-4C29-A681-491988C2F131/TITLE-SPRZ412N",
            "F2837xS": "https://www.ti.com/document-viewer/lit/html/sprz422k#GUID-5BE20B83-8402-487D-A5D6-1EAAACB9E862/TITLE-SPRZ422K",
            "F2838x": "https://www.ti.com/document-viewer/lit/html/sprz458f#GUID-8B500FB3-20CC-4F53-BEA9-E2C87DA3D6CC/TITLE-SPRZ458F",
            "F28P55x": "https://www.ti.com/document-viewer/lit/html/sprz572b#GUID-C78B20A8-5D35-4EC1-9214-E5D69C95A18C/TITLE-SPRZ572B",
            "F28P65x": "https://www.ti.com/document-viewer/lit/html/sprz545d#GUID-C78B20A8-5D35-4EC1-9214-E5D69C95A18C/TITLE-SPRZ545D"
        },
        description: {
            "default": "Revisions Affected: 0, A\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F28004x": "Revisions Affected: 0, A, B, C\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F2807x": "Revisions Affected: 0, A, B, C\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F2837xD": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F2837xS": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode."
        },
        check: (adcaintsel1, adcaintsel2, adcaintsel3, adcaintsel4, adcapowerdownerrata) => {
            if (adcapowerdownerrata === 0) return true;
            return adcaintsel1 !== 0 && adcaintsel2 !== 0 && adcaintsel3 !== 0 && adcaintsel4 !== 0;
        },
        applicable: (device) => DEVICES_WITH_ADCA.includes(device)
    },
    {
        name: "adccFractionalDivider",
        displayName: "ADCC Fractional Divider Set",
        peripheral: "adc",  // Associated peripheral module
        referenceLink: {
            "F280013x":"https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-2AD7590D-B516-48BA-AB61-C0DC9F09B194/TITLE-SPRZ439SPRZ439676",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-54731D89-E043-44AB-A73D-F6F70AD6168B/TITLE-SPRZ439SPRZ439676",
            "F28002x": "https://www.ti.com/document-viewer/lit/html/sprz506d#GUID-871D953D-C06E-401D-A107-C0A7DF78E185/TITLE-SPRZ506D",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-8A437E6A-4FD1-4CDE-BB0F-3A433B7BEF10/TITLE-SPRZ439SPRZ439676",
            "F28004x": "https://www.ti.com/document-viewer/lit/html/sprz506d#GUID-871D953D-C06E-401D-A107-C0A7DF78E185/TITLE-SPRZ506D"
        },
        check: (adccclkprescaleerrata) => {
            return adccclkprescaleerrata % 2 === 0;
        },
        applicable: (device) => DEVICES_WITH_ADC_FRACTIONAL_DIVIDER_ERRATA.includes(device) && DEVICES_WITH_ADCC.includes(device)
    },
    {
        name: "adcbFractionalDivider",
        displayName: "ADCB Fractional Divider Set",
        peripheral: "adc",
        referenceLink: {
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-8A437E6A-4FD1-4CDE-BB0F-3A433B7BEF10/TITLE-SPRZ439SPRZ439676",
            "F28004x": "https://www.ti.com/document-viewer/lit/html/sprz506d#GUID-871D953D-C06E-401D-A107-C0A7DF78E185/TITLE-SPRZ506D"
        },
        description: {
            "default": "Revisions Affected: 0, A\n\nProblem: Using an odd ADC clock prescale value (fractional divider) causes degraded ADC performance on affected devices. The half-step prescale values (e.g., /2.5, /3.5) produce incorrect ADC sample timing.\n\nWorkaround: Use only even prescale register values (integer divisors: /2, /4, /6, etc.) on F28003x and F28004x."
        },
        check: (adcbclkprescaleerrata) => {
            return adcbclkprescaleerrata % 2 === 0;
        },
        // Correct set: devices with the fractional divider errata AND an ADCB module
        applicable: (device) => DEVICES_WITH_ADC_FRACTIONAL_DIVIDER_ERRATA.includes(device) && DEVICES_WITH_ADCB.includes(device)
    },
    {
        name: "adcaFractionalDivider",
        displayName: "ADCA Fractional Divider Set",
        peripheral: "adc",  // Associated peripheral module
        referenceLink: {
            "F280013x":"https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-2AD7590D-B516-48BA-AB61-C0DC9F09B194/TITLE-SPRZ439SPRZ439676",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-54731D89-E043-44AB-A73D-F6F70AD6168B/TITLE-SPRZ439SPRZ439676",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-8A437E6A-4FD1-4CDE-BB0F-3A433B7BEF10/TITLE-SPRZ439SPRZ439676",
            "F28002x": "https://www.ti.com/document-viewer/lit/html/sprz506d#GUID-871D953D-C06E-401D-A107-C0A7DF78E185/TITLE-SPRZ506D",
            "F28004x": "https://www.ti.com/document-viewer/lit/html/sprz506d#GUID-871D953D-C06E-401D-A107-C0A7DF78E185/TITLE-SPRZ506D"
        },
        check: (adcaclkprescaleerrata) => {
            return adcaclkprescaleerrata % 2 === 0;
        },
        applicable: (device) => DEVICES_WITH_ADC_FRACTIONAL_DIVIDER_ERRATA.includes(device)
    },
    {
        name: "eqep1PositionCounter",
        displayName: "eQEP1 Position Counter Incorrect Reset",
        peripheral: "eqep",  // Associated peripheral module
        referenceLink: {
            "F280013x":"https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-379C7C8A-BEED-4B1B-B1D2-1544117F5D22/TITLE-SPRZ466SPRZ4122012",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-CB9E2FA5-4E20-4F78-81E4-C6224B5057D4/TITLE-SPRZ466SPRZ4122012",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-6A08D2E0-DF53-4158-9D7D-8E2ACFF30168/TITLE-SPRZ466SPRZ4122012",
            "F28002x": "https://www.ti.com/document-viewer/lit/html/sprz506d#GUID-D6360527-89C1-48E0-93F4-B5164B19D8A6/TITLE-SPRZ506D",
            "F28004x": "https://www.ti.com/document-viewer/lit/html/sprz506d#GUID-D6360527-89C1-48E0-93F4-B5164B19D8A6/TITLE-SPRZ506D",
            "F2807x": "https://www.ti.com/document-viewer/lit/html/sprz422k#GUID-569E8518-95F8-464F-9164-7395CB8F9519/TITLE-SPRZ422K",
            "F2837xD": "https://www.ti.com/document-viewer/lit/html/sprz412n#GUID-E454C888-B777-4607-8D9C-924ABC2A5A1A/TITLE-SPRZ412N",
            "F2837xS": "https://www.ti.com/document-viewer/lit/html/sprz423k#GUID-08443729-C880-45A3-A383-D17E4A97691C/TITLE-SPRZ423K",
            "F2838x": "https://www.ti.com/document-viewer/lit/html/sprz413a#GUID-8D2F2B27-1E7D-4FF7-A563-9D0A1B68D5C3/TITLE-SPRZ413A",
            "F28P55x": "https://www.ti.com/document-viewer/lit/html/sprz414a#GUID-A9C4C5A1-64E6-4EE9-B83A-114B1CF2E927/TITLE-SPRZ414A"
        },
        check: (eqep1posctrreset) => {
            return eqep1posctrreset !== 0;
        },
        applicable: (device) => DEVICES_WITH_EQEP_POSITION_ERRATA.includes(device) && DEVICES_WITH_EQEP1.includes(device)
    },
    {
        name: "eqep2PositionCounter",
        displayName: "eQEP2 Position Counter Incorrect Reset",
        peripheral: "eqep",  // Associated peripheral module
        referenceLink: {
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-CB9E2FA5-4E20-4F78-81E4-C6224B5057D4/TITLE-SPRZ466SPRZ4122012",
            "F28002x": "https://www.ti.com/document-viewer/lit/html/sprz506d#GUID-D6360527-89C1-48E0-93F4-B5164B19D8A6/TITLE-SPRZ506D",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-6A08D2E0-DF53-4158-9D7D-8E2ACFF30168/TITLE-SPRZ466SPRZ4122012",
            "F28004x": "https://www.ti.com/document-viewer/lit/html/sprz506d#GUID-D6360527-89C1-48E0-93F4-B5164B19D8A6/TITLE-SPRZ506D",
            "F2807x": "https://www.ti.com/document-viewer/lit/html/sprz422k#GUID-569E8518-95F8-464F-9164-7395CB8F9519/TITLE-SPRZ422K",
            "F2837xD": "https://www.ti.com/document-viewer/lit/html/sprz412n#GUID-E454C888-B777-4607-8D9C-924ABC2A5A1A/TITLE-SPRZ412N",
            "F2837xS": "https://www.ti.com/document-viewer/lit/html/sprz423k#GUID-08443729-C880-45A3-A383-D17E4A97691C/TITLE-SPRZ423K",
            "F2838x": "https://www.ti.com/document-viewer/lit/html/sprz413a#GUID-8D2F2B27-1E7D-4FF7-A563-9D0A1B68D5C3/TITLE-SPRZ413A",
            "F28P55x": "https://www.ti.com/document-viewer/lit/html/sprz414a#GUID-A9C4C5A1-64E6-4EE9-B83A-114B1CF2E927/TITLE-SPRZ414A"
        },
        check: (eqep2posctrreset) => {
            return eqep2posctrreset !== 0;
        },
        applicable: (device) => DEVICES_WITH_EQEP_POSITION_ERRATA.includes(device) && DEVICES_WITH_EQEP2.includes(device)
    },
    {
        name: "mpostNotWorking_F280013x",
        displayName: "Memory Power-On Self-Test Not Executing",
        referenceLink:{
            "F280013x": "https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-B9FBC6EC-F67C-45B1-94C5-912BE4A5F6F7/GUID-F5103B6A-8156-4B90-9969-D51EBE72AE4A"
        },
        check: (otprevisionnumber) => {
            return otprevisionnumber > 2;
        },
        applicable: (device) => {
             return ["F280013x"].includes(device);
        }
    },
    {
        name: "mpostNotWorking_F280015x",
        displayName: "Memory Power-On Self-Test Not Executing",
        referenceLink: {
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-2C414985-15EA-48AF-96C8-73249B17C36B/GUID-F5103B6A-8156-4B90-9969-D51EBE72AE4A"
        },
        check: (otprevisionnumber) => {
            return otprevisionnumber > 1;
        },
        applicable: (device) => {
             return ["F280015x"].includes(device);
        }
    },
    {
        name: "prefetchBeyondValidMemoryM1",
        displayName: "Prefetching Beyond Valid Memory M1",
        referenceLink:  {
            "F280013x": "https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-22BAEE22-C34F-462B-A9E7-AC292157557A/TITLE-SPRZ466SPRZ4588434",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-D0A87E1F-5C47-4AFF-99D1-C79207B1949D/TITLE-SPRZ466SPRZ4588434",
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-6B7E583C-8CD8-45F5-9E92-F131CC34C925/TITLE-SPRZ466SPRZ4588434"
        },
        check: (prefetchboundarym1) => {
            // The boundary register at 0x000007F8 must equal 0.
            // A non-zero value means the CPU fetched beyond the M1 SARAM boundary,
            // which can cause unpredictable execution. The errata workaround patches
            // the OTP to set this register to 0 on boot (via updated OTP revision).
            return prefetchboundarym1 === 0;
        },
        applicable: (device) => DEVICES_WITH_PREFETCH_BOUNDARY_ERRATA.includes(device)
    },
    {
        name: "prefetchBeyondValidMemoryGS3",
        displayName: "Prefetching Beyond Valid Memory GS3",
        referenceLink: {
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-6B7E583C-8CD8-45F5-9E92-F131CC34C925/TITLE-SPRZ466SPRZ4588434"
        },
        check: (prefetchboundarygs3) => {
            // The boundary register at 0x0000FFF8 must equal 0.
            // A non-zero value indicates prefetch extended beyond GS3 SARAM end.
            return prefetchboundarygs3 === 0;
        },
        applicable: (device) => device === "F28003x"
    },
    {
        name: "prefetchValidMemoryFlash",
        displayName: "Prefetching Valid Memory Flash",
        referenceLink: {
            "F28003x": "https://www.ti.com/document-viewer/lit/html/SPRZ496D#GUID-6B7E583C-8CD8-45F5-9E92-F131CC34C925/TITLE-SPRZ466SPRZ4588434"
        },
        check: (prefetchboundaryflash) => {
            // The Flash boundary register at 0x000AFFF0 must equal 0xFFFF (65535).
            // 0xFFFF means the prefetch window covers the full valid Flash address space
            // (boundary is at the top/end of Flash). Any other value indicates the
            // OTP patch was not applied and the boundary may be set incorrectly.
            return prefetchboundaryflash === 0xFFFF;
        },
        applicable: (device) => device === "F28003x"
    },
    {
        name: "pllRefClkMissingFlag",
        displayName: "PLL Reference Clock Missing Flag may be Incorrectly Activated",
        referenceLink: {
            "F280013x": "https://www.ti.com/document-viewer/lit/html/SPRZ506D#GUID-E8CA025A-80E8-4A6C-BD83-C315C6A9D5C0/GUID-6BAFB510-EE9D-4922-A62D-E949A0A8CD84",
            "F280015x": "https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-8CCCB916-7245-43D1-A7D6-938425ED4F73/GUID-6BAFB510-EE9D-4922-A62D-E949A0A8CD84"
        },
        check: (pllrefclklostflag) => {
            return pllrefclklostflag === 0;
        },
        applicable: (device) => DEVICES_WITH_PLL_REFLOST_REG.includes(device)
    },
    {
        name: "lcmCompareError",
        displayName: "LCM Compare Error can be caused by Consecutive Reset Cycles",
        referenceLink: {
            "F280015x":"https://www.ti.com/document-viewer/lit/html/SPRZ507D#GUID-F3608321-4F24-44B2-98E6-2DFF3F8F5811/GUID-7EF13FBF-46F9-43FF-9866-6E290AB1389F"
        },
        check: (sysclkdivsel) => {
            // divValue=1 when sysclkdivsel=0, which triggers the errata
            return sysclkdivsel !== 0;
        },
        applicable: (device) => device === "F280015x"  // device-specific: only F280015x has this errata
    },
    {
        name: "adcdContInterruptNotSet",
        displayName: "ADCD INTxCONT Not Set",
        peripheral: "adc",
        referenceLink: {
            "F2807x": "https://www.ti.com/document-viewer/lit/html/sprz422k#GUID-A1B5F986-F097-4AB6-A611-1F9FB27F0FA2/TITLE-SPRZ422K",
            "F2837xD": "https://www.ti.com/document-viewer/lit/html/sprz412n#GUID-DFB82063-C08D-4C29-A681-491988C2F131/TITLE-SPRZ412N",
            "F2837xS": "https://www.ti.com/document-viewer/lit/html/sprz423k#GUID-5BE20B83-8402-487D-A5D6-1EAAACB9E862/TITLE-SPRZ423K",
            "F2838x": "https://www.ti.com/document-viewer/lit/html/sprz413a#GUID-8B500FB3-20CC-4F53-BEA9-E2C87DA3D6CC/TITLE-SPRZ413A",
            "F28P55x": "https://www.ti.com/document-viewer/lit/html/sprz414a#GUID-C78B20A8-5D35-4EC1-9214-E5D69C95A18C/TITLE-SPRZ414A"
        },
        description: {
            "default": "Revisions Affected: 0, A\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F2807x": "Revisions Affected: 0, A, B, C\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F2837xD": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F2837xS": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F2838x": "Revisions Affected: 0, A\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode.",
            "F28P55x": "Revisions Affected: 0, A\n\nProblem: If INTxCONT=0 in ADCINTSELxNy register, only the first conversion generates an interrupt. Subsequent conversions will not trigger interrupts until the interrupt flag is manually cleared.\n\nWorkaround: Set INTxCONT=1 to enable continuous interrupt mode."
        },
        check: (adcdintsel1, adcdintsel2, adcdintsel3, adcdintsel4, adcdpowerdownerrata) => {
            if (adcdpowerdownerrata === 0) return true;
            return adcdintsel1 !== 0 && adcdintsel2 !== 0 && adcdintsel3 !== 0 && adcdintsel4 !== 0;
        },
        applicable: (device) => DEVICES_WITH_ADCD.includes(device)
    },
    {
        name: "eqep3PositionCounter",
        displayName: "eQEP3 Position Counter Incorrect Reset",
        peripheral: "eqep",
        referenceLink: {
            "F2807x": "https://www.ti.com/document-viewer/lit/html/sprz422k#GUID-569E8518-95F8-464F-9164-7395CB8F9519/TITLE-SPRZ422K",
            "F2837xD": "https://www.ti.com/document-viewer/lit/html/sprz412n#GUID-E454C888-B777-4607-8D9C-924ABC2A5A1A/TITLE-SPRZ412N",
            "F2837xS": "https://www.ti.com/document-viewer/lit/html/sprz422k#GUID-08443729-C880-45A3-A383-D17E4A97691C/TITLE-SPRZ422K",
            "F2838x": "https://www.ti.com/document-viewer/lit/html/sprz458f#GUID-8D2F2B27-1E7D-4FF7-A563-9D0A1B68D5C3/TITLE-SPRZ458F",
            "F28P55x": "https://www.ti.com/document-viewer/lit/html/sprz414a#GUID-A9C4C5A1-64E6-4EE9-B83A-114B1CF2E927/TITLE-SPRZ414A"
        },
        description: {
            "default": "Revisions Affected: 0, A\n\nProblem: When PCRM=0 (reset on index event) and the direction changes during an index pulse, the position counter may reset to an incorrect value. This can cause position tracking errors in bidirectional motion applications.\n\nWorkaround: Set PCRM=1 or PCRM=2 to use maximum position or first index reset modes, or implement software-based position tracking.",
            "F28002x": "Revisions Affected: 0, A\n\nProblem: When PCRM=0 (reset on index event) and the direction changes during an index pulse, the position counter may reset to an incorrect value. This can cause position tracking errors in bidirectional motion applications.\n\nWorkaround: Set PCRM=1 or PCRM=2 to use maximum position or first index reset modes, or implement software-based position tracking.",
            "F28004x": "Revisions Affected: 0, A, B, C\n\nProblem: When PCRM=0 (reset on index event) and the direction changes during an index pulse, the position counter may reset to an incorrect value. This can cause position tracking errors in bidirectional motion applications.\n\nWorkaround: Set PCRM=1 or PCRM=2 to use maximum position or first index reset modes, or implement software-based position tracking.",
            "F2807x": "Revisions Affected: 0, A, B, C\n\nProblem: When PCRM=0 (reset on index event) and the direction changes during an index pulse, the position counter may reset to an incorrect value. This can cause position tracking errors in bidirectional motion applications.\n\nWorkaround: Set PCRM=1 or PCRM=2 to use maximum position or first index reset modes, or implement software-based position tracking.",
            "F2837xD": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: When PCRM=0 (reset on index event) and the direction changes during an index pulse, the position counter may reset to an incorrect value. This can cause position tracking errors in bidirectional motion applications.\n\nWorkaround: Set PCRM=1 or PCRM=2 to use maximum position or first index reset modes, or implement software-based position tracking.",
            "F2837xS": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: When PCRM=0 (reset on index event) and the direction changes during an index pulse, the position counter may reset to an incorrect value. This can cause position tracking errors in bidirectional motion applications.\n\nWorkaround: Set PCRM=1 or PCRM=2 to use maximum position or first index reset modes, or implement software-based position tracking.",
            "F2838x": "Revisions Affected: 0, A\n\nProblem: When PCRM=0 (reset on index event) and the direction changes during an index pulse, the position counter may reset to an incorrect value. This can cause position tracking errors in bidirectional motion applications.\n\nWorkaround: Set PCRM=1 or PCRM=2 to use maximum position or first index reset modes, or implement software-based position tracking.",
            "F28P55x": "Revisions Affected: 0, A\n\nProblem: When PCRM=0 (reset on index event) and the direction changes during an index pulse, the position counter may reset to an incorrect value. This can cause position tracking errors in bidirectional motion applications.\n\nWorkaround: Set PCRM=1 or PCRM=2 to use maximum position or first index reset modes, or implement software-based position tracking."
        },
        check: (eqep3posctrreset) => {
            return eqep3posctrreset !== 0;
        },
        applicable: (device) => DEVICES_WITH_EQEP_POSITION_ERRATA.includes(device) && DEVICES_WITH_EQEP3.includes(device)
    },
    // =========================================================================
    // MCD (Missing Clock Detect) Check
    // Advisory: MCD Should be Disabled When PLL is Enabled
    // Affected: F28P55x, F28P65x, F2838x
    // =========================================================================
    {
        name: "mcdEnabledWithPll",
        displayName: "MCD Enabled While PLL is Active",
        peripheral: "system",
        referenceLink: {
            "F28P55x": "https://www.ti.com/document-viewer/lit/html/sprz572b#GUID-6B6B689D-4427-461F-8166-97F8EB521191/TITLE-SPRZ572B",
            "F28P65x": "https://www.ti.com/document-viewer/lit/html/sprz545d#GUID-6B6B689D-4427-461F-8166-97F8EB521191/TITLE-SPRZ545D",
            "F2838x": "https://www.ti.com/document-viewer/lit/html/sprz458f#GUID-E310A58C-B1D7-4787-B624-4A1C66D1B26C/TITLE-SPRZ458F"
        },
        description: {
            "default": "Revisions Affected: 0, A\n\nProblem: When PLL is enabled (PLLCLKEN=1), the Missing Clock Detect (MCD) circuit may falsely trigger due to clock transitions during PLL lock. This can cause unexpected system resets or NMI interrupts.\n\nWorkaround: Disable MCD by setting MCLKOFF=1 in MCDCR register before enabling PLL, and optionally re-enable after PLL is stable.",
            "F2838x": "Revisions Affected: 0, A\n\nProblem: When PLL is enabled (PLLCLKEN=1), the Missing Clock Detect (MCD) circuit may falsely trigger due to clock transitions during PLL lock. This can cause unexpected system resets or NMI interrupts.\n\nWorkaround: Disable MCD by setting MCLKOFF=1 in MCDCR register before enabling PLL, and optionally re-enable after PLL is stable.",
            "F28P55x": "Revisions Affected: 0, A\n\nProblem: When PLL is enabled (PLLCLKEN=1), the Missing Clock Detect (MCD) circuit may falsely trigger due to clock transitions during PLL lock. This can cause unexpected system resets or NMI interrupts.\n\nWorkaround: Disable MCD by setting MCLKOFF=1 in MCDCR register before enabling PLL, and optionally re-enable after PLL is stable.",
            "F28P65x": "Revisions Affected: 0, A\n\nProblem: When PLL is enabled (PLLCLKEN=1), the Missing Clock Detect (MCD) circuit may falsely trigger due to clock transitions during PLL lock. This can cause unexpected system resets or NMI interrupts.\n\nWorkaround: Disable MCD by setting MCLKOFF=1 in MCDCR register before enabling PLL, and optionally re-enable after PLL is stable."
        },
        check: (mcdenabled, pllclkenabled) => {
            // MCLKOFF=0 means MCD is enabled, PLLCLKEN=1 means PLL is enabled
            return !(mcdenabled === 0 && pllclkenabled === 1);
        },
        applicable: (device) => DEVICES_WITH_MCD_ERRATA.includes(device)
    },
    // =========================================================================
    // DCC Single-Shot Mode Check
    // Advisory: DCC Single-Shot-Mode Operation May End Prematurely
    // Affected: F28004x, F28002x
    // =========================================================================
    {
        name: "dccSingleShotMode",
        displayName: "DCC Single-Shot Mode May End Prematurely",
        peripheral: "dcc",
        referenceLink: {
            "F28002x": "https://www.ti.com/document-viewer/lit/html/sprz506d#GUID-7109C6C8-3232-481B-A35A-A4B03BF19DCE/TITLE-SPRZ506D",
            "F28004x": "https://www.ti.com/document-viewer/lit/html/sprz506d#GUID-7109C6C8-3232-481B-A35A-A4B03BF19DCE/TITLE-SPRZ506D"
        },
        description: {
            "default": "Revisions Affected: 0, A\n\nProblem: In single-shot mode, the DCC comparison may terminate before counter0 and counter1 reach their target values, leading to incorrect frequency measurement or validation results.\n\nWorkaround: Use continuous mode (SINGLESHOT=0) instead of single-shot mode for reliable clock comparison.",
            "F28002x": "Revisions Affected: 0, A\n\nProblem: In single-shot mode, the DCC comparison may terminate before counter0 and counter1 reach their target values, leading to incorrect frequency measurement or validation results.\n\nWorkaround: Use continuous mode (SINGLESHOT=0) instead of single-shot mode for reliable clock comparison.",
            "F28004x": "Revisions Affected: 0, A, B, C\n\nProblem: In single-shot mode, the DCC comparison may terminate before counter0 and counter1 reach their target values, leading to incorrect frequency measurement or validation results.\n\nWorkaround: Use continuous mode (SINGLESHOT=0) instead of single-shot mode for reliable clock comparison."
        },
        check: (dcc0singleshot, dcc0enabled) => {
            // Issue exists when DCC is enabled AND single-shot mode is active
            return !(dcc0enabled === 1 && dcc0singleshot === 1);
        },
        applicable: (device) => DEVICES_WITH_DCC_SINGLESHOT_ERRATA.includes(device)
    },
    // =========================================================================
    // SDFM Manchester Mode Check
    // Advisory: SDFM Manchester Mode (Mode 2) Does Not Produce Correct Results
    // Affected: F28004x, F2807x, F2837xD, F2837xS
    // =========================================================================
    {
        name: "sdfmManchesterMode",
        displayName: "SDFM Manchester Mode Incorrect Results",
        peripheral: "sdfm",
        referenceLink: {
            "F28004x": "https://www.ti.com/document-viewer/lit/html/sprz506d#GUID-DF753B81-5540-41B6-8EA6-E60E9D6FA351/TITLE-SPRZ506D",
            "F2807x": "https://www.ti.com/document-viewer/lit/html/sprz422k#GUID-C07E430A-D834-4B05-9C35-3ADF7E43B807/TITLE-SPRZ422K",
            "F2837xD": "https://www.ti.com/document-viewer/lit/html/sprz412n#GUID-44B2F6BA-66B5-4822-8119-E94302F91217/TITLE-SPRZ412N",
            "F2837xS": "https://www.ti.com/document-viewer/lit/html/sprz423k#GUID-BEC31169-B9FE-484F-B9E1-663692EE30D1/TITLE-SPRZ423K"
        },
        description: {
            "default": "Revisions Affected: 0, A, B, C\n\nProblem: When SDFM is configured for Manchester-encoded data (Mode 2, clock embedded in data stream), the filter produces incorrect output values. This affects applications using sigma-delta modulators with Manchester encoding.\n\nWorkaround: Use Mode 0 (separate clock/data) or Mode 1 (clock recovered from data edges) instead of Manchester mode.",
            "F28004x": "Revisions Affected: 0, A, B, C\n\nProblem: When SDFM is configured for Manchester-encoded data (Mode 2, clock embedded in data stream), the filter produces incorrect output values. This affects applications using sigma-delta modulators with Manchester encoding.\n\nWorkaround: Use Mode 0 (separate clock/data) or Mode 1 (clock recovered from data edges) instead of Manchester mode.",
            "F2807x": "Revisions Affected: 0, A, B, C\n\nProblem: When SDFM is configured for Manchester-encoded data (Mode 2, clock embedded in data stream), the filter produces incorrect output values. This affects applications using sigma-delta modulators with Manchester encoding.\n\nWorkaround: Use Mode 0 (separate clock/data) or Mode 1 (clock recovered from data edges) instead of Manchester mode.",
            "F2837xD": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: When SDFM is configured for Manchester-encoded data (Mode 2, clock embedded in data stream), the filter produces incorrect output values. This affects applications using sigma-delta modulators with Manchester encoding.\n\nWorkaround: Use Mode 0 (separate clock/data) or Mode 1 (clock recovered from data edges) instead of Manchester mode.",
            "F2837xS": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: When SDFM is configured for Manchester-encoded data (Mode 2, clock embedded in data stream), the filter produces incorrect output values. This affects applications using sigma-delta modulators with Manchester encoding.\n\nWorkaround: Use Mode 0 (separate clock/data) or Mode 1 (clock recovered from data edges) instead of Manchester mode."
        },
        check: (sdfm1filter1mode, sdfm1enabled) => {
            // Mode 2 = Manchester mode, issue when enabled
            return !(sdfm1enabled === 1 && sdfm1filter1mode === 2);
        },
        applicable: (device) => DEVICES_WITH_SDFM_MANCHESTER_ERRATA.includes(device)
    },
    // =========================================================================
    // ePWM Dead-Band Delay Check
    // Advisory: ePWM Dead-Band Delay Cannot be Set to 0 with Shadow Load
    // Affected: F2807x, F2837xD, F2837xS
    // =========================================================================
    {
        name: "epwmDeadbandZeroShadow",
        displayName: "ePWM Dead-Band Delay 0 with Shadow Load",
        peripheral: "epwm",
        referenceLink: {
            "F2807x": "https://www.ti.com/document-viewer/lit/html/sprz423k#GUID-4176D2F3-9DBD-420D-939B-D89D1980B02A/TITLE-SPRZ423K",
            "F2837xD": "https://www.ti.com/document-viewer/lit/html/sprz412n#GUID-78CA7DFE-D4D3-44AC-B4B1-A3C057728957/TITLE-SPRZ412N",
            "F2837xS": "https://www.ti.com/document-viewer/lit/html/sprz422k#GUID-ECACADCA-A6DE-43E1-9F0A-E436E2E11E76/TITLE-SPRZ422K"
        },
        description: {
            "default": "Revisions Affected: 0, A, B, C\n\nProblem: When using shadow load mode (LOADREDMODE/LOADFEDMODE != 0), writing 0 to DBRED or DBFED registers does not take effect. The dead-band delay remains at the previous non-zero value.\n\nWorkaround: Use immediate load mode (LOADREDMODE=0, LOADFEDMODE=0) when setting dead-band delay to zero.",
            "F2807x": "Revisions Affected: 0, A, B, C\n\nProblem: When using shadow load mode (LOADREDMODE/LOADFEDMODE != 0), writing 0 to DBRED or DBFED registers does not take effect. The dead-band delay remains at the previous non-zero value.\n\nWorkaround: Use immediate load mode (LOADREDMODE=0, LOADFEDMODE=0) when setting dead-band delay to zero.",
            "F2837xD": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: When using shadow load mode (LOADREDMODE/LOADFEDMODE != 0), writing 0 to DBRED or DBFED registers does not take effect. The dead-band delay remains at the previous non-zero value.\n\nWorkaround: Use immediate load mode (LOADREDMODE=0, LOADFEDMODE=0) when setting dead-band delay to zero.",
            "F2837xS": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: When using shadow load mode (LOADREDMODE/LOADFEDMODE != 0), writing 0 to DBRED or DBFED registers does not take effect. The dead-band delay remains at the previous non-zero value.\n\nWorkaround: Use immediate load mode (LOADREDMODE=0, LOADFEDMODE=0) when setting dead-band delay to zero."
        },
        check: (epwm1dbctlloadredmode, epwm1dbctlloadfedmode, epwm1dbred, epwm1dbfed) => {
            // Issue when shadow mode is used (LOADxMODE != 0) AND delay is 0
            return !((epwm1dbctlloadredmode !== 0 && epwm1dbred === 0) ||
                     (epwm1dbctlloadfedmode !== 0 && epwm1dbfed === 0));
        },
        applicable: (device) => DEVICES_WITH_EPWM_DEADBAND_ERRATA.includes(device)
    },
    // =========================================================================
    // CMPSS Latch Clear Check
    // Advisory: COMPxLATCH May Not Clear Properly Under Certain Conditions
    // Affected: F28004x, F2807x, F2837xD, F2837xS, F28P55x
    // =========================================================================
    {
        name: "cmpssLatchClear",
        displayName: "CMPSS Latch Clear Issue Present",
        peripheral: "cmpss",
        referenceLink: {
            "F28004x": "https://www.ti.com/document-viewer/lit/html/sprz506d#GUID-E0C82E91-F5AD-408A-9F6E-6962CD3D1D89/TITLE-SPRZ506D",
            "F2807x": "https://www.ti.com/document-viewer/lit/html/sprz422k#GUID-3E1491A6-E573-49F0-9F48-F78D34B4828F/TITLE-SPRZ422K",
            "F2837xD": "https://www.ti.com/document-viewer/lit/html/sprz412n#GUID-3191854F-5560-48A3-A9B9-0E6D57388D6F/TITLE-SPRZ412N",
            "F2837xS": "https://www.ti.com/document-viewer/lit/html/sprz423k#GUID-70999F8C-691F-4399-A18B-686EC050770F/TITLE-SPRZ423K",
            "F28P55x": "https://www.ti.com/document-viewer/lit/html/sprz414a#GUID-6D02A3EA-3617-401D-A89B-8DCB0295B099/TITLE-SPRZ414A"
        },
        description: {
            "default": "Revisions Affected: 0, A, B, C\n\nProblem: The comparator latch (COMPHSTS/COMPLSTS) may not clear when software writes to the COMPHSTCLR/COMPLSTCLR bits if the comparator output is still active at the time of the clear.\n\nWorkaround: Ensure comparator output is inactive (hysteresis may help) before clearing latch, or configure latch to clear on EPWMSYNCPER using COMPHSCLR/COMPLSCLR bits.",
            "F28004x": "Revisions Affected: 0, A, B, C\n\nProblem: The comparator latch (COMPHSTS/COMPLSTS) may not clear when software writes to the COMPHSTCLR/COMPLSTCLR bits if the comparator output is still active at the time of the clear.\n\nWorkaround: Ensure comparator output is inactive (hysteresis may help) before clearing latch, or configure latch to clear on EPWMSYNCPER using COMPHSCLR/COMPLSCLR bits.",
            "F2807x": "Revisions Affected: 0, A, B, C\n\nProblem: The comparator latch (COMPHSTS/COMPLSTS) may not clear when software writes to the COMPHSTCLR/COMPLSTCLR bits if the comparator output is still active at the time of the clear.\n\nWorkaround: Ensure comparator output is inactive (hysteresis may help) before clearing latch, or configure latch to clear on EPWMSYNCPER using COMPHSCLR/COMPLSCLR bits.",
            "F2837xD": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: The comparator latch (COMPHSTS/COMPLSTS) may not clear when software writes to the COMPHSTCLR/COMPLSTCLR bits if the comparator output is still active at the time of the clear.\n\nWorkaround: Ensure comparator output is inactive (hysteresis may help) before clearing latch, or configure latch to clear on EPWMSYNCPER using COMPHSCLR/COMPLSCLR bits.",
            "F2837xS": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: The comparator latch (COMPHSTS/COMPLSTS) may not clear when software writes to the COMPHSTCLR/COMPLSTCLR bits if the comparator output is still active at the time of the clear.\n\nWorkaround: Ensure comparator output is inactive (hysteresis may help) before clearing latch, or configure latch to clear on EPWMSYNCPER using COMPHSCLR/COMPLSCLR bits.",
            "F28P55x": "Revisions Affected: 0, A\n\nProblem: The comparator latch (COMPHSTS/COMPLSTS) may not clear when software writes to the COMPHSTCLR/COMPLSTCLR bits if the comparator output is still active at the time of the clear.\n\nWorkaround: Ensure comparator output is inactive (hysteresis may help) before clearing latch, or configure latch to clear on EPWMSYNCPER using COMPHSCLR/COMPLSCLR bits."
        },
        check: (cmpss1highlatch, cmpss1lowlatch) => {
            // FAIL (warn) if either comparator latch is currently set.
            // A set latch on an affected device may indicate the clear did not take effect
            // (the errata: COMPHSTCLR/COMPLSTCLR write is ignored when comparator output
            // is still active). User should verify the latch clears as expected.
            return !(cmpss1highlatch === 1 || cmpss1lowlatch === 1);
        },
        applicable: (device) => DEVICES_WITH_CMPSS_LATCH_ERRATA.includes(device)
    },
    // =========================================================================
    // CMPSS Ramp Generator Check
    // Advisory: CMPSS Ramp Generator May Not Start Under Certain Conditions
    // Affected: F2807x, F2837xD, F2837xS
    // =========================================================================
    {
        name: "cmpssRampStart",
        displayName: "CMPSS Ramp Generator Issue Present",
        peripheral: "cmpss",
        referenceLink: {
            "F2807x": "https://www.ti.com/document-viewer/lit/html/sprz423k#GUID-1A85EC26-1666-42B0-937B-8CCF51567964/TITLE-SPRZ423K",
            "F2837xD": "https://www.ti.com/document-viewer/lit/html/sprz412n#GUID-45BB716E-93EA-461B-9B5D-05394A0CDB4B/TITLE-SPRZ412N",
            "F2837xS": "https://www.ti.com/document-viewer/lit/html/sprz422k#GUID-3740F7B9-8C27-4188-91FA-3469B73A1FD9/TITLE-SPRZ422K"
        },
        description: {
            "default": "Revisions Affected: 0, A, B, C\n\nProblem: The CMPSS ramp generator may fail to start if the ramp is triggered before RAMPMAXREFA/RAMPMAXREFS and RAMPDECVALA/RAMPDECVALS are properly configured with non-zero values.\n\nWorkaround: Ensure RAMPMAXREF > 0 and RAMPDECVAL > 0 before enabling the ramp generator, and configure ramp parameters before the first sync pulse.",
            "F2807x": "Revisions Affected: 0, A, B, C\n\nProblem: The CMPSS ramp generator may fail to start if the ramp is triggered before RAMPMAXREFA/RAMPMAXREFS and RAMPDECVALA/RAMPDECVALS are properly configured with non-zero values.\n\nWorkaround: Ensure RAMPMAXREF > 0 and RAMPDECVAL > 0 before enabling the ramp generator, and configure ramp parameters before the first sync pulse.",
            "F2837xD": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: The CMPSS ramp generator may fail to start if the ramp is triggered before RAMPMAXREFA/RAMPMAXREFS and RAMPDECVALA/RAMPDECVALS are properly configured with non-zero values.\n\nWorkaround: Ensure RAMPMAXREF > 0 and RAMPDECVAL > 0 before enabling the ramp generator, and configure ramp parameters before the first sync pulse.",
            "F2837xS": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: The CMPSS ramp generator may fail to start if the ramp is triggered before RAMPMAXREFA/RAMPMAXREFS and RAMPDECVALA/RAMPDECVALS are properly configured with non-zero values.\n\nWorkaround: Ensure RAMPMAXREF > 0 and RAMPDECVAL > 0 before enabling the ramp generator, and configure ramp parameters before the first sync pulse."
        },
        check: (cmpss1rampstatus) => {
            // FAIL (warn) if the CMPSS1 high comparator latch is set on a device
            // affected by the ramp-start errata. The ramp generator may have triggered
            // a false trip if the latch is set unexpectedly.
            // Workaround: configure RAMPMAXREF > 0 and RAMPDECVAL > 0 before enabling.
            return cmpss1rampstatus === 0;
        },
        applicable: (device) => DEVICES_WITH_CMPSS_RAMP_ERRATA.includes(device)
    },
    // =========================================================================
    // I2C Open-Drain Buffer Check
    // Advisory: I2C SDA and SCL Open-Drain Output Buffer Issue
    // Affected: F28004x, F2807x, F2837xD, F2837xS
    // =========================================================================
    {
        name: "i2cOpenDrainBuffer",
        displayName: "I2C Open-Drain Buffer Issue Present",
        peripheral: "i2c",
        referenceLink: {
            "F28004x": "https://www.ti.com/document-viewer/lit/html/sprz506d#GUID-A32361DA-E87E-4643-BA7A-1E46D1F63B28/TITLE-SPRZ506D",
            "F2807x": "https://www.ti.com/document-viewer/lit/html/sprz422k#GUID-BD33CC8C-B197-43F4-817F-664E1EB182E4/TITLE-SPRZ422K",
            "F2837xD": "https://www.ti.com/document-viewer/lit/html/sprz412n#GUID-4DE24DBD-1D40-4399-A447-27B9D72A03D0/TITLE-SPRZ412N",
            "F2837xS": "https://www.ti.com/document-viewer/lit/html/sprz423k#GUID-C8E1F880-EBEE-4159-A6C4-2A6138F5E876/TITLE-SPRZ423K"
        },
        description: {
            "default": "Revisions Affected: 0, A, B, C\n\nProblem: The I2C SDA and SCL open-drain output buffers may not properly release the bus lines under certain electrical conditions, potentially causing bus contention or communication failures.\n\nWorkaround: Use appropriate external pull-up resistor values (typically 2.2k-10k ohm depending on bus capacitance) and ensure proper bus termination.",
            "F28004x": "Revisions Affected: 0, A, B, C\n\nProblem: The I2C SDA and SCL open-drain output buffers may not properly release the bus lines under certain electrical conditions, potentially causing bus contention or communication failures.\n\nWorkaround: Use appropriate external pull-up resistor values (typically 2.2k-10k ohm depending on bus capacitance) and ensure proper bus termination.",
            "F2807x": "Revisions Affected: 0, A, B, C\n\nProblem: The I2C SDA and SCL open-drain output buffers may not properly release the bus lines under certain electrical conditions, potentially causing bus contention or communication failures.\n\nWorkaround: Use appropriate external pull-up resistor values (typically 2.2k-10k ohm depending on bus capacitance) and ensure proper bus termination.",
            "F2837xD": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: The I2C SDA and SCL open-drain output buffers may not properly release the bus lines under certain electrical conditions, potentially causing bus contention or communication failures.\n\nWorkaround: Use appropriate external pull-up resistor values (typically 2.2k-10k ohm depending on bus capacitance) and ensure proper bus termination.",
            "F2837xS": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: The I2C SDA and SCL open-drain output buffers may not properly release the bus lines under certain electrical conditions, potentially causing bus contention or communication failures.\n\nWorkaround: Use appropriate external pull-up resistor values (typically 2.2k-10k ohm depending on bus capacitance) and ensure proper bus termination."
        },
        check: (i2camodemaster, i2caenabled) => {
            // FAIL (warn) when I2C is enabled AND in master mode on an affected device.
            // The open-drain buffer issue can affect SDA/SCL line release in master mode.
            // Workaround: use correct external pull-up resistor values (2.2k–10k Ω).
            return !(i2camodemaster === 1 && i2caenabled === 1);
        },
        applicable: (device) => DEVICES_WITH_I2C_OPENDRAIN_ERRATA.includes(device)
    },
    // =========================================================================
    // Flash ECC Error Interrupt Check
    // Advisory: Flash Single-Bit ECC Error Interrupt is Not Generated
    // Affected: F28P55x, F28P65x
    // =========================================================================
    {
        name: "flashEccInterrupt",
        displayName: "Flash ECC Error Interrupt Not Generated",
        peripheral: "flash",
        referenceLink: {
            "F28P55x": "https://www.ti.com/document-viewer/lit/html/sprz572b#GUID-153889C9-2161-4196-9279-F0F85095CF06/TITLE-SPRZ572B",
            "F28P65x": "https://www.ti.com/document-viewer/lit/html/sprz545d#GUID-3F1573D5-6AE8-4D21-9C36-85A8ECDEC917/TITLE-SPRZ545D"
        },
        description: {
            "default": "Revisions Affected: 0, A\n\nProblem: When a single-bit ECC error is detected during Flash read, the correctable error interrupt (FLASH_CORR_ERR) is not generated, though the error is still corrected by hardware. Applications relying on this interrupt for error logging will miss events.\n\nWorkaround: Periodically poll the Flash ECC status registers (ERR_STATUS, SINGLE_ERR_ADDR_LOW/HIGH) to detect and log correctable errors.",
            "F28P55x": "Revisions Affected: 0, A\n\nProblem: When a single-bit ECC error is detected during Flash read, the correctable error interrupt (FLASH_CORR_ERR) is not generated, though the error is still corrected by hardware. Applications relying on this interrupt for error logging will miss events.\n\nWorkaround: Periodically poll the Flash ECC status registers (ERR_STATUS, SINGLE_ERR_ADDR_LOW/HIGH) to detect and log correctable errors.",
            "F28P65x": "Revisions Affected: 0, A\n\nProblem: When a single-bit ECC error is detected during Flash read, the correctable error interrupt (FLASH_CORR_ERR) is not generated, though the error is still corrected by hardware. Applications relying on this interrupt for error logging will miss events.\n\nWorkaround: Periodically poll the Flash ECC status registers (ERR_STATUS, SINGLE_ERR_ADDR_LOW/HIGH) to detect and log correctable errors."
        },
        check: (flasheccenabled) => {
            // FAIL (warn) when Flash ECC is enabled on an affected device.
            // The errata: single-bit ECC error interrupt is NOT generated even though
            // the hardware corrects the error. Applications relying on this interrupt
            // for error logging will silently miss events.
            // Workaround: periodically poll Flash ECC status registers (ERR_STATUS,
            // SINGLE_ERR_ADDR_LOW/HIGH) when ECC is enabled on F28P55x/F28P65x.
            return flasheccenabled === 0;
        },
        applicable: (device) => DEVICES_WITH_FLASH_ECC_ERRATA.includes(device)
    },
    // =========================================================================
    // PLL Lock Check
    // Advisory: PLL May Not Lock on the First Lock Attempt
    // Affected: F28004x, F2807x, F2837xD, F2837xS
    // =========================================================================
    {
        name: "pllFirstLockAttempt",
        displayName: "PLL May Not Lock on First Attempt",
        peripheral: "system",
        referenceLink: {
            "F28004x": "https://www.ti.com/document-viewer/lit/html/sprz506d#GUID-38116E66-13FB-41F1-A894-B53A6B30D28B/TITLE-SPRZ506D",
            "F2807x": "https://www.ti.com/document-viewer/lit/html/sprz422k#GUID-5E654302-5BA1-454E-AB59-6B3966D3E3ED/TITLE-SPRZ422K",
            "F2837xD": "https://www.ti.com/document-viewer/lit/html/sprz412n#GUID-A1B74AC8-1F96-478C-9C97-A4A4427F71E6/TITLE-SPRZ412N",
            "F2837xS": "https://www.ti.com/document-viewer/lit/html/sprz423k#GUID-99E0F6F9-5656-4217-A361-CD8A6F55E7F4/TITLE-SPRZ423K"
        },
        description: {
            "default": "Revisions Affected: 0, A, B, C\n\nProblem: The PLL may fail to achieve lock on the first enable attempt, particularly after power-on reset or when switching clock sources.\n\nWorkaround: Implement retry logic by monitoring PLLSTS.PLLLOCKS bit and re-enabling the PLL if lock is not achieved within the expected timeout. The driverlib SysCtl_setClock() function handles this automatically with built-in retry logic.",
            "F28004x": "Revisions Affected: 0, A, B, C\n\nProblem: The PLL may fail to achieve lock on the first enable attempt, particularly after power-on reset or when switching clock sources.\n\nWorkaround: Implement retry logic by monitoring PLLSTS.PLLLOCKS bit and re-enabling the PLL if lock is not achieved within the expected timeout. The driverlib SysCtl_setClock() function handles this automatically with built-in retry logic.",
            "F2807x": "Revisions Affected: 0, A, B, C\n\nProblem: The PLL may fail to achieve lock on the first enable attempt, particularly after power-on reset or when switching clock sources.\n\nWorkaround: Implement retry logic by monitoring PLLSTS.PLLLOCKS bit and re-enabling the PLL if lock is not achieved within the expected timeout. The driverlib SysCtl_setClock() function handles this automatically with built-in retry logic.",
            "F2837xD": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: The PLL may fail to achieve lock on the first enable attempt, particularly after power-on reset or when switching clock sources.\n\nWorkaround: Implement retry logic by monitoring PLLSTS.PLLLOCKS bit and re-enabling the PLL if lock is not achieved within the expected timeout. The driverlib SysCtl_setClock() function handles this automatically with built-in retry logic.",
            "F2837xS": "Revisions Affected: 0, A, B, C, D, E, F, G\n\nProblem: The PLL may fail to achieve lock on the first enable attempt, particularly after power-on reset or when switching clock sources.\n\nWorkaround: Implement retry logic by monitoring PLLSTS.PLLLOCKS bit and re-enabling the PLL if lock is not achieved within the expected timeout. The driverlib SysCtl_setClock() function handles this automatically with built-in retry logic."
        },
        check: (plllockstatus) => {
            // FAIL (warn) if PLL is currently not locked on an affected device.
            // The errata: PLL may fail to lock on the first attempt after power-on
            // or clock source switch. A value of 0 (not locked) at runtime may
            // indicate the errata occurred and the retry did not complete.
            // Workaround: driverlib SysCtl_setClock() includes built-in retry logic.
            return plllockstatus === 1;
        },
        applicable: (device) => DEVICES_WITH_PLL_LOCK_ERRATA.includes(device)
    }
]

/**
 * Module exports for errata clinic functionality.
 * These are consumed by the GUI template (index.js.xdt) to generate
 * device-specific errata checking code.
 *
 * @exports errataPrereqMemoryLocs - Memory locations to read
 * @exports errataPrereqRegisters - Device registers to read
 * @exports memoryValueCalculators - Functions to process memory values
 * @exports errataChecks - The errata advisory checks
 */
exports = {
    errataPrereqMemoryLocs: errataPrereqMemoryLocs,
    errataPrereqRegisters: errataPrereqRegisters,
    memoryValueCalculators: memoryValueCalculators,
    errataChecks: errataChecks
} 