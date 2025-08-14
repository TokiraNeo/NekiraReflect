# NekiraReflectTool

## 概述

NekiraReflectTool 是负责头文件扫描，动态反射代码生成的工具。在安装完 NekiraReflect 库后，在安装路径的 bin 文件夹中，需要将该 bin 文件夹路径添加到系统环境变量，这样系统才能找到 NekiraReflectTool.exe

## 使用

NekiraReflectTool 会扫描指定头文件，识别其中的反射宏，生成对应的`gen.hpp`和`gen.cpp`文件。

### 命令行调用(不推荐)

可以提供命令行手动调用 NekiraReflectTool，虽然这不是推荐的做法，这里仅作示范。
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

#### cmake function

NekiraReflectTool 提供了两个 cmake 函数：

##### NekiraReflection_AddModule
