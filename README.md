# NekiraReflect

## 事项

还在构建中。。。目前最新进度：

- [x] 基本的函数萃取
- [x] 基本的变量萃取
- [x] 反射信息收集
- [x] 基本的静态反射(借助宏声明)
- [ ] 基本的动态反射
- [ ] 自动化扫描生成反射信息
- [ ] 整理成库

## 项目简介

NekiraReflect 是一个基于 C++ 的反射工具库，旨在为 C++ 提供更灵活的类型信息收集与运行时反射能力。

## 特性

- 支持静态与动态反射
- 类型信息自动收集
- 支持函数与变量特征提取

## 使用示例

请参考 `ReflectMacro/ReflectMacro.cpp` 或 `TypeExtraction/TypeExtration.cpp` 了解如何使用本库。

## 命名空间

- 本库的命名空间为 `NekiraReflect`，除了宏以外，其他的类型，函数都在该命名空间中。

## 目录结构

- `DynamicReflect/` 动态反射相关头文件
- `StaticReflect/` 静态反射相关头文件
- `ReflectMacro/` 反射宏实现及示例
- `TypeExtraction/` 类型与函数特征提取
- `InfoCollection/` 反射信息收集相关

---
