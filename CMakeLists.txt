cmake_minimum_required(VERSION 3.10)
project(Reflection)

set(CMAKE_CXX_STANDARD 20)

add_executable(Reflection
    DynamicReflect/DynamicReflect.cpp
)

target_include_directories(Reflection PUBLIC
    ${CMAKE_SOURCE_DIR}/TypeExtraction
    ${CMAKE_SOURCE_DIR}/StaticReflect
    ${CMAKE_SOURCE_DIR}/DynamicReflect

)

# 仅安装头文件，适用于 header-only 库
install(DIRECTORY ${CMAKE_SOURCE_DIR}/StaticReflect DESTINATION include FILES_MATCHING PATTERN "*.hpp")
install(DIRECTORY ${CMAKE_SOURCE_DIR}/StaticReflect/TypeCollection DESTINATION include FILES_MATCHING PATTERN "*.hpp")

install(DIRECTORY ${CMAKE_SOURCE_DIR}/TypeExtraction DESTINATION include FILES_MATCHING PATTERN "*.hpp")

install(DIRECTORY ${CMAKE_SOURCE_DIR}/DynamicReflect DESTINATION include FILES_MATCHING PATTERN "*.hpp")
install(DIRECTORY ${CMAKE_SOURCE_DIR}/DynamicReflect/TypeCollection DESTINATION include FILES_MATCHING PATTERN "*.hpp")
install(DIRECTORY ${CMAKE_SOURCE_DIR}/DynamicReflect/TypeRegist DESTINATION include FILES_MATCHING PATTERN "*.hpp")

# 如有其他头文件目录可继续添加