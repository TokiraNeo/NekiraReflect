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


#include "clang-c/Index.h"
#include <NekiraReflect/Generation/Tools/MetaInfo.hpp>
#include <fstream>
#include <string>
#include <vector>


namespace NekiraReflect
{
struct ReflectGenSettings;
}

namespace NekiraReflect
{
struct VisitorData
{
    std::vector<EnumMetaInfo>  Enums;   // 需要反射的枚举
    std::vector<ClassMetaInfo> Classes; // 需要反射的类或结构体
};

struct AttributeSearchData
{
    std::string Attribute;      // 属性名称
    bool        bFound = false; // 是否有该属性
};
} // namespace NekiraReflect

namespace NekiraReflect
{

// 辅助生成反射代码
class CodeGenerateHelper final
{
public:
    // 生成枚举的反射代码
    static void GenerateEnumCode(std::ofstream& Header, std::ofstream& Source, const std::vector<EnumMetaInfo>& Enums);

    // 生成类的反射代码
    static void GenerateClassCode(std::ofstream& Header, std::ofstream& Source,
                                  const std::vector<ClassMetaInfo>& Classes);

private:
    // 生成间隔行
    static inline void GenerateIntervalLine(std::ofstream& Stream)
    {
        Stream << "/////////////////////////////////////////////////////////////" << '\n';
    }
};

// 辅助扫描抽象语法树
class CodeScanHelper final
{
public:
    // 扫描源码的AST
    static void ScanCode(const std::string& FileName, const ReflectGenSettings& Settings, VisitorData& OutData);

private:
    // AST遍历回调函数
    static CXChildVisitResult Visitor(CXCursor Cursor, CXCursor Root, CXClientData ClientData);

    // 处理枚举声明
    static void ProcessEnumDecl(const CXCursor& Cursor, VisitorData* Data);

    // 处理结构体声明
    static void ProcessStructDecl(const CXCursor& Cursor, VisitorData* Data);

    // 处理类声明
    static void ProcessClassDecl(const CXCursor& Cursor, VisitorData* Data);

    // 处理成员变量的声明
    static void ProcessMemberVarDecl(const CXCursor& Cursor, ClassMetaInfo* ClassMeta);

    // 处理成员函数的声明
    static void ProcessMemberFuncDecl(const CXCursor& Cursor, ClassMetaInfo* ClassMeta);

    // 成员访问回调(用于类和结构体)
    static CXChildVisitResult MemberVisitor(CXCursor Cursor, CXCursor Root, CXClientData ClientData);

    // 枚举值访问回调
    static CXChildVisitResult EnumValueVisitor(CXCursor Cursor, CXCursor Root, CXClientData ClientData);

    // 检查是否有特定的Attribute
    static bool CheckAttribute(const CXCursor& Cursor, const std::string& AttributeName);

    // 获取完整命名空间(以::分隔)
    static std::string GetFullNameSpace(const CXCursor& Cursor);

    // 获取限定名称(包含命名空间)
    static std::string BuildQualifiedName(const std::string& NameSpace, const std::string& Name);
};
} // namespace NekiraReflect
