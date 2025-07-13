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
    }

    return 0;
}