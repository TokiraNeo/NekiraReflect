/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#pragma once
#include "TypeCollection/MemberFuncWrapper.hpp"
#include <any>
#include <cstdint>
#include <iostream>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>


// ======================================= 动态反射核心类型 ======================================= //


// ======================================== 类型别名 ======================================== //
namespace NekiraReflect
{
using EnumValuesMap = std::unordered_map<std::string, int64_t>;
using EnumNamesMap = std::unordered_map<int64_t, std::string>;

using VariableMap = std::unordered_map<std::string, std::unique_ptr<class MemberVarInfo>>;
using FunctionMap = std::unordered_map<std::string, std::unique_ptr<class MemberFuncInfo>>;

} // namespace NekiraReflect



// ======================================= 类型定义 ======================================= //
namespace NekiraReflect
{

enum class TypeCategory
{
    Unknown,
    Fundamental, // int, float, char, bool, etc.
    Enum,
    Class,
    Pointer,
    Array
};

} // namespace NekiraReflect



// ======================================= 统一的类型信息 ======================================= //
namespace NekiraReflect
{

class TypeInfo
{
public:
    TypeInfo(const std::string& name, std::type_index typeIndex, size_t size)
        : Name(name), TypeIndex(typeIndex), Size(size)
    {}

    inline const std::string GetName() const
    {
        return Name;
    }

    inline const std::type_index GetTypeIndex() const
    {
        return TypeIndex;
    }

    inline const size_t GetSize() const
    {
        return Size;
    }

    inline void SetSize(size_t size)
    {
        Size = size;
    }

private:
    std::string     Name;
    std::type_index TypeIndex;
    size_t          Size;
};

} // namespace NekiraReflect



// ======================================= 枚举类型信息 ======================================= //
namespace NekiraReflect
{

class EnumTypeInfo : public TypeInfo
{
public:
    EnumTypeInfo(const std::string& name, std::type_index typeIndex) : TypeInfo(name, typeIndex, 0)
    {}

    // Add enum value by name and corresponding value
    void AddEnumValue(const std::string& name, int64_t value);

    // Add multiple enum values
    void AddEnumValues(const EnumValuesMap& values);

    // Get enum value by name, return true if found
    bool GetEnumValueByName(const std::string& name, int64_t& outValue) const;

    // Get enum name by value, return true if found
    bool GetEnumNameByValue(const int64_t value, std::string& outName) const;

    // Get all enum values
    inline const EnumValuesMap& GetAllEnumValues() const
    {
        return EnumValues;
    }

    // Get all enum names
    inline const EnumNamesMap& GetAllEnumNames() const
    {
        return EnumNames;
    }

private:
    // Enum Values Map
    EnumValuesMap EnumValues;

    // Enum Names Map
    EnumNamesMap EnumNames;
};

} // namespace NekiraReflect



// ========================================== 成员变量信息 ========================================== //
namespace NekiraReflect
{

class MemberVarInfo : public TypeInfo
{
public:
    template <typename ClassType, typename VarType>
    MemberVarInfo(const std::string& name, VarType ClassType::* memberPtr)
        : TypeInfo(name, typeid(VarType), sizeof(VarType))
    {
        Offset = (size_t)&(((ClassType*)0)->*memberPtr);
    }

    // Get Member Variable Value.
    template <typename VarType>
    VarType& GetValue(void* Object) const
    {
        VarType* MemberPtr = (VarType*)(((char*)Object) + Offset);

        return *MemberPtr;
    }

    // Set Member Variable Value.
    template <typename VarType>
    void SetValue(void* Object, const VarType& Value) const
    {
        VarType* MemberPtr = (VarType*)(((char*)Object) + Offset);

        *MemberPtr = Value;
    }

private:
    // Member Variable Offset
    size_t Offset;
};

} // namespace NekiraReflect



// ========================================== 成员函数参数辅助 ========================================== //
namespace NekiraReflect
{
// Convert std::vector<std::any> to std::tuple<Args...>

template <typename... Args, size_t... Indices>
std::tuple<Args...> Anys_To_Tuple_Impl(const std::vector<std::any>& Params, std::index_sequence<Indices...>)
{
    return std::make_tuple(std::any_cast<Args>(Params[Indices])...);
}

template <typename... Args>
std::tuple<Args...> Anys_To_Tuple(const std::vector<std::any>& Params)
{
    if (Params.size() != sizeof...(Args))
    {
        std::cerr << "Parameter count mismatch! Expected: " << sizeof...(Args) << ", Actual: " << Params.size() << '\n';
    }

    return Anys_To_Tuple_Impl<Args...>(Params, std::index_sequence_for<Args...>{});
}
} // namespace NekiraReflect



// ========================================== 成员函数信息 ========================================== //
namespace NekiraReflect
{
class MemberFuncInfo : public TypeInfo
{
public:
    // Member Function(non-const)
    template <typename ClassType, typename RT, typename... Args>
    MemberFuncInfo(const std::string& name, RT (ClassType::*funcPtr)(Args...))
        : TypeInfo(name, typeid(funcPtr), sizeof(funcPtr))
    {
        auto WrapperLambda = [funcPtr](void* Object, const std::vector<std::any>& Params) -> std::any
        {
            ClassType* ObjectPtr = static_cast<ClassType*>(Object);
            if constexpr (std::is_void_v<RT>)
            {
                auto VoidLambda = [funcPtr, ObjectPtr](auto&&... args) -> void
                { (ObjectPtr->*funcPtr)(std::forward<Args>(args)...); };

                std::apply(VoidLambda, Anys_To_Tuple<Args...>(Params));

                return std::any();
            }
            else
            {
                auto AnyLambda = [funcPtr, ObjectPtr](auto&&... args) -> std::any
                { return (ObjectPtr->*funcPtr)(std::forward<Args>(args)...); };

                return std::apply(AnyLambda, Anys_To_Tuple<Args...>(Params));
            }
        };

        FuncWrapper = WrapperLambda;
    }

    // Member Function(const)
    template <typename ClassType, typename RT, typename... Args>
    MemberFuncInfo(const std::string& name, RT (ClassType::*funcPtr)(Args...) const)
        : TypeInfo(name, typeid(funcPtr), sizeof(funcPtr))
    {
        auto WrapperLambda = [funcPtr](void* Object, const std::vector<std::any>& Params) -> std::any
        {
            ClassType* ObjectPtr = static_cast<ClassType*>(Object);
            if constexpr (std::is_void_v<RT>)
            {
                auto VoidLambda = [funcPtr, ObjectPtr](auto&&... args) -> void
                { (ObjectPtr->*funcPtr)(std::forward<Args>(args)...); };

                std::apply(VoidLambda, Anys_To_Tuple<Args...>(Params));

                return std::any();
            }
            else
            {
                auto AnyLambda = [funcPtr, ObjectPtr](auto&&... args) -> std::any
                { return (ObjectPtr->*funcPtr)(std::forward<Args>(args)...); };

                return std::apply(AnyLambda, Anys_To_Tuple<Args...>(Params));
            }
        };

        FuncWrapper = WrapperLambda;
    }


    // Invoke Function
    template <typename... Args>
    std::any Invoke(void* Object, Args&&... args)
    {
        std::vector<std::any> Params{std::any(std::forward<Args>(args))...};
        return FuncWrapper.Invoke(Object, Params);
    }

private:
    MemberFuncWrapper<std::any(void*, const std::vector<std::any>&)> FuncWrapper;
};

} // namespace NekiraReflect



// ========================================== 类、结构体的信息 ========================================== //
namespace NekiraReflect
{

class ClassTypeInfo : public TypeInfo
{


public:
    ClassTypeInfo(const std::string& name, std::type_index typeIndex) : TypeInfo(name, typeIndex, 0)
    {}

    // Get Variable Value
    template <typename VarType>
    VarType GetVariableValue(void* object, const std::string& name) const
    {
        auto varInfo = GetVariable(name);
        return varInfo ? varInfo->GetValue<VarType>(object) : VarType{};
    }

    // Set Variblae Value
    template <typename VarType>
    void SetVariableValue(void* object, const std::string& name, const VarType& value)
    {
        auto varInfo = GetVariable(name);
        if (varInfo)
        {
            varInfo->SetValue(object, value);
        }
    }

    // Add a member variable
    void AddVariable(std::unique_ptr<MemberVarInfo> varInfo);

    // Add a member function
    void AddFunction(std::unique_ptr<MemberFuncInfo> funcInfo);

    // Get a member variable by name
    MemberVarInfo* GetVariable(const std::string& name) const;

    // Get a member function by name
    MemberFuncInfo* GetFunction(const std::string& name) const;

    // Remove a member variable by name
    inline void RemoveVariable(const std::string& name)
    {
        Variables.erase(name);
    }

    // Remove a member function by name
    inline void RemoveFunction(const std::string& name)
    {
        Functions.erase(name);
    }

    // Get all member variables
    inline const VariableMap& GetAllVariables() const
    {
        return Variables;
    }

    // Get all member functions
    inline const FunctionMap& GetAllFunctions() const
    {
        return Functions;
    }


private:
    // Member Variables
    VariableMap Variables;

    // Member Functions
    FunctionMap Functions;
};

} // namespace NekiraReflect