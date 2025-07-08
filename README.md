# NekiraReflect

## 项目简介

NekiraReflect 是一个基于 C++ 的反射工具库，旨在为 C++ 提供更灵活的类型信息收集与运行时反射能力。

## 特性

- 支持静态与动态反射
- 类型信息自动收集
- 支持函数与变量特征提取

## 安装与构建

本项目推荐使用 CMake 进行构建：

```bash
# 1. 生成构建文件
cmake -S . -B build
# 2. 编译
cmake --build build
```

或直接使用 g++ 编译单个文件：

```bash
g++ -std=c++23 -g 源文件.cpp -o 输出文件.exe
```

## 使用示例

请参考 `ReflectMacro/ReflectMacro.cpp` 或 `TypeExtraction/TypeExtration.cpp` 了解如何使用本库。

## 目录结构

- `DynamicReflect/` 动态反射相关头文件
- `StaticReflect/` 静态反射相关头文件
- `ReflectMacro/` 反射宏实现及示例
- `TypeExtraction/` 类型与函数特征提取
- `InfoCollection/` 反射信息收集相关

## 依赖

- C++23 编译器（如 g++ 13+）
- CMake（可选）

## 许可证

MIT License

---

如有建议或问题，欢迎提交 issue 或 PR。
