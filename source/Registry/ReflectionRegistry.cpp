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


#include "ReflectionRegistry.hpp"

namespace NekiraReflect
{

// Register Enum Info
void ReflectionRegistry::RegisterEnum(std::unique_ptr<EnumTypeInfo> EnumInfo)
{
    const std::type_index TypeIndex = EnumInfo->GetTypeIndex();
    EnumInfos[TypeIndex] = std::move(EnumInfo);
}

// Register Class Info
void ReflectionRegistry::RegisterClass(std::unique_ptr<ClassTypeInfo> ClassInfo)
{
    const std::type_index TypeIndex = ClassInfo->GetTypeIndex();
    ClassInfos[TypeIndex] = std::move(ClassInfo);
}

// Get Enum Info by TypeIndex
EnumTypeInfo* ReflectionRegistry::GetEnumInfo(std::type_index TypeIndex) const
{
    EnumTypeInfo* Result = nullptr;

    const auto it = EnumInfos.find(TypeIndex);

    if (it != EnumInfos.end())
    {
        Result = it->second.get();
    }

    return Result;
}

// Get Enum Info by Name(Would be slower)
EnumTypeInfo* ReflectionRegistry::GetEnumInfoByName(const std::string& Name) const
{
    EnumTypeInfo* Result = nullptr;

    for (const auto& Pair : EnumInfos)
    {
        if (Pair.second->GetName() == Name)
        {
            Result = Pair.second.get();
            break;
        }
    }

    return Result;
}

// Get Class Info by TypeIndex
ClassTypeInfo* ReflectionRegistry::GetClassInfo(std::type_index TypeIndex) const
{
    ClassTypeInfo* Result = nullptr;

    const auto it = ClassInfos.find(TypeIndex);

    if (it != ClassInfos.end())
    {
        Result = it->second.get();
    }

    return Result;
}

// Get Class Info by Name(Would be slower)
ClassTypeInfo* ReflectionRegistry::GetClassInfoByName(const std::string& Name) const
{
    ClassTypeInfo* Result = nullptr;

    for (const auto& Pair : ClassInfos)
    {
        if (Pair.second->GetName() == Name)
        {
            Result = Pair.second.get();
            break;
        }
    }

    return Result;
}

} // namespace NekiraReflect