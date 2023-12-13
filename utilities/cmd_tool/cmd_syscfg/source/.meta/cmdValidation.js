"use strict";
/*global exports, system*/
let meminfo   = system.getScript("/utilities/cmd_tool/cmd_syscfg/source/" + system.deviceData.device.toLowerCase() + "_memoryInfo.js");
let CMDCommon = system.getScript("/utilities/cmd_tool/cmd_syscfg/source/CMDCommon.js");
let Common   = system.getScript("/driverlib/Common.js");

var validation_warning = "warning"
var validation_error = "error"
var validation_info = "info"

var AllDevices = [
	"F2807x",
	"F2837xS",
	"F2837xD",
	"F28004x",
	"F28002x",
	"F28003x",
	"F280013x",
	"F280015x",
	"F2838x",
	"F28P65x",
	"F28P55x"
]


function sectionValidationError(validation, section, option, message)
{
	if(section.type == "compiler")
		validation.logError(message, section.inst, option + "_" + section.name)
	else
		validation.logError(message, section.inst, option)
}
function sectionValidationWarning(validation, section, option, message)
{
	if(section.type == "compiler")
		validation.logWarning(message, section.inst, option + "_" + section.name)
	else
		validation.logWarning(message, section.inst, option)
}
function sectionValidationInfo(validation, section, option, message)
{
	if(section.type == "compiler")
		validation.logInfo(message, section.inst, option + "_" + section.name)
	else
		validation.logInfo(message, section.inst, option)
}

var cmdValidation = [
	{
		id   : "ID_0000",
		type : validation_error,
		name :  "Device memory range in multiple memory range combinations",
		func : (inst, validation, name) => {
			//
		    // Check for multiple combos using the same device memomry range
		    //
		    for (var memGroup of CMDCommon.getDeviceCombinableMemoryRangeGroups())
		    {
		        for (var memCombo of inst[memGroup + "memoryCombination"])
		        {
		            for (var memComboCheckAgainst of inst[memGroup + "memoryCombination"])
		            {
		                if (memCombo.$name != memComboCheckAgainst.$name)
		                {
		                    for (var usedRanges of memCombo.combination)
		                    {
		                        if (memComboCheckAgainst.combination.includes(usedRanges))
		                        {
		                            validation.logError(
		                                "Multiple combination ranges use the same device memory range " + usedRanges + ". This range is also used by: "+ memComboCheckAgainst.$name +
		                                ".",
		                                memCombo, "combination");
		                        }
		                    }
		                }
		            }
		        }
		    }
		},
		devices :AllDevices
	},
	{
		id   : "ID_0001",
		type : validation_error,
		name :  "Check if the memories selected in a combination is continuous and is owned by same owner",
		func : (inst, validation, name) => {
			for (var memGroup of CMDCommon.getDeviceCombinableMemoryRangeGroups())
		    {
				for (var memCombo of inst[memGroup + "memoryCombination"])
				{
					var nextOrigin = undefined
					var memOwner = undefined
					for (var m of CMDCommon.getDeviceMemoryRangeInGroup(memGroup))
					{
						if(memCombo.combination.includes(m.name))
						{
							// Check for address continuity
							if((nextOrigin != undefined) && (m.origin != nextOrigin))
								validation.logError("Memories selected in a combination should be continuous.", memCombo, "combination");
							nextOrigin = m.origin + m.length

							// Check if all RAMs have the same owner
							var memConfig = m.name.startsWith("RAMLS") ? CMDCommon.getLSConfig(m.name) :
										    m.name.startsWith("RAMGS") ? CMDCommon.getGSConfig(m.name) : undefined
							if((memOwner != undefined) && (memConfig != memOwner))
								validation.logError("Memories selected in a combination should be have the same Memcfg configuration.", memCombo, "combination");
							memOwner = memConfig
						}
					}
				}
		    }
		},
		devices :AllDevices
	},
	{
		id   : "ID_0002",
		type : validation_error,
		name :  "Sections allocation checks",
		func : (inst, validation, name) => {
			var MemGroup  = {}
			var MemConfig = {}
			for (var mem of CMDCommon.getMemoryRangesInDetail(inst))
			{
				MemGroup[mem.name] = mem.group
				MemConfig[mem.name] = mem.config
			}

			for (var section of CMDCommon.getSectionsInDetail(inst))
		    {
				// ID_0002
				// Check name :  "Sections that cannot be split : cinit, init_array, stack, binit, ovly, section that has a START(), END(), or SIZE()",
				if ((section.sectionMemory.length > 1) || (section.sectionRun.length > 1))
				{
					if(["cinit", "init_array", "pinit", "stack","binit", "ovly"].includes(section.name))
					{
						var message = section.name + " cannot be split. If a single memory block is not large enough to fit the section, consider combining multiple memory blocks to form larger blocks (Memory Tab)"

						sectionValidationError(validation, section, "sectionMemory", message)
					}
					if(section.sectionSymbols && section.sectionSymbols.length > 0)
					{
						var message = "Sections that has a START(), END(), OR SIZE() operator applied to it cannot be split. If a single memory block is not large enough to fit the section, consider combining multiple memory blocks to form larger blocks (Memory Tab)"

						if(section.sectionMemory.length > 1)
							sectionValidationError(validation, section, "sectionMemory", message);
						if(section.sectionRun.length > 1)
							sectionValidationError(validation, section, "sectionRun", message);
					}
				}


				// ID_0003
				// Check name :  "Sections that cannot be allocated to Flash",
				if(["data", "bss", "sysmem"].includes(section.name))
				{
					for(var i of section.sectionMemory)
					{
						if(MemGroup[i] == "FLASH")
							sectionValidationError(validation, section, "sectionMemory", section.name + " should not be allocated to Flash");
					}
				}
				if(section.sectionRunFromDifferentAddr)
				{
					for(var i of section.sectionRun)
					{
						if(MemGroup[i] == "FLASH")
							sectionValidationError(validation, section, "sectionRun", "Run location should not be allocated to Flash");
					}
				}


				// ID_0004
				// Check name :  "While using Run from different location, Load address should be in Flash",
				if(section.sectionRunFromDifferentAddr)
				{
					for(var i of section.sectionMemory)
					{
						if(MemGroup[i] != "FLASH")
						sectionValidationWarning(validation, section, "sectionRun", "While using Run from different location, Load address should be in Flash");
					}
				}


				// ID_0005
				// Check name :  "Alignment should be power of 2",
				if(section.sectionAlignEnable && !CMDCommon.isPowerOf2(section.sectionAlign))
				{
					sectionValidationError(validation, section, "sectionAlign", "Alignment should be power of 2");
				}


				// ID_0006
				// Check name :  "Flash sectors must be  aligned to atleast a value of 8",
				for(var i of section.sectionMemory)
				{
					if(MemGroup[i] == "FLASH")
					{
						if (!section.sectionAlignEnable)
							sectionValidationError(validation, section, "sectionAlignEnable", "Flash sectors must be aligned to atleast a value of 8 (i.e., 8 * 16-bit boundary)");
						else if(section.sectionAlign < 8)
							sectionValidationError(validation, section, "sectionAlign", "Flash sectors must be aligned to atleast a value of 8 (i.e., 8 * 16-bit boundary)");
					}
				}


				// ID_0007
				// Check name : CLA sections should use LS memories only
				var sectionList = section.sectionRunFromDifferentAddr ? section.sectionRun : section.sectionMemory
				var sectionName = section.sectionRunFromDifferentAddr ? "sectionRun" : "sectionMemory"
				if(["cla1Prog", "claConst", "claScratchpad", "bssCla"].includes(section.name))
				{
					for(var i of sectionList)
					{
						if(MemGroup[i] != "RAMLS")
							sectionValidationError(validation, section, sectionName, "CLA can only access LS Memories");
						else
						{
							var memConfig = MemConfig[i]
							if ((section.name == "cla1Prog") && (memConfig != "CLA_prog"))
								sectionValidationError(validation, section, sectionName, i + " is not configured as CLA program memory in Memcfg module");
							if ((section.name != "cla1Prog") && (memConfig != "CLA_data"))
								sectionValidationError(validation, section, sectionName, i + " is not configured as CLA data memory in Memcfg module");
						}
					}
				}
				else if(["cla1ToCpuMsgRAM", "cpuToCla1MsgRAM"].includes(section.name))
				{
					for(var i of sectionList)
					{
						var memConfig = MemConfig[i]
						if (memConfig == undefined)
							sectionValidationWarning(validation, section, sectionName, "Memcfg module must be enabled for complete error checking.");
						if (memConfig == false)
							sectionValidationError(validation, section, sectionName, i + " is not initialized in Memcfg module");
					}
				}
				else if(section.type == "compiler")
				{
					for(var i of sectionList)
					{
						if(MemGroup[i] == "RAMLS")
						{
							var memConfig = MemConfig[i]
							if((memConfig == "CLA_prog") || (memConfig == "CLA_data"))
								sectionValidationError(validation, section, sectionName, i + " is configured as CLA memory in Memcfg module");
						}
					}
				}


				// ID_0008
				// Check name :  "Memory used in combination cannot be assigned to a section. Use the combined memory name instead",
				if(!["codestart"].includes(section.name))
				{
					const currentOptions = CMDCommon.getMemoryRanges(inst);
					var currentOptionNames = currentOptions.map((opt) => {return opt.name})
					for (var secMem of section.sectionMemory)
					{
						if (!currentOptionNames.includes(secMem))
						{
							sectionValidationError(validation, section, "sectionMemory", name + ". " + secMem + ": is no longer available");
						}
					}
				}
			}
		},
		devices :AllDevices
	},
	{
		id   : "ID_0009",
		type : validation_error,
		name :  "Stack should be stack should be allocated only to lower 64k address",
		func : (inst, validation, name) => {
			var ranges = CMDCommon.getMemoryRangesInDetail(inst)

			if (inst["sectionMemory_stack"].length != 0)
			{
				for(var i of ranges)
				{
					if ((i.name == inst["sectionMemory_stack"][0]) && (i.origin >= 0x10000))
					{
						validation.logError("Stack should be allocated only to lower 64k address", inst, "sectionMemory_stack");
					}
				}
			}
		},
		devices :AllDevices
	},
	{
		id   : "ID_0010",
		type : validation_error,
		name :  "GSRAM should only be used by the owner configured by CPU1 memcfg",
		func : (inst, validation, name) => {
			var MemGroup  = {}
			var MemConfig = {}
			for (var mem of CMDCommon.getMemoryRangesInDetail(inst))
			{
				MemGroup[mem.name] = mem.group
				MemConfig[mem.name] = mem.config
			}
			for (var section of CMDCommon.getSectionsInDetail(inst))
		    {
				var sectionList = section.sectionRunFromDifferentAddr ? section.sectionRun : section.sectionMemory
				var sectionName = section.sectionRunFromDifferentAddr ? "sectionRun" : "sectionMemory"
				if (Common.isMultiCoreSysConfig() || (Common.isMultiCoreDevice() && Common.isContextCPU1()))
				{
					var contextNames = Common.getContextNames();
					var context1 = null;
					var context2 = null;
					for (var cntx of contextNames) 
					{
						if (cntx.slice(-1) == "1")       // Look for CPU1 Context 
						{
						context1 = cntx;
						}	
			
						if (cntx.slice(-1) == "2")       // Look for CPU2 Context 
						{
						context2 = cntx;
						}	
					}
					var CPU1_mod = Common.getModuleForCore("/driverlib/memcfg.js", context1);   // get module from core 1
					if (CPU1_mod != null)
					{
						var stat_1 = CPU1_mod.$static;
					}
					
					if (!["cla1Prog", "claConst", "claScratchpad", "bssCla"].includes(section.name)){
						for(var i of sectionList)
						{
							var stat_filt = null;
							if(stat_1)
							{
								if (i.includes("FLASH")){
									var varName = "config_SYSCTL_FLASH_" + i.replace("FLASH_", "")
								}
								else {
									var varName = "config_MEMCFG_SECT_" + i.replace("RAM", "")
								}
								if (stat_1[varName])
								{
									stat_filt = stat_1[varName]
								} else {
									stat_filt = null;
								}
							}
							if(MemGroup[i] == ("RAMGS"))
							{
								if (Common.isContextCPU1())
								{
									if (MemConfig[i]){
										if ((MemConfig[i] != "MEMCFG_GSRAMCONTROLLER_CPU1")){
											sectionValidationWarning(validation, section, sectionName, i + " is not configured to be owned by CPU1 in " + system.getReference(stat_1, varName) + ". CPU1 will only have read access to this memory.");
										}
									}
									else {
										sectionValidationWarning(validation, section, sectionName, "The memcfg module is needed on CPU1 to assign GSRAM.");
									}
								}
								else if (Common.isContextCPU2())
								{
									if (MemConfig[i]){
										if ((MemConfig[i] != "MEMCFG_GSRAMCONTROLLER_CPU2")){
											sectionValidationWarning(validation, section, sectionName, i + " is not configured to be owned by CPU2 in " + system.getReference(stat_1, varName) + ". CPU2 will only have read access to this memory.");
										}
									}
									else {
										sectionValidationWarning(validation, section, sectionName, "The memcfg module is needed on CPU1 to assign GSRAM to CPU2.");
									}
								}
							}
							if(MemGroup[i] == ("FLASH"))
							{
								if (Common.isContextCPU1())
								{
									if (stat_filt){
										if ((stat_filt != "SYSCTL_CPUSEL_CPU1")){
											sectionValidationWarning(validation, section, sectionName, i + " is not configured to be owned by CPU1 in " + system.getReference(stat_1, varName) + ". CPU1 will only have read access to this memory.");
										}
									}
									else if(["F28P65x"].includes(system.deviceData.deviceId)){  // only gattino has global flash, stat_filt will be undefined on other devices
										sectionValidationWarning(validation, section, sectionName, "The memcfg module is needed on CPU1 to assign FLASH.");
									}
								}
								else if (Common.isContextCPU2())
								{
									if (stat_filt){
										if ((stat_filt != "SYSCTL_CPUSEL_CPU2")){
											sectionValidationWarning(validation, section, sectionName, i + " is not configured to be owned by CPU2 in " + system.getReference(stat_1, varName) + ". CPU2 will only have read access to this memory.");
										}
									}
									else if(["F28P65x"].includes(system.deviceData.deviceId)){  // only gattino has global flash, stat_filt will be undefined on other devices
										sectionValidationWarning(validation, section, sectionName, "The memcfg module is needed on CPU1 to assign FLASH to CPU2.");
									}
								}
							}
							
						}
					}
				}
				else if (Common.isContextCPU2()){
					if (!["cla1Prog", "claConst", "claScratchpad", "bssCla"].includes(section.name)){
						for(var i of sectionList)
						{
							if(MemGroup[i] == "RAMGS")
							{
								sectionValidationWarning(validation, section, sectionName, "Error checking is limited for single core SysConfig on a multicore device. Unless CPU1 memcfg assigns this GSRAM to CPU2, CPU2 will only have read access.");
							}
						}
					}
				}
			}
		},
		devices :AllDevices
	},



]

exports = {
	validation_error : validation_error,
	validation_warning : validation_warning,
	validation_info : validation_info,
	cmdValidation : cmdValidation,
}