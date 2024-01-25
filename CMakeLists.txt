cmake_minimum_required(VERSION 3.26)
project(eogll C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/hedley)
add_subdirectory(thirdparty/stb)
add_subdirectory(thirdparty/cglm)

add_library(eogll STATIC include/eogll.h src/eogll.c)

target_include_directories(eogll PUBLIC include)

target_link_libraries(eogll glad glfw hedley stb cglm)


add_executable(eogll_test src/main.c)

target_link_libraries(eogll_test eogll)