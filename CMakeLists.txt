cmake_minimum_required(VERSION 3.10)
project(Reflection)

set(CMAKE_CXX_STANDARD 23)

add_executable(Reflection
    ReflectMacro/ReflectMacro.cpp
)

target_include_directories(Reflection PUBLIC
    ${CMAKE_SOURCE_DIR}/TypeExtration
    ${CMAKE_SOURCE_DIR}/InfoCollection
    ${CMAKE_SOURCE_DIR}/ReflectMacro
)

# 仅安装头文件，适用于 header-only 库
install(DIRECTORY ${CMAKE_SOURCE_DIR}/TypeExtraction DESTINATION include FILES_MATCHING PATTERN "*.hpp")
install(DIRECTORY ${CMAKE_SOURCE_DIR}/InfoCollection DESTINATION include FILES_MATCHING PATTERN "*.hpp")
install(DIRECTORY ${CMAKE_SOURCE_DIR}/ReflectMacro DESTINATION include FILES_MATCHING PATTERN "*.hpp")
# 如有其他头文件目录可继续添加