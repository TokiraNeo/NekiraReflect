# NekiraReflection

## 概述

NekiraReflection 是主要的核心库，提供了类型萃取、静态反射、动态反射的核心功能。

## 链接库

要想使用 NekiraReflection 库，需在 CMake 中进行如下配置：

```cmake
target_link_libaries(Target PRIVATE NekiraReflectionLib::NekiraReflection)

target_include_directories(Target PRIVATE ${NekiraReflection_INCLUDE_DIRS})
```

## 接口

在项目中引入如下头文件，即可使用 NekiraReflection 库的功能

```cpp
#include "NekiraReflect/Core.hpp"
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
// 获取特定的类型的静态反射信息（前提是该类型已注册静态反射
template <typename T>
constexpr auto GetStaticTypeInfo() -> StaticTypeInfo<T>;
```

---

```cpp
// 获取成员变量指针
template <typename ClassType, std::size_t Index>
constexpr auto GetMemberFunction();
```

---

```cpp
// 获取成员变量指针
template <typename ClassType, std::size_t Index>
constexpr auto GetMemberVariable()
```

## 动态反射

`NekiraReflectTool` 会扫描头文件，为动态反射自动生成反射信息，详情见：[NekiraReflectTool](../NekiraReflectTool/NekiraReflectTool.CN.MD)

### 反射宏

#### NCLASS(), NSTRUCT(), NENUM(), NFUNCTION(), NPROPERTY()

反射宏，`NekiraReflectTool` 会识别这些宏并自动注册动态反射信息，它们分别对应于：`class`、`struct`、`enum class`、`member function`、`member variable`。

#### NEKIRA_REFLECT_BODY(ClasType)

为了让动态反射得以注册`Protected，Private`部分的成员，需要在`class，struct`这些的定义里添加`NEKIRA_REFLECT_BODY(ClasType)`宏(这里的 `ClassType` 包含命名空间限定)，并且在头文件添加对应的`gen.hpp`头文件。

### 动态反射注册

当然如果不涉及到注册`Protected，Private`部分的成员，可以只提供反射宏，不需要添加`NEKIRA_REFLECT_BODY(ClasType)`宏以及相应的`gen.hpp`头文件。`gen.hpp`头文件是 `NekiraReflectTool` 生成的文件，它的命名参考被扫描的源头文件，即如果是 `Test.h`，则生成 `Test.gen.hpp`。

可以在`gen.hpp`还没生成的时候，在源头文件显式引用(这时会提示文件不存在，但是在编译流程该文件会被生成，之后才进入正常编译流程)

### 一般情况的动态反射注册(假设涉及 Protected，Private 部分的成员)

```cpp
// Test.h

#include "NekiraReflect/Core.hpp"
#include "Test.gen.hpp"

namespace Nekira::Test
{

class NCLASS() QualifiedClass
{
    NEKIRA_REFLECT_BODY(Nekira::Test::QualifiedClass)

public:
    NFUNCTION()
    void Func() {}

private:
    NPROPERTY()
    std::string Arg;
};

enum class NENUM() QualifiedEnum
{
    value1,
    value2
}

} // namespace Nekira::Test

struct NSTRUCT() NormalStruct
{
    NEKIRA_REFLECT_BODY(NormalStruct)

protected:
    NPROPERTY()
    float Data;

private:
    void NonReflectFunc() {}

    NFUNCTION()
    void ReflectFunc() {}
};

```
