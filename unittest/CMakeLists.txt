cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(unittest LANGUAGES CXX)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
set(UNIT_TEST_LIB ${GTEST_LIBRARIES} pthread)

FILE(GLOB _sub_dirs RELAVIVE ${CMAKE_CURRENT_SOURCE_DIR}/*)
foreach(_sub_dir ${_sub_dirs})
  if (IS_DIRECTORY ${_sub_dir})
    add_subdirectory(${_sub_dir})
  endif()
endforeach()
