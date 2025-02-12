enable_testing()

add_library(STABLE_VECTOR_TEST INTERFACE)
target_include_directories(STABLE_VECTOR_TEST INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_link_libraries(STABLE_VECTOR_TEST INTERFACE STABLE_VECTOR)


add_executable(stable_vector_test stable_vector_test.cpp catch.hpp)
target_link_libraries(stable_vector_test STABLE_VECTOR_TEST)