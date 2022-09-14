
include(FetchContent)


set(FETCHCONTENT_BASE_DIR ${DEPS_DIR}/gflags)
FetchContent_Declare(
  gflags
  GIT_REPOSITORY https://gitee.com/mirrors/gflags.git
  GIT_TAG 986e8ee
)
FetchContent_GetProperties(gflags)

if(NOT gflags_POPULATED)
  FetchContent_Populate(gflags)
endif()

# add_subdirectory(
#   ${gflags_SOURCE_DIR}
#   ${gflags_BINARY_DIR}
# )


set(FETCHCONTENT_BASE_DIR ${DEPS_DIR}/gtest)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://gitee.com/mirrors/googletest.git
  GIT_TAG release-1.11.0
)
FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
endif()

# add_subdirectory(
#   ${googletest_SOURCE_DIR}
#   ${googletest_BINARY_DIR}
# )


set(FETCHCONTENT_BASE_DIR ${DEPS_DIR}/glog)
FetchContent_Declare(
  glog
  GIT_REPOSITORY https://gitee.com/mirrors/glog.git
  GIT_TAG v0.6.0-rc2
)
FetchContent_GetProperties(glog)

if(NOT glog_POPULATED)
  FetchContent_Populate(glog)
endif()

# add_subdirectory(
#   ${glog_SOURCE_DIR}
#   ${glog_BINARY_DIR}
# )
