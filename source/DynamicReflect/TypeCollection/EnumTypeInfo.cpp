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

#include "TypeCollection/CoreType.hpp"


namespace NekiraReflect
{

// Add enum value by name and corresponding value
void EnumTypeInfo::AddEnumValue(const std::string& name, int64_t value)
{
    EnumValues[name] = value;
    EnumNames[value] = name;
}

// Add multiple enum values
void EnumTypeInfo::AddEnumValues(const EnumValuesMap& values)
{
    for (const auto& Pair : values)
    {
        AddEnumValue(Pair.first, Pair.second);
    }
}

// Get enum value by name, return true if found
bool EnumTypeInfo::GetEnumValueByName(const std::string& name, int64_t& outValue) const
{
    bool bFound = false;
    auto it = EnumValues.find(name);

    if (it != EnumValues.end())
    {
        outValue = it->second;
        bFound = true;
    }

    return bFound;
}

// Get enum name by value, return true if found
bool EnumTypeInfo::GetEnumNameByValue(const int64_t value, std::string& outName) const
{
    bool bFound = false;
    auto it = EnumNames.find(value);

    if (it != EnumNames.end())
    {
        outName = it->second;
        bFound = true;
    }

    return bFound;
}

} // namespace NekiraReflect