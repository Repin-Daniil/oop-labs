set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "/Users/daniilr/Develop/qt")

add_library(NUMBERS_MODEL STATIC model/model.cpp model/observer/observer.cpp)
target_include_directories(NUMBERS_MODEL PUBLIC model)


add_library(NUMBERS_APP STATIC infrastructure/storage/storage.cpp app/application.cpp app/runner/runner.cpp infrastructure/log/log.cpp)
target_link_libraries(NUMBERS_APP PUBLIC NUMBERS_MODEL)
target_include_directories(NUMBERS_APP PUBLIC .)


find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(numbers main.cpp)

target_link_libraries(numbers Qt::Core Qt::Gui Qt::Widgets  NUMBERS_MODEL NUMBERS_APP)

include_directories(tests)