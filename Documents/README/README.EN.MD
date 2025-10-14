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

## Introduction

NekiraReflectionLib is a C++ Reflection Utilities Library, including static reflection, dynamic reflection, type traits, and a reflection generation tool.

## Tasks

- [x] Basic function extraction
- [x] Basic variable extraction
- [x] Reflection information collection
- [x] Basic static reflection (using macro declarations)
- [x] Basic dynamic reflection
- [x] Automated scanning and generation of reflection information
- [x] Organize into a library
- [ ] Reflection Flag support for dynamic reflection
- [ ] Serialization and deserialization
- [ ] Multithreading optimization

## Installation

Clone and download the source code of NekiraReflectionLib, enter the root directory, and run the following CMake commands in order:

```powershell
cmake -S . -B build -G Ninja
```

```powershell
cmake --build build
```

To install NekiraReflectionLib on your PC, you can keep the default installation path or specify it manually. After installation, add the `bin` folder path from the NekiraReflect installation directory to your environment variables so the system can find `NekiraReflectTool.exe`.

```powershell
cmake --install build [--prefix] [install_dir]
```

## Linking the Library

To link the NekiraReflectionLib library in your project, configure CMake as follows:

```cmake
find_package(NekiraReflectionLib REQUIRED)
```

## Documentation

### NekiraReflectStatic

[![NekiraReflectStatic](https://img.shields.io/badge/Doc-NekiraReflectStatic-BFCCF2?style=for-the-badge&labelColor=363a4f&color=b7bdf8)](/Documents/NekiraReflectStatic/NekiraReflectStatic.EN.MD)

### NekiraReflectDynamic

[![NekiraReflectDynamic](https://img.shields.io/badge/Doc-NekiraReflectDynamic-BFCCF2?style=for-the-badge&labelColor=363a4f&color=b7bdf8)](/Documents/NekiraReflectDynamic/NekiraReflectDynamic.EN.MD)

### NekiraReflecTool

[![NekiraReflecTool](https://img.shields.io/badge/Doc-NekiraReflectTool-BFCCF2?style=for-the-badge&labelColor=363a4f&color=b7bdf8)](/Documents/NekiraReflectTool/NekiraReflectTool.EN.MD)

---

## 📜 License

[![License](https://img.shields.io/badge/License-MIT-38E575?style=for-the-badge)](/LICENSE)
