cmake_minimum_required(VERSION 3.26)
project(glad C)

add_library(glad STATIC src/gl.c include/glad/gl.h include/KHR/khrplatform.h)

target_include_directories(glad PUBLIC include)