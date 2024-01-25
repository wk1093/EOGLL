cmake_minimum_required(VERSION 3.26)
project(eogll C)


file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()


set(CMAKE_C_STANDARD 11)

add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/hedley)
add_subdirectory(thirdparty/stb)
add_subdirectory(thirdparty/cglm)

add_library(eogll STATIC include/eogll.h src/eogll.c)

target_include_directories(eogll PUBLIC include)

target_link_libraries(eogll glad glfw hedley stb cglm)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug build.")
    target_compile_definitions(eogll PUBLIC EOGLL_DEBUG)
endif()

add_executable(eogll_test examples/dragon.c)

target_link_libraries(eogll_test eogll)