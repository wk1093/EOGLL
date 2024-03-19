cmake_minimum_required(VERSION 3.26)
project(eogll C)

# If BUILD_EOGLL is OFF, then the examples are also not built.
# The examples are built if BUILD_EOGLL is ON and BUILD_EXAMPLES is ON.
# The docs are built if BUILD_DOCS is ON. BUILD_EOGLL does not affect the docs.
option(BUILD_EOGLL "Build EOGLL Library" ON)
option(BUILD_DOCS "Generate Docs" ON)
option(BUILD_EXAMPLES "Build Examples" ON)

# versioning
set(EOGLL_VERSION_MAJOR 0)
set(EOGLL_VERSION_MINOR 4)
set(EOGLL_VERSION_PATCH 0)

set(PROJECT_VERSION ${EOGLL_VERSION_MAJOR}.${EOGLL_VERSION_MINOR}.${EOGLL_VERSION_PATCH})
# this version goes into the header eogll_version.h
configure_file(
        "include/eogll/version.h.in"
        "${PROJECT_BINARY_DIR}/include/eogll/version.h"
)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()


set(CMAKE_C_STANDARD 11)

# allow disabling of all libraries for docs

if (BUILD_EOGLL)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    add_subdirectory(thirdparty/glad)
    add_subdirectory(thirdparty/glfw)
    add_subdirectory(thirdparty/hedley)
    add_subdirectory(thirdparty/stb)
    add_subdirectory(thirdparty/cglm)

    add_library(eogll STATIC include/eogll.h src/eogll.c
            include/eogll/input.h
            include/eogll/defines.h
            include/eogll/logging.h
            include/eogll/util.h
            include/eogll/window.h
            include/eogll/shader.h
            include/eogll/pch.h
            include/eogll/gl.h
            include/eogll/attrib_builder.h
            include/eogll/buffer_object.h
            include/eogll/texture.h
            include/eogll/transforms.h
            include/eogll/camera.h
            include/eogll/obj_loader.h
            src/version.c
            src/util.c
            src/window.c
            src/shader.c
            src/gl.c
            src/attrib_builder.c
            src/buffer_object.c
            src/texture.c
            src/transforms.c
            src/camera.c
            src/obj_loader.c)

    target_include_directories(eogll PUBLIC include ${PROJECT_BINARY_DIR}/include)

    target_link_libraries(eogll glad glfw hedley stb cglm)

    if (CMAKE_BUILD_TYPE MATCHES Debug)
        message("Debug build.")
        target_compile_definitions(eogll PUBLIC EOGLL_DEBUG)
    endif()


        if (BUILD_EXAMPLES)
            add_subdirectory(examples)
        endif()

endif()

IF(BUILD_DOCS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/docs)
ENDIF()