#include "ReflectMacro.hpp"
#include <iostream>

struct TStruct
{
    int x;
    float y;

    void Func() {}

    void ConstFunc() const {}

    int Function(int a, int b) const
    {
        return a + b;
    }
};

// [INFO] 为结构体TStruct注册反射信息
REFLECT_BEGIN(TStruct)
REFLECT_VARIABLES(
    REGISTER_VARIABLE(&TStruct::x, x),
    REGISTER_VARIABLE(&TStruct::y, y))
REFLECT_FUNCTIONS(
    REGISTER_FUNCTION(&TStruct::Func, Func),
    REGISTER_FUNCTION(&TStruct::ConstFunc, ConstFunc),
    REGISTER_FUNCTION(&TStruct::Function, Function))
REFLECT_END()

int main()
{
    auto TStructInfo = GetTypeInfo<TStruct>();

    std::cout << "Type Name: " << TStructInfo.Name << std::endl;

    std::cout << "First Variable: " << std::get<0>(TStructInfo.Variables).FieldName << std::endl;
    std::cout << "Second Variable: " << std::get<1>(TStructInfo.Variables).FieldName << std::endl;

    std::cout << "First Function: " << std::get<0>(TStructInfo.Functions).FieldName << std::endl;
    std::cout << "Second Function: " << std::get<1>(TStructInfo.Functions).FieldName << std::endl;
    std::cout << "Third Function: " << std::get<2>(TStructInfo.Functions).FieldName << std::endl;

    auto VarTraits = std::get<0>(TStructInfo.Variables);
    std::cout << "Var Name: " << VarTraits.FieldName << std::endl;

    return 0;
}
