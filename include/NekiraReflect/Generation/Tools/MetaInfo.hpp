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

#include <cstdint>
#include <string>
#include <utility>
#include <vector>


namespace NekiraReflect
{
    // 枚举类型的元信息
    struct EnumMetaInfo
    {
        // 枚举类型的名称
        std::string Name;

        // 枚举值对
        std::vector< std::pair<std::string, int64_t> > Elements;
    };

    // 成员变量的元信息
    struct MemberVarMetaInfo
    {
        // 成员变量的名称
        std::string Name;

        // 成员变量的类型名称
        std::string TypeName;

        // 成员变量所属的类名称
        std::string ClassName;

        bool IsProtected = false;
        bool IsPrivate = false;
    };

    // 成员函数的元信息
    struct MemberFuncMetaInfo
    {
        // 成员函数的名称
        std::string Name;

        // 成员函数的返回类型名称
        std::string ReturnType;

        // 成员函数所属的类名称
        std::string ClassName;

        // 成员函数的参数列表  参数类型-参数名称
        std::vector< std::pair<std::string, std::string> > Parameters;

        bool IsProtected = false;
        bool IsPrivate = false;
    };

    // 类的元信息
    struct ClassMetaInfo
    {
        // 类的名称
        std::string Name;

        std::string QualifiedName;

        // 命名空间名称
        std::string Namespace;

        // 类的成员变量
        std::vector<MemberVarMetaInfo> MemberVars;

        // 类的成员函数
        std::vector<MemberFuncMetaInfo> MemberFuncs;
    };
} // namespace NekiraReflect