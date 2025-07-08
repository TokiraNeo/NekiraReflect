
#include "TypeExtration.hpp"
#include <iostream>

struct FStruct
{
    void Func() {}

    void ConstFunc() const {}

    int Function(int a, int b) const
    {
        return a + b;
    }
};


int main()
{
    using Type1 = function_traits_FuncType< decltype(&FStruct::Func) >;
    using Type2 = function_traits_FuncType< decltype(&FStruct::ConstFunc) >;
    using Type3 = function_traits_FuncType< decltype(&FStruct::Function) >;

    static_assert( std::is_same_v< Type1, void(FStruct::*)() > );
    static_assert( std::is_same_v< Type2, void(FStruct::*)() const > );
    static_assert( std::is_same_v< Type3, int(FStruct::*)(int, int) const > );

    auto Lambda = [](int a, int b) { return a + b; };

    using Type4 = function_traits_FuncType< decltype(Lambda) >;

    function_traits<decltype(Lambda)> LambdaTraits;
    
    std::cout << "Lambda IsMember: " << LambdaTraits.IsMember << std::endl;
    std::cout << "Is a lambda or function object: " << LambdaTraits.IsLambdaOrFunctionObject << std::endl;

    static_assert( function_traits_IsMember< decltype(&FStruct::Func) > );
  

    return 0;
}

