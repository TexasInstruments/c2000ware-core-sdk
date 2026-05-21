//=============================================================================
// export_mods_common.js - Common Export Module Utilities for CDT
//=============================================================================
// Purpose: Shared functions and constants for export module processing
// Devices: All Gen3 devices
//=============================================================================

let transferCommon;
if (system.getProducts()[0].name.includes("C2000")) {
    transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
} else {
    transferCommon = system.getScript("/transfer/transferCommon.js");
}

//=============================================================================
// Device Support Constants - Import from centralized device_constants.js
// All export modules should import these from here to avoid duplication
//=============================================================================
const deviceConstants = system.getScript(transferCommon.getTransferPath() + "clinic/f28x/device_constants.js");

// Core device family
const DEVICES_GEN2 = deviceConstants.DEVICES_GEN2;
const DEVICES_GEN3 = deviceConstants.DEVICES_GEN3;
const DEVICES_ALL = deviceConstants.DEVICES_ALL;
const DEVICES_WITH_CDT_SUPPORT = deviceConstants.DEVICES_WITH_CDT_SUPPORT;

// Gen2 PLL Architecture
const DEVICES_WITH_PLLCR_DIV = deviceConstants.DEVICES_WITH_PLLCR_DIV;

// PLL Architecture
const DEVICES_WITH_REFDIV_ODIV = deviceConstants.DEVICES_WITH_REFDIV_ODIV;
const DEVICES_WITH_FMULT = deviceConstants.DEVICES_WITH_FMULT;

// SYSCLK Frequency Groups
const DEVICES_WITH_100MHZ_MAX_SYSCLK = deviceConstants.DEVICES_WITH_100MHZ_MAX_SYSCLK;
const DEVICES_WITH_120MHZ_MAX_SYSCLK = deviceConstants.DEVICES_WITH_120MHZ_MAX_SYSCLK;
const DEVICES_WITH_150MHZ_MAX_SYSCLK = deviceConstants.DEVICES_WITH_150MHZ_MAX_SYSCLK;
const DEVICES_WITH_200MHZ_MAX_SYSCLK = deviceConstants.DEVICES_WITH_200MHZ_MAX_SYSCLK;

// ADC Instances
const DEVICES_WITH_ADCA = deviceConstants.DEVICES_WITH_ADCA;
const DEVICES_WITH_ADCB = deviceConstants.DEVICES_WITH_ADCB;
const DEVICES_WITH_ADCC = deviceConstants.DEVICES_WITH_ADCC;
const DEVICES_WITH_ADCD = deviceConstants.DEVICES_WITH_ADCD;
const DEVICES_WITH_ADCE = deviceConstants.DEVICES_WITH_ADCE;
const DEVICES_WITH_ADC_INTEGER_PRESCALE = deviceConstants.DEVICES_WITH_ADC_INTEGER_PRESCALE;
const DEVICES_WITH_ADC_HALFSTEP_PRESCALE = deviceConstants.DEVICES_WITH_ADC_HALFSTEP_PRESCALE;
const DEVICES_WITH_ADC_CONFIGURABLE_RESOLUTION = deviceConstants.DEVICES_WITH_ADC_CONFIGURABLE_RESOLUTION;

// eQEP Instances
const DEVICES_WITH_EQEP1 = deviceConstants.DEVICES_WITH_EQEP1;
const DEVICES_WITH_EQEP2 = deviceConstants.DEVICES_WITH_EQEP2;
const DEVICES_WITH_EQEP3 = deviceConstants.DEVICES_WITH_EQEP3;
const DEVICES_WITH_QMAE = deviceConstants.DEVICES_WITH_QMAE;

// Clock Features
const DEVICES_WITH_AUXPLL = deviceConstants.DEVICES_WITH_AUXPLL;
const DEVICES_WITH_EPWMCLKDIV = deviceConstants.DEVICES_WITH_EPWMCLKDIV;
const DEVICES_WITH_HRPWM = deviceConstants.DEVICES_WITH_HRPWM;
const DEVICES_WITH_HRCAP = deviceConstants.DEVICES_WITH_HRCAP;

// Communication
const DEVICES_WITH_MCAN = deviceConstants.DEVICES_WITH_MCAN;
const DEVICES_WITH_MCAN_AUXCLKIN = deviceConstants.DEVICES_WITH_MCAN_AUXCLKIN;
const DEVICES_WITH_CANA = deviceConstants.DEVICES_WITH_CANA;
const DEVICES_WITH_CANB = deviceConstants.DEVICES_WITH_CANB;
const DEVICES_WITH_FSI = deviceConstants.DEVICES_WITH_FSI;
const DEVICES_WITH_FSI_ERROR_TAG_MATCH = deviceConstants.DEVICES_WITH_FSI_ERROR_TAG_MATCH;

// DAC
const DEVICES_WITH_DAC = deviceConstants.DEVICES_WITH_DAC;
const DEVICES_WITH_DACA = deviceConstants.DEVICES_WITH_DACA;
const DEVICES_WITH_DACB = deviceConstants.DEVICES_WITH_DACB;
const DEVICES_WITH_DACC = deviceConstants.DEVICES_WITH_DACC;

// Analog System Features
const DEVICES_WITH_VMON = deviceConstants.DEVICES_WITH_VMON;
const DEVICES_WITH_LOOPBACK = deviceConstants.DEVICES_WITH_LOOPBACK;

// Flash Features
const DEVICES_WITHOUT_FLASH_SIZE_REG = deviceConstants.DEVICES_WITHOUT_FLASH_SIZE_REG;

// System Features
const DEVICES_WITH_CLA = deviceConstants.DEVICES_WITH_CLA;
const DEVICES_WITH_CLB = deviceConstants.DEVICES_WITH_CLB;  // TODO: Add CLB diagnostic support in future CDT release
const DEVICES_WITH_DMA = deviceConstants.DEVICES_WITH_DMA;
const DEVICES_WITH_CMPSS = deviceConstants.DEVICES_WITH_CMPSS;
const DEVICES_WITH_SDFM = deviceConstants.DEVICES_WITH_SDFM;
const DEVICES_WITH_DCC = deviceConstants.DEVICES_WITH_DCC;
const DEVICES_WITH_SOC_OVF = deviceConstants.DEVICES_WITH_SOC_OVF;

// GPIO Ports
const DEVICES_WITH_GPIO_PORTA = deviceConstants.DEVICES_WITH_GPIO_PORTA;
const DEVICES_WITH_GPIO_PORTB = deviceConstants.DEVICES_WITH_GPIO_PORTB;
const DEVICES_WITH_GPIO_PORTC = deviceConstants.DEVICES_WITH_GPIO_PORTC;
const DEVICES_WITH_GPIO_PORTD = deviceConstants.DEVICES_WITH_GPIO_PORTD;
const DEVICES_WITH_GPIO_PORTE = deviceConstants.DEVICES_WITH_GPIO_PORTE;
const DEVICES_WITH_GPIO_PORTF = deviceConstants.DEVICES_WITH_GPIO_PORTF;
const DEVICES_WITH_GPIO_PORTG = deviceConstants.DEVICES_WITH_GPIO_PORTG;
const DEVICES_WITH_GPIO_PORTH = deviceConstants.DEVICES_WITH_GPIO_PORTH;

// Errata Applicability
const DEVICES_WITH_ADC_FRACTIONAL_DIVIDER_ERRATA = deviceConstants.DEVICES_WITH_ADC_FRACTIONAL_DIVIDER_ERRATA;
const DEVICES_WITH_CMPSS_LATCH_ERRATA = deviceConstants.DEVICES_WITH_CMPSS_LATCH_ERRATA;
const DEVICES_WITH_CMPSS_RAMP_ERRATA = deviceConstants.DEVICES_WITH_CMPSS_RAMP_ERRATA;
const DEVICES_WITH_EPWM_DEADBAND_ERRATA = deviceConstants.DEVICES_WITH_EPWM_DEADBAND_ERRATA;
const DEVICES_WITH_MCD_ERRATA = deviceConstants.DEVICES_WITH_MCD_ERRATA;

// Helper functions
const getMaxSysclk = deviceConstants.getMaxSysclk;
const isValidDevice = deviceConstants.isValidDevice;
const hasFeature = deviceConstants.hasFeature;
const getMaxGpioPin = deviceConstants.getMaxGpioPin;
const getGpioPinCount = deviceConstants.getGpioPinCount;

/**
 * Helper function to get current device name at evaluation time.
 * @returns {string} Device name (e.g., "F280015x")
 */
function getDeviceName() {
    return system.deviceData.device;
}

//=============================================================================
// Export Module Functions
//=============================================================================

/**
 * Get the communication link name used by the exporter module.
 * @returns {string} The exporter's communication link $name, or empty string if not configured
 */
function getExporterComsLinkName() {
    const exporterMod = system.modules[transferCommon.getTransferPath() + "exporter.js"];
    let exporterComsLinkName = "";
    if (exporterMod && exporterMod.$instances.length > 0) {
        exporterComsLinkName = exporterMod.$instances[0].comsLinkModule.$name;
    }
    return exporterComsLinkName;
}

/**
 * Get module instances excluding the one used by the exporter.
 * @param {Object} mod - SysConfig module object
 * @returns {Array} Array of module instances not used by exporter
 */
function getNonExporterInstances(mod) {
    const exporterComsLinkName = getExporterComsLinkName();
    if (mod && mod.$instances.length > 0) {
        return mod.$instances.filter((inst) => inst.$name !== exporterComsLinkName);
    }
    return [];
}

/**
 * Generate export key-value pairs for a module's instances.
 * @param {Object} mod - SysConfig module object
 * @param {Array} exportsInfo - Array of export information objects
 * @returns {Array} Array of {name, updateFunc} objects for each applicable export
 */
function getExportKeyValuesForMod(mod, exportsInfo) {
    const exportKeyValues = [];
    for (const expInfo of exportsInfo) {
        for (const inst of getNonExporterInstances(mod)) {
            if (isExportModInfoApplicableForInst(inst, expInfo)) {
                exportKeyValues.push({
                    name: inst.$name + "_" + expInfo.name,
                    updateFunc: expInfo.updateFunc ? expInfo.updateFunc(inst.$name + "_BASE") : undefined,
                });
            }
        }
    }
    return exportKeyValues;
}

/**
 * Get applicable export info objects for a specific instance.
 * @param {Object} inst - SysConfig module instance
 * @param {Array} exportsInfo - Array of export information objects
 * @returns {Array} Filtered array of applicable export info objects
 */
function getInstanceExportModsInfo(inst, exportsInfo) {
    return exportsInfo.filter((expInfo) => {
        return isExportModInfoApplicableForInst(inst, expInfo);
    });
}

/**
 * Get applicable export info objects of a specific type for an instance.
 * @param {Object} inst - SysConfig module instance
 * @param {Array} exportsInfo - Array of export information objects
 * @param {string} type - Export type to filter by (e.g., 'led', 'text', 'bar')
 * @returns {Array} Filtered array of applicable export info objects matching type
 */
function getInstanceExportModsInfoWithType(inst, exportsInfo, type) {
    return exportsInfo.filter((expInfo) => {
        return (isExportModInfoApplicableForInst(inst, expInfo) && expInfo.type == type);
    });
}

/**
 * Get the bitfield register name for a peripheral instance.
 *
 * Generates register names like "AdcaRegs", "Epwm1Regs", "ScibRegs" based on
 * the peripheral module type and instance configuration.
 *
 * @param {Object} inst - SysConfig module instance object
 * @param {string} modName - Module name (e.g., "adc", "epwm", "sci")
 * @param {Object} bitfieldInstanceNames - Map of instance identifiers to register name functions
 * @param {Object} expInfo - Export info object (may contain bitfieldInstance override)
 * @returns {string} Register base name (e.g., "AdcaRegs", "Epwm1Regs")
 */
function getExportModInfoBitfieldRegForInst(inst, modName, bitfieldInstanceNames, expInfo)
{
    // Determine which bitfield instance mapping to use
    let bitfieldInstance = (expInfo && expInfo.bitfieldInstance) ? expInfo.bitfieldInstance : "default";

    // Validate bitfieldInstanceNames is provided
    if (!bitfieldInstanceNames) {
        return "UnknownRegs";
    }

    // Get the register name function for this instance type
    let bitfieldInstanceFunc = bitfieldInstanceNames[bitfieldInstance];

    // Fallback to "default" if specific instance function not found
    if (!bitfieldInstanceFunc && bitfieldInstance !== "default") {
        bitfieldInstanceFunc = bitfieldInstanceNames["default"];
    }

    // Return error placeholder if no function available
    if (!bitfieldInstanceFunc) {
        return "UnknownRegs";
    }

    // Method 1: Extract instance from pinmux $solution (preferred)
    // This works for modules with pinmux assignments (e.g., GPIO-mapped peripherals)
    if (inst && inst[modName] && inst[modName].$solution) {
        let pinmuxToolPeripheral = inst[modName].$solution.peripheralName;
        // Extract instance suffix: "ADCA" -> "a", "EPWM1" -> "1"
        return bitfieldInstanceFunc(pinmuxToolPeripheral.toLowerCase().replace(modName, ""));
    }

    // Method 2: Extract instance from module properties or $name
    // For modules without pinmux solutions (e.g., CPUTIMER, standalone ADC)
    let instNumber = "";

    // Step 2a: Check for explicit instance properties on the module
    if (inst && inst[modName]) {
        if (inst[modName].timerNumber !== undefined) {
            instNumber = String(inst[modName].timerNumber);
        } else if (inst[modName].instance !== undefined) {
            instNumber = String(inst[modName].instance);
        }
    }

    // Step 2b: Extract instance from SysConfig instance $name
    // Handles naming patterns like "myADCA", "myEPWM1", "mySCIB", etc.
    if (instNumber === "" && inst && inst.$name) {
        let instName = inst.$name;
        let modNameUpper = modName.toUpperCase();

        // Peripherals with letter instances (A, B, C, D)
        const LETTER_PERIPHERALS = ["adc", "sci", "spi", "i2c", "can", "mcan", "dcan", "fsi", "lin", "pmbus", "mcbsp"];
        if (LETTER_PERIPHERALS.includes(modName)) {
            let match = instName.match(new RegExp(modNameUpper + "([A-D])", "i"));
            if (match) {
                instNumber = match[1].toLowerCase();
            }
        }

        // Peripherals with number instances (1, 2, 3, ...)
        const NUMBER_PERIPHERALS = ["epwm", "ecap", "eqep", "cmpss", "dac", "clb", "sdfm", "hrpwm"];
        if (NUMBER_PERIPHERALS.includes(modName) && instNumber === "") {
            let match = instName.match(new RegExp(modNameUpper + "(\\d+)", "i"));
            if (match) {
                instNumber = match[1];
            }
        }

        // Generic fallback: try any trailing letter or number after module name
        if (instNumber === "") {
            let letterMatch = instName.match(new RegExp(modNameUpper + "([A-Z])", "i"));
            if (letterMatch) {
                instNumber = letterMatch[1].toLowerCase();
            } else {
                let numMatch = instName.match(new RegExp(modNameUpper + "(\\d+)", "i"));
                if (numMatch) {
                    instNumber = numMatch[1];
                }
            }
        }
    }

    // Step 2c: Apply module-specific defaults if no instance identified
    if (instNumber === "") {
        switch (modName) {
            case "cputimer":
                instNumber = "0";   // Default to CPUTIMER0
                break;
            case "adc":
            case "sci":
            case "spi":
            case "i2c":
            case "can":
                instNumber = "a";   // Default to instance A for letter-based peripherals
                break;
            case "epwm":
            case "ecap":
            case "eqep":
            case "cmpss":
                instNumber = "1";   // Default to instance 1 for number-based peripherals
                break;
            default:
                // Leave empty for modules without multiple instances
                break;
        }
    }

    // Step 2d: Look up instance-specific mapping function if available
    // This allows modules to define mappings like "0" -> "AdcaRegs" for numeric instance names
    if (instNumber !== "" && bitfieldInstanceNames[instNumber]) {
        bitfieldInstanceFunc = bitfieldInstanceNames[instNumber];
    }

    return bitfieldInstanceFunc(instNumber);
}

/**
 * Check if an export info object is applicable for a given instance.
 * @param {Object} inst - SysConfig module instance
 * @param {Object} expInfo - Export information object with optional applicable function
 * @returns {boolean} True if applicable (or no applicable function defined)
 */
function isExportModInfoApplicableForInst(inst, expInfo) {
    if (!expInfo.applicable) {
        return true;
    }
    return expInfo.applicable(inst);
}

/**
 * Get the list of supported export module names for the current device.
 * Returns device-specific module lists based on hardware availability.
 * @returns {Array<string>} Array of module names (e.g., ["sci", "spi", "adc", ...])
 */
function getExportModModuleNames() {
    let deviceName = transferCommon.getDeviceName();
    let expModuleNames;
    switch(deviceName)
    {
        //=====================================================================
        // Gen2 Devices (F2802x, F2803x, F2805x, F2806x)
        // Note: Gen2 uses SysCtrlRegs, AdcRegs (not ClkCfgRegs, AdcaRegs)
        //=====================================================================

        //---------------------------------------------------------------------
        // F2802x (PiccoloA) - Entry-level Gen2
        // Max 40MHz, HRPWM, LIN, No eCAN, No DMA, No CLA
        //---------------------------------------------------------------------
        case "F2802x":
            expModuleNames = [
                // Communication
                "sci", "spi", "i2c", "lin",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm",
                // Analog
                "adc", "cmpss",
                // System
                "gpio", "flash"
            ];
            break;

        //---------------------------------------------------------------------
        // F2803x (PiccoloB) - Mid-range Gen2
        // Max 60MHz, CLA, DMA, eCAN, LIN
        //---------------------------------------------------------------------
        case "F2803x":
            expModuleNames = [
                // Communication
                "sci", "spi", "i2c", "can", "lin",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm",
                // Analog
                "adc", "cmpss",
                // Accelerators
                "cla",
                // System
                "gpio", "dma", "flash"
            ];
            break;

        //---------------------------------------------------------------------
        // F2805x (Gizmo) - Motor control Gen2
        // Max 60MHz, eCAN, dual eQEP, No CLA, No DMA
        //---------------------------------------------------------------------
        case "F2805x":
            expModuleNames = [
                // Communication
                "sci", "spi", "i2c", "can",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm",
                // Analog
                "adc", "cmpss",
                // System
                "gpio", "flash"
            ];
            break;

        //---------------------------------------------------------------------
        // F2806x (Octave) - Highest performance Gen2
        // Max 90MHz, USB, CLA, DMA, eCAN
        //---------------------------------------------------------------------
        case "F2806x":
            expModuleNames = [
                // Communication
                "sci", "spi", "i2c", "can",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm",
                // Analog
                "adc", "cmpss",
                // Accelerators
                "cla",
                // System
                "gpio", "dma", "flash", "usb"
            ];
            break;

        //=====================================================================
        // Gen3 Devices
        //=====================================================================

        //---------------------------------------------------------------------
        // F280013x - Small device, No LIN, No FSI, No DAC, No CLB, No SDFM
        // Note: No PGA, DMA, JTAG registers files available
        //---------------------------------------------------------------------
        case "F280013x":
            expModuleNames = [
                // Communication
                "sci", "spi", "i2c", "can",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm",
                // Analog
                "adc", "cmpss",
                // System
                "gpio", "flash", "dcc", "xbar", "epg"
            ];
            break;

        //---------------------------------------------------------------------
        // F28002x - Has LIN, PMBus, CLB, ERAD, HRCAP, DMA, BGCRC, FSI
        // Note: No DAC, No SDFM, No PGA
        //---------------------------------------------------------------------
        case "F28002x":
            expModuleNames = [
                // Communication
                "sci", "spi", "i2c", "can", "lin", "pmbus", "fsirx", "fsitx",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm", "hrcap",
                // Analog
                "adc", "cmpss",
                // Accelerators
                "clb",
                // System
                "gpio", "dma", "flash", "dcc", "xbar", "bgcrc", "erad"
            ];
            break;

        //---------------------------------------------------------------------
        // F280015x - Has LIN, PMBus, EPG, MCAN
        // Note: No FSI, No DAC, No CLB, No SDFM, No PGA, No DMA
        //---------------------------------------------------------------------
        case "F280015x":
            expModuleNames = [
                // Communication
                "sci", "spi", "i2c", "can", "mcan", "lin", "pmbus",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm",
                // Analog
                "adc", "cmpss",
                // System
                "gpio", "flash", "dcc", "xbar", "epg"
            ];
            break;

        //---------------------------------------------------------------------
        // F28003x - Has LIN, FSI, CLB, SDFM, CLA, HRCAP, PMBus, MCAN, BGCRC, ERAD, EPG, WWDT
        //           SENT, AES
        //---------------------------------------------------------------------
        case "F28003x":
            expModuleNames = [
                // Communication
                "sci", "spi", "i2c", "can", "mcan", "lin", "pmbus", "fsirx", "fsitx",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm", "hrcap",
                // Analog
                "adc", "cmpss", "dac", "sdfm",
                // Accelerators
                "cla", "clb",
                // System
                "gpio", "dma", "flash", "dcc", "xbar", "bgcrc", "erad", "epg", "wwdt",
                // Security/Misc
                "sent", "aes"
            ];
            break;

        //---------------------------------------------------------------------
        // F28004x - Has LIN, CLB, SDFM, CLA, HRCAP, PMBus, DCC, PGA, ERAD, FSI
        //           SENT
        // Note: No BGCRC registers
        //---------------------------------------------------------------------
        case "F28004x":
            expModuleNames = [
                // Communication
                "sci", "spi", "i2c", "can", "lin", "pmbus", "fsirx", "fsitx",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm", "hrcap",
                // Analog
                "adc", "cmpss", "dac", "sdfm", "pga",
                // Accelerators
                "cla", "clb",
                // System
                "gpio", "dma", "flash", "dcc", "xbar", "erad",
                // Misc
                "sent"
            ];
            break;

        //---------------------------------------------------------------------
        // F2807x - Has LIN, SDFM, CLA, CLB, EMIF, McBSP
        // Note: No USB, FSI, MCAN, DCC, HRCAP, ERAD, BGCRC registers
        //---------------------------------------------------------------------
        case "F2807x":
            expModuleNames = [
                // Communication
                "sci", "spi", "i2c", "can", "lin", "mcbsp",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm",
                // Analog
                "adc", "cmpss", "dac", "sdfm",
                // Accelerators
                "cla", "clb",
                // System
                "gpio", "dma", "flash", "emif", "xbar"
            ];
            break;

        //---------------------------------------------------------------------
        // F2837xD - Dual-core: LIN, SDFM, CLA, CLB, EMIF, McBSP, UPP, IPC
        // Note: No USB, DCC, ERAD, FSI, BGCRC registers
        //---------------------------------------------------------------------
        case "F2837xD":
            expModuleNames = [
                // Communication
                "sci", "spi", "i2c", "can", "lin", "mcbsp",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm",
                // Analog
                "adc", "cmpss", "dac", "sdfm",
                // Accelerators
                "cla", "clb",
                // Multi-core
                "ipc",
                // System
                "gpio", "dma", "flash", "emif", "xbar"
            ];
            break;

        //---------------------------------------------------------------------
        // F2837xS - Single-core: LIN, SDFM, CLA, CLB, EMIF, McBSP, UPP
        // Note: No USB, DCC, ERAD, FSI, BGCRC registers
        //---------------------------------------------------------------------
        case "F2837xS":
            expModuleNames = [
                // Communication
                "sci", "spi", "i2c", "can", "lin", "mcbsp",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm",
                // Analog
                "adc", "cmpss", "dac", "sdfm",
                // Accelerators
                "cla", "clb",
                // System
                "gpio", "dma", "flash", "emif", "xbar"
            ];
            break;

        //---------------------------------------------------------------------
        // F2838x - Full featured: LIN, CLB, SDFM, CLA, HRCAP, PMBus, EMIF, McBSP
        //          MCAN, FSI, BGCRC, ERAD, WWDT, IPC (dual-core), EtherCAT
        //---------------------------------------------------------------------
        case "F2838x":
            expModuleNames = [
                // Communication
                "sci", "spi", "i2c", "can", "mcan", "lin", "pmbus", "mcbsp", "fsirx", "fsitx",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm", "hrcap",
                // Analog
                "adc", "cmpss", "dac", "sdfm",
                // Accelerators
                "cla", "clb",
                // Multi-core
                "ipc",
                // System
                "gpio", "dma", "flash", "dcc", "emif", "xbar", "bgcrc", "erad", "wwdt",
                // Networking
                "ethercat"
            ];
            break;

        //---------------------------------------------------------------------
        // F28P55x - Has LIN, CLB, CLA, HRCAP, PMBus, PGA, MCAN, FSI, ERAD, EPG, WWDT
        //           SENT, ESM, AES
        // Note: No DCAN (only MCAN), No SDFM, No BGCRC registers
        //---------------------------------------------------------------------
        case "F28P55x":
            expModuleNames = [
                // Communication (Note: MCAN only, no DCAN)
                "sci", "spi", "i2c", "mcan", "lin", "pmbus", "fsirx", "fsitx",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm", "hrcap",
                // Analog
                "adc", "cmpss", "dac", "pga",
                // Accelerators
                "cla", "clb",
                // System
                "gpio", "dma", "flash", "dcc", "xbar", "erad", "epg", "wwdt",
                // Security/Safety/Misc
                "sent", "esm", "aes"
            ];
            break;

        //---------------------------------------------------------------------
        // F28P65x - Has LIN, CLB, SDFM, CLA, HRCAP, PMBus, EMIF, MCAN, FSI
        //          BGCRC, ERAD, EPG, WWDT, IPC (dual-core), SENT, ESM
        //---------------------------------------------------------------------
        case "F28P65x":
            expModuleNames = [
                // Communication
                "sci", "spi", "i2c", "can", "mcan", "lin", "pmbus", "fsirx", "fsitx",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm", "hrcap",
                // Analog
                "adc", "cmpss", "dac", "sdfm",
                // Accelerators
                "cla", "clb",
                // Multi-core
                "ipc",
                // System
                "gpio", "dma", "flash", "dcc", "emif", "xbar", "bgcrc", "erad", "epg", "wwdt",
                // Safety/Misc
                "sent", "esm"
            ];
            break;

        //---------------------------------------------------------------------
        // Default fallback - include only modules with available registers
        // Individual module applicability functions will filter by device
        //---------------------------------------------------------------------
        default:
            expModuleNames = [
                // Communication
                "sci", "spi", "i2c", "can", "mcan", "lin", "pmbus", "mcbsp", "fsirx", "fsitx",
                // Control/Timing
                "eqep", "epwm", "ecap", "cputimer", "hrpwm", "hrcap",
                // Analog
                "adc", "cmpss", "dac", "sdfm", "pga",
                // Accelerators
                "cla", "clb",
                // Multi-core
                "ipc",
                // System
                "gpio", "dma", "flash", "dcc", "emif", "xbar", "bgcrc", "erad", "epg", "wwdt"
            ];
            break;
    }

   return expModuleNames;
}

/**
 * Get module names that are always exported regardless of SysConfig configuration.
 * These modules provide system-level diagnostics that are always relevant.
 * @param {string} deviceName - Device name (e.g., "F280015x", "F2802x")
 * @returns {Array<string>} Array of always-exported module names
 */
function getExportAlwaysModModuleNames(deviceName) {
    // These modules are exported for all supported devices
    const common = [
        "sysctl",       // System Control
        "interrupt",    // PIE controller
        "memory",       // Memory configuration
        "memoryerror",  // Memory ECC errors
        "syserror",     // System error status flags
        "testerror"     // Test error diagnostics
    ];

    if (DEVICES_GEN3.includes(deviceName)) {
        // Gen3-only modules
        return [...common,
            "asysctl",  // Analog System Control (Gen3 only)
            "dcsm",     // Dual Code Security Module (Gen3 only)
            "nmi",      // Non-Maskable Interrupts (Gen3 register structure)
            "bgcrc"     // Background CRC (Gen3 only)
        ];
    }
    // Gen2: only common modules
    return common;
}

//=============================================================================
// Module Exports
//=============================================================================
exports = {
    //-------------------------------------------------------------------------
    // Device Constants (import these instead of duplicating arrays)
    //-------------------------------------------------------------------------
    // Core device family
    DEVICES_GEN2,
    DEVICES_GEN3,
    DEVICES_ALL,
    DEVICES_WITH_CDT_SUPPORT,

    // PLL Architecture
    DEVICES_WITH_PLLCR_DIV,  // Gen2 PLL
    DEVICES_WITH_REFDIV_ODIV,
    DEVICES_WITH_FMULT,

    // SYSCLK Frequency Groups
    DEVICES_WITH_100MHZ_MAX_SYSCLK,
    DEVICES_WITH_120MHZ_MAX_SYSCLK,
    DEVICES_WITH_150MHZ_MAX_SYSCLK,
    DEVICES_WITH_200MHZ_MAX_SYSCLK,

    // ADC Instances
    DEVICES_WITH_ADCA,
    DEVICES_WITH_ADCB,
    DEVICES_WITH_ADCC,
    DEVICES_WITH_ADCD,
    DEVICES_WITH_ADCE,
    DEVICES_WITH_ADC_INTEGER_PRESCALE,
    DEVICES_WITH_ADC_HALFSTEP_PRESCALE,
    DEVICES_WITH_ADC_CONFIGURABLE_RESOLUTION,

    // eQEP Instances
    DEVICES_WITH_EQEP1,
    DEVICES_WITH_EQEP2,
    DEVICES_WITH_EQEP3,
    DEVICES_WITH_QMAE,

    // Clock Features
    DEVICES_WITH_AUXPLL,
    DEVICES_WITH_EPWMCLKDIV,
    DEVICES_WITH_HRPWM,
    DEVICES_WITH_HRCAP,

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
    DEVICES_WITH_CLB,  // TODO: Add CLB diagnostic support in future CDT release
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

    // Helper functions
    getDeviceName,
    getMaxSysclk,
    isValidDevice,
    hasFeature,
    getMaxGpioPin,
    getGpioPinCount,

    //-------------------------------------------------------------------------
    // Export Module Functions
    //-------------------------------------------------------------------------
    getExporterComsLinkName,
    getNonExporterInstances,
    getExportKeyValuesForMod,
    getExportModModuleNames,
    getExportAlwaysModModuleNames,
    getInstanceExportModsInfo,
    isExportModInfoApplicableForInst,
    getExportModInfoBitfieldRegForInst,
    getInstanceExportModsInfoWithType
};