cmake_minimum_required(VERSION 3.26)
project(glad C)

option(GLAD_DYNAMIC "Build GLAD as a shared library" OFF)

if (GLAD_DYNAMIC)
    add_library(glad SHARED src/gl.c include/glad/gl.h include/KHR/khrplatform.h)
else()
    add_library(glad STATIC src/gl.c include/glad/gl.h include/KHR/khrplatform.h)
endif()

target_include_directories(glad PUBLIC include)