cmake_minimum_required(VERSION 3.26)
project(stb C)

add_library(stb STATIC src/stb.c include/stb.h)

target_include_directories(stb PUBLIC include)