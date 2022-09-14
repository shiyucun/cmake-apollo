/***
 * @Author       : shiyucun
 * @Date         : 2022-04-14 19:27:36
 * @LastEditors  : shiyucun
 * @LastEditTime : 2022-04-14 19:33:50
 * @Description  : 软件版本、编译时环境信息打印接口
 */

#include "common/compile_env/include/compile_env.hpp"

namespace JustFollow {
namespace Common {
namespace CompileEnv {

std::string GetProgramVersion() { return PROGRAM_VERSION; }

std::string GetCompileTime() { return std::string(__DATE__) + " " + std::string(__TIME__); }

std::string GetCompileEnvHostname() { return HOSTNAME; }

std::string GetCompileEnvGitInfo() { return GIT_BRANCH + "-" + GIT_HASH; }

std::string GetCompileEnvProcessorInfo() { return PROCESSOR_NAME + "; " + PROCESSOR_DESCRIPTION; }

std::string GetCompileEnvOsInfo() {
  return OS_NAME + "; " + OS_PLATFORM + "; " + OS_RELEASE + "; " + OS_VERSION;
}

}  // namespace CompileEnv
}  // namespace Common
}  // namespace JustFollow
