add_library(NUMBERS_MODEL STATIC model/model.cpp model/observer/observer.cpp)
target_include_directories(NUMBERS_MODEL PUBLIC model)

enable_testing()

add_executable(numbers main.cpp infrastructure/storage/storage.cpp)
target_link_libraries(numbers PUBLIC NUMBERS_MODEL)

#add_test(NAME NUMBERS_MODEL_TEST COMMAND numbers_model_test)
