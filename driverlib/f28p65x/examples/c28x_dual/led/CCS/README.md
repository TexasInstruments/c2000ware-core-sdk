***Manual configuration of postBuildStep***
***(Applicable only for FLASH and FLASH_LAUNCHXL configs)***

1. Right-click on multi folder and select the desired Build Configuration.
2. Open the .sysconfig file in the cpu1 project folder and set CPU2 boot mode to Boot from Flash Bank 3, then save the file.
3. Right-click the sysconfig_multi project and select Build Projects.
4. Now, manually enter the following command as a postBuildStep under right-click CPU2 → Properties → Build → Steps → Post-build step and save it. The command is:

${CG_TOOL_ROOT}/bin/hex2000.exe --memwidth=16 --romwidth=16 -ii --map="..\..\combined.map" "..\..\led_ex2_blinky_sysconfig_cpu1\ $build_config_name\led_ex2_blinky_sysconfig_cpu1.out" "..\..\led_ex2_blinky_sysconfig_cpu2\ $build_config_name\led_ex2_blinky_sysconfig_cpu2.out" -o "..\..\combined.hex".

5. Open the. ccxml file in the cpu1 targetConfigs folder and click Start Project-less Debug.”
6. Now right-click on CPU1 and CPU2 to connect target.
7. Right-click on CPU1 -> Flash settings -> Scroll down to Flash Bank Map Settings -> Make sure all are set to 0 (we are loading the entire data from CPU1 itself, so it needs access to all banks)
8. Scroll down further to check select on Entire flash under Erase settings.
9. Scroll up to click Configure Clock and then, Save and Close.
10. Now click on Run -> Load program -> Browse -> combined.hex
11. Open View → Memory Browser and verify that data has been loaded correctly at 0x80000 for CPU1 and 0xE0000 for CPU2.
12. Click Run on both CPU1 and CPU2 to start execution, then verify the output using Launchpad LEDs or the Output Console.
