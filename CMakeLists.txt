
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