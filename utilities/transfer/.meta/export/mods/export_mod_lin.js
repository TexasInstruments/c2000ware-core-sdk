var deviceName = system.deviceData.device;
let exportsInfo = [
    {
        name: "be",
        displayName: "Bit Error",
        type: 'led',
        register: "SCIFLR.BE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_BE) == LIN_SCIFLR_BE)`,
        applicable: (inst) => {
            return (["F280015x", "F28003x"].includes(deviceName) && inst.opMode == "LIN")? true : false;
        },
    },
    {
        name: "pbe",
        displayName: "Physical Bus Error",
        type: 'led',
        register: "SCIFLR.PBE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_PBE) == LIN_SCIFLR_PBE)`,
        applicable: (inst) => {
            return (["F280015x", "F28003x"].includes(deviceName) && inst.opMode == "LIN") ? true : false;
        }
    },
    {
        name: "ce",
        displayName: "Checksum Error",
        type: 'led',
        register: "SCIFLR.CE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_CE) == LIN_SCIFLR_CE)`,
        applicable: (inst) => {
            return (["F280015x", "F28003x"].includes(deviceName) && inst.opMode == "LIN") ? true : false;
        }
    },
    {
        name: "isfe",
        displayName: "Inconsistent Sync Field Error",
        type: 'led',
        register: "SCIFLR.ISFE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_ISFE) == LIN_SCIFLR_ISFE)`,
        applicable: (inst) => {
            return (["F280015x", "F28003x"].includes(deviceName) && inst.opMode == "LIN") ? true : false;
        }
    },
    {
        name: "nre",
        displayName: "No-Response Error",
        type: 'led',
        register: "SCIFLR.NRE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_NRE) == LIN_SCIFLR_NRE)`,
        applicable: (inst) => {
            return (["F280015x", "F28003x"].includes(deviceName) && inst.opMode == "LIN") ? true : false;
        }
    },
    {
        name: "fe",
        displayName: "Framing Error",
        type: 'led',
        register: "SCIFLR.FE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_FE) == LIN_SCIFLR_FE)`,
        applicable: (inst) => {
            return (["F280015x", "F28003x"].includes(deviceName) && (inst.opMode == "LIN" || inst.opMode == "SCI")) ? true : false;
        }
    },
    {
        name: "oe",
        displayName: "Overrun Error",
        type: 'led',
        register: "SCIFLR.OE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_OE) == LIN_SCIFLR_OE)`,
        applicable: (inst) => {
            return (["F280015x", "F28003x"].includes(deviceName) && (inst.opMode == "LIN" || inst.opMode == "SCI")) ? true : false;
        }
    },
    {
        name: "pe",
        displayName: "Parity Error",
        type: 'led',
        register: "SCIFLR.PE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_PE) == LIN_SCIFLR_PE)`,
        applicable: (inst) => {
            return (["F280015x", "F28003x"].includes(deviceName) && (inst.opMode == "LIN" || inst.opMode == "SCI")) ? true : false;
        }
    },
]

let bitfiledInstanceNames = {
    "default": (instName) => { return "Lin"+ instName + "Regs" },
}

let exportsRegisterSkips = [
    
]

exports = {
    exportsInfo: exportsInfo,
    bitfiledInstanceNames : bitfiledInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}