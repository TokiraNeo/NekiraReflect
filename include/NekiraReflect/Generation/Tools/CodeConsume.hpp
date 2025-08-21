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

#include "NekiraReflect/Generation/Tools/CodeUtilities.hpp"
#include <filesystem>

namespace NekiraReflect
{
struct ReflectGenSettings;
}



namespace NekiraReflect
{
class CodeGenerator final
{
public:
    CodeGenerator() = default;

    // 生成枚举、类、结构体的反射代码
    static void GenerateCode(const std::filesystem::path& InputFile, const std::filesystem::path& OutputDir,
                             const std::vector<EnumMetaInfo>& Enums, const std::vector<ClassMetaInfo>& Classes);
};

// 用于扫描抽象语法树，查找反射相关Attribute
class CodeScanner final
{
public:
    CodeScanner() = default;

    static void ScanCode(const std::string& InputFile, const ReflectGenSettings& Settings, VisitorData& OutData);
};

} // namespace NekiraReflect
