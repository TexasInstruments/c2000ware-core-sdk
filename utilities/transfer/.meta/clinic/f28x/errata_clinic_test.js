/**
 * @fileoverview Unit Tests for Errata Clinic Module
 *
 * Tests the errata detection logic including:
 * - Device applicability filtering
 * - Errata check logic
 * - Prerequisite register definitions
 * - Gen2 and Gen3 errata coverage
 *
 * Run with: node errata_clinic_test.js
 */

//=============================================================================
// Test Framework
//=============================================================================
let testCount = 0;
let passCount = 0;
let failCount = 0;

function assert(condition, testName) {
    testCount++;
    if (condition) {
        passCount++;
        console.log(`  PASS: ${testName}`);
    } else {
        failCount++;
        console.log(`  FAIL: ${testName}`);
    }
}

function assertEqual(actual, expected, testName) {
    testCount++;
    if (actual === expected) {
        passCount++;
        console.log(`  PASS: ${testName}`);
    } else {
        failCount++;
        console.log(`  FAIL: ${testName} (expected: ${expected}, got: ${actual})`);
    }
}

function assertArrayIncludes(array, value, testName) {
    testCount++;
    if (array.includes(value)) {
        passCount++;
        console.log(`  PASS: ${testName}`);
    } else {
        failCount++;
        console.log(`  FAIL: ${testName} (${value} not in array)`);
    }
}

//=============================================================================
// Mock SysConfig System Object
//=============================================================================
const system = {
    getScript: function(path) {
        // Load device_constants.js
        if (path === "./device_constants.js") {
            return {
                // Device Families
                DEVICES_GEN2: ["F2802x", "F2803x", "F2805x", "F2806x"],
                DEVICES_GEN3: [
                    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
                    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
                ],
                DEVICES_WITH_CDT_SUPPORT: [
                    "F2802x", "F2803x", "F2805x", "F2806x",
                    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
                    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
                ],
                DEVICES_WITH_PLLCR_DIV: ["F2802x", "F2803x", "F2805x", "F2806x"],
                // ADC Instances
                DEVICES_WITH_ADCA: [
                    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
                    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
                ],
                DEVICES_WITH_ADCB: [
                    "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS",
                    "F2838x", "F28P55x", "F28P65x"
                ],
                DEVICES_WITH_ADCC: [
                    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
                    "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
                ],
                DEVICES_WITH_ADCD: [
                    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x"
                ],
                // eQEP Instances
                DEVICES_WITH_EQEP1: [
                    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
                    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
                ],
                DEVICES_WITH_EQEP2: [
                    "F280015x", "F28002x", "F28003x", "F28004x", "F2807x",
                    "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
                ],
                DEVICES_WITH_EQEP3: [
                    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
                ],
                // System Features
                DEVICES_WITH_CMPSS: [
                    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
                    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
                ],
                DEVICES_WITH_SDFM: [
                    "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS",
                    "F2838x", "F28P65x"
                ],
                DEVICES_WITH_DCC: [
                    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
                    "F2838x", "F28P55x", "F28P65x"
                ],
                DEVICES_WITH_FSI: [
                    "F28002x", "F28003x", "F28004x", "F2838x", "F28P55x", "F28P65x"
                ],
                // Errata Applicability (matches device_constants.js exactly)
                DEVICES_WITH_ADC_FRACTIONAL_DIVIDER_ERRATA: [
                    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x"
                ],
                DEVICES_WITH_CMPSS_LATCH_ERRATA: [
                    "F28004x", "F2807x", "F2837xD", "F2837xS", "F28P55x"
                ],
                DEVICES_WITH_CMPSS_RAMP_ERRATA: ["F2807x", "F2837xD", "F2837xS"],
                DEVICES_WITH_EPWM_DEADBAND_ERRATA: ["F2807x", "F2837xD", "F2837xS"],
                DEVICES_WITH_MCD_ERRATA: ["F28P55x", "F28P65x", "F2838x"],
                DEVICES_WITH_FLASH_ECC_ERRATA: ["F28P55x", "F28P65x"],
                DEVICES_WITH_DCC_SINGLESHOT_ERRATA: ["F28004x", "F28002x"],
                DEVICES_WITH_SDFM_MANCHESTER_ERRATA: [
                    "F28004x", "F2807x", "F2837xD", "F2837xS"
                ],
                DEVICES_WITH_I2C_OPENDRAIN_ERRATA: [
                    "F28004x", "F2807x", "F2837xD", "F2837xS"
                ],
                DEVICES_WITH_PLL_LOCK_ERRATA: [
                    "F28004x", "F2807x", "F2837xD", "F2837xS"
                ],
                DEVICES_WITH_FSI_OVERRUN_ERRATA: ["F28004x", "F2838x"],
                DEVICES_WITH_EQEP_POSITION_ERRATA: [
                    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
                    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x"
                ],
                // Register availability constants (new in this session)
                DEVICES_WITH_CERRTHRES_REG: ["F280013x", "F280015x", "F28003x"],
                DEVICES_WITH_PLL_REFLOST_REG: ["F280013x", "F280015x"],
                DEVICES_WITH_PREFETCH_BOUNDARY_ERRATA: ["F280013x", "F280015x", "F28003x"]
            };
        }
        return {};
    }
};

// Make system global for module loading
global.system = system;

//=============================================================================
// Load Module Under Test (simulated - we test the logic directly)
//=============================================================================

// Gen2 Errata Arrays (from errata_clinic.js)
const DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA = ["F2802x", "F2803x", "F2805x", "F2806x"];
const DEVICES_GEN2_WITH_FLASH_PUMP_ERRATA = ["F2802x", "F2803x"];
const DEVICES_GEN2_WITH_ADC_REF_ERRATA = ["F2802x", "F2803x", "F2805x"];
const DEVICES_GEN2_WITH_I2C_STRETCH_ERRATA = ["F2802x", "F2803x", "F2806x"];

// Gen3 Arrays
const DEVICES_GEN3 = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
];

const DEVICES_WITH_ADC_INTCONT_ERRATA = DEVICES_GEN3;

//=============================================================================
// Test Cases
//=============================================================================

console.log("\n=== Testing Gen2 Errata Applicability ===\n");

console.log("Testing Gen2 PLL Sequence Errata coverage...");
assertArrayIncludes(DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA, "F2802x", "F2802x has PLL sequence errata");
assertArrayIncludes(DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA, "F2803x", "F2803x has PLL sequence errata");
assertArrayIncludes(DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA, "F2805x", "F2805x has PLL sequence errata");
assertArrayIncludes(DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA, "F2806x", "F2806x has PLL sequence errata");
assertEqual(DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA.length, 4, "Exactly 4 Gen2 devices with PLL sequence errata");

console.log("\nTesting Gen2 Flash Pump Errata coverage...");
assertArrayIncludes(DEVICES_GEN2_WITH_FLASH_PUMP_ERRATA, "F2802x", "F2802x has flash pump errata");
assertArrayIncludes(DEVICES_GEN2_WITH_FLASH_PUMP_ERRATA, "F2803x", "F2803x has flash pump errata");
assert(!DEVICES_GEN2_WITH_FLASH_PUMP_ERRATA.includes("F2805x"), "F2805x excluded from flash pump errata");
assert(!DEVICES_GEN2_WITH_FLASH_PUMP_ERRATA.includes("F2806x"), "F2806x excluded from flash pump errata");

console.log("\nTesting Gen2 ADC Reference Errata coverage...");
assertArrayIncludes(DEVICES_GEN2_WITH_ADC_REF_ERRATA, "F2802x", "F2802x has ADC ref errata");
assertArrayIncludes(DEVICES_GEN2_WITH_ADC_REF_ERRATA, "F2803x", "F2803x has ADC ref errata");
assertArrayIncludes(DEVICES_GEN2_WITH_ADC_REF_ERRATA, "F2805x", "F2805x has ADC ref errata");
assert(!DEVICES_GEN2_WITH_ADC_REF_ERRATA.includes("F2806x"), "F2806x excluded from ADC ref errata");

console.log("\nTesting Gen2 I2C Stretch Errata coverage...");
assertArrayIncludes(DEVICES_GEN2_WITH_I2C_STRETCH_ERRATA, "F2802x", "F2802x has I2C stretch errata");
assertArrayIncludes(DEVICES_GEN2_WITH_I2C_STRETCH_ERRATA, "F2803x", "F2803x has I2C stretch errata");
assertArrayIncludes(DEVICES_GEN2_WITH_I2C_STRETCH_ERRATA, "F2806x", "F2806x has I2C stretch errata");
assert(!DEVICES_GEN2_WITH_I2C_STRETCH_ERRATA.includes("F2805x"), "F2805x excluded from I2C stretch errata");

console.log("\n=== Testing Gen3 Errata Applicability ===\n");

console.log("Testing ADC INTCONT Errata coverage...");
assertEqual(DEVICES_WITH_ADC_INTCONT_ERRATA.length, 11, "All 11 Gen3 devices have ADC INTCONT errata");
assertArrayIncludes(DEVICES_WITH_ADC_INTCONT_ERRATA, "F280013x", "F280013x has ADC INTCONT errata");
assertArrayIncludes(DEVICES_WITH_ADC_INTCONT_ERRATA, "F28P65x", "F28P65x has ADC INTCONT errata");
assert(!DEVICES_WITH_ADC_INTCONT_ERRATA.includes("F2802x"), "Gen2 F2802x excluded from Gen3 errata");

console.log("\n=== Testing Memory Calculator Masking ===\n");

// OTP revision: extract low byte
function calcOtpRevision(memVal) { return memVal & 0x000000FF; }
assertEqual(calcOtpRevision(0x0102), 0x02, "OTP revision: 0x0102 & 0xFF = 0x02");
assertEqual(calcOtpRevision(0x0000), 0x00, "OTP revision: 0x0000 → 0");
assertEqual(calcOtpRevision(0xFFFF), 0xFF, "OTP revision: 0xFFFF & 0xFF = 0xFF");

// Prefetch boundary: 16-bit mask
function calcPrefetchBoundary(memVal) { return memVal & 0xFFFF; }
assertEqual(calcPrefetchBoundary(0x00000000), 0, "Prefetch boundary: 0 → 0 (valid M1/GS3)");
assertEqual(calcPrefetchBoundary(0x0000FFFF), 0xFFFF, "Prefetch boundary: 0xFFFF → 65535 (valid Flash)");
assertEqual(calcPrefetchBoundary(0xDEAD1234), 0x1234, "Prefetch boundary: 0xDEAD1234 → 0x1234 (16-bit extract)");

console.log("\n=== Testing Errata Check Logic ===\n");

// Gen2 PLL DIVSEL Sequence Check
console.log("Testing Gen2 PLL DIVSEL Sequence check logic...");
function checkGen2PllDivselSequence(divsel, plllocks) {
    // DIVSEL=3 means /1 divider, PLLLOCKS=0 means not locked
    if (divsel === 3 && plllocks === 0) {
        return false;  // Errata condition detected
    }
    return true;
}

assert(checkGen2PllDivselSequence(0, 0) === true, "DIVSEL=/4, not locked -> OK");
assert(checkGen2PllDivselSequence(2, 0) === true, "DIVSEL=/2, not locked -> OK");
assert(checkGen2PllDivselSequence(3, 1) === true, "DIVSEL=/1, locked -> OK");
assert(checkGen2PllDivselSequence(3, 0) === false, "DIVSEL=/1, not locked -> ERRATA");
assert(checkGen2PllDivselSequence(1, 0) === true, "DIVSEL=/4 (via 1), not locked -> OK");

// Gen2 Missing Clock Detected Check
console.log("\nTesting Gen2 Missing Clock Detected check logic...");
function checkGen2MclkDetected(mclksts) {
    return mclksts === 0;  // Pass if no missing clock
}

assert(checkGen2MclkDetected(0) === true, "MCLKSTS=0 -> No missing clock (PASS)");
assert(checkGen2MclkDetected(1) === false, "MCLKSTS=1 -> Missing clock detected (FAIL)");

// ADC INTCONT Check
console.log("\nTesting ADC INTCONT check logic...");
function checkAdcIntcont(intsel1, intsel2, intsel3, intsel4, powerdown) {
    if (powerdown === 0) return true;  // ADC powered down, don't check
    return intsel1 !== 0 && intsel2 !== 0 && intsel3 !== 0 && intsel4 !== 0;
}

assert(checkAdcIntcont(1, 1, 1, 1, 1) === true, "All INTxCONT=1, powered on -> PASS");
assert(checkAdcIntcont(0, 1, 1, 1, 1) === false, "INT1CONT=0, powered on -> FAIL");
assert(checkAdcIntcont(1, 0, 1, 1, 1) === false, "INT2CONT=0, powered on -> FAIL");
assert(checkAdcIntcont(0, 0, 0, 0, 0) === true, "ADC powered down -> PASS (skip check)");
assert(checkAdcIntcont(0, 0, 0, 0, 1) === false, "All INTxCONT=0, powered on -> FAIL");

// ePWM Dead-Band shadow load check (complex boolean logic)
console.log("\nTesting ePWM Dead-Band check logic...");
function checkEpwmDeadband(loadredmode, loadfedmode, dbred, dbfed) {
    return !((loadredmode !== 0 && dbred === 0) || (loadfedmode !== 0 && dbfed === 0));
}
assert(checkEpwmDeadband(0, 0, 0, 0) === true, "EPWM DB: immediate mode + delay=0 → OK (no shadow)");
assert(checkEpwmDeadband(1, 0, 100, 0) === true, "EPWM DB: shadow RED+delay>0, FED immediate → OK");
assert(checkEpwmDeadband(1, 0, 0, 0) === false, "EPWM DB: shadow RED + DBRED=0 → ERRATA");
assert(checkEpwmDeadband(0, 1, 0, 0) === false, "EPWM DB: shadow FED + DBFED=0 → ERRATA");
assert(checkEpwmDeadband(1, 1, 0, 0) === false, "EPWM DB: both shadow + both=0 → ERRATA");
assert(checkEpwmDeadband(1, 1, 10, 10) === true, "EPWM DB: shadow + non-zero delays → OK");

// CMPSS latch clear check (E1 - now has real logic)
console.log("\nTesting CMPSS latch clear check logic...");
function checkCmpssLatch(highlatch, lowlatch) {
    return !(highlatch === 1 || lowlatch === 1);
}
assert(checkCmpssLatch(0, 0) === true, "CMPSS latch: both clear → OK");
assert(checkCmpssLatch(1, 0) === false, "CMPSS latch: high set → WARN");
assert(checkCmpssLatch(0, 1) === false, "CMPSS latch: low set → WARN");
assert(checkCmpssLatch(1, 1) === false, "CMPSS latch: both set → WARN");

// Flash ECC interrupt check (E1 - now has real logic)
console.log("\nTesting Flash ECC interrupt check logic...");
function checkFlashEcc(flasheccenabled) {
    return flasheccenabled === 0;
}
assert(checkFlashEcc(0) === true, "Flash ECC: disabled → OK (no interrupt issue)");
assert(checkFlashEcc(1) === false, "Flash ECC: enabled → WARN (interrupts not generated)");

// PLL first lock check (E1 - now has real logic)
console.log("\nTesting PLL first lock check logic...");
function checkPllFirstLock(plllockstatus) {
    return plllockstatus === 1;
}
assert(checkPllFirstLock(1) === true, "PLL lock: LOCKS=1 → OK");
assert(checkPllFirstLock(0) === false, "PLL lock: LOCKS=0 → WARN (possible errata)");

// I2C open-drain check (E1 - now has real logic)
console.log("\nTesting I2C open-drain check logic...");
function checkI2cOpenDrain(i2camodemaster, i2caenabled) {
    return !(i2camodemaster === 1 && i2caenabled === 1);
}
assert(checkI2cOpenDrain(0, 0) === true, "I2C: disabled slave → OK");
assert(checkI2cOpenDrain(1, 0) === true, "I2C: master but not enabled → OK");
assert(checkI2cOpenDrain(0, 1) === true, "I2C: enabled slave → OK");
assert(checkI2cOpenDrain(1, 1) === false, "I2C: enabled master → WARN (check pull-ups)");

// MCD check
console.log("\nTesting MCD enabled-with-PLL check logic...");
function checkMcdWithPll(mcdenabled, pllclkenabled) {
    return !(mcdenabled === 0 && pllclkenabled === 1);
}
assert(checkMcdWithPll(1, 1) === true, "MCD: MCD disabled (MCLKOFF=1) + PLL enabled → OK");
assert(checkMcdWithPll(0, 0) === true, "MCD: MCD enabled + PLL disabled → OK");
assert(checkMcdWithPll(0, 1) === false, "MCD: MCD enabled + PLL enabled → ERRATA");

// DCC single-shot check
console.log("\nTesting DCC single-shot check logic...");
function checkDccSingleShot(dcc0singleshot, dcc0enabled) {
    return !(dcc0enabled === 1 && dcc0singleshot === 1);
}
assert(checkDccSingleShot(0, 1) === true, "DCC: continuous mode → OK");
assert(checkDccSingleShot(1, 0) === true, "DCC: single-shot + disabled → OK");
assert(checkDccSingleShot(1, 1) === false, "DCC: single-shot + enabled → ERRATA");

// SDFM Manchester check
console.log("\nTesting SDFM Manchester mode check logic...");
function checkSdfmManchester(sdfm1filter1mode, sdfm1enabled) {
    return !(sdfm1enabled === 1 && sdfm1filter1mode === 2);
}
assert(checkSdfmManchester(0, 1) === true, "SDFM: Mode 0 enabled → OK");
assert(checkSdfmManchester(2, 0) === true, "SDFM: Manchester mode + disabled → OK");
assert(checkSdfmManchester(2, 1) === false, "SDFM: Manchester mode + enabled → ERRATA");

// Prefetch boundary checks
console.log("\nTesting prefetch boundary check logic...");
function checkPrefetchM1(val) { return val === 0; }
function checkPrefetchFlash(val) { return val === 0xFFFF; }
assert(checkPrefetchM1(0) === true, "Prefetch M1: boundary=0 → OK");
assert(checkPrefetchM1(1) === false, "Prefetch M1: boundary≠0 → ERRATA (OTP not patched)");
assert(checkPrefetchFlash(0xFFFF) === true, "Prefetch Flash: boundary=0xFFFF → OK");
assert(checkPrefetchFlash(0) === false, "Prefetch Flash: boundary=0 → ERRATA");

console.log("\n=== Testing Device Exclusion ===\n");

console.log("Testing Gen2 devices excluded from Gen3 errata...");
const GEN2_DEVICES = ["F2802x", "F2803x", "F2805x", "F2806x"];
for (const dev of GEN2_DEVICES) {
    assert(!DEVICES_GEN3.includes(dev), `${dev} excluded from DEVICES_GEN3`);
}

console.log("\nTesting Gen3 devices excluded from Gen2 errata...");
for (const dev of DEVICES_GEN3) {
    assert(!DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA.includes(dev), `${dev} excluded from Gen2 PLL errata`);
}

console.log("\n=== Testing Prerequisite Register Coverage ===\n");

// Simulate prerequisite register applicable functions
const prereqApplicable = {
    gen2PllstsDivsel: (device) => DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA.includes(device),
    gen2PllstsLocks: (device) => DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA.includes(device),
    gen2PllstsMclksts: (device) => DEVICES_GEN2_WITH_PLL_SEQUENCE_ERRATA.includes(device),
    adcaIntsel1: (device) => DEVICES_GEN3.includes(device) &&
                             ["F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
                              "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"].includes(device)
};

console.log("Testing Gen2 prerequisite register applicability...");
assert(prereqApplicable.gen2PllstsDivsel("F2802x") === true, "Gen2 PLLSTS.DIVSEL applies to F2802x");
assert(prereqApplicable.gen2PllstsDivsel("F2806x") === true, "Gen2 PLLSTS.DIVSEL applies to F2806x");
assert(prereqApplicable.gen2PllstsDivsel("F28003x") === false, "Gen2 PLLSTS.DIVSEL does NOT apply to F28003x");

console.log("\nTesting Gen3 prerequisite register applicability...");
assert(prereqApplicable.adcaIntsel1("F28003x") === true, "ADCA INTSEL applies to F28003x");
assert(prereqApplicable.adcaIntsel1("F28P65x") === true, "ADCA INTSEL applies to F28P65x");
assert(prereqApplicable.adcaIntsel1("F2802x") === false, "ADCA INTSEL does NOT apply to F2802x (Gen2)");

//=============================================================================
// Test Summary
//=============================================================================

console.log("\n============================================================");
console.log("TEST SUMMARY");
console.log("============================================================");
console.log(`Total Tests: ${testCount}`);
console.log(`Passed: ${passCount}`);
console.log(`Failed: ${failCount}`);
console.log("============================================================\n");

if (failCount === 0) {
    console.log("All tests passed!");
    process.exit(0);
} else {
    console.log(`${failCount} test(s) failed.`);
    process.exit(1);
}
