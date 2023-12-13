# - Config file for the SystemCLanguage package
# It defines the following variables:
#  SystemC_TARGET_ARCH - Target architecture according to the Accellera SystemC conventions
#  SystemC_CXX_STANDARD - Preferred C++ standard
#  SystemC_CXX_STANDARD_REQUIRED - Determine whether the selected C++ standard is a requirement


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was SystemCLanguageConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

include(CMakeFindDependencyMacro)

# SystemC requires Pthreads under certain conditions
if (1)
  set (THREADS_PREFER_PTHREAD_FLAG ON)
  find_dependency (Threads)
  if (NOT CMAKE_USE_PTHREADS_INIT)
    message (SEND_ERROR "Failed to find the Pthreads library required to implement the SystemC coroutines and async_request_update() of primitive channels on Unix.")
  endif (NOT CMAKE_USE_PTHREADS_INIT)
endif (1)

include ("${CMAKE_CURRENT_LIST_DIR}/SystemCLanguageTargets.cmake")

set (SystemC_TARGET_ARCH mingw64)
set (SystemC_CXX_STANDARD 98)
set (SystemC_CXX_STANDARD_REQUIRED ON)
