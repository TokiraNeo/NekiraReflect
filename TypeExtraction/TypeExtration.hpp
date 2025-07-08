

#pragma once

#include "FunctionTraits.hpp"
#include "VariableTraits.hpp"

// [Info] 判断是否为函数类型
template<typename T>
constexpr bool IsFunction_v = std::is_function_v< std::remove_pointer_t<T> > || std::is_member_function_pointer_v<T>;

// [INFO] 字段萃取器的公共参数
template <typename T>
struct field_traits_common
{
    static constexpr bool IsFunction = IsFunction_v<T>;
    static constexpr bool IsVariable = !IsFunction;
};

// [Info] 基础的字段萃取器
template < typename T, bool IsFunc = IsFunction_v<T> >
struct field_traits_base
{
};

// [Info] 对于函数类型的特化
template <typename T>
struct field_traits_base<T, true> : function_traits<T>, field_traits_common<T>
{
};

// [INFO] 对于变量类型的特化
template <typename T>
struct field_traits_base<T, false> : variable_traits<T>, field_traits_common<T>
{ 
};

// [Info] 字段萃取器
template < typename T, typename = std::enable_if_t< std::is_member_pointer_v<T> || std::is_pointer_v<T> > >
struct field_traits : field_traits_base<T>
{
    T FieldPointer;
    const char* FieldName;

    constexpr field_traits(T pointer, const char* name)
    : FieldPointer(pointer)
    , FieldName(name) 
    {
    }

    constexpr field_traits(T Pointer)
    : FieldPointer(Pointer)
    , FieldName("")
    {
    }
};


