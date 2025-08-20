<h1 align="center">
    <b>NekiraReflectionLib</b>
</h1>

![GitHub License](https://img.shields.io/github/license/TokiraNeo/NekiraReflect?style=flat-square&labelColor=2EA2EF&color=2EEFDC)
![GitHub top language](https://img.shields.io/github/languages/top/TokiraNeo/NekiraReflect?style=flat-square&labelColor=29F5BB&color=29C9F5)
![C++ std](https://img.shields.io/badge/C%2B%2B_std-%3E%3D20-%23FF5C9A?style=flat-square&labelColor=%23C988F7)
![CMake Version](https://img.shields.io/badge/CMake-%3E%3D20-8EFF80?style=flat-square&labelColor=CEFF80)
![GitHub commit activity (branch)](https://img.shields.io/github/commit-activity/m/TokiraNeo/NekiraReflect/main?style=flat-square&labelColor=91CBED&color=A0AEDE)

[![README CN](https://img.shields.io/badge/README-%E4%B8%AD%E6%96%87-D8E0F8?style=for-the-badge&labelColor=E0D8F8&color=D8E0F8)](/Documents/README/README.CN.MD)
[![README EN](https://img.shields.io/badge/README-EN-D8E0F8?style=for-the-badge&labelColor=E0D8F8&color=D8E0F8)](/Documents/README/README.EN.MD)

## 项目简介

NekiraReflectionLib 是一个基于 C++ 的反射工具库，提供静态反射与动态反射功能，包含一个反射生成器。

## 事项

- [x] 基本的函数萃取
- [x] 基本的变量萃取
- [x] 反射信息收集
- [x] 基本的静态反射(借助宏声明)
- [x] 基本的动态反射
- [x] 自动化扫描生成反射信息
- [x] 整理成库
- [ ] 动态反射的反射 Flag 支持
- [ ] 序列化、反序列化
- [ ] 多线程优化

## 安装

拉取下载 NekiraReflectionLib 的源码，进入根目录，依次运行如下 CMake 命令：

```powershell
cmake -S . -B build -G Ninja
```

```powershell
cmake --build build
```

将 NekiraReflectionLib 安装至 PC，可以保持默认的安装路径，也可以手动指定.

```powershell
cmake --install build [--prefix] [install_dir]
```

## 链接库

在项目中链接 NekiraReflectionLib 库，需在 CMake 中进行如下配置：

```cmake
find_package(NekiraReflectionLib REQUIRED)
```

## 文档

### NekiraReflection

[![NekiraReflection](https://img.shields.io/badge/Doc-NekiraReflection-BFCCF2?style=for-the-badge&labelColor=CCBFF2&color=BFCCF2)](/Documents/NekiraReflection/NekiraReflection.CN.MD)

### NekiraReflecTool

[![NekiraReflecTool](https://img.shields.io/badge/Doc-NekiraReflectTool-BFCCF2?style=for-the-badge&labelColor=CCBFF2&color=BFCCF2)](/Documents/NekiraReflectTool/NekiraReflectTool.CN.MD)

---

## 📜 License

[![License](https://img.shields.io/badge/License-MIT-38E575?style=for-the-badge)](/LICENSE)
