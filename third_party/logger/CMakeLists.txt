cmake_minimum_required(VERSION 3.16)
project(LOG)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(LOGGER STATIC src/log.cpp)
target_include_directories(LOGGER PUBLIC include)