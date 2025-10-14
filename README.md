<h1 align="center">
    <b>NekiraReflectionLib</b>
</h1>

<div align="center">

<img alt="GitHub License"
src="https://img.shields.io/github/license/TokiraNeo/NekiraReflect?style=flat-square&labelColor=363a4f&color=b7bdf8">
<img alt="GitHub top language"
src="https://img.shields.io/github/languages/top/TokiraNeo/NekiraReflect?style=flat-square&labelColor=363a4f&color=b7bdf8">
<img alt="C++" 
src="https://img.shields.io/badge/C%2B%2B-%3E%3D20-b7bdf8?style=flat-square&logo=cplusplus&labelColor=363a4f&color=b7bdf8">
<img alt="CMake" 
src="https://img.shields.io/badge/CMake-%3E%3D3.20-b7bdf8?style=flat-square&logo=cmake&labelColor=363a4f&color=b7bdf8">
<img alt="GitHub commit activity (branch)" 
src="https://img.shields.io/github/commit-activity/m/TokiraNeo/NekiraReflect/main?style=flat-square&logo=github&labelColor=363a4f&color=b7bdf8">

</div>

<div align="center">

[![README CN](https://img.shields.io/badge/README-%E4%B8%AD%E6%96%87-D8E0F8?style=for-the-badge&labelColor=363a4f&color=b7bdf8)](/Documents/README/README.CN.MD)
[![README EN](https://img.shields.io/badge/README-EN-D8E0F8?style=for-the-badge&labelColor=363a4f&color=b7bdf8)](/Documents/README/README.EN.MD)

</div>

> [!Important]
>
> ### ThirdParty
>
> - [nlohmann Json](https://github.com/nlohmann/json)
> - [LibClang](https://github.com/llvm/llvm-project)

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

### NekiraReflectStatic

[![NekiraReflectStatic](https://img.shields.io/badge/Doc-NekiraReflectStatic-BFCCF2?style=for-the-badge&labelColor=363a4f&color=b7bdf8)](/Documents/NekiraReflectStatic/NekiraReflectStatic.CN.MD)

### NekiraReflectDynamic

[![NekiraReflectDynamic](https://img.shields.io/badge/Doc-NekiraReflectDynamic-BFCCF2?style=for-the-badge&labelColor=363a4f&color=b7bdf8)](/Documents/NekiraReflectDynamic/NekiraReflectDynamic.CN.MD)

### NekiraReflecTool

[![NekiraReflecTool](https://img.shields.io/badge/Doc-NekiraReflectTool-BFCCF2?style=for-the-badge&labelColor=363a4f&color=b7bdf8)](/Documents/NekiraReflectTool/NekiraReflectTool.CN.MD)

---

## 📜 License

[![License](https://img.shields.io/badge/License-MIT-38E575?style=for-the-badge)](/LICENSE)
