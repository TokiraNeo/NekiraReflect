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

#include <NekiraReflect/DynamicReflect/DynamicReflect.hpp>
#include <NekiraReflect/DynamicReflect/TypeCollection/Utilities.hpp>

using namespace NekiraReflect;


enum class TestEnum
{
    Value1 = 1,
    Value2 = 2,
    Value3 = 3
};

class TestClass
{

public:
    int MemberVar;

    void Func( int a )
    {
        std::cout << "TestClass::Func called with value: " << a << '\n';
    }

    void ConstFunc( float b ) const
    {
        std::cout << "TestClass::ConstFunc called with value: " << b << '\n';
    }
};

int main()
{
    EnumValuesMap TestEnumValues = {
        { "Value1", static_cast< int64_t >( TestEnum::Value1 ) },
        { "Value2", static_cast< int64_t >( TestEnum::Value2 ) },
        { "Value3", static_cast< int64_t >( TestEnum::Value3 ) }
    };

    auto EnumInfo = MakeEnumTypeInfo<TestEnum>( "TestEnum", TestEnumValues );

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

    auto ClassInfo = MakeClassTypeInfo<TestClass>( "TestClass" );
    ClassInfo->AddVariable( MakeMemberVarInfo( "MemberVar", &TestClass::MemberVar ) );
    ClassInfo->AddFunction( MakeMemberFuncInfo( "Func", &TestClass::Func ) );
    ClassInfo->AddFunction( MakeMemberFuncInfo( "ConstFunc", &TestClass::ConstFunc ) );


    RegisterClassInfo( std::move( ClassInfo ) );

    TestClass ClassObj;

    if ( auto ClassTypeInfo = TypeInfoRegistry::Get().GetClassInfo( typeid( TestClass ) ) )
    {
        ClassTypeInfo->SetVariableValue( &ClassObj, "MemberVar", 999 );
        std::cout << "MemberVar: " << ClassTypeInfo->GetVariableValue<int>( &ClassObj, "MemberVar" ) << '\n';

        ClassTypeInfo->GetFunction( "Func" )->Invoke( &ClassObj, 9768 );

        ClassTypeInfo->GetFunction( "ConstFunc" )->Invoke( &ClassObj, 2.34f );
    }

    return 0;
}