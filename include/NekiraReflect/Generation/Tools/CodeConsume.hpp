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

#include <Tools/CodeGenerateHelper.hpp>
#include <Tools/MetaInfo.hpp>
#include <clang-c/CXString.h>
#include <clang-c/Index.h>
#include <iostream>
#include <vector>



namespace NekiraReflect
{
class CodeGenerator final
{
public:
    // 生成枚举、类、结构体的反射代码
    // OutputFile: 输出文件名(不包含后缀)
    static void GenerateCode(const std::string& OutputFile, const std::vector<EnumMetaInfo>& Enums,
                             const std::vector<ClassMetaInfo>& Classes)
    {
        const std::string HeaderName = OutputFile + ".gen.hpp";

        std::ofstream HeaderStream(HeaderName);

        HeaderStream << "#pragma once" << '\n' << '\n';
        HeaderStream << "#include <NekiraReflect/DynamicReflect/Accessor/ReflectAccessor.hpp>" << '\n';
        HeaderStream << '\n';

        // 生成枚举的反射代码
        if (!Enums.empty())
        {
            CodeGenerateHelper::GenerateEnumCode(HeaderStream, Enums);
        }

        // 生成类的反射注册代码
        if (!Classes.empty())
        {
            CodeGenerateHelper::GenerateClassCode(HeaderStream, Classes);
        }
    }
};

} // namespace NekiraReflect


namespace NekiraReflect
{

// 用于扫描抽象语法树，查找反射相关Attribute
class CodeScanner
{
public:
    static void ScanTranslationUnit(const std::string& InputFile, std::vector<EnumMetaInfo>& OutEnums,
                                    std::vector<ClassMetaInfo>& OutClasses)
    {
        // [TODO] 扫描编译单元，检查NStruct，NClass，NEnum，NFunction，NProperty等Attribute

        CXIndex Index = clang_createIndex(0, 0);

        const char* ArgsStr = "-D__REFLECT_GEN_ENABLE__";

        CXTranslationUnit TSUnit =
            clang_parseTranslationUnit(Index, InputFile.c_str(), &ArgsStr, 0, nullptr, 0, CXTranslationUnit_None);

        if (TSUnit == nullptr)
        {
            std::cerr << "Failed to parse translation unit: " << InputFile << '\n';

            // 清理资源
            clang_disposeIndex(Index);
            clang_disposeTranslationUnit(TSUnit);

            return;
        }

        // 清理资源
        clang_disposeIndex(Index);
        clang_disposeTranslationUnit(TSUnit);

        // 获取AST根节点
        CXCursor RootCursor = clang_getTranslationUnitCursor(TSUnit);

        clang_visitChildren(
            RootCursor,
            [](CXCursor Child, CXCursor Parent, CXClientData ClientData) -> CXChildVisitResult
            {
                auto CursorSpelling = clang_getCursorSpelling(Child);

                return CXChildVisit_Recurse;
            },
            nullptr);
    }


private:
};

} // namespace NekiraReflect
