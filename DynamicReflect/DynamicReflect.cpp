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


#include <iostream>

#include "DynamicReflect.hpp"

using namespace NekiraReflect;


enum class TestEnum
{
    Value1 = 1,
    Value2 = 2,
    Value3 = 3
};

int main()
{
    auto EnumInfo = MakeEnumTypeInfo<TestEnum>( "TestEnum",
        {
            { "Value1", static_cast< __int64 >( TestEnum::Value1 ) },
            { "Value2", static_cast< __int64 >( TestEnum::Value2 ) },
            { "Value3", static_cast< __int64 >( TestEnum::Value3 ) }
        }
    );



    RegisterEnumInfo( std::move( EnumInfo ) );

    auto EnumTypeInfo = TypeInfoRegistry::Get().GetEnumInfo<TestEnum>();
    if ( EnumTypeInfo )
    {
        std::cout << "Enum Name: " << EnumTypeInfo->GetName() << '\n';
        std::cout << "Values:\n";
        for ( const auto& Pair : EnumTypeInfo->GetAllEnumValues() )
        {
            std::cout << "  " << Pair.first << " = " << Pair.second << '\n';
        }
    }

    return 0;
}