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

#include <Tools/CodeUtilities.hpp>


namespace NekiraReflect
{

// 生成枚举的反射代码
void CodeGenerateHelper::GenerateEnumCode(std::ofstream& Header, std::ofstream& Source,
                                          const std::vector<EnumMetaInfo>& Enums)
{
    for (const auto& EnumMeta : Enums)
    {
        // --头文件内容

        Header << "// Enum: " << EnumMeta.QualifiedName << '\n';

        if (EnumMeta.NameSpace.empty())
        {
            // NEKIRA_REFLECT_ENUM_ACCESSOR_DECL(EnumName), 声明枚举的反射访问器特化(无命名空间)
            Header << "NEKIRA_REFLECT_ENUM_ACCESSOR_DECL" << "(" << EnumMeta.Name << ")" << '\n';
        }
        else
        {
            // NEKIRA_REFLECT_ENUM_ACCESSOR_DECL_NS(NameSpace, EnumName), 声明枚举的反射访问器特化(有命名空间)
            Header << "NEKIRA_REFLECT_ENUM_ACCESSOR_DECL_NS" << "(" << EnumMeta.NameSpace << ", " << EnumMeta.Name
                   << ")" << '\n';
        }

        GenerateIntervalLine(Header);

        // --源文件内容

        Source << "// Enum: " << EnumMeta.QualifiedName << '\n';

        // NEKIRA_REFLECT_ENUM_ACCESSOR_BEGIN(QualifiedName),定义枚举的反射访问器RegisterReflection()实现
        Source << "NEKIRA_REFLECT_ENUM_ACCESSOR_BEGIN" << "(" << EnumMeta.QualifiedName << ")" << '\n';

        // NEKIRA_REFLECT_ENUM_ACCESSOR_VALUE(ValueName), 注册枚举值
        for (const auto& EnumItem : EnumMeta.Elements)
        {
            Source << "NEKIRA_REFLECT_ENUM_ACCESSOR_VALUE" << "(" << EnumItem << ")" << '\n';
        }

        // NEKIRA_REFLECT_ENUM_ACCESSOR_END(),结束枚举反射访问器RegisterReflection()的实现
        Source << "NEKIRA_REFLECT_ENUM_ACCESSOR_END()" << '\n';

        if (EnumMeta.NameSpace.empty())
        {
            // NEKIRA_REFLECT_ENUM_REGISTER_AUTO(EnumName),自动注册枚举反射信息(无命名空间)
            Source << "NEKIRA_REFLECT_ENUM_REGISTER_AUTO" << "(" << EnumMeta.Name << ")" << '\n';
        }
        else
        {
            // NEKIRA_REFLECT_ENUM_REGISTER_AUTO_NS(NameSpace, EnumName),自动注册枚举反射信息(有命名空间)
            Source << "NEKIRA_REFLECT_ENUM_REGISTER_AUTO_NS" << "(" << EnumMeta.NameSpace << ", " << EnumMeta.Name
                   << ")" << '\n';
        }

        GenerateIntervalLine(Source);
    }
}

// 生成类的反射代码
void CodeGenerateHelper::GenerateClassCode(std::ofstream& Header, std::ofstream& Source,
                                           const std::vector<ClassMetaInfo>& Classes)
{
    for (const auto& ClassMeta : Classes)
    {
        // --头文件内容
        Header << "// Class/Struct: " << ClassMeta.QualifiedName << '\n';

        if (ClassMeta.NameSpace.empty())
        {
            // NEKIRA_REFLECT_CLASS_ACCESSOR_DECL(ClassName), 声明类的反射访问器特化(无命名空间)
            Header << "NEKIRA_REFLECT_CLASS_ACCESSOR_DECL" << "(" << ClassMeta.Name << ")" << '\n';
        }
        else
        {
            // NEKIRA_REFLECT_CLASS_ACCESSOR_DECL_NS(NameSpace, ClassName), 声明类的反射访问器特化(有命名空间)
            Header << "NEKIRA_REFLECT_CLASS_ACCESSOR_DECL_NS" << "(" << ClassMeta.NameSpace << ", " << ClassMeta.Name
                   << ")" << '\n';
        }

        GenerateIntervalLine(Header);

        // --源文件内容
        Source << "// Class/Struct: " << ClassMeta.QualifiedName << '\n';

        // NEKIRA_REFLECT_CLASS_ACCESSOR_BEGIN(QualifiedName),定义类的反射访问器RegisterReflection()实现
        Source << "NEKIRA_REFLECT_CLASS_ACCESSOR_BEGIN" << "(" << ClassMeta.QualifiedName << ")" << '\n';

        // NEKIRA_REFLECT_CLASS_ACCESSOR_VAR(VarName), 注册类成员变量
        for (const auto& VarMeta : ClassMeta.MemberVars)
        {
            Source << "NEKIRA_REFLECT_CLASS_ACCESSOR_VAR" << "(" << VarMeta.Name << ")" << '\n';
        }

        // NEKIRA_REFLECT_CLASS_ACCESSOR_FUNC(FuncName), 注册类成员函数
        for (const auto& FuncMeta : ClassMeta.MemberFuncs)
        {
            Source << "NEKIRA_REFLECT_CLASS_ACCESSOR_FUNC" << "(" << FuncMeta.Name << ")" << '\n';
        }

        // NEKIRA_REFLECT_CLASS_ACCESSOR_END(),结束类反射访问器RegisterReflection()的实现
        Source << "NEKIRA_REFLECT_CLASS_ACCESSOR_END()" << '\n';

        if (ClassMeta.NameSpace.empty())
        {
            // NEKIRA_REFLECT_CLASS_REGISTER_AUTO(ClassName),自动注册类反射信息(无命名空间)
            Source << "NEKIRA_REFLECT_CLASS_REGISTER_AUTO" << "(" << ClassMeta.Name << ")" << '\n';
        }
        else
        {
            // NEKIRA_REFLECT_CLASS_REGISTER_AUTO_NS(NameSpace, ClassName),自动注册类反射信息(有命名空间)
            Source << "NEKIRA_REFLECT_CLASS_REGISTER_AUTO_NS" << "(" << ClassMeta.NameSpace << ", " << ClassMeta.Name
                   << ")" << '\n';
        }

        GenerateIntervalLine(Source);
    }
}

} // namespace NekiraReflect