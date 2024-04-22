let fastPlusModePins = {
    SDA: {
        PMBUSA: {pins: ["GPIO2", "GPIO32"]},
    },
    SCL: {
        PMBUSA: {pins: ["GPIO3", "GPIO9"]},
    },
    ALERT: {
        PMBUSA: {pins: ["GPIO13", "GPIO19", "GPIO27", "GPIO37", "GPIO43", "GPIO45", "GPIO67"]},
    },
    CTL: {
        PMBUSA: {pins: ["GPIO12", "GPIO18", "GPIO26", "GPIO35", "GPIO42", "GPIO44", "GPIO68"]},
    },
}

module.exports = {
    fastPlusModePins: fastPlusModePins,
}