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

#include <tuple>

namespace NekiraReflect
{

// 存储类型静态反射信息
template <typename T>
struct StaticTypeInfo
{
    // 类型名
    static constexpr const char* Name = "UnknownType";

    // 变量萃取元组
    static constexpr auto Variables = std::make_tuple();

    // 函数萃取元组
    static constexpr auto Functions = std::make_tuple();
};

// 获取特定的类型的静态反射信息（前提是该类型已注册静态反射）
template <typename T>
static constexpr auto GetStaticTypeInfo() -> StaticTypeInfo<T>
{
    return StaticTypeInfo<T>{};
}

// 获取成员函数指针
template <typename ClassType, std::size_t Index>
static constexpr auto GetMemberFunction()
{
    return std::get<Index>(StaticTypeInfo<ClassType>::Functions).FieldPointer;
}

// 获取成员变量指针
template <typename ClassType, std::size_t Index>
static constexpr auto GetMemberVariable()
{
    return std::get<Index>(StaticTypeInfo<ClassType>::Variables).FieldPointer;
}

} // namespace NekiraReflect