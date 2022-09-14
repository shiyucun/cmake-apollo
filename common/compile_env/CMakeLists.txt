
add_library(CompileEnv OBJECT)
target_sources(CompileEnv
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/compile_env.cc
)
target_include_directories(CompileEnv
  PUBLIC
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}
)

add_executable(CompileEnvPrint)
target_sources(CompileEnvPrint
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/compile_env_print.cc
)
target_link_libraries(CompileEnvPrint
  PRIVATE
    CompileEnv
)

add_custom_command(
  OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/include/compile_env_data.hpp
  ALL
  COMMAND
    ${CMAKE_COMMAND}
      -D SRC_DIR=${CMAKE_CURRENT_SOURCE_DIR}
      -D TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR}
      -P ${CMAKE_CURRENT_SOURCE_DIR}/include/compile_env_data.cmake
  WORKING_DIRECTORY
    ${CMAKE_SOURCE_DIR}
)

add_custom_target(
  compile_env_generate
  ALL
  DEPENDS
    ${CMAKE_CURRENT_BINARY_DIR}/include/compile_env_data.hpp
)

add_dependencies(CompileEnv compile_env_generate)
add_dependencies(CompileEnvPrint compile_env_generate)
