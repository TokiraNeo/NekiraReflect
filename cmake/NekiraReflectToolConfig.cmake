# ========================================
# 添加反射模块
# ========================================
function(NekiraReflection_AddModule)
    # 可选项
    set(options "")
    # 反射输出目录
    set(oneValueArgs TARGET OUTPUT_DIR)
    # 需要反射的头文件、include包含路径、预定义
    set(multiValueArgs HEADERS INCLUDE_PATHS DEFINITIONS)

    # 解析参数(以NREFL_开头)
    cmake_parse_arguments(NREFL
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        ${ARGN}
    )

    # 检查必需参数
    if(NOT NREFL_TARGET)
        message(FATAL_ERROR "NekiraReflection_AddModule: TARGET is required.")
    endif()

    # 检查输出目录,若未指定则设置默认值为当前CMakeLists同级的Generated目录
    if(NOT NREFL_OUTPUT_DIR)
        set(NREFL_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Generated")
    endif()

    # 创建输出目录
    file(MAKE_DIRECTORY "${NREFL_OUTPUT_DIR}")

    # 存储反射生成的头文件、源文件
    set(GENERATED_HEADER_LIST "")
    set(GENERATED_SOURCE_LIST "")

    # 处理每个头文件
    foreach(HEADER_FILE ${NREFL_HEADERS})
        # 获取绝对路径，将HEADER_FILE相对于当前CMakeLists.txt的相对路径，进行拼接得到绝对路径
        if(NOT IS_ABSOLUTE ${HEADER_FILE})
            set(HEADER_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${HEADER_FILE}")
        endif()

        # 检查头文件是否存在
        if(NOT EXISTS ${HEADER_FILE})
            message(WARNING "Header file not found: ${HEADER_FILE}")
            continue()
        endif()

        # 获取头文件的基本名称，不含路径和扩展名
        get_filename_component(HEADER_STEM ${HEADER_FILE} NAME_WE)

        # 生成反射头文件和源文件的路径
        SET(GENERATED_HEADER "${NREFL_OUTPUT_DIR}/${HEADER_STEM}.gen.hpp")
        SET(GENERATED_SOURCE "${NREFL_OUTPUT_DIR}/${HEADER_STEM}.gen.cpp")

        # 配置NekiraReflectTool的参数
        set(REFLECT_TOOL_ARGS "")

        # 添加include路径
        if(NREFL_INCLUDE_PATHS)
            foreach (INCLUDE_PATH ${NREFL_INCLUDE_PATHS})
                list(APPEND REFLECT_TOOL_ARGS "-I${INCLUDE_PATH}")
            endforeach()
        endif()

        # 添加预处理定义
        if(NREFL_DEFINITIONS)
            foreach (DEFINITION ${NREFL_DEFINITIONS})
                list(APPEND REFLECT_TOOL_ARGS "-D${DEFINITION}")
            endforeach ()
        endif()

        # 自定义命令，调用NekiraReflectTool生成反射代码
        add_custom_command(
            OUTPUT ${GENERATED_HEADER} ${GENERATED_SOURCE}
            COMMAND NekiraReflectTool
            ARGS ${HEADER_FILE} ${NREFL_OUTPUT_DIR} ${REFLECT_TOOL_ARGS}
            # 依赖NekiraReflectTool和头文件，且只当头文件发生变化时才重新生成
            DEPENDS NekiraReflectTool ${HEADER_FILE}
            COMMENT "Generating reflection files for: ${HEADER_FILE}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        )

        # 将生成的头文件和源文件添加到列表中
        list(APPEND GENERATED_HEADER_LIST ${GENERATED_HEADER})
        list(APPEND GENERATED_SOURCE_LIST ${GENERATED_SOURCE})

    endforeach() # foreach(HEADER_FILE ${NREFL_HEADERS})

    # 将反射生成的头文件和源文件添加到自定义目标
    if(GENERATED_HEADER_LIST OR GENERATED_SOURCE_LIST)
        add_custom_target(${NREFL_TARGET}_Reflection
            DEPENDS ${GENERATED_HEADER_LIST} ${GENERATED_SOURCE_LIST}
            COMMENT "Building reflection files for: ${NREFL_TARGET}"
        )

        # 令原先的目标依赖于反射生成目标
        add_dependencies(${NREFL_TARGET} ${NREFL_TARGET}_Reflection)

        # 将生成的源文件添加到原目标
        target_sources(${NREFL_TARGET} PRIVATE ${GENERATED_SOURCE_LIST})

        # 将反射生成目录添加到原目标的include目录，用于包含生成的头文件
        target_include_directories(${NREFL_TARGET} PRIVATE ${NREFL_OUTPUT_DIR})

        # 设置目标属性，保存反射生成目录和文件列表
        set_target_properties(${NREFL_TARGET} PROPERTIES
            NEKIRA_REFLECT_GENERATED_DIR "${NREFL_OUTPUT_DIR}"
            NEKIRA_REFLECT_GENERATED_HEADERS "${GENERATED_HEADER_LIST}"
            NEKIRA_REFLECT_GENERATED_SOURCES "${GENERATED_SOURCE_LIST}"
        )

        message(STATUS "Added reflection files for: ${NREFL_TARGET}")
    endif ()

endfunction() # NekiraReflection_AddModule


# ========================================
# 清理反射生成的文件
# ========================================
function(NekiraReflection_CleanModule TARGET)
    # 获取存储在目标属性中的反射生成目录和文件列表
    get_target_property(GENERATED_DIR ${TARGET} NEKIRA_REFLECT_GENERATED_DIR)
    get_target_property(GENERATED_HEADERS ${TARGET} NEKIRA_REFLECT_GENERATED_HEADERS)
    get_target_property(GENERATED_SOURCES ${TARGET} NEKIRA_REFLECT_GENERATED_SOURCES)

    # 检查是否有生成的文件
    if(GENERATED_DIR AND (GENERATED_DIR OR GENERATED_SOURCES))
        # 添加自定义命令，调用CMake清理命令
        add_custom_target(${TARGET}_CleanReflection
            COMMAND ${CMAKE_COMMAND} -E remove ${GENERATED_HEADERS} ${GENERATED_SOURCES}
            COMMENT "Cleaning reflection files for: ${TARGET}"
        )
    endif()

    message(STATUS "Removed reflection files for: ${TARGET}")

endfunction() # NekiraReflection_CleanModule