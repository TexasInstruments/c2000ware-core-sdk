# CMake generated Testfile for 
# Source directory: C:/systemc-2.3.3/examples/sysc/2.1/reset_signal_is
# Build directory: C:/systemc-2.3.3/build/examples/sysc/2.1/reset_signal_is
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(examples/sysc/2.1/reset_signal_is/reset_signal_is "C:/Program Files/CMake/bin/cmake.exe" "-DTEST_EXE=C:/systemc-2.3.3/build/examples/sysc/2.1/reset_signal_is/reset_signal_is.exe" "-DTEST_DIR=C:/systemc-2.3.3/build/examples/sysc/2.1/reset_signal_is" "-DTEST_INPUT=" "-DTEST_GOLDEN=C:/systemc-2.3.3/examples/sysc/2.1/reset_signal_is/golden.log" "-DTEST_FILTER=" "-DDIFF_COMMAND=C:/Program Files/Git/usr/bin/diff.exe" "-DDIFF_OPTIONS=-u" "-P" "C:/systemc-2.3.3/cmake/run_test.cmake")
set_tests_properties(examples/sysc/2.1/reset_signal_is/reset_signal_is PROPERTIES  FAIL_REGULAR_EXPRESSION "^[*][*][*]ERROR")
