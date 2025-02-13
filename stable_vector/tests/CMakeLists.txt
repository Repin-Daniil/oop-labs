enable_testing()

add_library(STABLE_VECTOR_INTERFACE INTERFACE)
target_include_directories(STABLE_VECTOR_INTERFACE INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_link_libraries(STABLE_VECTOR_INTERFACE INTERFACE STABLE_VECTOR)


add_executable(stable_vector_test stable_vector_test.cpp catch.hpp)
target_link_libraries(stable_vector_test STABLE_VECTOR_INTERFACE)

add_test(NAME STABLE_VECTOR_TEST COMMAND stable_vector_test)
