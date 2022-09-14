cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(cmake-apollo)


option(ENABLE_UNIT_TESTS "Enable unit tests" ON)

message(STATUS "ENABLE_UNIT_TESTS: ${ENABLE_UNIT_TESTS}")

add_subdirectory(common)

if (ENABLE_UNIT_TESTS)
  enable_testing()  # 由 ${CMAKE_CURRENT_SOURCE_DIR} 执行 ctest 运行所有单元测试例
  add_subdirectory(unittest)
endif()
