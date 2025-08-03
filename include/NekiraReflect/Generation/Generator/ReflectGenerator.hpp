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



namespace NekiraReflect
{
    // 生成反射代码
    class ReflectGenerator final
    {
    public:
        
        static void GenerateCode
        (
            const std::string& OutputFile, 
            const std::vector<EnumMetaInfo>& Enums,
            const std::vector<ClassMetaInfo>& Classes
        )
        {
            const std::string HeaderFile = OutputFile + ".gen.hpp";
            const std::string SourceFile = OutputFile + ".gen.cpp";

            const std::string GeneratorName = OutputFile + "_Generator";
            const std::string GeneratorFuncName = OutputFile + "_Func()";

            // 头文件流，生成gen.hpp文件
            std::ofstream HeaderStream(HeaderFile);
            // 源文件流，生成gen.cpp文件
            std::ofstream SourceStream(SourceFile);
            
            HeaderStream << "#pragma once" << '\n' << '\n';
            HeaderStream << "#include <NekiraReflect/DynamicReflect/DynamicReflect.hpp>" << '\n' << '\n';

            HeaderStream << "using namespace NekiraReflect;" << '\n' << '\n';

            HeaderStream << "void " << GeneratorFuncName << '\n';
            HeaderStream << "{\n";

            // 生成枚举类型的反射代码
            CodeGenerateHelper::GenerateEnumCode(HeaderStream, Enums);

            // 生成类的反射代码
            CodeGenerateHelper::GenerateClassCode(HeaderStream, Classes);

            HeaderStream << "}" << '\n' << '\n';

            SourceStream << "#include \"" << HeaderFile << "\"" << '\n' << '\n';
            SourceStream << GeneratorName << ' ' << GeneratorName << "_Inst;" << '\n';
        }


    private:
        
    };

} // namespace NekiraReflect
 
