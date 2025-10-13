# =======================================
# nlohmann/CMakeLists.txt
# =======================================

include(GNUInstallDirs)

# Headers
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

# Library
add_library(nlohmann_json INTERFACE ${HEADERS})

# Include directories
target_include_directories(nlohmann_json
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/ThirdParty>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/NekiraReflect/ThirdParty>
)

# Installation
INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/NekiraReflect/ThirdParty
    FILES_MATCHING PATTERN "*.hpp"
)

# install LICENSE
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/NekiraReflect/ThirdParty/nlohmann
)