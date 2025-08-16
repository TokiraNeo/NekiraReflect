# NekiraReflectionLib

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

### [NekiraReflection](../NekiraReflection/NekiraReflection.EN.MD)

### [NekiraReflectTool](../NekiraReflectTool/NekiraReflectTool.EN.MD)

---

## License

```
MIT License

Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
```
