//=============================================================================
// Device Constants - Import from centralized module
//=============================================================================
const {
    // Device Families
    DEVICES_GEN2,
    DEVICES_GEN3,
    DEVICES_WITH_CDT_SUPPORT,
    // PLL Architecture
    DEVICES_WITH_PLLCR_DIV,  // Gen2 PLL
    DEVICES_WITH_REFDIV_ODIV,
    DEVICES_WITH_FMULT,
    DEVICES_WITH_FMULT_ODIV,
    // SYSCLK Frequency Groups - Gen2
    DEVICES_40MHZ,
    DEVICES_60MHZ_GEN2,
    DEVICES_90MHZ,
    // SYSCLK Frequency Groups - Gen3
    DEVICES_100MHZ,
    DEVICES_120MHZ,
    DEVICES_150MHZ,
    DEVICES_200MHZ,
    // ADC - Gen2
    DEVICES_GEN2_WITH_ADC,
    DEVICES_ADC_GEN2_PRESCALE,
    // ADC - Gen3
    DEVICES_WITH_ADCA,
    DEVICES_WITH_ADCB,
    DEVICES_WITH_ADCC,
    DEVICES_WITH_ADCD,
    DEVICES_WITH_ADCE,
    DEVICES_ADC_INTEGER_PRESCALE,
    DEVICES_ADC_HALFSTEP_PRESCALE,
    // Gen2 Peripherals
    DEVICES_GEN2_WITH_HRPWM,
    // Clock Features
    DEVICES_WITH_AUXPLL,
    DEVICES_WITH_EPWMCLKDIV,
    DEVICES_WITH_HRPWM,
    // Communication
    DEVICES_WITH_MCAN,
    DEVICES_WITH_MCAN_AUXCLKIN,
    DEVICES_WITH_CANA,
    DEVICES_WITH_CANB,
    // Helper Functions
    getMaxSysclk
} = system.getScript("./device_constants.js");

//=============================================================================
// Clocking-Specific Helper Functions
//=============================================================================

/**
 * Convert FMULT register value to fractional multiplier.
 * Reference: driverlib/f2837xd/driverlib/sysctl.h
 * @param {number} fmultReg - FMULT register value (0-3)
 * @returns {number} Fractional value (0.0, 0.25, 0.5, 0.75) or NaN if invalid
 */
function calcFmultValue(fmultReg) {
    switch (fmultReg) {
        case 0: return 0.0;
        case 1: return 0.25;
        case 2: return 0.5;
        case 3: return 0.75;
        default:
            console.warn("Warning: Invalid FMULT value: " + fmultReg + " (valid: 0-3)");
            return NaN;
    }
}

/**
 * Validate IMULT register value.
 * Reference: SYSPLLMULT.IMULT field is typically 7 bits (0-127)
 * @param {number} imult - IMULT register value
 * @returns {boolean} True if valid, false if out of range
 */
function validateImult(imult) {
    if (imult < 0 || imult > 127) {
        console.warn("Warning: IMULT value " + imult + " out of range (0-127)");
        return false;
    }
    if (imult === 0) {
        console.warn("Warning: IMULT=0 disables PLL output");
    }
    return true;
}

/**
 * Validate REFDIV register value.
 * Reference: SYSPLLMULT.REFDIV is typically 5 bits (0-31)
 * @param {number} refdiv - REFDIV register value
 * @returns {boolean} True if valid, false if out of range
 */
function validateRefdiv(refdiv) {
    if (refdiv < 0 || refdiv > 31) {
        console.warn("Warning: REFDIV value " + refdiv + " out of range (0-31)");
        return false;
    }
    return true;
}

/**
 * Validate ODIV register value.
 * Reference: SYSPLLMULT.ODIV is typically 5 bits (0-31)
 * @param {number} odiv - ODIV register value
 * @returns {boolean} True if valid, false if out of range
 */
function validateOdiv(odiv) {
    if (odiv < 0 || odiv > 31) {
        console.warn("Warning: ODIV value " + odiv + " out of range (0-31)");
        return false;
    }
    return true;
}

/**
 * Validate SYSCLKDIVSEL register value.
 * Reference: SYSCLKDIVSEL.PLLSYSCLKDIV is typically 6 bits (0-63)
 * @param {number} divsel - SYSCLKDIVSEL register value
 * @returns {boolean} True if valid, false if out of range
 */
function validateSysclkdivsel(divsel) {
    if (divsel < 0 || divsel > 63) {
        console.warn("Warning: SYSCLKDIVSEL value " + divsel + " out of range (0-63)");
        return false;
    }
    return true;
}

/**
 * Calculate ADC prescale divider from register value.
 * Reference: driverlib/<device>/driverlib/adc.h, ADC_ClkPrescale enum
 * Prescale register to divider mapping:
 *   0 -> /1, 2 -> /2, 3 -> /2.5 (half-step only), 4 -> /3, etc.
 * Max valid register values per ADC_ClkPrescale enum:
 *   Integer-only devices (F280013x-F28004x): 14 = ADC_CLK_DIV_8_0 (→ /8.0)
 *   Half-step devices   (F2807x+)          : 14 = ADC_CLK_DIV_8_0 (→ /8.0) typical;
 *                                           16 = ADC_CLK_DIV_9_0  (→ /9.0) on some devices
 * @param {number} prescaleReg - ADC prescale register value
 * @param {string} [device] - Device name for validation (optional)
 * @returns {number} Prescale divider value, or NaN if invalid
 */
function calcAdcPrescaleValue(prescaleReg, device) {
    // Value 1 is reserved/invalid on all devices
    if (prescaleReg === 1) {
        console.warn("Warning: Invalid ADC prescale value: 1 (reserved)");
        return NaN;
    }
    // Upper-bound guard: max valid ADC_ClkPrescale register value is 16
    // (ADC_CLK_DIV_9_0 on extended devices). Values > 16 are out-of-spec.
    if (prescaleReg > 16) {
        console.warn("Warning: ADC prescale " + prescaleReg + " exceeds max valid register value (16)");
        return NaN;
    }
    // Integer-only devices don't support odd prescale values (except 0)
    // Only validate if device is known; if unknown, compute value anyway
    if (device && DEVICES_ADC_INTEGER_PRESCALE.includes(device)) {
        if (prescaleReg !== 0 && prescaleReg % 2 !== 0) {
            console.warn("Warning: ADC prescale " + prescaleReg + " (odd) not supported on " + device);
            // Still compute the value for display, but mark as potentially invalid
        }
    }
    if (prescaleReg === 0) return 1.0;
    if (prescaleReg === 2) return 2.0;
    // Formula: divider = ((prescaleReg - 2) * 0.5) + 2
    // e.g., 4 -> 3.0, 5 -> 3.5, 6 -> 4.0, ..., 14 -> 8.0, 16 -> 9.0
    return ((prescaleReg - 2.0) * 0.5) + 2.0;
}

/**
 * Safe division with zero/invalid divisor protection.
 * Returns dividend if divisor is invalid (0, negative, NaN, Infinity).
 * This helper consolidates repeated division-by-zero checks.
 * @param {number} dividend - Value to divide
 * @param {number} divisor - Value to divide by
 * @param {number} [fallbackDivisor=1] - Divisor to use if original is invalid
 * @returns {number} Result of safe division
 */
function safeDiv(dividend, divisor, fallbackDivisor = 1) {
    if (!divisor || divisor <= 0 || !Number.isFinite(divisor)) {
        console.warn("clocking_clinic: safeDiv received invalid divisor " + divisor + ", using fallback " + fallbackDivisor);
        return dividend / fallbackDivisor;
    }
    return dividend / divisor;
}

//=============================================================================
// Prerequisite Registers
//=============================================================================
const prereqRegisters = [
    //-------------------------------------------------------------------------
    // Gen2 PLL Registers (SysCtrlRegs - F2802x, F2803x, F2805x, F2806x)
    //-------------------------------------------------------------------------
    {
        description: "Gen2 PLLCR DIV",
        register: "SysCtrlRegs.PLLCR.DIV",
        name: "pllcrdiv",
        applicable: (device) => DEVICES_WITH_PLLCR_DIV.includes(device)
    },
    {
        description: "Gen2 PLLSTS DIVSEL",
        register: "SysCtrlRegs.PLLSTS.DIVSEL",
        name: "pllstsdivsel",
        applicable: (device) => DEVICES_WITH_PLLCR_DIV.includes(device)
    },
    {
        description: "Gen2 PLL Lock Status",
        register: "SysCtrlRegs.PLLSTS.PLLLOCKS",
        name: "pllstslocks",
        // Note: PLLLOCKS is read here for runtime visibility. It is not used in
        // clock frequency calculations (SYSCLK is derived purely from PLLCR.DIV
        // and PLLSTS.DIVSEL). The lock status feeds errata_clinic.js for the
        // Gen2 PLL DIVSEL sequence check (gen2PllDivselSequence).
        applicable: (device) => DEVICES_WITH_PLLCR_DIV.includes(device)
    },
    {
        description: "Gen2 LSPCLK DIV",
        register: "SysCtrlRegs.LOSPCP.LSPCLK",
        name: "gen2lspclkdiv",
        applicable: (device) => DEVICES_WITH_PLLCR_DIV.includes(device)
    },
    {
        description: "Gen2 ADC CLKDIV2EN",
        register: "AdcRegs.ADCCTL2.CLKDIV2EN",
        name: "gen2adcclkdiv2en",
        applicable: (device) => DEVICES_ADC_GEN2_PRESCALE.includes(device)
    },
    {
        description: "Gen2 ADC CLKDIV4EN",
        register: "AdcRegs.ADCCTL2.CLKDIV4EN",
        name: "gen2adcclkdiv4en",
        applicable: (device) => DEVICES_ADC_GEN2_PRESCALE.includes(device)
    },
    //-------------------------------------------------------------------------
    // Gen3 PLL Registers (ClkCfgRegs)
    //-------------------------------------------------------------------------
    {
        description: "OSCCLK Source Select",
        register: "ClkCfgRegs.CLKSRCCTL1.OSCCLKSRCSEL",
        name: "oscclksrcsel",
        applicable: (device) => DEVICES_GEN3.includes(device)
    },
    {
        description: "SYSPLL IMULT",
        register: "ClkCfgRegs.SYSPLLMULT.IMULT",
        name: "imult",
        applicable: (device) => DEVICES_GEN3.includes(device)
    },
    {
        description: "SYSPLL ODIV",
        register: "ClkCfgRegs.SYSPLLMULT.ODIV",
        name: "odiv",
        // ODIV is used by REFDIV/ODIV devices AND F28004x (FMULT+ODIV hybrid)
        applicable: (device) => (DEVICES_WITH_REFDIV_ODIV.includes(device) || DEVICES_WITH_FMULT_ODIV.includes(device)) && DEVICES_GEN3.includes(device)
    },
    {
        description: "SYSPLL REFDIV",
        register: "ClkCfgRegs.SYSPLLMULT.REFDIV",
        name: "refdiv",
        applicable: (device) => DEVICES_WITH_REFDIV_ODIV.includes(device) && DEVICES_GEN3.includes(device)
    },
    {
        description: "SYSPLL FMULT",
        register: "ClkCfgRegs.SYSPLLMULT.FMULT",
        name: "fmult",
        // FMULT is used by pure FMULT devices AND FMULT+ODIV hybrid (F28004x)
        applicable: (device) => DEVICES_WITH_FMULT.includes(device) || DEVICES_WITH_FMULT_ODIV.includes(device)
    },
    {
        description: "SYSPLL CLOCKEN",
        register: "ClkCfgRegs.SYSPLLCTL1.PLLCLKEN",
        name: "syspllclken",
        applicable: (device) => DEVICES_GEN3.includes(device)
    },
    {
        description: "SYSCLK DIVSEL",
        register: "ClkCfgRegs.SYSCLKDIVSEL.PLLSYSCLKDIV",
        name: "sysclkdivsel",
        applicable: (device) => DEVICES_GEN3.includes(device)
    },
    {
        description: "SYSCLK DIVSEL LSB (odd divider enable)",
        register: "ClkCfgRegs.SYSCLKDIVSEL.PLLSYSCLKDIV_LSB",
        name: "sysclkdivsellsb",
        applicable: (device) => DEVICES_WITH_REFDIV_ODIV.includes(device)
    },
    {
        description: "LSPCLK DIVSEL",
        register: "ClkCfgRegs.LOSPCP.LSPCLKDIV",
        name: "lspclkdivsel",
        applicable: (device) => DEVICES_GEN3.includes(device)
    },
    {
        description: "EPWMCLK DIVSEL",
        register: "ClkCfgRegs.PERCLKDIVSEL.EPWMCLKDIV",
        name: "epwmclkdiv",
        applicable: (device) => DEVICES_WITH_EPWMCLKDIV.includes(device)
    },
    // AUXPLL Registers
    {
        description: "AUXPLL IMULT",
        register: "ClkCfgRegs.AUXPLLMULT.IMULT",
        name: "auximult",
        applicable: (device) => DEVICES_WITH_AUXPLL.includes(device)
    },
    {
        description: "AUXPLL FMULT",
        register: "ClkCfgRegs.AUXPLLMULT.FMULT",
        name: "auxfmult",
        applicable: (device) => DEVICES_WITH_AUXPLL.includes(device) && DEVICES_WITH_FMULT.includes(device)
    },
    {
        description: "AUXPLL ODIV",
        register: "ClkCfgRegs.AUXPLLMULT.ODIV",
        name: "auxodiv",
        applicable: (device) => DEVICES_WITH_AUXPLL.includes(device) && DEVICES_WITH_REFDIV_ODIV.includes(device)
    },
    {
        description: "AUXPLL REFDIV",
        register: "ClkCfgRegs.AUXPLLMULT.REFDIV",
        name: "auxrefdiv",
        applicable: (device) => DEVICES_WITH_AUXPLL.includes(device) && DEVICES_WITH_REFDIV_ODIV.includes(device)
    },
    {
        description: "AUXPLL CLOCKEN",
        register: "ClkCfgRegs.AUXPLLCTL1.PLLCLKEN",
        name: "auxpllclken",
        applicable: (device) => DEVICES_WITH_AUXPLL.includes(device)
    },
    // MCAN Clock Divider
    // Note: F28P65x has MCANACLKDIV (for MCAN-A instance), F2838x/F28P55x have MCANCLKDIV
    // Both use name "mcanclkdiv" for calculator unification (mutually exclusive by device)
    // Note: two entries share name "mcanclkdiv" intentionally. They have mutually exclusive
    // applicable() functions — one for F28P65x (which has a different register path) and one
    // for the remaining MCAN devices. The framework disambiguates by applicable predicate.
    {
        description: "MCANCLK DIVSEL (F28P65x MCANA)",
        register: "ClkCfgRegs.AUXCLKDIVSEL.MCANACLKDIV",
        name: "mcanclkdiv",  // Unified name for calculator
        applicable: (device) => ["F28P65x"].includes(device)
    },
    {
        // F280015x/F28003x/F2838x: MCANCLKDIV divides PLLCLK (or AUXPLL for F2838x)
        // F28P55x: MCANCLKDIV divides AUXCLKIN (external clock pin) — source is NOT the internal PLL
        description: "MCANCLK DIVSEL",
        register: "ClkCfgRegs.AUXCLKDIVSEL.MCANCLKDIV",
        name: "mcanclkdiv",
        applicable: (device) => ["F280015x", "F28003x", "F2838x", "F28P55x"].includes(device)
    },
    {
        description: "ADCACLK PRESCALE",
        register: "AdcaRegs.ADCCTL2.PRESCALE",
        name: "adcaclkprescale",
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device) && DEVICES_WITH_ADCA.includes(device)
    },
    {
        description: "ADCBCLK PRESCALE",
        register: "AdcbRegs.ADCCTL2.PRESCALE",
        name: "adcbclkprescale",
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device) && DEVICES_WITH_ADCB.includes(device)
    },
    {
        description: "ADCCCLK PRESCALE",
        register: "AdccRegs.ADCCTL2.PRESCALE",
        name: "adccclkprescale",
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device) && DEVICES_WITH_ADCC.includes(device)
    },
    {
        description: "ADCDCLK PRESCALE",
        register: "AdcdRegs.ADCCTL2.PRESCALE",
        name: "adcdclkprescale",
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device) && DEVICES_WITH_ADCD.includes(device)
    },
    {
        description: "ADCA POWERDOWN",
        register: "AdcaRegs.ADCCTL1.ADCPWDNZ",
        name: "adcapowerdown",
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device) && DEVICES_WITH_ADCA.includes(device)
    },
    {
        description: "ADCB POWERDOWN",
        register: "AdcbRegs.ADCCTL1.ADCPWDNZ",
        name: "adcbpowerdown",
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device) && DEVICES_WITH_ADCB.includes(device)
    },
    {
        description: "ADCC POWERDOWN",
        register: "AdccRegs.ADCCTL1.ADCPWDNZ",
        name: "adccpowerdown",
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device) && DEVICES_WITH_ADCC.includes(device)
    },
    {
        description: "ADCD POWERDOWN",
        register: "AdcdRegs.ADCCTL1.ADCPWDNZ",
        name: "adcdpowerdown",
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device) && DEVICES_WITH_ADCD.includes(device)
    },
    {
        description: "ADCE Clock Prescale",
        register: "AdceRegs.ADCCTL2.PRESCALE",
        name: "adceprescale",
        applicable: (device) => DEVICES_WITH_ADCE.includes(device)
    },
    {
        description: "ADCE Power Down",
        register: "AdceRegs.ADCCTL1.ADCPWDNZ",
        name: "adcepowerdown",
        applicable: (device) => DEVICES_WITH_ADCE.includes(device)
    },
]


//=============================================================================
// Clock Calculators
//=============================================================================
// NOTE: Some calculators share the same 'name' but have different 'applicable'
// functions. The CDT framework selects the correct calculator based on the
// device. This allows device-specific calculations (e.g., REFDIV/ODIV vs FMULT
// PLL architectures) while maintaining a consistent output name for downstream
// calculators and checks.
//=============================================================================
const clockCalculators = [
    //=========================================================================
    // Gen2 Clock Calculators (F2802x, F2803x, F2805x, F2806x)
    //=========================================================================
    {
        // Gen2 OSCCLK - always INTOSC (10MHz) for most boards
        // Gen2 devices use fixed 10MHz internal oscillator or external XTAL
        name: "oscclk",
        get: (xtal) => {
            // Gen2 devices typically use 10MHz internal oscillator
            // XTAL can be specified via GUI input (default 10MHz for Gen2)
            return (xtal && xtal > 0) ? xtal : 10000000;
        },
        applicable: (device) => DEVICES_WITH_PLLCR_DIV.includes(device)
    },
    {
        // Gen2 PLLRAWCLK: OSCCLK * DIV
        // Registers: SysCtrlRegs.PLLCR.DIV
        name: "pllrawclk",
        get: (oscclk, pllcrdiv) => {
            // DIV=0 means PLL bypass (output = OSCCLK)
            if (pllcrdiv === 0) return oscclk;
            // PLLRAWCLK = OSCCLK * DIV
            return oscclk * pllcrdiv;
        },
        applicable: (device) => DEVICES_WITH_PLLCR_DIV.includes(device)
    },
    {
        // Gen2 PLLSYSCLK: PLLRAWCLK / DIVSEL
        // Registers: SysCtrlRegs.PLLSTS.DIVSEL
        // DIVSEL encoding (Ref: SPRS523/SPRS584 Table 7-9 "DIVSEL"):
        //   0, 1 → /4 (only use /4 during PLL lock; /4 is safe default)
        //   2    → /2
        //   3    → /1 (only set after PLLLOCKS=1 per errata advisory)
        name: "pllsysclk",
        get: (pllrawclk, pllstsdivsel, device) => {
            // DIVSEL encoding: 0,1 → /4, 2 → /2, 3 → /1
            const divMap = { 0: 4, 1: 4, 2: 2, 3: 1 };
            const divider = divMap[pllstsdivsel];
            if (divider === undefined) {
                console.warn("clocking_clinic: unexpected DIVSEL value " + pllstsdivsel + " for " + device);
                return NaN;
            }
            return pllrawclk / divider;
        },
        applicable: (device) => DEVICES_WITH_PLLCR_DIV.includes(device)
    },
    {
        // Gen2 SYSCLK = PLLSYSCLK (same clock domain)
        name: "sysclk",
        get: (pllsysclk) => {
            return pllsysclk;
        },
        applicable: (device) => DEVICES_WITH_PLLCR_DIV.includes(device)
    },
    {
        // Gen2 LSPCLK: SYSCLK / divider
        // Register: SysCtrlRegs.LOSPCP.LSPCLK (3 bits)
        // Encoding: 0=/1, 1=/2, 2=/4, 3=/6, 4=/8, 5=/10, 6=/12, 7=/14
        name: "lspclk",
        get: (sysclk, gen2lspclkdiv) => {
            // LOSPCP.LSPCLK encoding (Ref: SPRS523 Table 7-13 "LSPCLK"):
            //   0→/1, 1→/2, 2→/4, 3→/6, 4→/8, 5→/10, 6→/12, 7→/14
            const divTable = [1, 2, 4, 6, 8, 10, 12, 14];
            const divider = divTable[gen2lspclkdiv & 0x7] || 1;
            return sysclk / divider;
        },
        applicable: (device) => DEVICES_WITH_PLLCR_DIV.includes(device)
    },
    {
        // Gen2 ADCCLK: SYSCLK / (1, 2, or 4 based on CLKDIV bits)
        // Registers: AdcRegs.ADCCTL2.CLKDIV2EN, AdcRegs.ADCCTL2.CLKDIV4EN
        name: "adcclk",
        get: (sysclk, gen2adcclkdiv2en, gen2adcclkdiv4en) => {
            // CLKDIV4EN takes priority over CLKDIV2EN
            if (gen2adcclkdiv4en) return sysclk / 4;
            if (gen2adcclkdiv2en) return sysclk / 2;
            return sysclk;  // No division (ADCCLK = SYSCLK)
        },
        applicable: (device) => DEVICES_ADC_GEN2_PRESCALE.includes(device)
    },
    {
        // Gen2 EPWMCLK = SYSCLK (no separate divider on Gen2)
        name: "epwmclk",
        get: (sysclk) => {
            return sysclk;
        },
        applicable: (device) => DEVICES_WITH_PLLCR_DIV.includes(device)
    },
    {
        // Gen2 HRPWMCLK = SYSCLK
        name: "hrpwmclk",
        get: (sysclk) => {
            return sysclk;
        },
        applicable: (device) => DEVICES_GEN2_WITH_HRPWM.includes(device)
    },
    //=========================================================================
    // Gen3 Clock Calculators
    //=========================================================================
    {
        // Gen3 OSCCLK
        name: "oscclk",
        get: (oscclksrcsel, xtal) => {
            // OSCCLKSRCSEL values (from ClkCfgRegs.CLKSRCCTL1.OSCCLKSRCSEL):
            //   0 = INTOSC1 (10MHz internal oscillator - fixed, known)
            //   1 = INTOSC2 (10MHz internal oscillator - fixed, known)
            //   2 = XTAL (external crystal - board-dependent, from GUI input)
            //
            // The 'xtal' parameter comes from the GUI input field at runtime.
            // XTAL frequency cannot be determined from device registers - it is
            // a physical property of the crystal on the board.
            // Default: 20MHz (most TI LaunchPads)
            // Exceptions: F2837xD/S = 10MHz, F28P65x = 25MHz
            switch (oscclksrcsel) {
                case 0:  // INTOSC1 - always 10MHz
                    return 10000000;
                case 1:  // INTOSC2 - always 10MHz
                    return 10000000;
                case 2:  // XTAL - from GUI input (default 20MHz)
                    return (xtal && xtal > 0) ? xtal : 20000000;
                default:
                    console.warn("Warning: Unknown OSCCLKSRCSEL value: " + oscclksrcsel);
                    return 10000000;
            }
        },
        applicable: (device) => DEVICES_GEN3.includes(device)
    },
    {
        // REFDIV/ODIV architecture PLL calculation
        // Devices: F280013x, F280015x, F28003x, F28002x, F2838x, F28P55x, F28P65x
        // Formula: PLLRAWCLK = OSCCLK / (REFDIV+1) * IMULT / (ODIV+1)
        name: "pllrawclk",
        get: (oscclk, refdiv, imult, odiv) => {
            // Calculate PLL output: PLLRAWCLK = OSCCLK / (REFDIV+1) * IMULT / (ODIV+1)
            return oscclk / (refdiv + 1) * imult / (odiv + 1);
        },
        applicable: (device) => DEVICES_WITH_REFDIV_ODIV.includes(device) && DEVICES_WITH_CDT_SUPPORT.includes(device)
    },
    {
        // FMULT architecture PLL calculation (pure FMULT, no ODIV)
        // Devices: F2807x, F2837xD, F2837xS
        // Formula: PLLRAWCLK = OSCCLK * (IMULT + FMULT)
        name: "pllrawclk",
        get: (oscclk, imult, fmult) => {
            const fmultVal = calcFmultValue(fmult);
            if (isNaN(fmultVal)) return NaN;
            return oscclk * (imult + fmultVal);
        },
        applicable: (device) => DEVICES_WITH_FMULT.includes(device)
    },
    {
        // FMULT+ODIV hybrid architecture PLL calculation
        // Devices: F28004x (has FMULT and ODIV but no REFDIV)
        // Formula: PLLRAWCLK = OSCCLK * (IMULT + FMULT) / (ODIV + 1)
        // Ref: F28004x driverlib sysctl.c SysCtl_getClock() line 203
        name: "pllrawclk",
        get: (oscclk, imult, fmult, odiv) => {
            const fmultVal = calcFmultValue(fmult);
            if (isNaN(fmultVal)) return NaN;
            const rawClk = oscclk * (imult + fmultVal);
            // ODIV encoding: divisor = ODIV + 1 (same as REFDIV/ODIV devices)
            return rawClk / (odiv + 1);
        },
        applicable: (device) => DEVICES_WITH_FMULT_ODIV.includes(device)
    },
    {
        // Internal reference clock (after REFDIV)
        name: "intclk",
        get: (oscclk, refdiv) => {
            return oscclk / (refdiv + 1);
        },
        applicable: (device) => DEVICES_WITH_REFDIV_ODIV.includes(device) && DEVICES_WITH_CDT_SUPPORT.includes(device)
    },
    {
        // VCO clock (before ODIV)
        name: "vcoclk",
        get: (oscclk, refdiv, imult) => {
            return oscclk / (refdiv + 1) * imult;
        },
        applicable: (device) => DEVICES_WITH_REFDIV_ODIV.includes(device) && DEVICES_WITH_CDT_SUPPORT.includes(device)
    },
    {
        // PLLSYSCLK for REFDIV/ODIV devices (uses LSB for odd dividers)
        // Devices: F280013x, F280015x, F28002x, F28003x, F2838x, F28P55x, F28P65x
        name: "pllsysclk",
        get: (oscclk, pllrawclk, syspllclken, sysclkdivsel, sysclkdivsellsb) => {
            // Calculate divider value based on SYSCLKDIVSEL register
            // PLLSYSCLKDIV (bits 5:0): base divider value
            // PLLSYSCLKDIV_LSB (bit 8): enables odd dividers
            // Formula: divider = 2 * PLLSYSCLKDIV + PLLSYSCLKDIV_LSB
            // When sysclkdivsel=0 and lsb=0, divider is 1
            let divValue;
            if (sysclkdivsel === 0 && (!sysclkdivsellsb || sysclkdivsellsb === 0)) {
                divValue = 1;
            } else {
                divValue = 2 * sysclkdivsel + (sysclkdivsellsb || 0);
            }
            const source = syspllclken ? pllrawclk : oscclk;
            return safeDiv(source, divValue, 1);
        },
        applicable: (device) => DEVICES_WITH_REFDIV_ODIV.includes(device) && DEVICES_WITH_CDT_SUPPORT.includes(device)
    },
    {
        // PLLSYSCLK for FMULT-based devices (no LSB bit - simpler divider)
        // Devices: F28004x, F2807x, F2837xD, F2837xS
        // Includes both pure FMULT devices and FMULT+ODIV hybrid (F28004x)
        name: "pllsysclk",
        get: (oscclk, pllrawclk, syspllclken, sysclkdivsel) => {
            // FMULT devices use simpler divider: divider = 2 * SYSCLKDIVSEL (or 1 if 0)
            const divValue = (sysclkdivsel === 0) ? 1 : 2 * sysclkdivsel;
            const source = syspllclken ? pllrawclk : oscclk;
            return safeDiv(source, divValue, 1);
        },
        applicable: (device) => DEVICES_WITH_FMULT.includes(device) || DEVICES_WITH_FMULT_ODIV.includes(device)
    },
    {
        name: "sysclk",
        get: (pllsysclk) => {
            return pllsysclk;
        },
        applicable: (device) => DEVICES_GEN3.includes(device)
    },
    {
        name: "lspclk",
        get: (sysclk, lspclkdivsel) => {
            const divValue = (lspclkdivsel === 0) ? 1 : 2 * lspclkdivsel;
            return safeDiv(sysclk, divValue, 1);
        },
        applicable: (device) => DEVICES_GEN3.includes(device)
    },
    {
        name: "adcaclk",
        get: (sysclk, adcaclkprescale) => {
            const prescale = calcAdcPrescaleValue(adcaclkprescale);
            if (isNaN(prescale) || prescale <= 0) return NaN;
            return sysclk / prescale;
        },
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device) && DEVICES_WITH_ADCA.includes(device)
    },
    {
        name: "adcbclk",
        get: (sysclk, adcbclkprescale) => {
            const prescale = calcAdcPrescaleValue(adcbclkprescale);
            if (isNaN(prescale) || prescale <= 0) return NaN;
            return sysclk / prescale;
        },
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device) && DEVICES_WITH_ADCB.includes(device)
    },
    {
        name: "adccclk",
        get: (sysclk, adccclkprescale) => {
            const prescale = calcAdcPrescaleValue(adccclkprescale);
            if (isNaN(prescale) || prescale <= 0) return NaN;
            return sysclk / prescale;
        },
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device) && DEVICES_WITH_ADCC.includes(device)
    },
    {
        name: "adcdclk",
        get: (sysclk, adcdclkprescale) => {
            const prescale = calcAdcPrescaleValue(adcdclkprescale);
            if (isNaN(prescale) || prescale <= 0) return NaN;
            return sysclk / prescale;
        },
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device) && DEVICES_WITH_ADCD.includes(device)
    },
    {
        name: "adceclk",
        get: (sysclk, adceprescale, adcepowerdown, device) => {
            if (!adcepowerdown) return 0;
            const prescale = calcAdcPrescaleValue(adceprescale, device);
            if (isNaN(prescale) || prescale <= 0) return NaN;
            return sysclk / prescale;
        },
        applicable: (device) => DEVICES_WITH_ADCE.includes(device)
    },
    {
        // Gen3 devices without EPWMCLKDIV register, EPWMCLK = SYSCLK (no divider)
        name: "epwmclk",
        get: (sysclk) => {
            return sysclk;
        },
        applicable: (device) => DEVICES_GEN3.includes(device) && !DEVICES_WITH_EPWMCLKDIV.includes(device)
    },
    {
        // Devices with EPWMCLKDIV register: EPWMCLK = SYSCLK / (EPWMCLKDIV ? 2 : 1)
        name: "epwmclk",
        get: (sysclk, epwmclkdiv) => {
            const divValue = (epwmclkdiv === 0) ? 1 : 2;
            return sysclk / divValue;
        },
        applicable: (device) => DEVICES_WITH_EPWMCLKDIV.includes(device)
    },
    {
        // Gen3 HRPWMCLK
        name: "hrpwmclk",
        get: (sysclk) => {
            return sysclk;
        },
        applicable: (device) => DEVICES_GEN3.includes(device) && DEVICES_WITH_HRPWM.includes(device)
    },
    // AUXPLL Clocks (REFDIV/ODIV architecture - F2838x, F28P65x; F2807x uses FMULT path below)
    {
        name: "auxpllrawclk",
        get: (oscclk, auxrefdiv, auximult, auxodiv, auxpllclken) => {
            if (!auxpllclken) return 0;
            return oscclk / (auxrefdiv + 1) * auximult / (auxodiv + 1);
        },
        applicable: (device) => DEVICES_WITH_AUXPLL.includes(device) && DEVICES_WITH_REFDIV_ODIV.includes(device)
    },
    // AUXPLL Clocks (FMULT architecture - F2807x, F2837xD, F2837xS)
    {
        name: "auxpllrawclk",
        get: (oscclk, auximult, auxfmult, auxpllclken) => {
            if (!auxpllclken) return 0;
            const fmultVal = calcFmultValue(auxfmult);
            if (isNaN(fmultVal)) return NaN;
            return oscclk * (auximult + fmultVal);
        },
        applicable: (device) => DEVICES_WITH_AUXPLL.includes(device) && DEVICES_WITH_FMULT.includes(device)
    },
    // MCAN Clock (CAN-FD) - F2838x/F28P65x source from AUXPLL
    {
        name: "mcanclk",
        get: (auxpllrawclk, mcanclkdiv) => {
            if (auxpllrawclk === 0) return 0;
            // MCANCLKDIV encoding: register value N → divisor (N+1)
            //   0→/1, 1→/2, ..., 19→/20  (Ref: SPRS458 Table 9-2 MCANCLKDIV)
            const divValue = mcanclkdiv + 1;
            return auxpllrawclk / divValue;
        },
        // Only for devices with both MCAN and AUXPLL
        applicable: (device) => DEVICES_WITH_MCAN.includes(device) && DEVICES_WITH_AUXPLL.includes(device)
    },
    // MCAN Clock (CAN-FD) - F280015x/F28003x source from PLLCLK (no AUXPLL)
    {
        name: "mcanclk",
        get: (pllrawclk, mcanclkdiv) => {
            // Fallback if MCANCLKDIV register not read - MCAN runs at PLLCLK directly
            if (mcanclkdiv === undefined || isNaN(mcanclkdiv)) return pllrawclk;
            // MCANCLKDIV encoding: register value N → divisor (N+1)
            //   0→/1, 1→/2, ..., 19→/20  (Ref: F280015x/F28003x TRM)
            const divValue = mcanclkdiv + 1;
            return pllrawclk / divValue;
        },
        // F280015x/F28003x have MCAN but no AUXPLL - uses PLLCLK
        // F28P55x is excluded here because it uses AUXCLKIN (external) - handled below
        applicable: (device) => DEVICES_WITH_MCAN.includes(device) &&
                                 !DEVICES_WITH_AUXPLL.includes(device) &&
                                 !DEVICES_WITH_MCAN_AUXCLKIN.includes(device)
    },
    // MCAN Clock (CAN-FD) - F28P55x uses AUXCLKIN external clock input pin
    // AUXCLKIN is a physical board-level clock (not derivable from internal PLL registers).
    // CDT can read MCANCLKDIV but cannot determine the source clock frequency automatically.
    // Returns NaN to indicate "cannot calculate — AUXCLKIN frequency is board-defined."
    {
        name: "mcanclk",
        get: () => {
            return NaN;  // AUXCLKIN frequency is not readable from device registers
        },
        applicable: (device) => DEVICES_WITH_MCAN_AUXCLKIN.includes(device)
    },
    // Legacy DCAN Clocks (CAN 2.0)
    // CANCLK = SYSCLK (no separate clock divider for DCAN on C2000)
    // Reference: driverlib/<device>/driverlib/can.h CAN_setBitRate() expects SYSCLK
    {
        name: "canaclk",
        get: (sysclk) => {
            return sysclk;
        },
        applicable: (device) => DEVICES_WITH_CANA.includes(device)
    },
    {
        name: "canbclk",
        get: (sysclk) => {
            return sysclk;
        },
        applicable: (device) => DEVICES_WITH_CANB.includes(device)
    },
    // Max SYSCLK frequency based on device family
    // These calculators provide the max frequency value for use in checks
    // Gen2 Max SYSCLK
    {
        name: "maxsysclk",
        get: () => { return 40000000; },
        applicable: (device) => DEVICES_40MHZ.includes(device)
    },
    {
        name: "maxsysclk",
        get: () => { return 60000000; },
        applicable: (device) => DEVICES_60MHZ_GEN2.includes(device)
    },
    {
        name: "maxsysclk",
        get: () => { return 90000000; },
        applicable: (device) => DEVICES_90MHZ.includes(device)
    },
    // Gen3 Max SYSCLK
    {
        name: "maxsysclk",
        get: () => { return 100000000; },
        applicable: (device) => DEVICES_100MHZ.includes(device)
    },
    {
        name: "maxsysclk",
        get: () => { return 120000000; },
        applicable: (device) => DEVICES_120MHZ.includes(device)
    },
    {
        name: "maxsysclk",
        get: () => { return 150000000; },
        applicable: (device) => DEVICES_150MHZ.includes(device)
    },
    {
        name: "maxsysclk",
        get: () => { return 200000000; },
        applicable: (device) => DEVICES_200MHZ.includes(device)
    }
]


//=============================================================================
// Clocking Checks
// Each check includes tooltip metadata: min, max, valueCalc (calculated clock name)
// Special values: "maxsysclk" = device-specific max, "sysclk" = current sysclk
//=============================================================================
const clockingChecks = [
    {
        name: "sysclkMaxMinFreq",
        displayName: "SYSCLK Max/Min Freq",
        description: "System clock must be 2-{max}MHz for proper CPU operation.",
        check: (sysclk, maxsysclk) => {
            return sysclk >= 2000000 && sysclk <= maxsysclk;
        },
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device),
        tooltip: { min: 2000000, max: "maxsysclk", valueCalc: "sysclk" }
    },
    {
        name: "pllsysclkMaxMinFreq",
        displayName: "PLLSYSCLK Max/Min Freq",
        description: "PLL output clock before SYSCLKDIVSEL. Must be 2-{max}MHz.",
        check: (pllsysclk, maxsysclk) => {
            return pllsysclk >= 2000000 && pllsysclk <= maxsysclk;
        },
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device),
        tooltip: { min: 2000000, max: "maxsysclk", valueCalc: "pllsysclk" }
    },
    {
        name: "lspclkMaxMinFreq",
        displayName: "LSPCLK Max/Min Freq",
        description: "Low-speed peripheral clock (SCI, SPI, I2C). Derived from SYSCLK.",
        check: (lspclk, sysclk) => {
            // LSPCLK is derived from SYSCLK via divider
            // Min: 2MHz for proper peripheral operation
            // Max: Cannot exceed SYSCLK (divider >= 1)
            return lspclk >= 2000000 && lspclk <= sysclk;
        },
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device),
        tooltip: { min: 2000000, max: "sysclk", valueCalc: "lspclk" }
    },
    {
        // Gen2 PLLRAWCLK check (different limits)
        name: "pllrawclkMaxMinFreq",
        displayName: "PLLRAWCLK Max/Min Freq",
        description: "Raw PLL output. Gen2 devices use simpler PLL with lower limits.",
        check: (pllrawclk, maxsysclk) => {
            // Gen2 PLL output is limited by max SYSCLK (40-90MHz)
            return pllrawclk >= 4000000 && pllrawclk <= maxsysclk * 4;
        },
        applicable: (device) => DEVICES_WITH_PLLCR_DIV.includes(device),
        // max = maxsysclk * 4: 160MHz for F2802x, 240MHz for F2803x/F2805x, 360MHz for F2806x
        tooltip: { min: 4000000, max: 360000000, valueCalc: "pllrawclk" }
    },
    {
        // Gen3 PLLRAWCLK check
        name: "pllrawclkMaxMinFreq",
        displayName: "PLLRAWCLK Max/Min Freq",
        description: "Raw PLL output before system dividers. Must be 6-240MHz.",
        check: (pllrawclk) => {
            return pllrawclk >= 6000000 && pllrawclk <= 240000000;
        },
        applicable: (device) => DEVICES_GEN3.includes(device),
        tooltip: { min: 6000000, max: 240000000, valueCalc: "pllrawclk" }
    },
    {
        name: "vcoclkMaxMinFreq",
        displayName: "VCOCLK Max/Min Freq",
        description: "VCO frequency (before ODIV). Must be 220-600MHz for PLL lock.",
        check: (vcoclk) => {
            return vcoclk >= 220000000 && vcoclk <= 600000000;
        },
        applicable: (device) => DEVICES_WITH_REFDIV_ODIV.includes(device) && DEVICES_WITH_CDT_SUPPORT.includes(device),
        tooltip: { min: 220000000, max: 600000000, valueCalc: "vcoclk" }
    },
    {
        name: "intclkMaxMinFreq",
        displayName: "INTCLK Max/Min Freq",
        description: "Internal PLL reference (OSCCLK/REFDIV). Must be 2-20MHz.",
        check: (intclk) => {
            return intclk >= 2000000 && intclk <= 20000000;
        },
        applicable: (device) => DEVICES_WITH_REFDIV_ODIV.includes(device) && DEVICES_WITH_CDT_SUPPORT.includes(device),
        tooltip: { min: 2000000, max: 20000000, valueCalc: "intclk" }
    },
    //-------------------------------------------------------------------------
    // Gen2 ADC Clock Check (single ADC module, 2-25 MHz limit)
    //-------------------------------------------------------------------------
    {
        name: "adcclkMaxMinFreq",
        displayName: "ADCCLK Max/Min Freq",
        description: "Gen2 ADC conversion clock. Must be 2-25MHz for proper sampling.",
        check: (adcclk) => {
            return adcclk >= 2000000 && adcclk <= 25000000;
        },
        applicable: (device) => DEVICES_ADC_GEN2_PRESCALE.includes(device),
        tooltip: { min: 2000000, max: 25000000, valueCalc: "adcclk" }
    },
    //-------------------------------------------------------------------------
    // Gen3 ADC Clock Checks (per-instance, 5-60 MHz limit)
    //-------------------------------------------------------------------------
    {
        name: "adcaclkMaxMinFreq",
        displayName: "ADCACLK Max/Min Freq",
        description: "ADCA conversion clock. Must be 5-60MHz when ADC is powered on.",
        check: (adcaclk, adcapowerdown) => {
            if (adcapowerdown === 0) return true;
            return adcaclk >= 5000000 && adcaclk <= 60000000;
        },
        applicable: (device) => DEVICES_GEN3.includes(device) && DEVICES_WITH_ADCA.includes(device),
        tooltip: { min: 5000000, max: 60000000, valueCalc: "adcaclk" }
    },
    {
        name: "adcbclkMaxMinFreq",
        displayName: "ADCBCLK Max/Min Freq",
        description: "ADCB conversion clock. Must be 5-60MHz when ADC is powered on.",
        check: (adcbclk, adcbpowerdown) => {
            if (adcbpowerdown === 0) return true;
            return adcbclk >= 5000000 && adcbclk <= 60000000;
        },
        applicable: (device) => DEVICES_GEN3.includes(device) && DEVICES_WITH_ADCB.includes(device),
        tooltip: { min: 5000000, max: 60000000, valueCalc: "adcbclk" }
    },
    {
        name: "adccclkMaxMinFreq",
        displayName: "ADCCCLK Max/Min Freq",
        description: "ADCC conversion clock. Must be 5-60MHz when ADC is powered on.",
        check: (adccclk, adccpowerdown) => {
            if (adccpowerdown === 0) return true;
            return adccclk >= 5000000 && adccclk <= 60000000;
        },
        applicable: (device) => DEVICES_GEN3.includes(device) && DEVICES_WITH_ADCC.includes(device),
        tooltip: { min: 5000000, max: 60000000, valueCalc: "adccclk" }
    },
    {
        name: "adcdclkMaxMinFreq",
        displayName: "ADCDCLK Max/Min Freq",
        description: "ADCD conversion clock. Must be 5-60MHz when ADC is powered on.",
        check: (adcdclk, adcdpowerdown) => {
            if (adcdpowerdown === 0) return true;
            return adcdclk >= 5000000 && adcdclk <= 60000000;
        },
        applicable: (device) => DEVICES_GEN3.includes(device) && DEVICES_WITH_ADCD.includes(device),
        tooltip: { min: 5000000, max: 60000000, valueCalc: "adcdclk" }
    },
    {
        name: "adceclkMaxMinFreq",
        get: (adceclk, device) => {
            if (adceclk === 0) return true; // powered down, skip check
            return adceclk >= 5000000 && adceclk <= 60000000;
        },
        applicable: (device) => DEVICES_WITH_ADCE.includes(device),
        tooltip: { min: 5000000, max: 60000000 }
    },
    {
        name: "epwmclkMaxfreq",
        displayName: "EPWMCLK Max Freq",
        description: "ePWM module clock. Cannot exceed device max SYSCLK.",
        check: (epwmclk, maxsysclk) => {
            return epwmclk <= maxsysclk;
        },
        applicable: (device) => DEVICES_WITH_CDT_SUPPORT.includes(device),
        tooltip: { min: null, max: "maxsysclk", valueCalc: "epwmclk" }
    },
    //-------------------------------------------------------------------------
    // Gen2 HRPWM Check (lower min frequency - older MEP calibration)
    //-------------------------------------------------------------------------
    {
        name: "hrpwmMaxMinfreq",
        displayName: "HRPWMCLK Max/Min Freq",
        description: "Gen2 HRPWM requires 40MHz+ for MEP calibration.",
        check: (hrpwmclk, maxsysclk) => {
            return hrpwmclk >= 40000000 && hrpwmclk <= maxsysclk;
        },
        applicable: (device) => DEVICES_GEN2_WITH_HRPWM.includes(device),
        tooltip: { min: 40000000, max: "maxsysclk", valueCalc: "hrpwmclk" }
    },
    //-------------------------------------------------------------------------
    // Gen3 HRPWM Check (requires 60MHz+ for SFO v8 calibration)
    //-------------------------------------------------------------------------
    {
        name: "hrpwmMaxMinfreq",
        displayName: "HRPWMCLK Max/Min Freq",
        description: "HRPWM requires 60MHz+ for MEP calibration (SFO library).",
        check: (hrpwmclk, maxsysclk) => {
            return hrpwmclk >= 60000000 && hrpwmclk <= maxsysclk;
        },
        applicable: (device) => DEVICES_GEN3.includes(device) && DEVICES_WITH_HRPWM.includes(device),
        tooltip: { min: 60000000, max: "maxsysclk", valueCalc: "hrpwmclk" }
    },
    // AUXPLL Clock Checks
    {
        name: "auxpllrawclkMaxMinFreq",
        displayName: "AUXPLLRAWCLK Max/Min Freq",
        description: "Auxiliary PLL output for CAN-FD, USB, etc. Must be 6-240MHz.",
        check: (auxpllrawclk) => {
            if (auxpllrawclk === 0) return true; // Disabled is OK
            return auxpllrawclk >= 6000000 && auxpllrawclk <= 240000000;
        },
        applicable: (device) => DEVICES_WITH_AUXPLL.includes(device),
        tooltip: { min: 6000000, max: 240000000, valueCalc: "auxpllrawclk" }
    },
    // MCAN Clock Checks (CAN-FD)
    {
        name: "mcanclkMinFreq",
        displayName: "MCANCLK Min Freq",
        description: "CAN-FD clock for MCAN peripheral. Requires 20MHz+ for bit timing.",
        check: (mcanclk) => {
            if (mcanclk === 0) return true;   // AUXPLL disabled is OK
            if (isNaN(mcanclk)) return true;  // F28P55x AUXCLKIN: cannot check, pass through
            // MCAN requires minimum clock for CAN-FD bit timing
            // Max is constrained by AUXPLL limits (validated separately)
            return mcanclk >= 20000000;
        },
        // F28P55x uses AUXCLKIN (external) — check is still applicable but returns pass
        // when mcanclk is NaN (AUXCLKIN frequency not derivable from registers)
        applicable: (device) => DEVICES_WITH_MCAN.includes(device),
        tooltip: { min: 20000000, max: null, valueCalc: "mcanclk" }
    },
    {
        name: "mcanclkMaxFreq",
        get: (mcanclk) => {
            if (mcanclk === 0) return true; // AUXPLL disabled, skip check
            return mcanclk <= 80000000;
        },
        applicable: (device) => DEVICES_WITH_MCAN.includes(device),
        tooltip: { max: 80000000 }
    },
    // Legacy DCAN Clock Checks (CAN 2.0)
    // CANCLK = SYSCLK for legacy CAN modules
    // Min frequency determined by CAN bit timing requirements:
    //   - 1 Mbps CAN with 10 time quanta requires CANCLK >= 10 MHz
    //   - 500 kbps CAN with 10 time quanta requires CANCLK >= 5 MHz
    // Using 8 MHz minimum to support 1 Mbps with reasonable BRP values
    {
        name: "canaclkMinFreq",
        displayName: "CANACLK Min Freq",
        description: "Legacy CAN-A module clock. Min 8MHz for 1Mbps bit timing.",
        check: (canaclk, maxsysclk) => {
            // CANCLK = SYSCLK, so max is device SYSCLK max
            // Min 8 MHz for proper 1 Mbps CAN bit timing with BRP >= 1
            return canaclk >= 8000000 && canaclk <= maxsysclk;
        },
        applicable: (device) => DEVICES_WITH_CANA.includes(device),
        tooltip: { min: 8000000, max: "maxsysclk", valueCalc: "canaclk" }
    },
    {
        name: "canbclkMinFreq",
        displayName: "CANBCLK Min Freq",
        description: "Legacy CAN-B module clock. Min 8MHz for 1Mbps bit timing.",
        check: (canbclk, maxsysclk) => {
            // CANCLK = SYSCLK, so max is device SYSCLK max
            // Min 8 MHz for proper 1 Mbps CAN bit timing with BRP >= 1
            return canbclk >= 8000000 && canbclk <= maxsysclk;
        },
        applicable: (device) => DEVICES_WITH_CANB.includes(device),
        tooltip: { min: 8000000, max: "maxsysclk", valueCalc: "canbclk" }
    }
]


//=============================================================================
// XTAL Frequency Handling (Runtime-Only Operation)
//=============================================================================
// CDT operates purely from runtime register reads - no project files required.
//
// Clock source detection:
// - OSCCLKSRCSEL register is read at runtime to determine active source
// - INTOSC1/INTOSC2: Fixed 10MHz (known, no user input needed)
// - XTAL: Board-dependent frequency (cannot be read from registers)
//
// TI LaunchPad XTAL Frequencies (from device_support/<device>/common/include/device.h):
//   20 MHz: F280013x, F280015x, F28002x, F28003x, F28004x, F2807x, F2838x, F28P55x
//   10 MHz: F2837xD, F2837xS
//   25 MHz: F28P65x
//
// For XTAL source:
// - User specifies XTAL frequency via GUI input field (defaults to 20MHz)
// - The 'xtal' parameter in oscclk calculator comes from GUI input


exports = {
    prereqRegisters: prereqRegisters,
    clockCalculators: clockCalculators,
    clockingChecks: clockingChecks
}
