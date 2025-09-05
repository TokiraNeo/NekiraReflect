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

#include <NekiraReflect/DynamicReflect/TypeCollection/CoreType.hpp>



// ======================================= 动态反射工具函数 ======================================= //

namespace NekiraReflect
{
// Get std::type_index by Type
template <typename T>
static std::type_index GetTypeIndex()
{
    return std::type_index(typeid(T));
}
} // namespace NekiraReflect


namespace NekiraReflect
{
// Create Enum TypeInfo
template <typename EnumType>
static std::unique_ptr<EnumTypeInfo> MakeEnumTypeInfo(const std::string& Name)
{
    auto TypeIndex = GetTypeIndex<EnumType>();

    const size_t TypeSize = sizeof(EnumType);

    auto EnumInfo = std::make_unique<EnumTypeInfo>(Name, TypeIndex);

    EnumInfo->SetSize(TypeSize);

    return EnumInfo;
}

// Create Enum TypeInfo with Enum Pairs
template <typename EnumType>
static std::unique_ptr<EnumTypeInfo> MakeEnumTypeInfo(const std::string& Name, const EnumValuesMap& Pairs)
{
    auto TypeIndex = GetTypeIndex<EnumType>();

    const size_t TypeSize = sizeof(EnumType);

    auto EnumInfo = std::make_unique<EnumTypeInfo>(Name, TypeIndex);

    EnumInfo->SetSize(TypeSize);

    for (const auto& [name, value] : Pairs)
    {
        EnumInfo->AddEnumValue(name, value);
    }

    return EnumInfo;
}

} // namespace NekiraReflect



namespace NekiraReflect
{
// Create Member Varaible TypeInfo
template <typename ClassType, typename VarType>
static std::unique_ptr<MemberVarInfo> MakeMemberVarInfo(const std::string& Name, VarType ClassType::* MemberVarPtr)
{
    return std::make_unique<MemberVarInfo>(Name, MemberVarPtr);
}

// Create Member Function TypeInfo
template <typename ClassType, typename RT, typename... Args>
static std::unique_ptr<MemberFuncInfo> MakeMemberFuncInfo(const std::string& Name, RT (ClassType::*FuncPtr)(Args...))
{
    return std::make_unique<MemberFuncInfo>(Name, FuncPtr);
}

// Create Member Function TypeInfo(const)
template <typename ClassType, typename RT, typename... Args>
static std::unique_ptr<MemberFuncInfo> MakeMemberFuncInfo(const std::string& Name,
                                                          RT (ClassType::*FuncPtr)(Args...) const)
{
    return std::make_unique<MemberFuncInfo>(Name, FuncPtr);
}

} // namespace NekiraReflect



namespace NekiraReflect
{

// Create Class TypeInfo
template <typename ClassType>
static std::unique_ptr<ClassTypeInfo> MakeClassTypeInfo(const std::string& Name)
{
    auto         TypeIndex = GetTypeIndex<ClassType>();
    const size_t TypeSize = sizeof(ClassType);

    auto ClassInfo = std::make_unique<ClassTypeInfo>(Name, TypeIndex);

    ClassInfo->SetSize(TypeSize);

    return ClassInfo;
}

} // namespace NekiraReflect



namespace NekiraReflect
{

// Register Enum TypeInfo
void RegisterEnumInfo(std::unique_ptr<EnumTypeInfo> EnumInfo);

// Register Class TypeInfo
void RegisterClassInfo(std::unique_ptr<ClassTypeInfo> ClassInfo);

} // namespace NekiraReflect


namespace NekiraReflect
{
// Get Enum TypeInfo by std::type_index
// @example:
// namespace Nekira::Test
// {
// enum class NENUM() SampleEnum
// {
//     Value1 = 20,
//     Value2 = 200
// };
// } // namespace Nekira::Test
//
// GetNEnum( std::type_index( typeid(Nekira::Test::SampleEnum) ) );
// OR:
// GetNEnum( GetTypeIndex<Nekira::Test::SampleEnum>() );
EnumTypeInfo* GetNEnum(std::type_index TypeIndex);

} // namespace NekiraReflect


namespace NekiraReflect
{
// Get Enum TypeInfo by Enum Type(include namespace)
// @example:
// namespace Nekira::Test
// {
// enum class NENUM() SampleEnum
// {
//     Value1 = 20,
//     Value2 = 200
// };
// } // namespace Nekira::Test
//
// GetNEnum<Nekira::Test::SampleEnum>();
template <typename EnumType>
static EnumTypeInfo* GetNEnum()
{
    auto TypeIndex = GetTypeIndex<EnumType>();
    return GetNEnum(TypeIndex);
}

} // namespace NekiraReflect


namespace NekiraReflect
{
// Get Class TypeInfo by std::type_index
// @example:
// namespace Nekira::Test
// {
// class NCLASS() SampleClass
// {
//     NEKIRA_REFLECT_BODY(SampleClass)
// private:
//     NPROPERTY()
//     int Value;
// };
// } // namespace Nekira::Test
//
// GetNClass( std::type_index( typeid(Nekira::Test::SampleClass) ) );
// OR:
// GetNClass( GetTypeIndex<Nekira::Test::SampleClass>() );
ClassTypeInfo* GetNClass(std::type_index TypeIndex);

} // namespace NekiraReflect


namespace NekiraReflect
{
// Get Class TypeInfo by Class Type(include namespace)
// @example:
// namespace Nekira::Test
// {
// class NCLASS() SampleClass
// {
//     NEKIRA_REFLECT_BODY(SampleClass)
// private:
//     NPROPERTY()
//     int Value;
// };
// } // namespace Nekira::Test
//
// GetNClass<Nekira::Test::SampleClass>();
template <typename ClassType>
static ClassTypeInfo* GetNClass()
{
    auto TypeIndex = GetTypeIndex<ClassType>();
    return GetNClass(TypeIndex);
}

} // namespace NekiraReflect


namespace NekiraReflect
{
// Get Struct TypeInfo by std::type_index
// @example:
// namespace Nekira::Test
// {
// struct NSTRUCT() SampleStruct
// {
//     NEKIRA_REFLECT_BODY(SampleStruct)
// private:
//     NPROPERTY()
//     int Value;
// };
// } // namespace Nekira::Test
//
// GetNStruct( std::type_index( typeid(Nekira::Test::SampleStruct) ) );
// OR:
// GetNStruct( GetTypeIndex<Nekira::Test::SampleStruct>() );
ClassTypeInfo* GetNStruct(std::type_index TypeIndex);

} // namespace NekiraReflect


namespace NekiraReflect
{
// Get Struct TypeInfo by Struct Type(include namespace)
// @example:
// namespace Nekira::Test
// {
// struct NSTRUCT() SampleStruct
// {
//     NEKIRA_REFLECT_BODY(SampleStruct)
// private:
//     NPROPERTY()
//     int Value;
// };
// } // namespace Nekira::Test
//
// GetNStruct<Nekira::Test::SampleStruct>();
template <typename StructType>
static ClassTypeInfo* GetNStruct()
{
    auto TypeIndex = GetTypeIndex<StructType>();
    return GetNStruct(TypeIndex);
}

} // namespace NekiraReflect