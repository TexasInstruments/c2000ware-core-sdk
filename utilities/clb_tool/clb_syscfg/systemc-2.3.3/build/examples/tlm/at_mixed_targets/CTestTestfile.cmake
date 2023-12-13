# CMake generated Testfile for 
# Source directory: C:/systemc-2.3.3/examples/tlm/at_mixed_targets
# Build directory: C:/systemc-2.3.3/build/examples/tlm/at_mixed_targets
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(examples/tlm/at_mixed_targets/at_mixed_targets "C:/Program Files/CMake/bin/cmake.exe" "-DTEST_EXE=C:/systemc-2.3.3/build/examples/tlm/at_mixed_targets/at_mixed_targets.exe" "-DTEST_DIR=C:/systemc-2.3.3/build/examples/tlm/at_mixed_targets" "-DTEST_INPUT=" "-DTEST_GOLDEN=C:/systemc-2.3.3/examples/tlm/at_mixed_targets/results/expected.log" "-DTEST_FILTER=" "-DDIFF_COMMAND=C:/Program Files/Git/usr/bin/diff.exe" "-DDIFF_OPTIONS=-u" "-P" "C:/systemc-2.3.3/cmake/run_test.cmake")
set_tests_properties(examples/tlm/at_mixed_targets/at_mixed_targets PROPERTIES  FAIL_REGULAR_EXPRESSION "^[*][*][*]ERROR")
