# =====================================
# Main/CMakeLists.txt 
# =====================================

include(GNUInstallDirs)

add_executable(NekiraReflectTool NekiraReflectTool.cpp)
add_executable(NekiraReflectionLib::NekiraReflectTool ALIAS NekiraReflectTool)

# include
target_include_directories(NekiraReflectTool 
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# link libraries
target_link_libraries(NekiraReflectTool 
    PRIVATE 
        NekiraReflectGen
)