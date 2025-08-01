var deviceName = system.deviceData.device;
let exportsInfo = [
  {
    name: "PER",
    displayName: "Parity Error Detected",
    type: 'led',
    register: "CAN_ES.PER",
    updateFunc: (instBase) => `((HWREGH(${instBase} + CAN_O_ES) & CAN_ES_PER) == CAN_ES_PER)`,
    applicable: (inst) => {
            return (["F280013x", "F280015x", "F28003x"].includes(deviceName)? true: false);
    } 
  },
  {
    name: "BOff",
    displayName: "Bus-Off Status",
    type: 'led',
    register: "CAN_ES.BOff",
    updateFunc: (instBase) => `((HWREGH(${instBase} + CAN_O_ES) & CAN_ES_BOff) == CAN_ES_BOff)`,
    applicable: (inst) => {
            return (["F280013x", "F280015x", "F28003x"].includes(deviceName)? true: false);
    } 
  },
  {
    name: "EPass",
    displayName: "Error-Passive Status",
    type: 'led',
    register: "CAN_ES.EPass",
    updateFunc: (instBase) => `((HWREGH(${instBase} + CAN_O_ES) & CAN_ES_EP) !== 0)`,
    applicable: (inst) => {
            return (["F280013x", "F280015x", "F28003x"].includes(deviceName)? true: false);
    } 
  },
];

let bitfiledInstanceNames = {
    "default": (instName) => { return "Can"+ instName + "Regs" },
}

let exportsRegisterSkips = [
   
]

exports = {
    exportsInfo: exportsInfo,
    bitfiledInstanceNames : bitfiledInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}