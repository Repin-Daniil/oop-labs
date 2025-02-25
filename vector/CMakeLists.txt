add_library(VECTOR STATIC src/vector.cpp)
target_include_directories(VECTOR PUBLIC include)

add_executable(vector_run vector_run.cpp)
target_link_libraries(vector_run VECTOR)

add_executable(vector_run_sanitized vector_run.cpp)
target_link_libraries(vector_run_sanitized VECTOR)

target_compile_options(vector_run_sanitized PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer -g)
target_link_options(vector_run_sanitized PRIVATE -fsanitize=address,undefined)

add_subdirectory(tests)
