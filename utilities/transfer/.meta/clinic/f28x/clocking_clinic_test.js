//=============================================================================
// clocking_clinic_test.js - Unit Tests for Clocking Clinic Functions
//=============================================================================
// Purpose: Standalone unit tests for clocking_clinic.js helper functions,
//          clock calculators, and validation checks.
// Usage: Run with Node.js: node clocking_clinic_test.js
//=============================================================================

"use strict";

//=============================================================================
// Test Framework (Simple assertion-based)
//=============================================================================
let testsPassed = 0;
let testsFailed = 0;
const testResults = [];

function assert(condition, testName, details = "") {
    if (condition) {
        testsPassed++;
        testResults.push({ name: testName, passed: true });
    } else {
        testsFailed++;
        testResults.push({ name: testName, passed: false, details });
        console.log(`FAIL: ${testName}${details ? " - " + details : ""}`);
    }
}

function assertEqual(actual, expected, testName) {
    const passed = actual === expected;
    if (!passed) {
        assert(false, testName, `expected ${expected}, got ${actual}`);
    } else {
        assert(true, testName);
    }
}

function assertApproxEqual(actual, expected, tolerance, testName) {
    const passed = Math.abs(actual - expected) <= tolerance;
    if (!passed) {
        assert(false, testName, `expected ~${expected}, got ${actual} (tolerance: ${tolerance})`);
    } else {
        assert(true, testName);
    }
}

//=============================================================================
// Device Constants (mirrored from clocking_clinic.js)
//=============================================================================
const DEVICES_GEN2 = ["F2802x", "F2803x", "F2805x", "F2806x"];
const DEVICES_GEN3 = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
];
const DEVICES_WITH_CDT_SUPPORT = [...DEVICES_GEN2, ...DEVICES_GEN3];
const DEVICES_WITH_PLLCR_DIV = ["F2802x", "F2803x", "F2805x", "F2806x"];  // Gen2 PLL arch

const DEVICES_WITH_REFDIV_ODIV = ["F280013x", "F280015x", "F28003x", "F28002x", "F2838x", "F28P55x", "F28P65x"];
const DEVICES_WITH_FMULT = ["F2807x", "F2837xD", "F2837xS"];
const DEVICES_WITH_FMULT_ODIV = ["F28004x"];
const DEVICES_WITH_AUXPLL = ["F2807x", "F2837xD", "F2837xS", "F2838x", "F28P65x"];
// F28P55x has MCAN but uses AUXCLKIN (external clock pin), not AUXPLL or PLLCLK
const DEVICES_WITH_MCAN = ["F280015x", "F28003x", "F2838x", "F28P55x", "F28P65x"];
const DEVICES_WITH_MCAN_AUXCLKIN = ["F28P55x"];

// Gen2 Max SYSCLK Groups
const DEVICES_WITH_40MHZ_MAX_SYSCLK = ["F2802x"];
const DEVICES_WITH_60MHZ_MAX_SYSCLK_GEN2 = ["F2803x", "F2805x"];
const DEVICES_WITH_90MHZ_MAX_SYSCLK = ["F2806x"];
// Gen3 Max SYSCLK Groups
const DEVICES_WITH_100MHZ_MAX_SYSCLK = ["F28002x", "F28004x"];
const DEVICES_WITH_120MHZ_MAX_SYSCLK = ["F280013x", "F280015x", "F28003x", "F2807x"];
const DEVICES_WITH_150MHZ_MAX_SYSCLK = ["F28P55x"];
const DEVICES_WITH_200MHZ_MAX_SYSCLK = ["F2837xD", "F2837xS", "F2838x", "F28P65x"];

const DEVICES_WITH_ADC_INTEGER_PRESCALE = ["F280013x", "F280015x", "F28002x", "F28003x", "F28004x"];
const DEVICES_WITH_ADC_HALFSTEP_PRESCALE = ["F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"];

//=============================================================================
// Helper Functions Under Test (extracted from clocking_clinic.js)
//=============================================================================

function getMaxSysclk(device) {
    // Gen2
    if (DEVICES_WITH_40MHZ_MAX_SYSCLK.includes(device)) return 40000000;
    if (DEVICES_WITH_60MHZ_MAX_SYSCLK_GEN2.includes(device)) return 60000000;
    if (DEVICES_WITH_90MHZ_MAX_SYSCLK.includes(device)) return 90000000;
    // Gen3
    if (DEVICES_WITH_100MHZ_MAX_SYSCLK.includes(device)) return 100000000;
    if (DEVICES_WITH_120MHZ_MAX_SYSCLK.includes(device)) return 120000000;
    if (DEVICES_WITH_150MHZ_MAX_SYSCLK.includes(device)) return 150000000;
    if (DEVICES_WITH_200MHZ_MAX_SYSCLK.includes(device)) return 200000000;
    return NaN;  // Matches production device_constants.js behavior
}

function calcFmultValue(fmultReg) {
    switch (fmultReg) {
        case 0: return 0.0;
        case 1: return 0.25;
        case 2: return 0.5;
        case 3: return 0.75;
        default: return NaN;  // Matches production clocking_clinic.js behavior
    }
}

function validateImult(imult) {
    if (imult < 0 || imult > 127) return false;
    return true;
}

function validateRefdiv(refdiv) {
    if (refdiv < 0 || refdiv > 31) return false;
    return true;
}

function validateOdiv(odiv) {
    if (odiv < 0 || odiv > 31) return false;
    return true;
}

function validateSysclkdivsel(divsel) {
    if (divsel < 0 || divsel > 63) return false;
    return true;
}

function calcAdcPrescaleValue(prescaleReg, device) {
    if (prescaleReg === 1) return NaN;   // Reserved - matches production NaN return
    if (prescaleReg > 16) return NaN;   // Out of valid range (max ADC_CLK_DIV_9_0 = 16)
    if (prescaleReg === 0) return 1.0;
    if (prescaleReg === 2) return 2.0;
    return ((prescaleReg - 2.0) * 0.5) + 2.0;
}

//=============================================================================
// Clock Calculator Functions Under Test
//=============================================================================

function calcOscclk(oscclksrcsel, xtal) {
    switch (oscclksrcsel) {
        case 0: return 10000000;  // INTOSC1
        case 1: return 10000000;  // INTOSC2
        case 2: return (xtal && xtal > 0) ? xtal : 20000000;  // XTAL
        default: return 10000000;
    }
}

function calcPllrawclk_RefdivOdiv(oscclk, refdiv, imult, odiv) {
    return oscclk / (refdiv + 1) * imult / (odiv + 1);
}

function calcPllrawclk_Fmult(oscclk, imult, fmult) {
    const fmultValue = calcFmultValue(fmult);
    return oscclk * (imult + fmultValue);
}

function calcPllsysclk(oscclk, pllrawclk, syspllclken, sysclkdivsel) {
    const divValue = (sysclkdivsel) ? 2 * sysclkdivsel : 1;
    if (syspllclken) {
        return pllrawclk / divValue;
    }
    return oscclk / divValue;
}

// Gen2 PLL calculators
function calcGen2Pllrawclk(oscclk, pllcrdiv) {
    if (pllcrdiv === 0) return oscclk;  // DIV=0 means PLL bypass
    return oscclk * pllcrdiv;
}

function calcGen2Pllsysclk(pllrawclk, pllstsdivsel) {
    // DIVSEL encoding: 0,1→/4, 2→/2, 3→/1 (Ref: SPRS523 Table 7-9)
    const divMap = { 0: 4, 1: 4, 2: 2, 3: 1 };
    const divider = divMap[pllstsdivsel] || 1;
    return pllrawclk / divider;
}

function calcGen2Lspclk(sysclk, gen2lspclkdiv) {
    // LOSPCP encoding: 0→/1, 1→/2, 2→/4, 3→/6, 4→/8, 5→/10, 6→/12, 7→/14
    const divTable = [1, 2, 4, 6, 8, 10, 12, 14];
    const divider = divTable[gen2lspclkdiv & 0x7] || 1;
    return sysclk / divider;
}

function calcGen2Adcclk(sysclk, clkdiv2en, clkdiv4en) {
    if (clkdiv4en) return sysclk / 4;  // CLKDIV4EN takes priority
    if (clkdiv2en) return sysclk / 2;
    return sysclk;
}

// AUXPLL calculators
function calcAuxpllrawclk_RefdivOdiv(oscclk, auxrefdiv, auximult, auxodiv, auxpllclken) {
    if (!auxpllclken) return 0;
    return oscclk / (auxrefdiv + 1) * auximult / (auxodiv + 1);
}

function calcAuxpllrawclk_Fmult(oscclk, auximult, auxfmult, auxpllclken) {
    if (!auxpllclken) return 0;
    const fmultVal = calcFmultValue(auxfmult);
    if (isNaN(fmultVal)) return NaN;
    return oscclk * (auximult + fmultVal);
}

// MCAN clock calculators
function calcMcanclk_AuxpllSource(auxpllrawclk, mcanclkdiv) {
    if (auxpllrawclk === 0) return 0;
    return auxpllrawclk / (mcanclkdiv + 1);  // MCANCLKDIV: 0→/1, 1→/2, ...
}

function calcMcanclk_PllSource(pllrawclk, mcanclkdiv) {
    if (mcanclkdiv === undefined || isNaN(mcanclkdiv)) return pllrawclk;
    return pllrawclk / (mcanclkdiv + 1);
}

function calcAdcClk(sysclk, prescaleReg) {
    const prescaleValue = calcAdcPrescaleValue(prescaleReg);
    if (isNaN(prescaleValue) || prescaleValue <= 0) return NaN;
    return sysclk / prescaleValue;
}

function calcIntclk(oscclk, refdiv) {
    return oscclk / (refdiv + 1);
}

function calcVcoclk(oscclk, refdiv, imult) {
    return oscclk / (refdiv + 1) * imult;
}

//=============================================================================
// Test Cases: Helper Functions
//=============================================================================

console.log("\n=== Testing Helper Functions ===\n");

// Test getMaxSysclk - Gen2 devices
console.log("Testing getMaxSysclk() Gen2...");
assertEqual(getMaxSysclk("F2802x"), 40000000, "getMaxSysclk(F2802x) = 40MHz");
assertEqual(getMaxSysclk("F2803x"), 60000000, "getMaxSysclk(F2803x) = 60MHz");
assertEqual(getMaxSysclk("F2805x"), 60000000, "getMaxSysclk(F2805x) = 60MHz");
assertEqual(getMaxSysclk("F2806x"), 90000000, "getMaxSysclk(F2806x) = 90MHz");
// Gen3 devices
console.log("Testing getMaxSysclk() Gen3...");
assertEqual(getMaxSysclk("F28002x"), 100000000, "getMaxSysclk(F28002x) = 100MHz");
assertEqual(getMaxSysclk("F28004x"), 100000000, "getMaxSysclk(F28004x) = 100MHz");
assertEqual(getMaxSysclk("F280013x"), 120000000, "getMaxSysclk(F280013x) = 120MHz");
assertEqual(getMaxSysclk("F280015x"), 120000000, "getMaxSysclk(F280015x) = 120MHz");
assertEqual(getMaxSysclk("F28003x"), 120000000, "getMaxSysclk(F28003x) = 120MHz");
assertEqual(getMaxSysclk("F2807x"), 120000000, "getMaxSysclk(F2807x) = 120MHz");
assertEqual(getMaxSysclk("F28P55x"), 150000000, "getMaxSysclk(F28P55x) = 150MHz");
assertEqual(getMaxSysclk("F2837xD"), 200000000, "getMaxSysclk(F2837xD) = 200MHz");
assertEqual(getMaxSysclk("F2837xS"), 200000000, "getMaxSysclk(F2837xS) = 200MHz");
assertEqual(getMaxSysclk("F2838x"), 200000000, "getMaxSysclk(F2838x) = 200MHz");
assertEqual(getMaxSysclk("F28P65x"), 200000000, "getMaxSysclk(F28P65x) = 200MHz");
assert(isNaN(getMaxSysclk("UnknownDevice")), "getMaxSysclk(unknown) = NaN");

// Test calcFmultValue — NaN for invalid inputs (matches production)
console.log("Testing calcFmultValue()...");
assertEqual(calcFmultValue(0), 0.0, "calcFmultValue(0) = 0.0");
assertEqual(calcFmultValue(1), 0.25, "calcFmultValue(1) = 0.25");
assertEqual(calcFmultValue(2), 0.5, "calcFmultValue(2) = 0.5");
assertEqual(calcFmultValue(3), 0.75, "calcFmultValue(3) = 0.75");
assert(isNaN(calcFmultValue(4)), "calcFmultValue(4) = NaN (invalid)");
assert(isNaN(calcFmultValue(-1)), "calcFmultValue(-1) = NaN (invalid)");

// Test validateImult
console.log("Testing validateImult()...");
assertEqual(validateImult(0), true, "validateImult(0) = true");
assertEqual(validateImult(1), true, "validateImult(1) = true");
assertEqual(validateImult(127), true, "validateImult(127) = true");
assertEqual(validateImult(128), false, "validateImult(128) = false (out of range)");
assertEqual(validateImult(-1), false, "validateImult(-1) = false (negative)");

// Test validateRefdiv
console.log("Testing validateRefdiv()...");
assertEqual(validateRefdiv(0), true, "validateRefdiv(0) = true");
assertEqual(validateRefdiv(31), true, "validateRefdiv(31) = true");
assertEqual(validateRefdiv(32), false, "validateRefdiv(32) = false (out of range)");
assertEqual(validateRefdiv(-1), false, "validateRefdiv(-1) = false (negative)");

// Test validateOdiv
console.log("Testing validateOdiv()...");
assertEqual(validateOdiv(0), true, "validateOdiv(0) = true");
assertEqual(validateOdiv(31), true, "validateOdiv(31) = true");
assertEqual(validateOdiv(32), false, "validateOdiv(32) = false (out of range)");

// Test validateSysclkdivsel
console.log("Testing validateSysclkdivsel()...");
assertEqual(validateSysclkdivsel(0), true, "validateSysclkdivsel(0) = true");
assertEqual(validateSysclkdivsel(63), true, "validateSysclkdivsel(63) = true");
assertEqual(validateSysclkdivsel(64), false, "validateSysclkdivsel(64) = false (out of range)");

// Test calcAdcPrescaleValue — NaN for reserved/out-of-range (matches production)
console.log("Testing calcAdcPrescaleValue()...");
assertEqual(calcAdcPrescaleValue(0), 1.0, "calcAdcPrescaleValue(0) = /1");
assert(isNaN(calcAdcPrescaleValue(1)), "calcAdcPrescaleValue(1) = NaN (reserved)");
assertEqual(calcAdcPrescaleValue(2), 2.0, "calcAdcPrescaleValue(2) = /2");
assertEqual(calcAdcPrescaleValue(3), 2.5, "calcAdcPrescaleValue(3) = /2.5");
assertEqual(calcAdcPrescaleValue(4), 3.0, "calcAdcPrescaleValue(4) = /3");
assertEqual(calcAdcPrescaleValue(5), 3.5, "calcAdcPrescaleValue(5) = /3.5");
assertEqual(calcAdcPrescaleValue(6), 4.0, "calcAdcPrescaleValue(6) = /4");
assertEqual(calcAdcPrescaleValue(14), 8.0, "calcAdcPrescaleValue(14) = /8 (max integer)");
assertEqual(calcAdcPrescaleValue(16), 9.0, "calcAdcPrescaleValue(16) = /9");
assert(isNaN(calcAdcPrescaleValue(17)), "calcAdcPrescaleValue(17) = NaN (out of range)");

//=============================================================================
// Test Cases: Clock Calculators
//=============================================================================

console.log("\n=== Testing Clock Calculators ===\n");

// Test calcOscclk
console.log("Testing calcOscclk()...");
assertEqual(calcOscclk(0, 0), 10000000, "calcOscclk(INTOSC1) = 10MHz");
assertEqual(calcOscclk(1, 0), 10000000, "calcOscclk(INTOSC2) = 10MHz");
assertEqual(calcOscclk(2, 20000000), 20000000, "calcOscclk(XTAL=20MHz) = 20MHz");
assertEqual(calcOscclk(2, 25000000), 25000000, "calcOscclk(XTAL=25MHz) = 25MHz");
assertEqual(calcOscclk(2, 0), 20000000, "calcOscclk(XTAL=0) defaults to 20MHz");
assertEqual(calcOscclk(99, 0), 10000000, "calcOscclk(invalid) defaults to 10MHz");

// Test REFDIV/ODIV PLL calculation
console.log("Testing calcPllrawclk_RefdivOdiv()...");
// F280015x typical: OSCCLK=20MHz, REFDIV=0, IMULT=24, ODIV=1 -> 240MHz
assertApproxEqual(calcPllrawclk_RefdivOdiv(20000000, 0, 24, 1), 240000000, 1, "PLLRAWCLK: 20MHz, REFDIV=0, IMULT=24, ODIV=1 -> 240MHz");
// F28003x: OSCCLK=20MHz, REFDIV=0, IMULT=12, ODIV=0 -> 240MHz
assertApproxEqual(calcPllrawclk_RefdivOdiv(20000000, 0, 12, 0), 240000000, 1, "PLLRAWCLK: 20MHz, REFDIV=0, IMULT=12, ODIV=0 -> 240MHz");
// With REFDIV=1: 20MHz / 2 * 24 / 2 = 120MHz
assertApproxEqual(calcPllrawclk_RefdivOdiv(20000000, 1, 24, 1), 120000000, 1, "PLLRAWCLK: 20MHz, REFDIV=1, IMULT=24, ODIV=1 -> 120MHz");

// Test FMULT PLL calculation
console.log("Testing calcPllrawclk_Fmult()...");
// F2837xD typical: OSCCLK=10MHz, IMULT=20, FMULT=0 -> 200MHz
assertApproxEqual(calcPllrawclk_Fmult(10000000, 20, 0), 200000000, 1, "PLLRAWCLK: 10MHz * (20 + 0) = 200MHz");
// With FMULT=2 (0.5): 10MHz * (20 + 0.5) = 205MHz
assertApproxEqual(calcPllrawclk_Fmult(10000000, 20, 2), 205000000, 1, "PLLRAWCLK: 10MHz * (20 + 0.5) = 205MHz");

// Test PLLSYSCLK calculation
console.log("Testing calcPllsysclk()...");
// PLL enabled, no divider: PLLRAWCLK = 240MHz, SYSCLKDIVSEL=0 -> 240MHz
assertApproxEqual(calcPllsysclk(20000000, 240000000, 1, 0), 240000000, 1, "PLLSYSCLK: PLL enabled, div=1 -> 240MHz");
// PLL enabled, divider=1 (divide by 2): 240MHz / 2 = 120MHz
assertApproxEqual(calcPllsysclk(20000000, 240000000, 1, 1), 120000000, 1, "PLLSYSCLK: PLL enabled, div=2 -> 120MHz");
// PLL disabled: OSCCLK=20MHz, SYSCLKDIVSEL=0 -> 20MHz
assertApproxEqual(calcPllsysclk(20000000, 240000000, 0, 0), 20000000, 1, "PLLSYSCLK: PLL bypassed -> 20MHz");

// Test ADC clock calculation — NaN for reserved (matches production)
console.log("Testing calcAdcClk()...");
assertApproxEqual(calcAdcClk(120000000, 0), 120000000, 1, "ADCCLK: 120MHz / 1 = 120MHz");
assertApproxEqual(calcAdcClk(120000000, 2), 60000000, 1, "ADCCLK: 120MHz / 2 = 60MHz");
assertApproxEqual(calcAdcClk(120000000, 4), 40000000, 1, "ADCCLK: 120MHz / 3 = 40MHz");
assert(isNaN(calcAdcClk(120000000, 1)), "ADCCLK: prescale=1 (reserved) = NaN");

// Test INTCLK calculation
console.log("Testing calcIntclk()...");
assertApproxEqual(calcIntclk(20000000, 0), 20000000, 1, "INTCLK: 20MHz / (0+1) = 20MHz");
assertApproxEqual(calcIntclk(20000000, 1), 10000000, 1, "INTCLK: 20MHz / (1+1) = 10MHz");
assertApproxEqual(calcIntclk(20000000, 9), 2000000, 1, "INTCLK: 20MHz / (9+1) = 2MHz");

// Test VCOCLK calculation
console.log("Testing calcVcoclk()...");
// 20MHz / (0+1) * 24 = 480MHz
assertApproxEqual(calcVcoclk(20000000, 0, 24), 480000000, 1, "VCOCLK: 20MHz * 24 = 480MHz");
// 20MHz / (1+1) * 48 = 480MHz
assertApproxEqual(calcVcoclk(20000000, 1, 48), 480000000, 1, "VCOCLK: 10MHz * 48 = 480MHz");

//=============================================================================
// Test Cases: Clocking Checks
//=============================================================================

console.log("\n=== Testing Clocking Checks ===\n");

// SYSCLK check: 2MHz - maxsysclk
function checkSysclkMaxMin(sysclk, maxsysclk) {
    return sysclk >= 2000000 && sysclk <= maxsysclk;
}

console.log("Testing SYSCLK range check...");
assertEqual(checkSysclkMaxMin(120000000, 120000000), true, "SYSCLK 120MHz on 120MHz device = pass");
assertEqual(checkSysclkMaxMin(100000000, 120000000), true, "SYSCLK 100MHz on 120MHz device = pass");
assertEqual(checkSysclkMaxMin(2000000, 120000000), true, "SYSCLK 2MHz (min) = pass");
assertEqual(checkSysclkMaxMin(1000000, 120000000), false, "SYSCLK 1MHz (below min) = fail");
assertEqual(checkSysclkMaxMin(130000000, 120000000), false, "SYSCLK 130MHz on 120MHz device = fail");

// PLLRAWCLK check: 6MHz - 240MHz
function checkPllrawclkMaxMin(pllrawclk) {
    return pllrawclk >= 6000000 && pllrawclk <= 240000000;
}

console.log("Testing PLLRAWCLK range check...");
assertEqual(checkPllrawclkMaxMin(240000000), true, "PLLRAWCLK 240MHz = pass");
assertEqual(checkPllrawclkMaxMin(6000000), true, "PLLRAWCLK 6MHz = pass");
assertEqual(checkPllrawclkMaxMin(5000000), false, "PLLRAWCLK 5MHz = fail (below min)");
assertEqual(checkPllrawclkMaxMin(250000000), false, "PLLRAWCLK 250MHz = fail (above max)");

// VCOCLK check: 220MHz - 600MHz
function checkVcoclkMaxMin(vcoclk) {
    return vcoclk >= 220000000 && vcoclk <= 600000000;
}

console.log("Testing VCOCLK range check...");
assertEqual(checkVcoclkMaxMin(480000000), true, "VCOCLK 480MHz = pass");
assertEqual(checkVcoclkMaxMin(220000000), true, "VCOCLK 220MHz (min) = pass");
assertEqual(checkVcoclkMaxMin(600000000), true, "VCOCLK 600MHz (max) = pass");
assertEqual(checkVcoclkMaxMin(210000000), false, "VCOCLK 210MHz = fail (below min)");
assertEqual(checkVcoclkMaxMin(610000000), false, "VCOCLK 610MHz = fail (above max)");

// INTCLK check: 2MHz - 20MHz
function checkIntclkMaxMin(intclk) {
    return intclk >= 2000000 && intclk <= 20000000;
}

console.log("Testing INTCLK range check...");
assertEqual(checkIntclkMaxMin(10000000), true, "INTCLK 10MHz = pass");
assertEqual(checkIntclkMaxMin(2000000), true, "INTCLK 2MHz (min) = pass");
assertEqual(checkIntclkMaxMin(20000000), true, "INTCLK 20MHz (max) = pass");
assertEqual(checkIntclkMaxMin(1000000), false, "INTCLK 1MHz = fail (below min)");
assertEqual(checkIntclkMaxMin(25000000), false, "INTCLK 25MHz = fail (above max)");

// ADCCLK check: 5MHz - 60MHz (when powered on)
function checkAdcclkMaxMin(adcclk, powerdown) {
    if (powerdown === 0) return true;  // Powered down - skip check (strict equality)
    return adcclk >= 5000000 && adcclk <= 60000000;
}

console.log("Testing ADCCLK range check...");
assertEqual(checkAdcclkMaxMin(60000000, 1), true, "ADCCLK 60MHz (powered on) = pass");
assertEqual(checkAdcclkMaxMin(5000000, 1), true, "ADCCLK 5MHz (powered on) = pass");
assertEqual(checkAdcclkMaxMin(30000000, 1), true, "ADCCLK 30MHz (powered on) = pass");
assertEqual(checkAdcclkMaxMin(4000000, 1), false, "ADCCLK 4MHz (powered on) = fail (below min)");
assertEqual(checkAdcclkMaxMin(65000000, 1), false, "ADCCLK 65MHz (powered on) = fail (above max)");
assertEqual(checkAdcclkMaxMin(4000000, 0), true, "ADCCLK 4MHz (powered down) = pass (skipped)");
assertEqual(checkAdcclkMaxMin(100000000, 0), true, "ADCCLK 100MHz (powered down) = pass (skipped)");

// HRPWMCLK check: 60MHz - maxsysclk
function checkHrpwmclkMaxMin(hrpwmclk, maxsysclk) {
    return hrpwmclk >= 60000000 && hrpwmclk <= maxsysclk;
}

console.log("Testing HRPWMCLK range check...");
assertEqual(checkHrpwmclkMaxMin(120000000, 120000000), true, "HRPWMCLK 120MHz = pass");
assertEqual(checkHrpwmclkMaxMin(60000000, 120000000), true, "HRPWMCLK 60MHz (min) = pass");
assertEqual(checkHrpwmclkMaxMin(50000000, 120000000), false, "HRPWMCLK 50MHz = fail (below min for MEP)");

// MCANCLK check: 20MHz minimum
function checkMcanclkMin(mcanclk) {
    if (mcanclk === 0) return true;  // AUXPLL disabled
    return mcanclk >= 20000000;
}

console.log("Testing MCANCLK range check...");
assertEqual(checkMcanclkMin(80000000), true, "MCANCLK 80MHz = pass");
assertEqual(checkMcanclkMin(20000000), true, "MCANCLK 20MHz (min) = pass");
assertEqual(checkMcanclkMin(15000000), false, "MCANCLK 15MHz = fail (below min)");
assertEqual(checkMcanclkMin(0), true, "MCANCLK 0 (disabled) = pass");

//=============================================================================
// Test Cases: Device Applicability
//=============================================================================

console.log("\n=== Testing Device Applicability ===\n");

// Test device categorization
console.log("Testing device categorization...");
for (const device of DEVICES_WITH_CDT_SUPPORT) {
    const maxSysclk = getMaxSysclk(device);
    assert(!isNaN(maxSysclk), `getMaxSysclk(${device}) returns valid value`);
    assert(maxSysclk >= 40000000 && maxSysclk <= 200000000,
           `getMaxSysclk(${device}) in valid range (40-200MHz)`);
}

// Test PLL architecture categorization
console.log("Testing PLL architecture categorization...");
for (const device of DEVICES_WITH_REFDIV_ODIV) {
    assert(!DEVICES_WITH_FMULT.includes(device),
           `${device} is REFDIV/ODIV only (not FMULT)`);
}
for (const device of DEVICES_WITH_FMULT) {
    assert(!DEVICES_WITH_REFDIV_ODIV.includes(device),
           `${device} is FMULT only (not REFDIV/ODIV)`);
}

// Test ADC prescale categorization
console.log("Testing ADC prescale categorization...");
for (const device of DEVICES_WITH_ADC_INTEGER_PRESCALE) {
    assert(!DEVICES_WITH_ADC_HALFSTEP_PRESCALE.includes(device),
           `${device} is integer prescale only`);
}

//=============================================================================
// Test Cases: Gen2 Clock Calculators (C1 - previously untested)
//=============================================================================

console.log("\n=== Testing Gen2 Clock Calculators ===\n");

// Gen2 PLLRAWCLK: OSCCLK * DIV (or OSCCLK if DIV=0 → bypass)
console.log("Testing calcGen2Pllrawclk()...");
// F2806x: 10MHz * 18 = 180MHz
assertApproxEqual(calcGen2Pllrawclk(10000000, 18), 180000000, 1, "Gen2 PLLRAWCLK: 10MHz * 18 = 180MHz");
// F2802x: 10MHz * 8 = 80MHz
assertApproxEqual(calcGen2Pllrawclk(10000000, 8), 80000000, 1, "Gen2 PLLRAWCLK: 10MHz * 8 = 80MHz");
// PLL bypass (DIV=0): PLLRAWCLK = OSCCLK
assertApproxEqual(calcGen2Pllrawclk(10000000, 0), 10000000, 1, "Gen2 PLLRAWCLK: DIV=0 → bypass = 10MHz");

// Gen2 PLLSYSCLK: PLLRAWCLK / DIVSEL
console.log("Testing calcGen2Pllsysclk()...");
// DIVSEL=3 (/1): PLLRAWCLK=90MHz → SYSCLK=90MHz (F2806x: OSCCLK=10MHz, DIV=9)
assertApproxEqual(calcGen2Pllsysclk(90000000, 3), 90000000, 1, "Gen2 PLLSYSCLK: 90MHz / 1 → 90MHz (DIVSEL=3)");
// DIVSEL=2 (/2): 180MHz / 2 = 90MHz
assertApproxEqual(calcGen2Pllsysclk(180000000, 2), 90000000, 1, "Gen2 PLLSYSCLK: 180MHz / 2 → 90MHz (DIVSEL=2)");
// DIVSEL=0 (/4, safe default): 80MHz / 4 = 20MHz
assertApproxEqual(calcGen2Pllsysclk(80000000, 0), 20000000, 1, "Gen2 PLLSYSCLK: 80MHz / 4 → 20MHz (DIVSEL=0)");
// DIVSEL=1 also /4: 80MHz / 4 = 20MHz
assertApproxEqual(calcGen2Pllsysclk(80000000, 1), 20000000, 1, "Gen2 PLLSYSCLK: 80MHz / 4 → 20MHz (DIVSEL=1)");

// Gen2 LSPCLK divider
console.log("Testing calcGen2Lspclk()...");
assertApproxEqual(calcGen2Lspclk(90000000, 0), 90000000, 1, "Gen2 LSPCLK: /1 → 90MHz");
assertApproxEqual(calcGen2Lspclk(90000000, 1), 45000000, 1, "Gen2 LSPCLK: /2 → 45MHz");
assertApproxEqual(calcGen2Lspclk(90000000, 2), 22500000, 1, "Gen2 LSPCLK: /4 → 22.5MHz");
assertApproxEqual(calcGen2Lspclk(90000000, 4), 11250000, 1, "Gen2 LSPCLK: /8 → 11.25MHz");

// Gen2 ADCCLK
console.log("Testing calcGen2Adcclk()...");
assertApproxEqual(calcGen2Adcclk(90000000, 0, 0), 90000000, 1, "Gen2 ADCCLK: no divide → 90MHz");
assertApproxEqual(calcGen2Adcclk(90000000, 1, 0), 45000000, 1, "Gen2 ADCCLK: CLKDIV2EN → 45MHz");
assertApproxEqual(calcGen2Adcclk(90000000, 0, 1), 22500000, 1, "Gen2 ADCCLK: CLKDIV4EN → 22.5MHz");
// CLKDIV4EN takes priority over CLKDIV2EN
assertApproxEqual(calcGen2Adcclk(90000000, 1, 1), 22500000, 1, "Gen2 ADCCLK: CLKDIV4EN+2EN → /4 = 22.5MHz");

//=============================================================================
// Test Cases: AUXPLL Calculators (C2 - previously untested)
//=============================================================================

console.log("\n=== Testing AUXPLL Calculators ===\n");

// AUXPLL REFDIV/ODIV path (F2838x, F28P65x)
console.log("Testing calcAuxpllrawclk_RefdivOdiv()...");
// F2838x: OSCCLK=20MHz, REFDIV=0, IMULT=15, ODIV=1 → 20/1 * 15 / 2 = 150MHz
assertApproxEqual(calcAuxpllrawclk_RefdivOdiv(20000000, 0, 15, 1, 1), 150000000, 1,
    "AUXPLLRAWCLK: 20MHz, REFDIV=0, IMULT=15, ODIV=1 → 150MHz");
// Disabled (auxpllclken=0) → 0
assertEqual(calcAuxpllrawclk_RefdivOdiv(20000000, 0, 15, 1, 0), 0,
    "AUXPLLRAWCLK: disabled (PLLCLKEN=0) → 0");
// F28P65x: 25MHz XTAL, REFDIV=0, IMULT=8, ODIV=1 → 25 * 8 / 2 = 100MHz
assertApproxEqual(calcAuxpllrawclk_RefdivOdiv(25000000, 0, 8, 1, 1), 100000000, 1,
    "AUXPLLRAWCLK: 25MHz, REFDIV=0, IMULT=8, ODIV=1 → 100MHz");

// AUXPLL FMULT path (F2807x, F2837xD, F2837xS)
console.log("Testing calcAuxpllrawclk_Fmult()...");
// F2807x: OSCCLK=20MHz, IMULT=10, FMULT=0 → 200MHz
assertApproxEqual(calcAuxpllrawclk_Fmult(20000000, 10, 0, 1), 200000000, 1,
    "AUXPLLRAWCLK (FMULT): 20MHz * (10+0) = 200MHz");
// With FMULT=2 (0.5): 20 * 10.5 = 210MHz
assertApproxEqual(calcAuxpllrawclk_Fmult(20000000, 10, 2, 1), 210000000, 1,
    "AUXPLLRAWCLK (FMULT): 20MHz * (10+0.5) = 210MHz");
// Disabled → 0
assertEqual(calcAuxpllrawclk_Fmult(20000000, 10, 0, 0), 0,
    "AUXPLLRAWCLK (FMULT): disabled → 0");
// Invalid FMULT → NaN
assert(isNaN(calcAuxpllrawclk_Fmult(20000000, 10, 5, 1)),
    "AUXPLLRAWCLK (FMULT): invalid FMULT=5 → NaN");

//=============================================================================
// Test Cases: MCAN Clock Calculators (C2 - previously untested)
//=============================================================================

console.log("\n=== Testing MCAN Clock Calculators ===\n");

// MCAN from AUXPLL (F2838x, F28P65x)
console.log("Testing calcMcanclk_AuxpllSource()...");
// AUXPLLRAWCLK=80MHz, MCANCLKDIV=3 (→ /4): 80/4 = 20MHz
assertApproxEqual(calcMcanclk_AuxpllSource(80000000, 3), 20000000, 1,
    "MCANCLK (AUXPLL): 80MHz, DIV=3 (÷4) → 20MHz");
// No divide (MCANCLKDIV=0 → ÷1): 80MHz
assertApproxEqual(calcMcanclk_AuxpllSource(80000000, 0), 80000000, 1,
    "MCANCLK (AUXPLL): 80MHz, DIV=0 (÷1) → 80MHz");
// AUXPLL disabled → 0
assertEqual(calcMcanclk_AuxpllSource(0, 0), 0,
    "MCANCLK (AUXPLL): AUXPLL disabled → 0");

// MCAN from PLLCLK (F280015x, F28003x only — F28P55x is NOT in this path)
console.log("Testing calcMcanclk_PllSource() for F280015x/F28003x...");
// PLLRAWCLK=120MHz, MCANCLKDIV=5 (→ /6): 120/6 = 20MHz
assertApproxEqual(calcMcanclk_PllSource(120000000, 5), 20000000, 1,
    "MCANCLK (PLL): 120MHz, DIV=5 (÷6) → 20MHz");
// No MCANCLKDIV register → pass-through
assertApproxEqual(calcMcanclk_PllSource(120000000, undefined), 120000000, 1,
    "MCANCLK (PLL): no MCANCLKDIV register → PLLRAWCLK pass-through");

// MCAN on F28P55x: AUXCLKIN (external clock) — cannot auto-calculate
console.log("Testing F28P55x MCAN AUXCLKIN path...");
// F28P55x is in DEVICES_WITH_MCAN_AUXCLKIN; mcanclk calculator returns NaN
assert(DEVICES_WITH_MCAN_AUXCLKIN.includes("F28P55x"),
    "F28P55x is in DEVICES_WITH_MCAN_AUXCLKIN");
assert(!DEVICES_WITH_AUXPLL.includes("F28P55x"),
    "F28P55x has no AUXPLL — confirmed");
// mcanclkMinFreq check passes through NaN (board-defined clock cannot be validated)
function checkMcanclkMinWithAuxclkin(mcanclk) {
    if (mcanclk === 0) return true;
    if (isNaN(mcanclk)) return true;  // AUXCLKIN path — pass through
    return mcanclk >= 20000000;
}
assert(checkMcanclkMinWithAuxclkin(NaN) === true,
    "MCANCLK check: NaN (AUXCLKIN) passes through → OK");
assert(checkMcanclkMinWithAuxclkin(10000000) === false,
    "MCANCLK check: 10MHz < 20MHz → FAIL (for non-AUXCLKIN devices)");

// ADC topology verification
console.log("\nTesting ADC topology verification...");
// F28P65x: ADCA/B/C only — NO ADCD, NO ADCE
const DEVICES_WITH_ADCD = ["F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x"];
const DEVICES_WITH_ADCE = ["F28P55x"];
assert(!DEVICES_WITH_ADCD.includes("F28P65x"),
    "F28P65x correctly absent from DEVICES_WITH_ADCD (3-ADC device)");
assert(!DEVICES_WITH_ADCE.includes("F28P65x"),
    "F28P65x correctly absent from DEVICES_WITH_ADCE");
assert(DEVICES_WITH_ADCE.includes("F28P55x"),
    "F28P55x has ADCE (5-ADC device)");

// CAN topology verification
console.log("\nTesting CAN topology verification...");
// F28P65x: CANA (DCAN) + MCANA/MCANB — NO CANB (second DCAN)
const DEVICES_WITH_CANB = ["F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x"];
assert(!DEVICES_WITH_CANB.includes("F28P65x"),
    "F28P65x correctly absent from DEVICES_WITH_CANB (has MCANA/MCANB, not second DCAN)");
assert(DEVICES_WITH_MCAN.includes("F28P65x"),
    "F28P65x is in DEVICES_WITH_MCAN (has MCANA/MCANB)");
// F28P55x has MCAN only (no DCAN at all)
const DEVICES_WITH_CANA = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P65x"
];
assert(!DEVICES_WITH_CANA.includes("F28P55x"),
    "F28P55x has no DCAN — correctly absent from DEVICES_WITH_CANA");

//=============================================================================
// Test Summary
//=============================================================================

console.log("\n" + "=".repeat(60));
console.log("TEST SUMMARY");
console.log("=".repeat(60));
console.log(`Total Tests: ${testsPassed + testsFailed}`);
console.log(`Passed: ${testsPassed}`);
console.log(`Failed: ${testsFailed}`);
console.log("=".repeat(60));

if (testsFailed > 0) {
    console.log("\nFailed tests:");
    testResults.filter(t => !t.passed).forEach(t => {
        console.log(`  - ${t.name}${t.details ? ": " + t.details : ""}`);
    });
    process.exit(1);
} else {
    console.log("\nAll tests passed!");
    process.exit(0);
}
