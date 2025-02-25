cmake_minimum_required(VERSION 3.16)
project(OOP_LABS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "/Users/daniilr/Develop/qt")


add_library(CIRCLES_MODEL STATIC
        src/model/geometry/circle.cpp
        src/model/circles.cpp)
target_include_directories(CIRCLES_MODEL PUBLIC src/model)
target_link_libraries(CIRCLES_MODEL PUBLIC LOGGER OBSERVER)


add_library(CIRCLES_APP STATIC src/app/application.cpp src/view/gui/ui.cpp  src/view/form/form.cpp)
target_link_libraries(CIRCLES_APP PUBLIC CIRCLES_MODEL CIRCLES_UTILS Qt::Core Qt::Gui Qt::Widgets)
target_include_directories(CIRCLES_APP PUBLIC src/)


find_package(Qt6 COMPONENTS Core gui Widgets REQUIRED)

add_executable(circles main.cpp)

target_link_libraries(circles CIRCLES_APP)

enable_testing()
add_subdirectory(tests)