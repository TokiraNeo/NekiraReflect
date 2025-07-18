cmake_minimum_required(VERSION 3.20)
project(NekiraReflection)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(NekiraReflectExec
    DynamicReflect/DynamicReflect.cpp
    StaticReflect/StaticReflect.cpp
)

set(HEADER_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/DynamicReflect
    ${CMAKE_CURRENT_SOURCE_DIR}/StaticReflect
    ${CMAKE_CURRENT_SOURCE_DIR}/TypeExtraction
)

add_library(NekiraReflection INTERFACE)
target_include_directories(NekiraReflection INTERFACE ${HEADER_DIRS})


target_link_libraries(NekiraReflectExec INTERFACE NekiraReflection)