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

#include <TypeCollection/StaticTypeInfo.hpp>
#include <TypeExtraction.hpp>



// [INFO] NekiraReflect::TypeInfo定义在TypeCollection/StaticTypeInfo.hpp中
// [INFO] NekiraReflect::field_traits定义在TypeExtraction/TypeExtraction.hpp中

// 静态反射的起始宏
#ifndef STATIC_REFLECT_BEGIN
#define STATIC_REFLECT_BEGIN(Type)                                                                                     \
    template <>                                                                                                        \
    struct NekiraReflect::StaticTypeInfo<Type>                                                                         \
    {                                                                                                                  \
        static constexpr const char* Name = #Type;
#endif

// 注册函数，接收的参数包为包装后的field_traits<>
#ifndef STATIC_REFLECT_FUNCTIONS
#define STATIC_REFLECT_FUNCTIONS(...) static constexpr auto Functions = std::make_tuple(__VA_ARGS__);
#endif

// 用于将函数指针和函数名包装为field_traits
#ifndef STATIC_REGISTER_FUNCTION
#define STATIC_REGISTER_FUNCTION(FuncPtr, FuncName)                                                                    \
    NekiraReflect::field_traits                                                                                        \
    {                                                                                                                  \
        FuncPtr, #FuncName                                                                                             \
    }
#endif

// 注册变量，接收的参数包为包装后的field_traits<>
#ifndef STATIC_REFLECT_VARIABLES
#define STATIC_REFLECT_VARIABLES(...) static constexpr auto Variables = std::make_tuple(__VA_ARGS__);
#endif

// 用于将变量指针和变量名包装为field_traits
#ifndef STATIC_REGISTER_VARIABLE
#define STATIC_REGISTER_VARIABLE(VarPtr, VarName)                                                                      \
    NekiraReflect::field_traits                                                                                        \
    {                                                                                                                  \
        VarPtr, #VarName                                                                                               \
    }
#endif

// 静态反射的结束宏
#ifndef STATIC_REFLECT_END
#define STATIC_REFLECT_END()                                                                                           \
    }                                                                                                                  \
    ;                                                                                                                  \
    ;
#endif