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

#include "MetaInfo.hpp"
#include <fstream>
#include <Tools/MetaInfo.hpp>


namespace NekiraReflect
{
    class CodeGenerateHelper final
    {
    public:
        // 生成枚举反射代码
        static void GenerateEnumCode(std::ofstream& HeaderStream, const std::vector<EnumMetaInfo>& Enums)
        {
            HeaderStream << "    //===================Generate Enum Reflection Code===================" << '\n';

            std::string EnumTypeInfoName;

            for (const auto Enum : Enums)
            {
                GenerateIntervalLine(HeaderStream);

                HeaderStream << "    // Enum: " << Enum.Name << '\n';
                EnumTypeInfoName = Enum.Name + "_TypeInfo";
                
                // 创建EnumTypeInfo的实例
                HeaderStream << "    auto " << EnumTypeInfoName << " = MakeEnumTypeInfo<";
                HeaderStream << Enum.Name << ">" << "(\"" << Enum.Name << "\")" << '\n';

                // 添加枚举对
                for (const auto& Pair : Enum.Elements)
                {
                    HeaderStream << "    " << EnumTypeInfoName << "->AddEnumValue";
                    HeaderStream << "(\"" << Pair.first << "\", " << Pair.second << ");" << '\n';
                }

                // 注册新建的EnumTypeInfo
                HeaderStream << "    RegisterEnumInfo( std::move(" << EnumTypeInfoName << ") );" << '\n';

                HeaderStream << '\n';
            }
        }

        // 生成类反射代码
        static void GenerateClassCode(std::ofstream& HeaderStream, const std::vector<ClassMetaInfo>& Classes)
        {
            HeaderStream << "    //===================Generate Class Reflection Code===================" << '\n';

        }

    private:
        // 生成间隔行
        static void GenerateIntervalLine(std::ofstream& Stream)
        {
            Stream << "    //////////////////////////////////////////////////////////" << '\n';
        }
    };

} // namespace NekiraReflect