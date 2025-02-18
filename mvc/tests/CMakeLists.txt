enable_testing()

add_executable(runner_test runner_test.cpp)
target_link_libraries(runner_test PUBLIC NUMBERS_APP)

add_test(NAME RUNNER_TEST COMMAND runner_test)
#add_test(NAME NUMBERS_MODEL_TEST COMMAND numbers_model_test)
