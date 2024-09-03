let Common   = system.getScript("/driverlib/Common.js");
let clocktree_common   = system.getScript("/driverlib/clocktree/clocktree_common.js");
const multi_core = clocktree_common.multi_core;
if (("system" === system.context || "CPU1" === system.context) && system.deviceData.clockTree)
{

	let Support = system.getScript("./support.js");

	const typeMap = {
		Oscillator: "/driverlib/clocktree/oscillators.js",
		PinFunction: "/driverlib/clocktree/pinFunction.js",
		Mux: "/driverlib/clocktree/mux.js",
		Divider: "/driverlib/clocktree/divider.js",
		Multiplier: "/driverlib/clocktree/multiplier.js",
		Adder: "/driverlib/clocktree/adder.js",
		Gate: "/driverlib/clocktree/unknown.js",
		NamedConnection: "/driverlib/clocktree/namedConnection.js",
		unknown: "/driverlib/clocktree/unknown.js",
	};

	let FreqLabels = _.chain(system.deviceData.clockTree.connectivity).filter((c)=>!_.isEmpty(c.displayName)).map((c)=>c.name).value()

	let namedConnection = _.chain(system.deviceData.clockTree.ipInstances).filter((c) => (c.shape === "NamedConnection")).map((c)=>c.name).value()

	let InputClock = _.chain(system.deviceData.clockTree.ipInstances).filter((c) => (c.displayName === "OSCCLK")).map((c)=>c.name).value()

	FreqLabels = FreqLabels.concat(namedConnection)

	function defaultView(ipInstance) {
		return {
			displayName: (ipInstance.description ?? ipInstance.name).replace(/domain/ig,''),
			ipInstances: [ipInstance.name],
			algorithm: "fanIn",//"fanInAndOut",
			frequencyLabels: FreqLabels,
		}
	}

	let All_Instances = _.map(system.deviceData.clockTree.ipInstances, (i) => i.name)


	let SYSCLK_Entries = [
		"SYSCLK"
	]

	let CPUCLK_Entries = ["PLLSYSCLK", "CPU", "CPUCLK", "SYSCLK", "CPUCLK_domain"]

	var device = system.deviceData.device

	var brokenConnection1

	switch(device)
	{
		case 'F2837xD':
			brokenConnection1 = Support.F2837xD_bc
			break

		case 'F2837xS':
		case 'F2807x':
			brokenConnection1 = Support.F2837xS_F2807x_bc
			break
		
		case 'F2838x':
			brokenConnection1 = Support.F2838x_bc
			break

		case 'F28004x':
		case 'F28002x':		
		case 'F280013x':
			brokenConnection1 = Support.F28004x_F280013x_bc
			break
		
		case 'F28003x':	
			brokenConnection1 = Support.F28003x_bc
			break

		case 'F280015x':
			brokenConnection1 = Support.F280015x_bc
			break
	}

	if(multi_core.includes(device))
	{
		var myipInstance1 = ["CPU1CLK_domain", "CPU2CLK_domain", "CPU1_SYSCLK_domain", "CPU2_SYSCLK_domain"]
		var myipInstance2 = ["CPU1_SYSCLK", "CPU2_SYSCLK"]
	}
	else
	{
		var myipInstance1 = ["CPUCLK", "SYSCLK"]
		var myipInstance2 = ["SYSCLK"]
	}


	All_Instances = All_Instances.concat(FreqLabels)

	//Beta version: reasonableLayout is not used in beta version of clocktree tool
	//Purpose: Used for customized Layout. 
	const reasonableLayout = {
		"INTOSC1"			: { layer: 0, position: 1 },
		"INTOSC2"			: { layer: 0, position: 2 },
		"XTAL"				: { layer: 0, position: 3 },
		"OSCCLKSRCSEL"		: { layer: 1, position: 0 },
		"PLL_IMULT"			: { layer: 4, position: 1 },
		"PLL_FMULT"			: { layer: 4, position: 2 },
		"PLL_ADD"			: { layer: 5, position: 2 },
		"PLL_ODIV"			: { layer: 6, position: 2 },
		"PLL_Group"			: { layer: 3, position: 3 },
	};

	
		
	var tree = [
		{
			displayName: "Complete ClockTree",
			entries: [
				{
					displayName: "ClockTree",
					ipInstances: All_Instances,
					frequencyLabels: FreqLabels,
					brokenConnections: brokenConnection1,
				},
			],
		}, 
	]
	// checking the deviceData to see if the device has AUXPLL 
	var AUXPLLDevice = (system.deviceData.clockTree.ipInstances).filter(function(ipInst) {
		return ipInst.name === "AUXCLKDIVSEL";
	  });
	if(( AUXPLLDevice.length > 0)& (multi_core.includes(device))){
			tree = tree.concat ([
				{
					displayName: "PLLs",
					entries: [
						{
							displayName: "System PLL",
							ipInstances: ["CPU1_SYSCLK", "CPU2_SYSCLK"],
							frequencyLabels: FreqLabels,
							algorithm: "fanIn"
						},
						{
							displayName: "Auxillary PLL",
							ipInstances: ["AUXPLLCLK"],
							frequencyLabels: FreqLabels,
							algorithm: "fanIn"
						},
					],
				}
			])
	}
	else if (( AUXPLLDevice.length > 0)& (!(multi_core.includes(device)))) {
		tree = tree.concat ([
			{
				displayName: "PLLs",
				entries: [
					{
						displayName: "System PLL",
						ipInstances: ["SYSCLK"],
						frequencyLabels: FreqLabels,
						algorithm: "fanIn"
					},
					{
						displayName: "Auxillary PLL",
						ipInstances: ["AUXPLLCLK"],
						frequencyLabels: FreqLabels,
						algorithm: "fanIn"
					},
				],
			}
		])
	} 
		
	tree = tree.concat ([
		{
		displayName: "Clock domain view",
		entries: _.chain(system.deviceData.clockTree.ipInstances)
			.filter((ipInstance) => _.endsWith(ipInstance.name, "domain"))
			.map(defaultView)
			.value(),
		}
	]);

	const views = [
		{
			name: "/driverlib/clocktree/summaryView.xdt",
			displayName: "Clock Tree Summary",
			viewType: "markdown"
		}
	];

	exports = {
		// topModules: [{
		// 	displayName: "Modules",
		// 	modules: ["/modules/basic.js"],
		// }],
		displayName: "ClockTree Tool",
		clockTree: {
			typeMap,
			tree,
		},
		views,
		templates: [
			{
				name: "/driverlib/clocktree/clocktree.h.xdt",
		     	outputPath: "clocktree.h",
			 	alwaysRun: true,
			 	ignoreErrors: false 
			},
			]
	};
}
else if ("CPU2" === system.context) //"CPU2" === system.context
{
	exports = {
		displayName: "ClockTree Tool",
		templates: [
			{
				name: "/driverlib/clocktree/clocktree_cpu2.h.xdt",
		     	outputPath: "clocktree.h",
			 	alwaysRun: true,
			 	ignoreErrors: false 
			},
		]
	};
}