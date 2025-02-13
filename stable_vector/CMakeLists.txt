add_library(STABLE_VECTOR STATIC src/stable_vector.cpp)
target_include_directories(STABLE_VECTOR PUBLIC include)

add_subdirectory(tests)
