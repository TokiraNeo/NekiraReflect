# NekiraReflectStatic

## Overview

NekiraReflectStatic focus on providing essential features for static reflection.

## Linking

```cmake
target_link_libraries(Target PRIVATE NekiraReflectionLib::NekiraReflectStatic)

target_include_directories(Target PRIVATE ${NekiraReflection_INCLUDE_DIRS})
```

## Interface

To use NekiraReflectStatic, include the following header:

```c++
#include "NekiraReflect/StaticReflect/Core/Core.hpp"
```

## Static Reflection

### Static Reflection Registration

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

### Static Reflection Interfaces

```cpp
// Get static reflection info for a specific type (the type must be registered for static reflection)
template <typename T>
static constexpr auto GetStaticTypeInfo() -> StaticTypeInfo<T>;
```

---

```cpp
// Get member function pointer
template <typename ClassType, std::size_t Index>
static constexpr auto GetMemberFunction();
```

---

```cpp
// Get member variable pointer
template <typename ClassType, std::size_t Index>
static constexpr auto GetMemberVariable();
```
