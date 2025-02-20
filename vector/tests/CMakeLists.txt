enable_testing()

add_executable(vector_test vector_test.cpp catch.hpp)
target_link_libraries(vector_test VECTOR)

add_test(NAME VECTOR_TEST COMMAND vector_test)

# Таргет с санитайзерами
add_executable(vector_test_sanitized vector_test.cpp catch.hpp)
target_link_libraries(vector_test_sanitized VECTOR)

target_compile_options(vector_test_sanitized PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer -g)
target_link_options(vector_test_sanitized PRIVATE -fsanitize=address,undefined)

add_test(NAME VECTOR_TEST_SANITIZED COMMAND vector_test_sanitized)
