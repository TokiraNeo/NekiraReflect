# =====================================
# StaticReflect/CMakeLists.txt 
# =====================================

include(GNUInstallDirs)

# Headers
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

add_library(NekiraReflectStatic INTERFACE ${HEADERS})
add_library(NekiraReflectionLib::NekiraReflectStatic ALIAS NekiraReflectStatic)

# include
target_include_directories(NekiraReflectStatic 
    INTERFACE 
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# install
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/NekiraReflect/StaticReflect
    FILES_MATCHING PATTERN "*.hpp"
)