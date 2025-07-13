/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#pragma once

#include "TypeRegist/TypeInfoRegistry.hpp"


 /** 动态反射
  *  TypeCollection/DynamicTypeInfo.hpp 定义了动态反射的信息存储类。
  *  主要实现了两类：EnumTypeInfo 和 ClassTypeInfo。
  *  同时，提供了CastDynamicTypeInfo方法，用于将 DynamicTypeInfo 转换为具体的子类。
  *
  *  TypeRegist/TypeInfoRegistry.hpp 提供了全局注册表TypeInfoRegistry，用于管理运行时类型信息。
  *  其中也包含了一些注册动态反射信息的辅助函数。
  *
  */
