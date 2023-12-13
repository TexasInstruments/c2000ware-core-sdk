# CMake generated Testfile for 
# Source directory: C:/systemc-2.3.3/examples/tlm/lt_mixed_endian
# Build directory: C:/systemc-2.3.3/build/examples/tlm/lt_mixed_endian
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(examples/tlm/lt_mixed_endian/lt_mixed_endian "C:/Program Files/CMake/bin/cmake.exe" "-DTEST_EXE=C:/systemc-2.3.3/build/examples/tlm/lt_mixed_endian/lt_mixed_endian.exe" "-DTEST_DIR=C:/systemc-2.3.3/build/examples/tlm/lt_mixed_endian" "-DTEST_INPUT=C:/systemc-2.3.3/examples/tlm/lt_mixed_endian/results/input.txt" "-DTEST_GOLDEN=C:/systemc-2.3.3/examples/tlm/lt_mixed_endian/results/expected.log" "-DTEST_FILTER=::" "-DDIFF_COMMAND=C:/Program Files/Git/usr/bin/diff.exe" "-DDIFF_OPTIONS=-u" "-P" "C:/systemc-2.3.3/cmake/run_test.cmake")
set_tests_properties(examples/tlm/lt_mixed_endian/lt_mixed_endian PROPERTIES  FAIL_REGULAR_EXPRESSION "^[*][*][*]ERROR")
