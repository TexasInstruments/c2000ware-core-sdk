//=============================================================================
// Centralized Device Constants for CDT Clinic Modules
//=============================================================================
// This file contains all device support arrays used across clocking_clinic.js,
// errata_clinic.js, and export_mods_common.js. Import from this file to ensure
// consistency across all modules.
//
// Usage:
//   const { DEVICES_WITH_CDT_SUPPORT, DEVICES_WITH_ADCA, ... } = require('./device_constants.js');
//   // Note: DEVICES_GEN3 is also exported for backward compatibility
//=============================================================================

//=============================================================================
// Device Name Normalization
//=============================================================================
// Maps specific part numbers (e.g., "TMS320F280049C") to family names (e.g., "F28004x")
// This handles the case where SysConfig returns specific part numbers instead of
// family names depending on the device/package selection.

/**
 * Normalize a device name to its family name
 * @param {string} deviceName - Device name from SysConfig (can be family name or part number)
 * @returns {string} Normalized family name (e.g., "F28004x")
 */
function normalizeDeviceName(deviceName) {
    if (!deviceName) return deviceName;

    // If already a family name, return as-is (includes F28Pxx-series and F2807x/F2837x/F2838x)
    if (deviceName.match(/^F28[0-9P]\d{1,3}x[DS]?$/)) {
        return deviceName;
    }

    // Map part numbers to family names
    // Pattern: TMS320Fxxxxxx or Fxxxxxx -> family name
    const partNumberPatterns = [
        // Gen2 devices
        { pattern: /^(?:TMS320)?F2802[0-7]/i, family: "F2802x" },
        { pattern: /^(?:TMS320)?F2803[0-5]/i, family: "F2803x" },
        { pattern: /^(?:TMS320)?F2805[0-7]/i, family: "F2805x" },
        { pattern: /^(?:TMS320)?F2806[2-9]/i, family: "F2806x" },
        // Gen3 devices
        // F280013x: variants are F2800131 (32KB), F2800133 (128KB), F2800137 (256KB)
        //   digit after F28001 is 3 (for all variants starting with F280013)
        { pattern: /^(?:TMS320)?F28001[37]/i, family: "F280013x" },
        // F280015x: variants are F2800152/155/156 (64KB), F2800157/158 (128KB)
        //   digit after F28001 is 5 (for all F280015x variants)
        { pattern: /^(?:TMS320)?F28001[56]/i, family: "F280015x" },
        // F28002x: variants include F280023 (128KB), F280025 (256KB), F280027/28/29 (512KB)
        //   Pattern was [5-9] which incorrectly missed F280023 and F280024 — corrected to [0-9]
        { pattern: /^(?:TMS320)?F28002[0-9]/i, family: "F28002x" },
        { pattern: /^(?:TMS320)?F28003[0-9]/i, family: "F28003x" },
        { pattern: /^(?:TMS320)?F28004[0-9]/i, family: "F28004x" },
        { pattern: /^(?:TMS320)?F2807[0-9]/i, family: "F2807x" },
        // F2837x: S suffix = single core, D suffix = dual core
        { pattern: /^(?:TMS320)?F2837[0-9]S/i, family: "F2837xS" },
        { pattern: /^(?:TMS320)?F2837[0-9]D/i, family: "F2837xD" },
        { pattern: /^(?:TMS320)?F2838[0-9]/i, family: "F2838x" },
        { pattern: /^(?:TMS320)?F28P55/i, family: "F28P55x" },
        { pattern: /^(?:TMS320)?F28P65/i, family: "F28P65x" },
    ];

    for (const { pattern, family } of partNumberPatterns) {
        if (pattern.test(deviceName)) {
            return family;
        }
    }

    // If no match found, log warning and return original (might be a new device)
    console.log("Warning: Device name '" + deviceName + "' did not match any known pattern - using as-is");
    return deviceName;
}

//=============================================================================
// Generation 2 Device Family (Pure C28x - no Concerto)
//=============================================================================

// Gen2 devices - Pure C28x architecture
// Codenames: PiccoloA (F2802x), PiccoloB (F2803x), Gizmo (F2805x), Octave (F2806x)
const DEVICES_GEN2 = ["F2802x", "F2803x", "F2805x", "F2806x"];

//=============================================================================
// Generation 3 Device Family
//=============================================================================

// All supported Gen3 devices
const DEVICES_GEN3 = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
];

//=============================================================================
// All Supported Devices (Gen2 + Gen3)
//=============================================================================
const DEVICES_ALL = [...DEVICES_GEN2, ...DEVICES_GEN3];

// Alias for backward compatibility (includes all supported devices now)
const DEVICES_WITH_CDT_SUPPORT = DEVICES_ALL;

//=============================================================================
// PLL Architecture Groups
//=============================================================================

// Gen2 devices using PLLCR/PLLSTS PLL architecture
// Formula: PLLRAWCLK = OSCCLK * DIV, SYSCLK = PLLRAWCLK / DIVSEL
// Registers: SysCtrlRegs.PLLCR.DIV, SysCtrlRegs.PLLSTS.DIVSEL
const DEVICES_WITH_PLLCR_DIV = ["F2802x", "F2803x", "F2805x", "F2806x"];

// Gen3 devices using REFDIV/ODIV PLL architecture
const DEVICES_WITH_REFDIV_ODIV = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F2838x", "F28P55x", "F28P65x"
];

// Devices using pure FMULT PLL architecture (OSCCLK * (IMULT + FMULT))
// Note: F28004x is excluded - it has FMULT+ODIV hybrid architecture
const DEVICES_WITH_FMULT = ["F2807x", "F2837xD", "F2837xS"];

// Devices using hybrid FMULT+ODIV architecture (OSCCLK * (IMULT + FMULT) / ODIV)
// F28004x has FMULT and ODIV but no REFDIV - unique among C2000 devices
const DEVICES_WITH_FMULT_ODIV = ["F28004x"];

//=============================================================================
// Maximum SYSCLK Frequency Groups
//=============================================================================

// Gen2 Max SYSCLK Groups
const DEVICES_WITH_40MHZ_MAX_SYSCLK = ["F2802x"];
const DEVICES_WITH_60MHZ_MAX_SYSCLK_GEN2 = ["F2803x", "F2805x"];
const DEVICES_WITH_90MHZ_MAX_SYSCLK = ["F2806x"];

// Gen3 Max SYSCLK Groups
const DEVICES_WITH_100MHZ_MAX_SYSCLK = ["F28002x", "F28004x"];
const DEVICES_WITH_120MHZ_MAX_SYSCLK = ["F280013x", "F280015x", "F28003x", "F2807x"];
const DEVICES_WITH_150MHZ_MAX_SYSCLK = ["F28P55x"];
const DEVICES_WITH_200MHZ_MAX_SYSCLK = ["F2837xD", "F2837xS", "F2838x", "F28P65x"];

// Short aliases for backward compatibility
const DEVICES_40MHZ = DEVICES_WITH_40MHZ_MAX_SYSCLK;
const DEVICES_60MHZ_GEN2 = DEVICES_WITH_60MHZ_MAX_SYSCLK_GEN2;
const DEVICES_90MHZ = DEVICES_WITH_90MHZ_MAX_SYSCLK;
const DEVICES_100MHZ = DEVICES_WITH_100MHZ_MAX_SYSCLK;
const DEVICES_120MHZ = DEVICES_WITH_120MHZ_MAX_SYSCLK;
const DEVICES_150MHZ = DEVICES_WITH_150MHZ_MAX_SYSCLK;
const DEVICES_200MHZ = DEVICES_WITH_200MHZ_MAX_SYSCLK;

//=============================================================================
// ADC Instance Availability
// Source: driverlib/<device>/driverlib/adc.h
//=============================================================================

// Gen2 devices have a single ADC module (not named ADCA/B/C)
const DEVICES_GEN2_WITH_ADC = ["F2802x", "F2803x", "F2805x", "F2806x"];

// Gen3 ADC instances
const DEVICES_WITH_ADCA = DEVICES_GEN3;
const DEVICES_WITH_ADCB = [
    "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS",
    "F2838x", "F28P55x", "F28P65x"
];
// Note: F2807x has ADCD but NOT ADCC (unique among Gen3 devices).
// F280013x and F280015x have ADC-A and ADC-C only (no ADC-B) — see DEVICES_WITH_ADCB.
const DEVICES_WITH_ADCC = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
    "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
    // F2807x intentionally excluded — it has ADCD instead of ADCC
];
// Note: F28P65x has ONLY ADCA, ADCB, ADCC — it does NOT have ADCD or ADCE
//       (confirmed by F28P65x hardware; the device was designed with 3 ADC modules)
const DEVICES_WITH_ADCD = ["F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x"];
// F28P55x is the only device with a 5th ADC instance (ADCE)
// F28P65x does NOT have ADCE (it has only ADCA/B/C)
const DEVICES_WITH_ADCE = ["F28P55x"];

//=============================================================================
// ADC Prescale Constraints
// Source: driverlib/<device>/driverlib/adc.h, ADC_ClkPrescale enum
//=============================================================================

// Gen2 ADC prescale: CLKDIV2EN/CLKDIV4EN bits provide /1, /2, /4 dividers
// ADCCLK max ~25 MHz for Gen2 devices
const DEVICES_WITH_ADC_GEN2_PRESCALE = ["F2802x", "F2803x", "F2805x", "F2806x"];

// Gen3 Integer dividers only (1, 2, 3, 4, 5, 6, 7, 8)
const DEVICES_WITH_ADC_INTEGER_PRESCALE = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x"
];

// Half-step dividers (1, 2, 2.5, 3, 3.5, 4, 4.5, ... 8.5)
const DEVICES_WITH_ADC_HALFSTEP_PRESCALE = [
    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
];

// Devices with configurable ADC resolution (12-bit vs 16-bit) and signal mode
const DEVICES_WITH_ADC_CONFIGURABLE_RESOLUTION = [
    "F2837xD", "F2837xS", "F2838x", "F28P65x"
];

// Short aliases for backward compatibility
const DEVICES_ADC_GEN2_PRESCALE = DEVICES_WITH_ADC_GEN2_PRESCALE;
const DEVICES_ADC_INTEGER_PRESCALE = DEVICES_WITH_ADC_INTEGER_PRESCALE;
const DEVICES_ADC_HALFSTEP_PRESCALE = DEVICES_WITH_ADC_HALFSTEP_PRESCALE;

//=============================================================================
// Gen2 Peripheral Availability
// Source: Device datasheets (SPRS523, SPRS584, SPRS797, SPRS698)
//=============================================================================

// Gen2 devices with CLA (Control Law Accelerator)
const DEVICES_GEN2_WITH_CLA = ["F2803x", "F2806x"];

// Gen2 devices with eCAN (legacy CAN 2.0)
const DEVICES_GEN2_WITH_ECAN = ["F2803x", "F2805x", "F2806x"];

// Gen2 devices with DMA
const DEVICES_GEN2_WITH_DMA = ["F2803x", "F2806x"];

// Gen2 devices with USB
const DEVICES_GEN2_WITH_USB = ["F2806x"];

// Gen2 devices with LIN
const DEVICES_GEN2_WITH_LIN = ["F2802x", "F2803x"];

// Gen2 devices with HRPWM
const DEVICES_GEN2_WITH_HRPWM = ["F2802x", "F2803x", "F2805x", "F2806x"];

//=============================================================================
// eQEP Instance Availability
//=============================================================================

const DEVICES_WITH_EQEP1 = DEVICES_GEN3;
const DEVICES_WITH_EQEP2 = [
    "F280015x", "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD",
    "F2837xS", "F2838x", "F28P55x", "F28P65x"
];
const DEVICES_WITH_EQEP3 = ["F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"];
// QMAE bitfield only exists on these devices (NOT on F2807x, F2837xD, F2837xS)
const DEVICES_WITH_QMAE = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
    "F2838x", "F28P55x", "F28P65x"
];

//=============================================================================
// Clock and PLL Features
//=============================================================================

// AUXPLL Support — internal auxiliary PLL for MCAN/USB clock generation
// Note: F28P55x does NOT have AUXPLL. Its MCAN bit clock comes from the AUXCLKIN pin
//       (external clock input), which is board-defined and not derivable from registers.
const DEVICES_WITH_AUXPLL = ["F2807x", "F2837xD", "F2837xS", "F2838x", "F28P65x"];

// EPWMCLK Divider
// Note: DEVICES_WITH_EPWMCLKDIV and DEVICES_WITH_AUXPLL are intentionally identical —
// both features exist on the same device set. If a new device is added to one, add to both.
const DEVICES_WITH_EPWMCLKDIV = ["F2807x", "F2837xD", "F2837xS", "F2838x", "F28P65x"];

// HRPWM Support (MEP + SFO v8 calibration)
const DEVICES_WITH_HRPWM = DEVICES_GEN3;

//=============================================================================
// Communication Peripherals
//=============================================================================

// MCAN Support (CAN-FD) — all devices that have at least one MCAN instance
// MCAN clock sources differ by device:
//   AUXPLL source:  F2838x (1x MCAN), F28P65x (2x MCAN: MCANA/MCANB)
//   PLLCLK source:  F280015x, F28003x (via MCANCLKDIV register)
//   AUXCLKIN source: F28P55x — external clock on AUXCLKIN pin (NOT derivable from registers)
const DEVICES_WITH_MCAN = ["F280015x", "F28003x", "F2838x", "F28P55x", "F28P65x"];

// Devices whose MCAN bit clock is sourced from AUXCLKIN (external clock input pin).
// CDT cannot calculate this frequency from internal registers — it is board-determined.
const DEVICES_WITH_MCAN_AUXCLKIN = ["F28P55x"];

// Legacy DCAN Support (CAN 2.0)
// Note: F28P55x has NO legacy DCAN — it has MCAN (CAN-FD) only
// Note: F28P65x has 1x DCAN (CANA) + 2x MCAN (MCANA/MCANB) — it has CANA but NO CANB
const DEVICES_WITH_CANA = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P65x"
];
// Note: F28P65x has MCANA/MCANB but NOT a second DCAN (CANB). CANB = legacy eCAN only.
const DEVICES_WITH_CANB = ["F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x"];

// FSI (Fast Serial Interface)
const DEVICES_WITH_FSI = ["F28002x", "F28003x", "F28004x", "F2838x", "F28P55x", "F28P65x"];

// FSI Error Tag Match feature (enhanced error detection)
const DEVICES_WITH_FSI_ERROR_TAG_MATCH = ["F28002x", "F28003x", "F2838x", "F28P55x", "F28P65x"];

//=============================================================================
// DAC (Digital-to-Analog Converter)
//=============================================================================

// DAC Instance A
const DEVICES_WITH_DACA = [
    "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS",
    "F2838x", "F28P55x", "F28P65x"
];

// DAC Instance B
const DEVICES_WITH_DACB = [
    "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x"
];

// DAC Instance C
const DEVICES_WITH_DACC = ["F2807x", "F2837xD", "F2837xS", "F2838x", "F28P65x"];

// Any DAC support (at least one DAC instance)
const DEVICES_WITH_DAC = [
    "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS",
    "F2838x", "F28P55x", "F28P65x"
];

//=============================================================================
// Analog System Features
//=============================================================================

// Voltage Monitor (VMON) support
const DEVICES_WITH_VMON = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x", "F28P55x", "F28P65x"
];

// ADC-DAC Loopback support
const DEVICES_WITH_LOOPBACK = [
    "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS",
    "F2838x", "F28P55x", "F28P65x"
];

//=============================================================================
// Flash Features
//=============================================================================

// Devices without flash size in PARTIDL register
// These devices need alternative methods to determine flash size
const DEVICES_WITHOUT_FLASH_SIZE_REG = ["F280013x", "F280015x"];

//=============================================================================
// System Features
//=============================================================================

// CLA (Control Law Accelerator)
const DEVICES_WITH_CLA = [
    "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS",
    "F2838x", "F28P55x", "F28P65x"
];

// CLB (Configurable Logic Block)
// Note: CLB diagnostic panel is planned for a future CDT release.
// CLB provides FPGA-like programmable logic for custom signal processing
// Note: F280013x, F280015x do NOT have CLB
const DEVICES_WITH_CLB = [
    "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS",
    "F2838x", "F28P55x", "F28P65x"
];

// DMA (Direct Memory Access)
const DEVICES_WITH_DMA = [
    "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS",
    "F2838x", "F28P55x", "F28P65x"
];

// CMPSS (Comparator Subsystem) - All Gen3 devices have CMPSS
// Instance counts vary: F280013x/F28002x (2), F280015x/F28003x/F28P55x (4),
// F28004x (7), F2807x/F2837xD/S/F2838x (8), F28P65x (11)
const DEVICES_WITH_CMPSS = DEVICES_GEN3;

// SDFM (Sigma-Delta Filter Module)
const DEVICES_WITH_SDFM = [
    "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS",
    "F2838x", "F28P65x"
];

// EPWM SOC Overflow Flags (SOCAOVF/SOCBOVF/INTOVF in ETFLG register)
// Only available on larger devices with enhanced EPWM
const DEVICES_WITH_SOC_OVF = ["F2837xD", "F2837xS", "F2838x", "F28P65x"];

// DCC (Dual Clock Comparator)
// Note: F2807x, F2837xD, F2837xS have DCC1 (and F2837xD/S have DCC2 as well)
const DEVICES_WITH_DCC = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
];

//=============================================================================
// GPIO Port Availability
// Source: Device datasheets - GPIO pin counts vary by package and device
//
// Port register covers GPIO pins in 32-pin blocks:
//   Port A: GPIO0  – GPIO31
//   Port B: GPIO32 – GPIO63
//   Port C: GPIO64 – GPIO95
//   Port D: GPIO96 – GPIO127
//   Port E: GPIO128 – GPIO159
//   Port F: GPIO160 – GPIO191  (valid up to GPIO168 on current devices)
//
// NOTE: Not all pins in a port range are physically present on every device.
// Use getGpioPinCount() for the actual bonded pin count.
// Use getMaxGpioPin() for the highest valid GPIO number.
//=============================================================================

// Port A (GPIO0-31) — present on all Gen3 devices
// Approximate valid pins per device:
//   F280013x: GPIO0-15 (~16 pins, 38-pin package)
//   F280015x: GPIO0-28 (~22 pins, 64-pin package)
//   F28002x:  GPIO0-31 (32 pins, various packages)
//   F28003x:  GPIO0-31 (32 pins)
//   F28004x:  GPIO0-31 (32 pins)
//   F2807x+:  GPIO0-31 (32 pins, full port)
const DEVICES_WITH_GPIO_PORTA = DEVICES_GEN3;

// Port B (GPIO32-63) — all Gen3 devices have the register, but valid pins vary
// Approximate valid pins per device:
//   F280013x: GPIO32-42 (~10 pins — port only partially bonded)
//   F280015x: GPIO32-49 (~18 pins)
//   F28002x:  GPIO32-58 (~22 pins)
//   F28003x:  GPIO32-61 (~30 pins)
//   F28004x:  GPIO32-58 (~20 pins)
//   F2807x+:  GPIO32-63 (32 pins, full port)
const DEVICES_WITH_GPIO_PORTB = DEVICES_GEN3;

// Port C (GPIO64-95) — larger devices only
// Approximate valid pins per device:
//   F2807x:   GPIO64-87 (~24 pins, including isolated GPIO99/133)
//   F28P55x:  GPIO64-81 (~18 pins, 100-pin package)
//   F2837xD/S, F2838x, F28P65x: GPIO64-95 (32 pins, full port)
const DEVICES_WITH_GPIO_PORTC = ["F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"];

// Port D (GPIO96-127) — high-pin-count devices only (176-pin+ packages)
// All listed devices: GPIO96-127 (32 pins, full port)
const DEVICES_WITH_GPIO_PORTD = ["F2837xD", "F2837xS", "F2838x", "F28P65x"];

// Port E (GPIO128-159) — high-pin-count devices only
// All listed devices: GPIO128-159 (32 pins, full port)
const DEVICES_WITH_GPIO_PORTE = ["F2837xD", "F2837xS", "F2838x", "F28P65x"];

// Port F (GPIO160-191) — high-pin-count devices only
// Valid pins: GPIO160-168 only (9 pins) — GPIO169-191 are reserved on all current devices
// getMaxGpioPin() returns 168 for all Port-F devices to reflect this.
const DEVICES_WITH_GPIO_PORTF = ["F2837xD", "F2837xS", "F2838x", "F28P65x"];

// Port G (GPIO192-223) — reserved for future devices; no current C2000 device uses this range
const DEVICES_WITH_GPIO_PORTG = [];

// Port H (GPIO224-255) — reserved for future devices; no current C2000 device uses this range
const DEVICES_WITH_GPIO_PORTH = [];

/**
 * Get the maximum GPIO pin number for a device.
 * @param {string} device - Device name
 * @returns {number} Highest GPIO pin number available
 */
function getMaxGpioPin(device) {
    if (DEVICES_WITH_GPIO_PORTH.includes(device)) return 255;
    if (DEVICES_WITH_GPIO_PORTG.includes(device)) return 223;
    if (DEVICES_WITH_GPIO_PORTF.includes(device)) return 168;
    if (DEVICES_WITH_GPIO_PORTE.includes(device)) return 159;
    if (DEVICES_WITH_GPIO_PORTD.includes(device)) return 127;
    if (DEVICES_WITH_GPIO_PORTC.includes(device)) return 95;
    if (DEVICES_WITH_GPIO_PORTB.includes(device)) return 63;
    return 31; // Port A only
}

/**
 * Get device-specific GPIO pin count.
 * @param {string} device - Device name
 * @returns {number} Total number of GPIO pins available
 */
function getGpioPinCount(device) {
    // Device-specific actual bonded pin counts (from datasheets / LaunchPad schematics)
    const pinCounts = {
        // Gen2 devices (Piccolo family) — counts verified against SPRS523/SPRS584/SPRS324/SPRS281
        "F2802x": 26,     // Port A + Port B partial (GPIO0-34 valid range, ~26 physical pins; LAUNCHXL-F28027F)
        "F2803x": 41,     // Port A + Port B partial (GPIO0-63 valid range, ~41 physical pins; LAUNCHXL-F28035)
        "F2805x": 40,     // Port A + Port B partial (GPIO0-38 valid range, ~40 physical pins; controlCARD-F28055)
        "F2806x": 59,     // Port A + Port B partial (GPIO0-63 valid range, ~59 physical pins; LAUNCHXL-F28069M)
        // Gen3 devices
        "F280013x": 26,   // Port A + Port B partial (GPIO0-41 valid range, ~26 physical pins)
        "F280015x": 42,   // Port A + Port B partial (GPIO0-49 valid range)
        "F28002x": 24,    // Port A + Port B partial (GPIO0-59 valid range, ~24 physical pins)
        "F28003x": 62,    // Port A + Port B partial (GPIO0-61)
        "F28004x": 40,    // Port A + Port B partial (GPIO0-59 valid, ~40 physical pins)
        "F2807x": 64,     // Port A-C (GPIO0-94 + isolated 99,133)
        "F2837xD": 169,   // Port A-F (GPIO0-168)
        "F2837xS": 169,   // Port A-F (GPIO0-168)
        "F2838x": 169,    // Port A-F (GPIO0-168)
        "F28P55x": 72,    // Port A-C (GPIO0-81 valid range, ~72 physical pins)
        "F28P65x": 169    // Port A-F (GPIO0-168)
    };
    return pinCounts[device] || 32;
}

//=============================================================================
// PIE (Peripheral Interrupt Expansion) Mapping
// Source: driverlib/<device>/driverlib/inc/hw_ints.h
//        TRM Section "PIE Channel Mapping" (SPRU430 / device-specific TRMs)
//
// The C2000 PIE controller expands 12 CPU interrupt lines into up to 16
// peripheral interrupt channels each (192 total channels). Groups 1-12 map
// to CPU interrupts INT1-INT12. Each group has 8 primary channels (some
// devices extend to 16 for ADC events in Group 10).
//
// MAINTENANCE NOTE: Verify mappings against hw_ints.h for each new device.
// The PIE layout is largely stable across Gen3, but check:
//   - New peripherals (e.g., MCAN, ESM) may use previously-reserved channels
//   - ePWM channel counts (Groups 2-3) vary: small devices have fewer instances
//   - ADC Group 10 channels 9-16 exist only on devices with ADCC/D
//=============================================================================

// PIE Group Information — verified against TRM PIE channel mapping table
const PIE_GROUP_INFO = {
    1:  { name: "ADC/Timer",  desc: "ADCA-D INT1, XINT1-2, ADCD1, TIMER0, LPM Wake",
          register: "PieVectTable.ADCA1 ... PieVectTable.WAKE" },
    2:  { name: "EPWM TZ",   desc: "ePWM1-8 trip-zone interrupts (EPWM_TZ)",
          register: "PieVectTable.EPWM1_TZ ... PieVectTable.EPWM8_TZ" },
    3:  { name: "EPWM",      desc: "ePWM1-8 period/event interrupts",
          register: "PieVectTable.EPWM1 ... PieVectTable.EPWM8" },
    4:  { name: "ECAP",      desc: "eCAP1-7 capture event interrupts",
          register: "PieVectTable.ECAP1 ... PieVectTable.ECAP7" },
    5:  { name: "EQEP/CLB",  desc: "eQEP1-3, CLB1-4 (ch4 reserved), SDFM on some devices",
          register: "PieVectTable.EQEP1 ... PieVectTable.CLB4" },
    6:  { name: "SPI",       desc: "SPIA-C RX/TX FIFO interrupts",
          register: "PieVectTable.SPIA_RX ... PieVectTable.SPIC_TX" },
    7:  { name: "DMA",       desc: "DMA channels 1-6 completion interrupts",
          register: "PieVectTable.DMA_CH1 ... PieVectTable.DMA_CH6" },
    8:  { name: "I2C/LIN",   desc: "I2CA-B (with FIFO), LINA-B ch0-1, PMBUS on some devices",
          register: "PieVectTable.I2CA ... PieVectTable.LINB_1" },
    9:  { name: "SCI/CAN",   desc: "SCIA-B RX/TX, CANA-B INT0-1",
          register: "PieVectTable.SCIA_RX ... PieVectTable.CANB1" },
    10: { name: "ADC Evt",   desc: "ADCA-D EVT + INT2-4 (channels 1-8 for A/B; 9-16 for C/D on larger devices)",
          register: "PieVectTable.ADCA_EVT ... PieVectTable.ADCD4" },
    11: { name: "CLA",       desc: "CLA Task 1-8 completion interrupts",
          register: "PieVectTable.CLA1_1 ... PieVectTable.CLA1_8" },
    12: { name: "XINT/Err",  desc: "XINT3-5, FMC flash, FPU overflow/underflow (ch4/6 reserved)",
          register: "PieVectTable.XINT3 ... PieVectTable.FPU_UNF" }
};

// PIE Vector Table Mapping
// Format: PIE_VECTOR_TABLE[group][channel] = { name, short, devices }
// devices can be: DEVICES_GEN3 (all), specific array, or empty [] for reserved
const PIE_VECTOR_TABLE = {
    // Group 1: ADC End-of-Conversion, Timers, External Interrupts
    1: {
        1:  { name: "ADCA1", short: "ADCA1", devices: DEVICES_WITH_ADCA },
        2:  { name: "ADCB1", short: "ADCB1", devices: DEVICES_WITH_ADCB },
        3:  { name: "ADCC1", short: "ADCC1", devices: DEVICES_WITH_ADCC },
        4:  { name: "XINT1", short: "XINT1", devices: DEVICES_GEN3 },
        5:  { name: "XINT2", short: "XINT2", devices: DEVICES_GEN3 },
        6:  { name: "ADCD1", short: "ADCD1", devices: DEVICES_WITH_ADCD },
        7:  { name: "TIMER0", short: "TMR0", devices: DEVICES_GEN3 },
        8:  { name: "WAKE", short: "WAKE", devices: DEVICES_GEN3 }
    },
    // Group 2: ePWM Trip Zone
    2: {
        1:  { name: "EPWM1_TZ", short: "TZ1", devices: DEVICES_GEN3 },
        2:  { name: "EPWM2_TZ", short: "TZ2", devices: DEVICES_GEN3 },
        3:  { name: "EPWM3_TZ", short: "TZ3", devices: DEVICES_GEN3 },
        4:  { name: "EPWM4_TZ", short: "TZ4", devices: DEVICES_GEN3 },
        5:  { name: "EPWM5_TZ", short: "TZ5", devices: DEVICES_GEN3 },
        6:  { name: "EPWM6_TZ", short: "TZ6", devices: DEVICES_GEN3 },
        7:  { name: "EPWM7_TZ", short: "TZ7", devices: DEVICES_GEN3 },
        8:  { name: "EPWM8_TZ", short: "TZ8", devices: DEVICES_GEN3 }
    },
    // Group 3: ePWM Interrupts
    3: {
        1:  { name: "EPWM1", short: "PWM1", devices: DEVICES_GEN3 },
        2:  { name: "EPWM2", short: "PWM2", devices: DEVICES_GEN3 },
        3:  { name: "EPWM3", short: "PWM3", devices: DEVICES_GEN3 },
        4:  { name: "EPWM4", short: "PWM4", devices: DEVICES_GEN3 },
        5:  { name: "EPWM5", short: "PWM5", devices: DEVICES_GEN3 },
        6:  { name: "EPWM6", short: "PWM6", devices: DEVICES_GEN3 },
        7:  { name: "EPWM7", short: "PWM7", devices: DEVICES_GEN3 },
        8:  { name: "EPWM8", short: "PWM8", devices: DEVICES_GEN3 }
    },
    // Group 4: eCAP Interrupts
    4: {
        1:  { name: "ECAP1", short: "CAP1", devices: DEVICES_GEN3 },
        2:  { name: "ECAP2", short: "CAP2", devices: DEVICES_GEN3 },
        3:  { name: "ECAP3", short: "CAP3", devices: ["F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"] },
        4:  { name: "ECAP4", short: "CAP4", devices: ["F2807x", "F2837xD", "F2837xS", "F2838x", "F28P65x"] },
        5:  { name: "ECAP5", short: "CAP5", devices: ["F2807x", "F2837xD", "F2837xS", "F2838x", "F28P65x"] },
        6:  { name: "ECAP6", short: "CAP6", devices: ["F2807x", "F2837xD", "F2837xS", "F2838x", "F28P65x"] },
        7:  { name: "ECAP7", short: "CAP7", devices: ["F2838x", "F28P65x"] }
    },
    // Group 5: eQEP, CLB, SDFM
    5: {
        1:  { name: "EQEP1", short: "QEP1", devices: DEVICES_WITH_EQEP1 },
        2:  { name: "EQEP2", short: "QEP2", devices: DEVICES_WITH_EQEP2 },
        3:  { name: "EQEP3", short: "QEP3", devices: DEVICES_WITH_EQEP3 },
        5:  { name: "CLB1", short: "CLB1", devices: DEVICES_WITH_CLB },
        6:  { name: "CLB2", short: "CLB2", devices: DEVICES_WITH_CLB },
        7:  { name: "CLB3", short: "CLB3", devices: DEVICES_WITH_CLB },
        8:  { name: "CLB4", short: "CLB4", devices: DEVICES_WITH_CLB }
    },
    // Group 6: SPI Interrupts
    6: {
        1:  { name: "SPIA_RX", short: "SPIRXA", devices: DEVICES_GEN3 },
        2:  { name: "SPIA_TX", short: "SPITXA", devices: DEVICES_GEN3 },
        3:  { name: "SPIB_RX", short: "SPIRXB", devices: ["F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"] },
        4:  { name: "SPIB_TX", short: "SPITXB", devices: ["F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"] },
        5:  { name: "SPIC_RX", short: "SPIRXC", devices: ["F2807x", "F2837xD", "F2837xS", "F2838x", "F28P65x"] },
        6:  { name: "SPIC_TX", short: "SPITXC", devices: ["F2807x", "F2837xD", "F2837xS", "F2838x", "F28P65x"] }
    },
    // Group 7: DMA Interrupts
    7: {
        1:  { name: "DMA_CH1", short: "DMA1", devices: DEVICES_WITH_DMA },
        2:  { name: "DMA_CH2", short: "DMA2", devices: DEVICES_WITH_DMA },
        3:  { name: "DMA_CH3", short: "DMA3", devices: DEVICES_WITH_DMA },
        4:  { name: "DMA_CH4", short: "DMA4", devices: DEVICES_WITH_DMA },
        5:  { name: "DMA_CH5", short: "DMA5", devices: DEVICES_WITH_DMA },
        6:  { name: "DMA_CH6", short: "DMA6", devices: DEVICES_WITH_DMA }
    },
    // Group 8: I2C, LIN, PMBUS
    8: {
        1:  { name: "I2CA", short: "I2CA", devices: DEVICES_GEN3 },
        2:  { name: "I2CA_FIFO", short: "I2CAF", devices: DEVICES_GEN3 },
        3:  { name: "I2CB", short: "I2CB", devices: ["F280013x", "F280015x", "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"] },
        4:  { name: "I2CB_FIFO", short: "I2CBF", devices: ["F280013x", "F280015x", "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"] },
        5:  { name: "LINA_0", short: "LINA0", devices: ["F280013x", "F280015x", "F28002x", "F28003x", "F28004x", "F28P55x", "F28P65x"] },
        6:  { name: "LINA_1", short: "LINA1", devices: ["F280013x", "F280015x", "F28002x", "F28003x", "F28004x", "F28P55x", "F28P65x"] },
        7:  { name: "LINB_0", short: "LINB0", devices: ["F28002x", "F28003x", "F28P65x"] },
        8:  { name: "LINB_1", short: "LINB1", devices: ["F28002x", "F28003x", "F28P65x"] }
    },
    // Group 9: SCI, CAN
    9: {
        1:  { name: "SCIA_RX", short: "SCIRXA", devices: DEVICES_GEN3 },
        2:  { name: "SCIA_TX", short: "SCITXA", devices: DEVICES_GEN3 },
        3:  { name: "SCIB_RX", short: "SCIRXB", devices: ["F280013x", "F280015x", "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"] },
        4:  { name: "SCIB_TX", short: "SCITXB", devices: ["F280013x", "F280015x", "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"] },
        5:  { name: "CANA0", short: "CANA0", devices: DEVICES_WITH_CANA },
        6:  { name: "CANA1", short: "CANA1", devices: DEVICES_WITH_CANA },
        7:  { name: "CANB0", short: "CANB0", devices: DEVICES_WITH_CANB },
        8:  { name: "CANB1", short: "CANB1", devices: DEVICES_WITH_CANB }
    },
    // Group 10: ADC Events
    10: {
        1:  { name: "ADCA_EVT", short: "ADCAEV", devices: DEVICES_WITH_ADCA },
        2:  { name: "ADCA2", short: "ADCA2", devices: DEVICES_WITH_ADCA },
        3:  { name: "ADCA3", short: "ADCA3", devices: DEVICES_WITH_ADCA },
        4:  { name: "ADCA4", short: "ADCA4", devices: DEVICES_WITH_ADCA },
        5:  { name: "ADCB_EVT", short: "ADCBEV", devices: DEVICES_WITH_ADCB },
        6:  { name: "ADCB2",    short: "ADCB2",  devices: DEVICES_WITH_ADCB },
        7:  { name: "ADCB3",    short: "ADCB3",  devices: DEVICES_WITH_ADCB },
        8:  { name: "ADCB4",    short: "ADCB4",  devices: DEVICES_WITH_ADCB },
        9:  { name: "ADCC_EVT", short: "ADCCEV", devices: DEVICES_WITH_ADCC },
        10: { name: "ADCC2",    short: "ADCC2",  devices: DEVICES_WITH_ADCC },
        11: { name: "ADCC3",    short: "ADCC3",  devices: DEVICES_WITH_ADCC },
        12: { name: "ADCC4",    short: "ADCC4",  devices: DEVICES_WITH_ADCC },
        13: { name: "ADCD_EVT", short: "ADCDEV", devices: DEVICES_WITH_ADCD },
        14: { name: "ADCD2",    short: "ADCD2",  devices: DEVICES_WITH_ADCD },
        15: { name: "ADCD3",    short: "ADCD3",  devices: DEVICES_WITH_ADCD },
        16: { name: "ADCD4",    short: "ADCD4",  devices: DEVICES_WITH_ADCD }
    },
    // Group 11: CLA
    11: {
        1:  { name: "CLA1_1", short: "CLA1", devices: DEVICES_WITH_CLA },
        2:  { name: "CLA1_2", short: "CLA2", devices: DEVICES_WITH_CLA },
        3:  { name: "CLA1_3", short: "CLA3", devices: DEVICES_WITH_CLA },
        4:  { name: "CLA1_4", short: "CLA4", devices: DEVICES_WITH_CLA },
        5:  { name: "CLA1_5", short: "CLA5", devices: DEVICES_WITH_CLA },
        6:  { name: "CLA1_6", short: "CLA6", devices: DEVICES_WITH_CLA },
        7:  { name: "CLA1_7", short: "CLA7", devices: DEVICES_WITH_CLA },
        8:  { name: "CLA1_8", short: "CLA8", devices: DEVICES_WITH_CLA }
    },
    // Group 12: External Interrupts, FPU, Memory Errors
    12: {
        1:  { name: "XINT3", short: "XINT3", devices: DEVICES_GEN3 },
        2:  { name: "XINT4", short: "XINT4", devices: DEVICES_GEN3 },
        3:  { name: "XINT5", short: "XINT5", devices: DEVICES_GEN3 },
        5:  { name: "FMC", short: "FMC", devices: DEVICES_GEN3 },
        7:  { name: "FPU_OVF", short: "FPUOVF", devices: DEVICES_GEN3 },
        8:  { name: "FPU_UNF", short: "FPUUNF", devices: DEVICES_GEN3 }
    }
};

/**
 * Get PIE interrupt name for a specific device, group, and channel.
 * @param {string} device - Device name (e.g., "F28003x")
 * @param {number} group - PIE group number (1-12)
 * @param {number} channel - PIE channel number (1-16)
 * @returns {object|null} Interrupt info {name, short} or null if not available
 */
function getPieInterruptName(device, group, channel) {
    const groupMap = PIE_VECTOR_TABLE[group];
    if (!groupMap || !groupMap[channel]) return null;

    const info = groupMap[channel];
    // Check if this interrupt is available on this device
    if (info.devices.includes(device)) {
        return { name: info.name, short: info.short };
    }
    return null;
}

//=============================================================================
// Errata Applicability Groups
// These define which devices are affected by specific errata advisories.
//
// !! MAINTENANCE WARNING — most volatile section of this file !!
//
// Errata applicability changes with every silicon revision and device release.
// Before each CDT release, verify ALL arrays below against:
//   - TI Errata documents: https://www.ti.com/product/<device>#design-tools (Errata tab)
//
// Each entry below includes the TI errata ID where known. When TI publishes
// a resolution (silicon fix, silicon rev, or workaround only), update the
// comment accordingly and remove fixed revisions from the device list.
//
// Last verified: 2026-04 against available errata documents
//=============================================================================

// ADC Fractional Divider Errata
// Advisory: Degraded ADC performance when ADCCLK uses a fractional prescale value.
// Workaround: Use only integer prescale values (ADC_CLK_PRESCALE_1, _2, ..., _8).
// TI ID: ADC#001 (advisory number varies by device datasheet errata section)
// Verified: Affects integer-prescale devices only; half-step devices (F2807x+) not affected.
const DEVICES_WITH_ADC_FRACTIONAL_DIVIDER_ERRATA = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x"
];

// CMPSS Latch Clear Errata
// Advisory: COMPxLATCH bit may not clear properly when read-back is used.
// Workaround: Write COMPSTSCLR before reading COMPSTS.
// Note: F2838x and F28P65x are NOT affected — confirmed, this errata does not apply
const DEVICES_WITH_CMPSS_LATCH_ERRATA = [
    "F28004x", "F2807x", "F2837xD", "F2837xS", "F28P55x"
];

// CMPSS Ramp Generator Errata
// Advisory: Ramp generator may fail to start if RAMPSTS is not cleared first.
// Workaround: Clear RAMPSTS before enabling ramp generation.
// Note: F2838x and F28P65x are NOT affected — confirmed, this errata does not apply
const DEVICES_WITH_CMPSS_RAMP_ERRATA = ["F2807x", "F2837xD", "F2837xS"];

// ePWM Dead-Band Errata
// Advisory: Dead-band delay cannot be set to 0 when shadow load mode is enabled.
// Workaround: Set dead-band to minimum non-zero value, or disable shadow load.
// Note: F2838x and F28P65x are NOT affected — confirmed, this errata does not apply
const DEVICES_WITH_EPWM_DEADBAND_ERRATA = ["F2807x", "F2837xD", "F2837xS"];

// MCD (Missing Clock Detect) Errata
// Advisory: MCD should be disabled before enabling the PLL; may trigger falsely
//           during PLL lock sequence.
// Workaround: Disable MCD via CLKCTL.MCLKOFF before SYSPLLCTL1.PLLEN = 1.
// Note: F2838x IS affected (confirmed); only MCD errata applies to F2838x, not the others above
const DEVICES_WITH_MCD_ERRATA = ["F28P55x", "F28P65x", "F2838x"];

// Flash ECC Errata
// Advisory: Single-bit ECC correctable error interrupt (INT) not generated;
//           only the error flag is set.
// Workaround: Poll FRDCNTL.RWAIT and flash ECC status registers instead of
//             relying on the interrupt.
// NOTE: Check silicon rev — may be fixed in later F28P55x/F28P65x revisions.
const DEVICES_WITH_FLASH_ECC_ERRATA = ["F28P55x", "F28P65x"];

// DCC Single-Shot Mode Errata
// Advisory: DCC single-shot mode may terminate prematurely on the first run.
// Workaround: Run DCC twice; discard the first result.
const DEVICES_WITH_DCC_SINGLESHOT_ERRATA = ["F28002x", "F28004x"];

// SDFM Manchester Mode Errata
// Advisory: Manchester Mode (SDFM_MODE_2) does not produce correct decoded output.
// Workaround: Use NRZ (Mode 0) or NRZI (Mode 1) encoding instead.
// Note: F2838x and F28P65x are NOT affected — confirmed, this errata does not apply
const DEVICES_WITH_SDFM_MANCHESTER_ERRATA = ["F28004x", "F2807x", "F2837xD", "F2837xS"];

// I2C Open-Drain Buffer Errata
// Advisory: I2C SDA/SCL open-drain output buffer may hold the line low under
//           certain bus fault conditions.
// Workaround: Reset the I2C module if bus-stuck condition is detected.
// Note: F2838x and F28P65x are NOT affected — confirmed, this errata does not apply
const DEVICES_WITH_I2C_OPENDRAIN_ERRATA = ["F28004x", "F2807x", "F2837xD", "F2837xS"];

// PLL Lock Errata
// Advisory: PLL may not achieve lock on the first attempt after power-on.
// Workaround: Check SYSPLLSTS.LOCKS; retry PLL enable sequence if not locked
//             within the expected lock time.
// Note: F2838x and F28P65x are NOT affected — confirmed, this errata does not apply
const DEVICES_WITH_PLL_LOCK_ERRATA = ["F28004x", "F2807x", "F2837xD", "F2837xS"];

// FSI Overrun Errata
// Advisory: FSI RX overrun flag may not assert correctly in back-to-back
//           frame reception scenarios.
// Workaround: Insert a software delay between frame receptions.
// Note: errata_clinic.js check not yet implemented — planned for future CDT release.
const DEVICES_WITH_FSI_OVERRUN_ERRATA = ["F28004x", "F2838x"];

// HRCAP (High-Resolution Capture) availability
// Ref: device_support/<device>/common/include/hw_memmap.h - HRCAP_BASE
// F28002x confirmed via export_mods_common.js module list (includes "hrcap")
const DEVICES_WITH_HRCAP = ["F28002x", "F28003x", "F28004x", "F2838x", "F28P55x", "F28P65x"];

// Memory Error CERRTHRES register (MemoryErrorRegs.CERRTHRES)
// Only present on devices with enhanced memory error detection
const DEVICES_WITH_CERRTHRES_REG = ["F280013x", "F280015x", "F28003x"];

// PLL Reference Clock Lost status register (ClkCfgRegs.SYSPLLSTS.REF_LOSTS)
// Only F280013x and F280015x have this flag (REFDIV/ODIV architecture with ref-lost detection)
const DEVICES_WITH_PLL_REFLOST_REG = ["F280013x", "F280015x"];

// Prefetch Boundary Errata applicability
// Devices where prefetch-beyond-valid-memory errata must be checked
const DEVICES_WITH_PREFETCH_BOUNDARY_ERRATA = ["F280013x", "F280015x", "F28003x"];

// eQEP Position Counter Errata
// Advisory: Position counter may be incorrectly reset on direction change
// Note: F28P65x is NOT affected by this errata
const DEVICES_WITH_EQEP_POSITION_ERRATA = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x"
];

//=============================================================================
// Helper Functions
//=============================================================================

/**
 * Get device-specific maximum SYSCLK frequency.
 * @param {string} device - Device name (e.g., "F280015x", "F28003x", "F2802x")
 * @returns {number} Maximum SYSCLK in Hz, or NaN if device unknown
 */
function getMaxSysclk(device) {
    // Gen2 devices
    if (DEVICES_WITH_40MHZ_MAX_SYSCLK.includes(device)) return 40000000;
    if (DEVICES_WITH_60MHZ_MAX_SYSCLK_GEN2.includes(device)) return 60000000;
    if (DEVICES_WITH_90MHZ_MAX_SYSCLK.includes(device)) return 90000000;
    // Gen3 devices
    if (DEVICES_WITH_100MHZ_MAX_SYSCLK.includes(device)) return 100000000;
    if (DEVICES_WITH_120MHZ_MAX_SYSCLK.includes(device)) return 120000000;
    if (DEVICES_WITH_150MHZ_MAX_SYSCLK.includes(device)) return 150000000;
    if (DEVICES_WITH_200MHZ_MAX_SYSCLK.includes(device)) return 200000000;
    console.log("Error: Unknown device for max SYSCLK: " + device);
    return NaN;
}

/**
 * Validate if device is a supported Gen3 device.
 * @param {string} device - Device name to validate
 * @returns {boolean} True if device is supported
 */
function isValidDevice(device) {
    return DEVICES_WITH_CDT_SUPPORT.includes(device);
}

/**
 * Check if device has a specific feature/peripheral.
 * @param {string} device - Device name
 * @param {string} feature - Feature name (e.g., 'ADCB', 'MCAN', 'CLA', 'AUXPLL')
 * @returns {boolean} True if device has the feature
 */
function hasFeature(device, feature) {
    const featureMap = {
        // ADC instances
        'ADCA': DEVICES_WITH_ADCA,
        'ADCB': DEVICES_WITH_ADCB,
        'ADCC': DEVICES_WITH_ADCC,
        'ADCD': DEVICES_WITH_ADCD,
        'ADCE': DEVICES_WITH_ADCE,
        // eQEP instances
        'EQEP1': DEVICES_WITH_EQEP1,
        'EQEP2': DEVICES_WITH_EQEP2,
        'EQEP3': DEVICES_WITH_EQEP3,
        // Clock features
        'AUXPLL': DEVICES_WITH_AUXPLL,
        'EPWMCLKDIV': DEVICES_WITH_EPWMCLKDIV,
        'HRPWM': DEVICES_WITH_HRPWM,
        // Communication
        'MCAN': DEVICES_WITH_MCAN,
        'MCAN_AUXCLKIN': DEVICES_WITH_MCAN_AUXCLKIN,
        'CANA': DEVICES_WITH_CANA,
        'CANB': DEVICES_WITH_CANB,
        'FSI': DEVICES_WITH_FSI,
        // DAC instances
        'DAC': DEVICES_WITH_DAC,
        'DACA': DEVICES_WITH_DACA,
        'DACB': DEVICES_WITH_DACB,
        'DACC': DEVICES_WITH_DACC,
        // System features
        'CLA': DEVICES_WITH_CLA,
        'CLB': DEVICES_WITH_CLB,
        'DMA': DEVICES_WITH_DMA,
        'CMPSS': DEVICES_WITH_CMPSS,
        'SDFM': DEVICES_WITH_SDFM,
        'DCC': DEVICES_WITH_DCC,
        'SOC_OVF': DEVICES_WITH_SOC_OVF,
        'VMON': DEVICES_WITH_VMON,
        'LOOPBACK': DEVICES_WITH_LOOPBACK,
        'QMAE': DEVICES_WITH_QMAE,
        // GPIO ports
        'GPIO_PORTA': DEVICES_WITH_GPIO_PORTA,
        'GPIO_PORTB': DEVICES_WITH_GPIO_PORTB,
        'GPIO_PORTC': DEVICES_WITH_GPIO_PORTC,
        'GPIO_PORTD': DEVICES_WITH_GPIO_PORTD,
        'GPIO_PORTE': DEVICES_WITH_GPIO_PORTE,
        'GPIO_PORTF': DEVICES_WITH_GPIO_PORTF,
        'GPIO_PORTG': DEVICES_WITH_GPIO_PORTG,
        'GPIO_PORTH': DEVICES_WITH_GPIO_PORTH
    };
    const deviceList = featureMap[feature.toUpperCase()];
    return deviceList ? deviceList.includes(device) : false;
}

/**
 * Check if device uses REFDIV/ODIV PLL architecture.
 * @param {string} device - Device name
 * @returns {boolean} True if device uses REFDIV/ODIV architecture
 */
function usesRefdivOdiv(device) {
    return DEVICES_WITH_REFDIV_ODIV.includes(device);
}

/**
 * Check if device uses FMULT PLL architecture.
 * @param {string} device - Device name
 * @returns {boolean} True if device uses FMULT architecture
 */
function usesFmult(device) {
    return DEVICES_WITH_FMULT.includes(device);
}

/**
 * Check if device uses integer-only ADC prescale dividers.
 * @param {string} device - Device name
 * @returns {boolean} True if device uses integer prescale only
 */
function usesIntegerAdcPrescale(device) {
    return DEVICES_WITH_ADC_INTEGER_PRESCALE.includes(device);
}

/**
 * Check if device uses Gen2 PLLCR/PLLSTS PLL architecture.
 * @param {string} device - Device name
 * @returns {boolean} True if device uses Gen2 PLL architecture
 */
function usesPllcrDiv(device) {
    return DEVICES_WITH_PLLCR_DIV.includes(device);
}

/**
 * Check if device is Gen2.
 * @param {string} device - Device name
 * @returns {boolean} True if device is Gen2
 */
function isGen2Device(device) {
    return DEVICES_GEN2.includes(device);
}

/**
 * Check if device is Gen3.
 * @param {string} device - Device name
 * @returns {boolean} True if device is Gen3
 */
function isGen3Device(device) {
    return DEVICES_GEN3.includes(device);
}

//=============================================================================
// Exports
//=============================================================================

exports = {
    // Device Families
    DEVICES_GEN2,
    DEVICES_GEN3,
    DEVICES_ALL,
    DEVICES_WITH_CDT_SUPPORT,

    // PLL Architecture
    DEVICES_WITH_PLLCR_DIV,  // Gen2 PLL architecture
    DEVICES_WITH_REFDIV_ODIV,
    DEVICES_WITH_FMULT,
    DEVICES_WITH_FMULT_ODIV,

    // SYSCLK Frequency Groups - Gen2
    DEVICES_WITH_40MHZ_MAX_SYSCLK,
    DEVICES_WITH_60MHZ_MAX_SYSCLK_GEN2,
    DEVICES_WITH_90MHZ_MAX_SYSCLK,
    DEVICES_40MHZ,
    DEVICES_60MHZ_GEN2,
    DEVICES_90MHZ,
    // SYSCLK Frequency Groups - Gen3
    DEVICES_WITH_100MHZ_MAX_SYSCLK,
    DEVICES_WITH_120MHZ_MAX_SYSCLK,
    DEVICES_WITH_150MHZ_MAX_SYSCLK,
    DEVICES_WITH_200MHZ_MAX_SYSCLK,
    // Short aliases for backward compatibility
    DEVICES_100MHZ,
    DEVICES_120MHZ,
    DEVICES_150MHZ,
    DEVICES_200MHZ,

    // ADC - Gen2
    DEVICES_GEN2_WITH_ADC,
    DEVICES_WITH_ADC_GEN2_PRESCALE,
    DEVICES_ADC_GEN2_PRESCALE,
    // ADC - Gen3
    DEVICES_WITH_ADCA,
    DEVICES_WITH_ADCB,
    DEVICES_WITH_ADCC,
    DEVICES_WITH_ADCD,
    DEVICES_WITH_ADCE,
    DEVICES_WITH_ADC_INTEGER_PRESCALE,
    DEVICES_WITH_ADC_HALFSTEP_PRESCALE,
    DEVICES_WITH_ADC_CONFIGURABLE_RESOLUTION,
    // Short aliases for backward compatibility
    DEVICES_ADC_INTEGER_PRESCALE,
    DEVICES_ADC_HALFSTEP_PRESCALE,

    // Gen2 Peripherals
    DEVICES_GEN2_WITH_CLA,
    DEVICES_GEN2_WITH_ECAN,
    DEVICES_GEN2_WITH_DMA,
    DEVICES_GEN2_WITH_USB,
    DEVICES_GEN2_WITH_LIN,
    DEVICES_GEN2_WITH_HRPWM,

    // eQEP
    DEVICES_WITH_EQEP1,
    DEVICES_WITH_EQEP2,
    DEVICES_WITH_EQEP3,
    DEVICES_WITH_QMAE,

    // Clock Features
    DEVICES_WITH_AUXPLL,
    DEVICES_WITH_EPWMCLKDIV,
    DEVICES_WITH_HRPWM,

    // Communication
    DEVICES_WITH_MCAN,
    DEVICES_WITH_MCAN_AUXCLKIN,
    DEVICES_WITH_CANA,
    DEVICES_WITH_CANB,
    DEVICES_WITH_FSI,
    DEVICES_WITH_FSI_ERROR_TAG_MATCH,

    // DAC
    DEVICES_WITH_DAC,
    DEVICES_WITH_DACA,
    DEVICES_WITH_DACB,
    DEVICES_WITH_DACC,

    // Analog System Features
    DEVICES_WITH_VMON,
    DEVICES_WITH_LOOPBACK,

    // Flash Features
    DEVICES_WITHOUT_FLASH_SIZE_REG,

    // System Features
    DEVICES_WITH_CLA,
    DEVICES_WITH_CLB,  // CLB panel planned for future CDT release
    DEVICES_WITH_DMA,
    DEVICES_WITH_CMPSS,
    DEVICES_WITH_SDFM,
    DEVICES_WITH_DCC,
    DEVICES_WITH_SOC_OVF,

    // GPIO Ports
    DEVICES_WITH_GPIO_PORTA,
    DEVICES_WITH_GPIO_PORTB,
    DEVICES_WITH_GPIO_PORTC,
    DEVICES_WITH_GPIO_PORTD,
    DEVICES_WITH_GPIO_PORTE,
    DEVICES_WITH_GPIO_PORTF,
    DEVICES_WITH_GPIO_PORTG,
    DEVICES_WITH_GPIO_PORTH,

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
    DEVICES_WITH_FSI_OVERRUN_ERRATA,
    DEVICES_WITH_EQEP_POSITION_ERRATA,
    // Peripheral feature availability
    DEVICES_WITH_HRCAP,
    // Errata-check register availability
    DEVICES_WITH_CERRTHRES_REG,
    DEVICES_WITH_PLL_REFLOST_REG,
    DEVICES_WITH_PREFETCH_BOUNDARY_ERRATA,

    // PIE Interrupt Mapping
    PIE_GROUP_INFO,
    PIE_VECTOR_TABLE,

    // Helper Functions
    normalizeDeviceName,
    getMaxSysclk,
    isValidDevice,
    hasFeature,
    usesRefdivOdiv,
    usesFmult,
    usesIntegerAdcPrescale,
    usesPllcrDiv,
    isGen2Device,
    isGen3Device,
    getMaxGpioPin,
    getGpioPinCount,
    getPieInterruptName
};
