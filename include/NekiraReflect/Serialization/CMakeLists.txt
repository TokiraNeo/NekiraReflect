# =====================================
# Serialization/CMakeLists.txt 
# =====================================

include(GNUInstallDirs)

# Headers
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
# Sources
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/source/Serialization/*.cpp")

add_library(NekiraReflectSerialize STATIC ${HEADERS} ${SOURCES})
add_library(NekiraReflectionLib::NekiraReflectSerialize ALIAS NekiraReflectSerialize)

# include
target_include_directories(NekiraReflectSerialize 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# install
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/NekiraReflect/Serialization
    FILES_MATCHING PATTERN "*.hpp"
)