# CMake generated Testfile for 
# Source directory: C:/systemc-2.3.3/examples/sysc/pkt_switch
# Build directory: C:/systemc-2.3.3/build/examples/sysc/pkt_switch
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(examples/sysc/pkt_switch/pkt_switch "C:/Program Files/CMake/bin/cmake.exe" "-DTEST_EXE=C:/systemc-2.3.3/build/examples/sysc/pkt_switch/pkt_switch.exe" "-DTEST_DIR=C:/systemc-2.3.3/build/examples/sysc/pkt_switch" "-DTEST_INPUT=" "-DTEST_GOLDEN=" "-DTEST_FILTER=" "-DDIFF_COMMAND=C:/Program Files/Git/usr/bin/diff.exe" "-DDIFF_OPTIONS=-u" "-P" "C:/systemc-2.3.3/cmake/run_test.cmake")
set_tests_properties(examples/sysc/pkt_switch/pkt_switch PROPERTIES  FAIL_REGULAR_EXPRESSION "^[*][*][*]ERROR")
