#pragma once

#include "TypeRegist/TypeInfoRegistry.hpp"


/** 动态反射
 *  TypeCollection/DynamicTypeInfo.hpp 定义了动态反射的信息存储类。
 *  主要实现了两类：EnumTypeInfo 和 ClassTypeInfo。
 *  同时，提供了CastDynamicTypeInfo方法，用于将 DynamicTypeInfo 转换为具体的子类。
 *
 *  TypeRegist/TypeInfoRegistry.hpp 提供了全局注册表TypeInfoRegistry，用于管理运行时类型信息。
 *  其中也包含了一些注册动态反射信息的辅助函数。
 *
 */
