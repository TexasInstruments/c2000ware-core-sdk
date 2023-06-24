let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");


let device_driverlib_peripheral =      // need to change
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memcfg.js");
let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");
let device_driverlib_int_names =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_interrupt.js");

/* Intro splash on GUI */
let longDescription = `The Inter-Processor Communication (IPC) allows to setup a communication channel 
between various cores.`;
var sharedModuleInstances = undefined;

var driverlibIntNames = [];

device_driverlib_int_names.interrupts.
    forEach((element, index) =>
        {
            if ((element.int_define_name.includes("INT_CIPC")) || (element.int_define_name.includes("INT_IPC_")))
                {
                    driverlibIntNames.push(element.int_define_name);
                }
        }
);


let IntNumber = [                      // Only for display in GUI, replaced with driverlib names for codegen
{name: "0", displayName: "IPC 0"},    
{name: "1", displayName: "IPC 1"},
{name: "2", displayName: "IPC 2"},
{name: "3", displayName: "IPC 3"},
]

let bootModes = [                                  
{name: "FLASH", displayName: "Boot from Flash"},
{name: "RAM", displayName: "Boot from RAM"},
]


let IPC_FLAGS = [                   
    {name: "IPC_NO_FLAG",     displayName: "IPC_NO_FLAG"},
    {name: "IPC_FLAG0",       displayName: "IPC_FLAG0"},
    {name: "IPC_FLAG1",       displayName: "IPC_FLAG1"},
    {name: "IPC_FLAG2",       displayName: "IPC_FLAG2"},
    {name: "IPC_FLAG3",       displayName: "IPC_FLAG3"},
    {name: "IPC_FLAG4",       displayName: "IPC_FLAG4"},
    {name: "IPC_FLAG5",       displayName: "IPC_FLAG5"},
    {name: "IPC_FLAG6",       displayName: "IPC_FLAG6"},
    {name: "IPC_FLAG7",       displayName: "IPC_FLAG7"},
    {name: "IPC_FLAG8",       displayName: "IPC_FLAG8"},
    {name: "IPC_FLAG9",       displayName: "IPC_FLAG9"},
    {name: "IPC_FLAG10",      displayName: "IPC_FLAG10"},
    {name: "IPC_FLAG11",      displayName: "IPC_FLAG11"},
    {name: "IPC_FLAG12",      displayName: "IPC_FLAG12"},
    {name: "IPC_FLAG13",      displayName: "IPC_FLAG13"},
    {name: "IPC_FLAG14",      displayName: "IPC_FLAG14"},
    {name: "IPC_FLAG15",      displayName: "IPC_FLAG15"},
    {name: "IPC_FLAG16",      displayName: "IPC_FLAG16"},
    {name: "IPC_FLAG17",      displayName: "IPC_FLAG17"},
    {name: "IPC_FLAG18",      displayName: "IPC_FLAG18"},
    {name: "IPC_FLAG19",      displayName: "IPC_FLAG19"},
    {name: "IPC_FLAG20",      displayName: "IPC_FLAG20"},
    {name: "IPC_FLAG21",      displayName: "IPC_FLAG21"},
    {name: "IPC_FLAG22",      displayName: "IPC_FLAG22"},
    {name: "IPC_FLAG23",      displayName: "IPC_FLAG23"},
    {name: "IPC_FLAG24",      displayName: "IPC_FLAG24"},
    {name: "IPC_FLAG25",      displayName: "IPC_FLAG25"},
    {name: "IPC_FLAG26",      displayName: "IPC_FLAG26"},
    {name: "IPC_FLAG27",      displayName: "IPC_FLAG27"},
    {name: "IPC_FLAG28",      displayName: "IPC_FLAG28"},
    {name: "IPC_FLAG29",      displayName: "IPC_FLAG29"},
    {name: "IPC_FLAG30",      displayName: "IPC_FLAG30"},
    {name: "IPC_FLAG31",      displayName: "IPC_FLAG31"},
    {name: "IPC_FLAG_ALL",    displayName: "IPC_FLAG_ALL"}
]

function onChangeEnabledInts(inst, ui){
    for(var intIndex in IntNumber){ 
        var currentINT = IntNumber[intIndex].name
        var inti = (currentINT).replace(/[^0-9]/g,'')    // Gets Number after removing all other characters
        var intConfigs = [ 
            "enableInterrupt" + inti.toString(),
        ]

        if (ui)
        {
            for (var intConfig of intConfigs)
            {
                if((inst.registerOtherCoreInterrupts).includes(currentINT))
                {
                    ui[intConfig].hidden = false;
                }
                else
                {
                    ui[intConfig].hidden = true;
                }
            }
        }
    }
}

var IPC_SLICE = IPC_FLAGS.slice(1,33);  // Used when need flag list without 'all' and 'none'

function onChangeMakeFlags(inst, ui){
    for(var flagIndex in IPC_SLICE){ 
        var currentFLAG = IPC_SLICE[flagIndex].name
        if((!currentFLAG.includes("_ALL")) && (!currentFLAG.includes("NO")))
        {
            var flagi = (currentFLAG).replace(/[^0-9]/g,'')    // Gets number after removing all other characters
            let flagConfigs = [ 
                "flagHandler"+ flagi.toString(),
            ]
            if (flagi < 4){
                flagConfigs.push("enableInterrupt" + flagi.toString())
            }
            if (ui)
            {
                var prepend = "CPU1_to_CPU2_";
                if(!Common.isContextCPU1()){
                    prepend = "CPU2_to_CPU1_";
                }
                
                for (var flagConfig of flagConfigs)
                {
                    if((inst.ipcRegisterFlag).includes(currentFLAG))
                    {
                        ui[flagConfig].hidden = false;
                    }
                    else
                    {
                        ui[flagConfig].hidden = true;
                        if (flagConfig.includes("flagHandler")){
                            inst[flagConfig] = prepend + "IPC_FLAG" + flagi.toString();
                        }
                        if (flagConfig.includes("enableInterrupt")){
                            inst[flagConfig] = false;
                        }
                    }
                }
            }
        }
    }
}

var intConfigs = [           // Submodule for interrup initialization and configuration
    {
        name        : "registerInterrupts",
        displayName : "Register Interrupts to Receive signal from other Core",
        description : 'Whether or not to register interrupt handlers in the interrupt module.',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : IntNumber
    }
]


var otherCoreConfigs = [ 
    {
        name        : "registerOtherCoreInterrupts",
        displayName : "Register Interrupts for other Core",
        description : 'Whether or not to register interrupts for the other core.',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : IntNumber,           
        onChange    : onChangeEnabledInts
    },
]

var flagsConfigs = [            // submodule for initializing selectable flags
    {
        name: "ipcRegisterFlag",
        displayName:"Designate flag as usable",
        description : "Type of IPC Sync Flag",
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : IPC_SLICE,
        onChange    : onChangeMakeFlags
    }
]

for(var flagIndex in IPC_FLAGS){
    var currentFLAG = IPC_FLAGS[flagIndex].name
    if((!currentFLAG.includes("_ALL")) && (!currentFLAG.includes("NO")))
    {
        var prepend = "CPU1_to_CPU2_";
        if(!Common.isContextCPU1()){
            prepend = "CPU2_to_CPU1_";
        }
        var flagi = (currentFLAG).replace(/[^0-9]/g, '')
        let thisFlagsConfig = [
            {
                name        : "flagHandler"+ flagi.toString(),
                displayName : "Flag Name",
                description : 'Define custom flag name in generated board.h',
                hidden      : true,
                readOnly    : false,
                default     : prepend + 'IPC_FLAG' + flagi.toString()
            },
        ]
        if (flagi < 4){
            thisFlagsConfig.push({
                name: "enableInterrupt" + flagi.toString(),
                displayName : "Generate Interrupt on other Core",
                description : 'Generate IPC' + flagi.toString() + ' on other CPU',
                hidden      : true,
                default     : false,
            })
        }
        flagsConfigs = flagsConfigs.concat([
            {
                name: "GROUP_FLAG" + flagi.toString(),
                displayName: "Enable IPC_FLAG" + flagi.toString(),
                description: "",
                longDescription: "",
                config: thisFlagsConfig
            }
        ])
    }
}

//var IPC_ISR_FLAGS = IPC_FLAGS.slice(1,5);

for(var intIndex in IntNumber){ 
    var currentINT = IntNumber[intIndex].name
    var inti = (currentINT).replace(/[^0-9]/g,'')
    otherCoreConfigs = otherCoreConfigs.concat([
                {
                    name: "enableInterrupt" + inti.toString(),
                    displayName : "Register IPC" + inti.toString(),
                    description : 'Register IPC' + inti.toString() + ' for this CPU with the PIE',
                    hidden      : true,
                    default     : false,
                },
    ])
}

let staticConfig = []

if(Common.isContextCPU1()) {
    staticConfig = staticConfig.concat(
        [{
            name        : "bootModeSelect",
            displayName : "Select CPU2 Boot Mode",
            description : 'You still need to boot CPU2 in .c code if you want to use CPU2',
            longDescription: 'You still need to use "Device_bootCPU2(BOOT_MODE_CPU2)" in code to actually boot CPU2', 
            hidden      : false,
            default     : bootModes[0].name,
            options     : bootModes    
        }]
    )

}

staticConfig = staticConfig.concat([
    {
        name: "GROUP_INIT_FLAGS",
        displayName: "Initialize Flags",
        description: "",
        longDescription: "Choose Flags to Initialize for use",
        collapsed: false,
        config: flagsConfigs,
    },
    {
        name        : "registerInterrupts",
        displayName : "Register Interrupts to Receive signal from other Core",
        description : 'Whether or not to register interrupt handlers in the interrupt module.',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : IntNumber    
    }
]);

function onValidate(inst, validation)
{
    if (Common.isMultiCoreSysConfig())
    {
        if (Common.isModuleOnOtherContext("/driverlib/ipc.js") == false)
        {
            validation.logError("The IPC module needs to be added on both CPUs", 
            inst, "registerInterrupts");
        }
    }
    if (!Common.isMultiCoreSysConfig())
    {
        validation.logWarning("The IPC module is intended for use in a dual-core system. Error checking is limited in single-core mode.", 
        inst, "registerInterrupts");
    }

    if (Common.isMultiCoreSysConfig())   // only look for things owned by CPU2 if multicore device
    {
        var contextNames = Common.getContextNames();
    	var context1 = "";
        var context2 = "";
    	for (var cntx of contextNames) 
    	{
    		if (cntx.slice(-1) == "1")       // Look for CPU1 Context 
    		{
    		context1 = cntx;
    		}	

            if (cntx.slice(-1) == "2")       // Look for CPU1 Context 
    		{
    		context2 = cntx;
    		}	
    	}
    
    	var CPU1_mod = Common.getModuleForCore('/driverlib/ipc.js', context1);   // get module from core 1
        var CPU2_mod = Common.getModuleForCore('/driverlib/ipc.js', context2);   // get module from core 2
    	var syncFlagVal1 = "";
        var syncFlagVal2 = "";
    	if (CPU1_mod != null)
    	{
            var configs1=[]
	        CPU1_mod.moduleStatic.config.forEach((element, index) =>
            {
                configs1[element.name] = element.config
            });

            if (CPU2_mod != null)
            {
                var configs2=[]
                CPU2_mod.moduleStatic.config.forEach((element, index) =>
                {
                    configs2[element.name] = element.config
                });
                var stat_1 = CPU1_mod.$static;
                syncFlagVal1 = stat_1.ipc_sync_flag;
                if (CPU2_mod != null)
                {
                    var stat_2 = CPU2_mod.$static;
                }
                
                var i = 0;
                var flagHandleList1 = []
                var flagHandleList2 = []
                var doubledIndexCPU1 = []
                var doubledIndexCPU2 = []
                for (i = 0; i < 32; i++){
                    if (i<4){
                        if (stat_1["enableInterrupt"+i]){
                            if(!stat_2["registerInterrupts"].includes(i.toString())){
                                if(Common.isContextCPU1()){
                                    validation.logError("You need to initialize IPC " + i + " PIE INTERRUPT on " + system.getReference(stat_2, "enableInterrupt"+i) + " ", inst, "enableInterrupt" + i);
                                }
                                if(Common.isContextCPU2()){
                                    validation.logError("You need to initialize IPC " + i + " PIE INTERRUPT on this CPU", inst, "registerInterrupts");
                                }
                            }
                        }
                        if (stat_2["enableInterrupt"+i]){
                            if(!stat_1["registerInterrupts"].includes(i.toString())){
                                if(Common.isContextCPU2()){
                                    validation.logError("You need to initialize IPC " + i + " PIE INTERRUPT on " + system.getReference(stat_1, "enableInterrupt"+i) + " ", inst, "enableInterrupt" + i);
                                }
                                if(Common.isContextCPU1()){
                                    validation.logError("You need to initialize IPC " + i + " PIE INTERRUPT on this CPU", inst, "registerInterrupts");
                                }
                            }
                        }
                        if (stat_2["registerInterrupts"].includes(i.toString())){
                            if(!stat_1["enableInterrupt"+i]){
                                if(Common.isContextCPU1()){
                                    validation.logWarning("You are initializing an interrupt on the other CPU without this CPU's corresponding FLAG" + i, inst, "enableInterrupt" + i);
                                }
                                if(Common.isContextCPU2()){
                                    validation.logWarning("You are initializing an interrupt without corresponding IPC_FLAG" + i + " on " + system.getReference(stat_1, "registerInterrupts") + " ", inst, "registerInterrupts");
                                }
                            }
                        }
                        if (stat_1["registerInterrupts"].includes(i.toString())){
                            if(!stat_2["enableInterrupt"+i]){
                                if(Common.isContextCPU2()){
                                    validation.logWarning("You are initializing an interrupt on the other CPU without this CPU's corresponding FLAG" + i, inst, "enableInterrupt" + i);
                                }
                                if(Common.isContextCPU1()){
                                    validation.logWarning("You are initializing an interrupt without corresponding IPC_FLAG" + i + " on " + system.getReference(stat_2, "registerInterrupts") + " ", inst, "registerInterrupts");
                                }
                            }
                        }
                    }
                    var nameFlag = "flagHandler" + i.toString()
                    var old_nameFlag = "IPC_FLAG" + i.toString()   
                    var flagHandle1 = stat_1[nameFlag]
                    var flagHandle2 = stat_2[nameFlag]
                    if ((!doubledIndexCPU1.includes(i)) && (flagHandle1 != old_nameFlag) && (flagHandleList2.includes(flagHandle1) || flagHandleList1.includes(flagHandle1))){
                        if (Common.isContextCPU1()){
                            validation.logError("Two different flags cannot be given the same name, even accross CPUs", inst, nameFlag);
                        }
                        doubledIndexCPU1.push(i)
                    }
                    if ((!doubledIndexCPU2.includes(i)) && (flagHandle2 != old_nameFlag) && (flagHandleList2.includes(flagHandle2) || flagHandleList1.includes(flagHandle2))){
                        if (!Common.isContextCPU1()){
                            validation.logError("Two different flags cannot be given the same name, even accross CPUs", inst, nameFlag);
                        }
                        doubledIndexCPU2.push(i)
                    }

                    flagHandleList1.push(flagHandle1)
                    flagHandleList2.push(flagHandle2)
                }

                flagHandleList1 = []
                flagHandleList2 = []
                for (i = 31; i > -1; i--){
                    var nameFlag = "flagHandler" + i.toString()
                    var old_nameFlag = "IPC_FLAG" + i.toString()   
                    var flagHandle1 = stat_1[nameFlag]
                    var flagHandle2 = stat_2[nameFlag]
                    if ((!doubledIndexCPU1.includes(i)) && (flagHandle1 != old_nameFlag) && (flagHandleList2.includes(flagHandle1) || flagHandleList1.includes(flagHandle1))){
                        if (Common.isContextCPU1()){
                            validation.logError("Two different flags cannot be given the same name, even accross CPUs", inst, nameFlag);
                        }
                        doubledIndexCPU1.push(i)
                    }
                    if ((!doubledIndexCPU2.includes(i)) && (flagHandle2 != old_nameFlag) && (flagHandleList2.includes(flagHandle2) || flagHandleList1.includes(flagHandle2))){
                        if (!Common.isContextCPU1()){
                            validation.logError("Two different flags cannot be given the same name, even accross CPUs", inst, nameFlag);
                        }
                        doubledIndexCPU2.push(i)
                    }
                    flagHandleList1.push(flagHandle1)
                    flagHandleList2.push(flagHandle2)
                }
            }
        }
    }
}


function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["IPC"]));
}

function moduleInstances(inst)
{
    let intReturn =  []
    if ((inst.registerInterrupts).includes("0"))
    {
        intReturn.push ({
            name: "ipcInt0",
            displayName: "IPC 0 PIE INTERRUPT",
            moduleName: "/driverlib/interrupt.js",
            collapsed: true,
            args: {
                $name : driverlibIntNames[0],
                int : "IPC_0",
                pinmuxPeripheralModule :"",
                driverlibInt: driverlibIntNames[0] // Name needs to match driverlibInt name
            }                                       // different for f2838x and f2837xd
        }
        )
    }

    if ((inst.registerInterrupts).includes("1"))
    {
        intReturn.push ({
            name: "ipcInt1",
            displayName: "IPC 1 PIE INTERRUPT",
            moduleName: "/driverlib/interrupt.js",
            collapsed: true,
            args: {
                $name : driverlibIntNames[1],
                int : "IPC_1",
                pinmuxPeripheralModule :"",
                driverlibInt: driverlibIntNames[1] // Name needs to match driverlibInt name
            }                                       // different for f2838x and f2837xd
        }
        )
    }

    if ((inst.registerInterrupts).includes("2"))
    {
        intReturn.push ({
            name: "ipcInt2",
            displayName: "IPC 2 PIE INTERRUPT", 
            moduleName: "/driverlib/interrupt.js",
            collapsed: true,
            args: {
                $name : driverlibIntNames[2],
                int : "IPC_2",
                pinmuxPeripheralModule :"",
                driverlibInt: driverlibIntNames[2] // Name needs to match driverlibInt name
            }                                       // different for f2838x and f2837xd
        }
        )
    }

    if ((inst.registerInterrupts).includes("3"))
    {
        intReturn.push ({
            name: "ipcInt3",
            displayName: "IPC 3 PIE INTERRUPT",
            moduleName: "/driverlib/interrupt.js",
            collapsed: true,
            args: {
                $name : driverlibIntNames[3],
                int : "IPC_3",
                pinmuxPeripheralModule :"",
                driverlibInt: driverlibIntNames[3] // Name needs to match driverlibInt name
            }                                      // different for f2838x and f2837xd
        }
        )
    }

    return intReturn;


}


var ipcModule = {
    peripheralName: "IPC",
    displayName: "IPC",
    maxInstances: Common.peripheralCount("IPC"),
    defaultInstanceName: "myIPC",
    description: "Interprocessor Communication between C28x Cores",
    filterHardware : filterHardware,
    moduleStatic : {
        config: staticConfig,
        moduleInstances: moduleInstances,
        validate: onValidate,
    },
    templates: {
        boardc : "/driverlib/ipc/ipc.board.c.xdt",
        boardh : "/driverlib/ipc/ipc.board.h.xdt"
    },
    //sharedModuleInstances: sharedModuleInstances,
    //moduleInstances     : moduleInstances,
};


exports = ipcModule;

