# NekiraReflectTool

## Overview

NekiraReflectTool is a tool responsible for scanning header files and generating dynamic reflection code.

## Usage

NekiraReflectTool scans specified header files, identifies reflection macros, and generates corresponding `gen.hpp` and `gen.cpp` files.

### Command Line Invocation (Not Recommended)

You can invoke NekiraReflectTool manually via the command line, although this is not the recommended approach. This section is for demonstration purposes only.

After installing the NekiraReflectionLib library, add the `bin` folder path from the installation directory to your system environment variables so that the system can locate `NekiraReflectTool.exe`.

When invoking NekiraReflectTool manually from the command line, **you must provide the header file path and the output path**. Both paths must be **absolute paths**, and **the order cannot be changed**.

#### Help Command

```powershell
NekiraReflectTool -help
```

#### Manually Scan and Generate Reflection Files

```powershell
NekiraReflectTool <input_header> <output_dir> [options]
```

### CMake Configuration (Highly Recommended)

Configuring NekiraReflectTool via CMake allows you to modularly set up reflection for each module.

If you have multiple modules, you can configure reflection for each module individually in its root CMakeLists file. NekiraReflectTool can generate separate reflection code for each module and perform related automation tasks.

#### CMake Functions

NekiraReflectTool provides two CMake functions:

##### NekiraReflection_AddModule()

`NekiraReflection_AddModule()` informs NekiraReflectTool of the reflection configuration for the current module. Main parameters:

- **TARGET**: The target module to add reflection info to; can be an executable, library, etc.

- **OUTPUT_DIR**: Output path for reflection code, which will be added to the **TARGET**'s include path. Default is `${CMAKE_CURRENT_SOURCE_DIR}/Generated`.

- **HEADERS**: Header files to scan. NekiraReflectTool will scan for reflection macros and generate corresponding `gen.hpp` and `gen.cpp` files.

- **INCLUDE_PATHS**: Similar to `target_include_directories()`, tells NekiraReflectTool which include search paths to use. NekiraReflectTool automatically includes NekiraReflection's include path, so `${NekiraReflection_INCLUDE_DIRS}` can be omitted.

- **DEFINITIONS**: Preprocessor macros, e.g., `DEBUG`.

- **OPTIONS**: Other optional parameters, e.g., `-std=c++20`. **(Note: If the scanned header file is a `.h` C++ header, you must add `-x c++`, otherwise it will be treated as a C header and may cause syntax errors.)**

---

#### NekiraReflection_CleanModule()

`NekiraReflection_CleanModule()` tells NekiraReflectTool to clean up the reflection code generated for the current module. Usually, you don't need to use this function.

- **TARGET**: Specifies the module to clean reflection code for; can be an executable, library, etc.

#### Example

Suppose the project has two modules: Core and Math

```cmake
# Core/CMakeLists.txt

file(GLOB_RECURSE CORE_HEADERS Public/*.h Public/*.hpp)
file(GLOB_RECURSE CORE_SOURCES Private/*.cpp)

add_library(Core ${CORE_HEADERS} ${CORE_SOURCES})

target_link_libraries(Core PRIVATE
        NekiraReflection
)

target_include_directories(Core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
        PRIVATE
        ${NekiraReflection_INCLUDE_DIRS})


NekiraReflection_AddModule(
        TARGET Core
        HEADERS ${CORE_HEADERS}
        INCLUDE_PATHS
        OPTIONS -std=c++20 -fsyntax-only -x c++
)
```

---

```cmake
# Math/CMakeLists.txt

file(GLOB_RECURSE MATH_HEADERS "Public/*.h" "Public/*.hpp")
file(GLOB_RECURSE MATH_SOURCES "Private/*.cpp")

add_library(Math ${MATH_HEADERS} ${MATH_SOURCES})

target_link_libraries(Math PRIVATE NekiraReflection)

target_include_directories(Math PRIVATE ${NekiraReflection_INCLUDE_DIRS})

NekiraReflection_AddModule(
        TARGET Math
        HEADERS ${MATH_HEADERS}
        INCLUDE_PATHS
        OPTIONS -std=c++20 -fsyntax-only -x c++
)
```
