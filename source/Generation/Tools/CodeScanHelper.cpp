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

#include "Tools/CodeUtilities.hpp"
#include "Tools/ReflectGenSettings.hpp"
#include "clang-c/CXString.h"
#include "clang-c/Index.h"
#include <cstring>
#include <iostream>
#include <vector>


namespace NekiraReflect
{

// 扫描源码的AST
void CodeScanHelper::ScanCode(const std::string& FileName, const ReflectGenSettings& Settings, VisitorData& OutData)
{
    CXIndex Index = clang_createIndex(0, 0);

    int                ArgsNum = Settings.CommandLineArgs.size();
    const char* const* ArgsPtr = Settings.CommandLineArgs.data();

    /* 不提供详细报错代码
    CXTranslationUnit TSUnit = clang_parseTranslationUnit(Index, FileName.c_str(), ArgsPtr, ArgsNum, nullptr, 0,
                                                          CXTranslationUnit_SkipFunctionBodies);
                                                          */
    CXTranslationUnit TSUnit = nullptr;
    // 记录报错代码
    const auto Result =
    clang_parseTranslationUnit2(Index, FileName.c_str(), ArgsPtr, ArgsNum, nullptr, 0, CXTranslationUnit_SkipFunctionBodies, &TSUnit);

    if (TSUnit == nullptr)
    {
        std::cerr << "\033[31mFailed to parse translation unit: " << FileName << "\033[0m\n";
        std::cerr << "\033[31mError code: " << Result << "\033[0m\n";

        clang_disposeIndex(Index);
        clang_disposeTranslationUnit(TSUnit);

        return;
    }

    /*
    // [TODO] 在Release版本中取消诊断，以允许源文件可以预先包含对应的.gen.hpp文件即使该文件还未生成。
    // 提供诊断信息
    unsigned DiagNum = clang_getNumDiagnostics(TSUnit);
    for (unsigned i = 0; i < DiagNum; ++i)
    {
        CXDiagnostic Diag = clang_getDiagnostic(TSUnit, i);
        CXString     DiagStr = clang_formatDiagnostic(Diag, clang_defaultDiagnosticDisplayOptions());
        std::cout << "Diagnostic: " << clang_getCString(DiagStr) << '\n';
        clang_disposeString(DiagStr);
        clang_disposeDiagnostic(Diag);
    }
    */

    // 获取AST根节点
    CXCursor RootCursor = clang_getTranslationUnitCursor(TSUnit);

    // 遍历AST
    clang_visitChildren(RootCursor, Visitor, &OutData);

    clang_disposeIndex(Index);
    clang_disposeTranslationUnit(TSUnit);
}

// AST遍历回调函数
CXChildVisitResult CodeScanHelper::Visitor(CXCursor Current, CXCursor Root, CXClientData ClientData)
{
    auto*        Data = static_cast<VisitorData*>(ClientData);
    CXCursorKind Kind = clang_getCursorKind(Current);

    // 仅处理主文件中的节点
    CXSourceLocation CursorLocation = clang_getCursorLocation(Current);
    if (clang_Location_isFromMainFile(CursorLocation) == 0)
    {
        return CXChildVisit_Continue;
    }

    switch (Kind)
    {
    case CXCursor_EnumDecl:
        // 处理枚举声明
        // [INFO] 检查是否有NEnum属性，并提取枚举值
        ProcessEnumDecl(Current, Data);
        break;

    case CXCursor_StructDecl:
        // 处理结构体声明
        // [INFO] 检查是否有NStruct属性，并提取成员变量和函数
        ProcessStructDecl(Current, Data);
        break;

    case CXCursor_ClassDecl:
        // 处理类声明
        // [INFO] 检查是否有NClass属性，并提取成员变量和函数
        ProcessClassDecl(Current, Data);
        break;

    default:
        break;
    }

    // 继续遍历子节点
    return CXChildVisit_Recurse;
}

// 处理枚举声明
void CodeScanHelper::ProcessEnumDecl(const CXCursor& Cursor, VisitorData* Data)
{
    if (!CheckAttribute(Cursor, "NEnum"))
    {
        return;
    }

    // 初始化枚举的命名空间
    EnumMetaInfo EnumMeta{GetFullNameSpace(Cursor)};

    // 获取枚举名称
    CXString EnumSpelling = clang_getCursorSpelling(Cursor);
    EnumMeta.Name = clang_getCString(EnumSpelling);
    clang_disposeString(EnumSpelling);

    // 获取枚举限定名称
    EnumMeta.QualifiedName = BuildQualifiedName(EnumMeta.NameSpace, EnumMeta.Name);

    // 获取枚举值
    clang_visitChildren(Cursor, EnumValueVisitor, &EnumMeta);

    // 添加到枚举列表
    Data->Enums.push_back(std::move(EnumMeta));
}

// 处理结构体声明
void CodeScanHelper::ProcessStructDecl(const CXCursor& Cursor, VisitorData* Data)
{
    if (!CheckAttribute(Cursor, "NStruct"))
    {
        return;
    }

    // 初始化结构体的命名空间
    ClassMetaInfo StructMeta{GetFullNameSpace(Cursor)};

    // 获取结构体名称
    CXString StructSpelling = clang_getCursorSpelling(Cursor);
    StructMeta.Name = clang_getCString(StructSpelling);
    clang_disposeString(StructSpelling);

    // 获取结构体限定名称
    StructMeta.QualifiedName = BuildQualifiedName(StructMeta.NameSpace, StructMeta.Name);

    // 处理成员变量和函数
    clang_visitChildren(Cursor, MemberVisitor, &StructMeta);

    // 添加到类列表
    Data->Classes.push_back(std::move(StructMeta));
}

// 处理类声明
void CodeScanHelper::ProcessClassDecl(const CXCursor& Cursor, VisitorData* Data)
{
    if (!CheckAttribute(Cursor, "NClass"))
    {
        return;
    }

    // 初始化类的命名空间
    ClassMetaInfo ClassMeta{GetFullNameSpace(Cursor)};

    // 获取类名称
    CXString ClassSpelling = clang_getCursorSpelling(Cursor);
    ClassMeta.Name = clang_getCString(ClassSpelling);
    clang_disposeString(ClassSpelling);

    // 获取类限定名称
    ClassMeta.QualifiedName = BuildQualifiedName(ClassMeta.NameSpace, ClassMeta.Name);

    // 处理成员变量和函数
    clang_visitChildren(Cursor, MemberVisitor, &ClassMeta);

    // 添加到类列表
    Data->Classes.push_back(std::move(ClassMeta));
}

// 处理成员变量的声明
void CodeScanHelper::ProcessMemberVarDecl(const CXCursor& Cursor, ClassMetaInfo* ClassMeta)
{
    if (!CheckAttribute(Cursor, "NProperty"))
    {
        return;
    }

    MemberVarMetaInfo VarMeta;

    // 获取成员变量名称
    CXString VarSpelling = clang_getCursorSpelling(Cursor);
    VarMeta.Name = clang_getCString(VarSpelling);
    clang_disposeString(VarSpelling);

    // 获取成员变量限定名称
    CXString VarQualify = clang_getCursorDisplayName(Cursor);
    VarMeta.QualifiedName = clang_getCString(VarQualify);
    clang_disposeString(VarQualify);

    // 添加到类的成员变量列表
    ClassMeta->MemberVars.push_back(std::move(VarMeta));
}

// 处理成员函数的声明
void CodeScanHelper::ProcessMemberFuncDecl(const CXCursor& Cursor, ClassMetaInfo* ClassMeta)
{
    if (!CheckAttribute(Cursor, "NFunction"))
    {
        return;
    }

    MemberFuncMetaInfo FuncMeta;

    // 获取成员函数名称
    CXString FuncSpelling = clang_getCursorSpelling(Cursor);
    FuncMeta.Name = clang_getCString(FuncSpelling);
    clang_disposeString(FuncSpelling);

    // 获取成员函数限定名称
    CXString FuncQualify = clang_getCursorDisplayName(Cursor);
    FuncMeta.QualifiedName = clang_getCString(FuncQualify);
    clang_disposeString(FuncQualify);

    // 添加到类的成员函数列表
    ClassMeta->MemberFuncs.push_back(std::move(FuncMeta));
}

// 成员访问回调(用于类和结构体)
CXChildVisitResult CodeScanHelper::MemberVisitor(CXCursor Current, CXCursor Root, CXClientData ClientData)
{
    auto* ClassMeta = static_cast<ClassMetaInfo*>(ClientData);

    if (Current.kind == CXCursor_FieldDecl)
    {
        ProcessMemberVarDecl(Current, ClassMeta);
    }
    else if (Current.kind == CXCursor_CXXMethod)
    {
        ProcessMemberFuncDecl(Current, ClassMeta);
    }

    // 继续遍历同级节点
    return CXChildVisit_Continue;
}

// 枚举值访问回调
CXChildVisitResult CodeScanHelper::EnumValueVisitor(CXCursor Current, CXCursor Root, CXClientData ClientData)
{
    if (Current.kind == CXCursor_EnumConstantDecl)
    {
        auto* EnumMeta = static_cast<EnumMetaInfo*>(ClientData);

        // 获取枚举值名称
        CXString    ValueSpelling = clang_getCursorSpelling(Current);
        std::string ValueName = clang_getCString(ValueSpelling);
        clang_disposeString(ValueSpelling);

        // 添加到枚举值列表
        EnumMeta->Elements.push_back(std::move(ValueName));
    }

    // 继续遍历同级节点
    return CXChildVisit_Continue;
}

// 检查是否有特定的Attribute
bool CodeScanHelper::CheckAttribute(const CXCursor& Cursor, const std::string& AttributeName)
{
    if (AttributeName.empty())
    {
        return false;
    }

    AttributeSearchData Data{AttributeName, false};

    clang_visitChildren(
        Cursor,
        [](CXCursor Current, CXCursor Root, CXClientData ClientData) -> CXChildVisitResult
        {
            if (clang_getCursorKind(Current) == CXCursor_AnnotateAttr)
            {
                auto* SearchData = static_cast<AttributeSearchData*>(ClientData);

                CXString    AttrSpelling = clang_getCursorSpelling(Current);
                const char* AttrCStr = clang_getCString(AttrSpelling);
                // 这里如果过早释放CXString，会导致AttrCStr为空

                // 比较
                if (AttrCStr != nullptr)
                {
                    if (SearchData->Attribute == AttrCStr)
                    {
                        SearchData->bFound = true;

                        clang_disposeString(AttrSpelling);
                        return CXChildVisit_Break;
                    }
                }
            }

            return CXChildVisit_Continue;
        },
        &Data);

    return Data.bFound;
}

// 获取完整命名空间(以::分隔)
std::string CodeScanHelper::GetFullNameSpace(const CXCursor& Cursor)
{
    std::vector<std::string> NameSpaces;

    // 获取父节点。
    CXCursor Parent = clang_getCursorSemanticParent(Cursor);

    while (!clang_Cursor_isNull(Parent))
    {
        // 到达顶部编译单元时停止
        if (Parent.kind == CXCursor_TranslationUnit)
        {
            break;
        }
        // 如果是命名空间，则向前插入
        else if (Parent.kind == CXCursor_Namespace)
        {
            CXString NameSpaceSpelling = clang_getCursorSpelling(Parent);
            auto     NameSpaceStr = clang_getCString(NameSpaceSpelling);

            if (NameSpaceStr && strlen(NameSpaceStr) > 0)
            {
                NameSpaces.insert(NameSpaces.begin(), NameSpaceStr);
            }

            // 释放字符串
            clang_disposeString(NameSpaceSpelling);
        }

        // 继续向上获取父节点
        Parent = clang_getCursorSemanticParent(Parent);
    }

    // 拼接命名空间
    std::string FullNameSpace;
    for (const auto& NameSpace : NameSpaces)
    {
        // 如果不是第一个命名空间，则添加分隔符
        if (!FullNameSpace.empty())
        {
            FullNameSpace += "::";
        }

        FullNameSpace += NameSpace;
    }

    return FullNameSpace;
}

// 获取限定名称(包含命名空间)
std::string CodeScanHelper::BuildQualifiedName(const std::string& NameSpace, const std::string& Name)
{
    if (NameSpace.empty())
    {
        return Name;
    }

    return NameSpace + "::" + Name;
}

} // namespace NekiraReflect