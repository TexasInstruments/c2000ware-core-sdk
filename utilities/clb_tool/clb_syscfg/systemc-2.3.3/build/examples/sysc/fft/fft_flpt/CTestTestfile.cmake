# CMake generated Testfile for 
# Source directory: C:/systemc-2.3.3/examples/sysc/fft/fft_flpt
# Build directory: C:/systemc-2.3.3/build/examples/sysc/fft/fft_flpt
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(examples/sysc/fft/fft_flpt/fft_flpt "C:/Program Files/CMake/bin/cmake.exe" "-DTEST_EXE=C:/systemc-2.3.3/build/examples/sysc/fft/fft_flpt/fft_flpt.exe" "-DTEST_DIR=C:/systemc-2.3.3/build/examples/sysc/fft/fft_flpt" "-DTEST_INPUT=" "-DTEST_GOLDEN=C:/systemc-2.3.3/examples/sysc/fft/fft_flpt/golden.log" "-DTEST_FILTER=" "-DDIFF_COMMAND=C:/Program Files/Git/usr/bin/diff.exe" "-DDIFF_OPTIONS=-u" "-P" "C:/systemc-2.3.3/cmake/run_test.cmake")
set_tests_properties(examples/sysc/fft/fft_flpt/fft_flpt PROPERTIES  FAIL_REGULAR_EXPRESSION "^[*][*][*]ERROR")
