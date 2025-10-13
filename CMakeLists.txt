# =====================================
# Root/CMakeLists.txt 
# =====================================

cmake_minimum_required(VERSION 3.20)
project(NekiraReflectionLib VERSION 1.0.2 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# 导入必要模块
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)



# =====================================
# 子目录、子模块
# =====================================

add_subdirectory(ThirdParty)
add_subdirectory(include/NekiraReflect)
add_subdirectory(Main)

# 添加子模块
set(SubModules 
    NekiraReflectStatic
    NekiraReflectDynamic
    NekiraReflectGen
    NekiraReflectTool
    NekiraReflectSerialize
)

# 遍历添加子模块
set(NekiraReflectModules "")

foreach(module ${SubModules})
    list(APPEND NekiraReflectModules ${module})
endforeach()

# =====================================
# 总目标
# =====================================

add_custom_target(NekiraReflectionLib)

# 将子模块添加为总目标的依赖
add_dependencies(NekiraReflectionLib ${NekiraReflectModules})

# =====================================
# install
# =====================================

# config 文件路径
set(CONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/NekiraReflectionLib)

# 创建版本配置文件
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraReflectionLibConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# 安装所有模块
install(TARGETS ${NekiraReflectModules}
    EXPORT NekiraReflectionLibTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# 指定NekiraReflectionLib的Targets.cmake文件
install(EXPORT NekiraReflectionLibTargets
    FILE NekiraReflectionLibTargets.cmake
    NAMESPACE NekiraReflectionLib::
    DESTINATION ${CONFIG_INSTALL_DIR}
)

# NekiraReflectionLib的Config.cmake配置文件
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/NekiraReflectionLibConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraReflectionLibConfig.cmake"
    INSTALL_DESTINATION ${CONFIG_INSTALL_DIR}
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR
)

# NekiraReflectStatic, NekiraReflectDynamic的Config.cmake配置文件
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/NekiraReflectionConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraReflectionConfig.cmake"
    INSTALL_DESTINATION ${CONFIG_INSTALL_DIR}
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR
)

# NekiraReflectTool的Config.cmake配置文件
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/NekiraReflectToolConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraReflectToolConfig.cmake"
    INSTALL_DESTINATION ${CONFIG_INSTALL_DIR}
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR
)

# 安装NekiraReflectionLib的配置文件和版本文件
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraReflectionLibConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraReflectionConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraReflectToolConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraReflectionLibConfigVersion.cmake"
    DESTINATION ${CONFIG_INSTALL_DIR}
)

# =====================================
# export
# =====================================

export(EXPORT NekiraReflectionLibTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/NekiraReflectionLibTargets.cmake"
    NAMESPACE NekiraReflectionLib::
)

# 导出包体为NekiraReflectionLib
export(PACKAGE NekiraReflectionLib)