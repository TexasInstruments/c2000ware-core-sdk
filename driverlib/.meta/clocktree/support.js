

var device = system.deviceData.device

var F2837xD_bc =
        [
            { instName: "OSCCLKSRCSEL", pinName: "X1_XTAL", name: "X1_XTAL" },
            { instName: "AUXOSCCLKSRCSEL", pinName: "AUXCLKIN", name: "AUXCLKIN" },
            { instName: "AUXOSCCLKSRCSEL", pinName: "INTOSC2", name: "INTOSC2" },
            { instName: "AUXOSCCLKSRCSEL", pinName: "X1_XTAL", name: "X1_XTAL" },
            { instName: "CANABCLKSEL", pinName: "XTAL", name: "XTAL" },            
            { instName: "CANABCLKSEL", pinName: "AUXCLKIN", name: "AUXCLKIN" },  
            { instName: "CANBBCLKSEL", pinName: "XTAL", name: "XTAL" },
            { instName: "CANBBCLKSEL", pinName: "AUXCLKIN", name: "AUXCLKIN" }, 
        ]

var F2837xS_F2807x_bc = 
		[
//			 { instName: "OSCCLKSRCSEL", pinName: "X1_XTAL", name: "X1_XTAL" },
             { instName: "AUXOSCCLKSRCSEL", pinName: "INTOSC2", name: "INTOSC2" },
             { instName: "AUXOSCCLKSRCSEL", pinName: "X1_XTAL", name: "X1_XTAL" },
             { instName: "CANABCLKSEL", pinName: "XTAL", name: "XTAL" },
             { instName: "CANABCLKSEL", pinName: "AUXCLKIN", name: "AUXCLKIN" },
             { instName: "CANBBCLKSEL", pinName: "AUXCLKIN", name: "AUXCLKIN" },   
             { instName: "CANBBCLKSEL", pinName: "XTAL", name: "XTAL" },        
		]

var F2838x_bc =
        [
            //{ instName: "OSCCLKSRCSEL", pinName: "X1_XTAL", name: "X1_XTAL" },
            { instName: "AUXOSCCLKSRCSEL", pinName: "AUXCLKIN", name: "AUXCLKIN" },
            { instName: "AUXOSCCLKSRCSEL", pinName: "INTOSC2", name: "INTOSC2" },
            { instName: "AUXOSCCLKSRCSEL", pinName: "X1_XTAL", name: "X1_XTAL" },
            { instName: "CANABCLKSEL", pinName: "XTAL", name: "XTAL" },            
            { instName: "CANABCLKSEL", pinName: "AUXCLKIN", name: "AUXCLKIN" },  
            { instName: "CANBBCLKSEL", pinName: "XTAL", name: "XTAL" },
            { instName: "CANBBCLKSEL", pinName: "AUXCLKIN", name: "AUXCLKIN" },
            { instName: "DIVSRCSEL", pinName: "PLLSYSCLK", name: "PLLSYSCLK" },
            { instName: "DIVSRCSEL", pinName: "AUXPLLRAWCLK", name: "AUXPLLRAWCLK" },
            { instName: "CMDIVSRCSEL", pinName: "PLLSYSCLK", name: "PLLSYSCLK" },
            { instName: "CMDIVSRCSEL", pinName: "AUXPLLRAWCLK", name: "AUXPLLRAWCLK" },
            { instName: "CPU1", pinName: "PLLSYSCLK", name: "PLLSYSCLK" },
            { instName: "CPU2", pinName: "PLLSYSCLK", name: "PLLSYSCLK" },
            { instName: "CANA_CPUSEL", pinName: "CPU1SYSCLK", name: "CPU1SYSCLK" },
            { instName: "CANA_CPUSEL", pinName: "CPU2SYSCLK", name: "CPU2SYSCLK" },
            { instName: "CANB_CPUSEL", pinName: "CPU1SYSCLK", name: "CPU1SYSCLK" },
            { instName: "CANB_CPUSEL", pinName: "CPU2SYSCLK", name: "CPU2SYSCLK" },
            { instName: "CPUSELx", pinName: "CPU1_SYSCLK", name: "CPU1_SYSCLK" },
            { instName: "CPUSELx", pinName: "CPU2_SYSCLK", name: "CPU2_SYSCLK" },
            { instName: "CANA_PALLOCATE0", pinName: "CM_SYSCLK", name: "CM_SYSCLK"},
            { instName: "CANB_PALLOCATE0", pinName: "CM_SYSCLK", name: "CM_SYSCLK"},
            
        ]

var F28004x_F280013x_bc = 
	    [
            { instName: "CANABCLKSEL", pinName: "XTAL", name: "XTAL" }
	    ]

var F28003x_bc = 
        [
            { instName: "MCANABCLKSEL", pinName: "AUXCLKIN", name: "AUXCLKIN" },
            { instName: "MCANABCLKSEL", pinName: "PLLRAWCLK", name: "PLLRAWCLK" },
            { instName: "CANABCLKSEL", pinName: "AUXCLK", name: "AUXCLK" },
			{ instName: "CANABCLKSEL", pinName: "XTAL", name: "XTAL" }
        ]

var F280015x_bc = 
		[
			{ instName: "MCANABCLKSEL", pinName: "PLLRAWCLK", name: "PLLRAWCLK" },
			{ instName: "MCANABCLKSEL", pinName: "SYSCLK", name: "SYSCLK" },
			{ instName: "MCANABCLKSEL", pinName: "AUXCLKIN", name: "AUXCLKIN" },
			{ instName: "CANABCLKSEL", pinName: "XTAL", name: "XTAL" }
		]
	
exports =
{
    F2837xD_bc              : F2837xD_bc,
    F2837xS_F2807x_bc       : F2837xS_F2807x_bc,
    F28004x_F280013x_bc     : F28004x_F280013x_bc,
    F2838x_bc               : F2838x_bc,
    F28003x_bc              : F28003x_bc,
    F280015x_bc             : F280015x_bc
}