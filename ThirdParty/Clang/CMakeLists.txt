# =================================
# Clang/CMakeLists.txt
# =================================

list(APPEND CMAKE_PREFIX_PATH ${CLANG_CMAKE_DIR})

find_package(Clang REQUIRED CONFIG)

# 调试信息
#message("LIBXML2_INCLUDE_DIR: ${LIBXML2_INCLUDE_DIR}")
#message("LIBXML2_LIBRARIES: ${LIBXML2_LIBRARIES}")
message("LLVM_INCLUDE_DIRS: ${LLVM_INCLUDE_DIRS}")
message("LLVM_DIR: ${LLVM_DIR}")
#message("LLVM_LIBRARIES: ${LLVM_LIBRARIES}")
#message("Clang_INCLUDE_DIRS: ${Clang_INCLUDE_DIRS}")
message("Clang_DIR: ${Clang_DIR}")
#message("Clang_LIBRARIES: ${Clang_LIBRARIES}")

# install LICENSE
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ThirdParty/Clang
)