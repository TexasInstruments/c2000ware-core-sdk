# CMake generated Testfile for 
# Source directory: C:/systemc-2.3.3/examples/tlm/lt
# Build directory: C:/systemc-2.3.3/build/examples/tlm/lt
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(examples/tlm/lt/lt "C:/Program Files/CMake/bin/cmake.exe" "-DTEST_EXE=C:/systemc-2.3.3/build/examples/tlm/lt/lt.exe" "-DTEST_DIR=C:/systemc-2.3.3/build/examples/tlm/lt" "-DTEST_INPUT=" "-DTEST_GOLDEN=C:/systemc-2.3.3/examples/tlm/lt/results/expected.log" "-DTEST_FILTER=" "-DDIFF_COMMAND=C:/Program Files/Git/usr/bin/diff.exe" "-DDIFF_OPTIONS=-u" "-P" "C:/systemc-2.3.3/cmake/run_test.cmake")
set_tests_properties(examples/tlm/lt/lt PROPERTIES  FAIL_REGULAR_EXPRESSION "^[*][*][*]ERROR")
