#pragma once

#include <tuple>

namespace NekiraReflect
{

    // 存储类型反射信息
    template <typename T>
    struct StaticTypeInfo
    {
        // 类型名
        static constexpr const char *Name = "UnknownType";

        // 变量名元组
        static constexpr auto Variables = std::make_tuple();

        // 函数名元组
        static constexpr auto Functions = std::make_tuple();
    };

    // 获取特定的类型的静态反射信息（前提是该类型已注册静态反射）
    template <typename T>
    constexpr auto GetStaticTypeInfo() -> StaticTypeInfo<T>
    {
        return StaticTypeInfo<T>{};
    }

    // 获取成员函数指针
    template <typename ClassType, std::size_t Index>
    constexpr auto GetMemberFunction()
    {
        return std::get<Index>(StaticTypeInfo<ClassType>::Functions).FieldPointer;
    }

    // 获取成员变量指针
    template <typename ClassType, std::size_t Index>
    constexpr auto GetMemberVariable()
    {
        return std::get<Index>(StaticTypeInfo<ClassType>::Variables).FieldPointer;
    }

} // namespace NekiraReflect