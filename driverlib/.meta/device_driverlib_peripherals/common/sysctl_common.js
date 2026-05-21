
// Multicore devices which have distinct peripherals part of the same CPUSEL register
let groupedCpuSelPeripherals =
{
    "F28P65x": {
        "SCI": ["UARTA", "UARTB"],
        "I2C": ["PMBUSA"],
        "CAN": ["MCANA", "MCANB"],
    },
    "F2838x": {
        "CAN": ["MCANA"],
    }
};

let groupedCpuSelPeripheralIndices =
{
    "UARTA": 17,
    "UARTB": 18,
    "PMBUSA": 17,
    "MCANA": 5,
    "MCANB": 6
};

exports = {
    groupedCpuSelPeripherals,
    groupedCpuSelPeripheralIndices
}
