//=============================================================================
// export_mod_pga.js - PGA Export Module for CDT
//=============================================================================
// Purpose: Expose Programmable Gain Amplifier diagnostic information for CDT
// Devices: F28004x, F28P55x (validated against hw_pga.h presence)
// Note: Only 2 Gen3 devices have PGA peripheral
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// PGA availability (validated against hw_pga.h presence in driverlib)
const DEVICES_WITH_PGA = [
    "F28004x", "F28P55x"
];

let exportsInfo = [
    {
        name: "PGAEN",
        displayName: "PGA Enabled",
        type: 'led',
        register: "PGACTL.PGAEN",
        updateFunc: (instBase) => `((HWREGH(${instBase} + PGA_O_CTL) & PGA_CTL_PGAEN) == PGA_CTL_PGAEN)`,
        applicable: (inst) => {
            return DEVICES_WITH_PGA.includes(deviceName);
        }
    },
    {
        name: "FILTRESSEL",
        displayName: "Filter Resistor Select",
        type: 'value',
        register: "PGACTL.FILTRESSEL",
        updateFunc: (instBase) => `((HWREGH(${instBase} + PGA_O_CTL) & PGA_CTL_FILTRESSEL_M) >> PGA_CTL_FILTRESSEL_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_PGA.includes(deviceName);
        }
    },
    {
        name: "GAIN",
        displayName: "Gain Setting",
        type: 'value',
        register: "PGACTL.GAIN",
        updateFunc: (instBase) => `((HWREGH(${instBase} + PGA_O_CTL) & PGA_CTL_GAIN_M) >> PGA_CTL_GAIN_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_PGA.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "Pga" + instName + "Regs" },
};

let exportsRegisterSkips = [];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
