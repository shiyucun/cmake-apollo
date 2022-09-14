
add_executable(CompileEnvUt)
target_sources(CompileEnvUt
  PRIVATE
    compile_env_ut.cc
)
target_link_libraries(CompileEnvUt
  PRIVATE
    CompileEnv
    ${UNIT_TEST_LIB}
)

add_test(
    NAME CompileEnvUt
    COMMAND $<TARGET_FILE:CompileEnvUt>  # cmake 生成器表达式，获取目标文件路径
)
