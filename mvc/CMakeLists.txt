add_library(NUMBERS_MODEL STATIC model/model.cpp model/observer/observer.cpp)
target_include_directories(NUMBERS_MODEL PUBLIC model)

enable_testing()

add_executable(numbers_model_test tests/model_test.cpp tests/catch.hpp)
target_link_libraries(numbers_model_test PUBLIC NUMBERS_MODEL)
add_test(NAME NUMBERS_MODEL_TEST COMMAND numbers_model_test)
