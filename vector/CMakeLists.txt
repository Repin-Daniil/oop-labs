add_library(VECTOR STATIC src/vector.cpp)
target_include_directories(VECTOR PUBLIC include)

add_subdirectory(tests)
