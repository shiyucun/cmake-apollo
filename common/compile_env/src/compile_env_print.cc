/***
 * @Author       : shiyucun
 * @Date         : 2022-04-18 15:36:08
 * @LastEditors  : shiyucun
 * @LastEditTime : 2022-04-21 13:43:26
 * @Description  : 打印版本信息、编译环境信息
 */

#include "common/compile_env/include/compile_env.hpp"

#include <iostream>

int main(int argc, char* argv[], char* envp[]) {
  std::string program_version = JustFollow::Common::CompileEnv::GetProgramVersion();
  printf("program version: %s\n", program_version.c_str());

  std::string compile_time = JustFollow::Common::CompileEnv::GetCompileTime();
  printf("compile time: %s\n", compile_time.c_str());

  std::string hostname = JustFollow::Common::CompileEnv::GetCompileEnvHostname();
  printf("compile hostname: %s\n", hostname.c_str());

  std::string git_info = JustFollow::Common::CompileEnv::GetCompileEnvGitInfo();
  printf("compile git info: %s\n", git_info.c_str());

  std::string processor_info = JustFollow::Common::CompileEnv::GetCompileEnvProcessorInfo();
  printf("compile processor info: %s\n", processor_info.c_str());

  std::string os_info = JustFollow::Common::CompileEnv::GetCompileEnvOsInfo();
  printf("compile os info: %s\n", os_info.c_str());

  return 0;
}
