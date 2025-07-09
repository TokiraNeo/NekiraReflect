#pragma once

#include <tuple>
#include <type_traits>
#include <functional>

namespace NekiraReflect
{
    // =============================================== 函数萃取器 =============================================== //
    // 基础的函数萃取器
    template <typename Callable>
    struct function_traits_base
    {
        using FuncType = void;
        using ReturnType = void;
        using ArgTypes = std::tuple<>;
        using ObjectType = void;
        // 这里的static，主要是便于能够直接“类型级别”访问。并且由于模版会根据不同模版参数实例化，即每个T各一份。
        // 相当于每个T模版都是一个独立的类，它有自己的static成员变量IsMember,IsConst。
        static constexpr bool IsMember = false;
        static constexpr bool IsConst = false;
        static constexpr bool IsLambdaOrFunctionObject = false;
    };

    // 用于提取函数信息，默认实现（带SFINAE，避免递归冲突）
    template <typename Callable, typename = void>
    struct function_traits : function_traits_base<Callable>
    {
    };

    // 对普通函数指针的特化
    template <typename RT, typename... ParamTypes>
    struct function_traits<RT (*)(ParamTypes...), void> : function_traits_base<RT (*)(ParamTypes...)>
    {
        using FuncType = RT (*)(ParamTypes...);
        using ReturnType = RT;
        using ArgTypes = std::tuple<ParamTypes...>;
    };

    // 对成员函数指针的特化
    template <typename ClassType, typename RT, typename... ParamTypes>
    struct function_traits<RT (ClassType::*)(ParamTypes...), void> : function_traits_base<RT (ClassType::*)(ParamTypes...)>
    {
        using FuncType = RT (ClassType::*)(ParamTypes...);
        using ReturnType = RT;
        using ArgTypes = std::tuple<ParamTypes...>;
        using ObjectType = ClassType;
        static constexpr bool IsMember = true;
    };

    // 对常量成员函数指针的特化
    template <typename ClassType, typename RT, typename... ParamTypes>
    struct function_traits<RT (ClassType::*)(ParamTypes...) const, void> : function_traits_base<RT (ClassType::*)(ParamTypes...) const>
    {
        using FuncType = RT (ClassType::*)(ParamTypes...) const;
        using ReturnType = RT;
        using ArgTypes = std::tuple<ParamTypes...>;
        using ObjectType = ClassType;
        static constexpr bool IsMember = true;
        static constexpr bool IsConst = true;
    };

    // 对std::function的特化
    template <typename RT, typename... Args>
    struct function_traits<std::function<RT(Args...)>, void> : function_traits<RT (*)(Args...)>
    {
    };

    // 对函数对象以及 lambda 表达式的特化（仅对类类型生效，避免递归冲突）
    template <typename Callable>
    struct function_traits<Callable, std::enable_if_t<std::is_class_v<Callable>>> : function_traits<decltype(&Callable::operator())>
    {
        static constexpr bool IsLambdaOrFunctionObject = true;
    };

    // ================================================== 便捷别名和常量 ================================================== //
    // 获取函数指针类型
    template <typename T>
    using function_traits_FuncType = typename function_traits<T>::FuncType;

    // 获取返回值类型
    template <typename T>
    using function_traits_RT = typename function_traits<T>::ReturnType;

    // 获取参数类型的元组
    template <typename T>
    using function_traits_ArgTypes = typename function_traits<T>::ArgTypes;

    // 获取对象类型（仅对成员函数有效）
    template <typename T>
    using function_traits_ObjectType = typename function_traits<T>::ObjectType;

    // 是否为成员函数
    template <typename T>
    constexpr bool function_traits_IsMember = function_traits<T>::IsMember;

    // 是否为常量成员函数
    template <typename T>
    constexpr bool function_traits_IsConst = function_traits<T>::IsConst;

    // 参数个数
    template <typename T>
    constexpr size_t function_traits_Arity = std::tuple_size<function_traits_ArgTypes<T>>::value;

    // 获取第N个参数类型
    template <typename T, size_t N>
    using function_traits_Arg = std::tuple_element_t<N, function_traits_ArgTypes<T>>;

} // namespace NekiraReflect