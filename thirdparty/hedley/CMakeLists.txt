cmake_minimum_required(VERSION 3.26)
project(hedley C)

add_library(hedley INTERFACE include/hedley.h)
target_include_directories(hedley INTERFACE include)
