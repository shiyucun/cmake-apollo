
add_executable(BaseUt)
target_sources(BaseUt
  PRIVATE
    atomic_hash_map_ut.cc
    atomic_rw_lock_ut.cc
    reentrant_rw_lock_ut.cc
    base_ut.cc
)
target_link_libraries(BaseUt
  PRIVATE
    ${UNIT_TEST_LIB}
)
target_include_directories(BaseUt
  PRIVATE
    ${CMAKE_SOURCE_DIR}
)

add_test(
    NAME BaseUt
    COMMAND $<TARGET_FILE:BaseUt>  # cmake 生成器表达式，获取目标文件路径
)
