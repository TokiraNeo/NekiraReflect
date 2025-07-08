
#pragma once

#include <tuple>



// [INFO] 存储类型反射信息
template <typename T>
struct TypeInfo
{
    // 类型名
    static constexpr const char* Name = "UnknownType";

    // 变量名元组
    static constexpr auto Variables = std::make_tuple();

    // 函数名元组
    static constexpr auto Functions = std::make_tuple();

};

template <typename T>
auto GetTypeInfo() -> TypeInfo<T>
{
    return TypeInfo<T>{};
}