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

#include <StaticReflect.hpp>
#include <iostream>

using namespace NekiraReflect;

struct TStruct
{
    int   a;
    float b;
    char  Name[7] = "Nekira";

    void Func()
    {
        std::cout << "TStruct::Func" << std::endl;
    }

    void ConstFunc() const
    {
        std::cout << "TStruct::ConstFunc" << std::endl;
    }

    void FuncWithArgs(int x, float y, int z)
    {
        std::cout << "TStruct::FuncWithArgs" << std::endl;
    }
};

STATIC_REFLECT_BEGIN(TStruct)
STATIC_REFLECT_FUNCTIONS(STATIC_REGISTER_FUNCTION(&TStruct::Func, Func),
                         STATIC_REGISTER_FUNCTION(&TStruct::ConstFunc, ConstFunc),
                         STATIC_REGISTER_FUNCTION(&TStruct::FuncWithArgs, FuncWithArgs))

STATIC_REFLECT_VARIABLES(STATIC_REGISTER_VARIABLE(&TStruct::a, a), STATIC_REGISTER_VARIABLE(&TStruct::b, b),
                         STATIC_REGISTER_VARIABLE(&TStruct::Name, Name))
STATIC_REFLECT_END()


auto Lambda = [](int x, float y) { std::cout << "Lambda called with: " << x << ", " << y << std::endl; };


int main()
{
    auto TStructInfo = GetStaticTypeInfo<TStruct>();
    std::cout << "Type Name: " << TStructInfo.Name << std::endl;

    auto FuncPtr = GetMemberFunction<TStruct, 2>();

    auto IntCount = function_traits_CountTypeInArgs<decltype(FuncPtr), int>;
    std::cout << "Number of int parameters in FuncWithArgs: " << IntCount << std::endl;

    function_traits<decltype(Lambda)> LambdaTraits;

    bool IsLambda = function_traits_IsLambdaOrFuncObject<decltype(Lambda)>;

    return 0;
}
