/*** 
 * @Author       : shiyucun
 * @Date         : 2022-05-03 13:03:59
 * @LastEditors  : shiyucun
 * @LastEditTime : 2022-05-03 13:08:32
 * @Description  : common/base 目录代码单元测试入口
 */

#include "gtest/gtest.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}