# NekiraReflectTool

## 概述

NekiraReflectTool 是负责头文件扫描，动态反射代码生成的工具。

## 使用

NekiraReflectTool 会扫描指定头文件，识别其中的反射宏，生成对应的`gen.hpp`和`gen.cpp`文件。

### 命令行调用(不推荐)

可以提供命令行手动调用 NekiraReflectTool，虽然这不是推荐的做法，这里仅作示范。

在安装完 NekiraReflectionLib 库后，在安装路径的 bin 文件夹中，需要将该 bin 文件夹路径添加到系统环境变量，这样系统才能找到 NekiraReflectTool.exe

在命令行中手动调用 NekiraReflectTool 时，**必须提供头文件路径和生成路径**，这两个路径必须是**绝对路径**，**顺序不可调换**。

#### 帮助命令

```powershell
NekiraReflect -help
```

#### 手动扫描生成反射文件

```powershell
NekiraReflect <input_header> <output_dir> [options]
```

### CMake 配置(非常推荐)

通过 CMake 配置 NekiraReflectTool，可以模块化地配置每个模块的反射配置。

假设你有多个模块，你可以在每个模块的根目录中的 CMakeLists 中单独配置该模块的反射配置，NekiraReflectTool 能够为每个模块生成单独的反射代码并进行相关自动化配置操作。

#### CMake Function

NekiraReflectTool 提供了两个 cmake 函数：

##### NekiraReflection_AddModule()

`NekiraReflection_AddModule()` 告知 NekiraReflectTool 当前模块的反射配置，主要参数如下：

- **TARGET**: 要添加反射信息的模块 target，可以是 executable、library...

- **OUTPUT_DIR**: 反射代码的输出路径，会被添加到**TARGET**的 include 路径之中，默认是`${CMAKE_CURRENT_SOURCE_DIR}/Generated`

- **HEADERS**: 希望扫描的头文件，NekiraReflectTool 会扫描其中的反射宏，生成对应的`gen.hpp`和`gen.cpp`文件

- **INCLUDE_PATHS**: 类似`target_include_directories()`,告知 NekiraReflectTool 需要使用的 include 搜索路径。NekiraReflectTool 会自动包含 NekiraReflection 的 include 路径，因此可以省略`${NekiraReflection_INCLUDE_DIRS}`

- **DEFINITIONS**: 预处理宏，例如`DEBUG`

- **OPTIONS**: 其他可选参数。例如`-std=c++20`.**(需要特别注意：如果扫描的头文件是`.h`形式的 C++头文件，必须添加`-x c++`,否则会识别成 C 头文件导致语法错误无法扫描)**

---

#### NekiraReflection_CleanModule()

`NekiraReflection_CleanModule()`告知 NekiraReflectTool 清理当前模块已经生成的反射代码，通常情况下并不需要用到该函数。

- **TARGET**：指定要清理反射代码的模块，可以是 executable、library...

#### Example

假设工程有两个模块：Core 和 Math

```cmake
# Core/CMakeLists.txt

file(GLOB_RECURSE CORE_HEADERS Public/*.h Public/*.hpp)
file(GLOB_RECURSE CORE_SOURCES Private/*.cpp)

add_library(Core ${CORE_HEADERS} ${CORE_SOURCES})

target_link_libraries(Core PRIVATE
        NekiraReflection
)

target_include_directories(Core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
        ${NekiraReflection_INCLUDE_DIRS})


NekiraReflection_AddModule(
        TARGET Core
        HEADERS ${CORE_HEADERS}
        INCLUDE_PATHS
        OPTIONS -std=c++20 -fsyntax-only -x c++
)
```

---

```cmake
# Math/CMakeLists.txt

file(GLOB_RECURSE MATH_HEADERS "Public/*.h" "Public/*.hpp")
file(GLOB_RECURSE MATH_SOURCES "Private/*.cpp")

add_library(Math ${MATH_HEADERS} ${MATH_SOURCES})

target_link_libraries(Math PRIVATE NekiraReflection)

target_include_directories(Math PRIVATE ${NekiraReflection_INCLUDE_DIRS})

NekiraReflection_AddModule(
        TARGET Math
        HEADERS ${MATH_HEADERS}
        INCLUDE_PATHS
        OPTIONS -std=c++20 -fsyntax-only -x c++
)
```
