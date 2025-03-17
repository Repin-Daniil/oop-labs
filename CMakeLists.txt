cmake_minimum_required(VERSION 3.16)
project(OOP_LABS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third_party/symcpp)

enable_testing()

add_subdirectory(cpp)
add_subdirectory(mvc)
add_subdirectory(vector)