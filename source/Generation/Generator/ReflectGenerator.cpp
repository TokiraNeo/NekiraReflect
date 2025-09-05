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
#include <Tools/CodeConsume.hpp>
#include <Tools/CodeUtilities.hpp>
#include <Tools/ReflectGenSettings.hpp>
#include <iostream>


namespace NekiraReflect
{
// 扫描代码并生成反射代码
void ReflectGenerator::GenerateReflectCode(const std::filesystem::path& InputFile,
                                           const std::filesystem::path& OutputDir, const ReflectGenSettings& Settings)
{
    VisitorData Data;

    // 扫描代码
    std::cout << "\033[32m-- Scan File: " << InputFile.filename() << "\033[0m\n";
    CodeScanner::ScanCode(InputFile.string(), Settings, Data);

    if (Data.Enums.empty() && Data.Classes.empty())
    {
        std::cout << "\033[33m-Skip File: " << InputFile.filename() << "\033[0m\n";
        return;
    }

    // 生成反射代码
    std::cout << "\033[34m-- Generate Code For: " << InputFile.filename() << "\033[0m\n";
    CodeGenerator::GenerateCode(InputFile, OutputDir, Data.Enums, Data.Classes);
}

} // namespace NekiraReflect