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
    ValueOne,
    ValueTwo,
    ValueThree
};

class TestClass
{
public:
    int a;
    float b;

    void Func()
    {
        std::cout << "TestClass::Func called" << std::endl;
    }

    void ConstFunc() const
    {
        std::cout << "TestClass::ConstFunc called" << std::endl;
    }

    void DoubleFunc( int x, float y ) const
    {
        std::cout << "TestClass::DoubleFunc called with x: " << x << " and y: " << y << std::endl;
    }

    void PrintFunc() const
    {
        std::cout << "TestClass::PrintFunc called" << std::endl;
    }

};

int main()
{
    MemberVarInfoVector MemberVars =
    {
        MakeMemberVariableInfo( &TestClass::a, "a" ),
        MakeMemberVariableInfo( &TestClass::b, "b" )
    };

    MemberFuncInfoVector MemberFuncs =
    {
        MakeMemberFunctionInfo( &TestClass::Func, "Func" ),
        MakeMemberFunctionInfo( &TestClass::ConstFunc, "ConstFunc" ),
        MakeMemberFunctionInfo( &TestClass::DoubleFunc, "DoubleFunc" )
    };

    auto ClassInfo = RegistClassTypeInfo( "TestClass", MemberVars, MemberFuncs );

    TestClass Obj{ 89, 4.5f };

    if ( ClassInfo )
    {
        std::cout << "ClassTypeInfo registered: " << ClassInfo->GetName() << std::endl;

        // [INFO] Mamually adding a member function
        ClassInfo->AddMemberFunction( &TestClass::PrintFunc, "PrintFunc" );

        if ( auto aPtr = ClassInfo->GetMemberVariable<int( TestClass::* )>( "a" ) )
        {
            std::cout << "MemberVar a: " << Obj.*aPtr << std::endl;
        }

        if ( auto bPtr = ClassInfo->GetMemberVariable<float( TestClass::* )>( "b" ) )
        {
            std::cout << "MemberVar b: " << Obj.*bPtr << std::endl;
        }

        if ( auto funcPtr = ClassInfo->GetMemberFunction<void( TestClass::* )( )>( "Func" ) )
        {
            ( Obj.*funcPtr )( );
        }

        if ( auto constFuncPtr = ClassInfo->GetMemberFunction<void( TestClass::* )( ) const>( "ConstFunc" ) )
        {
            ( Obj.*constFuncPtr )( );
        }

        if ( auto doubleFuncPtr = ClassInfo->GetMemberFunction<void( TestClass::* )( int, float ) const>( "DoubleFunc" ) )
        {
            ( Obj.*doubleFuncPtr )( 42, 3.14f );
        }

        if ( auto printFuncPtr = ClassInfo->GetMemberFunction<void( TestClass::* )( ) const>( "PrintFunc" ) )
        {
            ( Obj.*printFuncPtr )( );
        }
    }

    return 0;
}