let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let config = [

]


var sfoModule = {
    c2000wareLibraryName: "HRPWM_SFO",
    displayName: "HRPWM SFO",
    defaultInstanceName: "mySFO",
    description: "HRPWM SFO Calibration",
    maxInstances: 1,
    config: config,
    templates: {
        c2000ware_libraries_h           : "/libraries/calibration/hrpwm/templates/sfo.c2000ware_libraries.h.xdt",
        c2000ware_libraries_c           : "/libraries/calibration/hrpwm/templates/sfo.c2000ware_libraries.c.xdt",
        c2000ware_libraries_opt         : "/libraries/calibration/hrpwm/templates/sfo.c2000ware_libraries.opt.xdt",
        c2000ware_libraries_cmd_genlibs : "/libraries/calibration/hrpwm/templates/sfo.c2000ware_libraries.cmd.genlibs.xdt",
    },
};

exports = sfoModule;