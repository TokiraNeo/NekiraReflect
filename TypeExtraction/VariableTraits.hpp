
#pragma once

#include <type_traits>

// [INFO] 成员变量指针的剥离
template <typename T>
struct member_pointer_traits
{
    using Type = T;
    using ObjectType = void;
};

template <typename ClassType, typename MemberType>
struct member_pointer_traits<MemberType ClassType::*>
{
    using Type = MemberType;
    using ObjectType = ClassType;
};


// [INFO] 类型剥离，获取去除引用、指针、const等修饰符的类型
template <typename T>
struct raw_type
{
    using Type = T;
};

// [INFO] 剥离const
template <typename T>
struct raw_type<const T> : raw_type<T> {};

// [INFO] 剥离volatile
template <typename T>
struct raw_type<volatile T> : raw_type<T> {};

// [INFO] 剥离引用
template <typename T>
struct raw_type<T&> : raw_type<T> {};

// [INFO] 剥离右值引用
template <typename T>
struct raw_type<T&&> : raw_type<T> {};

// [INFO] 剥离指针
template <typename T>
struct raw_type<T*> : raw_type<T> {};

// [INFO] 剥离数组
template <typename T, std::size_t N>
struct raw_type<T[N]> : raw_type<T> {};

// [INFO] 基础的变量萃取器
template <typename T>
struct variable_traits_base
{
    // 去除引用，指针，const等修饰符的类型
    using RawType = typename raw_type< typename member_pointer_traits<T>::Type >::Type; 

    using ValueType = T;

    using ClassType = typename member_pointer_traits<T>::ObjectType;
};

// [INFO] 变量萃取器，默认实现
template <typename T>
struct variable_traits : variable_traits_base<T>
{
};


// ================================================== 便捷别名和常量 ================================================== //
// 获取去除引用、指针、const等修饰符的类型
template <typename T>
using variable_traits_RawType = typename variable_traits<T>::RawType;

// 获取值类型
template <typename T>
using variable_traits_ValueType = typename variable_traits<T>::ValueType;
