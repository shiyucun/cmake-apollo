
FILE(GLOB _sub_dirs RELAVIVE ${CMAKE_CURRENT_SOURCE_DIR}/*)
foreach(_sub_dir ${_sub_dirs})
  if (IS_DIRECTORY ${_sub_dir})
    add_subdirectory(${_sub_dir})
  endif()
endforeach()
