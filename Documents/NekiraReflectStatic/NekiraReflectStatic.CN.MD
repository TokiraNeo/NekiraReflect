# NekiraReflectStatic

## 概述

`NekiraReflectStatic`主要负责实现静态反射相关。

## 链接

```cmake
target_link_libraries(Target PRIVATE NekiraReflectionLib::NekiraReflectStatic)

target_include_directories(Target PRIVATE ${NekiraReflection_INCLUDE_DIRS})
```

## 接口

在项目中引入如下头文件，即可使用 NekiraReflectStatic 库的功能

```cpp
#include "NekiraReflect/StaticReflect/Core/Core.hpp"
```

## 静态反射

### 静态反射注册

```cpp
struct SampleStruct
{
    int Value;
    const char* Args[];

    void Func() {}

    void ConstFunc() const {}
};

STATIC_REFLECT_BEGIN(SampleStruct)
STATIC_REFLECT_VARIABLES
(
    // MemberVarPtr + MemberVarName
    STATIC_REGISTER_VARIABLE(&SampleStruct::Value, Value),
    STATIC_REGISTER_VARIABLE(&SampleStruct::Args, Args)
)
STATIC_REFLECT_FUNCTIONS
(
    // MemberFuncPtr + MemberFuncName
    STATIC_REGISTER_FUNCTION(&SampleStruct::Func, Func)
    STATIC_REGISTER_FUNCTION(&SampleStruct::ConstFunc, ConstFunc)
)
STATIC_REFLECT_END()
```

### 静态反射接口

```cpp
// 获取特定的类型的静态反射信息（前提是该类型已注册静态反射)
template <typename T>
static constexpr auto GetStaticTypeInfo() -> StaticTypeInfo<T>;
```

---

```cpp
// 获取成员变量指针
template <typename ClassType, std::size_t Index>
static constexpr auto GetMemberFunction();
```

---

```cpp
// 获取成员变量指针
template <typename ClassType, std::size_t Index>
static constexpr auto GetMemberVariable()
```
