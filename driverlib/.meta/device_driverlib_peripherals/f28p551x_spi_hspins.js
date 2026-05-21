let nonHsModePins = {
    PICO: {
        SPIA: {pins:["GPIO2"]},
        SPIB: {pins:[]},
        SPIC: {pins:[]},
        SPID: {pins:[]},
    },
    POCI: {
        SPIA: {pins:[]},
        SPIB: {pins:["GPIO41"]},
        SPIC: {pins:[]},
        SPID: {pins:[]},
    },
    CLK: {
        SPIA: {pins:["GPIO3", "GPIO9"]},
        SPIB: {pins:["GPIO32"]},
        SPIC: {pins:[]},
        SPID: {pins:[]},
    },
    PTE: {
        SPIA: {pins:[]},
        SPIB: {pins:["GPIO23"]},
        SPIC: {pins:[]},
        SPID: {pins:[]},
    }
}

module.exports = {
	nonHsModePins: nonHsModePins,
}
