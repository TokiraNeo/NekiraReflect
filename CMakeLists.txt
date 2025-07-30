cmake_minimum_required(VERSION 3.20)
project(NekiraReflection)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBXML2_LIBRARIES "C:/libxml2-2.7.8.win32/lib/libxml2.lib")
set(LIBXML2_INCLUDE_DIR "C:/libxml2-2.7.8.win32/include")

set(LLVM_INCLUDE_DIRS "C:/llvm+clang/include")
set(LLVM_LIBRARIES "C:/llvm+clang/lib")
set(Clang_INCLUDE_DIRS "C:/llvm+clang/include")
set(Clang_LIBRARIES "C:/llvm+clang/lib")

# 查找llvm、clang库
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
find_package(LibXml2 REQUIRED)

# 添加LLVM定义和包含目录
add_definitions(${LLVM_DEFINITIONS})
# include_directories(${LLVM_INCLUDE_DIRS})

# 调试信息
message("LIBXML2_INCLUDE_DIR: ${LIBXML2_INCLUDE_DIR}")
message("LIBXML2_LIBRARIES: ${LIBXML2_LIBRARIES}")
message("LLVM_INCLUDE_DIRS: ${LLVM_INCLUDE_DIRS}")
message("LLVM_DIR: ${LLVM_DIR}")
message("LLVM_LIBRARIES: ${LLVM_LIBRARIES}")
message("Clang_INCLUDE_DIRS: ${Clang_INCLUDE_DIRS}")
message("Clang_DIR: ${Clang_DIR}")
message("Clang_LIBRARIES: ${Clang_LIBRARIES}")
message("LLVM libs: ${llvm_libs}")


add_executable(ReflectGenerator
    Generation/Generator/ReflectGenerator.cpp
)

target_include_directories(ReflectGenerator PRIVATE
    ${LLVM_INCLUDE_DIRS}
    ${Clang_INCLUDE_DIRS}
)

# 链接最少必要的库
target_link_libraries(ReflectGenerator PRIVATE
    clangAST
    clangBasic
    clangLex
    ${llvm_libs} 
)