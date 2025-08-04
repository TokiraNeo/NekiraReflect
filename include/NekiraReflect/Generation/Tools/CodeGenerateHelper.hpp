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


#include <Tools/MetaInfo.hpp>
#include <fstream>
#include <vector>



namespace NekiraReflect
{
class CodeGenerateHelper final
{
public:
    // 生成枚举的反射代码
    static void GenerateEnumCode(std::ofstream& Stream, const std::vector<EnumMetaInfo>& Enums)
    {
        Stream << "// =========================== Generate Enum Reflection Code =========================== " << '\n';

        for (const auto& EnumMeta : Enums)
        {
            Stream << "// Enum: " << EnumMeta.Name << '\n';

            // NEKIRA_REFLECT_ENUM_ACCESSOR_BEGIN(EnumName), 声明枚举的反射访问器特化
            Stream << "NEKIRA_REFLECT_ENUM_ACCESSOR_BEGIN" << "(" << EnumMeta.Name << ")" << '\n';

            // NEKIRA_REFLECT_ENUM_ACCESSOR_VALUE(ValueName), 注册枚举值
            for (const auto& Element : EnumMeta.Elements)
            {
                Stream << "NEKIRA_REFLECT_ENUM_ACCESSOR_VALUE" << "(" << Element << ")" << '\n';
            }

            // NEKIRA_REFLECT_ENUM_ACCESSOR_END(), 结束枚举的反射访问器定义
            Stream << "NEKIRA_REFLECT_ENUM_ACCESSOR_END()" << '\n' << '\n';

            // NEKIRA_REFLECT_ENUM_REGISTER_AUTO(EnumName), 自动注册枚举的反射信息
            Stream << "NEKIRA_REFLECT_ENUM_REGISTER_AUTO" << "(" << EnumMeta.Name << ")" << '\n';

            GenerateIntervalLine(Stream);
        }
    }

    // 生成类的反射代码
    static void GenerateClassCode(std::ofstream& Stream, const std::vector<ClassMetaInfo>& Classes)
    {
        Stream << "// =========================== Generate Class Reflection Code =========================== " << '\n';

        for (const auto& ClassMeta : Classes)
        {
            Stream << "// Class: " << ClassMeta.QualifiedName << '\n';

            // NEKIRA_REFLECT_CLASS_ACCESSOR_BEGIN(ClassName)，声明类的反射访问器特化
            Stream << "NEKIRA_REFLECT_CLASS_ACCESSOR_BEGIN" << "(" << ClassMeta.Name << ")" << '\n';

            // NEKIRA_REFLECT_CLASS_ACCESSOR_VAR(VarName)，注册类的成员变量
            for (const auto& VarMeta : ClassMeta.MemberVars)
            {
                Stream << "NEKIRA_REFLECT_CLASS_ACCESSOR_VAR" << "(" << VarMeta.Name << ")" << '\n';
            }

            // NEKIRA_REFLECT_CLASS_ACCESSOR_FUNC(FuncName), 注册类的成员函数
            for (const auto& FuncMeta : ClassMeta.MemberFuncs)
            {
                Stream << "NEKIRA_REFLECT_CLASS_ACCESSOR_FUNC" << "(" << FuncMeta.Name << ")" << '\n';
            }

            // NEKIRA_REFLECT_CLASS_ACCESSOR_END(), 结束类的反射访问器定义
            Stream << "NEKIRA_REFLECT_CLASS_ACCESSOR_END()" << '\n' << '\n';

            // NEKIRA_REFLECT_CLASS_REGISTER_AUTO(ClassName), 自动注册类的反射信息
            Stream << "NEKIRA_REFLECT_CLASS_REGISTER_AUTO" << "(" << ClassMeta.Name << ")" << '\n';

            GenerateIntervalLine(Stream);
        }
    }

private:
    // 生成间隔行
    static void GenerateIntervalLine(std::ofstream& Stream)
    {
        Stream << "/////////////////////////////////////////////////////////////" << '\n';
    }
};

} // namespace NekiraReflect