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

#include "FunctionTraits.hpp"
#include "VariableTraits.hpp"

namespace NekiraReflect
{

// 判断是否为函数类型
template <typename T>
constexpr bool IsFunction_v = std::is_function_v<std::remove_pointer_t<T>> || std::is_member_function_pointer_v<T>;

// 字段萃取器的公共参数
template <typename T>
struct field_traits_common
{
    static constexpr bool IsFunction = IsFunction_v<T>;
    static constexpr bool IsVariable = !IsFunction;
};

// 基础的字段萃取器
template <typename T, bool IsFunc = IsFunction_v<T>>
struct field_traits_base
{};

// 对于函数类型的特化
template <typename T>
struct field_traits_base<T, true> : function_traits<T>, field_traits_common<T>
{};

// 对于变量类型的特化
template <typename T>
struct field_traits_base<T, false> : variable_traits<T>, field_traits_common<T>
{};

// 字段萃取器
template <typename T>
    requires(std::is_member_pointer_v<T> || std::is_pointer_v<T>)
struct field_traits : field_traits_base<T>
{
    T           FieldPointer;
    const char* FieldName;

    constexpr field_traits(T pointer, const char* name) : FieldPointer(pointer), FieldName(name)
    {}

    explicit constexpr field_traits(T Pointer) : FieldPointer(Pointer), FieldName("")
    {}
};

} // namespace NekiraReflect