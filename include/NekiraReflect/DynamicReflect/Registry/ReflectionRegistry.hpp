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


// ======================================= 动态反射全局注册表 ======================================= //
namespace NekiraReflect
{

class ReflectionRegistry final
{
    using EnumInfoMap = std::unordered_map<std::type_index, std::unique_ptr<EnumTypeInfo>>;
    using ClassInfoMap = std::unordered_map<std::type_index, std::unique_ptr<ClassTypeInfo>>;

public:
    ReflectionRegistry(const ReflectionRegistry&) = delete;
    ReflectionRegistry& operator=(const ReflectionRegistry&) = delete;

    ReflectionRegistry(ReflectionRegistry&&) = delete;
    ReflectionRegistry& operator=(ReflectionRegistry&&) = delete;

    // 获取单例实例
    static ReflectionRegistry& Get();

    // Register Enum Info
    void RegisterEnum(std::unique_ptr<EnumTypeInfo> EnumInfo);

    // Register Class Info
    void RegisterClass(std::unique_ptr<ClassTypeInfo> ClassInfo);

    // Remove Enum Info
    void RemoveEnum(std::type_index TypeIndex);

    // Remove Class Info
    void RemoveClass(std::type_index TypeIndex);

    // Get Enum Info by TypeIndex
    EnumTypeInfo* GetEnumInfo(std::type_index TypeIndex) const;

    // Get Enum Info by Enum Type
    template <typename EnumType>
    EnumTypeInfo* GetEnumInfo() const
    {
        auto TypeIndex = std::type_index(typeid(EnumType));

        return GetEnumInfo(TypeIndex);
    }

    // Get Enum Info by Name(Would be slower)
    EnumTypeInfo* GetEnumInfoByName(const std::string& Name) const;

    // Get Class Info by TypeIndex
    ClassTypeInfo* GetClassInfo(std::type_index TypeIndex) const;

    // Get Class Info by Class Type
    template <typename ClassType>
    ClassTypeInfo* GetClassInfo() const
    {
        auto TypeIndex = std::type_index(typeid(ClassType));

        return GetClassInfo(TypeIndex);
    }

    // Get Class Info by Name(Would be slower)
    ClassTypeInfo* GetClassInfoByName(const std::string& Name) const;

private:
    ReflectionRegistry() = default;

private:
    // Enum Info
    EnumInfoMap EnumInfos{};

    // Class Info for Classes and Structs
    ClassInfoMap ClassInfos{};
};

} // namespace NekiraReflect
