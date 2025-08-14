cmake_minimum_required(VERSION 3.20)
project(NekiraReflection VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 查找llvm、clang库
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

# 调试信息
message("LIBXML2_INCLUDE_DIR: ${LIBXML2_INCLUDE_DIR}")
message("LIBXML2_LIBRARIES: ${LIBXML2_LIBRARIES}")
message("LLVM_INCLUDE_DIRS: ${LLVM_INCLUDE_DIRS}")
message("LLVM_DIR: ${LLVM_DIR}")
message("LLVM_LIBRARIES: ${LLVM_LIBRARIES}")
message("Clang_INCLUDE_DIRS: ${Clang_INCLUDE_DIRS}")
message("Clang_DIR: ${Clang_DIR}")
message("Clang_LIBRARIES: ${Clang_LIBRARIES}")

# =============================================================================
# 反射类型注册表库定义
# =============================================================================

# 添加头文件
file(GLOB_RECURSE REGISTRY_HEADERS
    "include/NekiraReflect/Registry/*.hpp"
)

# 收集源文件
file(GLOB_RECURSE REGISTRY_SOURCES
    "source/Registry/*.cpp"
)

# 创建反射类型注册表库(这里使用动态库，避免多个静态实例)
add_library(NekiraReflectRegistry SHARED ${REGISTRY_HEADERS} ${REGISTRY_SOURCES})
add_library(NekiraReflect::Registry ALIAS NekiraReflectRegistry)

# 配置包含目录
target_include_directories(NekiraReflectRegistry
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>

        ${CMAKE_CURRENT_SOURCE_DIR}/include/NekiraReflect/Registry
)

# =============================================================================
# 核心库定义
# =============================================================================

# 添加头文件
file(GLOB_RECURSE CORE_HEADERS
    "include/NekiraReflect/TypeExtraction/*.hpp"
    "include/NekiraReflect/DynamicReflect/*.hpp"
    "include/NekiraReflect/StaticReflect/*.hpp"
    "include/NekiraReflect/Core.hpp"
)

# 收集源文件
file(GLOB_RECURSE CORE_SOURCES
    "source/DynamicReflect/*.cpp"
)


# 创建核心库
add_library(NekiraReflection SHARED ${CORE_HEADERS} ${CORE_SOURCES})
add_library(NekiraReflection::NekiraReflection ALIAS NekiraReflection)

# 设置目标属性
set_target_properties(NekiraReflection PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
)

# 配置包含目录
target_include_directories(NekiraReflection
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/NekiraReflect/TypeExtraction
        ${CMAKE_CURRENT_SOURCE_DIR}/include/NekiraReflect/DynamicReflect
        ${CMAKE_CURRENT_SOURCE_DIR}/include/NekiraReflect/StaticReflect
        ${CMAKE_CURRENT_SOURCE_DIR}/include/NekiraReflect/Registry
)

# 链接库
target_link_libraries(NekiraReflection PRIVATE
    NekiraReflectRegistry
)

# =============================================================================
# 反射生成库
# =============================================================================

# 添加头文件
file(GLOB_RECURSE GEN_HEADERS
    "include/NekiraReflect/Generation/*.hpp"
)

# 收集源文件
file(GLOB_RECURSE GEN_SOURCES
    "source/Generation/*.cpp"
)

# 创建反射生成库
add_library(NekiraReflectGen STATIC ${GEN_HEADERS} ${GEN_SOURCES})
add_library(NekiraReflection::NekiraReflectGen ALIAS NekiraReflectGen)

# 包含目录
target_include_directories(NekiraReflectGen PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>

    ${CMAKE_CURRENT_SOURCE_DIR}/include/NekiraReflect/Generation
    ${LLVM_INCLUDE_DIRS}
    ${Clang_INCLUDE_DIRS}
)

# 依赖库
target_link_libraries(NekiraReflectGen PRIVATE
    libclang
)

# =============================================================================
# 反射生成工具
# =============================================================================

# 生成工具可执行文件
add_executable(NekiraReflectTool
    ${CMAKE_CURRENT_SOURCE_DIR}/Main/NekiraReflectTool.cpp
)
add_executable(NekiraReflection::NekiraReflectTool ALIAS NekiraReflectTool)

# 配置包含目录
target_include_directories(NekiraReflectTool PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_CURRENT_SOURCE_DIR}/include/NekiraReflect/Generation
)

# 链接库
target_link_libraries(NekiraReflectTool PRIVATE
    NekiraReflection
    NekiraReflectGen
)

# =============================================================================
# 包含反射生成工具配置
# =============================================================================

# 将cmake目录添加到CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# 包含反射生成工具的配置文件
include(NekiraReflectToolConfig)

# =============================================================================
# 安装配置
# =============================================================================

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# 安装反射库、反射注册表库、反射生成库、反射生成工具
install(TARGETS NekiraReflectRegistry NekiraReflection NekiraReflectGen NekiraReflectTool
    EXPORT NekiraReflectionTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# 安装头文件
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
)

# 配置文件目录
set(CONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/NekiraReflection)

# 安装反射生成器配置
install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/NekiraReflectToolConfig.cmake"
    DESTINATION ${CONFIG_INSTALL_DIR}
)

# 导出目标
install(EXPORT NekiraReflectionTargets
    FILE NekiraReflectionTargets.cmake
    NAMESPACE NekiraReflection::
    DESTINATION ${CONFIG_INSTALL_DIR}
)

# 创建配置文件
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/NekiraReflectionConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraReflectionConfig.cmake"
    INSTALL_DESTINATION ${CONFIG_INSTALL_DIR}
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR
)

# 创建版本文件
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraReflectionConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# 安装配置文件
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraReflectionConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraReflectionConfigVersion.cmake"
    DESTINATION ${CONFIG_INSTALL_DIR}
)

# =============================================================================
# 导出
# =============================================================================

export(EXPORT NekiraReflectionTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/NekiraReflectionTargets.cmake"
    NAMESPACE NekiraReflection::
)

export(PACKAGE NekiraReflection)