# CMake generated Testfile for 
# Source directory: C:/systemc-2.3.3/examples/tlm/at_2_phase
# Build directory: C:/systemc-2.3.3/build/examples/tlm/at_2_phase
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(examples/tlm/at_2_phase/at_2_phase "C:/Program Files/CMake/bin/cmake.exe" "-DTEST_EXE=C:/systemc-2.3.3/build/examples/tlm/at_2_phase/at_2_phase.exe" "-DTEST_DIR=C:/systemc-2.3.3/build/examples/tlm/at_2_phase" "-DTEST_INPUT=" "-DTEST_GOLDEN=C:/systemc-2.3.3/examples/tlm/at_2_phase/results/expected.log" "-DTEST_FILTER=" "-DDIFF_COMMAND=C:/Program Files/Git/usr/bin/diff.exe" "-DDIFF_OPTIONS=-u" "-P" "C:/systemc-2.3.3/cmake/run_test.cmake")
set_tests_properties(examples/tlm/at_2_phase/at_2_phase PROPERTIES  FAIL_REGULAR_EXPRESSION "^[*][*][*]ERROR")
