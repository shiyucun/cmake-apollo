/***
 * @Author       : shiyucun
 * @Date         : 2022-04-20 17:33:31
 * @LastEditors  : shiyucun
 * @LastEditTime : 2022-04-20 17:33:32
 * @Description  : 通用宏定义
 */

#pragma once

#define DISALLOW_COPY_AND_ASSIGN(classname) \
  classname(const classname &) = delete;    \
  classname &operator=(const classname &) = delete;
