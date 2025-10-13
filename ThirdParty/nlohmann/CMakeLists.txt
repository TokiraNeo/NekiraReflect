# =======================================
# nlohmann/CMakeLists.txt
# =======================================

include(GNUInstallDirs)

# Headers
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

# Library
add_library(nlohmann_Json INTERFACE ${HEADERS})

# Include directories
target_include_directories(nlohmann_Json
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/ThirdParty>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/ThirdParty>
)

# Install Target
install(TARGETS nlohmann_Json
    EXPORT NekiraReflectionLibTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ThirdParty
)

# Install Headers
INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ThirdParty
    FILES_MATCHING PATTERN "*.hpp"
)

# Install LICENSE
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ThirdParty/nlohmann
)