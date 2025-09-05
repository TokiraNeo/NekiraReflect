# =====================================
# Generation/CMakeLists.txt 
# =====================================

include(GNUInstallDirs)

# Headers, Sources
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/source/Generation/*.cpp")

add_library(NekiraReflectGen STATIC ${HEADERS} ${SOURCES})
add_library(NekiraReflectionLib::NekiraReflectGen ALIAS NekiraReflectGen)

# include
target_include_directories(NekiraReflectGen
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${LLVM_INCLUDE_DIRS}
        ${Clang_INCLUDE_DIRS}
)

# link libraries
target_link_libraries(NekiraReflectGen
    PRIVATE
        libclang
)

# install
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/NekiraReflect/Generation
    FILES_MATCHING PATTERN "*.hpp"
)