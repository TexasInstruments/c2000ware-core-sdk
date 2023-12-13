# CMake generated Testfile for 
# Source directory: C:/systemc-2.3.3/examples/sysc/rsa
# Build directory: C:/systemc-2.3.3/build/examples/sysc/rsa
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(examples/sysc/rsa/rsa "C:/Program Files/CMake/bin/cmake.exe" "-DTEST_EXE=C:/systemc-2.3.3/build/examples/sysc/rsa/rsa.exe" "-DTEST_DIR=C:/systemc-2.3.3/build/examples/sysc/rsa" "-DTEST_INPUT=" "-DTEST_GOLDEN=" "-DTEST_FILTER=" "-DDIFF_COMMAND=C:/Program Files/Git/usr/bin/diff.exe" "-DDIFF_OPTIONS=-u" "-P" "C:/systemc-2.3.3/cmake/run_test.cmake")
set_tests_properties(examples/sysc/rsa/rsa PROPERTIES  FAIL_REGULAR_EXPRESSION "^[*][*][*]ERROR")
