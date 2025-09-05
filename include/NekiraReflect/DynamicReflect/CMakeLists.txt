# =====================================
# DynamicReflect/CMakeLists.txt 
# =====================================

include(GNUInstallDirs)

# Headers, Sources
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/source/DynamicReflect/*.cpp")

add_library(NekiraReflectDynamic SHARED ${HEADERS} ${SOURCES})
add_library(NekiraReflectionLib::NekiraReflectDynamic ALIAS NekiraReflectDynamic)

# include
target_include_directories(NekiraReflectDynamic
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# install
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/NekiraReflect/DynamicReflect
    FILES_MATCHING PATTERN "*.hpp"
)