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
#include <clang-c/CXString.h>
#include <clang-c/Index.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>




namespace NekiraReflect
{

struct VisitorData
{
    std::vector<EnumMetaInfo>  Enums;   // 需要反射的枚举
    std::vector<ClassMetaInfo> Classes; // 需要反射的类或结构体
};

struct AttributeData
{
    std::string Attribute;             // 属性名称
    bool        bHasAttribute = false; // 是否有该属性
};


} // namespace NekiraReflect

namespace NekiraReflect
{

class CodeScanHelper final
{
public:
    // 扫描源码的AST
    static void ScanCode(const std::string& FileName, VisitorData& OutData)
    {
        CXIndex Index = clang_createIndex(0, 0);

        const char*        ArgsStr[] = {"-std=c++20", "-D__REFLECT_GEN_ENABLE__"};
        int                ArgsNum = sizeof(ArgsStr) / sizeof(ArgsStr[0]);
        const char* const* ArgsPtr = ArgsStr;

        CXTranslationUnit TSUnit =
            clang_parseTranslationUnit(Index, FileName.c_str(), ArgsPtr, ArgsNum, nullptr, 0, CXTranslationUnit_None);

        if (TSUnit == nullptr)
        {
            std::cerr << "Failed to parse translation unit: " << FileName << std::endl;

            clang_disposeIndex(Index);
            clang_disposeTranslationUnit(TSUnit);

            return;
        }

        // 获取AST根节点
        CXCursor RootCursor = clang_getTranslationUnitCursor(TSUnit);

        // 遍历AST
        clang_visitChildren(RootCursor, Visitor, &OutData);

        clang_disposeIndex(Index);
        clang_disposeTranslationUnit(TSUnit);
    }



private:
    // AST遍历回调函数
    static CXChildVisitResult Visitor(CXCursor Cursor, CXCursor Parent, CXClientData ClientData)
    {
        VisitorData* Data = static_cast<VisitorData*>(ClientData);
        CXCursorKind Kind = clang_getCursorKind(Cursor);

        // 仅处理主文件中的节点
        CXSourceLocation CursorLocation = clang_getCursorLocation(Cursor);
        if (clang_Location_isFromMainFile(CursorLocation) == 0)
        {
            return CXChildVisit_Continue;
        }

        switch (Kind)
        {
        case CXCursor_EnumDecl:
            // 处理枚举声明
            // [INFO] 检查是否有NENUM属性，并提取枚举值
            ProcessEnumDecl(Cursor, Data);
            break;

        case CXCursor_StructDecl:
            // 处理结构体声明
            // [INFO] 检查是否有NSTRUCT属性，并提取成员变量和函数
            ProcessStructDecl(Cursor, Data);
            break;

        case CXCursor_ClassDecl:
            // 处理类声明
            // [INFO] 检查是否有NCLASS属性，并提取成员变量和函数
            ProcessClassDecl(Cursor, Data);
            break;

        default:
            break;
        }

        // 继续遍历子节点
        return CXChildVisit_Recurse;
    }


    // 处理枚举声明
    static void ProcessEnumDecl(CXCursor Cursor, VisitorData* Data)
    {
        if (!CheckAttribute(Cursor, "NENUM"))
        {
            return;
        }

        EnumMetaInfo EnumMeta;

        // 获取枚举名称
        CXString EnumSpelling = clang_getCursorSpelling(Cursor);
        EnumMeta.Name = clang_getCString(EnumSpelling);
        clang_disposeString(EnumSpelling);

        // 获取枚举值
        clang_visitChildren(Cursor, EnumValueVisitor, &EnumMeta);

        // 添加到枚举列表
        Data->Enums.push_back(std::move(EnumMeta));
    }


    // 处理结构体声明
    static void ProcessStructDecl(CXCursor Cursor, VisitorData* Data)
    {
        if (!CheckAttribute(Cursor, "NSTRUCT"))
        {
            return;
        }

        ClassMetaInfo StructMeta;

        // 获取结构体名称
        CXString StructSpelling = clang_getCursorSpelling(Cursor);
        StructMeta.Name = clang_getCString(StructSpelling);
        clang_disposeString(StructSpelling);

        // 获取结构体限定名称
        CXString StructQualify = clang_getCursorDisplayName(Cursor);
        StructMeta.QualifiedName = clang_getCString(StructQualify);
        clang_disposeString(StructQualify);

        // 处理成员变量和函数
        clang_visitChildren(Cursor, MemberVisitor, &StructMeta);

        // 添加到类列表
        Data->Classes.push_back(std::move(StructMeta));
    }


    // 处理类声明
    static void ProcessClassDecl(CXCursor Cursor, VisitorData* Data)
    {
        if (!CheckAttribute(Cursor, "NCLASS"))
        {
            return;
        }

        ClassMetaInfo ClassMeta;

        // 获取类名称
        CXString ClassSpelling = clang_getCursorSpelling(Cursor);
        ClassMeta.Name = clang_getCString(ClassSpelling);
        clang_disposeString(ClassSpelling);

        // 获取类限定名称
        CXString ClassQualify = clang_getCursorDisplayName(Cursor);
        ClassMeta.QualifiedName = clang_getCString(ClassQualify);
        clang_disposeString(ClassQualify);

        // 处理成员变量和函数
        clang_visitChildren(Cursor, MemberVisitor, &ClassMeta);

        // 添加到类列表
        Data->Classes.push_back(std::move(ClassMeta));
    }


    // 处理成员变量的声明
    static void ProcessMemberVarDecl(CXCursor Cursor, ClassMetaInfo* ClassMeta)
    {
        if (!CheckAttribute(Cursor, "NPROPERTY"))
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
    static void ProcessMemberFuncDecl(CXCursor Cursor, ClassMetaInfo* ClassMeta)
    {
        if (!CheckAttribute(Cursor, "NFUNCTION"))
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
    static CXChildVisitResult MemberVisitor(CXCursor Cursor, CXCursor Parent, CXClientData ClientData)
    {
        ClassMetaInfo* ClassMeta = static_cast<ClassMetaInfo*>(ClientData);

        if (Cursor.kind == CXCursor_FieldDecl)
        {
            ProcessMemberVarDecl(Cursor, ClassMeta);
        }
        else if (Cursor.kind == CXCursor_CXXMethod)
        {
            ProcessMemberFuncDecl(Cursor, ClassMeta);
        }

        // 继续遍历同级节点
        return CXChildVisit_Continue;
    }


    // 枚举值访问回调
    static CXChildVisitResult EnumValueVisitor(CXCursor Cursor, CXCursor Parent, CXClientData ClientData)
    {
        if (Cursor.kind == CXCursor_EnumConstantDecl)
        {
            EnumMetaInfo* EnumMeta = static_cast<EnumMetaInfo*>(ClientData);

            // 获取枚举值名称
            CXString    ValueSpelling = clang_getCursorSpelling(Cursor);
            std::string ValueName = clang_getCString(ValueSpelling);
            clang_disposeString(ValueSpelling);

            // 添加到枚举值列表
            EnumMeta->Elements.push_back(std::move(ValueName));
        }

        // 继续遍历同级节点
        return CXChildVisit_Continue;
    }


    // 检查是否有特定的Attribute
    static bool CheckAttribute(CXCursor Cursor, const std::string& AttributeName)
    {
        if (AttributeName.empty())
        {
            return false;
        }

        AttributeData Data{AttributeName, false};

        clang_visitChildren(
            Cursor,
            [](CXCursor Current, CXCursor Parent, CXClientData ClientData) -> CXChildVisitResult
            {
                if (Current.kind == CXCursor_AnnotateAttr)
                {
                    AttributeData* Data = static_cast<AttributeData*>(ClientData);

                    CXString AttrSpelling = clang_getCursorSpelling(Current);
                    auto     AttrString = clang_getCString(AttrSpelling);
                    clang_disposeString(AttrSpelling);

                    if (AttrString == Data->Attribute)
                    {
                        Data->bHasAttribute = true;
                        return CXChildVisit_Break;
                    }
                }

                return CXChildVisit_Continue;
            },
            &Data);

        return Data.bHasAttribute;
    }
};

} // namespace NekiraReflect