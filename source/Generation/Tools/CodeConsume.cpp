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

#include "Tools/CodeConsume.hpp"
#include <fstream>



namespace NekiraReflect
{
// 生成枚举、类、结构体的反射代码
// OutputFile: 输出文件名(不包含后缀)
void CodeGenerator::GenerateCode(const std::filesystem::path& InputFile, const std::vector<EnumMetaInfo>& Enums,
                                 const std::vector<ClassMetaInfo>& Classes)
{
    const std::string InputFileStem = InputFile.stem().string();

    // 输出文件名(.gen.hpp & .gen.cpp)
    const std::string HeaderFileName = InputFileStem + ".gen.hpp";
    const std::string SourceFileName = InputFileStem + ".gen.cpp";

    // 输出文件路径
    const std::string HeaderFile = "Generated/" + HeaderFileName;
    const std::string SourceFile = "Generated/" + SourceFileName;

    std::ofstream HeaderStream(HeaderFile);
    std::ofstream SourceStream(SourceFile);

    // 生成头文件内容
    HeaderStream << "#pragma once" << '\n' << '\n';
    HeaderStream << "#include <NekiraReflect/DynamicReflect/Accessor/ReflectAccessor.hpp>" << '\n';
    HeaderStream << '\n';

    // 生成源文件内容
    SourceStream << "#include \"" << HeaderFileName << "\"" << '\n';
    SourceStream << "#include \"" << "../" << InputFile.string() << "\"" << '\n';
    SourceStream << '\n';

    // 生成枚举的反射代码
    if (!Enums.empty())
    {
        CodeGenerateHelper::GenerateEnumCode(HeaderStream, SourceStream, Enums);
    }

    // 生成类的反射注册代码
    if (!Classes.empty())
    {
        CodeGenerateHelper::GenerateClassCode(HeaderStream, SourceStream, Classes);
    }
}

// 用于扫描抽象语法树，查找反射相关Attribute
void CodeScanner::ScanCode(const std::string& InputFile, VisitorData& OutData)
{
    CodeScanHelper::ScanCode(InputFile, OutData);
}

} // namespace NekiraReflect