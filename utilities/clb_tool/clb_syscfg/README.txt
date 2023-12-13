Linux System C Compiler (systemc_linux/makefile):
	The systemc_linux directory contains the basic structure for compiling the .d/.o files for Linux
		-Change filepaths of .cpp/.h files to be compiled (i.e. C2000WARE_ROOT)
			-Please note that absolute paths are required for C2000WARE_ROOT and SYSTEMC_INSTALL; there is a placeholder path used by default
		-Modify the makefile if there is a change to which files are being compiled (only add files to the list, do not remove)
		-Run sudo make (src folder should have all generated .d/.o files once complete)
Windows System C Compiler (systemc/SystemC_Compiler.cmd):
	- Change the file paths for CLB_SIM_COMPILER, C2000WARE_ROOT, and SYSTEMC_INSTALL
		CLB_SIM_COMPILER = TDM-GCC-64\bin directory
		C2000WARE_ROOT = clb_syscfg directory
		SYSTEMC_INSTALL = systemc-2.3.3 directory
	- Optionally change BuildDirectory if you do not want to overwrite existing .d/.o files
	- NOTE: Wherever this .cmd file is run will fill with text file outputs of any errors