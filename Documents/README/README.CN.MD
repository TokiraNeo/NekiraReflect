# NekiraReflect

## 项目简介

NekiraReflect 是一个基于 C++ 的反射工具库，提供静态反射与动态反射功能，包含一个反射生成器。

## 事项

- [x] 基本的函数萃取
- [x] 基本的变量萃取
- [x] 反射信息收集
- [x] 基本的静态反射(借助宏声明)
- [x] 基本的动态反射
- [x] 自动化扫描生成反射信息
- [x] 整理成库

## 安装

拉取下载 NekiraReflect 的源码，进入根目录，依次运行如下 CMake 命令：

```powershell
cmake -S . -B build -G Ninja
```

```powershell
cmake --build build
```

将 NekiraReflect 安装至 PC，可以保持默认的安装路径，也可以手动指定，在安装完毕之后将 NekiraReflect 安装路径中的 `bin` 文件夹路径添加至环境变量,这样系统可以找到`NekiraReflectTool.exe`

```powershell
cmake --install build [--prefix] [install_dir]
```

## 文档

### [NekiraReflection](../NekiraReflection/NekiraReflection.CN.MD)

### [NekiraReflectTool](../NekiraReflectTool/NekiraReflectTool.CN.MD)
