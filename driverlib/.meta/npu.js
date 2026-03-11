var npuModule = {
    peripheralName: "NPU",
    displayName: "NPU",
    maxInstances: 1,
    defaultInstanceName: "myNPU",
    description: "Neural Processing Unit",
    config: [],
    templates: {
        boardc : "/driverlib/npu/npu.board.c.xdt"
    },
};

exports = npuModule;