#include "ReflectMacro.hpp"
#include <iostream>

using namespace NekiraReflect;

struct TStruct
{
    int x;
    float y;

    void Func()
    {
        std::cout << "TStruct::Func called" << std::endl;
    }

    void ConstFunc() const
    {
        std::cout << "TStruct::ConstFunc called" << std::endl;
    }

    int Function(int a, int b) const
    {
        std::cout << "TStruct::Function called with a: " << a << ", b: " << b << std::endl;
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
    TStruct Obj{10, 20.5f};

    auto TStructInfo = GetTypeInfo<TStruct>();

    std::cout << "Type Name: " << TStructInfo.Name << std::endl;

    std::cout << "First Variable: " << std::get<0>(TStructInfo.Variables).FieldName << std::endl;
    std::cout << "Second Variable: " << std::get<1>(TStructInfo.Variables).FieldName << std::endl;

    std::cout << "First Function: " << std::get<0>(TStructInfo.Functions).FieldName << std::endl;
    std::cout << "Second Function: " << std::get<1>(TStructInfo.Functions).FieldName << std::endl;
    std::cout << "Third Function: " << std::get<2>(TStructInfo.Functions).FieldName << std::endl;

    auto VarTraits = std::get<0>(TStructInfo.Variables);
    std::cout << "Var Name: " << VarTraits.FieldName << std::endl;

    auto FuncPtr = std::get<0>(TStructInfo.Functions).FieldPointer;
    if (FuncPtr)
    {
        (Obj.*FuncPtr)();
    }

    auto ConstFuncPtr = GetMemberFunction<TStruct, 1>();
    if (ConstFuncPtr)
    {
        (Obj.*ConstFuncPtr)();
    }

    auto VarPtr = GetMemberVariable<TStruct, 0>();
    if (VarPtr)
    {
        std::cout << "Variable x: " << Obj.*VarPtr << std::endl;
        Obj.*VarPtr = 90;
        std::cout << "Updated Variable x: " << Obj.*VarPtr << std::endl;
    }

    return 0;
}
