cmake_minimum_required(VERSION 3.26)
project(eogll)

# If BUILD_EOGLL is OFF, then the examples are also not built.
# The examples are built if BUILD_EOGLL is ON and BUILD_EXAMPLES is ON.
# The docs are built if BUILD_DOCS is ON. BUILD_EOGLL does not affect the docs.
option(BUILD_EOGLL "Build EOGLL Library" ON)
option(BUILD_DOCS "Generate Docs" ON)
option(BUILD_EXAMPLES "Build Examples" ON)

# versioning
set(EOGLL_VERSION_MAJOR 0)
set(EOGLL_VERSION_MINOR 8)
set(EOGLL_VERSION_PATCH 1)

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
    include(FetchContent)

    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
    add_subdirectory(thirdparty/glad)

    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG 3.3.4
    )
    FetchContent_MakeAvailable(glfw)

    FetchContent_Declare(
            hedley
            GIT_REPOSITORY https://github.com/nemequ/hedley.git
            GIT_TAG v15
    )
    FetchContent_MakeAvailable(hedley)
    add_library(hedley INTERFACE IMPORTED)
    target_include_directories(hedley INTERFACE ${hedley_SOURCE_DIR})

    add_subdirectory(thirdparty/stb)
    FetchContent_Declare(
            cglm
            GIT_REPOSITORY https://github.com/recp/cglm.git
            GIT_TAG v0.9.4
    )
    FetchContent_MakeAvailable(cglm)

    FetchContent_Declare(
            assimp
            GIT_REPOSITORY https://github.com/assimp/assimp.git
            GIT_TAG v5.4.3
    )
    FetchContent_MakeAvailable(assimp)
    target_compile_options(assimp PRIVATE -Wno-error=pedantic -Wno-error=unknown-pragmas)

    FetchContent_Declare(
            glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG 1.0.1
    )
    FetchContent_MakeAvailable(glm)

    add_library(eogll STATIC include/eogll.h
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
            include/eogll/framebuffer.h
            src/eogll/version.c
            src/eogll/util.c
            src/eogll/window.c
            src/eogll/shader.c
            src/eogll/gl.c
            src/eogll/attrib_builder.c
            src/eogll/buffer_object.c
            src/eogll/texture.c
            src/eogll/transforms.c
            src/eogll/camera.c
            src/eogll/obj_loader.c
            src/eogll/framebuffer.c
            src/eogll/eogll.c)
    target_include_directories(eogll PUBLIC include ${PROJECT_BINARY_DIR}/include)

    target_link_libraries(eogll glad glfw hedley stb cglm)

    if (CMAKE_BUILD_TYPE MATCHES Debug)
        message("Debug build.")
        target_compile_definitions(eogll PUBLIC EOGLL_DEBUG)
    endif()

    if (BUILD_EXAMPLES)
        add_subdirectory(examples)
    endif()

    add_library(hogll STATIC include/hogll.hpp
            include/hogll/pch.hpp
            include/hogll/window.hpp
            include/hogll/bufferobj.hpp
            include/hogll/objectattrs.hpp
            include/hogll/transforms.hpp
            include/hogll/shadergen.hpp
            include/hogll/model.hpp
            src/hogll/window.cpp
            src/hogll/bufferobj.cpp
            src/hogll/objectattrs.cpp
            src/hogll/transforms.cpp
            src/hogll/shadergen.cpp
            src/hogll/model.cpp)
    target_include_directories(hogll PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include ${PROJECT_SOURCE_DIR}/thirdparty/glm)
    target_link_libraries(hogll eogll assimp glm)
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        target_compile_definitions(hogll PUBLIC EOGLL_DEBUG)
    endif()


endif()

IF(BUILD_DOCS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/docs)
ENDIF()