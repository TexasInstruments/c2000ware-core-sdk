//=============================================================================
// export_mod_uart.js - UART Export Module for CDT
//=============================================================================
// Purpose: Expose UART (SCI) diagnostic information for CDT
// Note: UART on C2000 is implemented via SCI peripheral
// Devices: All Gen3 devices
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

const DEVICES_WITH_UART = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
];

let exportsInfo = [
    {
        name: "RXRDY",
        displayName: "Receive Ready",
        type: 'led',
        register: "SCIRXST.RXRDY",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_RXST) & SCI_RXST_RXRDY) == SCI_RXST_RXRDY)`,
        applicable: (inst) => {
            return DEVICES_WITH_UART.includes(deviceName);
        }
    },
    {
        name: "TXRDY",
        displayName: "Transmit Ready",
        type: 'led',
        register: "SCICTL2.TXRDY",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_CTL2) & SCI_CTL2_TXRDY) == SCI_CTL2_TXRDY)`,
        applicable: (inst) => {
            return DEVICES_WITH_UART.includes(deviceName);
        }
    },
    {
        name: "RXERROR",
        displayName: "Receive Error",
        type: 'led',
        register: "SCIRXST.RXERROR",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_RXST) & SCI_RXST_RXERROR) == SCI_RXST_RXERROR)`,
        applicable: (inst) => {
            return DEVICES_WITH_UART.includes(deviceName);
        }
    },
    {
        name: "BRKDT",
        displayName: "Break Detect",
        type: 'led',
        register: "SCIRXST.BRKDT",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_RXST) & SCI_RXST_BRKDT) == SCI_RXST_BRKDT)`,
        applicable: (inst) => {
            return DEVICES_WITH_UART.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "Sci" + instName + "Regs" },
};

let exportsRegisterSkips = [];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
