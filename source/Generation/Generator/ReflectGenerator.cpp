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


#include <Generator/ReflectGenerator.hpp>
#include <filesystem>
#include <iostream>

namespace NekiraReflect
{
// 扫描代码并生成反射代码
void ReflectGenerator::GenerateReflectCode(const std::string& InputFile)
{
    VisitorData Data;

    // 输入路径
    std::filesystem::path InputPath(InputFile);

    // 扫描代码
    CodeScanner::ScanCode(InputFile, Data);

    std::cout << "Scanning file: " << InputPath.filename() << '\n';

    if (Data.Enums.empty() && Data.Classes.empty())
    {
        std::cout << "Skip File: " << InputPath.filename() << '\n';
        return;
    }

    // 获取输入文件名字(去除路径和后缀)
    const std::string InputFileStem = InputPath.stem().string();

    // 输出文件名
    const std::string OutputFileName = InputFileStem + ".gen.hpp";

    // 输出文件（路径 + 文件名）
    std::filesystem::path OutputFile = "Generated/" + OutputFileName;

    std::cout << "Generating Code: " << InputPath.filename() << " -> " << OutputFileName << '\n';

    // 生成反射代码
    CodeGenerator::GenerateCode(OutputFile.string(), Data.Enums, Data.Classes);
}
} // namespace NekiraReflect