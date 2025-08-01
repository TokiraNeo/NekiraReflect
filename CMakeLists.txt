cmake_minimum_required(VERSION 3.20)
project(NekiraReflection)

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

add_executable(ReflectGenerator
    Generation/Generator/ReflectGenerator.cpp
)

target_include_directories(ReflectGenerator PRIVATE
    ${LLVM_INCLUDE_DIRS}
    ${Clang_INCLUDE_DIRS}
)

# 链接最少必要的库
target_link_libraries(ReflectGenerator PRIVATE
    libclang
)