/***
 * @Author       : shiyucun
 * @Date         : 2022-04-21 10:59:08
 * @LastEditors  : shiyucun
 * @LastEditTime : 2022-04-21 18:02:28
 * @Description  : 软件版本、编译时环境信息打印接口单元测试
 */

#include "common/compile_env/include/compile_env.hpp"

#include "gtest/gtest.h"

namespace JustFollow {
namespace Common {
namespace CompileEnv {

TEST(CompileEnvUt, program_version) {
  std::string program_version = GetProgramVersion();
  ASSERT_FALSE(program_version.empty());
}

TEST(CompileEnvUt, compile_time) {
  std::string compile_time = GetCompileTime();
  ASSERT_FALSE(compile_time.empty());
}

TEST(CompileEnvUt, hostname) {
  std::string hostname = GetCompileEnvHostname();
  ASSERT_FALSE(hostname.empty());
}

TEST(CompileEnvUt, git_info) {
  std::string git_info = GetCompileEnvGitInfo();
  ASSERT_FALSE(git_info.empty());
}

TEST(CompileEnvUt, processor_info) {
  std::string processor_info = GetCompileEnvProcessorInfo();
  ASSERT_FALSE(processor_info.empty());
}

TEST(CompileEnvUt, os_info) {
  std::string os_info = GetCompileEnvOsInfo();
  ASSERT_FALSE(os_info.empty());
}

}  // namespace CompileEnv
}  // namespace Common
}  // namespace JustFollow

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
