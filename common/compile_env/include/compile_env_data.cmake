
set(_PROGRAM_VERSION "Unknown")

if(EXISTS "${CMAKE_SOURCE_DIR}/VERSION")
  file(READ "${CMAKE_SOURCE_DIR}/VERSION" _PROGRAM_VERSION)
  string(STRIP "${_PROGRAM_VERSION}" _PROGRAM_VERSION)
endif()

set(_GIT_BRANCH "Unknown")
set(_GIT_HASH "Unknown")

find_package(Git QUIET)
if (Git_FOUND)
  execute_process(
    COMMAND
      ${GIT_EXECUTABLE} symbolic-ref --short -q HEAD
    OUTPUT_VARIABLE
      _GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )

  execute_process(
    COMMAND
      ${GIT_EXECUTABLE} describe --always --dirty
    OUTPUT_VARIABLE
      _GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )
endif()

foreach(key
  IN ITEMS
    HOSTNAME
    PROCESSOR_NAME
    PROCESSOR_DESCRIPTION
    OS_PLATFORM
    OS_NAME
    OS_RELEASE
    OS_VERSION)
  cmake_host_system_information(RESULT _${key} QUERY ${key})
endforeach()

# message(STATUS "PROGRAM_VERSION is ${_PROGRAM_VERSION}")
# message(STATUS "GIT_BRANCH is ${_GIT_BRANCH}")
# message(STATUS "GIT_HASH is ${_GIT_HASH}")

# message(STATUS "HOSTNAME is ${_HOSTNAME}")

# message(STATUS "PROCESSOR_NAME is ${_PROCESSOR_NAME}")
# message(STATUS "PROCESSOR_DESCRIPTION is ${_PROCESSOR_DESCRIPTION}")

# message(STATUS "OS_PLATFORM is ${_OS_PLATFORM}")
# message(STATUS "OS_NAME is ${_OS_NAME}")
# message(STATUS "OS_RELEASE is ${_OS_RELEASE}")
# message(STATUS "OS_VERSION is ${_OS_VERSION}")

configure_file(
  ${SRC_DIR}/include/compile_env_data.hpp.in
  ${TARGET_DIR}/include/compile_env_data.hpp
  @ONLY
)
