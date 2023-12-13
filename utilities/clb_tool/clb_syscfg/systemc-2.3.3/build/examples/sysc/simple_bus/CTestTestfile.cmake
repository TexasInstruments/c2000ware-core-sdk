# CMake generated Testfile for 
# Source directory: C:/systemc-2.3.3/examples/sysc/simple_bus
# Build directory: C:/systemc-2.3.3/build/examples/sysc/simple_bus
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(examples/sysc/simple_bus/simple_bus "C:/Program Files/CMake/bin/cmake.exe" "-DTEST_EXE=C:/systemc-2.3.3/build/examples/sysc/simple_bus/simple_bus.exe" "-DTEST_DIR=C:/systemc-2.3.3/build/examples/sysc/simple_bus" "-DTEST_INPUT=" "-DTEST_GOLDEN=C:/systemc-2.3.3/examples/sysc/simple_bus/golden.log" "-DTEST_FILTER=" "-DDIFF_COMMAND=C:/Program Files/Git/usr/bin/diff.exe" "-DDIFF_OPTIONS=-u" "-P" "C:/systemc-2.3.3/cmake/run_test.cmake")
set_tests_properties(examples/sysc/simple_bus/simple_bus PROPERTIES  FAIL_REGULAR_EXPRESSION "^[*][*][*]ERROR")
