cmake_minimum_required(VERSION 3.16)
project(ObserverPattern)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(OBSERVER STATIC src/observer.cpp)
target_include_directories(OBSERVER PUBLIC include)