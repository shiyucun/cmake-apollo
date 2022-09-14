/***
 * @Author       : shiyucun
 * @Date         : 2022-04-18 15:26:22
 * @LastEditors  : shiyucun
 * @LastEditTime : 2022-04-18 16:13:20
 * @Description  : 软件版本、编译时环境信息打印接口
 */

#pragma once

#include "common/compile_env/include/compile_env_data.hpp"

namespace JustFollow {
namespace Common {
namespace CompileEnv {

/***
 * @description: 获取软件版本号
 * @param {*}
 * @return {std::string} 软件版本号
 */
std::string GetProgramVersion();

/***
 * @description: 获取软件编译时间
 * @param {*}
 * @return {std::string} 软件编译时间，例如：Apr 21 2022 20:11:26
 */
std::string GetCompileTime();

/***
 * @description: 获取编译时主机名，使用docker时，建议设置docker的hostname格式为[宿主机名-docker]
 * @param {*}
 * @return {std::string} 编译时主机名，例如：hostname-docker 或 hostname
 */
std::string GetCompileEnvHostname();

/***
 * @description: 获取编译时git环境信息
 * @param {*}
 * @return {std::string} 编译时git环境信息
 *  例如：master-168429b[-dirty]
 *       Git Branch：master
 *       Git Commint ID：168429b
 *       是否有未提交的信息：显示dirty时表示自Commint ID后有未提交的修改
 */
std::string GetCompileEnvGitInfo();

/***
 * @description: 获取编译使用的CPU相关的信息
 * @param {*}
 * @return {std::string} 编译使用的CPU相关的信息
 *  例如：Unknown P6 family; 8 core Intel(R) Core(TM) i7-10700 CPU @ 2.90GHz
 *       处理器名字：Unknown P6 family
 *       处理器描述信息：8 core Intel(R) Core(TM) i7-10700 CPU @ 2.90GHz
 */
std::string GetCompileEnvProcessorInfo();

/***
 * @description: 获取编译时操作系统相关信息
 * @param {*}
 * @return {std::string} 编译时操作系统相关信息
 *  例如：Linux; x86_64; 5.8.0-43-generic; #49~20.04.1-Ubuntu SMP Fri Feb 5 09:57:56 UTC 2021
 *       操作系统名：Linux
 *       编译硬件平台：x86_64
 *       内核版本号：5.8.0-43-generic
 *       操作系统版号：#49~20.04.1-Ubuntu SMP Fri Feb 5 09:57:56 UTC 2021
 */
std::string GetCompileEnvOsInfo();

}  // namespace CompileEnv
}  // namespace Common
}  // namespace JustFollow
