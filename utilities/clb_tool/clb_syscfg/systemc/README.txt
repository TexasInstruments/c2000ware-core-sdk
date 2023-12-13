CLB_Tool_SystemC_Compiler_Windows.cmd:
	- Change the file paths for CLB_SIM_COMPILER, C2000WARE_ROOT, and SYSTEMC_INSTALL
		CLB_SIM_COMPILER = TDM-GCC-64\bin directory
		C2000WARE_ROOT = clb_syscfg directory
		SYSTEMC_INSTALL = systemc-2.3.3 directory
	- Optionally change BuildDirectory if you do not want to overwrite existing .d/.o files
	- NOTE: Wherever this .cmd file is run will fill with text file outputs of any errors