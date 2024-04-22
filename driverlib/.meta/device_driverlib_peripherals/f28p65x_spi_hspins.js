let hsModePins = {
    PICO: {
        SPIA: {pins:["GPIO58"]},
        SPIB: {pins:["GPIO63"]},
        SPIC: {pins:["GPIO69"]},
        SPID: {pins:["GPIO91"]},
    },
    POCI: {
        SPIA: {pins:["GPIO59"]},
        SPIB: {pins:["GPIO64"]},
        SPIC: {pins:["GPIO70"]},
        SPID: {pins:["GPIO92"]},
    },
    CLK: {
        SPIA: {pins:["GPIO60"]},
        SPIB: {pins:["GPIO65"]},
        SPIC: {pins:["GPIO71"]},
        SPID: {pins:["GPIO93"]},
    },
    PTE: {
        SPIA: {pins:["GPIO61"]},
        SPIB: {pins:["GPIO66"]},
        SPIC: {pins:["GPIO72"]},
        SPID: {pins:["GPIO94"]},
    }
}

module.exports = {
	hsModePins: hsModePins,
}
