cmake_minimum_required(VERSION 3.16)
project(OOP_LABS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "/Users/daniilr/Develop/qt")


add_library(NUMBERS_MODEL STATIC src/model/model.cpp src/model/observer/observer.cpp)
target_include_directories(NUMBERS_MODEL PUBLIC src/model)
target_link_libraries(NUMBERS_MODEL PUBLIC LOGGER)

add_library(NUMBERS_UTILS STATIC src/utils/runner/runners.cpp src/utils/runner/runner.cpp src/utils/storage/storage.cpp)
target_include_directories(NUMBERS_UTILS PUBLIC src/)
target_link_libraries(NUMBERS_UTILS PUBLIC NUMBERS_MODEL)



add_library(NUMBERS_APP STATIC src/app/application.cpp src/gui/ui.cpp src/gui/ui.hpp)
target_link_libraries(NUMBERS_APP PUBLIC NUMBERS_MODEL NUMBERS_UTILS Qt::Core Qt::Gui Qt::Widgets)
target_include_directories(NUMBERS_APP PUBLIC src/)


find_package(Qt6 COMPONENTS Core gui Widgets REQUIRED)

add_executable(numbers main.cpp src/gui/form.cpp)

target_link_libraries(numbers NUMBERS_APP)

enable_testing()
add_subdirectory(tests)