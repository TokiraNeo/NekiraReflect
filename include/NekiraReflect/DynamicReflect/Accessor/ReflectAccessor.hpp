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

#include <Utility/Utilities.hpp>

namespace NekiraReflect
{
    // 反射友元访问器
    template <typename ClassType>
    class ReflectionAccessor
    {
    public:
        static void RegisterReflection()
        {
            // 特化类必须重写该方法以注册反射信息
        }    
    };
}

// 定义类的反射访问器特化
#ifndef NEKIRA_REFLECT_ACCESSOR_BEGIN
#define NEKIRA_REFLECT_ACCESSOR_BEGIN(ClassName) \
namespace NekiraReflect \
{\
    template<> \
    class ReflectionAccessor<ClassName> \
    {\
    public:\
        using ClassType = ClassName;\
        static void RegisterReflection() \
        {\
            auto classInfo = MakeClassTypeInfo<ClassType>(#ClassName);
#endif

// 通过反射访问器注册成员变量
#ifndef NEKIRA_REFLECT_ACCESSOR_VAR
#define NEKIRA_REFLECT_ACCESSOR_VAR(VarName) \
            classInfo -> AddVariable( MakeMemberVarInfo( #VarName, &ClassType::VarName ) );
#endif 

// 通过反射访问器注册成员函数
#ifndef NEKIRA_REFLECT_ACCESSOR_FUNC
#define NEKIRA_REFLECT_ACCESSOR_FUNC(FuncName) \
            classInfo -> AddFunction( MakeMemberFuncInfo( #FuncName, &ClassType::FuncName ) );
#endif

// 结束反射访问器的定义
#ifndef NEKIRA_REFLECT_ACCESSOR_END
#define NEKIRA_REFLECT_ACCESSOR_END() \
            RegisterClassInfo( std::move(classInfo) ); \
        } \
    } \
}            
#endif

// 自动注册反射信息
#ifndef NEKIRA_REFLECT_REGISTER_AUTO
#define NEKIRA_REFLECT_REGISTER_AUTO(ClassName) \
namespace NekiraReflect_Inside \
{\
    struct ClassName##_AutoRegister \
    {\
        ClassName##_AutoRegister() \
        { \
            ReflectionAccessor<ClassName>::RegisterReflection(); \
        } \
    }; \
    static ClassName##_AutoRegister ClassName##_AutoRegister_Inst; \
} // namespace NekiraReflect_Inside
#endif