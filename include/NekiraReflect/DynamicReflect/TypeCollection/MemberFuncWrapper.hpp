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
#include <memory>


namespace NekiraReflect
{
template <typename RT, typename... Args>
struct MemberFuncWrapper_Base
{
    virtual ~MemberFuncWrapper_Base() = default;

    virtual RT Invoke(Args... args) = 0;
};

template <typename Callable, typename RT, typename... Args>
    requires std::is_invocable_r_v<RT, Callable, Args...>
struct MemberFuncWrapper_Impl : MemberFuncWrapper_Base<RT, Args...>
{
    explicit MemberFuncWrapper_Impl(Callable&& obj) : CallableObj(std::forward<Callable>(obj))
    {}

    RT Invoke(Args... args) override
    {
        return CallableObj(std::forward<Args>(args)...);
    }

private:
    Callable CallableObj;
};

template <typename T>
struct MemberFuncWrapper;

template <typename RT, typename... Args>
struct MemberFuncWrapper<RT(Args...)>
{
    MemberFuncWrapper() = default;

    template <typename Callable>
        requires std::is_invocable_r_v<RT, Callable, Args...>
    explicit MemberFuncWrapper(Callable func)
        : Wrapper(std::make_unique<MemberFuncWrapper_Impl<Callable, RT, Args...>>(std::move(func)))
    {}

    template <typename Callable>
        requires std::is_invocable_r_v<RT, Callable, Args...>
    MemberFuncWrapper& operator=(Callable func)
    {
        Wrapper = std::make_unique<MemberFuncWrapper_Impl<Callable, RT, Args...>>(std::move(func));
        return *this;
    }

    RT Invoke(Args... args)
    {
        return Wrapper->Invoke(std::forward<Args>(args)...);
    }

private:
    //@[TODO] 这里在外部使用时，指针类型无法正常支持万能引用，考虑优化
    std::unique_ptr<MemberFuncWrapper_Base<RT, Args...>> Wrapper;
};



} // namespace NekiraReflect
