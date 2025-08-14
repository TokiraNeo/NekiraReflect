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

#include "Utility/Utilities.hpp"
#include "ReflectionRegistry.hpp"


namespace NekiraReflect
{

// Register Enum TypeInfo
void RegisterEnumInfo(std::unique_ptr<EnumTypeInfo> EnumInfo)
{
    ReflectionRegistry::Get().RegisterEnum(std::move(EnumInfo));
}

// Register Class TypeInfo
void RegisterClassInfo(std::unique_ptr<ClassTypeInfo> ClassInfo)
{
    ReflectionRegistry::Get().RegisterClass(std::move(ClassInfo));
}

} // namespace NekiraReflect


namespace NekiraReflect
{
// Get Enum TypeInfo by std::type_index
EnumTypeInfo* GetNEnum(std::type_index TypeIndex)
{
    return ReflectionRegistry::Get().GetEnumInfo(TypeIndex);
}

// Get Class TypeInfo by std::type_index
ClassTypeInfo* GetNClass(std::type_index TypeIndex)
{
    return ReflectionRegistry::Get().GetClassInfo(TypeIndex);
}

// Get Struct TypeInfo by std::type_index
ClassTypeInfo* GetNStruct(std::type_index TypeIndex)
{
    return ReflectionRegistry::Get().GetClassInfo(TypeIndex);
}

} // namespace NekiraReflect