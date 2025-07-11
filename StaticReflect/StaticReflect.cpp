
#include "StaticReflect.hpp"
#include <iostream>

using namespace NekiraReflect;

struct TStruct
{
    int a;
    float b;
    char Name[ 7 ] = "Nekira";

    void Func()
    {
        std::cout << "TStruct::Func" << std::endl;
    }

    void ConstFunc() const
    {
        std::cout << "TStruct::ConstFunc" << std::endl;
    }

    void FuncWithArgs( int x, float y, int z )
    {
        std::cout << "TStruct::FuncWithArgs" << std::endl;
    }
};

STATIC_REFLECT_BEGIN( TStruct )
STATIC_REFLECT_FUNCTIONS(
    STATIC_REGISTER_FUNCTION( &TStruct::Func, Func ),
    STATIC_REGISTER_FUNCTION( &TStruct::ConstFunc, ConstFunc ),
    STATIC_REGISTER_FUNCTION( &TStruct::FuncWithArgs, FuncWithArgs ) )
    STATIC_REFLECT_VARIABLES(
        STATIC_REGISTER_VARIABLE( &TStruct::a, a ),
        STATIC_REGISTER_VARIABLE( &TStruct::b, b ),
        STATIC_REGISTER_VARIABLE( &TStruct::Name, Name ) )
    STATIC_REFLECT_END()

    int main()
{
    auto TStructInfo = GetStaticTypeInfo<TStruct>();
    std::cout << "Type Name: " << TStructInfo.Name << std::endl;

    auto FuncPtr = GetMemberFunction<TStruct, 2>();

    auto IntCount = function_traits_CountTypeInArgs<decltype( FuncPtr ), int>;
    std::cout << "Number of int parameters in FuncWithArgs: " << IntCount << std::endl;

    return 0;
}
