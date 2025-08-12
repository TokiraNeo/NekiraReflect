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

// Add a member variable
void ClassTypeInfo::AddVariable(std::unique_ptr<MemberVarInfo> varInfo)
{
    const auto name = varInfo->GetName();
    Variables[name] = std::move(varInfo);
}

// Add a member function
void ClassTypeInfo::AddFunction(std::unique_ptr<MemberFuncInfo> funcInfo)
{
    const auto name = funcInfo->GetName();
    Functions[name] = std::move(funcInfo);
}

// Get a member variable by name
MemberVarInfo* ClassTypeInfo::GetVariable(const std::string& name) const
{
    MemberVarInfo* Result = nullptr;

    auto it = Variables.find(name);

    if (it != Variables.end())
    {
        Result = it->second.get();
    }

    return Result;
}

// Get a member function by name
MemberFuncInfo* ClassTypeInfo::GetFunction(const std::string& name) const
{
    MemberFuncInfo* Result = nullptr;

    auto it = Functions.find(name);

    if (it != Functions.end())
    {
        Result = it->second.get();
    }

    return Result;
}

} // namespace NekiraReflect