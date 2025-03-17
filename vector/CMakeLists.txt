enable_testing()

add_executable(vector_test tests/vector_test.cpp tests/catch.hpp)
target_include_directories(vector_test PUBLIC include)

add_test(NAME VECTOR_TEST COMMAND vector_test)

if (NOT WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(vector_test_sanitized tests/vector_test.cpp tests/catch.hpp)
    target_include_directories(vector_test_sanitized PUBLIC include)

    target_compile_options(vector_test_sanitized PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer -g)
    target_link_options(vector_test_sanitized PRIVATE -fsanitize=address,undefined)

    add_test(NAME VECTOR_TEST_SANITIZED COMMAND vector_test_sanitized)
endif()
