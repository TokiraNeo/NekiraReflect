<h1 align="center">
    <b>NekiraReflectionLib</b>
</h1>

![GitHub License](https://img.shields.io/github/license/TokiraNeo/NekiraReflect?style=flat-square&labelColor=2EA2EF&color=2EEFDC)
![GitHub top language](https://img.shields.io/github/languages/top/TokiraNeo/NekiraReflect?style=flat-square&labelColor=29F5BB&color=29C9F5)
![C++ std](https://img.shields.io/badge/C%2B%2B_std-%3E%3D20-%23FF5C9A?style=flat-square&labelColor=%23C988F7)
![CMake Version](https://img.shields.io/badge/CMake-%3E%3D3.20-8EFF80?style=flat-square&labelColor=CEFF80)
![GitHub commit activity (branch)](https://img.shields.io/github/commit-activity/m/TokiraNeo/NekiraReflect/main?style=flat-square&labelColor=91CBED&color=A0AEDE)

[![README CN](https://img.shields.io/badge/README-%E4%B8%AD%E6%96%87-D8E0F8?style=for-the-badge&labelColor=E0D8F8&color=D8E0F8)](/Documents/README/README.CN.MD)
[![README EN](https://img.shields.io/badge/README-EN-D8E0F8?style=for-the-badge&labelColor=E0D8F8&color=D8E0F8)](/Documents/README/README.EN.MD)

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

### NekiraReflection

[![NekiraReflection](https://img.shields.io/badge/Doc-NekiraReflection-BFCCF2?style=for-the-badge&labelColor=CCBFF2&color=BFCCF2)](/Documents/NekiraReflection/NekiraReflection.EN.MD)

### NekiraReflecTool

[![NekiraReflecTool](https://img.shields.io/badge/Doc-NekiraReflectTool-BFCCF2?style=for-the-badge&labelColor=CCBFF2&color=BFCCF2)](/Documents/NekiraReflectTool/NekiraReflectTool.EN.MD)

---

## 📜 License

[![License](https://img.shields.io/badge/License-MIT-38E575?style=for-the-badge)](/LICENSE)
