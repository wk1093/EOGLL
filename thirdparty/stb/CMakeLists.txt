cmake_minimum_required(VERSION 3.26)
project(stb C)

option(STB_DYNAMIC "Build STB as a shared library" OFF)

if (STB_DYNAMIC)
    add_library(stb SHARED src/stb.c include/stb.h)
else()
    add_library(stb STATIC src/stb.c include/stb.h)
endif()

target_include_directories(stb PUBLIC include)