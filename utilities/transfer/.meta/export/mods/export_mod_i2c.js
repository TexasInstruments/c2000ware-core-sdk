var deviceName = system.deviceData.device;
let exportsInfo = [
    {
        name: "al",
        displayName: "Arbitration Lost",
        type: 'led',
        register: "I2CSTR.ARBL",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_STR) & I2C_STR_ARBL) == I2C_STR_ARBL)`,
        applicable: (inst) => {
            return ["F280013x", "F280015x", "F28003x"].includes(deviceName) && inst.mode == "CONTROLLER" && inst.initialMode == "SEND_MODE";
        }
    },
    {
        name: "nack",
        displayName: "No Acknowledgement",
        type: 'led',
        register: "I2CSTR.NACK",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_STR) & I2C_STR_NACK) == I2C_STR_NACK)`,
        applicable: (inst) => {
            return ["F280013x", "F280015x", "F28003x"].includes(deviceName) && inst.mode == "CONTROLLER" && inst.initialMode == "SEND_MODE";
        }
    },
    {
        name: "rsfull",
        displayName: "Receive Shift Register Overrun",
        type: 'led',
        register: "I2CSTR.RSFULL",
        updateFunc: (instBase) => `((HWREGH(${instBase} + I2C_O_STR) & I2C_STR_RSFULL) == I2C_STR_RSFULL)`,
        applicable: (inst) => {
            return ["F280013x", "F280015x", "F28003x"].includes(deviceName) && inst.initialMode == "RECEIVE_MODE";
        }
    },
]

let bitfiledInstanceNames = {
    "default": (instName) => { return "I2c"+ instName + "Regs" },
}

let exportsRegisterSkips = [
   {
    name: "FFRX",
    register: "I2CDRR"
  },
  {
    name: "FFTX",
    register: "I2CDXR"
  }
]

exports = {
    exportsInfo: exportsInfo,
    bitfiledInstanceNames : bitfiledInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}