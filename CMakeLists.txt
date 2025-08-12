cmake_minimum_required(VERSION 3.20)
project(NekiraReflection VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
# 核心库定义
# =============================================================================

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 添加头文件
file(GLOB_RECURSE CORE_HEADERS
    "include/NekiraReflect/*.hpp"
)

# 收集源文件
file(GLOB_RECURSE CORE_SOURCES
    "source/*.cpp"
)

# 创建核心库
add_library(NekiraReflection ${CORE_HEADERS} ${CORE_SOURCES})
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
        ${CMAKE_CURRENT_SOURCE_DIR}/include/NekiraReflect/DynamicReflect
        ${CMAKE_CURRENT_SOURCE_DIR}/include/NekiraReflect/StaticReflect
        ${CMAKE_CURRENT_SOURCE_DIR}/include/NekiraReflect/TypeExtraction
        ${CMAKE_CURRENT_SOURCE_DIR}/include/NekiraReflect/Generation
        ${LLVM_INCLUDE_DIRS}
        ${Clang_INCLUDE_DIRS}
)

# =============================================================================
# 反射生成工具
# =============================================================================

# 生成工具可执行文件
add_executable(NekiraReflectTool
    ${CMAKE_CURRENT_SOURCE_DIR}/Main/NekiraReflectTool.cpp
)

# 配置包含目录
target_include_directories(NekiraReflectTool PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/NekiraReflect/DynamicReflect
    ${CMAKE_CURRENT_SOURCE_DIR}/include/NekiraReflect/StaticReflect
    ${CMAKE_CURRENT_SOURCE_DIR}/include/NekiraReflect/TypeExtraction
    ${CMAKE_CURRENT_SOURCE_DIR}/include/NekiraReflect/Generation
    ${LLVM_INCLUDE_DIRS}
    ${Clang_INCLUDE_DIRS}
)

# 链接库
target_link_libraries(NekiraReflectTool PRIVATE
    NekiraReflection::NekiraReflection
    libclang
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

# 安装库和反射生成器
install(TARGETS NekiraReflection NekiraReflectTool
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